; SPDX-License-Identifier: GPL-3.0-or-later
; Provenance: own-binary-via-Ghidra
;   Hand-written assembly object, recovered as MASM source and assembled by the toolchain's
;   ml.exe 6.15 (scripts/vc6/vc6asm.sh), not C++ (AGENTS.md "Hand-written assembly").
;   One original object: 0x7C5F3D-0x7C60B7 (four byte-packed routines; the object is followed
;   by 0xCC padding to the next 16-byte boundary at 0x7C60C0). Evidence the code was not
;   compiled C: every routine opens with the PROC C frame shape (push ebp / mov ebp,esp,
;   add esp,-N for LOCALs, USES pushes after the locals, pop-leave-ret epilogue) that
;   VC6 never emits, the routines are byte-packed with no alignment between them, and the
;   object is surrounded by CC padding. The retail range makes no import calls.
;   Every instruction, displacement, constant and data address below was read off the user's
;   retail gamemd.exe v1.001 at the address in each annotation; the routines are CPU feature
;   probes (CPUID presence via the AC and ID EFLAGS bits, CMOV support, RDTSC, 386/486/586
;   class), described in the comments. All names are placeholders: the binary attests none.
;   Operand order follows MASM (test dl,cl puts the first operand in the reg field).
;
;   GLOBAL:   GAMEMD 0x84E860   DAT_0084E860   cmov usable flag, byte
;   GLOBAL:   GAMEMD 0x84E861   DAT_0084E861   cmov detection ran flag, byte
;   GLOBAL:   GAMEMD 0x84E862   DAT_0084E862   MMX present flag, byte
;   GLOBAL:   GAMEMD 0x84E863   DAT_0084E863   CPU family/class number, byte
;   GLOBAL:   GAMEMD 0x84E864   DAT_0084E864   CPU stepping nibble, byte
;   GLOBAL:   GAMEMD 0x84E865   DAT_0084E865   CPUID vendor string (ebx, edx, ecx), 12 bytes
;   GLOBAL:   GAMEMD 0x84E871   DAT_0084E871   dword set to 0x20 when CPUID is present

; Not `.MODEL FLAT` + `.CODE`: that segment is 16-byte aligned, and this object was
; byte-packed against its neighbours (it starts at 0x7C5F3D), so the segment is declared BYTE.
.586
OPTION LANGUAGE:C
ASSUME CS:FLAT, DS:FLAT, ES:FLAT, SS:FLAT
_TEXT SEGMENT BYTE PUBLIC FLAT 'CODE'

PUBLIC C FUN_007C5F3D
PUBLIC C FUN_007C5FFF
PUBLIC C FUN_007C6064
PUBLIC C FUN_007C6072
EXTERN C DAT_0084E860:BYTE
EXTERN C DAT_0084E861:BYTE
EXTERN C DAT_0084E862:BYTE
EXTERN C DAT_0084E863:BYTE
EXTERN C DAT_0084E864:BYTE
EXTERN C DAT_0084E865:BYTE
EXTERN C DAT_0084E871:DWORD

; FUNCTION: GAMEMD 0x7C5F3D
; FUN_007C5F3D -- CPU identification: class 3/4 by the AC/ID flag toggles, CPUID vendor
; string, family and stepping; returns whether MMX is present (EDX bit 23 of leaf 1).
FUN_007C5F3D PROC C USES ebx ecx edx
	LOCAL	cpuid_ok:BYTE, family:BYTE
	mov	DAT_0084E864,0
	mov	cpuid_ok,0
	pushfd
	pop	eax
	mov	ecx,eax
	xor	eax,40000h
	push	eax
	popfd
	pushfd
	pop	eax
	xor	eax,ecx
	mov	family,3
	jz	@@classed
	push	ecx
	popfd
	mov	family,4
	mov	eax,ecx
	xor	eax,200000h
	push	eax
	popfd
	pushfd
	pop	eax
	xor	eax,ecx
	jz	@@classed
	mov	cpuid_ok,1
	xor	eax,eax
	cpuid
	mov	DWORD PTR DAT_0084E865,ebx
	mov	DWORD PTR [DAT_0084E865+4],edx
	mov	DWORD PTR [DAT_0084E865+8],ecx
	mov	DAT_0084E871,20h
	cmp	eax,1
	jl	@@classed
	xor	eax,eax
	inc	eax
	cpuid
	mov	edx,eax
	and	edx,0F0h
	shr	edx,4
	mov	DAT_0084E864,dl
	and	eax,0F00h
	shr	eax,8
	mov	family,al
@@classed:
	mov	al,family
	mov	DAT_0084E863,al
	cmp	al,5
	jb	@@nomultimedia
	mov	eax,1
	cpuid
	test	edx,800000h
	jz	@@nomultimedia
	mov	eax,1
	mov	DAT_0084E862,1
	ret
@@nomultimedia:
	xor	eax,eax
	mov	DAT_0084E862,0
	ret
FUN_007C5F3D ENDP

; FUNCTION: GAMEMD 0x7C5FFF
; FUN_007C5FFF -- CMOV detection: needs family 5 or later and CPUID leaf 1 EDX bit 15; sets
; the two cmov flags (the first only above family 5) and returns whether CMOV is usable.
FUN_007C5FFF PROC C
	push	ebx
	push	ecx
	cmp	DAT_0084E863,5
	jb	@@unsupported
	mov	eax,1
	cpuid
	test	edx,8000h
	jz	@@unsupported
	cmp	DAT_0084E863,5
	jbe	@@family5
	mov	DAT_0084E860,1
	mov	DAT_0084E861,1
	mov	eax,1
	pop	ecx
	pop	ebx
	ret
@@family5:
	mov	DAT_0084E860,0
	mov	DAT_0084E861,1
	mov	eax,1
	pop	ecx
	pop	ebx
	ret
@@unsupported:
	mov	DAT_0084E860,0
	mov	DAT_0084E861,0
	mov	eax,0
	pop	ecx
	pop	ebx
	ret
FUN_007C5FFF ENDP

; FUNCTION: GAMEMD 0x7C6064
; FUN_007C6064 -- RDTSC wrapper: stores the high dword of the time-stamp counter through
; its one pointer argument.
FUN_007C6064 PROC C USES esi, high_out:DWORD
	rdtsc
	mov	esi,[high_out]
	mov	[esi],edx
	ret
FUN_007C6064 ENDP

; FUNCTION: GAMEMD 0x7C6072
; FUN_007C6072 -- 386/486/586 class: tries to toggle the AC flag, then the ID flag, in
; EFLAGS; returns 0 when AC cannot be toggled, 1 when ID cannot, else 2 (low word).
FUN_007C6072 PROC C USES ebx
	LOCAL	cpu_class:WORD
	pushfd
	mov	cpu_class,0
	pushfd
	pop	eax
	mov	ebx,eax
	xor	eax,40000h
	push	eax
	popfd
	pushfd
	pop	eax
	xor	eax,ebx
	jz	@@done
	mov	cpu_class,1
	pushfd
	pop	eax
	mov	ebx,eax
	xor	eax,200000h
	push	eax
	popfd
	pushfd
	pop	eax
	xor	eax,ebx
	jz	@@done
	mov	cpu_class,2
@@done:
	popfd
	sub	eax,eax
	mov	ax,cpu_class
	ret
FUN_007C6072 ENDP
_TEXT ENDS
END
