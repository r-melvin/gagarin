; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C60C0-0x7C6262 (two routines).
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

PUBLIC C FUN_007C60C0
PUBLIC C FUN_007C61CF

; FUNCTION: GAMEMD 0x7C60C0
; FUN_007C60C0 -- Depth-tested span draw into a 16-bit surface. arg1 points at a context record that the routine loads into EBP (its fields
; are addressed through EBP); a pixel is written when its 16-bit depth compares
; below the stored depth. First variant.
FUN_007C60C0 PROC C USES ebx esi edi ecx ebp, arg1:DWORD
	mov	ebp,arg1
	mov	eax,DWORD PTR [ebp+8Ch]
	or	eax,DWORD PTR [ebp+88h]
	mov	DWORD PTR [ebp+74h],eax
	xor	ch,ch
	mov	eax,DWORD PTR [ebp+54h]
	mov	DWORD PTR [ebp+6Ch],eax
$L007C60E2:
	xor	cl,cl
	mov	esi,DWORD PTR [ebp+54h]
$L007C60E7:
	mov	al,BYTE PTR [esi]
	inc	esi
	test	al,al
	je	$L007C612D
	xor	ebx,ebx
	mov	edi,DWORD PTR [ebp+50h]
	mov	edx,DWORD PTR [ebp+40h]
	mov	bl,BYTE PTR [edi]
	add	ebx,DWORD PTR [ebp+10h]
	xor	eax,eax
	cmp	bx,WORD PTR [edx]
	jae	$L007C6127
	mov	WORD PTR [edx],bx
	mov	ebx,DWORD PTR [ebp+44h]
	mov	edx,DWORD PTR [ebp+4Ch]
	movzx	eax,WORD PTR [ebx]
	mov	ebx,DWORD PTR [ebp+90h]
	mov	ax,WORD PTR [ebx+eax*2]
	mov	al,BYTE PTR [edx]
	mov	edx,DWORD PTR [ebp+58h]
	mov	edi,DWORD PTR [ebp+48h]
	mov	ax,WORD PTR [edx+eax*2]
	mov	WORD PTR [edi],ax
$L007C6127:
	inc	DWORD PTR [ebp+50h]
	inc	DWORD PTR [ebp+4Ch]
$L007C612D:
	inc	cl
	add	DWORD PTR [ebp+48h],2
	add	DWORD PTR [ebp+40h],2
	add	DWORD PTR [ebp+44h],2
	cmp	cl,BYTE PTR [ebp+0]
	jl	$L007C60E7
	mov	eax,DWORD PTR [ebp+1Ch]
	add	DWORD PTR [ebp+48h],eax
	mov	eax,DWORD PTR [ebp+14h]
	add	DWORD PTR [ebp+40h],eax
	add	DWORD PTR [ebp+40h],eax
	mov	eax,DWORD PTR [ebp+18h]
	add	DWORD PTR [ebp+44h],eax
	add	DWORD PTR [ebp+44h],eax
	mov	eax,DWORD PTR [ebp+6Ch]
	add	eax,DWORD PTR [ebp+0]
	mov	DWORD PTR [ebp+54h],eax
	mov	DWORD PTR [ebp+6Ch],eax
	cmp	DWORD PTR [ebp+74h],0
	jne	$L007C617C
	inc	ch
	cmp	ch,BYTE PTR [ebp+4]
	jl	$L007C60E2
	ret
$L007C617C:
	movzx	eax,ch
	add	eax,DWORD PTR [ebp+0Ch]
	shl	eax,4
	lea	ebx,[eax+eax*2]
	add	ebx,DWORD PTR [ebp+8]
	mov	edx,ebx
	cmp	DWORD PTR [ebp+8Ch],0
	je	$L007C61A5
	mov	esi,DWORD PTR [ebp+60h]
	add	ebx,DWORD PTR [ebp+0]
	mov	eax,DWORD PTR [esi+ebx*4]
	add	DWORD PTR [ebp+4Ch],eax
	add	DWORD PTR [ebp+50h],eax
$L007C61A5:
	cmp	DWORD PTR [ebp+88h],0
	je	$L007C61BD
	mov	esi,DWORD PTR [ebp+5Ch]
	add	edx,DWORD PTR [ebp+0]
	mov	eax,DWORD PTR [esi+edx*4]
	add	DWORD PTR [ebp+4Ch],eax
	add	DWORD PTR [ebp+50h],eax
$L007C61BD:
	inc	ch
	cmp	ch,BYTE PTR [ebp+4]
	jl	$L007C60E2
	ret
FUN_007C60C0 ENDP

; FUNCTION: GAMEMD 0x7C61CF
; FUN_007C61CF -- Depth-tested span draw into a 16-bit surface (second variant of the routine above, context record in arg1 loaded into EBP;
; called from the isometric tile draw).
FUN_007C61CF PROC C USES ebp, arg1:DWORD
	mov	ebp,arg1
	xor	ch,ch
	mov	esi,DWORD PTR [ebp+4Ch]
$L007C61DB:
	xor	cl,cl
$L007C61DD:
	movzx	eax,BYTE PTR [esi]
	inc	esi
	test	al,al
	je	$L007C621E
	xor	ebx,ebx
	mov	edi,DWORD PTR [ebp+50h]
	mov	edx,DWORD PTR [ebp+40h]
	mov	bl,BYTE PTR [edi]
	add	ebx,DWORD PTR [ebp+10h]
	and	eax,0FFh
	cmp	bx,WORD PTR [edx]
	jae	$L007C621E
	mov	WORD PTR [edx],bx
	mov	ebx,DWORD PTR [ebp+44h]
	mov	edi,DWORD PTR [ebp+48h]
	movzx	edx,WORD PTR [ebx]
	mov	ebx,DWORD PTR [ebp+90h]
	mov	dx,WORD PTR [ebx+edx*2]
	mov	dl,al
	mov	eax,DWORD PTR [ebp+58h]
	mov	ax,WORD PTR [eax+edx*2]
	mov	WORD PTR [edi],ax
$L007C621E:
	inc	cl
	inc	DWORD PTR [ebp+50h]
	add	DWORD PTR [ebp+48h],2
	add	DWORD PTR [ebp+40h],2
	add	DWORD PTR [ebp+44h],2
	cmp	cl,BYTE PTR [ebp+0]
	jl	$L007C61DD
	mov	eax,DWORD PTR [ebp+1Ch]
	add	DWORD PTR [ebp+48h],eax
	mov	eax,DWORD PTR [ebp+14h]
	add	DWORD PTR [ebp+40h],eax
	add	DWORD PTR [ebp+40h],eax
	mov	eax,DWORD PTR [ebp+18h]
	add	DWORD PTR [ebp+44h],eax
	add	DWORD PTR [ebp+44h],eax
	mov	eax,DWORD PTR [ebp+20h]
	add	esi,DWORD PTR [ebp+20h]
	add	DWORD PTR [ebp+50h],eax
	inc	ch
	cmp	ch,BYTE PTR [ebp+4]
	jl	$L007C61DB
	ret
FUN_007C61CF ENDP

_TEXT ENDS
END
