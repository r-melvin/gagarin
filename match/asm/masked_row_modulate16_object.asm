; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7DF280-0x7DF780 (four routines).
;   Evidence the code was not compiled C: the routines open with the PROC C frame shape (push ebp / mov ebp,esp,
;   add esp,-N for LOCALs, USES pushes after the locals, pop-leave-ret epilogue) that VC6 never emits, they are byte-packed
;   inside the object with no alignment between them, and the object is surrounded by 0xCC padding.
;   Every instruction, displacement, constant and data address below was read off the user's retail gamemd.exe
;   v1.001 at the address in each annotation; the descriptions come from reading the code. All names are
;   placeholders: the binary attests none. Operand order follows MASM (test/xchg put the first operand in the
;   reg field); alignment filler inside the object (LEA reg,[reg+0] forms, NOPs) and the few non-minimal
;   immediate encodings are written as DB so the bytes stay exact. Data the code reads (DAT_ tables) lives
;   in the retail data sections and is only referenced here.
;   Assembler-encoding workaround: the register-to-register `movq mm,mm` lines are written as DB.
;   Retail has the 0F 7F (store) form, which ml 6.15 emits for the mnemonic, but JWasm (the CI
;   assembler) emits the 0F 6F (load) form, and MASM syntax cannot select between them. With DB both
;   assemblers produce the retail bytes. The mnemonic is kept in the comment on each line.

; Not `.MODEL FLAT` + `.CODE`: that segment is 16-byte aligned, and this object is byte-packed
; against its neighbours, so the segment is declared BYTE.
; .686 for CMOVcc and .MMX for the MMX instructions (assembler mode only; no encoding changes).
.686
.MMX
OPTION LANGUAGE:C
ASSUME CS:FLAT, DS:FLAT, ES:FLAT, SS:FLAT
_TEXT SEGMENT BYTE PUBLIC FLAT 'CODE'

PUBLIC C FUN_007DF280
PUBLIC C FUN_007DF3C2
PUBLIC C FUN_007DF500
PUBLIC C FUN_007DF640

; FUNCTION: GAMEMD 0x7DF280
; FUN_007DF280 -- Masked row modulate of 16-bit destination pixels with MMX (PUNPCKLBW/PMULLW/PADDUSB): a source mask byte of 0 skips the pixel;
; the pixel is looked up through the table in arg7, scaled and added back with unsigned saturation, EMMS on exit.
FUN_007DF280 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD, loc7:DWORD, loc8:DWORD, loc9:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc7,0
	mov	loc6,0
	mov	loc9,0
	mov	loc8,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
	mov	edx,arg7
$L007DF2C1:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
	jmp	$L007DF340
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	mov	edi,edi
$L007DF300:
	inc	esi
	lea	edi,[edi+2]
	dec	loc1
	jne	$L007DF340
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF2C1
	jmp	$L007DF3B9
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,9Bh,0,0,0,0
$L007DF340:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DF300
	mov	BYTE PTR [ebp-1Ch],al
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-1Ah],al
	mov	BYTE PTR [ebp-18h],al
	punpcklbw	mm0,[edx+ebx*4]
	psrlw	mm0,8
	db	0Fh,7Fh,0C1h	; movq mm1,mm0
	pmullw	mm0,QWORD PTR [ebp-1Ch]
	psrlw	mm0,8
	paddusb	mm0,mm1
	psrlw	mm0,2
	movq	QWORD PTR [ebp-24h],mm0
	xor	ebx,ebx
	xor	eax,eax
	mov	bl,BYTE PTR [ebp-24h]
	mov	al,BYTE PTR [ebp-22h]
	shr	bl,1
	xor	ecx,ecx
	shl	eax,5
	mov	cl,BYTE PTR [ebp-20h]
	shl	ecx,0Ah
	or	ebx,eax
	and	ecx,0F800h
	inc	esi
	or	ebx,ecx
	lea	edi,[edi+2]
	mov	WORD PTR [edi-2],bx
	dec	loc1
	jne	$L007DF340
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF2C1
$L007DF3B9:
	emms
	ret
FUN_007DF280 ENDP

; FUNCTION: GAMEMD 0x7DF3C2
; FUN_007DF3C2 -- Masked row modulate, variant 2 of the routine at 0x7DF280.
FUN_007DF3C2 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD, loc7:DWORD, loc8:DWORD, loc9:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc7,0
	mov	loc6,0
	mov	loc9,0
	mov	loc8,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
	mov	edx,arg7
$L007DF403:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
	jmp	$L007DF480
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
$L007DF440:
	inc	esi
	lea	edi,[edi+2]
	dec	loc1
	jne	$L007DF480
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF403
	jmp	$L007DF4F7
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,9Bh,0,0,0,0
$L007DF480:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DF440
	mov	BYTE PTR [ebp-1Ch],al
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-1Ah],al
	mov	BYTE PTR [ebp-18h],al
	punpcklbw	mm0,[edx+ebx*4]
	psrlw	mm0,8
	db	0Fh,7Fh,0C1h	; movq mm1,mm0
	pmullw	mm0,QWORD PTR [ebp-1Ch]
	psrlw	mm0,8
	paddusb	mm0,mm1
	psrlw	mm0,3
	movq	QWORD PTR [ebp-24h],mm0
	xor	ebx,ebx
	xor	eax,eax
	mov	bl,BYTE PTR [ebp-24h]
	mov	al,BYTE PTR [ebp-22h]
	xor	ecx,ecx
	shl	eax,5
	mov	cl,BYTE PTR [ebp-20h]
	shl	ecx,0Ah
	or	ebx,eax
	and	ecx,7C00h
	inc	esi
	or	ebx,ecx
	lea	edi,[edi+2]
	mov	WORD PTR [edi-2],bx
	dec	loc1
	jne	$L007DF480
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF403
$L007DF4F7:
	emms
	ret
FUN_007DF3C2 ENDP

; FUNCTION: GAMEMD 0x7DF500
; FUN_007DF500 -- Masked row modulate, variant 3 of the routine at 0x7DF280.
FUN_007DF500 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD, loc7:DWORD, loc8:DWORD, loc9:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc7,0
	mov	loc6,0
	mov	loc9,0
	mov	loc8,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
	mov	edx,arg7
$L007DF541:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
	jmp	$L007DF5C0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	mov	edi,edi
$L007DF580:
	inc	esi
	lea	edi,[edi+2]
	dec	loc1
	jne	$L007DF5C0
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF541
	jmp	$L007DF637
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,9Bh,0,0,0,0
$L007DF5C0:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DF580
	mov	BYTE PTR [ebp-1Ch],al
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-1Ah],al
	mov	BYTE PTR [ebp-18h],al
	punpcklbw	mm0,[edx+ebx*4]
	psrlw	mm0,8
	db	0Fh,7Fh,0C1h	; movq mm1,mm0
	pmullw	mm0,QWORD PTR [ebp-1Ch]
	psrlw	mm0,8
	paddusb	mm0,mm1
	psrlw	mm0,2
	movq	QWORD PTR [ebp-24h],mm0
	xor	ebx,ebx
	xor	eax,eax
	mov	bl,BYTE PTR [ebp-24h]
	mov	al,BYTE PTR [ebp-22h]
	xor	ecx,ecx
	shl	eax,6
	mov	cl,BYTE PTR [ebp-20h]
	shl	ecx,0Ah
	or	ebx,eax
	and	ecx,0F800h
	inc	esi
	or	ebx,ecx
	lea	edi,[edi+2]
	mov	WORD PTR [edi-2],bx
	dec	loc1
	jne	$L007DF5C0
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF541
$L007DF637:
	emms
	ret
FUN_007DF500 ENDP

; FUNCTION: GAMEMD 0x7DF640
; FUN_007DF640 -- Masked row modulate, variant 4 of the routine at 0x7DF280.
FUN_007DF640 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD, loc7:DWORD, loc8:DWORD, loc9:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc7,0
	mov	loc6,0
	mov	loc9,0
	mov	loc8,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
	mov	edx,arg7
$L007DF681:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
	jmp	$L007DF700
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	mov	edi,edi
$L007DF6C0:
	inc	esi
	lea	edi,[edi+2]
	dec	loc1
	jne	$L007DF700
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF681
	jmp	$L007DF778
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,9Bh,0,0,0,0
$L007DF700:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DF6C0
	mov	BYTE PTR [ebp-1Ch],al
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-1Ah],al
	mov	BYTE PTR [ebp-18h],al
	punpcklbw	mm0,[edx+ebx*4]
	psrlw	mm0,8
	db	0Fh,7Fh,0C1h	; movq mm1,mm0
	pmullw	mm0,QWORD PTR [ebp-1Ch]
	psrlw	mm0,8
	paddusb	mm0,mm1
	psrlw	mm0,2
	movq	QWORD PTR [ebp-24h],mm0
	xor	ebx,ebx
	xor	eax,eax
	mov	bl,BYTE PTR [ebp-24h]
	mov	al,BYTE PTR [ebp-22h]
	shr	bl,1
	xor	ecx,ecx
	shl	eax,4
	mov	cl,BYTE PTR [ebp-20h]
	shl	ecx,0Ah
	and	eax,423A0A60h
	or	ebx,eax
	inc	esi
	or	ebx,ecx
	lea	edi,[edi+2]
	mov	WORD PTR [edi-2],bx
	dec	loc1
	jne	$L007DF700
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF681
$L007DF778:
	emms
	ret
FUN_007DF640 ENDP

_TEXT ENDS
END
