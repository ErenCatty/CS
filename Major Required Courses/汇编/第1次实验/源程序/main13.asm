.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess �� kernel32.lib��ʵ��
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
BNAME  DB  'zhongyi',0 ;�ϰ��������Լ����ֵ�ƴ����
BPASS  DB  'U201914978',0 ;���루�Լ���ѧ�ţ�
USERNAME DB 9 dup(0)
PASSWORD DB 11 dup(0)
GOODNAME DB 10 DUP(0)
N    EQU   30
choice DB 0
x DD 0
number DD 0
GA1   DB   'PEN',7 DUP(0) ;��Ʒ1 ����
      DW   15,20,70,25,0  ; �����ۡ����ۼۡ��������������������������ʣ���δ���㣩
GA2   DB  'PENCIL', 4 DUP(0) ;��Ʒ2 ����
      DW   2,3,100,50,0
GA3   DB   'BOOK',6 DUP(0) ;��Ʒ3 ����
      DW   30,40,25,5,0
GA4   DB   'RULER',5 DUP(0) ;��Ʒ4 ����
      DW   3,4,200,150,0
GAN   DB N-4 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,0,0) ;����4���Ѿ����嶨���˵���Ʒ��Ϣ���⣬������Ʒ��Ϣ��ʱ�ٶ�Ϊһ���ġ�
NAMErequest     DB '�������û���: ',0
PASSWORDrequest DB '����������: ',0
WARNING  DB   '�û������������������',0dh,0ah,0
WARNING1 DB   '������������ȷ��ѡ��',0dh,0ah,0
menu1    DB   '           ��Ʒ��Ϣ��̨����ϵͳ',0dh,0ah,0
menu2    DB   '1.����ָ����Ʒ����ʾ����Ϣ',0dh,0ah,0
menu3    DB   '2.����',0dh,0ah,0
menu4    DB   '3.����',0dh,0ah,0
menu5    DB   '4.������Ʒ��������',0dh,0ah,0
menu6    DB   '9.�˳�',0dh,0ah,0
menu7    DB   '����������1��9ѡ���ܣ�',0dh,0ah,0

msg1  DB '�������������',0
msg2  DB '�޸û���',0
msg3  DB '������:',0
msg4  DB '�����뱾������������',0
msg5  DB '���������ɹ��޸�',0
msg6  DB '�������������',0
msg7  DB '��Ʒ�������޸ĳɹ�',0
msg8  DB '��Ʒ������:',0
msg9  DB '�ù����д�ʵ��!',0
msg10 DB '������:',0
msg11 DB '���ۼ�:',0
msg12 DB '��������:',0
msg13 DB '��������:',0
msg14 DB '��������PEN',0dh,0ah,0
msg15 DB '��������PENCIL',0dh,0ah,0
msg16 DB '��������BOOK',0dh,0ah,0
msg17 DB '��������RULER',0dh,0ah,0
msg18 DB '�����뱾�ν���������',0

.CODE

main proc c
NAME_INPUT:                    ;�û��������Լ����
  invoke printf,offset NAMErequest
  invoke scanf,offset buf,addr[USERNAME]
compare_NAME:
  push offset BNAME
  push offset USERNAME
  call strcmp
  add esp,8
  cmp eax,0
  jnz exit
PASSWORD_INPUT:                ;���������Լ����
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

    case1:           ;���β�����Ʒ
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
      invoke printf,offset lpFet,offset msg2     ;�޸���Ʒ
      jmp system_start
L2:   mov ebx,x
      imul ebx,20        ;ÿ����GA�е��ڴ��С��һ����
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

    case2:               ;�������޸Ļ�������)
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
      mov ax,word ptr GA1[ebx]    ;ax���������
      add ebx,2
      sub ax,word ptr GA1[ebx]    ;GA1[ebx]Ϊ����������ax��Ϊʣ������
      cmp number,0                ;number>0
      js L4
      cmp eax,number;eax>number
      js L4
      mov ax,word ptr GA1[ebx]    ;eaxΪ��������
      add eax,number
      mov word ptr GA1[ebx],ax
      invoke printf,offset lpFet,offset msg5
      jmp system_start
L4:   invoke printf,offset lpFet,offset msg6
      jmp system_start

    case3:                        ;����
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
      mov eax,dword ptr GA1[ebx]       ;eax���������
      cmp number,0                     ;number>0
      js L6
      add eax,number
      mov word ptr GA1[ebx],ax
      invoke printf,offset lpFet,offset msg7
      jmp system_start
L6:   invoke printf,offset lpFet,offset msg6
      jmp system_start

    case4:                             ;�������Ʒ��������
      mov x,0
      mov edi,x
      imul edi,20
      mov eax,0
      mov ebx,0
      mov esi,0
      invoke printf,offset msg14
      add edi,10
      mov si,word ptr GA1[edi]        ;ȡcost
      add edi,4
      mov ax,word ptr GA1[edi]        ;ȡquantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi]        ;ȡprice
      add edi,4
      mov dx,word ptr GA1[edi]        ;ȡquantityout
      imul ax,dx
      sub ax,si;ax�汻������λ
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx�汻������λ
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
      mov si,word ptr GA1[edi];ȡcost
      add edi,4
      mov ax,word ptr GA1[edi];ȡquantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi];ȡprice
      add edi,4
      mov dx,word ptr GA1[edi];ȡquantityout
      imul ax,dx
      sub ax,si;ax�汻������λ
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx�汻������λ
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
      mov si,word ptr GA1[edi];ȡcost
      add edi,4
      mov ax,word ptr GA1[edi];ȡquantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi];ȡprice
      add edi,4
      mov dx,word ptr GA1[edi];ȡquantityout
      imul ax,dx
      sub ax,si;ax�汻������λ
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx�汻������λ
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
      mov si,word ptr GA1[edi];ȡcost
      add edi,4
      mov ax,word ptr GA1[edi];ȡquantityin
      imul si,ax
      sub edi,2
      mov ax,word ptr GA1[edi];ȡprice
      add edi,4
      mov dx,word ptr GA1[edi];ȡquantityout
      imul ax,dx
      sub ax,si;ax�汻������λ
      cwde
      imul eax,100
      mov edx,eax
      shr edx,16;dx�汻������λ
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


;�ӳ���strcmp str1��str2
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

end