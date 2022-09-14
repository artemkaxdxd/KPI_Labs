.386
option casemap: none
include \masm32\include\masm32rt.inc

.data?
buff db 128 dup(?)
buffA db 32 dup(?)
buffB db 32 dup(?)
buffC db 32 dup(?)
buffD db 32 dup(?)
buffDneg db 32 dup(?)
buffE db 32 dup(?)
buffEneg db 32 dup(?)
buffF db 32 dup(?)
buffFneg db 32 dup(?)
buffSymb db 128 DUP (?)
.data
MsgBoxCaption db "1-03-IP-05-Bondarchuk",0

formS db "����� ddmmyyyy - '%s'", 0
formA db "+A= %d", 10, "-A= %d", 0
formB db "+B= %d", 10, "-B= %d", 0
formC db "+C= %d", 10, "-C= %d", 0
formD db "+D= %s", 0
formDneg db "-D= %s", 0
formE db "+E= %s", 0
formEneg db "-E= %s", 0
formF db "+F= %s", 0
formFneg db "-F= %s", 0
	
AposByte db 5
AnegByte db -5
AposWord dw 5
AnegWord dw -5
AposShortInt dd 5
AnegShortInt dd -5
AposLongInt dq 5
AnegLongInt dq -5
BposWord dw 507
BnegWord dw -507
BposShortInt dd 507
BnegShortInt dd -507
BposLongInt dq 507
BnegLongInt dq -507
CposShortInt dd 5072003
CnegShortInt dd -5072003
CposLongInt dq 5072003
CnegLongInt dq -5072003
	 	
symbol db "05072003", 0
Apos dd 5
Aneg dd -5
Bpos dd 507
Bneg dd -507
Cpos dd 5072003
Cneg dd -5072003
Dpos dq 0.009
DposBuff db "0.009", 0
Dneg dq -0.009
DnegBuff db "-0.009", 0
Epos dq 1.007
EposBuff db "1.007", 0
Eneg dq -1.007
EnegBuff db "-1.007", 0
Fpos dq 10083.504
FposBuff db "10083.504", 0
Fneg dq -10083.504 
FnegBuff db "-10083.504", 0  

format DB "%s", 13, "%s", 13, 
		  "%s", 13, "%s", 13,
		  "%s", 13, "%s", 13,
		  "%s", 13, "%s", 13,
		  "%s", 13, "%s", 13, 0

.code
Main:
invoke FloatToStr2, Dpos, addr buffD
invoke FloatToStr2, Dneg, addr buffDneg
invoke FloatToStr2, Epos, addr buffE
invoke FloatToStr2, Eneg, addr buffEneg
invoke FloatToStr2, Fpos, addr buffF
invoke FloatToStr2, Fneg, addr buffFneg

invoke wsprintf, addr buffSymb, addr formS, addr symbol
invoke wsprintf, addr buffA, addr formA, Apos, Aneg 
invoke wsprintf, addr buffB, addr formB, Bpos, Bneg
invoke wsprintf, addr buffC, addr formC, Cpos, Cneg
invoke wsprintf, addr buffD, addr formD, addr DposBuff
invoke wsprintf, addr buffDneg, addr formDneg, addr DnegBuff
invoke wsprintf, addr buffE, addr formE, addr EposBuff
invoke wsprintf, addr buffEneg, addr formEneg, addr EnegBuff
invoke wsprintf, addr buffF, addr formF, addr FposBuff
invoke wsprintf, addr buffFneg, addr formFneg, addr FnegBuff

invoke wsprintf, addr buff, addr format,
        addr buffSymb, addr buffA, addr buffB, addr buffC,
        addr buffD, addr buffDneg,
        addr buffE, addr buffEneg,
        addr buffF, addr buffFneg

invoke MessageBox, 0, addr buff, addr MsgBoxCaption, 0
invoke ExitProcess, 0
end Main
