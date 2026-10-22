// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6E3EE0  TActionClass::GetFlags          (__fastcall)
//   FUNCTION: GAMEMD 0x6E45E0  TActionClass::FindHouseByIndex  (__stdcall)

#include "taction_class_methods.h"

// External callees reached by FindHouseByIndex. Declared (no body) so cl emits a
// relocatable CALL; the reloc is normalised by the differ. Each single-argument
// callee takes its argument in ECX (modelled as __fastcall).
//   0x726910 — resolve the "current/special" house from the source pointer.
//   0x510F60 — predicate over a raw house index (returns bool in AL).
//   0x510ED0 — house lookup when the predicate holds.
//   0x502D30 — house lookup otherwise.
int __fastcall TActionClass_Sub726910(void* pSource);
bool __fastcall TActionClass_Sub510F60(int index);
int __fastcall TActionClass_Sub510ED0(int index);
int __fastcall TActionClass_Sub502D30(int index);

// FUNCTION: GAMEMD 0x6E3EE0  (__fastcall)
// Sparse switch over the action id: a handful of ids carry flag bit 0x2, the
// rest return 0. cl lowers this to the `add ecx,-0xe` range-reduce + a packed
// byte index table feeding a 2-entry jump table.
int __fastcall TActionClass::GetFlags(int actionKind)
{
    int flags = 0;
    switch (actionKind)
    {
    case 0xE:
    case 0x20:
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x5B:
    case 0x6F:
        flags = 2;
    }
    return flags;
}

// FUNCTION: GAMEMD 0x6E45E0  (__stdcall)
//
// Null source -> none. Index 0x2325 is the special "source's own" house. Index
// -1 -> none. Otherwise a predicate picks between two index-based lookups.
//
// Retail defers `push esi` past the leading `pSource == 0` guard, so the null
// path returns via `xor eax,eax; ret 8` with no saved-register traffic. cl only
// produces that when the guard is the sole statement of the outer function and
// the ESI-using body is a separate __inline helper it expands after the guard:
// the inlined body brings its own register save. Writing the whole chain in one
// body (any nesting, own-block returns, a switch over the index, or a result
// local) puts `push esi` in the prologue and a `pop esi` on the null path
// (3.4%..14.3%). Bytes are identical to retail (raw_match.py 100%, 4 reloc
// slots); diff_retail.py alone reads 26.7% because objdump splits the inlined
// helper's `$L` block labels at odd offsets inside the `jnz`/`call` pair.
static __inline int find_house_inner(void* pSource, int index)
{
    if (index == 0x2325)
        return TActionClass_Sub726910(pSource);

    if (index == -1)
        return 0;

    if (TActionClass_Sub510F60(index))
        return TActionClass_Sub510ED0(index);

    return TActionClass_Sub502D30(index);
}

int __stdcall TActionClass::FindHouseByIndex(void* pSource, int index)
{
    if (pSource == 0)
        return 0;

    return find_house_inner(pSource, index);
}
