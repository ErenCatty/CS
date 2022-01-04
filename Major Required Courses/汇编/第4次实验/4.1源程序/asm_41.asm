;  程序功能：每隔约1秒钟 显示一次当前的时间（时：分：秒）
;            按任意键结束本程序的运行
;        为了更好的展示正在运行的程序被打断，时间的显示和字符串的显示交杂在一起

;  涉及的知识点：
;  (1) 8号中断
;  (2) 扩充8号中断的中断处理程序
;  (3) 中断处理程序驻留在内存
;  (4) 获取系统当前时间
;  (5) 在屏幕指定位置显示串

.386
STACK  SEGMENT  USE16  STACK ;主程序的堆栈段
       DB  200  DUP (0)
STACK  ENDS

CODE   SEGMENT USE16
       ASSUME CS:CODE, SS:STACK
;新的INT08H使用的变址
  COUNT  DB  18           ;“滴答”计数
  HOUR   DB  ?, ?, ':'    ;时的ASCI码
  MIN    DB  ?, ?, ':'    ;分的ASCII码
  SEC    DB  ?, ?         ;秒的ASCII码
  BUF_LEN = $ - HOUR      ;计算显示信息长度
  CURSOR   DW  ?          ;原光标位置
  OLD_INT  DW  ?, ?       ;原INT08H的中断矢量
  MESSAGE  DB  0dh,0ah,'press any key to return',0dh,0ah,0dh,0ah,'$'
  PROMPT   DB  0DH, 0AH, ' Please select:   ' 
           DB  0DH, 0AH, '      1:  simple display chars'
           DB  0DH, 0AH, '      2:  new 8  interrupt,  and restore when return'
           DB  0DH, 0AH, '      3:  new 8  interrupt,  and resudile when return'
           DB  0DH, 0AH, '$'
 SELECT_ITEM   DB  0


; -------------------------------------NEW08H----------------------------------------------------
; 扩充的 8号中断处理程序  
NEW08H  PROC  FAR
        PUSHF
        CALL  DWORD  PTR  OLD_INT
                                   ;完成原功能(变量在汇编后使用的默认段寄存器
                                   ;为DS,故必须加段前缀CS:)
        DEC   COUNT                ; (倒)计数
        JZ    DISP                 ;计满18次,转时钟显示
        IRET                       ;未计满,中断返回
  DISP: MOV  COUNT,18              ; 重置计数初值
        STI                        ;开中断
        PUSHA                      ;1将5.指向CS
        PUSH  DS
        PUSH  ES
        MOV   AX, CS
        MOV   DS, AX
        MOV   ES, AX

        CALL  GET_TIME             ;获取当时间，并转换成ASCIHI码

        MOV   BH, 0                ;获取0号显示页面当前的光标位置
        MOV   AH, 3
        INT    10H                 ;读取光标位置 (DH,DL)=(行，列)
        MOV   CURSOR,  DX          ;保存当前光标的位置
                                   ;在指定位置显示时间后，再将光标复原
        MOV   DH, 0                ;显示在0行
        MOV   DL, 80 - BUF_LEN     ;显示在最后几列(光标位置设到右上角)
        MOV   BP,  OFFSET  HOUR    ;ES,[BP]指向显示信息的起始地址
        MOV   BH, 0                ;显示到0号页面
        MOV   BL, 07H              ;显示字符的属性(白色)
        MOV   CX, BUF_LEN          ;显示的字符串长度
        MOV   AL, 0                ;BL包含显示属性,写后光标不动
        MOV   AH, 13H              ;调用显示字符串的功能
        INT    10H                 ;显示时间字符串
        MOV   DX, CURSOR           ;恢复原来的光标位置
        MOV   AH, 2                ;设置光标位置的功能号
        INT   10H                  ;设置光标位置，也即恢复到显示时间串前的位置
         
        POP   ES
        POP   DS
        POPA                       ;恢复现场
        IRET                       ;中断返回
NEW08H  ENDP

; -------------------------------GET_TIME ------------------------------------------------
; 取时间
; 参考资料，CMOS数据的读写
GET_TIME  PROC
        MOV   AL, 4                ;4是"时"信息的偏移地址
        OUT   70H, AL              ;设定将要访同的单元是偏移值为4的“时”信息
        JMP   $+2                  ;延时,保证端口操作的可靠性
        IN    AL,71H               ;读取“时”信息
        MOV   AH,AL                ;将2位压缩的BCD码转换成未压缩的BCD码
        AND   AL,0FH
        SHR   AH, 4
        ADD   AX, 3030H            ;转换成对应的ASCII码
        XCHG  AH,  AL              ;高位放在前面显示
        MOV   WORD PTR HOUR, AX    ;保存到HOUR指示的前2个字节中
        MOV   AL, 2                ;2是“分”信息的偏移地址
        OUT   70H, AL
        JMP   $+2
        IN    AL, 71H              ;读取“分“信息
        MOV   AH, AL               ;转换成对应的ASI码
        AND   AL, 0FH
        SHR   AH, 4
        ADD   AX, 3030H
        XCHG  AH, AL
        MOV   WORD PTR MIN, AX     ;保存到MIN党量指示的第工个字中
        MOV   AL, 0                ;0是“秒“信息的偏移地址
        OUT   70H, AL
        JMP   $+2
        IN    AL,71H               ;读取“秒”信息
        MOV   AH,AL                ;转换成对应的ASCII码
        AND   AL,0FH
        SHR   AH,4
        ADD   AX,3030H
        XCHG  AH,AL
        MOV   WORD PTR SEC,AX     ;保存到SEC变量指示的2个字节中
        RET
GET_TIME ENDP

; _____________DELAY __________________
; 延时程序段
DELAY   PROC
        PUSH  ECX
        MOV   ECX,0
L1:     INC   ECX
        CMP   ECX, 020000H
        JB    L1
        POP   ECX
        RET
DELAY   ENDP


; __________________________________________________________
; 获取及设置8号中断的处理程序入口地址

GET_SET_INTR8_ADDRESS  PROC
         ; 获取原 8 号中断的中断处理程序的入口地址
        MOV   AX, 3508H
        INT   21H
        MOV   OLD_INT,  BX
        MOV   OLD_INT+2, ES

           ; 设置新的 8号中断的中断处理程序的入口地址
        MOV   DX, OFFSET NEW08H
        MOV   AX, 2508H
        INT   21H
        RET
GET_SET_INTR8_ADDRESS  ENDP



RESTORE_INTR8_RETURN    PROC
;        原来的程序是将中断处理程序的入口地址复原
         LDS   DX, DWORD PTR OLD_INT
         MOV   AX, 2508H
         INT   21H
         MOV   AH, 4CH
         INT   21H

RESTORE_INTR8_RETURN  ENDP 


RESIDULE_INTR8      PROC
    ;       将新的中断处理程序驻留内存
        MOV   DX, OFFSET DELAY+15
        MOV   CL, 4
        SHR   DX, CL
        ADD   DX, 10H
        ADD   DX, 70H
        MOV   AL, 0
        MOV   AH, 31H
        INT   21H
RESIDULE_INTR8   ENDP


; -------------------------------------------------------------------------------------------------------
; 主程序开始
; 程序从此处开始执行

BEGIN:   
          ; 显示定义在代码段中的 MESSAGE串中的内容，
        PUSH  CS
        POP   DS

        LEA   DX, PROMPT    ;显示提示串 PROMPT
        MOV   AH, 9
        INT   21H  
        
        MOV   AH, 1         ;输入选择
        INT   21H           ;系统功能调用25H的人口/出口参数的规定

        MOV   SELECT_ITEM, AL

        LEA   DX, MESSAGE    ; 显示提示串 MESSAGE
        MOV   AH, 9
        INT   21H  
          
        CMP   SELECT_ITEM,  '1'
        JZ    DISP_CHARS
                                                               ; --------------------------------
        CALL  GET_SET_INTR8_ADDRESS      ;   设置新的中断向量
                                                               ; --------------------------------       

DISP_CHARS:
        MOV   DL,30H
LOOP_DISP:    
        MOV   AH, 2           ;   显示一个字符
        INT   21H
    
        CALL  DELAY           ;  希望该程序在运行过程中，能看到 8号中断产生后的运行效果
                                     ;   因而，缓慢（即代有延时功能）的显示一些字符。          

        MOV   AH, 0BH       ;   判断有无击键，无则继续。有按键中止         
        INT   21H
        CMP   AL, 0   
        JNZ   EXIT

        INC   DL                ;  准备下一个要显示的字符
        CMP   DL, 200
        JNZ   CONTINUE
        MOV   DL, 30H

CONTINUE:
        JMP   LOOP_DISP


EXIT:
        CMP   SELECT_ITEM, '1'
        JZ    EXIT1
        CMP   SELECT_ITEM, '3'
        JZ    EXIT3
      
        JMP   EXIT2

EXIT1: 
        MOV   AH,4CH
        INT   21H

EXIT2:
                         ;    原来的程序是将中断处理程序的入口地址复原
                         ;    并返回 DOS
        CALL  RESTORE_INTR8_RETURN       

EXIT3:
                         ;       将新的中断处理程序驻留内存, 并返回 DOS
        CALL  RESIDULE_INTR8 

CODE    ENDS
        END  BEGIN

 