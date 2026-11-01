; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7DF7C0-0x7DFFFB (eight routines).
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
; .686 for CMOVcc and .MMX for the MMX instructions (assembler mode only; no encoding changes).
.686
.MMX
OPTION LANGUAGE:C
ASSUME CS:FLAT, DS:FLAT, ES:FLAT, SS:FLAT
_TEXT SEGMENT BYTE PUBLIC FLAT 'CODE'

PUBLIC C FUN_007DF7C0
PUBLIC C FUN_007DF8C0
PUBLIC C FUN_007DF9C0
PUBLIC C FUN_007DFAE0
PUBLIC C FUN_007DFC00
PUBLIC C FUN_007DFD00
PUBLIC C FUN_007DFE00
PUBLIC C FUN_007DFF00
EXTERN C DAT_00B45590:BYTE
EXTERN C DAT_00B2FF78:BYTE
EXTERN C DAT_00B45990:BYTE
EXTERN C DAT_00B41178:BYTE
EXTERN C DAT_00B2FF79:BYTE

; FUNCTION: GAMEMD 0x7DF7C0
; FUN_007DF7C0 -- Row draw driven by a record at arg1: first fills the 16-bit step table at DAT_00B45590 from the step fields (+0x2A, +0x2C) and
; count byte (+0x32), then walks the rows described by the record.
FUN_007DF7C0 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DF7EA:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DF7EA
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DF80C:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DF81B:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DF860
$L007DF82D:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DF81B
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DF80C
	ret
	db	8Dh,9Bh,0,0,0,0
$L007DF860:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DF879:
	xor	eax,eax
	cmp	ecx,0
	je	$L007DF8B0
	mov	al,BYTE PTR [edi]
	inc	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	mov	ch,BYTE PTR [edi]
	inc	edi
	test	ch,ch
	je	$L007DF8AD
$L007DF893:
	mov	eax,ebx
	dec	cl
	shr	eax,10h
	mov	dl,BYTE PTR [edi]
	mov	al,bh
	add	edi,2
	add	ebx,ebp
	dec	ch
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	jne	$L007DF893
$L007DF8AD:
	inc	edi
	jmp	$L007DF879
$L007DF8B0:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DF82D
	db	8Dh,0A4h,24h,0,0,0,0
	nop
FUN_007DF7C0 ENDP

; FUNCTION: GAMEMD 0x7DF8C0
; FUN_007DF8C0 -- Row draw driven by a record at arg1, variant 2 of the routine at 0x7DF7C0.
FUN_007DF8C0 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DF8EA:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DF8EA
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DF90C:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DF91B:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi+4]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DF960
$L007DF92E:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DF91B
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DF90C
	ret
	db	5,0,0,0,0	; add eax,0x0
$L007DF960:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DF979:
	cmp	ecx,0
	je	$L007DF9AF
	mov	ch,BYTE PTR [edi]
	dec	edi
	test	ch,ch
	je	$L007DF99E
$L007DF985:
	mov	eax,ebx
	dec	cl
	dec	edi
	shr	eax,10h
	mov	dl,BYTE PTR [edi]
	mov	al,bh
	dec	edi
	add	ebx,ebp
	dec	ch
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	jne	$L007DF985
$L007DF99E:
	dec	edi
	xor	eax,eax
	mov	al,BYTE PTR [edi]
	dec	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	jmp	$L007DF979
$L007DF9AF:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DF92E
	db	8Dh,0A4h,24h,0,0,0,0
	mov	edi,edi
FUN_007DF8C0 ENDP

; FUNCTION: GAMEMD 0x7DF9C0
; FUN_007DF9C0 -- Row draw driven by a record at arg1, variant 3 of the routine at 0x7DF7C0.
FUN_007DF9C0 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DF9EA:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DF9EA
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DFA0C:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DFA1B:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DFA60
$L007DFA2D:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DFA1B
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DFA0C
	ret
	db	8Dh,9Bh,0,0,0,0
$L007DFA60:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DFA79:
	xor	eax,eax
	cmp	ecx,0
	je	$L007DFAC1
	mov	al,BYTE PTR [edi]
	inc	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	mov	ch,BYTE PTR [edi]
	inc	edi
	test	ch,ch
	je	$L007DFABE
$L007DFA93:
	mov	eax,ebx
	dec	cl
	shr	eax,10h
	xor	edx,edx
	mov	dl,BYTE PTR [edi+1]
	mov	al,bh
	mov	dh,BYTE PTR [edx+DAT_00B45990]
	mov	dl,BYTE PTR [edi]
	add	ebx,ebp
	add	edi,2
	dec	ch
	mov	dl,BYTE PTR [edx+DAT_00B41178]
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	jne	$L007DFA93
$L007DFABE:
	inc	edi
	jmp	$L007DFA79
$L007DFAC1:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DFA2D
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	mov	edi,edi
FUN_007DF9C0 ENDP

; FUNCTION: GAMEMD 0x7DFAE0
; FUN_007DFAE0 -- Row draw driven by a record at arg1, variant 4 of the routine at 0x7DF7C0.
FUN_007DFAE0 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DFB0A:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DFB0A
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DFB2C:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DFB3B:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi+4]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DFB80
$L007DFB4E:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DFB3B
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DFB2C
	ret
	db	5,0,0,0,0	; add eax,0x0
$L007DFB80:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DFB99:
	cmp	ecx,0
	je	$L007DFBE1
	mov	ch,BYTE PTR [edi]
	dec	edi
	test	ch,ch
	je	$L007DFBD0
$L007DFBA5:
	mov	eax,ebx
	dec	cl
	shr	eax,10h
	xor	edx,edx
	mov	dl,BYTE PTR [edi]
	mov	al,bh
	mov	dh,BYTE PTR [edx+DAT_00B45990]
	mov	dl,BYTE PTR [edi-1]
	add	ebx,ebp
	sub	edi,2
	dec	ch
	mov	dl,BYTE PTR [edx+DAT_00B41178]
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	jne	$L007DFBA5
$L007DFBD0:
	dec	edi
	xor	eax,eax
	mov	al,BYTE PTR [edi]
	dec	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	jmp	$L007DFB99
$L007DFBE1:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DFB4E
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	mov	edi,edi
FUN_007DFAE0 ENDP

; FUNCTION: GAMEMD 0x7DFC00
; FUN_007DFC00 -- Row draw driven by a record at arg1, variant 5 of the routine at 0x7DF7C0.
FUN_007DFC00 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	mov	ecx,0FFh
	sub	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DFC2D:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DFC2D
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DFC4F:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DFC5E:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DFCA0
$L007DFC70:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DFC5E
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DFC4F
	ret
	db	8Dh,49h,0
$L007DFCA0:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DFCB9:
	xor	eax,eax
	cmp	ecx,0
	je	$L007DFCEE
	mov	al,BYTE PTR [edi]
	inc	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	mov	ch,BYTE PTR [edi]
	inc	edi
	test	ch,ch
	je	$L007DFCEB
$L007DFCD3:
	mov	eax,ebx
	dec	cl
	shr	eax,10h
	mov	dl,BYTE PTR [edi]
	mov	al,bh
	inc	edi
	add	ebx,ebp
	dec	ch
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	jne	$L007DFCD3
$L007DFCEB:
	inc	edi
	jmp	$L007DFCB9
$L007DFCEE:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DFC70
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,49h,0
FUN_007DFC00 ENDP

; FUNCTION: GAMEMD 0x7DFD00
; FUN_007DFD00 -- Row draw driven by a record at arg1, variant 6 of the routine at 0x7DF7C0.
FUN_007DFD00 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	mov	ecx,0FFh
	sub	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DFD2D:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DFD2D
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DFD4F:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DFD5E:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi+4]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DFDA0
$L007DFD71:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DFD5E
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DFD4F
	ret
	mov	edi,edi
$L007DFDA0:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DFDB9:
	cmp	ecx,0
	je	$L007DFDEE
	mov	ch,BYTE PTR [edi]
	dec	edi
	test	ch,ch
	je	$L007DFDDD
$L007DFDC5:
	mov	eax,ebx
	dec	cl
	shr	eax,10h
	mov	dl,BYTE PTR [edi]
	mov	al,bh
	dec	edi
	add	ebx,ebp
	dec	ch
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	jne	$L007DFDC5
$L007DFDDD:
	dec	edi
	xor	eax,eax
	mov	al,BYTE PTR [edi]
	dec	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	jmp	$L007DFDB9
$L007DFDEE:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DFD71
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,49h,0
FUN_007DFD00 ENDP

; FUNCTION: GAMEMD 0x7DFE00
; FUN_007DFE00 -- Row draw driven by a record at arg1, variant 7 of the routine at 0x7DF7C0.
FUN_007DFE00 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	mov	ecx,0FFh
	sub	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DFE2D:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DFE2D
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DFE4F:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DFE5E:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DFEA0
$L007DFE70:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DFE5E
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DFE4F
	ret
	db	8Dh,49h,0
$L007DFEA0:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DFEB9:
	xor	eax,eax
	cmp	ecx,0
	je	$L007DFEF4
	mov	al,BYTE PTR [edi]
	inc	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	mov	ch,BYTE PTR [edi]
	inc	edi
	test	ch,ch
	je	$L007DFEF1
$L007DFED3:
	mov	eax,ebx
	dec	cl
	shr	eax,10h
	mov	dl,BYTE PTR [edi]
	mov	al,bh
	inc	edi
	add	ebx,ebp
	dec	ch
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	mov	BYTE PTR [eax+DAT_00B2FF79],dl
	jne	$L007DFED3
$L007DFEF1:
	inc	edi
	jmp	$L007DFEB9
$L007DFEF4:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DFE70
	db	8Dh,64h,24h,0
FUN_007DFE00 ENDP

; FUNCTION: GAMEMD 0x7DFF00
; FUN_007DFF00 -- Row draw driven by a record at arg1, variant 8 of the routine at 0x7DF7C0.
FUN_007DFF00 PROC C USES esi edi ebx ecx edx, arg1:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	mov	esi,arg1
	push	ebp
	movsx	ebp,WORD PTR [esi+2Ah]
	movsx	edx,WORD PTR [esi+2Ch]
	mov	ecx,0FFh
	sub	cl,BYTE PTR [esi+32h]
	mov	edi,OFFSET DAT_00B45590
	xor	eax,eax
	xor	ebx,ebx
	mov	esi,4
$L007DFF2D:
	mov	WORD PTR [edi],ax
	add	edi,2
	add	eax,ebp
	mov	WORD PTR [edi],bx
	add	edi,2
	add	ebx,edx
	dec	ecx
	jne	$L007DFF2D
	pop	ebp
	mov	esi,arg1
	xor	eax,eax
	mov	eax,DWORD PTR [esi+18h]
	mov	loc3,eax
	mov	ch,BYTE PTR [esi+31h]
$L007DFF4F:
	mov	eax,DWORD PTR [esi+0Ch]
	mov	loc1,eax
	mov	eax,loc3
	mov	loc2,eax
	mov	cl,BYTE PTR [esi+30h]
$L007DFF5E:
	mov	eax,loc3
	mov	DWORD PTR [esi+18h],eax
	xor	edi,edi
	mov	eax,DWORD PTR [esi+0Ch]
	mov	ebx,DWORD PTR [esi+4]
	or	edi,DWORD PTR [ebx+eax*4]
	jns	$L007DFFA0
$L007DFF71:
	mov	eax,DWORD PTR [esi+1Eh]
	add	loc3,eax
	mov	eax,DWORD PTR [esi+10h]
	add	DWORD PTR [esi+0Ch],eax
	dec	cl
	jne	$L007DFF5E
	mov	eax,loc2
	add	eax,DWORD PTR [esi+24h]
	mov	loc3,eax
	mov	eax,loc1
	add	eax,DWORD PTR [esi+14h]
	mov	DWORD PTR [esi+0Ch],eax
	dec	ch
	jne	$L007DFF4F
	ret
	mov	edi,edi
$L007DFFA0:
	push	esi
	push	ecx
	push	ebp
	xor	ecx,ecx
	add	edi,DWORD PTR [esi+8]
	mov	cl,BYTE PTR [esi+32h]
	mov	bx,WORD PTR [esi+1Ah]
	shl	ebx,10h
	mov	ebp,DWORD PTR [esi+2Ah]
	mov	bx,WORD PTR [esi+18h]
$L007DFFB9:
	cmp	ecx,0
	je	$L007DFFF4
	mov	ch,BYTE PTR [edi]
	dec	edi
	test	ch,ch
	je	$L007DFFE3
$L007DFFC5:
	mov	eax,ebx
	dec	cl
	shr	eax,10h
	mov	dl,BYTE PTR [edi]
	mov	al,bh
	dec	edi
	add	ebx,ebp
	dec	ch
	mov	BYTE PTR [eax+DAT_00B2FF78],dl
	mov	BYTE PTR [eax+DAT_00B2FF79],dl
	jne	$L007DFFC5
$L007DFFE3:
	dec	edi
	xor	eax,eax
	mov	al,BYTE PTR [edi]
	dec	edi
	sub	cl,al
	add	ebx,DWORD PTR [eax*4+DAT_00B45590]
	jmp	$L007DFFB9
$L007DFFF4:
	pop	ebp
	pop	ecx
	pop	esi
	jmp	$L007DFF71
FUN_007DFF00 ENDP

_TEXT ENDS
END
