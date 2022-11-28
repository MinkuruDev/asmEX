.data
	myByte		DB		20h
	fl			real4	420.69

.code
	testFunc PROC
		MOV EAX, fl
		RET
	testFunc ENDP

	; void addPack(float* rcx, float* rdx, float* r8)
	addPack PROC
		VMOVUPS ymm0, ymmword ptr [rdx]

		; VMOVUPS ymm1, ymmword ptr [r8]
		VBROADCASTSS ymm1, real4 ptr [r8]

		VADDPS ymm0, ymm0, ymm1

		VMOVUPS ymmword ptr [rcx], ymm0

		RET
	addPack ENDP

	; void mulInt(int* rcx, int* rdx, int* r8)
	mulInt PROC
		VMOVDQU ymm0, ymmword ptr [rdx]

		VBROADCASTSS ymm1, dword ptr [r8]

		VPMULLD ymm0, ymm0, ymm1

		VMOVDQU ymmword ptr [rcx], ymm0

		RET
	mulInt ENDP
END
