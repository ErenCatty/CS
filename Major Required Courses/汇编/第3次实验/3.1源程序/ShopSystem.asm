;��д�ߣ�����
;����������main
;�����궨��PrintFindGoodMsg
.686P     
.model flat, stdcall
 includelib  kernel32.lib  ; ExitProcess �� kernel32.lib��ʵ��
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
BNAME  DB  'zhongyi',0 ;�ϰ��������Լ����ֵ�ƴ����
BPASS  DB  'U201914978',0 ;���루�Լ���ѧ�ţ�
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
GOODS  STRUCT        ;����洢�ṹ
   GOODSNAME  db 10 DUP(0);��Ʒ1 ����
   BUYPRICE   DW  0;������
   SELLPRICE  DW  0;���ۼ�
   BUYNUM     DW  0;��������
   SELLNUM    DW  0;��������
   RATE       DW  0;�����ʣ���δ���㣩
GOODS  ENDS
N    EQU   30
GA1 GOODS<'PEN',15,20,70,25,0>
GA2 GOODS<'PENCIL',2,3,100,50,0>
GA3 GOODS<'BOOK',30,40,25,5,0>
GA4 GOODS<'RULER',3,4,200,150,0>
GAN GOODS N-4 DUP(<'TempValue',15,20,30,2,0>);����4���Ѿ����嶨���˵���Ʒ��Ϣ���⣬������Ʒ��Ϣ��ʱ�ٶ�Ϊһ���ġ�
INPUTNAME DB '�������û���: ',0
INPUTPASSWORD DB '����������: ',0
OUTPUT DB '�û������������!',0
msg1 DB '             ��Ʒ��Ϣϵͳ',0
msg2 DB '1.������Ʒ                          2.����',0
msg3 DB '3.����                              4.����������',0
msg4 DB '5.������Ʒ����������                6.����+�����㷨ʱ��',0
msg5 DB '9.�˳�',0
msg6 DB '������ѡ�',0
msg7 DB '����������ѡ�',0
msg8 DB '��������Ʒ����',0
msg9 DB '��Ʒ:',0
msg10 DB '����:',0
msg11 DB '�ۼ�:',0
msg12 DB '������:',0
msg13 DB '������:',0
msg14 DB '������:',0
msg15 DB '����������',0
msg16 DB '�޸û���!',0
msg17 DB '�������!',0
msg18 DB '����δ���!',0
msg19 DB '�����ɹ�!',0
msg20 DB '�����ɹ�!',0
BUFFER DB 20
       DB ?
       DB 20 DUP(0)
__t1		dd	?
__t2		dd	?
__fmtTime	db	0ah,0dh,"Time elapsed is %ld ms",2 dup(0ah,0dh),0

.CODE
;��ָ��
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
;����NAME
  invoke printf,offset lpFet,offset INPUTNAME
input_NAME:
  invoke scanf,offset buf,addr[NAME1]
;����PASSWORD
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
case1:;������Ʒ
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke findGoods,N,offset GA1
      PrintFindGoodMsg ebx
      jmp system_start
      
case2:;����
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg15
      invoke scanf,offset buf1,addr[number]
      invoke findGoods,N,offset GA1
      call sellGoods
      jmp system_start

case3:;����
      invoke printf,offset lpFet,offset msg8
      invoke scanf,offset buf,addr[GOODNAME]
      invoke printf,offset lpFet,offset msg15
      invoke scanf,offset buf1,addr[number]
      invoke findGoods,N,offset GA1
      invoke buyGoods,ebx
      jmp system_start
      
case4:;�������Ʒ��������
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

case5:;�������ʴӸߵ�������
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

case6:;�����㷨ʱ��
      invoke winTimer,0
      mov y,0
count_start:      
      inc y;������
      cmp y,1000          ;ִ�ж����ʹwinTimerЧ������
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