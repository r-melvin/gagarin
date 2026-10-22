// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Slot numbers, the HRESULT constant and both IID addresses are read
//   numerically off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x45AEA0 and 0x45AF20. Neither entry point is bound by YRpp.
//
// A pair of "re-point this holder at an interface queried from another" helpers.
// They differ only in the IID pushed (0x818858 against 0x819088).
//
// The COM shape is read straight off the call sites: slot 0 takes three stack
// arguments with the receiver pushed first (QueryInterface(this, riid, ppv))
// and slot +0x08 takes only the receiver (Release(this)) - the __stdcall
// virtual convention, not __thiscall.
#ifndef GG_MATCH_CORE_COM_HOLDER_QUERY_METHODS_H
#define GG_MATCH_CORE_COM_HOLDER_QUERY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct IUnk;

typedef long (__stdcall* QuerySlot)(IUnk*, const void*, void**);
typedef unsigned long (__stdcall* ReleaseSlot)(IUnk*);

#define COM_QUERY(p, iid, ppv) \
    ((*(QuerySlot*)(*(char**)(p) + 0x00))(p, iid, ppv))
#define COM_SLOT_08(p) \
    ((*(ReleaseSlot*)(*(char**)(p) + 0x08))(p))

// The two interface identifiers, pushed by address as plain immediates.
struct Guid { char Bytes[16]; };
extern Guid DAT_00818858;   // GLOBAL: GAMEMD 0x818858
extern Guid DAT_00819088;   // GLOBAL: GAMEMD 0x819088

struct ComHolder_0045AEA0
{
    IUnk* Held;   // +0x0000

    // FUNCTION: GAMEMD 0x45AEA0
    long FUN_0045AEA0(IUnk** source);
    // FUNCTION: GAMEMD 0x45AF20
    long FUN_0045AF20(IUnk** source);
};
GG_STATIC_ASSERT(offsetof(ComHolder_0045AEA0, Held) == 0);

#endif  // GG_MATCH_CORE_COM_HOLDER_QUERY_METHODS_H
