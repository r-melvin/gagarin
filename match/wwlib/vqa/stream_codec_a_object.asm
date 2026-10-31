; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C6270-0x7C6612 (two routines).
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

PUBLIC C FUN_007C6270
PUBLIC C FUN_007C62AC
EXTERN C DAT_008758C4:WORD
EXTERN C DAT_008758E4:WORD

; FUNCTION: GAMEMD 0x7C6270
; FUN_007C6270 -- Clears a two-channel stream record at arg1: sample accumulators zeroed, step indices set to 7.
FUN_007C6270 PROC C arg1:DWORD
	mov	eax,arg1
	mov	WORD PTR [eax+22h],0
	mov	WORD PTR [eax+20h],7
	mov	DWORD PTR [eax+14h],0
	mov	DWORD PTR [eax+10h],0
	mov	WORD PTR [eax+36h],0
	mov	WORD PTR [eax+34h],7
	mov	DWORD PTR [eax+28h],0
	mov	DWORD PTR [eax+24h],0
	ret
FUN_007C6270 ENDP

; FUNCTION: GAMEMD 0x7C62AC
; FUN_007C62AC -- Table-driven 4-bit step-index sample decoder. arg1 stream record (source pointer +0, destination pointer +4, sample width +0x38,
; channel count +0x3A, per-channel state), arg2 byte count. Output is clamped to +-0x7FFF using the tables DAT_00879B30,
; DAT_0087B170, DAT_0087BC90 and DAT_0087BD90.
FUN_007C62AC PROC C USES esi edi ebx ecx edx, arg1:DWORD, arg2:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD
	mov	ebx,arg1
	mov	eax,arg2
	mov	loc1,eax
	mov	DWORD PTR [ebx+10h],0
	mov	DWORD PTR [ebx+24h],0
	cmp	WORD PTR [ebx+38h],10h
	jne	$L007C62D7
	shr	eax,1
$L007C62D7:
	mov	loc2,eax
	mov	esi,DWORD PTR [ebx]
	mov	edi,DWORD PTR [ebx+4]
	cmp	WORD PTR [ebx+3Ah],2
	je	$L007C63EA
$L007C62EA:
	test	DWORD PTR [ebx+10h],1
	je	$L007C6305
	xor	eax,eax
	mov	ax,WORD PTR [ebx+1Ch]
	shr	eax,4
	and	eax,0Fh
	mov	WORD PTR [ebx+1Eh],ax
	jmp	$L007C6315
$L007C6305:
	xor	eax,eax
	mov	al,BYTE PTR [esi]
	mov	WORD PTR [ebx+1Ch],ax
	inc	esi
	and	eax,0Fh
	mov	WORD PTR [ebx+1Eh],ax
$L007C6315:
	mov	DWORD PTR [ebx+18h],0
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+20h]
	test	eax,4
	je	$L007C632C
	add	DWORD PTR [ebx+18h],ecx
$L007C632C:
	test	eax,2
	je	$L007C633A
	mov	edx,ecx
	shr	edx,1
	add	DWORD PTR [ebx+18h],edx
$L007C633A:
	test	eax,1
	je	$L007C6349
	mov	edx,ecx
	shr	edx,2
	add	DWORD PTR [ebx+18h],edx
$L007C6349:
	mov	edx,ecx
	shr	edx,3
	add	DWORD PTR [ebx+18h],edx
	test	eax,8
	je	$L007C635B
	neg	DWORD PTR [ebx+18h]
$L007C635B:
	mov	eax,DWORD PTR [ebx+14h]
	add	eax,DWORD PTR [ebx+18h]
	cmp	eax,7FFFh
	jl	$L007C636D
	mov	eax,7FFFh
$L007C636D:
	cmp	eax,0FFFF8000h
	jg	$L007C6379
	mov	eax,0FFFF8000h
$L007C6379:
	mov	DWORD PTR [ebx+14h],eax
	cmp	WORD PTR [ebx+38h],10h
	jne	$L007C638B
	mov	WORD PTR [edi],ax
	add	edi,2
	jmp	$L007C6391
$L007C638B:
	xor	ah,80h
	mov	BYTE PTR [edi],ah
	inc	edi
$L007C6391:
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+1Eh]
	xor	eax,eax
	shl	ecx,1
	mov	ax,WORD PTR [ecx+DAT_008758C4]
	add	WORD PTR [ebx+22h],ax
	cmp	WORD PTR [ebx+22h],8000h
	jb	$L007C63B6
	mov	WORD PTR [ebx+22h],0
	jmp	$L007C63C3
$L007C63B6:
	cmp	WORD PTR [ebx+22h],58h
	jbe	$L007C63C3
	mov	WORD PTR [ebx+22h],58h
$L007C63C3:
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+22h]
	xor	eax,eax
	shl	ecx,1
	mov	ax,WORD PTR [ecx+DAT_008758E4]
	add	DWORD PTR [ebx+10h],1
	mov	WORD PTR [ebx+20h],ax
	dec	loc2
	jne	$L007C62EA
	jmp	$L007C6609
$L007C63EA:
	test	DWORD PTR [ebx+10h],1
	je	$L007C6405
	xor	eax,eax
	mov	ax,WORD PTR [ebx+1Ch]
	shr	eax,4
	and	eax,0Fh
	mov	WORD PTR [ebx+1Eh],ax
	jmp	$L007C6417
$L007C6405:
	xor	eax,eax
	mov	al,BYTE PTR [esi]
	mov	WORD PTR [ebx+1Ch],ax
	add	esi,2
	and	eax,0Fh
	mov	WORD PTR [ebx+1Eh],ax
$L007C6417:
	mov	DWORD PTR [ebx+18h],0
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+20h]
	test	eax,4
	je	$L007C642E
	add	DWORD PTR [ebx+18h],ecx
$L007C642E:
	test	eax,2
	je	$L007C643C
	mov	edx,ecx
	shr	edx,1
	add	DWORD PTR [ebx+18h],edx
$L007C643C:
	test	eax,1
	je	$L007C644B
	mov	edx,ecx
	shr	edx,2
	add	DWORD PTR [ebx+18h],edx
$L007C644B:
	mov	edx,ecx
	shr	edx,3
	add	DWORD PTR [ebx+18h],edx
	test	eax,8
	je	$L007C645D
	neg	DWORD PTR [ebx+18h]
$L007C645D:
	mov	eax,DWORD PTR [ebx+14h]
	add	eax,DWORD PTR [ebx+18h]
	cmp	eax,7FFFh
	jl	$L007C646F
	mov	eax,7FFFh
$L007C646F:
	cmp	eax,0FFFF8000h
	jg	$L007C647B
	mov	eax,0FFFF8000h
$L007C647B:
	mov	DWORD PTR [ebx+14h],eax
	cmp	WORD PTR [ebx+38h],10h
	jne	$L007C648D
	mov	WORD PTR [edi],ax
	add	edi,4
	jmp	$L007C6495
$L007C648D:
	xor	ah,80h
	mov	BYTE PTR [edi],ah
	add	edi,2
$L007C6495:
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+1Eh]
	xor	eax,eax
	shl	ecx,1
	mov	ax,WORD PTR [ecx+DAT_008758C4]
	add	WORD PTR [ebx+22h],ax
	cmp	WORD PTR [ebx+22h],8000h
	jb	$L007C64BA
	mov	WORD PTR [ebx+22h],0
	jmp	$L007C64C7
$L007C64BA:
	cmp	WORD PTR [ebx+22h],58h
	jbe	$L007C64C7
	mov	WORD PTR [ebx+22h],58h
$L007C64C7:
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+22h]
	xor	eax,eax
	shl	ecx,1
	mov	ax,WORD PTR [ecx+DAT_008758E4]
	add	DWORD PTR [ebx+10h],1
	mov	WORD PTR [ebx+20h],ax
	sub	loc2,2
	jne	$L007C63EA
	mov	eax,arg2
	mov	loc1,eax
	mov	esi,DWORD PTR [ebx]
	mov	edi,DWORD PTR [ebx+4]
	inc	esi
	inc	edi
	cmp	WORD PTR [ebx+38h],10h
	je	$L007C6503
	mov	loc2,eax
	jmp	$L007C6509
$L007C6503:
	shr	eax,1
	inc	edi
	mov	loc2,eax
$L007C6509:
	test	DWORD PTR [ebx+24h],1
	je	$L007C6524
	xor	eax,eax
	mov	ax,WORD PTR [ebx+30h]
	shr	eax,4
	and	eax,0Fh
	mov	WORD PTR [ebx+32h],ax
	jmp	$L007C6536
$L007C6524:
	xor	eax,eax
	mov	al,BYTE PTR [esi]
	mov	WORD PTR [ebx+30h],ax
	add	esi,2
	and	eax,0Fh
	mov	WORD PTR [ebx+32h],ax
$L007C6536:
	mov	DWORD PTR [ebx+2Ch],0
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+34h]
	test	eax,4
	je	$L007C654D
	add	DWORD PTR [ebx+2Ch],ecx
$L007C654D:
	test	eax,2
	je	$L007C655B
	mov	edx,ecx
	shr	edx,1
	add	DWORD PTR [ebx+2Ch],edx
$L007C655B:
	test	eax,1
	je	$L007C656A
	mov	edx,ecx
	shr	edx,2
	add	DWORD PTR [ebx+2Ch],edx
$L007C656A:
	mov	edx,ecx
	shr	edx,3
	add	DWORD PTR [ebx+2Ch],edx
	test	eax,8
	je	$L007C657C
	neg	DWORD PTR [ebx+2Ch]
$L007C657C:
	mov	eax,DWORD PTR [ebx+28h]
	add	eax,DWORD PTR [ebx+2Ch]
	cmp	eax,7FFFh
	jl	$L007C658E
	mov	eax,7FFFh
$L007C658E:
	cmp	eax,0FFFF8000h
	jg	$L007C659A
	mov	eax,0FFFF8000h
$L007C659A:
	mov	DWORD PTR [ebx+28h],eax
	cmp	WORD PTR [ebx+38h],10h
	jne	$L007C65AC
	mov	WORD PTR [edi],ax
	add	edi,4
	jmp	$L007C65B4
$L007C65AC:
	xor	ah,80h
	mov	BYTE PTR [edi],ah
	add	edi,2
$L007C65B4:
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+32h]
	xor	eax,eax
	shl	ecx,1
	mov	ax,WORD PTR [ecx+DAT_008758C4]
	add	WORD PTR [ebx+36h],ax
	cmp	WORD PTR [ebx+36h],8000h
	jb	$L007C65D9
	mov	WORD PTR [ebx+36h],0
	jmp	$L007C65E6
$L007C65D9:
	cmp	WORD PTR [ebx+36h],58h
	jbe	$L007C65E6
	mov	WORD PTR [ebx+36h],58h
$L007C65E6:
	xor	ecx,ecx
	mov	cx,WORD PTR [ebx+36h]
	xor	eax,eax
	shl	ecx,1
	mov	ax,WORD PTR [ecx+DAT_008758E4]
	add	DWORD PTR [ebx+24h],1
	mov	WORD PTR [ebx+34h],ax
	sub	loc2,2
	jne	$L007C6509
$L007C6609:
	mov	eax,loc1
	ret
FUN_007C62AC ENDP

_TEXT ENDS
END
