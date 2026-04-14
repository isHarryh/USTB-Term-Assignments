DATA SEGMENT
	COUNT EQU 20 ; 待统计数据长度
	BLOCK DB 12, -3, 45, -20, 0, 8, -1, 30, -15, 6, -7, 10, -12, 4, 18, -9, 2, -5, 25, -11 ; 20 个带符号单字节数据
	POS_SUM DW 0 ; 正数和
	NEG_SUM DW 0 ; 负数和
	CRLF  DB 13, 10, '$' ; 换行符
DATA ENDS

STACKS SEGMENT
	DB 200H DUP(?) ; 分配栈空间
STACKS ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACKS

; 主程序
MAIN PROC
	; 令 DS 指向数据段、SS 指向堆栈段
	mov ax, DATA
	mov ds, ax
	mov ax, SEG STACKS
	mov ss, ax

	; 初始化栈指针
	mov sp, 200H

	; 清零正数和与负数和
	mov word ptr POS_SUM, 0
	mov word ptr NEG_SUM, 0

	; 使用 SI 遍历 BLOCK，CX 作为循环计数器
	lea si, BLOCK
	mov cx, COUNT

SUM_LOOP:
	; 读取一个带符号字节到 AL，并扩展到 AX
	mov al, [si]
	cbw

	; 根据符号分别累加到正数和或负数和
	cmp al, 0
	jg ADD_POS
	jl ADD_NEG
	jmp NEXT_ITEM

ADD_POS:
	add POS_SUM, ax
	jmp NEXT_ITEM

ADD_NEG:
	add NEG_SUM, ax

NEXT_ITEM:
	inc si
	loop SUM_LOOP

	; 调用函数，打印正数和
	mov ax, POS_SUM
	call PRINT_SIGNED_WORD

	; 使用 9 号功能打印换行符
	mov ah, 09h
	lea dx, CRLF
	int 21h

	; 调用函数，打印负数和
	mov ax, NEG_SUM
	call PRINT_SIGNED_WORD

	; 使用 9 号功能打印换行符
	mov ah, 09h
	lea dx, CRLF
	int 21h

	; 终止程序
	mov ah, 4CH
	int 21h
MAIN ENDP

; 从 AX 打印一个带符号字
PRINT_SIGNED_WORD PROC
	push ax
	push bx
	push cx
	push dx

    ; 初始化位数计数器
	xor cx, cx

    ; 测试 AX 是否为负数
	test ax, ax
	jns DIVIDE_LOOP

    ; 使用 2 号功能打印负号
	push ax
	mov dl, '-'
	mov ah, 02h
	int 21h
	pop ax

; 提取各个数位的值到栈中，并统计位数到 CX 中
DIVIDE_LOOP:
    ; 将 AX 除以 10，商存在 AX 中，余数存在 DX 中
	mov bx, 10
	cwd
	idiv bx

    ; 如果余数为负数，取其绝对值
	test dx, dx
	jns PUSH_DIGIT
	neg dx

; 将余数压入栈中，并增加位数计数器
PUSH_DIGIT:
	push dx
	inc cx

    ; 如果商不为零，继续提取下一位
	test ax, ax
	jnz DIVIDE_LOOP

; 输出数字字符
OUTPUT_LOOP:
    ; 从栈顶弹出一个数字，并将其转换为 ASCII 字符
	pop dx
	add dl, '0'

    ; 使用 2 号功能打印一个数字字符
	mov ah, 02h
	int 21h
	loop OUTPUT_LOOP

PRINT_DONE:
	pop dx
	pop cx
	pop bx
	pop ax
	ret
PRINT_SIGNED_WORD ENDP

CODE ENDS
END MAIN
