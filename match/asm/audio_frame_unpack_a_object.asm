; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C5BC0-0x7C5DA5 (one routine plus its 22-byte delta table).
;   Evidence the code was not compiled C: the routines open with the PROC C frame shape (push ebp / mov ebp,esp,
;   add esp,-N for LOCALs, USES pushes after the locals, pop-leave-ret epilogue) that VC6 never emits, they are byte-packed
;   inside the object with no alignment between them, and the object is surrounded by 0xCC padding.
;   Every instruction, displacement, constant and data address below was read off the user's retail gamemd.exe
;   v1.001 at the address in each annotation; the descriptions come from reading the code. All names are
;   placeholders: the binary attests none. Operand order follows MASM (test/xchg put the first operand in the
;   reg field); alignment filler inside the object (LEA reg,[reg+0] forms, NOPs) and the few non-minimal
;   immediate encodings are written as DB so the bytes stay exact. Data the code reads (DAT_ tables) lives
;   in the retail data sections and is only referenced here.

; Not `.MODEL FLAT` + `.CODE`: that segment is 16-byte aligned, and this object is byte-packed
; against its neighbours, so the segment is declared BYTE.
.586
OPTION LANGUAGE:C
ASSUME CS:FLAT, DS:FLAT, ES:FLAT, SS:FLAT
_TEXT SEGMENT BYTE PUBLIC FLAT 'CODE'

PUBLIC C FUN_007C5BC0

; FUNCTION: GAMEMD 0x7C5BC0
; FUN_007C5BC0 -- Delta-coded 8-bit audio frame unpacker. arg1 source stream, arg2 destination, arg3 output byte count; returns the number of
; source bytes consumed. The top two bits of each command byte select nibble-delta pairs (the table at the end of this object),
; a single signed delta, a block copy or a fill.
FUN_007C5BC0 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD
	pushfd
	cld
	mov	loc2,0
	cmp	arg1,0
	je	$L007C5D87
	cmp	arg2,0
	je	$L007C5D87
	cmp	arg3,0
	je	$L007C5D87
	mov	esi,arg1
	mov	edi,arg2
	mov	ecx,arg3
	mov	dl,80h
$L007C5BFD:
	cmp	ecx,0
	jle	$L007C5D87
	xor	eax,eax
	mov	al,BYTE PTR [esi]
	inc	loc2
	inc	esi
	shl	eax,2
	shr	al,2
	cmp	ah,2
	jne	$L007C5C49
	test	al,20h
	je	$L007C5C2B
	shl	al,3
	sar	al,3
	add	dl,al
	mov	BYTE PTR [edi],dl
	dec	ecx
	inc	edi
	jmp	$L007C5BFD
$L007C5C2B:
	mov	ebx,ecx
	xor	ah,ah
	inc	al
	mov	ecx,eax
	shr	ecx,1
	rep movsw
	adc	ecx,ecx
	rep movsb
	mov	ecx,ebx
	add	loc2,eax
	sub	ecx,eax
	dec	edi
	mov	dl,BYTE PTR [edi]
	inc	edi
	jmp	$L007C5BFD
$L007C5C49:
	inc	al
	cmp	ah,1
	jne	$L007C5CAE
$L007C5C50:
	mov	ah,BYTE PTR [esi]
	mov	bl,ah
	inc	loc2
	inc	esi
	and	ebx,0Fh
	add	dl,BYTE PTR [ebx+$L007C5D96]
	pushfd
	cmp	BYTE PTR [ebx+$L007C5D96],0
	jl	$L007C5C72
	popfd
	jae	$L007C5C77
	mov	dl,0FFh
	jmp	$L007C5C77
$L007C5C72:
	popfd
	jb	$L007C5C77
	xor	dl,dl
$L007C5C77:
	mov	dh,dl
	mov	bl,ah
	shr	bl,4
	add	dh,BYTE PTR [ebx+$L007C5D96]
	pushfd
	cmp	BYTE PTR [ebx+$L007C5D96],0
	jl	$L007C5C95
	popfd
	jae	$L007C5C9A
	mov	dh,0FFh
	jmp	$L007C5C9A
$L007C5C95:
	popfd
	jb	$L007C5C9A
	xor	dh,dh
$L007C5C9A:
	mov	WORD PTR [edi],dx
	sub	ecx,2
	add	edi,2
	mov	dl,dh
	dec	al
	jne	$L007C5C50
	jmp	$L007C5BFD
$L007C5CAE:
	cmp	ah,0
	jne	$L007C5D74
$L007C5CB7:
	mov	ah,BYTE PTR [esi]
	inc	loc2
	inc	esi
	mov	bl,ah
	and	ebx,3
	add	dl,BYTE PTR [ebx+$L007C5D92]
	pushfd
	cmp	BYTE PTR [ebx+$L007C5D92],0
	jl	$L007C5CD9
	popfd
	jae	$L007C5CDE
	mov	dl,0FFh
	jmp	$L007C5CDE
$L007C5CD9:
	popfd
	jb	$L007C5CDE
	xor	dl,dl
$L007C5CDE:
	mov	dh,dl
	ror	edx,8
	mov	bl,ah
	shr	ebx,2
	and	bl,3
	add	dl,BYTE PTR [ebx+$L007C5D92]
	pushfd
	cmp	BYTE PTR [ebx+$L007C5D92],0
	jl	$L007C5D02
	popfd
	jae	$L007C5D07
	mov	dl,0FFh
	jmp	$L007C5D07
$L007C5D02:
	popfd
	jb	$L007C5D07
	xor	dl,dl
$L007C5D07:
	mov	dh,dl
	ror	edx,8
	mov	bl,ah
	shr	ebx,4
	and	bl,3
	add	dl,BYTE PTR [ebx+$L007C5D92]
	pushfd
	cmp	BYTE PTR [ebx+$L007C5D92],0
	jl	$L007C5D2B
	popfd
	jae	$L007C5D30
	mov	dl,0FFh
	jmp	$L007C5D30
$L007C5D2B:
	popfd
	jb	$L007C5D30
	xor	dl,dl
$L007C5D30:
	mov	dh,dl
	ror	edx,8
	mov	bl,ah
	shr	ebx,6
	and	bl,3
	add	dl,BYTE PTR [ebx+$L007C5D92]
	pushfd
	cmp	BYTE PTR [ebx+$L007C5D92],0
	jl	$L007C5D54
	popfd
	jae	$L007C5D59
	mov	dl,0FFh
	jmp	$L007C5D59
$L007C5D54:
	popfd
	jb	$L007C5D59
	xor	dl,dl
$L007C5D59:
	ror	edx,8
	mov	DWORD PTR [edi],edx
	sub	ecx,4
	add	edi,4
	rol	edx,8
	dec	al
	jne	$L007C5CB7
	jmp	$L007C5BFD
$L007C5D74:
	xor	ebx,ebx
	mov	bl,al
	mov	al,dl
	sub	ecx,ebx
	xchg	ecx,ebx
	rep stosb
	mov	ecx,ebx
	jmp	$L007C5BFD
$L007C5D87:
	popfd
	mov	eax,loc2
	ret
; data 0x7c5d92-0x7c5da6
$L007C5D92:
	db	0FEh,0FFh,0,1
$L007C5D96:
	db	0F7h,0F8h,0FAh,0FBh,0FCh,0FDh,0FEh,0FFh,0,1,2,3,4,5,6,8
FUN_007C5BC0 ENDP

_TEXT ENDS
END
