;��д�ߣ�����
;�����ӳ���findGoods��sellGoods��buyGoods��calculate��rank��rateprint��strcmp
.686P
.model flat, stdcall
.DATA
 printf          PROTO C :ptr sbyte,:VARARG
 GOODS  STRUCT        ;����洢�ṹ
    GOODSNAME  db 10 DUP(0);��Ʒ1 ����
    BUYPRICE   DW  0;������
    SELLPRICE  DW  0;���ۼ�
    BUYNUM     DW  0;��������
    SELLNUM    DW  0;��������
    RATE       DW  0;�����ʣ���δ���㣩
 GOODS  ENDS
 extern x:dword
 extern i:dword
 extern j:dword
 extern GOODNAME:byte
 extern number:dword
 extern ratelist:dword
 extern lpFet:byte
 extern lpFet1:byte
 extern lpFmt:byte
 extern lpFmt1:byte
 extern msg9:byte
 extern msg10:byte
 extern msg11:byte
 extern msg12:byte
 extern msg13:byte
 extern msg14:byte
 extern msg16:byte
 extern msg17:byte
 extern msg19:byte
 extern msg20:byte

.CODE

;�ӳ���findGoods
;���ܣ�������Ʒ�ӳ���
;��ڲ�������Ʒ����GOODNAME����Ʒ������N
;���ڲ�����ebx,�����ҳɹ��򷵻���Ʒ���ţ�δ���ҵ��򷵻�-1
;�����ӳ���strcmp
;�㷨˼�룺���αȽ���Ʒ������
;����x����ָ����Ʒ
findGoods proc GoodNum:dword,GoodAddr:dword
      mov x,0
FG1:  mov ebx,x
      imul ebx,20
      add ebx,GoodAddr
      push offset GOODNAME
      push ebx
      call strcmp
      add esp,8
      cmp eax,0
      jz FG2
      inc x
      mov ebx,GoodNum
      cmp x,ebx
      js FG1
      mov ebx,-1
      ret
FG2:  ret
findGoods endp

;���ܣ���Ʒ�����ӳ���
;��ڲ�����ebx:�洢��Ʒ���
;���ڲ�������
;�㷨˼�룺��
sellGoods proc 
      cmp ebx,-1
      je  L100
      cmp ebx,0
      jnb L101
L100: invoke printf,offset lpFet,offset msg16
      ret
L101: mov ax,[ebx].GOODS.BUYNUM;ax���������
      sub ax,[ebx].GOODS.SELLNUM;ax��Ϊʣ������
      cmp number,0;number>0
      js L102
      cmp eax,number;eax>number
      js L102
      mov ax,[ebx].GOODS.SELLNUM;eaxΪ��������
      add eax,number
      mov [ebx].GOODS.SELLNUM,ax
      invoke printf,offset lpFet,offset msg19
      ret
L102: invoke printf,offset lpFet,offset msg17
      ret
sellGoods endp

;���ܣ���Ʒ�����ӳ���
;��ڲ�����ebx:�洢��Ʒ���
;���ڲ�������
;�㷨˼�룺��
buyGoods proc w:dword
      local goodNumber:dword
      mov ebx,w
      mov goodNumber,ebx
      mov ebx,goodNumber
      cmp ebx,-1
      je  L103
      cmp ebx,0
      jnb L104
L103: invoke printf,offset lpFet,offset msg16
      ret
L104: mov ax,[ebx].GOODS.BUYNUM;eax���������
      cmp number,0;number>0
      js L105
      add eax,number
      mov [ebx].GOODS.BUYNUM,ax
      invoke printf,offset lpFet,offset msg20
      ret
L105: invoke printf,offset lpFet,offset msg17
      ret
buyGoods endp

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
      inc x
      mov ebx,GoodNum
      cmp x,ebx
      cmp x,ebx
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
rank proc GoodAddr:dword
      push eax
      push ebx
      push esi
      push edi
      mov i,0
      mov j,0
rank1:  
      ;ð��������ѭ��
      mov eax,i
      mov j,eax
rank2:  
      mov eax,i
      mov ebx,ratelist[eax*4] 
      imul ebx,20
      add ebx,GoodAddr                 ;����ratelist����iλ�õ���
      mov si,[ebx].GOODS.RATE       
      
      inc j;ð��������ѭ��
      cmp j,3
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
      cmp i,3
      jb rank1
      pop edi
      pop esi
      pop ebx
      pop eax
      ret
rank endp

;��������Ӻ���
rateprint proc GoodAddr:dword
      push ebx
      mov x,1
print1:  
      mov ebx,x;���ѭ��
      mov ebx,ratelist[ebx*4-4]
      imul ebx,20
      add ebx,GoodAddr
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

end