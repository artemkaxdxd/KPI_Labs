include \masm32\include\masm32rt.inc
include \masm32\include\Fpu.inc
includelib \masm32\lib\Fpu.lib
expressionMacro MACRO a, b, c, d, res, zeroFl, rootFl
local errZero
local errRoot
local noErrs
finit   
	fld b ; st(0) = b
	fld constMul4    
	fmul    
	valueMacro res, printNum1	
	fld c  
	fadd   
	valueMacro res, printNum2
	fld d  
	fld constMul123  
	fmul  
	fcom constZero
	fstsw AX
	sahf
	jb errRoot 
	valueMacro res, printNum3	
	fsqrt  
	valueMacro res, printNum4
	fsub 
	valueMacro res, printNum5	
	fld a
	fld constDiv2  
	fdiv  
	valueMacro res, printNum6	
	fld constSub1 
	fsubr		
	valueMacro res, printNum7
   	fcom constZero
	fstsw AX
	sahf
	je errZero
    jmp noErrs
    errZero: 
    errZeroHandle zeroFl    
    errRoot:
	errRootHandle rootFl
    noErrs:
    fdiv   
    fstp res           
ENDM
valueMacro MACRO value, buffer
    fstp value
    invoke crt_sprintf, addr buffer, addr valForm, value
    fld value
ENDM
errZeroHandle MACRO zeroFl
    mov errF, 0    
ENDM
errRootHandle MACRO rootFl
    mov errRootF, 0    
ENDM
.data
numA dq 2.0, -20.547, 1.5, -63.43, 211.0453
numB dq 53.0, 60.44, 8.7, 36.78 , 74596745.5623444367
numC dq 22.12, 167.456, 0.0000002, 200.12, 34571457.00003
numD dq 5.34, -332.634, 0.74, 660.63, 0.93475768 
constMul4 dq 4.0
constMul123 dq 123.0
constDiv2 dq 2.0
constSub1 dq 1.0
constZero dq 0.0
MsgBoxCaption db "Bondarchuk Artem Lab 6", 0
expressionText db "Expression: (c+4*b-sqrt(123*d))/(1-a/2)", 0
resForm db 10, 10, "%d) a = %.2f, b = %.2f, c = %.2f, d = %.2f", 10,
    "4 * b = %s", 10, 
    "c + (4*b) = %s", 10,
    "(123*d) = %s", 10,                    
    "sqrt(123*d) = %s", 10,
    "(c + 4*b - sqrt(123*d)) = %s", 10,
    "a/2 = %s", 10, 
    "1 - a/2 = %s", 10, 
    "%s", 0
answForm db "Result = %.8f", 0
valForm db "%.8f", 0
errFormZero db 10, 10, "%d) a = %.2f, b = %.2f, c = %.2f, d = %.2f", 10, "Error! Division on Zero", 0
errFormRoot db 10, 10, "%d) a = %.2f, b = %.2f, c = %.2f, d = %.2f", 10, "Error! Negative number under square root", 0        
printNum1 dt 1024 dup(?)
printNum2 dt 1024 dup(?)
results db 4096 dup(?)
printNum3 dt 1024 dup(?)
result dq 16 dup(0)
printNum4 dt 1024 dup(?)
printNum5 dt 1024 dup(?)
answBuff dd 1024 dup(?)
printNum6 dt 1024 dup(?)
resBuff db 2048 dup(?)
printNum7 dt 1024 dup(?)
errF dd 1
errRootF dd 1 
.code
main: 
invoke wsprintf, addr results, addr expressionText
mov esi, 0   
.WHILE esi < 5
    mov errF, 1
    mov errRootF, 1
    expressionMacro numA[8 * esi], numB[8 * esi], numC[8 * esi], numD[8 * esi], result[8 * esi], errF, errRootF
    cmp errF, 0
    je errZero
	cmp errRootF, 0
    je errRoot
    jmp noErr
    noErr: 
    invoke crt_sprintf, addr answBuff, addr answForm, result[8 * esi]
    invoke crt_sprintf, addr resBuff, addr resForm, esi,
    numA[8 * esi], numB[8 * esi], numC[8 * esi], numD[8 * esi],
    addr printNum1, addr printNum2, addr printNum3, addr printNum4, 
    addr printNum5, addr printNum6, addr printNum7, 
    addr answBuff  
    jmp cont
    errZero: 
    invoke crt_sprintf, addr resBuff, addr errFormZero, esi, numA[8 * esi], numB[8 * esi], numC[8 * esi], numD[8 * esi]
    jmp cont
    errRoot: 
    invoke crt_sprintf, addr resBuff, addr errFormRoot, esi, numA[8 * esi], numB[8 * esi], numC[8 * esi], numD[8 * esi]
    jmp cont
    cont:
    invoke szCatStr, addr results, addr resBuff
    inc esi
.ENDW
invoke MessageBox, 0, addr results, addr MsgBoxCaption, 0
invoke ExitProcess, 0
end main
