// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x710470. InOpenToppedTransport @0x82 comes from the
//   committed ObjectClass spine and is reconfirmed here
//   (`MOV byte ptr [ESI+0x82],1`). The singleton and callee bindings are YRpp's
//  , reconfirmed against the disassembly:
//   0x0087F778 = LogicClass::Instance, 0x0055BAA0 = LogicClass::AddObject.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_OPENTOPPED_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_OPENTOPPED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;

// LogicClass — the global per-frame update list. AddObject is virtual in the
// class hierarchy, but retail reaches it with a *direct* CALL because the
// receiver is the concrete `Instance` object rather than a pointer, so it is
// declared non-virtual here to reproduce that.
struct LogicClass
{
    bool AddObject(TechnoClass* object, bool sorted);   // GAMEMD 0x55BAA0 (declared; reloc)
};

// GLOBAL: GAMEMD 0x0087F778 — LogicClass::Instance (the object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0x87F778`).
extern LogicClass LogicInstance;

// The passenger's virtual at primary-vtable slot +0x3D0, dispatched through the
// tree's usual __fastcall-fn-pointer idiom.
typedef void (__fastcall* Slot3D0Func)(TechnoClass*);
#define TECHNO_SLOT_3D0(obj) ((*(Slot3D0Func*)(*(char**)(obj) + 0x3d0))(obj))

// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass
{
public:
    char _pad00[0x82];                 // +0x0000
    bool InOpenToppedTransport;        // +0x0082

    void EnteredOpenTopped(TechnoClass* who);   // GAMEMD 0x710470
};
GG_STATIC_ASSERT(offsetof(TechnoClass, InOpenToppedTransport) == 0x82);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_OPENTOPPED_METHODS_H
