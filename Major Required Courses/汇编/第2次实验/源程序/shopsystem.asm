.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 timeGetTime proto stdcall
 winTimer    proto stdcall:dword
 includelib  kernel32.lib  ; ExitProcess �� kernel32.lib��ʵ��
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
case2:;����
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
L3:   mov ax,[ebx].GOODS.BUYNUM;ax���������
      sub ax,[ebx].GOODS.SELLNUM;ax��Ϊʣ������
      cmp number,0;number>0
      js L4
      cmp eax,number;eax>number
      js L4
      mov ax,[ebx].GOODS.SELLNUM;eaxΪ��������
      add eax,number
      mov [ebx].GOODS.SELLNUM,ax
      invoke printf,offset lpFet,offset msg19
      jmp system_start
L4:   invoke printf,offset lpFet,offset msg17
      jmp system_start
case3:;����
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
L5:   mov ax,[ebx].GOODS.BUYNUM;eax���������
      cmp number,0;number>0
      js L6
      add eax,number
      mov [ebx].GOODS.BUYNUM,ax
      invoke printf,offset lpFet,offset msg20
      jmp system_start
L6:   invoke printf,offset lpFet,offset msg17
      jmp system_start
case4:;�������Ʒ��������
      mov x,0
changelist1:      
      mov ebx,x
      mov ratelist[ebx*4],ebx
      inc x
      cmp x,4
      jb changelist1
      call calculate
      jmp system_start
case5:;�������ʴӸߵ�������
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
case6:;�����㷨ʱ��
      invoke winTimer,0
      mov y,0
count_start:      
      inc y;������
      cmp y,1000000  ;ִ�ж����ʹwinTimerЧ������
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


;�ӳ���strcmp str1��str2
;���ܣ��Ƚ������ַ���str1��str2�Ĵ�С��ϵ
;��ڲ��������������׵�ַ�ڶ�ջ�У�str2���׵�ַ����ջ
;���ڲ�����eax����ǰ��С����eax��Ϊ-1����ǰ������Ϊ1������ȣ���Ϊ0
;�㷨˼�룺�Ӵ�������˿�ʼ���ң���һ�Ƚ���������Ӧ�ַ��Ĺ�ϵ
;��������Ӧ�ַ�����ȣ���ȽϽ��������������ַ��Ĵ�С��ϵ�������Ĵ�С��ϵ
;��������Ӧ�ַ�����Ҳ��Ǵ��Ľ�������������ұȽϣ�����0���򷵻ش����
;�Ĵ�������
;edi,ָ��str1������edi��Ϊ��str1�д��Ƚ��ַ��ĵ�ַ
;esi��ָ��str2������esi��Ϊ��str2�д��Ƚ��ַ��ĵ�ַ
;dl�����ڻ��浱ǰ��ȡ���ַ�
strcmp proc
  push ebp
  mov ebp,esp
  push esi
  push edi
  push edx
  mov edi,[ebp+8];��һ��������ʼ��ַ����edi��
  mov esi,[ebp+12];�ڶ���������ʼ��ַ����esi��
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
  cmp dl,0         ;���е���˵��ǰ��Ƚϵ������ַ����
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

;���ܣ��������Ʒ��������
;��ڲ�������
;���ڲ�������
;�㷨˼�룺����ȡ����Ʒ�Ľ��ۣ������������ۼۣ���������
;���ۼ������������ĳ˻���ȥ��������������ĳ˻��Ĳ���Խ�������������ĳ˻�
;���������ڸ���Ӧ��Ʒ�������ʵ�λ��
;�Ĵ�������
;si�������Ʒ���ۺͽ�������������ĳ˻�
;ax�������Ʒ�����������ۼۺͲ�ĵ�λ
;dx�������Ʒ���������Ͳ�ĸ�λ
;����x����ָ����Ʒ
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
      mov si,[edi].GOODS.BUYPRICE;ȡBUYPRICE
      mov ax,[edi].GOODS.BUYNUM;ȡBUYNUM
      imul si,ax
      mov ax,[edi].GOODS.SELLPRICE;ȡSELLPRICE
      mov dx,[edi].GOODS.SELLNUM;ȡSELLNUM
      imul ax,dx
      sub ax,si;ax�汻������λ
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx�汻������λ
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

;���ܣ�����Ʒ�����������ɸߵ�������
;��ڲ�������
;���ڲ�������
;�㷨˼�룺����ȡ����Ʒ��������
;��ð�����򷨽�������
;�Ĵ�������
;ebx���������浱ǰ��Ʒ���׵�ַ�͵�ǰ��ratelist�е�λ��
;si����ŵ�ǰ��Ʒ��������
;eax�������䵱�������ݽ���ʱ���м����
;����i��������ð���������ѭ��
;����j��������ð���������ѭ��
;����x�������ƽ�����ѭ��
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
      mov ebx,i;ð��������ѭ��
      imul ebx,20
      add ebx,offset GA1
      mov si,[ebx].GOODS.RATE
      mov eax,i
      mov j,eax
rank2:  
      inc j;ð��������ѭ��
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

;��������Ӻ���
rateprint proc
      push ebx
      mov x,1
print1:  
      mov ebx,x;���ѭ��
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