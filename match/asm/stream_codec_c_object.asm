; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C7350-0x7C7F1F (two routines and jump tables).
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

PUBLIC C FUN_007C7350
PUBLIC C FUN_007C7371
EXTERN C DAT_00879B30:DWORD
EXTERN C DAT_0087B170:WORD
EXTERN C DAT_0087BD90:BYTE
EXTERN C DAT_0087BC90:BYTE

; FUNCTION: GAMEMD 0x7C7350
; FUN_007C7350 -- Clears a small stream record at arg1 (dword +0, word +4, dword +6, word +0xA).
FUN_007C7350 PROC C arg1:DWORD
	mov	eax,arg1
	mov	WORD PTR [eax+4],0
	mov	DWORD PTR [eax],0
	mov	WORD PTR [eax+0Ah],0
	mov	DWORD PTR [eax+6],0
	ret
FUN_007C7350 ENDP

; FUNCTION: GAMEMD 0x7C7371
; FUN_007C7371 -- Table-driven sample decoder, third variant (arg1 source, arg2 destination, arg3 sample width, arg4 channel count, arg5 byte
; count, arg6 stream state record). Dispatches on width and channels, then on source alignment through the jump tables inside and
; at the end of this object; output is clamped to +-0x7FFF with the tables DAT_00879B30, DAT_0087B170 and DAT_0087BD90.
FUN_007C7371 PROC C USES esi edi ebx ecx edx, arg1:DWORD, arg2:DWORD, arg3:DWORD, arg4:DWORD, arg5:DWORD, arg6:DWORD
	mov	ebx,DWORD PTR [ebp+1Ch]
	mov	cx,WORD PTR [ebp+10h]
	mov	dx,WORD PTR [ebp+14h]
	cmp	cx,8
	jne	$L007C73A4
	cmp	dx,2
	jne	$L007C7395
	jmp	$L007C75CC
$L007C7395:
	cmp	dx,1
	jne	$L007C75CC
	jmp	$L007C75CC
$L007C73A4:
	cmp	cx,10h
	jne	$L007C75CC
	cmp	dx,2
	jne	$L007C73B9
	jmp	$L007C7788
$L007C73B9:
	cmp	dx,1
	jne	$L007C75CC
	push	ebp
	push	ebx
	xor	edx,edx
	mov	eax,DWORD PTR [ebx]
	mov	dx,WORD PTR [ebx+4]
	mov	esi,DWORD PTR [ebp+8]
	mov	edi,DWORD PTR [ebp+0Ch]
	mov	ebp,DWORD PTR [ebp+18h]
	cmp	ebp,10h
	jl	$L007C73E2
	mov	ebx,esi
	and	ebx,3
	jne	$L007C73EF
$L007C73E2::
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	or	ebp,ebp
	jmp	$L007C75A1
$L007C73EF:
	jmp	DWORD PTR [ebx*4+$L007C7778]
	mov	edi,edi
$L007C73F8::
	sub	ebp,0Ch
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C771C
	nop
$L007C7408::
	sub	ebp,8
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C76E0
	nop
$L007C7418::
	sub	ebp,4
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C76AC
	nop
$L007C7428:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C75D4
	cmp	eax,0FFFF8000h
	jl	$L007C75E0
$L007C744C:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi],ax
$L007C7455:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C75EC
	cmp	eax,0FFFF8000h
	jl	$L007C75F8
$L007C747B:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+2],ax
	shr	ecx,10h
$L007C7488:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7604
	cmp	eax,0FFFF8000h
	jl	$L007C7610
$L007C74AC:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+4],ax
$L007C74B6:
	mov	bl,cl
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C761C
	cmp	eax,0FFFF8000h
	jl	$L007C7628
$L007C74DC:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+6],ax
$L007C74E6:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7634
	cmp	eax,0FFFF8000h
	jl	$L007C7640
$L007C750A:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+8],ax
$L007C7514:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C764C
	cmp	eax,0FFFF8000h
	jl	$L007C7658
$L007C753A:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+0Ah],ax
$L007C7544:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7664
	cmp	eax,0FFFF8000h
	jl	$L007C7670
$L007C7568:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+0Ch],ax
$L007C7572:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C767C
	cmp	eax,0FFFF8000h
	jl	$L007C7688
$L007C7596:
	mov	WORD PTR [edi+0Eh],ax
	add	esi,4
	add	edi,10h
	dec	ebp
$L007C75A1:
	jle	$L007C75B2
	mov	ecx,DWORD PTR [esi]
	mov	bl,cl
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7428
$L007C75B2:
	jne	$L007C75C1
	pop	ecx
	shr	ecx,1
	and	ecx,7
	jmp	DWORD PTR [ecx*4+$L007C7758]
$L007C75C1::
	pop	ebx
	pop	ebp
	mov	DWORD PTR [ebx],eax
	mov	WORD PTR [ebx+4],dx
	mov	eax,DWORD PTR [ebp+18h]
$L007C75CC:
	ret
	nop
$L007C75D4:
	mov	eax,7FFFh
	jmp	$L007C744C
	mov	edi,edi
$L007C75E0:
	mov	eax,0FFFF8000h
	jmp	$L007C744C
	mov	edi,edi
$L007C75EC:
	mov	eax,7FFFh
	jmp	$L007C747B
	mov	edi,edi
$L007C75F8:
	mov	eax,0FFFF8000h
	jmp	$L007C747B
	mov	edi,edi
$L007C7604:
	mov	eax,7FFFh
	jmp	$L007C74AC
	mov	edi,edi
$L007C7610:
	mov	eax,0FFFF8000h
	jmp	$L007C74AC
	mov	edi,edi
$L007C761C:
	mov	eax,7FFFh
	jmp	$L007C74DC
	mov	edi,edi
$L007C7628:
	mov	eax,0FFFF8000h
	jmp	$L007C74DC
	mov	edi,edi
$L007C7634:
	mov	eax,7FFFh
	jmp	$L007C750A
	mov	edi,edi
$L007C7640:
	mov	eax,0FFFF8000h
	jmp	$L007C750A
	mov	edi,edi
$L007C764C:
	mov	eax,7FFFh
	jmp	$L007C753A
	mov	edi,edi
$L007C7658:
	mov	eax,0FFFF8000h
	jmp	$L007C753A
	mov	edi,edi
$L007C7664:
	mov	eax,7FFFh
	jmp	$L007C7568
	mov	edi,edi
$L007C7670:
	mov	eax,0FFFF8000h
	jmp	$L007C7568
	mov	edi,edi
$L007C767C:
	mov	eax,7FFFh
	jmp	$L007C7596
	mov	edi,edi
$L007C7688:
	mov	eax,0FFFF8000h
	jmp	$L007C7596
	mov	edi,edi
$L007C7694::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	shl	ch,4
	mov	bl,ch
	sub	edi,0Eh
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C7572
	nop
$L007C76AC::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	mov	bl,ch
	sub	edi,0Ch
	sub	esi,3
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7544
	nop
$L007C76C4::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	shl	cx,4
	mov	bl,cl
	sub	edi,0Ah
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C7514
	db	8Dh,49h,0
$L007C76E0::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	sub	edi,8
	sub	esi,2
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C74E6
$L007C76F8::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,4
	shl	bl,4
	sub	edi,6
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C74B6
	db	8Dh,49h,0
$L007C771C::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,8
	sub	esi,1
	sub	edi,4
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7488
	db	8Dh,49h,0
$L007C7740::
	xor	ecx,ecx
	mov	ecx,DWORD PTR [esi]
	shl	ecx,4
	mov	bl,cl
	sub	edi,2
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C7455
	nop
; data 0x7c7758-0x7c7788
$L007C7758:
	dd	$L007C75C1
	dd	$L007C7694
	dd	$L007C76AC
	dd	$L007C76C4
	dd	$L007C76E0
	dd	$L007C76F8
	dd	$L007C771C
	dd	$L007C7740
$L007C7778:
	dd	$L007C73E2
	dd	$L007C73F8
	dd	$L007C7408
	dd	$L007C7418
$L007C7788:
	push	ebp
	push	ebx
	xor	edx,edx
	mov	eax,DWORD PTR [ebx]
	mov	dx,WORD PTR [ebx+4]
	mov	esi,DWORD PTR [ebp+8]
	mov	edi,DWORD PTR [ebp+0Ch]
	mov	ebp,DWORD PTR [ebp+18h]
	shr	ebp,1
	cmp	ebp,10h
	jl	$L007C77A9
	mov	ebx,esi
	and	ebx,3
	jne	$L007C77B6
$L007C77A9::
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	or	ebp,ebp
	jmp	$L007C7969
$L007C77B6:
	jmp	DWORD PTR [ebx*4+$L007C7B3C]
	db	8Dh,49h,0
$L007C77C0::
	sub	ebp,0Ch
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C7AE0
	nop
$L007C77D0::
	sub	ebp,8
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C7AA4
	nop
$L007C77E0::
	sub	ebp,4
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C7A70
	nop
$L007C77F0:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7998
	cmp	eax,0FFFF8000h
	jl	$L007C79A4
$L007C7814:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi],ax
$L007C781D:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C79B0
	cmp	eax,0FFFF8000h
	jl	$L007C79BC
$L007C7843:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+4],ax
	shr	ecx,10h
$L007C7850:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C79C8
	cmp	eax,0FFFF8000h
	jl	$L007C79D4
$L007C7874:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+8],ax
$L007C787E:
	mov	bl,cl
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C79E0
	cmp	eax,0FFFF8000h
	jl	$L007C79EC
$L007C78A4:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+0Ch],ax
$L007C78AE:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C79F8
	cmp	eax,0FFFF8000h
	jl	$L007C7A04
$L007C78D2:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+10h],ax
$L007C78DC:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7A10
	cmp	eax,0FFFF8000h
	jl	$L007C7A1C
$L007C7902:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+14h],ax
$L007C790C:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7A28
	cmp	eax,0FFFF8000h
	jl	$L007C7A34
$L007C7930:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+18h],ax
$L007C793A:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7A40
	cmp	eax,0FFFF8000h
	jl	$L007C7A4C
$L007C795E:
	mov	WORD PTR [edi+1Ch],ax
	add	esi,4
	add	edi,20h
	dec	ebp
$L007C7969:
	jle	$L007C797A
	mov	ecx,DWORD PTR [esi]
	mov	bl,cl
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C77F0
$L007C797A:
	jne	$L007C7989
	pop	ecx
	shr	ecx,1
	and	ecx,7
	jmp	DWORD PTR [ecx*4+$L007C7B1C]
$L007C7989::
	pop	ebx
	pop	ebp
	mov	DWORD PTR [ebx],eax
	mov	WORD PTR [ebx+4],dx
	jmp	$L007C7B4C
	mov	edi,edi
$L007C7998:
	mov	eax,7FFFh
	jmp	$L007C7814
	mov	edi,edi
$L007C79A4:
	mov	eax,0FFFF8000h
	jmp	$L007C7814
	mov	edi,edi
$L007C79B0:
	mov	eax,7FFFh
	jmp	$L007C7843
	mov	edi,edi
$L007C79BC:
	mov	eax,0FFFF8000h
	jmp	$L007C7843
	mov	edi,edi
$L007C79C8:
	mov	eax,7FFFh
	jmp	$L007C7874
	mov	edi,edi
$L007C79D4:
	mov	eax,0FFFF8000h
	jmp	$L007C7874
	mov	edi,edi
$L007C79E0:
	mov	eax,7FFFh
	jmp	$L007C78A4
	mov	edi,edi
$L007C79EC:
	mov	eax,0FFFF8000h
	jmp	$L007C78A4
	mov	edi,edi
$L007C79F8:
	mov	eax,7FFFh
	jmp	$L007C78D2
	mov	edi,edi
$L007C7A04:
	mov	eax,0FFFF8000h
	jmp	$L007C78D2
	mov	edi,edi
$L007C7A10:
	mov	eax,7FFFh
	jmp	$L007C7902
	mov	edi,edi
$L007C7A1C:
	mov	eax,0FFFF8000h
	jmp	$L007C7902
	mov	edi,edi
$L007C7A28:
	mov	eax,7FFFh
	jmp	$L007C7930
	mov	edi,edi
$L007C7A34:
	mov	eax,0FFFF8000h
	jmp	$L007C7930
	mov	edi,edi
$L007C7A40:
	mov	eax,7FFFh
	jmp	$L007C795E
	mov	edi,edi
$L007C7A4C:
	mov	eax,0FFFF8000h
	jmp	$L007C795E
	mov	edi,edi
$L007C7A58::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	shl	ch,4
	mov	bl,ch
	sub	edi,1Ch
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C793A
	nop
$L007C7A70::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	mov	bl,ch
	sub	edi,18h
	sub	esi,3
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C790C
	nop
$L007C7A88::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	shl	cx,4
	mov	bl,cl
	sub	edi,14h
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C78DC
	db	8Dh,49h,0
$L007C7AA4::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	sub	edi,10h
	sub	esi,2
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C78AE
$L007C7ABC::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,4
	shl	bl,4
	sub	edi,0Ch
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C787E
	db	8Dh,49h,0
$L007C7AE0::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,8
	sub	esi,1
	sub	edi,8
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7850
	db	8Dh,49h,0
$L007C7B04::
	xor	ecx,ecx
	mov	ecx,DWORD PTR [esi]
	shl	ecx,4
	mov	bl,cl
	sub	edi,4
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C781D
	nop
; data 0x7c7b1c-0x7c7b4c
$L007C7B1C:
	dd	$L007C7989
	dd	$L007C7A58
	dd	$L007C7A70
	dd	$L007C7A88
	dd	$L007C7AA4
	dd	$L007C7ABC
	dd	$L007C7AE0
	dd	$L007C7B04
$L007C7B3C:
	dd	$L007C77A9
	dd	$L007C77C0
	dd	$L007C77D0
	dd	$L007C77E0
$L007C7B4C:
	push	ebp
	push	ebx
	mov	esi,DWORD PTR [ebp+8]
	mov	edi,DWORD PTR [ebp+0Ch]
	add	edi,2
	mov	edx,DWORD PTR [ebp+18h]
	shr	edx,3
	add	esi,edx
	xor	edx,edx
	mov	eax,DWORD PTR [ebx+6]
	mov	dx,WORD PTR [ebx+0Ah]
	mov	ebp,DWORD PTR [ebp+18h]
	shr	ebp,1
	cmp	ebp,10h
	jl	$L007C7B79
	mov	ebx,esi
	and	ebx,3
	jne	$L007C7B86
$L007C7B79::
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	or	ebp,ebp
	jmp	$L007C7D39
$L007C7B86:
	jmp	DWORD PTR [ebx*4+$L007C7F10]
	db	8Dh,49h,0
$L007C7B90::
	sub	ebp,0Ch
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C7EB4
	nop
$L007C7BA0::
	sub	ebp,8
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C7E78
	nop
$L007C7BB0::
	sub	ebp,4
	push	ebp
	shr	ebp,4
	xor	ebx,ebx
	inc	ebp
	jmp	$L007C7E44
	nop
$L007C7BC0:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7D6C
	cmp	eax,0FFFF8000h
	jl	$L007C7D78
$L007C7BE4:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi],ax
$L007C7BED:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7D84
	cmp	eax,0FFFF8000h
	jl	$L007C7D90
$L007C7C13:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+4],ax
	shr	ecx,10h
$L007C7C20:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7D9C
	cmp	eax,0FFFF8000h
	jl	$L007C7DA8
$L007C7C44:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+8],ax
$L007C7C4E:
	mov	bl,cl
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7DB4
	cmp	eax,0FFFF8000h
	jl	$L007C7DC0
$L007C7C74:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+0Ch],ax
$L007C7C7E:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7DCC
	cmp	eax,0FFFF8000h
	jl	$L007C7DD8
$L007C7CA2:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+10h],ax
$L007C7CAC:
	mov	bl,ch
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7DE4
	cmp	eax,0FFFF8000h
	jl	$L007C7DF0
$L007C7CD2:
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	mov	WORD PTR [edi+14h],ax
$L007C7CDC:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7DFC
	cmp	eax,0FFFF8000h
	jl	$L007C7E08
$L007C7D00:
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	mov	WORD PTR [edi+18h],ax
$L007C7D0A:
	add	eax,DWORD PTR [edx*2+DAT_00879B30]
	mov	dx,WORD PTR [edx+DAT_0087B170]
	cmp	eax,7FFFh
	jg	$L007C7E14
	cmp	eax,0FFFF8000h
	jl	$L007C7E20
$L007C7D2E:
	mov	WORD PTR [edi+1Ch],ax
	add	esi,4
	add	edi,20h
	dec	ebp
$L007C7D39:
	jle	$L007C7D4A
	mov	ecx,DWORD PTR [esi]
	mov	bl,cl
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7BC0
$L007C7D4A:
	jne	$L007C7D59
	pop	ecx
	shr	ecx,1
	and	ecx,7
	jmp	DWORD PTR [ecx*4+$L007C7EF0]
$L007C7D59::
	pop	ebx
	pop	ebp
	mov	DWORD PTR [ebx+6],eax
	mov	WORD PTR [ebx+0Ah],dx
	mov	eax,DWORD PTR [ebp+18h]
	jmp	$L007C75CC
	mov	edi,edi
$L007C7D6C:
	mov	eax,7FFFh
	jmp	$L007C7BE4
	mov	edi,edi
$L007C7D78:
	mov	eax,0FFFF8000h
	jmp	$L007C7BE4
	mov	edi,edi
$L007C7D84:
	mov	eax,7FFFh
	jmp	$L007C7C13
	mov	edi,edi
$L007C7D90:
	mov	eax,0FFFF8000h
	jmp	$L007C7C13
	mov	edi,edi
$L007C7D9C:
	mov	eax,7FFFh
	jmp	$L007C7C44
	mov	edi,edi
$L007C7DA8:
	mov	eax,0FFFF8000h
	jmp	$L007C7C44
	mov	edi,edi
$L007C7DB4:
	mov	eax,7FFFh
	jmp	$L007C7C74
	mov	edi,edi
$L007C7DC0:
	mov	eax,0FFFF8000h
	jmp	$L007C7C74
	mov	edi,edi
$L007C7DCC:
	mov	eax,7FFFh
	jmp	$L007C7CA2
	mov	edi,edi
$L007C7DD8:
	mov	eax,0FFFF8000h
	jmp	$L007C7CA2
	mov	edi,edi
$L007C7DE4:
	mov	eax,7FFFh
	jmp	$L007C7CD2
	mov	edi,edi
$L007C7DF0:
	mov	eax,0FFFF8000h
	jmp	$L007C7CD2
	mov	edi,edi
$L007C7DFC:
	mov	eax,7FFFh
	jmp	$L007C7D00
	mov	edi,edi
$L007C7E08:
	mov	eax,0FFFF8000h
	jmp	$L007C7D00
	mov	edi,edi
$L007C7E14:
	mov	eax,7FFFh
	jmp	$L007C7D2E
	mov	edi,edi
$L007C7E20:
	mov	eax,0FFFF8000h
	jmp	$L007C7D2E
	mov	edi,edi
$L007C7E2C::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	shl	ch,4
	mov	bl,ch
	sub	edi,1Ch
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C7D0A
	nop
$L007C7E44::
	xor	ecx,ecx
	mov	ch,BYTE PTR [esi]
	mov	bl,ch
	sub	edi,18h
	sub	esi,3
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7CDC
	nop
$L007C7E5C::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	shl	cx,4
	mov	bl,cl
	sub	edi,14h
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C7CAC
	db	8Dh,49h,0
$L007C7E78::
	xor	ecx,ecx
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	sub	edi,10h
	sub	esi,2
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7C7E
$L007C7E90::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,4
	shl	bl,4
	sub	edi,0Ch
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C7C4E
	db	8Dh,49h,0
$L007C7EB4::
	xor	ecx,ecx
	mov	cl,BYTE PTR [esi+2]
	shl	ecx,10h
	mov	cx,WORD PTR [esi]
	mov	bl,cl
	shr	ecx,8
	sub	esi,1
	sub	edi,8
	or	dl,BYTE PTR [ebx+DAT_0087BC90]
	jmp	$L007C7C20
	db	8Dh,49h,0
$L007C7ED8::
	xor	ecx,ecx
	mov	ecx,DWORD PTR [esi]
	shl	ecx,4
	mov	bl,cl
	sub	edi,4
	or	dl,BYTE PTR [ebx+DAT_0087BD90]
	jmp	$L007C7BED
	nop
; data 0x7c7ef0-0x7c7f20
$L007C7EF0:
	dd	$L007C7D59
	dd	$L007C7E2C
	dd	$L007C7E44
	dd	$L007C7E5C
	dd	$L007C7E78
	dd	$L007C7E90
	dd	$L007C7EB4
	dd	$L007C7ED8
$L007C7F10:
	dd	$L007C7B79
	dd	$L007C7B90
	dd	$L007C7BA0
	dd	$L007C7BB0
FUN_007C7371 ENDP

_TEXT ENDS
END
