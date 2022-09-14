include \masm32\include\masm32rt.inc
include \masm32\include\Fpu.inc
includelib \masm32\lib\Fpu.lib
extern part3:PROTO
extern thirdRes: qword
public publicA

.data?
    buff1 db 128 DUP (?)
    buff2 db 128 DUP (?)
    buff3 db 128 DUP (?)
    buff4 db 128 DUP (?)
    buff5 db 128 DUP (?)
    buff6 db 128 DUP (?)
    buff7 db 128 DUP (?)
    resBuff db 4096 DUP (?)
    buffOut1 db 1024 DUP (?)
    buffOut2 db 1024 DUP (?)
    buffOut3 db 1024 DUP (?)
    buffOut4 db 1024 DUP (?)
    buffOut5 db 1024 DUP (?)
    buffSize = $ - buffOut5

.data
    MsgBoxCaption db "Bondarchuk Artem Lab 7", 0
    resForm db "Expression: (c+4*b-sqrt(123*d))/(1-a/2)", 10, 
    "1. %s", 10,
    "2. %s", 10,
    "3. %s", 10,
    "4. %s", 10,
    "5. %s", 0
    errFormZero db "a = %.10f, b = %.10f, c = %.10f, d = %.10f", 10, "Error! Division on Zero", 10, 0
    errFormRoot db "a = %.10f, b = %.10f, c = %.10f, d = %.10f", 10, "Error! Negative number under square root", 10, 0
    answForm db "a = %.10f, b = %.10f, c = %.10f, d = %.10f", 10,
    "c-sqrt(123*d) = %s",10,
	"4*b = %s",10,
    "c+4*b-sqrt(123*d) = %s",10,
	"a/2 = %s",10,
    "1-a/2 = %s",10,
    "Result = %s",10, 0
    curBuff dd 0
    res dq 6 DUP (0)
    a dq 2.0, -20.547, 1.5, -63.43, 211.0453
	b dq 53.0, 60.44, 8.7, 36.78 , 74596745.5623444367
	cc dq 22.12, 167.456, 0.0000002, 200.12, 34571457.00003
	d dq 5.34, -332.634, 0.74, 660.63, 0.93475768
    publicA dq 0.0
    firstRes dq 0.0
    secondRes dq 0.0
    errZero dd 0
    errRoot dd 0
    valForm db "%.20f", 0
    const4 dq 4.0
    const123 dq 123.0
    const0 dq 0.0

expressionMacro MACRO a, b, cc, d, res
    mov errZero, 0
    mov errRoot, 0
    lea esi, d
    lea edx, cc
    lea eax, firstRes    
    call part1 
    valueMacro    buff1, firstRes
    push dword ptr b[4]
    push dword ptr b[0]  
    push offset secondRes
    call part2
    valueMacro    buff2, secondRes
    shift8 a, publicA
    call part3
    valueMacro buff4, thirdRes[16]
    valueMacro buff5, thirdRes[8]
    valueMacro buff6, thirdRes
    finit
    fld     firstRes
    fld     secondRes
    fadd    st, st(1)   
    fstp     firstRes
    valueMacro    buff3, firstRes
    fld     firstRes
    fcom const0
    fstsw ax
    sahf
    jle ifErrRoot
    fld     thirdRes
    fcom const0
    fstsw ax
    sahf
    jz ifErrZero
    fdivp   st(1), st
    fstp    res
    jmp ifNoErr
    ifErrZero:
    mov eax, 1
    mov errZero, eax
    ifErrRoot:
    mov eax, 1
    mov errRoot, eax       
    ifNoErr:
    valueMacro    buff7, res
ENDM

part1 proc 
    finit
	fld const123
	fld qword ptr [esi]
	fmul
	fsqrt
	fld qword ptr [edx]
	fsubr
	fstp qword ptr [eax] 
	ret
part1 endp

part2 proc
    push ebp
    mov ebp, esp
    push edx
    mov edx, [ebp+8]
    finit
    fld qword ptr [ebp+12]
    fld const4
    fmul        
    fstp qword ptr [edx]
    pop edx
    pop ebp
    ret 12
part2 endp

valueMacro MACRO buffer, num
    invoke crt_sprintf, addr buffer, addr valForm, num
ENDM

shift8 MACRO input, output
    local cycle
    mov ax, 0
    cycle:
    mov esi, dword ptr input[0]
    mov dword ptr output[0], esi
    inc ax
    cmp ax, 2
    mov esi, dword ptr input[4]
    mov dword ptr output[4], esi
    cmp ax, 2
ENDM

calcExpression MACRO i, buff, errorZero, errorRoot
    local errZero
    local errRoot
    local noErr
    expressionMacro a[i*8], b[i*8], cc[i*8], d[i*8], res[i*8]
    cmp errorZero, 1
    je errZero
	cmp errorRoot, 1
    je errRoot
    jmp noErr
    noErr:
    invoke crt_sprintf, buff, addr answForm, a[i*8], b[i*8], cc[i*8], d[i*8],
    addr buff1, addr buff2, addr buff3, addr buff4, addr buff5, addr buff7
    jmp endMacro
    errRoot:
    invoke crt_sprintf, buff, addr errFormRoot, a[i*8], b[i*8], cc[i*8], d[i*8]
    jmp endMacro
    errZero:
    invoke crt_sprintf, buff, addr errFormZero, a[i*8], b[i*8], cc[i*8], d[i*8]
    jmp endMacro
    endMacro:
ENDM

.code
main:
    mov edi, 0
    mov curBuff, offset buffOut1
    mainCycle:
    calcExpression edi, curBuff, errZero, errRoot
    add curBuff, buffSize
    inc edi
    cmp edi, 5
    jb mainCycle
    invoke crt_sprintf, addr resBuff, addr resForm, addr buffOut1, 
    addr buffOut2, addr buffOut3, addr buffOut4, addr buffOut5
    invoke MessageBox, 0, addr resBuff, addr MsgBoxCaption, MB_OK
    invoke ExitProcess, 0
END main
