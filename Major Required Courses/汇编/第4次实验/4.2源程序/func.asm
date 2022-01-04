;编写者：钟逸
;包含子程序findGoods、sellGoods、buyGoods、calculate、rank、rateprint、strcmp
.686P
.model flat, stdcall
.DATA
 printf          PROTO C :ptr sbyte,:VARARG
 GOODS  STRUCT        ;货物存储结构
    GOODSNAME  db 10 DUP(0);商品1 名称
    BUYPRICE   DW  0;进货价
    SELLPRICE  DW  0;销售价
    BUYNUM     DW  0;进货数量
    SELLNUM    DW  0;已售数量
    RATE       DW  0;利润率（尚未计算）
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

;子程序：findGoods
;功能：查找商品子程序
;入口参数：商品名称GOODNAME、商品总数量N
;出口参数：ebx,若查找成功则返回商品代号；未查找到则返回-1
;调用子程序：strcmp
;算法思想：依次比较商品的名称
;变量x用来指定商品
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