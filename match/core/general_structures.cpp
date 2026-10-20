// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp GeneralStructures.h (consult-only, no LICENSE;
//   each offset/address reconfirmed against the user's binary below).
//
// Translation unit: BasePlanningCellContainer growth + qsort comparator.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x510860  BasePlanningCellContainer::AddCapacity (__thiscall)
//   FUNCTION: GAMEMD 0x5108F0  BasePlanningCellContainer::Comparator  (__cdecl)
//   LIBRARY:  GAMEMD 0x7C8E17  operator new / malloc  (CRT; excluded from match)
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete / free (CRT; excluded from match)

#include "general_structures.h"

// CRT allocation thunks. The diff harness normalises the call relocation, so
// only the call shape matters (PUSH size; CALL; ADD ESP,4 / PUSH ptr; CALL;
// ADD ESP,4). Declared __cdecl, no body, so cl emits the call.
extern "C" void* __cdecl gamemd_operator_new(unsigned int size);  // GAMEMD 0x7C8E17
extern "C" void  __cdecl gamemd_operator_delete(void* block);     // GAMEMD 0x7C8B3D

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x510860  (__thiscall)
//
// Grow the cell array by `additionalCapacity` slots, preserving the existing
// Count elements. Reject a negative request; reject allocation failure. On
// success: copy the live elements, free the old buffer, publish the new buffer
// and capacity, and clear the Unknown_10 cursor.
//
// STILL A TRANSCRIPTION -- debt, not a match. Screened for the inline-assembly
// signature first (batch 38) and it is absent: the prologue uses EBP as an
// ordinary general register holding the argument (`PUSH EBP; MOV EBP,[ESP+0xC]`)
// rather than as a frame pointer, which is frame-pointer-omitted compiler
// output and something no hand-written block would do. So retail was compiled
// from C++ and the stream below still needs replacing.
//
// This pass got the C++ to 96.4% (54/56 instructions, multiset identical) and
// the whole body is now understood. The spelling that reaches it is:
//
//   bool AddCapacity(int additionalCapacity) {
//     if (additionalCapacity >= 0) {
//       int newCapacity = Capacity + additionalCapacity;
//       BasePlanningCell* newItems = (BasePlanningCell*)
//           operator new(newCapacity * sizeof(BasePlanningCell));
//       if (newItems != 0) {
//         int count = *(volatile int*)&Count;
//         int i = 0;
//         volatile int lastIndex = newCapacity - 1;   // retail's dead spill
//         if (count > 0) {
//           do { newItems[i] = Items[i]; ++i; } while (i < Count);
//         }
//         operator delete(Items);
//         Items = newItems; Capacity += additionalCapacity; Unknown_10 = 0;
//         return true;
//       }
//     }
//     return false;
//   }
//
// Three levers found, all reusable:
//   * retail's `DEC EBX; MOV [ESP+0x14],EBX` is a DEAD STORE of
//     `newCapacity - 1` into the argument's own home slot. A plain local is
//     eliminated (1.7%); a `volatile` local reproduces it exactly (11.3%).
//   * the two `return false` arms must be reached as the function's natural
//     trailing fallthrough -- nested success arms with one trailing
//     `return false` -- or cl parks the shared failure block in the middle of
//     the body. Two early returns give 11.3%, an explicit shared `fail:` label
//     35.7%, a bool accumulator 3.5%, nested arms 92.9%.
//   * reading Count through a volatile lvalue cast pins the loop-guard load
//     ahead of the dead spill, 92.9% -> 96.4%.
//
// The one residual is a two-instruction transposition with an identical
// multiset: retail emits `DEC EBX; XOR ECX,ECX` and cl emits
// `XOR ECX,ECX; DEC EBX`, i.e. it materialises the loop index before computing
// the dead value. Everything before and after is byte-exact. Nine further
// spellings were measured against it and none moves it: the dead value split
// into a plain local assigned into a pre-declared volatile; the same with the
// index zeroed before, between and after; `--newCapacity` in place of a second
// local; the value re-derived as `Capacity + additionalCapacity - 1` (8.9%);
// the index written as `count - count`; the `for` loop in place of the guarded
// `do`/`while` (28.1%); and writing the spill through the parameter itself with
// a volatile lvalue cast (12.5%).
//
// Per the charter the naked stream stays until the transposition is solved,
// because 96.4% is a regression against it. On entry ECX = this;
// additionalCapacity at [ESP+4].
__declspec(naked) bool BasePlanningCellContainer::AddCapacity(int /*additionalCapacity*/)
{
    __asm {
        push    ebx
        push    ebp
        mov     ebp, [esp+0xc]          // additionalCapacity
        push    esi
        test    ebp, ebp
        push    edi
        mov     esi, ecx                // this
        jl      L_fail                  // additionalCapacity < 0 -> false
        mov     ebx, [esi+8]            // Capacity
        add     ebx, ebp                // newCapacity = Capacity + add
        lea     eax, [ebx*8]            // newCapacity * sizeof(BasePlanningCell)
        push    eax
        call    gamemd_operator_new
        mov     edi, eax                // newItems
        add     esp, 4
        test    edi, edi
        jz      L_fail                  // allocation failed -> false
        mov     eax, [esi+4]            // Count
        dec     ebx                     // newCapacity - 1 (dead; SP5 keeps it)
        xor     ecx, ecx                // i = 0
        mov     [esp+0x14], ebx         // spill into add's home slot
        test    eax, eax
        jle     L_after                 // Count <= 0 -> skip copy
    L_loop:
        mov     ebx, [esi]              // Items
        lea     eax, [ecx*8]            // i * 8
        mov     edx, eax
        add     edx, ebx                // &Items[i]
        inc     ecx                     // ++i
        mov     ebx, [edx]              // Items[i].Weight
        mov     [eax+edi], ebx          // newItems[i].Weight
        mov     edx, [edx+4]            // Items[i].Position
        mov     [eax+edi+4], edx        // newItems[i].Position
        mov     eax, [esi+4]            // Count
        cmp     ecx, eax
        jl      L_loop
    L_after:
        mov     eax, [esi]              // Items
        push    eax
        call    gamemd_operator_delete
        mov     eax, [esi+8]            // Capacity
        add     esp, 4
        add     eax, ebp                // Capacity + add
        mov     [esi], edi              // Items = newItems
        mov     [esi+8], eax            // Capacity += add
        mov     dword ptr [esi+0x10], 0 // Unknown_10 = 0
        pop     edi
        pop     esi
        pop     ebp
        mov     al, 1                   // return true
        pop     ebx
        ret     4
    L_fail:
        pop     edi
        pop     esi
        pop     ebp
        xor     al, al                  // return false
        pop     ebx
        ret     4
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5108F0  (__cdecl)
//
// qsort comparator over BasePlanningCell::Weight (the leading int of each
// element). Ascending: 0 when equal, +1 when a > b, -1 when a < b.
//
// MATCHED (100%, 16/16). This was recorded as a phrasing-invariant setcc-tail
// delta and is not one. Retail emits `setge dl; dec; and -2; inc` and the
// ternary written `(wa >= wb) ? 1 : -1` emits the mirror `setl dl; dec; and 2;
// dec` (81.2%). The lever is which arm carries the negative literal: writing
// the *less-than* test with -1 in the true arm, `(wa < wb) ? -1 : 1`, makes cl
// keep the comparison as written and invert the arithmetic instead, which is
// retail's tail exactly. Spelling the tail out by hand as
// `((wa >= wb) - 1 & -2) + 1` also reaches 100%, so the two forms are the same
// codegen path. Eight other spellings stay at 81.2% (`>` ternary, nested ifs,
// a named bool, a named int result, the loads written inline) and two are
// worse: `1 - 2 * (wa < wb)` is 62.5% and inverting the equality guard to
// `if (wa != wb) return ...` is 43.8%.
// ---------------------------------------------------------------------------
int __cdecl BasePlanningCellContainer::Comparator(const void* a, const void* b)
{
    int wa = *(const int*)a;
    int wb = *(const int*)b;
    if (wa == wb)
        return 0;
    return (wa < wb) ? -1 : 1;
}
