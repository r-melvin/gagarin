; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C6D40-0x7C734D (eight routines).
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

PUBLIC C FUN_007C6D40
PUBLIC C FUN_007C6DD6
PUBLIC C FUN_007C6E94
PUBLIC C FUN_007C6F2E
PUBLIC C FUN_007C6FC8
PUBLIC C FUN_007C70C4
PUBLIC C FUN_007C7174
PUBLIC C FUN_007C726A

; FUNCTION: GAMEMD 0x7C6D40
; FUN_007C6D40 -- Codebook block expander with 8-byte entries (arguments as the routine at 0x7C6B70); a high index byte of 0xFF takes the
; alternate path.
FUN_007C6D40 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD
	mov	eax,arg6
	shl	eax,1
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc4,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C6D6A:
	mov	ecx,arg4
$L007C6D6D:
	mov	eax,loc4
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	cmp	bh,0FFh
	je	$L007C6DA6
	shl	ebx,3
	add	ebx,arg1
	mov	eax,DWORD PTR [ebx]
	mov	edx,DWORD PTR [ebx+4]
	mov	ebx,arg6
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [ebx+edi*1],edx
	add	edi,4
	dec	ecx
	jne	$L007C6D6D
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6DCF
	jmp	$L007C6D6A
$L007C6DA6:
	mov	bh,bl
	mov	ax,bx
	rol	eax,10h
	mov	ax,bx
	mov	ebx,arg6
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [ebx+edi*1],eax
	add	edi,4
	dec	ecx
	jne	$L007C6D6D
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6DCF
	jmp	$L007C6D6A
$L007C6DCF:
	ret
FUN_007C6D40 ENDP

; FUNCTION: GAMEMD 0x7C6DD6
; FUN_007C6DD6 -- Codebook block expander with 16-byte entries; a high index byte of 0xFF takes the alternate path.
FUN_007C6DD6 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD
	mov	eax,arg6
	shl	eax,2
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc4,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C6E01:
	mov	ecx,arg4
$L007C6E04:
	mov	eax,loc4
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	cmp	bh,0FFh
	je	$L007C6E55
	shl	ebx,4
	add	ebx,arg1
	mov	eax,DWORD PTR [ebx]
	mov	edx,DWORD PTR [ebx+4]
	mov	DWORD PTR [edi],eax
	mov	eax,ebx
	mov	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],edx
	mov	ebx,eax
	mov	eax,DWORD PTR [ebx+8]
	mov	edx,DWORD PTR [ebx+0Ch]
	mov	ebx,arg6
	shl	ebx,1
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],edx
	add	edi,4
	dec	ecx
	jne	$L007C6E04
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6E8D
	jmp	$L007C6E01
$L007C6E55:
	mov	bh,bl
	mov	ax,bx
	rol	eax,10h
	mov	ax,bx
	mov	DWORD PTR [edi],eax
	mov	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	edi,4
	dec	ecx
	jne	$L007C6E04
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6E8D
	jmp	$L007C6E01
$L007C6E8D:
	ret
FUN_007C6DD6 ENDP

; FUNCTION: GAMEMD 0x7C6E94
; FUN_007C6E94 -- Codebook block expander with 16-byte entries, another variant; a high index byte of 0xFF takes the alternate path.
FUN_007C6E94 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD
	mov	eax,arg6
	shl	eax,1
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc4,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C6EBE:
	mov	ecx,arg4
$L007C6EC1:
	mov	eax,loc4
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	cmp	bh,0FFh
	je	$L007C6F02
	shl	ebx,4
	add	ebx,arg1
	mov	al,BYTE PTR [ebx]
	mov	ah,BYTE PTR [ebx+2]
	mov	WORD PTR [edi],ax
	mov	al,BYTE PTR [ebx+8]
	mov	ah,BYTE PTR [ebx+0Ah]
	mov	ebx,arg6
	mov	WORD PTR [ebx+edi*1],ax
	add	edi,2
	dec	ecx
	jne	$L007C6EC1
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6F27
	jmp	$L007C6EBE
$L007C6F02:
	mov	bh,bl
	mov	ax,bx
	mov	WORD PTR [edi],ax
	mov	ebx,arg6
	mov	WORD PTR [ebx+edi*1],ax
	add	edi,2
	dec	ecx
	jne	$L007C6EC1
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6F27
	jmp	$L007C6EBE
$L007C6F27:
	ret
FUN_007C6E94 ENDP

; FUNCTION: GAMEMD 0x7C6F2E
; FUN_007C6F2E -- Codebook block expander with 8-byte entries, another variant; a high index byte of 0xFF takes the alternate path.
FUN_007C6F2E PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD
	mov	eax,arg6
	shl	eax,1
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc4,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C6F58:
	mov	ecx,arg4
$L007C6F5B:
	mov	eax,loc4
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	cmp	bh,0FFh
	je	$L007C6F9C
	shl	ebx,3
	add	ebx,arg1
	mov	al,BYTE PTR [ebx]
	mov	ah,BYTE PTR [ebx+2]
	mov	WORD PTR [edi],ax
	mov	al,BYTE PTR [ebx+8]
	mov	ah,BYTE PTR [ebx+0Ah]
	mov	ebx,arg6
	mov	WORD PTR [ebx+edi*1],ax
	add	edi,2
	dec	ecx
	jne	$L007C6F5B
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6FC1
	jmp	$L007C6F58
$L007C6F9C:
	mov	bh,bl
	mov	ax,bx
	mov	WORD PTR [edi],ax
	mov	ebx,arg6
	mov	WORD PTR [ebx+edi*1],ax
	add	edi,2
	dec	ecx
	jne	$L007C6F5B
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C6FC1
	jmp	$L007C6F58
$L007C6FC1:
	ret
FUN_007C6F2E ENDP

; FUNCTION: GAMEMD 0x7C6FC8
; FUN_007C6FC8 -- Codebook block expander with 32-byte entries; bit 7 of the high index byte takes the alternate path.
FUN_007C6FC8 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
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
$L007C6FF6:
	mov	ecx,arg4
$L007C6FF9:
	mov	eax,loc5
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	test	bh,80h
	js	$L007C706F
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
	jne	$L007C6FF9
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C70BD
	jmp	$L007C6FF6
$L007C706F:
	and	bx,7FFFh
	mov	ax,bx
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
	jne	$L007C6FF9
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C70BD
	jmp	$L007C6FF6
$L007C70BD:
	ret
FUN_007C6FC8 ENDP

; FUNCTION: GAMEMD 0x7C70C4
; FUN_007C70C4 -- Codebook block expander with 16-byte entries; bit 7 of the high index byte takes the alternate path.
FUN_007C70C4 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD
	shl	arg6,1
	mov	eax,arg6
	shl	eax,1
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc5,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C70F1:
	mov	ecx,arg4
$L007C70F4:
	mov	eax,loc5
	xor	ebx,ebx
	mov	bh,BYTE PTR [eax+esi*1]
	mov	bl,BYTE PTR [esi]
	inc	esi
	test	bh,80h
	js	$L007C713A
	shl	ebx,4
	add	ebx,arg1
	mov	eax,DWORD PTR [ebx]
	mov	edx,DWORD PTR [ebx+4]
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [edi+4],edx
	mov	eax,DWORD PTR [ebx+8]
	mov	edx,DWORD PTR [ebx+0Ch]
	mov	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],edx
	add	edi,8
	dec	ecx
	jne	$L007C70F4
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C716D
	jmp	$L007C70F1
$L007C713A:
	and	bx,7FFFh
	mov	ax,bx
	shl	eax,10h
	mov	ax,bx
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [edi+4],eax
	mov	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	add	edi,8
	dec	ecx
	jne	$L007C70F4
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C716D
	jmp	$L007C70F1
$L007C716D:
	ret
FUN_007C70C4 ENDP

; FUNCTION: GAMEMD 0x7C7174
; FUN_007C7174 -- Codebook block expander with 32-byte entries; a high index byte of 0xFF takes the alternate path.
FUN_007C7174 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD
	mov	eax,arg6
	shl	eax,3
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc4,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C719F:
	mov	ecx,arg4
$L007C71A2:
	mov	eax,loc4
	xor	ebx,ebx
	mov	bl,BYTE PTR [esi]
	mov	bh,BYTE PTR [eax+esi*1]
	inc	esi
	cmp	bh,0FFh
	je	$L007C7210
	shl	ebx,5
	add	ebx,arg1
	mov	eax,DWORD PTR [ebx]
	mov	edx,arg6
	mov	DWORD PTR [edi],eax
	mov	eax,DWORD PTR [ebx+4]
	mov	DWORD PTR [edx+edi*1],eax
	shl	edx,1
	mov	eax,DWORD PTR [ebx+8]
	mov	DWORD PTR [edx+edi*1],eax
	add	edx,arg6
	mov	eax,DWORD PTR [ebx+0Ch]
	mov	DWORD PTR [edx+edi*1],eax
	add	edx,arg6
	mov	eax,DWORD PTR [ebx+10h]
	mov	DWORD PTR [edx+edi*1],eax
	add	edx,arg6
	mov	eax,DWORD PTR [ebx+14h]
	mov	DWORD PTR [edx+edi*1],eax
	add	edx,arg6
	mov	eax,DWORD PTR [ebx+18h]
	mov	DWORD PTR [edx+edi*1],eax
	add	edx,arg6
	mov	eax,DWORD PTR [ebx+1Ch]
	mov	DWORD PTR [edx+edi*1],eax
	add	edi,4
	dec	ecx
	jne	$L007C71A2
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C7263
	jmp	$L007C719F
$L007C7210:
	mov	bh,bl
	mov	ax,bx
	rol	eax,10h
	mov	ax,bx
	mov	ebx,arg6
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [ebx+edi*1],eax
	shl	ebx,1
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	add	edi,4
	dec	ecx
	jne	$L007C71A2
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C7263
	jmp	$L007C719F
$L007C7263:
	ret
FUN_007C7174 ENDP

; FUNCTION: GAMEMD 0x7C726A
; FUN_007C726A -- Codebook block expander with 32-byte entries, another variant; a high index byte of 0xFF takes the alternate path.
FUN_007C726A PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD
	mov	eax,arg6
	shl	eax,2
	mov	loc3,eax
	mov	esi,arg2
	mov	eax,arg5
	mul	arg4
	mov	loc4,eax
	add	eax,esi
	mov	loc1,eax
	mov	edi,arg3
	mov	loc2,edi
$L007C7295:
	mov	ecx,arg4
$L007C7298:
	mov	eax,loc4
	xor	ebx,ebx
	mov	bl,BYTE PTR [esi]
	mov	bh,BYTE PTR [eax+esi*1]
	inc	esi
	cmp	bh,0FFh
	je	$L007C72FD
	shl	ebx,5
	add	ebx,arg1
	mov	eax,DWORD PTR [ebx]
	mov	edx,arg6
	mov	DWORD PTR [edi],eax
	mov	eax,DWORD PTR [ebx+4]
	mov	DWORD PTR [edi+4],eax
	mov	eax,DWORD PTR [ebx+8]
	mov	DWORD PTR [edx+edi*1],eax
	mov	eax,DWORD PTR [ebx+0Ch]
	mov	DWORD PTR [edx+edi*1+4],eax
	shl	edx,1
	mov	eax,DWORD PTR [ebx+10h]
	mov	DWORD PTR [edx+edi*1],eax
	mov	eax,DWORD PTR [ebx+14h]
	mov	DWORD PTR [edx+edi*1+4],eax
	add	edx,arg6
	mov	eax,DWORD PTR [ebx+18h]
	mov	DWORD PTR [edx+edi*1],eax
	mov	eax,DWORD PTR [ebx+1Ch]
	mov	DWORD PTR [edx+edi*1+4],eax
	add	edi,8
	dec	ecx
	jne	$L007C7298
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C7347
	jmp	$L007C7295
$L007C72FD:
	mov	bh,bl
	mov	ax,bx
	rol	eax,10h
	mov	ax,bx
	mov	ebx,arg6
	mov	DWORD PTR [edi],eax
	mov	DWORD PTR [edi+4],eax
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	shl	ebx,1
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	add	ebx,arg6
	mov	DWORD PTR [ebx+edi*1],eax
	mov	DWORD PTR [ebx+edi*1+4],eax
	add	edi,8
	dec	ecx
	jne	$L007C7298
	mov	edi,loc2
	add	edi,loc3
	mov	loc2,edi
	cmp	esi,loc1
	jae	$L007C7347
	jmp	$L007C7295
$L007C7347:
	ret
FUN_007C726A ENDP

_TEXT ENDS
END
