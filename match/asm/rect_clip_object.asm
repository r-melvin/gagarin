; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C5DB0-0x7C5EDD (two routines).
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

PUBLIC C FUN_007C5DB0
PUBLIC C FUN_007C5E7E

; FUNCTION: GAMEMD 0x7C5DB0
; FUN_007C5DB0 -- Rectangle clip. arg1/arg2 are pointers to x,y, arg3/arg4 pointers to width,height, arg5/arg6 the clip extents. Computes
; outer-region outcodes with SHLD, trims the rectangle in place and returns -1 (rejected), 0 (already inside) or 1 (clipped).
FUN_007C5DB0 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	mov	esi,arg1
	mov	edi,arg2
	mov	eax,arg3
	mov	ebx,arg4
	mov	esi,DWORD PTR [esi]
	mov	edi,DWORD PTR [edi]
	mov	eax,DWORD PTR [eax]
	mov	ebx,DWORD PTR [ebx]
	add	eax,esi
	add	ebx,edi
	xor	ecx,ecx
	xor	edx,edx
	shld	ecx,esi,1
	shld	edx,eax,1
	sub	esi,arg5
	sub	eax,arg5
	dec	esi
	dec	eax
	shld	ecx,esi,1
	shld	edx,eax,1
	shld	ecx,edi,1
	shld	edx,ebx,1
	sub	edi,arg6
	sub	ebx,arg6
	dec	edi
	dec	ebx
	shld	ecx,edi,1
	shld	edx,ebx,1
	xor	cl,5
	xor	dl,5
	mov	eax,0FFFFFFFFh
	mov	bl,cl
	test	dl,cl
	jne	$L007C5E77
	xor	eax,eax
	or	bl,dl
	je	$L007C5E77
	mov	eax,0FFFFFFFFh
	test	cl,8
	je	$L007C5E35
	mov	edi,arg1
	mov	ebx,arg3
	mov	esi,DWORD PTR [edi]
	mov	DWORD PTR [edi],0
	add	DWORD PTR [ebx],esi
$L007C5E35:
	test	cl,2
	je	$L007C5E4A
	mov	edi,arg2
	mov	ebx,arg4
	mov	esi,DWORD PTR [edi]
	mov	DWORD PTR [edi],0
	add	DWORD PTR [ebx],esi
$L007C5E4A:
	test	dl,4
	je	$L007C5E5E
	mov	edi,arg3
	mov	esi,arg1
	mov	ebx,arg5
	sub	ebx,DWORD PTR [esi]
	mov	DWORD PTR [edi],ebx
	jle	$L007C5E77
$L007C5E5E:
	test	dl,1
	je	$L007C5E72
	mov	edi,arg4
	mov	esi,arg2
	mov	ebx,arg6
	sub	ebx,DWORD PTR [esi]
	mov	DWORD PTR [edi],ebx
	jle	$L007C5E77
$L007C5E72:
	mov	eax,1
$L007C5E77:
	ret
FUN_007C5DB0 ENDP

; FUNCTION: GAMEMD 0x7C5E7E
; FUN_007C5E7E -- Rectangle confine. Same argument layout as the clip routine above: trims x,y and width,height against the extents
; (arg5, arg6) and returns 0 when nothing changed, 1 when either axis was trimmed.
FUN_007C5E7E PROC C USES ebx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	xor	eax,eax
	mov	ebx,arg1
	mov	edi,arg3
	mov	esi,DWORD PTR [ebx]
	add	edi,DWORD PTR [ebx]
	sub	edi,arg5
	neg	esi
	dec	edi
	test	esi,edi
	jl	$L007C5EAE
	mov	eax,1
	test	esi,esi
	jl	$L007C5EAB
	mov	DWORD PTR [ebx],0
	jmp	$L007C5EAE
$L007C5EAB:
	inc	edi
	sub	DWORD PTR [ebx],edi
$L007C5EAE:
	mov	ebx,arg2
	mov	edi,arg4
	mov	esi,DWORD PTR [ebx]
	add	edi,DWORD PTR [ebx]
	sub	edi,arg6
	neg	esi
	dec	edi
	test	esi,edi
	jl	$L007C5ED9
	mov	eax,1
	test	esi,esi
	jl	$L007C5ED6
	mov	DWORD PTR [ebx],0
	ret
$L007C5ED6:
	inc	edi
	sub	DWORD PTR [ebx],edi
$L007C5ED9:
	ret
FUN_007C5E7E ENDP

_TEXT ENDS
END
