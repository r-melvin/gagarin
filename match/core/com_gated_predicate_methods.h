// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, the vtable slot, the two RulesClass fields and the global read are
//   taken numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x41B920 and 0x41B980. Neither address is bound by YRpp,
//   so the placeholder names are kept.
//
// A pair of predicates that route on the object's type index and, for two
// particular types, answer from a COM interface instead. They differ in exactly
// two places: the __fastcall helper taken on the other path (0x4DE620 against
// 0x5F6B60) and the polarity of the final answer - 0x41B920 ends
// `NEG AL; SBB EAX,EAX; NEG EAX` (non-zero -> 1) and 0x41B980 ends
// `NEG AL; SBB EAX,EAX; INC EAX` (zero -> 1). Written out longhand rather than
// shared, per the family rule.
#ifndef GG_MATCH_CORE_COM_GATED_PREDICATE_METHODS_H
#define GG_MATCH_CORE_COM_GATED_PREDICATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/rules_class.h"

struct IFace;

// The interface slot at +0x80 takes no arguments beyond the receiver and
// returns a byte - retail tests it with `NEG AL`, never the full register. It
// is reached as `PUSH ESI; MOV EAX,[ESI]; CALL [EAX+0x80]`, i.e. the receiver
// goes on the stack rather than into ECX, which is the __stdcall COM virtual
// convention RA2 uses throughout.
typedef char (__stdcall* Slot0b)(IFace*);
#define IFACE_CALL0B(p, slot) \
    ((*(Slot0b*)(*(char**)(p) + (slot)))(p))

// __stdcall, one argument, no return used. 0x80004003 is E_POINTER; this is the
// missing-pointer report the smart-pointer dereference emits.
void __stdcall FUN_007DC720(unsigned int hr);


// GLOBAL: GAMEMD 0x008871E0 — pointer to the active RulesClass instance.
extern RulesClass* RulesInstance;

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AircraftClass's own vtable is 0x7E22A4.
//   0x41B920 -> AircraftClass slot 21 (byte-off 0x54).
//   0x41B980 -> AircraftClass slot 20 (byte-off 0x50).
// Each of those tables is the only table in the image that holds them, so the slot is
// declared on AircraftClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AircraftClass_0041B920
{
    char   _pad000[0x674];
    IFace* Interface;    // +0x0674
    char   _pad678[0x6C4 - 0x678];
    AircraftTypeClass* TypeIndex;    // +0x06C4

    // Fallback used by the predicate at 0x41B920.
    // FUNCTION: GAMEMD 0x4DE620
    int FUN_004DE620();

    // FUNCTION: GAMEMD 0x41B920
    int FUN_0041B920();
};
GG_STATIC_ASSERT(offsetof(AircraftClass_0041B920, Interface) == 0x674);
GG_STATIC_ASSERT(offsetof(AircraftClass_0041B920, TypeIndex) == 0x6C4);

#endif  // GG_MATCH_CORE_COM_GATED_PREDICATE_METHODS_H
