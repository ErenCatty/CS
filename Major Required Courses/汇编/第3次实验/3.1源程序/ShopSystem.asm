;编写者：钟逸
;包含主程序main
;包含宏定义PrintFindGoodMsg
.686P     
.model flat, stdcall
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 ExitProcess PROTO STDCALL :DWORD
 findGoods   proto:dword,:dword
 rateprint   proto:dword
 sellGoods   proto
 buyGoods    proto:dword
 calculate   proto:dword,:dword
 rank        proto:dword
 strcmp      proto
 winTimer    proto stdcall:dword
 printf          PROTO C :ptr sbyte,:VARARG
 scanf           PROTO C :ptr sbyte,:VARARG 
 public x
 public i
 public j
 public GOODNAME
 public number
 public ratelist
 public lpFet
 public lpFet1
 public lpFmt
 public lpFmt1
 public msg9
 public msg10
 public msg11
 public msg12
 public msg13
 public msg14
 public msg16
 public msg17
 public msg19
 public msg20

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
;宏指令
PrintFindGoodMsg macro v1
      mov v1,ebx
      cmp v1,-1
      je  PR1
      cmp v1,0
      jnb PR2
PR1:  invoke printf,offset lpFet,offset msg16
      jmp PREND
PR2:  invoke printf,offset lpFet1,offset msg9,offset GOODNAME
      invoke printf,offset lpFmt,offset msg10,[ebx].GOODS.BUYPRICE
      invoke printf,offset lpFmt,offset msg11,[ebx].GOODS.SELLPRICE
      invoke printf,offset lpFmt,offset msg12,[ebx].GOODS.BUYNUM
      invoke printf,offset lpFmt,offset msg13,[ebx].GOODS.SELLNUM
      invoke printf,offset ratefmt,offset msg14,[ebx].GOODS.RATE
PREND:
      endm

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
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke findGoods,N,offset GA1
      PrintFindGoodMsg ebx
      jmp system_start
      
case2:;出货
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg15
      invoke scanf,offset buf1,addr[number]
      invoke findGoods,N,offset GA1
      call sellGoods
      jmp system_start

case3:;进货
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg15
      invoke scanf,offset buf1,addr[number]
      invoke findGoods,N,offset GA1
      invoke buyGoods,ebx
      jmp system_start
      
case4:;计算各商品的利润率
      mov x,0
changelist1:      
      mov ebx,x
      mov ratelist[ebx*4],ebx
      inc x
      cmp x,4
      jb changelist1
      invoke calculate,N,offset GA1
      invoke rateprint,offset GA1
      jmp system_start

case5:;按利润率从高到低排序
      mov x,0
changelist2:      
      mov ebx,x
      mov ratelist[ebx*4],ebx
      inc x
      cmp x,4
      jb changelist2
      invoke rank,offset GA1
      invoke rateprint,offset GA1
      jmp system_start

case6:;计算算法时间
      invoke winTimer,0
      mov y,0
count_start:      
      inc y;计数器
      cmp y,1000          ;执行多次以使winTimer效果明显
      ja count_end
      mov x,0
changelist3:      
      mov ebx,x
      mov ratelist[ebx*4],ebx
      inc x
      cmp x,4
      jb changelist3
      invoke calculate,N,offset GA1
      invoke rank,offset GA1
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

end