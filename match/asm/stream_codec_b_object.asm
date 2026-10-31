; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C6730-0x7C6B67 (two routines and a jump table).
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

PUBLIC C FUN_007C6730
PUBLIC C FUN_007C6752
EXTERN C DAT_008759B4:DWORD
EXTERN C DAT_00876FF4:WORD
EXTERN C DAT_00877C14:BYTE
EXTERN C DAT_00877B14:BYTE

; FUNCTION: GAMEMD 0x7C6730
; FUN_007C6730 -- Clears the counters of a stream record at arg1 (offsets 0x14, 0x22, 0x28, 0x36).
FUN_007C6730 PROC C arg1:DWORD
	mov	eax,arg1
	mov	WORD PTR [eax+22h],0
	mov	DWORD PTR [eax+14h],0
	mov	WORD PTR [eax+36h],0
	mov	DWORD PTR [eax+28h],0
	ret
FUN_007C6730 ENDP

; FUNCTION: GAMEMD 0x7C6752
; FUN_007C6752 -- Table-driven sample decoder, second variant (see the first stream codec object): arg1 stream record, arg2 byte count;
; the tail of the routine is a dispatch on the source alignment through the jump table at the end of this object.
FUN_007C6752 PROC C USES esi edi ebx ecx edx, arg1:DWORD, arg2:DWORD
	mov	ebx,arg1
	mov	cx,WORD PTR [ebx+38h]
	mov	dx,WORD PTR [ebx+3Ah]
	cmp	cx,8
	jne	$L007C6785
	cmp	dx,2
	jne	$L007C6776
	jmp	$L007C69AD
$L007C6776:
	cmp	dx,1
	jne	$L007C69AD
	jmp	$L007C69AD
$L007C6785:
	cmp	cx,10h
	jne	$L007C69AD
	cmp	dx,2
	jne	$L007C679A
	jmp	$L007C69AD
$L007C679A:
	cmp	dx,1
	jne	$L007C69AD
	push	ebp
	push	ebx
	xor	edx,edx
	mov	eax,DWORD PTR [ebx+14h]
	mov	dx,WORD PTR [ebx+22h]
	mov	esi,DWORD PTR [ebx]
	mov	edi,DWORD PTR [ebx+4]
	mov	ebp,arg2
	cmp	ebp,10h
	jl	$L007C67C3
	mov	ebx,esi
	and	ebx,3
	jne	$L007C67D0
$L007C67C3::
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	or	ebp,ebp
	jmp	$L007C6981
$L007C67D0:
	jmp	DWORD PTR [ebx*4+$L007C6B58]
	nop
$L007C67D8::
	sub	ebp,0Ch
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C6AFC
	nop
$L007C67E8::
	sub	ebp,8
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C6AC0
	nop
$L007C67F8::
	sub	ebp,4
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C6A8C
	nop
$L007C6808:
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C69B4
	cmp	eax,0FFFF8000h
	jl	$L007C69C0
$L007C682C:
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	mov	WORD PTR [edi],ax
$L007C6835:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C69CC
	cmp	eax,0FFFF8000h
	jl	$L007C69D8
$L007C685B:
	or	dl,BYTE PTR [ebx+DAT_00877B14]
	mov	WORD PTR [edi+2],ax
	shr	ecx,10h
$L007C6868:
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C69E4
	cmp	eax,0FFFF8000h
	jl	$L007C69F0
$L007C688C:
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	mov	WORD PTR [edi+4],ax
$L007C6896:
	mov	bl,cl
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C69FC
	cmp	eax,0FFFF8000h
	jl	$L007C6A08
$L007C68BC:
	or	dl,BYTE PTR [ebx+DAT_00877B14]
	mov	WORD PTR [edi+6],ax
$L007C68C6:
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C6A14
	cmp	eax,0FFFF8000h
	jl	$L007C6A20
$L007C68EA:
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	mov	WORD PTR [edi+8],ax
$L007C68F4:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C6A2C
	cmp	eax,0FFFF8000h
	jl	$L007C6A38
$L007C691A:
	or	dl,BYTE PTR [ebx+DAT_00877B14]
	mov	WORD PTR [edi+0Ah],ax
$L007C6924:
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C6A44
	cmp	eax,0FFFF8000h
	jl	$L007C6A50
$L007C6948:
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	mov	WORD PTR [edi+0Ch],ax
$L007C6952:
	add	eax,DWORD PTR [edx*2+DAT_008759B4]
	mov	dx,WORD PTR [edx+DAT_00876FF4]
	cmp	eax,7FFFh
	jg	$L007C6A5C
	cmp	eax,0FFFF8000h
	jl	$L007C6A68
$L007C6976:
	mov	WORD PTR [edi+0Eh],ax
	add	esi,4
	add	edi,10h
	dec	ebp
$L007C6981:
	jle	$L007C6992
	mov	ecx,DWORD PTR [esi]
	mov	bl,cl
	or	dl,BYTE PTR [ebx+DAT_00877B14]
	jmp	$L007C6808
$L007C6992:
	jne	$L007C69A1
	pop	ecx
	shr	ecx,1
	and	ecx,7
	jmp	DWORD PTR [ecx*4+$L007C6B38]
$L007C69A1::
	pop	ebx
	pop	ebp
	mov	DWORD PTR [ebx+14h],eax
	mov	WORD PTR [ebx+22h],dx
	mov	eax,arg2
$L007C69AD:
	ret
$L007C69B4:
	mov	eax,7FFFh
	jmp	$L007C682C
	mov	edi,edi
$L007C69C0:
	mov	eax,0FFFF8000h
	jmp	$L007C682C
	mov	edi,edi
$L007C69CC:
	mov	eax,7FFFh
	jmp	$L007C685B
	mov	edi,edi
$L007C69D8:
	mov	eax,0FFFF8000h
	jmp	$L007C685B
	mov	edi,edi
$L007C69E4:
	mov	eax,7FFFh
	jmp	$L007C688C
	mov	edi,edi
$L007C69F0:
	mov	eax,0FFFF8000h
	jmp	$L007C688C
	mov	edi,edi
$L007C69FC:
	mov	eax,7FFFh
	jmp	$L007C68BC
	mov	edi,edi
$L007C6A08:
	mov	eax,0FFFF8000h
	jmp	$L007C68BC
	mov	edi,edi
$L007C6A14:
	mov	eax,7FFFh
	jmp	$L007C68EA
	mov	edi,edi
$L007C6A20:
	mov	eax,0FFFF8000h
	jmp	$L007C68EA
	mov	edi,edi
$L007C6A2C:
	mov	eax,7FFFh
	jmp	$L007C691A
	mov	edi,edi
$L007C6A38:
	mov	eax,0FFFF8000h
	jmp	$L007C691A
	mov	edi,edi
$L007C6A44:
	mov	eax,7FFFh
	jmp	$L007C6948
	mov	edi,edi
$L007C6A50:
	mov	eax,0FFFF8000h
	jmp	$L007C6948
	mov	edi,edi
$L007C6A5C:
	mov	eax,7FFFh
	jmp	$L007C6976
	mov	edi,edi
$L007C6A68:
	mov	eax,0FFFF8000h
	jmp	$L007C6976
	mov	edi,edi
$L007C6A74::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	shl	ch,4
	mov	bl,ch
	sub	edi,0Eh
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	jmp	$L007C6952
	nop
$L007C6A8C::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	mov	bl,ch
	sub	edi,0Ch
	sub	esi,3
	or	dl,BYTE PTR [ebx+DAT_00877B14]
	jmp	$L007C6924
	nop
$L007C6AA4::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	shl	cx,4
	mov	bl,cl
	sub	edi,0Ah
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	jmp	$L007C68F4
	db	8Dh,49h,0
$L007C6AC0::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	sub	edi,8
	sub	esi,2
	or	dl,BYTE PTR [ebx+DAT_00877B14]
	jmp	$L007C68C6
$L007C6AD8::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,4
	shl	bl,4
	sub	edi,6
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	jmp	$L007C6896
	db	8Dh,49h,0
$L007C6AFC::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,8
	sub	esi,1
	sub	edi,4
	or	dl,BYTE PTR [ebx+DAT_00877B14]
	jmp	$L007C6868
	db	8Dh,49h,0
$L007C6B20::
	xor	ecx,ecx
	mov	ecx,DWORD PTR [esi]
	shl	ecx,4
	mov	bl,cl
	sub	edi,2
	or	dl,BYTE PTR [ebx+DAT_00877C14]
	jmp	$L007C6835
	nop
; data 0x7c6b38-0x7c6b68
$L007C6B38:
	dd	$L007C69A1
	dd	$L007C6A74
	dd	$L007C6A8C
	dd	$L007C6AA4
	dd	$L007C6AC0
	dd	$L007C6AD8
	dd	$L007C6AFC
	dd	$L007C6B20
$L007C6B58:
	dd	$L007C67C3
	dd	$L007C67D8
	dd	$L007C67E8
	dd	$L007C67F8
FUN_007C6752 ENDP

_TEXT ENDS
END
