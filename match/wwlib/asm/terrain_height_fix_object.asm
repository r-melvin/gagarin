; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C6620-0x7C6729 (one routine).
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

PUBLIC C FUN_007C6620
EXTERN C DAT_00B0B6EC:DWORD
EXTERN C DAT_008759A4:DWORD

; FUNCTION: GAMEMD 0x7C6620
; FUN_007C6620 -- Recursive neighbour fix-up on the grid of 8-byte cells at DAT_00B0B6EC (row stride DAT_008759A4). arg1,arg2 are the cell
; x,y; arg3 selects raise (1) or lower; arg4 is a check-only flag. Each of the eight neighbours whose height (dword at +0) is
; more than 12 away from this cell's is pulled to within 12, flagged (bit 1 of the dword at +4) and fixed up in turn; returns 0
; when a flagged neighbour (bit 0 of +4) is out of range or a nested fix-up fails.
FUN_007C6620 PROC C USES esi edi ebx ecx, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	eax,arg2
	mov	esi,DWORD PTR DAT_00B0B6EC
	imul	eax,DWORD PTR DAT_008759A4
	add	eax,arg1
	lea	esi,[esi+eax*8]
	mov	eax,DWORD PTR [esi]
	mov	loc1,eax
	mov	edi,0FFFFFFFFh
$L007C664A:
	mov	ecx,0FFFFFFFFh
$L007C664F:
	mov	eax,edi
	or	eax,ecx
	test	eax,eax
	je	$L007C670B
	mov	eax,arg1
	add	eax,ecx
	mov	loc2,eax
	mov	ebx,arg2
	add	ebx,edi
	mov	loc3,ebx
	imul	ebx,DWORD PTR DAT_008759A4
	mov	esi,DWORD PTR DAT_00B0B6EC
	add	ebx,eax
	lea	esi,[esi+ebx*8]
	test	DWORD PTR [esi+4],1
	je	$L007C66A3
	cmp	arg4,0
	jne	$L007C670B
	mov	eax,DWORD PTR [esi]
	sub	eax,loc1
	cdq
	xor	eax,edx
	sub	eax,edx
	cmp	eax,0Ch
	jbe	$L007C670B
	xor	eax,eax
	ret
$L007C66A3:
	mov	eax,DWORD PTR [esi]
	sub	eax,loc1
	cdq
	xor	eax,edx
	sub	eax,edx
	cmp	eax,0Ch
	jbe	$L007C670B
	cmp	arg3,1
	jne	$L007C66CD
	mov	eax,DWORD PTR [esi]
	cmp	eax,loc1
	jae	$L007C66E0
	mov	eax,loc1
	sub	eax,0Ch
	mov	DWORD PTR [esi],eax
	or	DWORD PTR [esi+4],2
	jmp	$L007C66E0
$L007C66CD:
	mov	eax,DWORD PTR [esi]
	cmp	eax,loc1
	jbe	$L007C66E0
	mov	eax,loc1
	add	eax,0Ch
	mov	DWORD PTR [esi],eax
	or	DWORD PTR [esi+4],2
$L007C66E0:
	push	ecx
	push	edi
	push	arg4
	push	arg3
	push	loc3
	push	loc2
	call	FUN_007C6620
	lea	esp,[esp+10h]
	pop	edi
	pop	ecx
	test	eax,eax
	jne	$L007C670B
	cmp	arg4,0
	jne	$L007C670B
	xor	eax,eax
	ret
$L007C670B:
	inc	ecx
	cmp	ecx,2
	jl	$L007C664F
	inc	edi
	cmp	edi,2
	jl	$L007C664A
	mov	eax,1
	ret
FUN_007C6620 ENDP

_TEXT ENDS
END
