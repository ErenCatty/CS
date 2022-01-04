.686P
.model flat,stdcall
 printf          PROTO C :ptr sbyte,:VARARG
 public findGoods
 public sellGoods
 public buyGoods
 public calculate
 public rank
 public rateprint
 extern number:dword
 extern GoodName:byte
 extern GoodNumber:dword
 extern ratelist:dword
.DATA
 lpFet db "%s",0dh,0ah,0
 lpFet1 db "%s %s",0dh,0ah,0
 lpFmt db "%s %d",0dh,0ah,0
 lpFmt1 db "%s %hd",0dh,0ah,0
 x DD 0
 GOODS  STRUCT        ;货物存储结构
    GOODSNAME  db 10 DUP(0);商品1 名称
    BUYPRICE   DW  0;进货价
    SELLPRICE  DW  0;销售价
    BUYNUM     DW  0;进货数量
    SELLNUM    DW  0;已售数量
    RATE       DW  0;利润率（尚未计算）
 GOODS  ENDS
 msg9 DB '商品:',0
 msg10 DB '进价:',0
 msg11 DB '售价:',0
 msg12 DB '购货量:',0
 msg13 DB '出货量:',0
 msg14 DB '利润率:',0
 msg16 DB '无该货物!',0
 msg17 DB '输入错误!',0
 msg19 DB '出货成功!',0
 msg20 DB '进货成功!',0
.CODE

;子程序：findGoods
;功能：查找商品子程序
;入口参数：商品名称GOODNAME、商品总数量N
;出口参数：GoodNumber,若查找成功则返回商品代号；未查找到则返回-1
;调用子程序：strcmp
;算法思想：依次比较商品的名称
;变量x用来指定商品
findGoods proc GoodNum:dword,GoodAddr:dword
      mov x,0
FG1:  mov ebx,x
      imul ebx,20
      add ebx,GoodAddr
      push offset GoodName
      push ebx
      call strcmp
      add esp,8
      cmp eax,0
      jz FG2
      inc x
      mov ebx,GoodNum
      cmp x,ebx
      js FG1
      mov GoodNumber,-1
      ret
FG2:  mov eax,x
      mov GoodNumber,eax
      ret
findGoods endp

;功能：商品出货子程序
;入口参数：ebx:存储商品序号
;出口参数：无
;算法思想：略
sellGoods proc 
      cmp ebx,-1
      je  L100
      cmp ebx,0
      jnb L101
L100: invoke printf,offset lpFet,offset msg16
      ret
L101: mov ax,[ebx].GOODS.BUYNUM;ax存进货数量
      sub ax,[ebx].GOODS.SELLNUM;ax变为剩余数量
      cmp number,0;number>0
      js L102
      cmp eax,number;eax>number
      js L102
      mov ax,[ebx].GOODS.SELLNUM;eax为已售数量
      add eax,number
      mov [ebx].GOODS.SELLNUM,ax
      invoke printf,offset lpFet,offset msg19
      ret
L102: invoke printf,offset lpFet,offset msg17
      ret
sellGoods endp

;功能：商品购货子程序
;入口参数：ebx:存储商品序号
;出口参数：无
;算法思想：略
buyGoods proc
      cmp ebx,-1
      je  L103
      cmp ebx,0
      jnb L104
L103: invoke printf,offset lpFet,offset msg16
      ret
L104: mov ax,[ebx].GOODS.BUYNUM;eax存进货数量
      cmp number,0;number>0
      js L105
      add eax,number
      mov [ebx].GOODS.BUYNUM,ax
      invoke printf,offset lpFet,offset msg20
      ret
L105: invoke printf,offset lpFet,offset msg17
      ret
buyGoods endp

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
calculate proc GoodNum:dword,GoodAddr:dword
      push eax
      push ebx
      push edi
      push esi
      mov x,0
cal:  mov edi,x
      imul edi,20
      add edi,GoodAddr
      mov eax,0
      mov ebx,0
      mov esi,0
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
      inc x
      mov ebx,GoodNum
      cmp x,ebx
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
rank proc GoodNum:dword,GoodAddr:dword
      local i:dword,j:dword
      push eax
      push ebx
      push esi
      push edi
      mov i,0
      mov j,0
rank1:  
      ;冒泡排序外循环
      mov eax,i
      mov j,eax
rank2:  
      mov eax,i
      mov ebx,ratelist[eax*4] 
      imul ebx,20
      add ebx,GoodAddr                 ;查找ratelist表中i位置的数
      mov si,[ebx].GOODS.RATE       
      
      inc j;冒泡排序内循环
      mov eax,GoodNum
      cmp j,eax
      ja rank3
      mov eax,j
      mov ebx,ratelist[eax*4]
      imul ebx,20
      add ebx,GoodAddr 
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
      mov eax,GoodNum
      cmp i,eax
      jb rank1
      pop edi
      pop esi
      pop ebx
      pop eax
      ret
rank endp

;输出排序子函数
rateprint proc GoodNum:dword,GoodAddr:dword
      push ebx
      mov x,0
print1:  
      mov ebx,x;输出循环
      mov ebx,ratelist[ebx*4]
      imul ebx,20
      add ebx,GoodAddr
      invoke printf,offset lpFet1,offset msg9,ebx
      invoke printf,offset lpFmt,offset msg10,[ebx].GOODS.BUYPRICE
      invoke printf,offset lpFmt,offset msg11,[ebx].GOODS.SELLPRICE
      invoke printf,offset lpFmt,offset msg12,[ebx].GOODS.BUYNUM
      invoke printf,offset lpFmt,offset msg13,[ebx].GOODS.SELLNUM
      invoke printf,offset lpFmt1,offset msg14,[ebx].GOODS.RATE
      inc x
      mov ebx,GoodNum
      cmp x,ebx
      jb print1
      pop ebx
      ret
rateprint endp

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

end