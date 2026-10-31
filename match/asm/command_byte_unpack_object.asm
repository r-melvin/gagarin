; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C8110-0x7C8361 (two routines).
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

PUBLIC C FUN_007C8110
PUBLIC C FUN_007C81DB

; FUNCTION: GAMEMD 0x7C8110
; FUN_007C8110 -- Command-byte run/copy decompressor. arg1 source, arg2 destination, arg3 output size; returns the bytes written. Command 0x80
; ends the stream; 0x00..0x7F copy from earlier output at a one-byte distance, 0x81..0xBF are literal runs, 0xC0..0xFD copy from an
; absolute output offset, 0xFE is a fill and 0xFF a long absolute copy.
FUN_007C8110 PROC C USES ebx ecx edx esi edi, arg1:DWORD, arg2:DWORD, arg3:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD
	mov	esi,arg1
	mov	edi,arg2
	mov	edx,arg3
	mov	loc1,edi
	add	edx,edi
	mov	loc3,edx
	cld
	mov	ebx,esi
$L007C812F:
	mov	eax,loc3
	sub	eax,edi
	je	$L007C8181
	mov	loc2,eax
	mov	esi,ebx
	lodsb
	or	al,al
	js	$L007C8166
	mov	ah,al
	and	ah,0Fh
	sub	ecx,ecx
	mov	ch,al
	shr	ch,4
	mov	cl,ch
	xor	ch,ch
	add	ecx,3
	cmp	ecx,loc2
	jbe	$L007C815B
	mov	ecx,loc2
$L007C815B:
	lodsb
	mov	ebx,esi
	mov	esi,edi
	sub	esi,eax
	rep movsb
	jmp	$L007C812F
$L007C8166:
	test	al,40h
	jne	$L007C8188
	cmp	al,80h
	je	$L007C8181
	mov	cl,al
	and	ecx,3Fh
	cmp	ecx,loc2
	jbe	$L007C817B
	mov	ecx,loc2
$L007C817B:
	rep movsb
	mov	ebx,esi
	jmp	$L007C812F
$L007C8181:
	mov	eax,edi
	sub	eax,loc1
	jmp	$L007C81CD
$L007C8188:
	mov	cl,al
	and	ecx,3Fh
	add	ecx,3
	cmp	al,0FEh
	jne	$L007C81AB
	sub	eax,eax
	lodsw
	mov	ecx,eax
	sub	eax,eax
	lodsb
	mov	ebx,esi
	cmp	ecx,loc2
	jbe	$L007C81A7
	mov	ecx,loc2
$L007C81A7:
	rep stosb
	jmp	$L007C812F
$L007C81AB:
	cmp	al,0FFh
	jne	$L007C81B5
	sub	eax,eax
	lodsw
	mov	ecx,eax
$L007C81B5:
	lodsw
	mov	ebx,esi
	add	eax,loc1
	mov	esi,eax
	cmp	ecx,loc2
	jbe	$L007C81C6
	mov	ecx,loc2
$L007C81C6:
	rep movsb
	jmp	$L007C812F
$L007C81CD:
	mov	eax,edi
	mov	ebx,arg2
	sub	eax,ebx
	ret
FUN_007C8110 ENDP

; FUNCTION: GAMEMD 0x7C81DB
; FUN_007C81DB -- Command-byte run/copy decompressor, second variant (called from the movie loader): same command set as the routine at
; 0x7C8110, with an empty-input check on the first source byte and an overrun guard on the remaining count.
FUN_007C81DB PROC C USES ebx ecx edx edi esi, arg1:DWORD, arg2:DWORD, arg3:DWORD
	LOCAL	loc1:DWORD, loc2:DWORD, loc3:DWORD, loc4:DWORD, loc5:DWORD
	mov	edi,arg2
	mov	esi,arg1
	mov	edx,arg3
	mov	al,BYTE PTR [esi]
	or	al,al
	je	$L007C82AF
	mov	loc1,edi
	add	edx,edi
	mov	loc3,edx
	cld
	mov	ebx,esi
$L007C8204:
	mov	eax,loc3
	sub	eax,edi
	je	$L007C8257
	js	$L007C8256
	mov	loc2,eax
	mov	esi,ebx
	sub	eax,eax
	lodsb
	or	al,al
	js	$L007C823B
	mov	ah,al
	and	ah,0Fh
	sub	ecx,ecx
	mov	cl,al
	shr	cl,4
	add	ecx,3
	cmp	ecx,loc2
	jbe	$L007C8230
	mov	ecx,loc2
$L007C8230:
	lodsb
	mov	ebx,esi
	mov	esi,edi
	sub	esi,eax
	rep movsb
	jmp	$L007C8204
$L007C823B:
	test	al,40h
	jne	$L007C825E
	cmp	al,80h
	je	$L007C8257
	mov	cl,al
	and	ecx,3Fh
	cmp	ecx,loc2
	jbe	$L007C8250
	mov	ecx,loc2
$L007C8250:
	rep movsb
	mov	ebx,esi
	jmp	$L007C8204
$L007C8256:
	nop
$L007C8257:
	mov	eax,edi
	sub	eax,loc1
	jmp	$L007C82A3
$L007C825E:
	mov	cl,al
	and	ecx,3Fh
	add	ecx,3
	cmp	al,0FEh
	jne	$L007C8281
	sub	eax,eax
	lodsw
	mov	ecx,eax
	sub	eax,eax
	lodsb
	mov	ebx,esi
	cmp	ecx,loc2
	jbe	$L007C827D
	mov	ecx,loc2
$L007C827D:
	rep stosb
	jmp	$L007C8204
$L007C8281:
	cmp	al,0FFh
	jne	$L007C828B
	sub	eax,eax
	lodsw
	mov	ecx,eax
$L007C828B:
	lodsw
	mov	ebx,esi
	add	eax,loc1
	mov	esi,eax
	cmp	ecx,loc2
	jbe	$L007C829C
	mov	ecx,loc2
$L007C829C:
	rep movsb
	jmp	$L007C8204
$L007C82A3:
	mov	eax,edi
	mov	ebx,arg2
	sub	eax,ebx
	jmp	$L007C835B
$L007C82AF:
	lodsb
	mov	loc1,edi
	add	edx,edi
	mov	loc3,edx
	cld
	mov	ebx,esi
$L007C82BB:
	mov	eax,loc3
	sub	eax,edi
	je	$L007C830B
	mov	loc2,eax
	mov	esi,ebx
	sub	eax,eax
	lodsb
	or	al,al
	js	$L007C82F0
	mov	ah,al
	and	ah,0Fh
	sub	ecx,ecx
	mov	cl,al
	shr	cl,4
	add	ecx,3
	cmp	ecx,loc2
	jbe	$L007C82E5
	mov	ecx,loc2
$L007C82E5:
	lodsb
	mov	ebx,esi
	mov	esi,edi
	sub	esi,eax
	rep movsb
	jmp	$L007C82BB
$L007C82F0:
	test	al,40h
	jne	$L007C8312
	cmp	al,80h
	je	$L007C830B
	mov	cl,al
	and	ecx,3Fh
	cmp	ecx,loc2
	jbe	$L007C8305
	mov	ecx,loc2
$L007C8305:
	rep movsb
	mov	ebx,esi
	jmp	$L007C82BB
$L007C830B:
	mov	eax,edi
	sub	eax,loc1
	jmp	$L007C82A3
$L007C8312:
	mov	cl,al
	and	ecx,3Fh
	add	ecx,3
	cmp	al,0FEh
	jne	$L007C8335
	sub	eax,eax
	lodsw
	mov	ecx,eax
	sub	eax,eax
	lodsb
	mov	ebx,esi
	cmp	ecx,loc2
	jbe	$L007C8331
	mov	ecx,loc2
$L007C8331:
	rep stosb
	jmp	$L007C82BB
$L007C8335:
	cmp	al,0FFh
	jne	$L007C833F
	sub	eax,eax
	lodsw
	mov	ecx,eax
$L007C833F:
	lodsw
	mov	ebx,esi
	mov	esi,edi
	sub	esi,eax
	cmp	ecx,loc2
	jbe	$L007C834F
	mov	ecx,loc2
$L007C834F:
	rep movsb
	jmp	$L007C82BB
	jmp	$L007C82A3
$L007C835B:
	ret
FUN_007C81DB ENDP

_TEXT ENDS
END
