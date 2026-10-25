// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; address-local linked-object prefix view | YRpp-cross-check
//   Every member offset below is read from a foundation entry's disassembly:
//     +0x09C Location        0x55A7D0 `ADD EAX,0x9C`, 0x55ACA0 `ADD ECX,0x9C`
//     +0x388 PrimaryFacing   0x55A730 / 0x55A7D0 `ADD ECX,0x388`
//     vtable +0x1C8          0x55A8C0 `CALL [EDX+0x1C8]` (int result)
//     vtable +0x538          0x55AD10 `CALL [EDX+0x538]` (int result)
//   Names from YRpp.
//
// Address-local prefix view of the linked object. The public method signatures
// use the project FootClass forward declaration; this uniquely named layout view
// is only for the field and vtable slots read by these base bodies.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_FOOT_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_FOOT_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "loco_interfaces.h"

// A binary-angle direction. The user-declared constructor is what makes VC6
// return it through a hidden pointer (a POD this size would come back in EAX);
// retail reads the whole dword off that pointer.
struct LocoDir
{
    unsigned int Raw;   // +0x00
    LocoDir() {}
};
GG_STATIC_ASSERT(offsetof(LocoDir, Raw) == 0x00);
GG_STATIC_ASSERT(sizeof(LocoDir) == 4);

// FacingClass (0x18, opaque): only Current() is called.
struct LocoFacing
{
    char opaque[0x18];

    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) - FacingClass::Current (__thiscall, hidden return).
    LocoDir Current();
};
GG_STATIC_ASSERT(sizeof(LocoFacing) == 0x18);

// Single-argument __fastcall slot call: ECX = the object, nothing in EDX.
typedef int (*LocoFootSlot)(FootClass*);

struct LocoFootVtbl
{
    char         unknown_000[0x1C8];
    LocoFootSlot At_1C8;                              // +0x1C8
    char         unknown_1CC[0x538 - 0x1CC];
    LocoFootSlot At_538;                              // +0x538
};
GG_STATIC_ASSERT(offsetof(LocoFootVtbl, At_1C8) == 0x1C8);
GG_STATIC_ASSERT(offsetof(LocoFootVtbl, At_538) == 0x538);

struct LocoFootView_0055A730
{
    LocoFootVtbl* Vtbl;                               // +0x000
    char          unknown_004[0x9C - 0x04];
    LocoCoord     Location;                           // +0x09C
    char          unknown_0A8[0x388 - 0xA8];
    LocoFacing    PrimaryFacing;                      // +0x388
};
GG_STATIC_ASSERT(offsetof(LocoFootView_0055A730, Vtbl) == 0x00);
GG_STATIC_ASSERT(sizeof(LocoFootVtbl*) == 4);
GG_STATIC_ASSERT(offsetof(LocoFootView_0055A730, Location)      == 0x09C);
GG_STATIC_ASSERT(offsetof(LocoFootView_0055A730, PrimaryFacing) == 0x388);

// MapClass cell lookup used by ShadowMatrix (0x55A7D0 passes the map object in
// ECX and one pointer on the stack, callee pops: `CALL 0x565730`).
struct LocoCell
{
    char          unknown_000[0x11C];
    unsigned char SlopeIndex;                         // +0x11C
};
GG_STATIC_ASSERT(offsetof(LocoCell, SlopeIndex) == 0x11C);

struct LocoMap
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x565730 (decl; reloc) - MapClass::GetCellAt (__thiscall).
    LocoCell* GetCellAt(const LocoCoord& coord);
};

// GLOBAL: GAMEMD 0x87F7E8 - the map object (ShadowMatrix `MOV ECX,0x87F7E8`).
extern LocoMap DAT_0087F7E8;

// GLOBAL: GAMEMD 0xABCC78 - 3-dword coordinate constant copied by Destination.
extern LocoCoord DAT_00ABCC78;

// GLOBAL: GAMEMD 0xABCD3C - live COM-object counter, bumped by this class's
// AddRef/Release and by at least ten other COM classes (x-refs 0x46AFD4,
// 0x49FFF4, 0x4A0524 ...).
extern int DAT_00ABCD3C;

// FUNCTION: GAMEMD 0x6D20E0 (decl; reloc) - `__fastcall int (int)`, ECX argument,
// float arithmetic and a `_ftol` return (ShadowPoint's Y).
int FUN_006D20E0(int value);

#include "matrix3d_native_helpers.h"

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_LOCO_FOOT_H
