; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C6B70-0x7C6D3E (two routines).
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

PUBLIC C FUN_007C6B70
PUBLIC C FUN_007C6C79
EXTERN C DAT_00B1D14C:DWORD

; FUNCTION: GAMEMD 0x7C6B70
; FUN_007C6B70 -- Codebook block expander: arg1 codebook (32-byte entries), arg2 source index bytes (low plane, then the high plane arg5*arg4
; bytes later), arg3 destination, arg4 blocks per row, arg5 rows, arg6 destination row pitch. A high index byte with bit 7 set
; takes the alternate path.
FUN_007C6B70 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD
	shl	arg6,1
	mov	eax,arg6
	shl	eax,2
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc5,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C6B9E:
	mov	ecx,arg4
$L007C6BA1:
	mov	eax,loc5
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	test	bh,80h
	js	$L007C6C17
	shl	ebx,5
	add	ebx,arg1
	mov	eax,DWORD PTR [ebx]
	mov	edx,DWORD PTR [ebx+4]
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [edi+4],edx
	mov	eax,DWORD PTR [ebx+8]
	mov	edx,DWORD PTR [ebx+0Ch]
	mov	loc4,ebx
	mov	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],edx
	mov	ebx,loc4
	mov	eax,DWORD PTR [ebx+10h]
	mov	edx,DWORD PTR [ebx+14h]
	mov	ebx,arg6
	shl	ebx,1
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],edx
	mov	ebx,loc4
	mov	eax,DWORD PTR [ebx+18h]
	mov	edx,DWORD PTR [ebx+1Ch]
	mov	ebx,arg6
	shl	ebx,1
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],edx
	add	edi,8
	dec	ecx
	jne	$L007C6BA1
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6C72
	jmp	$L007C6B9E
$L007C6C17:
	and	ebx,7FFFh
	shl	ebx,1
	mov	edx,DWORD PTR DAT_00B1D14C
	mov	ax,WORD PTR [ebx+edx*1]
	mov	bx,ax
	shl	eax,10h
	mov	ax,bx
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [edi+4],eax
	mov	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	add	edi,8
	dec	ecx
	jne	$L007C6BA1
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6C72
	jmp	$L007C6B9E
$L007C6C72:
	ret
FUN_007C6B70 ENDP

; FUNCTION: GAMEMD 0x7C6C79
; FUN_007C6C79 -- Codebook block expander, second variant of the routine above (32-byte entries; bit 7 of the high index byte takes the
; alternate path).
FUN_007C6C79 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD
	shl	arg6,1
	mov	eax,arg6
	shl	eax,2
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc5,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C6CA7:
	mov	ecx,arg4
$L007C6CAA:
	mov	eax,loc5
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	test	bh,80h
	js	$L007C6CF2
	shl	ebx,5
	add	ebx,arg1
	mov	eax,DWORD PTR [ebx]
	mov	edx,DWORD PTR [ebx+4]
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [edi+4],edx
	mov	eax,DWORD PTR [ebx+10h]
	mov	edx,DWORD PTR [ebx+14h]
	mov	ebx,arg6
	shl	ebx,1
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],edx
	add	edi,8
	dec	ecx
	jne	$L007C6CAA
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6D38
	jmp	$L007C6CA7
$L007C6CF2:
	and	ebx,7FFFh
	shl	ebx,1
	mov	edx,DWORD PTR DAT_00B1D14C
	mov	ax,WORD PTR [ebx+edx*1]
	mov	bx,ax
	shl	eax,10h
	mov	ax,bx
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [edi+4],eax
	mov	ebx,arg6
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	add	edi,8
	dec	ecx
	jne	$L007C6CAA
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6D38
	jmp	$L007C6CA7
$L007C6D38:
	ret
FUN_007C6C79 ENDP

_TEXT ENDS
END
