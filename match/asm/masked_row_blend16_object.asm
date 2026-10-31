; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7DE200-0x7DF26D (eight routines).
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

PUBLIC C FUN_007DE200
PUBLIC C FUN_007DE53A
PUBLIC C FUN_007DE87A
PUBLIC C FUN_007DEBBA
PUBLIC C FUN_007DEEFA
PUBLIC C FUN_007DEFD7
PUBLIC C FUN_007DF0B4
PUBLIC C FUN_007DF191
EXTERN C DAT_0084E862:BYTE
EXTERN C DAT_0084E860:BYTE

; FUNCTION: GAMEMD 0x7DE200
; FUN_007DE200 -- Masked row blit of 24-bit RGB source pixels (arg1) into 16-bit destination pixels (arg2). A per-pixel mask byte (arg7) of 0 skips
; the pixel; each channel is scaled by arg3..arg5 and saturated, then packed. Three paths: MMX when DAT_0084E862 is set, a CMOV
; saturating path when DAT_0084E860 is set, otherwise plain integer code. This variant packs 5-6-5.
FUN_007DE200 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD
	cmp	BYTE PTR DAT_0084E862,0
	jne	$L007DE267
	cmp	BYTE PTR DAT_0084E860,0
	jne	$L007DE23D
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	xor	ebx,ebx
	jmp	$L007DE440
$L007DE23D:
	pushfd
	cld
	mov	loc2,0FFh
	mov	esi,arg1
	mov	loc1,0FF0000h
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	add	edi,2
	jmp	$L007DE3C0
$L007DE267:
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	sub	edi,2
	movq	mm1,QWORD PTR [ebp+10h]
	movq	mm2,QWORD PTR [ebp+18h]
	psrad	mm1,4
	psrad	mm2,4
	packssdw	mm1,mm2
	pxor	mm0,mm0
	db	0Fh,7Fh,0CAh	; movq mm2,mm1
	punpckhwd	mm2,mm1
	punpckhwd	mm2,mm2
	jmp	$L007DE2C0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	5,0,0,0,0	; add eax,0x0
$L007DE2C0:
	add	edi,2
	packuswb	mm0,mm0
	cmp	BYTE PTR [edx],0
	je	$L007DE340
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0FC00h
	shr	ebx,5
	and	ecx,0F80000h
	shr	ecx,13h
	pmulhw	mm0,mm1
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DE2C0
$L007DE309:
	add	edi,2
	packuswb	mm0,mm0
	movd	eax,mm0
	mov	ebx,eax
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0FC00h
	shr	ebx,5
	and	ecx,0F80000h
	shr	ecx,13h
	or	eax,ebx
	or	eax,ecx
	mov	WORD PTR [edi],ax
	emms
	ret
$L007DE340:
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0FC00h
	shr	ebx,5
	and	ecx,0F80000h
	shr	ecx,13h
	pmulhw	mm0,mm2
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DE2C0
	jmp	$L007DE309
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007DE3C0:
	cmp	BYTE PTR [edx],0
	movzx	eax,BYTE PTR [esi]
	movzx	ebx,BYTE PTR [esi+1]
	movzx	ecx,BYTE PTR [esi+2]
	je	$L007DE42A
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
$L007DE3DC:
	add	esi,3
	test	eax,0FF000000h
	cmovne	eax,loc1
	test	ebx,0FF000000h
	cmovne	ebx,loc1
	test	ecx,0FF000000h
	cmovne	ecx,loc1
	and	eax,0F80000h
	shr	eax,8
	and	ebx,0FC0000h
	shr	ebx,0Dh
	and	ecx,0F80000h
	or	eax,ebx
	shr	ecx,13h
	inc	edx
	or	eax,ecx
	stosw
	dec	loc2
	jne	$L007DE3C0
	popfd
	ret
$L007DE42A:
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	jmp	$L007DE3DC
	db	8Dh,0A4h,24h,0,0,0,0
	nop
$L007DE440:
	xor	eax,eax
	mov	bl,BYTE PTR [esi+1]
	xor	ecx,ecx
	mov	al,BYTE PTR [esi]
	cmp	BYTE PTR [edx],0
	je	$L007DE4C2
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0F8h
	shl	eax,8
	and	ebx,0FCh
	shl	ebx,3
	and	ecx,0F8h
	shr	ecx,3
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DE440
	ret
$L007DE4C2:
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0F8h
	shl	eax,8
	and	ebx,0FCh
	shl	ebx,3
	and	ecx,0F8h
	shr	ecx,3
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DE440
	ret
FUN_007DE200 ENDP

; FUNCTION: GAMEMD 0x7DE53A
; FUN_007DE53A -- Same as the routine at 0x7DE200, packing variant 2 (different channel masks).
FUN_007DE53A PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD
	cmp	BYTE PTR DAT_0084E862,0
	jne	$L007DE5A1
	cmp	BYTE PTR DAT_0084E860,0
	jne	$L007DE577
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	xor	ebx,ebx
	jmp	$L007DE780
$L007DE577:
	pushfd
	cld
	mov	loc2,0FFh
	mov	esi,arg1
	mov	loc1,0FF0000h
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	add	edi,2
	jmp	$L007DE700
$L007DE5A1:
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	sub	edi,2
	movq	mm1,QWORD PTR [ebp+10h]
	movq	mm2,QWORD PTR [ebp+18h]
	psrad	mm1,4
	psrad	mm2,4
	packssdw	mm1,mm2
	pxor	mm0,mm0
	db	0Fh,7Fh,0CAh	; movq mm2,mm1
	punpckhwd	mm2,mm1
	punpckhwd	mm2,mm2
	jmp	$L007DE600
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007DE600:
	add	edi,2
	packuswb	mm0,mm0
	cmp	BYTE PTR [edx],0
	je	$L007DE680
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,7
	and	ebx,0F800h
	shr	ebx,6
	and	ecx,0F80000h
	shr	ecx,13h
	pmulhw	mm0,mm1
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DE600
$L007DE649:
	add	edi,2
	packuswb	mm0,mm0
	movd	eax,mm0
	mov	ebx,eax
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,7
	and	ebx,0F800h
	shr	ebx,6
	and	ecx,0F80000h
	shr	ecx,13h
	or	eax,ebx
	or	eax,ecx
	mov	WORD PTR [edi],ax
	emms
	ret
$L007DE680:
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,7
	and	ebx,0F800h
	shr	ebx,6
	and	ecx,0F80000h
	shr	ecx,13h
	pmulhw	mm0,mm2
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DE600
	jmp	$L007DE649
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007DE700:
	cmp	BYTE PTR [edx],0
	movzx	eax,BYTE PTR [esi]
	movzx	ebx,BYTE PTR [esi+1]
	movzx	ecx,BYTE PTR [esi+2]
	je	$L007DE76A
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
$L007DE71C:
	add	esi,3
	test	eax,0FF000000h
	cmovne	eax,loc1
	test	ebx,0FF000000h
	cmovne	ebx,loc1
	test	ecx,0FF000000h
	cmovne	ecx,loc1
	and	eax,0F80000h
	shr	eax,9
	and	ebx,0F80000h
	shr	ebx,0Eh
	and	ecx,0F80000h
	or	eax,ebx
	shr	ecx,13h
	inc	edx
	or	eax,ecx
	stosw
	dec	loc2
	jne	$L007DE700
	popfd
	ret
$L007DE76A:
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	jmp	$L007DE71C
	db	8Dh,0A4h,24h,0,0,0,0
	nop
$L007DE780:
	xor	eax,eax
	mov	bl,BYTE PTR [esi+1]
	xor	ecx,ecx
	mov	al,BYTE PTR [esi]
	cmp	BYTE PTR [edx],0
	je	$L007DE802
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0F8h
	shl	eax,7
	and	ebx,0F8h
	shl	ebx,2
	and	ecx,0F8h
	shr	ecx,3
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DE780
	ret
$L007DE802:
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0F8h
	shl	eax,7
	and	ebx,0F8h
	shl	ebx,2
	and	ecx,0F8h
	shr	ecx,3
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DE780
	ret
FUN_007DE53A ENDP

; FUNCTION: GAMEMD 0x7DE87A
; FUN_007DE87A -- Same as the routine at 0x7DE200, packing variant 3.
FUN_007DE87A PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD
	cmp	BYTE PTR DAT_0084E862,0
	jne	$L007DE8E1
	cmp	BYTE PTR DAT_0084E860,0
	jne	$L007DE8B7
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	xor	ebx,ebx
	jmp	$L007DEAC0
$L007DE8B7:
	pushfd
	cld
	mov	loc2,0FFh
	mov	esi,arg1
	mov	loc1,0FF0000h
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	add	edi,2
	jmp	$L007DEA40
$L007DE8E1:
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	sub	edi,2
	movq	mm1,QWORD PTR [ebp+10h]
	movq	mm2,QWORD PTR [ebp+18h]
	psrad	mm1,4
	psrad	mm2,4
	packssdw	mm1,mm2
	pxor	mm0,mm0
	db	0Fh,7Fh,0CAh	; movq mm2,mm1
	punpckhwd	mm2,mm1
	punpckhwd	mm2,mm2
	jmp	$L007DE940
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007DE940:
	add	edi,2
	packuswb	mm0,mm0
	cmp	BYTE PTR [edx],0
	je	$L007DE9C0
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0F800h
	shr	ebx,5
	and	ecx,0FC0000h
	shr	ecx,12h
	pmulhw	mm0,mm1
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DE940
$L007DE989:
	add	edi,2
	packuswb	mm0,mm0
	movd	eax,mm0
	mov	ebx,eax
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0F800h
	shr	ebx,5
	and	ecx,0FC0000h
	shr	ecx,12h
	or	eax,ebx
	or	eax,ecx
	mov	WORD PTR [edi],ax
	emms
	ret
$L007DE9C0:
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0F8h
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0F800h
	shr	ebx,5
	and	ecx,0FC0000h
	shr	ecx,12h
	pmulhw	mm0,mm2
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DE940
	jmp	$L007DE989
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007DEA40:
	cmp	BYTE PTR [edx],0
	movzx	eax,BYTE PTR [esi]
	movzx	ebx,BYTE PTR [esi+1]
	movzx	ecx,BYTE PTR [esi+2]
	je	$L007DEAAA
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
$L007DEA5C:
	add	esi,3
	test	eax,0FF000000h
	cmovne	eax,loc1
	test	ebx,0FF000000h
	cmovne	ebx,loc1
	test	ecx,0FF000000h
	cmovne	ecx,loc1
	and	eax,0F80000h
	shr	eax,8
	and	ebx,0F80000h
	shr	ebx,0Dh
	and	ecx,0FC0000h
	or	eax,ebx
	shr	ecx,12h
	inc	edx
	or	eax,ecx
	stosw
	dec	loc2
	jne	$L007DEA40
	popfd
	ret
$L007DEAAA:
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	jmp	$L007DEA5C
	db	8Dh,0A4h,24h,0,0,0,0
	nop
$L007DEAC0:
	xor	eax,eax
	mov	bl,BYTE PTR [esi+1]
	xor	ecx,ecx
	mov	al,BYTE PTR [esi]
	cmp	BYTE PTR [edx],0
	je	$L007DEB42
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0F8h
	shl	eax,8
	and	ebx,0F8h
	shl	ebx,3
	and	ecx,0FCh
	shr	ecx,2
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DEAC0
	ret
$L007DEB42:
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0F8h
	shl	eax,8
	and	ebx,0F8h
	shl	ebx,3
	and	ecx,0FCh
	shr	ecx,2
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DEAC0
	ret
FUN_007DE87A ENDP

; FUNCTION: GAMEMD 0x7DEBBA
; FUN_007DEBBA -- Same as the routine at 0x7DE200, packing variant 4.
FUN_007DEBBA PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD, arg7:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD
	cmp	BYTE PTR DAT_0084E862,0
	jne	$L007DEC21
	cmp	BYTE PTR DAT_0084E860,0
	jne	$L007DEBF7
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	xor	ebx,ebx
	jmp	$L007DEE00
$L007DEBF7:
	pushfd
	cld
	mov	loc2,0FFh
	mov	esi,arg1
	mov	loc1,0FF0000h
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	mov	WORD PTR [edi],0
	add	edi,2
	jmp	$L007DED80
$L007DEC21:
	mov	loc2,0FFh
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg7
	add	esi,3
	inc	edx
	sub	edi,2
	movq	mm1,QWORD PTR [ebp+10h]
	movq	mm2,QWORD PTR [ebp+18h]
	psrad	mm1,4
	psrad	mm2,4
	packssdw	mm1,mm2
	pxor	mm0,mm0
	db	0Fh,7Fh,0CAh	; movq mm2,mm1
	punpckhwd	mm2,mm1
	punpckhwd	mm2,mm2
	jmp	$L007DEC80
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007DEC80:
	add	edi,2
	packuswb	mm0,mm0
	cmp	BYTE PTR [edx],0
	je	$L007DED00
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0FCh
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0F800h
	shr	ebx,6
	and	ecx,0F80000h
	shr	ecx,13h
	pmulhw	mm0,mm1
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DEC80
$L007DECC9:
	add	edi,2
	packuswb	mm0,mm0
	movd	eax,mm0
	mov	ebx,eax
	and	eax,0FCh
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0F800h
	shr	ebx,6
	and	ecx,0F80000h
	shr	ecx,13h
	or	eax,ebx
	or	eax,ecx
	mov	WORD PTR [edi],ax
	emms
	ret
$L007DED00:
	movd	eax,mm0
	pxor	mm0,mm0
	punpcklbw	mm0,[esi]
	mov	ebx,eax
	psrlw	mm0,4
	and	eax,0FCh
	mov	ecx,ebx
	shl	eax,8
	and	ebx,0F800h
	shr	ebx,6
	and	ecx,0F80000h
	shr	ecx,13h
	pmulhw	mm0,mm2
	or	eax,ebx
	add	esi,3
	or	eax,ecx
	inc	edx
	mov	WORD PTR [edi],ax
	dec	loc2
	jne	$L007DEC80
	jmp	$L007DECC9
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007DED80:
	cmp	BYTE PTR [edx],0
	movzx	eax,BYTE PTR [esi]
	movzx	ebx,BYTE PTR [esi+1]
	movzx	ecx,BYTE PTR [esi+2]
	je	$L007DEDEA
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
$L007DED9C:
	add	esi,3
	test	eax,0FF000000h
	cmovne	eax,loc1
	test	ebx,0FF000000h
	cmovne	ebx,loc1
	test	ecx,0FF000000h
	cmovne	ecx,loc1
	and	eax,0FC0000h
	shr	eax,8
	and	ebx,0F80000h
	shr	ebx,0Eh
	and	ecx,0F80000h
	or	eax,ebx
	shr	ecx,13h
	inc	edx
	or	eax,ecx
	stosw
	dec	loc2
	jne	$L007DED80
	popfd
	ret
$L007DEDEA:
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	jmp	$L007DED9C
	db	8Dh,0A4h,24h,0,0,0,0
	nop
$L007DEE00:
	xor	eax,eax
	mov	bl,BYTE PTR [esi+1]
	xor	ecx,ecx
	mov	al,BYTE PTR [esi]
	cmp	BYTE PTR [edx],0
	je	$L007DEE82
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg3
	imul	ebx,arg4
	imul	ecx,arg5
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0FCh
	shl	eax,8
	and	ebx,0F8h
	shl	ebx,2
	and	ecx,0F8h
	shr	ecx,3
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DEE00
	ret
$L007DEE82:
	mov	cl,BYTE PTR [esi+2]
	inc	edx
	imul	eax,arg6
	imul	ebx,arg6
	imul	ecx,arg6
	shr	eax,10h
	add	esi,3
	shr	ebx,10h
	cmp	eax,0FFh
	setbe	ah
	shr	ecx,10h
	dec	ah
	or	al,ah
	cmp	ebx,0FFh
	setbe	bh
	dec	bh
	cmp	ecx,0FFh
	setbe	ch
	or	bl,bh
	dec	ch
	or	cl,ch
	and	eax,0FCh
	shl	eax,8
	and	ebx,0F8h
	shl	ebx,2
	and	ecx,0F8h
	shr	ecx,3
	or	eax,ebx
	add	edi,2
	xor	ebx,ebx
	or	eax,ecx
	dec	loc2
	mov	WORD PTR [edi],ax
	jne	$L007DEE00
	ret
FUN_007DEBBA ENDP

; FUNCTION: GAMEMD 0x7DEEFA
; FUN_007DEEFA -- Masked row blend into 16-bit destination pixels, scalar form: a mask byte of 0 skips the pixel, otherwise the destination 5-6-5
; channels are blended with a weight derived from the mask byte, with byte saturation (SETAE/DEC clamp).
FUN_007DEEFA PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc6,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
$L007DEF23:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
$L007DEF2D:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DEFA8
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-18h],al
	mov	loc5,ebx
	shr	ebx,8
	mov	eax,loc5
	shr	eax,3
	and	ebx,0F8h
	and	eax,0FCh
	mov	edx,ebx
	mov	ecx,eax
	imul	ebx,loc6
	imul	eax,loc6
	shr	ebx,8
	shr	eax,8
	add	bl,dl
	setae	dl
	add	al,cl
	setae	cl
	dec	dl
	dec	cl
	or	bl,dl
	or	al,cl
	shr	ebx,3
	shr	eax,2
	shl	ebx,0Bh
	shl	eax,5
	mov	ecx,loc5
	shl	ecx,3
	or	eax,ebx
	and	ecx,0FFh
	mov	edx,ecx
	imul	ecx,loc6
	shr	ecx,8
	add	cl,dl
	setae	dl
	dec	dl
	or	cl,dl
	shr	ecx,3
	or	eax,ecx
	mov	WORD PTR [edi],ax
$L007DEFA8:
	inc	esi
	add	edi,2
	dec	loc1
	jne	$L007DEF2D
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DEF23
	ret
FUN_007DEEFA ENDP

; FUNCTION: GAMEMD 0x7DEFD7
; FUN_007DEFD7 -- Masked row blend, scalar form, variant 2 of the routine at 0x7DEEFA.
FUN_007DEFD7 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc6,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
$L007DF000:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
$L007DF00A:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DF085
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-18h],al
	mov	loc5,ebx
	shr	ebx,8
	mov	eax,loc5
	shr	eax,2
	and	ebx,0FCh
	and	eax,0F8h
	mov	edx,ebx
	mov	ecx,eax
	imul	ebx,loc6
	imul	eax,loc6
	shr	ebx,8
	shr	eax,8
	add	bl,dl
	setae	dl
	add	al,cl
	setae	cl
	dec	dl
	dec	cl
	or	bl,dl
	or	al,cl
	shr	ebx,2
	shr	eax,3
	shl	ebx,0Ah
	shl	eax,5
	mov	ecx,loc5
	shl	ecx,3
	or	eax,ebx
	and	ecx,0FFh
	mov	edx,ecx
	imul	ecx,loc6
	shr	ecx,8
	add	cl,dl
	setae	dl
	dec	dl
	or	cl,dl
	shr	ecx,3
	or	eax,ecx
	mov	WORD PTR [edi],ax
$L007DF085:
	inc	esi
	add	edi,2
	dec	loc1
	jne	$L007DF00A
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF000
	ret
FUN_007DEFD7 ENDP

; FUNCTION: GAMEMD 0x7DF0B4
; FUN_007DF0B4 -- Masked row blend, scalar form, variant 3 of the routine at 0x7DEEFA.
FUN_007DF0B4 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc6,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
$L007DF0DD:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
$L007DF0E7:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DF162
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-18h],al
	mov	loc5,ebx
	shr	ebx,8
	mov	eax,loc5
	shr	eax,3
	and	ebx,0F8h
	and	eax,0F8h
	mov	edx,ebx
	mov	ecx,eax
	imul	ebx,loc6
	imul	eax,loc6
	shr	ebx,8
	shr	eax,8
	add	bl,dl
	setae	dl
	add	al,cl
	setae	cl
	dec	dl
	dec	cl
	or	bl,dl
	or	al,cl
	shr	ebx,3
	shr	eax,3
	shl	ebx,0Bh
	shl	eax,6
	mov	ecx,loc5
	shl	ecx,2
	or	eax,ebx
	and	ecx,0FFh
	mov	edx,ecx
	imul	ecx,loc6
	shr	ecx,8
	add	cl,dl
	setae	dl
	dec	dl
	or	cl,dl
	shr	ecx,2
	or	eax,ecx
	mov	WORD PTR [edi],ax
$L007DF162:
	inc	esi
	add	edi,2
	dec	loc1
	jne	$L007DF0E7
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF0DD
	ret
FUN_007DF0B4 ENDP

; FUNCTION: GAMEMD 0x7DF191
; FUN_007DF191 -- Masked row blend, scalar form, variant 4 of the routine at 0x7DEEFA.
FUN_007DF191 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD
	xor	eax,eax
	mov	loc5,eax
	mov	eax,arg6
	mov	loc2,eax
	mov	loc6,0
	mov	esi,arg1
	mov	loc3,esi
	mov	edi,arg2
	mov	loc4,edi
$L007DF1BA:
	mov	eax,arg5
	mov	loc1,eax
	xor	eax,eax
	xor	ebx,ebx
$L007DF1C4:
	mov	al,BYTE PTR [esi]
	test	al,al
	je	$L007DF23F
	mov	bx,WORD PTR [edi]
	mov	BYTE PTR [ebp-18h],al
	mov	loc5,ebx
	shr	ebx,7
	mov	eax,loc5
	shr	eax,2
	and	ebx,0F8h
	and	eax,0F8h
	mov	edx,ebx
	mov	ecx,eax
	imul	ebx,loc6
	imul	eax,loc6
	shr	ebx,8
	shr	eax,8
	add	bl,dl
	setae	dl
	add	al,cl
	setae	cl
	dec	dl
	dec	cl
	or	bl,dl
	or	al,cl
	shr	ebx,3
	shr	eax,3
	shl	ebx,0Ah
	shl	eax,5
	mov	ecx,loc5
	shl	ecx,3
	or	eax,ebx
	and	ecx,0FFh
	mov	edx,ecx
	imul	ecx,loc6
	shr	ecx,8
	add	cl,dl
	setae	dl
	dec	dl
	or	cl,dl
	shr	ecx,3
	or	eax,ecx
	mov	WORD PTR [edi],ax
$L007DF23F:
	inc	esi
	add	edi,2
	dec	loc1
	jne	$L007DF1C4
	mov	esi,loc3
	add	esi,arg3
	mov	loc3,esi
	mov	edi,loc4
	add	edi,arg4
	mov	loc4,edi
	dec	loc2
	jne	$L007DF1BA
	ret
FUN_007DF191 ENDP

_TEXT ENDS
END
