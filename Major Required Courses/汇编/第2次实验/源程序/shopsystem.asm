.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 timeGetTime proto stdcall
 winTimer    proto stdcall:dword
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :ptr sbyte,:VARARG
 scanf           PROTO C :ptr sbyte,:VARARG
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 includelib  Winmm.lib

.DATA
lpFet db "%s",0dh,0ah,0
lpFet1 db "%s %s",0dh,0ah,0
lpFmt db "%s %d",0dh,0ah,0
lpFmt1 db "%s %hd",0dh,0ah,0
lpFmt2   db	"%d seconds",0ah, 0dh, 0
ratefmt db "%s %hd%%",0ah,0dh,0
buf db "%s",0
buf1 db "%d",0
BNAME  DB  'zhongyi',0 ;老板姓名（自己名字的拼音）
BPASS  DB  'U201914978',0 ;密码（自己的学号）
NAME1 DB 8 dup(0)
PASS DB 11 dup(0)
GOODNAME DB 10 DUP(0)
choice DD 0
x DD 0
y DD 0
z DD 0
i DD 0
j DD 0
number DD 0
ratelist DD 0,1,2,3,4
GOODS  STRUCT        ;货物存储结构
   GOODSNAME  db 10 DUP(0);商品1 名称
   BUYPRICE   DW  0;进货价
   SELLPRICE  DW  0;销售价
   BUYNUM     DW  0;进货数量
   SELLNUM    DW  0;已售数量
   RATE       DW  0;利润率（尚未计算）
GOODS  ENDS
N    EQU   30
GA1 GOODS<'PEN',15,20,70,25,0>
GA2 GOODS<'PENCIL',2,3,100,50,0>
GA3 GOODS<'BOOK',30,40,25,5,0>
GA4 GOODS<'RULER',3,4,200,150,0>
GAN GOODS N-4 DUP(<'TempValue',15,20,30,2,0>);除了4个已经具体定义了的商品信息以外，其他商品信息暂时假定为一样的。
INPUTNAME DB '请输入用户名: ',0
INPUTPASSWORD DB '请输入密码: ',0
OUTPUT DB '用户名或密码错误!',0
msg1 DB '             商品信息系统',0
msg2 DB '1.查找商品                          2.出货',0
msg3 DB '3.进货                              4.计算利润率',0
msg4 DB '5.根据商品利润率排序                6.计算+排序算法时间',0
msg5 DB '9.退出',0
msg6 DB '请输入选项：',0
msg7 DB '请重新输入选项：',0
msg8 DB '请输入商品名：',0
msg9 DB '商品:',0
msg10 DB '进价:',0
msg11 DB '售价:',0
msg12 DB '购货量:',0
msg13 DB '出货量:',0
msg14 DB '利润率:',0
msg15 DB '请输入数字',0
msg16 DB '无该货物!',0
msg17 DB '输入错误!',0
msg18 DB '功能未完成!',0
msg19 DB '出货成功!',0
msg20 DB '进货成功!',0
BUFFER DB 20
       DB ?
       DB 20 DUP(0)
__t1		dd	?
__t2		dd	?
__fmtTime	db	0ah,0dh,"Time elapsed is %ld ms",2 dup(0ah,0dh),0

.CODE
main proc c

;输入NAME
  invoke printf,offset lpFet,offset INPUTNAME
input_NAME:
  invoke scanf,offset buf,addr[NAME1]
;输入PASSWORD
  invoke printf,offset lpFet,offset INPUTPASSWORD
input_PASSWORD:
  invoke scanf,offset buf,addr[PASS]
compare_NAME:
  push offset BNAME
  push offset NAME1
  call strcmp
  add esp,8
  cmp eax,0
  jnz exit
compare_PASSWORD:
  push offset BPASS
  push offset PASS
  call strcmp
  add esp,8
  cmp eax,0
  jnz exit
system_start:
  invoke printf,offset lpFet,offset msg1
  invoke printf,offset lpFet,offset msg2
  invoke printf,offset lpFet,offset msg3
  invoke printf,offset lpFet,offset msg4
  invoke printf,offset lpFet,offset msg5
  invoke printf,offset lpFet,offset msg6
  invoke scanf,offset buf1,addr[choice]
  switch_start:
    cmp choice,1
    je case1
    cmp choice,2
    je case2
    cmp choice,3
    je case3
    cmp choice,4
    je case4
    cmp choice,5
    je case5
    cmp choice,6
    je case6
    cmp choice,9
    je case9
    invoke printf,offset lpFet,offset msg7;default
    jmp system_start
case1:;查找商品
      mov x,0
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
L21:  mov ebx,x
      imul ebx,20
      add ebx,offset GA1
      push offset GOODNAME
      push ebx
      call strcmp
      add esp,8
      cmp eax,0
      jz L2
      inc x
      cmp x,N
      js L21
      invoke printf,offset lpFet,offset msg16
      jmp system_start
L2:   invoke printf,offset lpFet1,offset msg9,offset GOODNAME
      invoke printf,offset lpFmt,offset msg10,[ebx].GOODS.BUYPRICE
      invoke printf,offset lpFmt,offset msg11,[ebx].GOODS.SELLPRICE
      invoke printf,offset lpFmt,offset msg12,[ebx].GOODS.BUYNUM
      invoke printf,offset lpFmt,offset msg13,[ebx].GOODS.SELLNUM
      invoke printf,offset ratefmt,offset msg14,[ebx].GOODS.RATE
      jmp system_start
case2:;出货
      mov x,0
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg15
      invoke scanf,offset buf1,addr[number]
L31:  mov ebx,x
      imul ebx,20
      add ebx,offset GA1
      push offset GOODNAME
      push ebx
      call strcmp
      add esp,8
      cmp eax,0
      jz L3
      inc x
      cmp x,N
      js L31
      invoke printf,offset lpFet,offset msg16
      jmp system_start
L3:   mov ax,[ebx].GOODS.BUYNUM;ax存进货数量
      sub ax,[ebx].GOODS.SELLNUM;ax变为剩余数量
      cmp number,0;number>0
      js L4
      cmp eax,number;eax>number
      js L4
      mov ax,[ebx].GOODS.SELLNUM;eax为已售数量
      add eax,number
      mov [ebx].GOODS.SELLNUM,ax
      invoke printf,offset lpFet,offset msg19
      jmp system_start
L4:   invoke printf,offset lpFet,offset msg17
      jmp system_start
case3:;进货
      mov x,0
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg15
      invoke scanf,offset buf1,addr[number]
L51:  mov ebx,x
      imul ebx,20
      add ebx,offset GA1
      push offset GOODNAME
      push ebx
      call strcmp
      add esp,8
      cmp eax,0
      jz L5
      inc x
      cmp x,N
      js L51
      invoke printf,offset lpFet,offset msg16
      jmp system_start
L5:   mov ax,[ebx].GOODS.BUYNUM;eax存进货数量
      cmp number,0;number>0
      js L6
      add eax,number
      mov [ebx].GOODS.BUYNUM,ax
      invoke printf,offset lpFet,offset msg20
      jmp system_start
L6:   invoke printf,offset lpFet,offset msg17
      jmp system_start
case4:;计算各商品的利润率
      mov x,0
changelist1:      
      mov ebx,x
      mov ratelist[ebx*4],ebx
      inc x
      cmp x,4
      jb changelist1
      call calculate
      jmp system_start
case5:;按利润率从高到低排序
      mov x,0
changelist2:      
      mov ebx,x
      mov ratelist[ebx*4],ebx
      inc x
      cmp x,4
      jb changelist2
      call rank
      call rateprint
      jmp system_start
case6:;计算算法时间
      invoke winTimer,0
      mov y,0
count_start:      
      inc y;计数器
      cmp y,1000000  ;执行多次以使winTimer效果明显
      ja count_end
      mov x,0
changelist3:      
      mov ebx,x
      mov ratelist[ebx*4],ebx
      inc x
      cmp x,4
      jb changelist3
      call calculate
      call rank
      jmp count_start
count_end:
      invoke winTimer,1
      jmp system_start
case9:
      jmp system_end
exit:
  invoke printf,offset lpFet,offset OUTPUT
system_end:
  invoke ExitProcess,0
main endp


;子程序strcmp str1，str2
;功能：比较两个字符串str1和str2的大小关系
;入口参数：两个串的首地址在堆栈中，str2的首地址先入栈
;出口参数：eax，若前串小，则（eax）为-1；若前串大，则为1；若相等，则为0
;算法思想：从串的最左端开始向右，逐一比较两个串对应字符的关系
;若两个对应字符不相等，则比较结束，由这两个字符的大小关系决定串的大小关系
;若两个对应字符相等且不是串的结束，则继续向右比较；若是0，则返回串相等
;寄存器分配
;edi,指向str1，即（edi）为串str1中待比较字符的地址
;esi，指向str2，即（esi）为串str2中待比较字符的地址
;dl，用于缓存当前读取的字符
strcmp proc
  push ebp
  mov ebp,esp
  push esi
  push edi
  push edx
  mov edi,[ebp+8];第一个串的起始地址放入edi中
  mov esi,[ebp+12];第二个串的起始地址放入esi中
strcmp_start:
  mov dl,[esi]
  cmp dl,30
  jz strcmp_large
  mov dl,[edi]
  cmp dl,30
  jz strcmp_little
  cmp dl,[esi]
  ja strcmp_large
  jb strcmp_little
  cmp dl,0         ;运行到这说明前面比较的两个字符相等
  je strcmp_equ
  inc esi
  inc edi
  jmp strcmp_start
strcmp_large:
  mov eax,1
  jmp strcmp_exit
strcmp_little:
  mov eax,-1
  jmp strcmp_exit
strcmp_equ:
  mov eax,0
  jmp strcmp_exit
strcmp_exit:
  pop edx
  pop edi
  pop esi
  pop ebp
  ret
strcmp endp

;功能：计算各商品的利润率
;入口参数：无
;出口参数：无
;算法思想：依次取出商品的进价，进货数量，售价，已售数量
;用售价与已售数量的乘积减去进价与进货数量的乘积的差除以进价与进货数量的乘积
;将结果存放在各对应商品的利润率单位中
;寄存器分配
;si，存放商品进价和进价与进货数量的乘积
;ax，存放商品进货数量、售价和差的低位
;dx，存放商品已售数量和差的高位
;变量x用来指定商品
calculate proc
      push eax
      push ebx
      push edi
      push esi
      mov x,0
cal:  mov edi,x
      imul edi,20
      add edi,offset GA1
      mov eax,0
      mov ebx,0
      mov esi,0
      ;invoke printf,offset lpFet,offset msg9
      ;invoke printf,offset lpFet,edi
      mov si,[edi].GOODS.BUYPRICE;取BUYPRICE
      mov ax,[edi].GOODS.BUYNUM;取BUYNUM
      imul si,ax
      mov ax,[edi].GOODS.SELLPRICE;取SELLPRICE
      mov dx,[edi].GOODS.SELLNUM;取SELLNUM
      imul ax,dx
      sub ax,si;ax存被除数低位
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx存被除数高位
      idiv si
      mov [edi].GOODS.RATE,ax
      ;invoke printf,offset lpFmt1,offset msg14,[edi].GOODS.RATE
      inc x
      cmp x,N
      js cal
      pop esi
      pop edi
      pop ebx
      pop eax
      ret
calculate endp

;功能：将商品按照利润率由高到低排序
;入口参数：无
;出口参数：无
;算法思想：依次取出商品的利润率
;用冒泡排序法进行排序
;寄存器分配
;ebx，用来保存当前商品的首地址和当前在ratelist中的位置
;si，存放当前商品的利润率
;eax，用来充当变量数据交换时的中间变量
;变量i用来控制冒泡排序的外循环
;变量j用来控制冒泡排序的内循环
;变量x用来控制结果输出循环
rank proc
      push eax
      push ebx
      push esi
      push edi
      mov i,0
      mov j,0
      mov x,0
      mov z,0
      add z,2
      add z,1
rank1:  
      mov ebx,i;冒泡排序外循环
      imul ebx,20
      add ebx,offset GA1
      mov si,[ebx].GOODS.RATE
      mov eax,i
      mov j,eax
rank2:  
      inc j;冒泡排序内循环
      cmp j,5
      ja rank3
      mov ebx,j
      imul ebx,20
      add ebx,offset GA1
      cmp [ebx].GOODS.RATE,si
      jng rank2
      mov ebx,j
      mov eax,ratelist[ebx*4]
      mov ebx,i
      mov edi,ratelist[ebx*4]
      mov ratelist[ebx*4],eax
      mov ebx,j
      mov ratelist[ebx*4],edi
      jmp rank2
rank3:  
      inc i
      cmp i,5
      jb rank1
      pop edi
      pop esi
      pop ebx
      pop eax
      ret
rank endp

;输出排序子函数
rateprint proc
      push ebx
      mov x,1
print1:  
      mov ebx,x;输出循环
      mov ebx,ratelist[ebx*4-4]
      imul ebx,20
      add ebx,offset GA1
      invoke printf,offset lpFet1,offset msg9,ebx
      invoke printf,offset lpFmt,offset msg10,[ebx].GOODS.BUYPRICE
      invoke printf,offset lpFmt,offset msg11,[ebx].GOODS.SELLPRICE
      invoke printf,offset lpFmt,offset msg12,[ebx].GOODS.BUYNUM
      invoke printf,offset lpFmt,offset msg13,[ebx].GOODS.SELLNUM
      invoke printf,offset lpFmt1,offset msg14,[ebx].GOODS.RATE
      inc x
      cmp x,6
      jb print1
      pop ebx
      ret
rateprint endp

winTimer	proc stdcall, flag:DWORD
		jmp	__L1
__L1:		call	timeGetTime
		cmp	flag, 0
		jnz	__L2
		mov	__t1, eax
		ret	4
__L2:		mov	__t2, eax
		sub	eax, __t1

		invoke	printf,offset __fmtTime,eax
		ret	4
winTimer	endp
end