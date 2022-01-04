.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 printf          PROTO C :ptr sbyte,:VARARG
 scanf           PROTO C :ptr sbyte,:VARARG
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib

.DATA
lpFet db "%s",0dh,0ah,0
lpFet1 db "%s %s",0dh,0ah,0
lpFmt db "%s %d",0dh,0ah,0
lpFmt1 db "%s %hd",'%%',0dh,0ah,0
buf db "%s",0
buf1 db "%d",0
BNAME  DB  'zhongyi',0 ;老板姓名（自己名字的拼音）
BPASS  DB  'U201914978',0 ;密码（自己的学号）
USERNAME DB 9 dup(0)
PASSWORD DB 11 dup(0)
GOODNAME DB 10 DUP(0)
N    EQU   30
choice DB 0
x DD 0
number DD 0
GA1   DB   'PEN',7 DUP(0) ;商品1 名称
      DW   15,20,70,25,0  ; 进货价、销售价、进货数量、已售数量，利润率（尚未计算）
GA2   DB  'PENCIL', 4 DUP(0) ;商品2 名称
      DW   2,3,100,50,0
GA3   DB   'BOOK',6 DUP(0) ;商品3 名称
      DW   30,40,25,5,0
GA4   DB   'RULER',5 DUP(0) ;商品4 名称
      DW   3,4,200,150,0
GAN   DB N-4 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,0,0) ;除了4个已经具体定义了的商品信息以外，其他商品信息暂时假定为一样的。
NAMErequest     DB '请输入用户名: ',0
PASSWORDrequest DB '请输入密码: ',0
WARNING  DB   '用户名或者密码输入错误',0dh,0ah,0
WARNING1 DB   '请重新输入正确的选择',0dh,0ah,0
menu1    DB   '           商品信息后台管理系统',0dh,0ah,0
menu2    DB   '1.查找指定商品并显示其信息',0dh,0ah,0
menu3    DB   '2.出货',0dh,0ah,0
menu4    DB   '3.补货',0dh,0ah,0
menu5    DB   '4.计算商品的利润率',0dh,0ah,0
menu6    DB   '9.退出',0dh,0ah,0
menu7    DB   '请输入数字1…9选择功能：',0dh,0ah,0

msg1  DB '请输入货物名：',0
msg2  DB '无该货物',0
msg3  DB '货物名:',0
msg4  DB '请输入本次销售数量：',0
msg5  DB '货物数量成功修改',0
msg6  DB '出货量输入错误',0
msg7  DB '商品进货量修改成功',0
msg8  DB '商品利润率:',0
msg9  DB '该功能有待实现!',0
msg10 DB '进货价:',0
msg11 DB '销售价:',0
msg12 DB '进货数量:',0
msg13 DB '已售数量:',0
msg14 DB '货物名：PEN',0dh,0ah,0
msg15 DB '货物名：PENCIL',0dh,0ah,0
msg16 DB '货物名：BOOK',0dh,0ah,0
msg17 DB '货物名：RULER',0dh,0ah,0
msg18 DB '请输入本次进货数量：',0

.CODE

main proc c
NAME_INPUT:                    ;用户名输入以及检测
  invoke printf,offset NAMErequest
  invoke scanf,offset buf,addr[USERNAME]
compare_NAME:
  push offset BNAME
  push offset USERNAME
  call strcmp
  add esp,8
  cmp eax,0
  jnz exit
PASSWORD_INPUT:                ;密码输入以及检测
  invoke printf,offset PASSWORDrequest
  invoke scanf,offset buf,addr[PASSWORD]
compare_PASSWORD:
  push offset BPASS
  push offset PASSWORD
  call strcmp
  add esp,8
  cmp eax,0
  jnz exit

system_start:
  invoke printf,offset menu1
  invoke printf,offset menu2
  invoke printf,offset menu3
  invoke printf,offset menu4
  invoke printf,offset menu5
  invoke printf,offset menu6
  invoke printf,offset menu7
  invoke scanf,offset buf1,addr[choice]
  switch_start:
    cmp choice,1
    jz case1
    cmp choice,2
    jz case2
    cmp choice,3
    jz case3
    cmp choice,4
    jz case4
    cmp choice,5
    jz case5
    cmp choice,9
    jz case9
    invoke printf,offset WARNING1;default
    jmp system_start

    case1:           ;依次查找商品
    mov x,0
      invoke printf,offset msg1
      invoke scanf,offset buf,addr[GOODNAME]
      push offset GOODNAME
      push offset GA1
      call strcmp
      cmp eax,0
      jz L2
      inc x
      push offset GOODNAME
      push offset GA2
      call strcmp
      cmp eax,0
      jz L2
      inc x
      push offset GOODNAME
      push offset GA3
      call strcmp
      cmp eax,0
      jz L2
      inc x
      push offset GOODNAME
      push offset GA4
      call strcmp
      cmp eax,0
      jz L2
      invoke printf,offset lpFet,offset msg2     ;无该商品
      jmp system_start
L2:   mov ebx,x
      imul ebx,20        ;每个段GA中的内存大小是一定的
      invoke printf,offset lpFet1,offset msg3,offset GOODNAME
      add ebx,10
      invoke printf,offset lpFmt,offset msg10,GA1[ebx]
      add ebx,2
      invoke printf,offset lpFmt,offset msg11,GA1[ebx]
      add ebx,2
      invoke printf,offset lpFmt,offset msg12,GA1[ebx]
      add ebx,2
      invoke printf,offset lpFmt,offset msg13,GA1[ebx]
      jmp system_start

    case2:               ;出货（修改货物数量)
    mov x,0
      invoke printf,offset lpFet,offset msg1
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg4
      invoke scanf,offset buf1,addr[number]
      push offset GOODNAME
      push offset GA1
      call strcmp
      cmp eax,0
      jz L3
      inc x
      push offset GOODNAME
      push offset GA2
      call strcmp
      cmp eax,0
      jz L3
      inc x
      push offset GOODNAME
      push offset GA3
      call strcmp
      cmp eax,0
      jz L3
      inc x
      push offset GOODNAME
      push offset GA4
      call strcmp
      cmp eax,0
      jz L3
      invoke printf,offset lpFet,offset msg2
      jmp system_start
L3:   mov ebx,x
      imul ebx,20
      add ebx,14
      mov ax,word ptr GA1[ebx]    ;ax存进货数量
      add ebx,2
      sub ax,word ptr GA1[ebx]    ;GA1[ebx]为已售数量，ax变为剩余数量
      cmp number,0                ;number>0
      js L4
      cmp eax,number;eax>number
      js L4
      mov ax,word ptr GA1[ebx]    ;eax为已售数量
      add eax,number
      mov word ptr GA1[ebx],ax
      invoke printf,offset lpFet,offset msg5
      jmp system_start
L4:   invoke printf,offset lpFet,offset msg6
      jmp system_start

    case3:                        ;进货
    mov x,0
      invoke printf,offset lpFet,offset msg1
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg18
      invoke scanf,offset buf1,addr[number]
      push offset GOODNAME
      push offset GA1
      call strcmp
      cmp eax,0
      jz L5
      inc x
      push offset GOODNAME
      push offset GA2
      call strcmp
      cmp eax,0
      jz L5
      inc x
      push offset GOODNAME
      push offset GA3
      call strcmp
      cmp eax,0
      jz L5
      inc x
      push offset GOODNAME
      push offset GA4
      call strcmp
      cmp eax,0
      jz L5
      invoke printf,offset lpFet,offset msg2
      jmp system_start
L5:   mov ebx,x
      imul ebx,20
      add ebx,14
      mov eax,dword ptr GA1[ebx]       ;eax存进货数量
      cmp number,0                     ;number>0
      js L6
      add eax,number
      mov word ptr GA1[ebx],ax
      invoke printf,offset lpFet,offset msg7
      jmp system_start
L6:   invoke printf,offset lpFet,offset msg6
      jmp system_start

    case4:                             ;计算各商品的利润率
      mov x,0
      mov edi,x
      imul edi,20
      mov eax,0
      mov ebx,0
      mov esi,0
      invoke printf,offset msg14
      add edi,10
      mov si,word ptr GA1[edi]        ;取cost
      add edi,4
      mov ax,word ptr GA1[edi]        ;取quantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi]        ;取price
      add edi,4
      mov dx,word ptr GA1[edi]        ;取quantityout
      imul ax,dx
      sub ax,si;ax存被除数低位
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx存被除数高位
      idiv si
      add edi,2
      mov word ptr GA1[edi],ax
      invoke printf,offset lpFmt1,offset msg8,word ptr GA1[edi]
      inc x
      mov edi,x
      imul edi,20
      mov eax,0
      mov ebx,0
      mov esi,0
      invoke printf,offset msg15
      add edi,10
      mov si,word ptr GA1[edi];取cost
      add edi,4
      mov ax,word ptr GA1[edi];取quantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi];取price
      add edi,4
      mov dx,word ptr GA1[edi];取quantityout
      imul ax,dx
      sub ax,si;ax存被除数低位
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx存被除数高位
      idiv si
      add edi,2
      mov word ptr GA1[edi],ax
      invoke printf,offset lpFmt1,offset msg8,word ptr GA1[edi]
      inc x
      mov edi,x
      imul edi,20
      mov eax,0
      mov ebx,0
      mov esi,0
      invoke printf,offset msg16
      add edi,10
      mov si,word ptr GA1[edi];取cost
      add edi,4
      mov ax,word ptr GA1[edi];取quantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi];取price
      add edi,4
      mov dx,word ptr GA1[edi];取quantityout
      imul ax,dx
      sub ax,si;ax存被除数低位
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx存被除数高位
      idiv si
      add edi,2
      mov word ptr GA1[edi],ax
      invoke printf,offset lpFmt1,offset msg8,word ptr GA1[edi]
      inc x
      mov edi,x
      imul edi,20
      mov eax,0
      mov ebx,0
      mov esi,0
      invoke printf,offset msg17
      add edi,10
      mov si,word ptr GA1[edi];取cost
      add edi,4
      mov ax,word ptr GA1[edi];取quantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi];取price
      add edi,4
      mov dx,word ptr GA1[edi];取quantityout
      imul ax,dx
      sub ax,si;ax存被除数低位
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx存被除数高位
      idiv si
      add edi,2
      mov word ptr GA1[edi],ax
      invoke printf,offset lpFmt1,offset msg8,word ptr GA1[edi]
      jmp system_start
    case5:
      invoke printf,offset lpFet,offset msg9
      jmp system_start

    case9:
      jmp system_end
exit:
  invoke printf,offset WARNING
system_end:
  invoke ExitProcess,0
main endp


;子程序strcmp str1，str2
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