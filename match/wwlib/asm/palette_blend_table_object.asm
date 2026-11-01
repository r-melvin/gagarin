; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7E0000-0x7E038C (seven routines).
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

PUBLIC C FUN_007E0000
PUBLIC C FUN_007E0001
PUBLIC C FUN_007E00A6
PUBLIC C FUN_007E0170
PUBLIC C FUN_007E01D2
PUBLIC C FUN_007E01FB
PUBLIC C FUN_007E02CB
EXTERN C DAT_00A8F91C:BYTE
EXTERN C DAT_00879124:BYTE
EXTERN C DAT_00877D20:BYTE
EXTERN C DAT_00878720:BYTE
EXTERN C DAT_00A8F918:DWORD

; FUNCTION: GAMEMD 0x7E0000
; FUN_007E0000 -- A bare RET (an empty routine).
FUN_007E0000 PROC C
	ret
FUN_007E0000 ENDP

; FUNCTION: GAMEMD 0x7E0001
; FUN_007E0001 -- Row-pair merge through the 64 KiB blend table DAT_00A8F91C: arg1 source rows, arg2 destination, arg3 row count, arg4 row
; width in bytes, arg5 destination pitch. Each output pixel is the table entry for a neighbouring source pixel pair.
FUN_007E0001 PROC C USES ebx ecx edi esi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD
	LOCAL	loc1:DWORD
	pushad
	mov	eax,arg2
	mov	loc1,eax
	mov	esi,arg1
$L007E0015:
	mov	ecx,arg4
	sub	ecx,2
	shr	ecx,1
	mov	edi,loc1
	jmp	$L007E0040
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,0A4h,24h,0,0,0,0
	mov	edi,edi
$L007E0040:
	mov	eax,DWORD PTR [esi]
	lea	esi,[esi+2]
	mov	edx,eax
	mov	ebx,eax
	and	edx,0FFFFh
	ror	ebx,8
	mov	bl,BYTE PTR [edx+DAT_00A8F91C]
	mov	bh,ah
	and	eax,0FFFF00h
	ror	ebx,8
	shr	eax,8
	mov	bh,BYTE PTR [eax+DAT_00A8F91C]
	ror	ebx,10h
	mov	DWORD PTR [edi],ebx
	add	edi,4
	dec	ecx
	jne	$L007E0040
	xor	eax,eax
	mov	ax,WORD PTR [esi]
	mov	BYTE PTR [edi],al
	inc	edi
	lea	esi,[esi+2]
	mov	al,BYTE PTR [eax+DAT_00A8F91C]
	mov	BYTE PTR [edi],al
	inc	edi
	mov	BYTE PTR [edi],ah
	inc	edi
	mov	BYTE PTR [edi],0
	mov	edi,arg5
	add	loc1,edi
	dec	arg3
	jne	$L007E0015
	popad
	ret
FUN_007E0001 ENDP

; FUNCTION: GAMEMD 0x7E00A6
; FUN_007E00A6 -- Row-pair merge through DAT_00A8F91C, second form of the routine at 0x7E0001.
FUN_007E00A6 PROC C arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD
	pushad
	mov	eax,arg2
	mov	loc1,eax
	mov	esi,arg1
	mov	edi,arg2
$L007E00B9:
	mov	loc2,0
	mov	ecx,arg4
	sub	ecx,2
	shr	ecx,1
	mov	loc3,ecx
	mov	ecx,OFFSET DAT_00879124
	mov	edi,loc1
	jmp	$L007E00E0
	db	8Dh,0A4h,24h,0,0,0,0
	db	8Dh,64h,24h,0
$L007E00E0:
	mov	eax,DWORD PTR [esi]
	lea	esi,[esi+2]
	mov	edx,eax
	mov	ebx,eax
	and	edx,0FFFFh
	ror	ebx,8
	mov	bl,BYTE PTR [edx+DAT_00A8F91C]
	mov	bh,ah
	and	eax,0FFFF00h
	ror	ebx,8
	shr	eax,8
	mov	bh,BYTE PTR [eax+DAT_00A8F91C]
	ror	ebx,10h
	mov	DWORD PTR [edi],ebx
	mov	DWORD PTR [ecx],ebx
	add	edi,4
	add	ecx,4
	dec	loc3
	jne	$L007E00E0
	xor	eax,eax
	mov	ax,WORD PTR [esi]
	mov	BYTE PTR [edi],al
	mov	BYTE PTR [ecx],al
	inc	edi
	inc	ecx
	lea	esi,[esi+2]
	mov	al,BYTE PTR [eax+DAT_00A8F91C]
	mov	BYTE PTR [edi],al
	mov	BYTE PTR [ecx],al
	inc	edi
	inc	ecx
	mov	BYTE PTR [edi],ah
	mov	BYTE PTR [ecx],ah
	inc	edi
	inc	ecx
	mov	BYTE PTR [edi],0
	mov	BYTE PTR [ecx],0
	mov	edi,arg5
	shr	edi,1
	add	loc1,edi
	push	esi
	push	edi
	mov	esi,OFFSET DAT_00879124
	mov	edi,loc1
	mov	ecx,arg4
	shr	ecx,1
	rep movsd
	pop	edi
	pop	esi
	add	loc1,edi
	mov	edi,loc1
	dec	arg3
	jne	$L007E00B9
	popad
	ret
FUN_007E00A6 ENDP

; FUNCTION: GAMEMD 0x7E0170
; FUN_007E0170 -- Merges one row of 8-bit pixels (arg1, width arg3) pairwise through DAT_00A8F91C into arg2.
FUN_007E0170 PROC C arg1:DWORD, arg2:DWORD, arg3:DWORD
	pushad
	mov	ecx,arg3
	sub	ecx,2
	shr	ecx,1
	mov	esi,arg1
	mov	edi,arg2
$L007E0182:
	mov	eax,DWORD PTR [esi]
	lea	esi,[esi+2]
	mov	edx,eax
	mov	ebx,eax
	and	edx,0FFFFh
	ror	ebx,8
	mov	bl,BYTE PTR [edx+DAT_00A8F91C]
	mov	bh,ah
	and	eax,0FFFF00h
	ror	ebx,8
	shr	eax,8
	mov	bh,BYTE PTR [eax+DAT_00A8F91C]
	ror	ebx,10h
	mov	DWORD PTR [edi],ebx
	add	edi,4
	dec	ecx
	jne	$L007E0182
	xor	eax,eax
	mov	ax,WORD PTR [esi]
	mov	BYTE PTR [edi],al
	inc	edi
	mov	al,BYTE PTR [eax+DAT_00A8F91C]
	mov	BYTE PTR [edi],al
	inc	edi
	mov	BYTE PTR [edi],ah
	inc	edi
	mov	BYTE PTR [edi],0
	popad
	ret
FUN_007E0170 ENDP

; FUNCTION: GAMEMD 0x7E01D2
; FUN_007E01D2 -- Looks up arg4*2 pixel pairs: out[k] = DAT_00A8F91C[(arg2[k] << 8) | arg1[k]] into arg3.
FUN_007E01D2 PROC C arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD
	pushad
	mov	esi,arg1
	mov	edi,arg3
	mov	ebx,arg2
	xor	eax,eax
	mov	ecx,arg4
	add	ecx,ecx
$L007E01E6:
	mov	al,BYTE PTR [esi]
	mov	ah,BYTE PTR [ebx]
	inc	esi
	inc	ebx
	mov	dl,BYTE PTR [eax+DAT_00A8F91C]
	mov	BYTE PTR [edi],dl
	inc	edi
	dec	ecx
	jne	$L007E01E6
	popad
	ret
FUN_007E01D2 ENDP

; FUNCTION: GAMEMD 0x7E01FB
; FUN_007E01FB -- Merges arg3 rows by combining each pair of source rows with the two row merges above, using the scratch rows at DAT_00877D20,
; DAT_00878720 and DAT_00879124.
FUN_007E01FB PROC C arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD
	pushad
	mov	eax,arg2
	mov	loc1,eax
	mov	loc3,OFFSET DAT_00877D20
	mov	loc4,OFFSET DAT_00878720
	mov	ecx,arg4
	shr	ecx,1
	mov	loc2,ecx
	shr	arg5,1
	push	arg4
	push	loc3
	push	arg1
	call	FUN_007E0170
	add	esp,0Ch
	mov	esi,arg4
	push	loc3
	push	loc4
	pop	loc3
	pop	loc4
	add	arg1,esi
	dec	arg3
$L007E0247:
	push	arg4
	push	loc3
	push	arg1
	call	FUN_007E0170
	add	esp,0Ch
	push	arg4
	push	OFFSET DAT_00879124
	push	loc3
	push	loc4
	call	FUN_007E01D2
	add	esp,10h
	mov	esi,loc4
	mov	edi,loc1
	mov	ecx,loc2
	rep movsd
	mov	edi,loc1
	mov	esi,OFFSET DAT_00879124
	add	edi,arg5
	mov	ecx,loc2
	mov	loc1,edi
	rep movsd
	mov	edi,loc1
	mov	esi,arg4
	add	edi,arg5
	add	arg1,esi
	mov	loc1,edi
	push	loc3
	push	loc4
	pop	loc3
	pop	loc4
	dec	arg3
	jne	$L007E0247
	push	arg4
	push	loc3
	push	arg1
	call	FUN_007E0170
	add	esp,0Ch
	mov	esi,loc3
	mov	edi,loc1
	mov	ecx,loc2
	rep movsd
	popad
	ret
FUN_007E01FB ENDP

; FUNCTION: GAMEMD 0x7E02CB
; FUN_007E02CB -- Builds the 256x256 byte blend table at DAT_00A8F91C: entry [i*256+j] is the index of the palette entry (palette at
; DAT_00A8F918, 3 bytes per entry) closest in squared distance to the average of entries i and j.
FUN_007E02CB PROC C
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD, loc6:DWORD, loc7:DWORD
	pushad
	mov	loc4,0
	mov	loc1,100h
	mov	esi,DWORD PTR DAT_00A8F918
$L007E02E6:
	mov	edi,DWORD PTR DAT_00A8F918
	mov	ecx,100h
$L007E02F1:
	mov	bl,BYTE PTR [esi]
	add	bl,BYTE PTR [edi]
	shr	bl,1
	mov	bh,BYTE PTR [esi+1]
	add	bh,BYTE PTR [edi+1]
	shr	bh,1
	mov	dl,BYTE PTR [esi+2]
	add	dl,BYTE PTR [edi+2]
	shr	dl,1
	mov	loc6,0
	mov	loc7,0FFFFFFFFh
	push	edi
	push	ecx
	mov	edi,DWORD PTR DAT_00A8F918
	mov	loc5,0
$L007E0324:
	xor	eax,eax
	xor	ecx,ecx
	mov	al,BYTE PTR [edi]
	sub	al,bl
	imul	al
	mov	ecx,eax
	mov	al,BYTE PTR [edi+1]
	sub	al,bh
	imul	al
	add	ecx,eax
	mov	al,BYTE PTR [edi+2]
	sub	al,dl
	imul	al
	add	ecx,eax
	cmp	ecx,loc7
	ja	$L007E0354
	mov	loc7,ecx
	mov	eax,loc5
	mov	loc6,eax
	test	ecx,ecx
	je	$L007E0363
$L007E0354:
	lea	edi,[edi+3]
	inc	loc5
	cmp	loc5,100h
	jb	$L007E0324
$L007E0363:
	mov	edi,loc4
	mov	eax,loc6
	mov	BYTE PTR [edi+DAT_00A8F91C],al
	inc	loc4
	pop	ecx
	pop	edi
	lea	edi,[edi+3]
	dec	ecx
	jne	$L007E02F1
	lea	esi,[esi+3]
	dec	loc1
	jne	$L007E02E6
	popad
	ret
FUN_007E02CB ENDP

_TEXT ENDS
END
