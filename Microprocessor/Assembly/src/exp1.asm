DATA SEGMENT
    COUNT EQU 10 ; 待排序数据长度
    BLOCK DW 42, -5, 2000, 0, -32768, 32767, 15, -200, 500, -1 ; 待排序数据
    CRLF  DB 13, 10, '$' ; 换行符
DATA ENDS

STACKS SEGMENT
    DB 200H DUP(?) ; 分配栈空间
STACKS ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACKS

; 主程序
MAIN PROC
    ; 令 DX 指向数据段、SS 指向堆栈段
	mov ax, DATA
	mov ds, ax
	mov ax, SEG STACKS
	mov ss, ax

    ; 初始化栈指针
	mov sp, 200H

    ; 使用 CX 作为外层循环计数器，排序轮数为 COUNT - 1
	mov cx, COUNT - 1

OUTER_LOOP:
    ; 使用 SI 作为数组索引指针，BX 作为内层循环计数器
	lea si, BLOCK
	mov bx, cx

INNER_LOOP:
    ; 比较当前元素与下一个元素
	mov ax, [si]
	cmp ax, [si+2]

    ; 当前元素不小于下一个元素，无需交换
	jge NO_SWAP

    ; 交换当前元素与下一个元素
	xchg ax, [si+2]
	mov [si], ax

NO_SWAP:
    ; 前往下一个元素，并减少内层循环计数器
	add si, 2
	dec bx

    ; 如果内层循环计数器不为零，继续比较
	jnz INNER_LOOP
	loop OUTER_LOOP

    ; 恢复 SI 指向排序后的数组起始位置，并准备打印
	lea si, BLOCK
	mov cx, COUNT

PRINT_LOOP:
    ; 加载当前元素到 AX，并调用打印函数
	mov ax, [si]
	call PRINT_SIGNED_WORD

    ; 选择 9 号功能打印换行符
	mov ah, 09h
	lea dx, CRLF
	int 21h

    ; 前往下一个元素，循环执行
	add si, 2
	loop PRINT_LOOP

    ; 终止程序
	mov ah, 4Ch
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
