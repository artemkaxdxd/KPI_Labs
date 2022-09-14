.686
.model flat, stdcall
option casemap:none
include <\masm32\include\user32.inc>
includelib <\masm32\lib\user32.lib>
include <\masm32\include\masm32.inc>
includelib <\masm32\lib\masm32.lib>

.data
MsgBoxCaption db '���������, ��-05, ������ 3', 0
expressionCaption db '����� - (c/d + 3*a/2)/(c - a + 1)',13,13,0
firstRes dd 10 dup(?)
endRes dd 10 dup(?)	
buff db 128 dup(?)
outBuff db 512 dup(?)
divider dd 2
multiplier dd 3
whileLen dd 5
resultsForm db "��������: a = %d, c = %d, d = %d,",13,
	"��������� ������� = %d;",13,
	"��������� ���� ������/�������� = %d",13,13,0
ifErr0 db "��������: a = %d, c = %d, d = %d",13,
	"�������: ������ �� 0 ���������.",13,13,0
ifErrNotWhole db "��������: a = %d, c = %d, d = %d",13,
	"�������: ��������� ������ - �� ���� �����.",13,13,0
numA dd 22, 4, 40, -12, 5
numC dd 24, 2, 48, 5, 4
numD dd -8, 2, -8, 25, -9	
.code
start:
invoke wsprintf, addr outBuff, addr expressionCaption
mov edi, 0
.WHILE edi < whileLen
    mov eax, numA[4*edi]    
    mov ecx, numC[4*edi]    
	sub ecx, eax 
	inc ecx
	cmp ecx, 0
	je Err0  
	mov esi, ecx
	mov ebx, numD[4*edi]		
	mov eax, numC[4*edi]
	cmp ebx, 0  
    je Err0 
    cdq
    idiv ebx 
    mov edx, eax
    imul edx, ebx
    cmp edx, numC[4*edi]
    jne ErrNotWhole 
    mov ecx, eax	 	
	mov eax, numA[4*edi]
	imul eax, multiplier
	mov ebx, eax
	cdq
	idiv divider 
	mov edx, eax
	imul edx, divider
    cmp edx, ebx
    jne ErrNotWhole 			
	add eax, ecx 
	mov ebx, eax 		
    cdq 
    idiv esi
    mov edx, eax
    imul edx, esi
    cmp edx, ebx
    jne ErrNotWhole     
    mov firstRes[4*edi], eax   
    test eax, 1 
    jnz ifNotEven                   
    cdq
    idiv divider 
    jmp outif
    ifNotEven:
    imul eax, 5   
	outif:
    mov endRes[4*edi], eax	 
    invoke wsprintf, addr buff, addr resultsForm, 
	numA[4*edi], numC[4*edi], numD[4*edi], 
	firstRes[4*edi], endRes[4*edi]
    jmp cont
    Err0:
    invoke wsprintf, addr buff, addr ifErr0, 
	numA[4*edi], numC[4*edi], numD[4*edi]
    jmp cont
    ErrNotWhole:
    invoke wsprintf, addr buff, addr ifErrNotWhole, 
	numA[4*edi], numC[4*edi], numD[4*edi]
    jmp cont
    cont:
    invoke szCatStr, addr outBuff, addr buff
    inc edi	
.ENDW
invoke MessageBox, 0, addr outBuff, addr MsgBoxCaption, 0
end start
