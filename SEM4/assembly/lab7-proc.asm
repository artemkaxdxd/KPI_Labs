include \masm32\include\masm32rt.inc
public part3, thirdRes
extern publicA:qword

.data
    const2 dq 2.0
    thirdRes dq 0.0, 0.0, 0.0
.code
part3 proc
   	finit
   	fld publicA
   	fld const2          
   	fdiv
   	fst thirdRes[16]   

   	fld1 
    fsub st, st(1)
    fst thirdRes[8]

	fstp thirdRes
	ret
part3 endp
end
