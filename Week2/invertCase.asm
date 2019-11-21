    .cpu cortex-m0
    .align 1
    .global invertCase
    .text

invertCase:
   	MOV R2, #'A'
	SUB R1, R0, R2
	BGE upperZCheck
	b .return
upperZCheck:
	MOV R2, #'Z'
	SUB R1, R0, R2
	BGE lowerACheck
	SUB R0, #('A' - 'a')
	b .return
lowerACheck:
	MOV R2, #'a'
	SUB R1, R0, R2
	BGE lowerZCheck
	b .return
lowerZCheck:
	MOV R2, #'z'
	SUB R1, R0, R2
	BGE .return
	SUB R0, #('a' - 'A')
.return:
	MOV pc, lr