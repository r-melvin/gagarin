// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x424B50: `[ESI+0xCC]` (OwnerObject, cleared and
//   re-set), `[ESI+0x74]` (the byte that gates the display remove/submit
//   pair), `[EBP+0x84]` / `[EDI+0x84]` on the owner (cleared to 0 / raised to
//   1), the anim array globals `[0xA8E9B8]` (Count, loaded first) and
//   `[0xA8E9AC]` (Items, loaded inside the `> 0` gate, walked with `ADD
//   EDX,4`), the display instance `MOV ECX,0x87F7E8`, and the three virtual
//   slots `[EAX+0x48]` (GetCoords, out-pointer returned in EAX),
//   `[EAX+0x1B4]` (takes a CoordStruct*) and `[EDX+0x17C]` on the owner.
//   YRpp (consult-only, no LICENSE) names AnimClass::SetOwnerObject and
//   DisplayClass::Remove / Submit.
#ifndef GG_MATCH_COMBAT_ANIM_CLASS_OWNER_METHODS_H
#define GG_MATCH_COMBAT_ANIM_CLASS_OWNER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_00424B50 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Coord_00424B50) == 0xC);

struct VtblOwner_00424B50;

// The owned object an animation is attached to.
struct Owner_00424B50
{
    VtblOwner_00424B50* Vptr;               // +0x0000
    char                _pad0004[0x84 - 4]; // +0x0004
    char                unknown_84;         // +0x0084  1 while an anim is attached
};
GG_STATIC_ASSERT(offsetof(Owner_00424B50, unknown_84) == 0x84);

typedef Coord_00424B50* (Owner_00424B50::*Fn48O_00424B50)(Coord_00424B50* out);
typedef void (Owner_00424B50::*Fn17C_00424B50)();

struct VtblOwner_00424B50
{
    char _pad000[0x48];              // +0x0000
    Fn48O_00424B50 GetCoords;        // +0x0048
    char _pad04C[0x17C - 0x4C];      // +0x004C
    Fn17C_00424B50 At_17C;           // +0x017C
};
GG_STATIC_ASSERT(offsetof(VtblOwner_00424B50, GetCoords) == 0x48);
GG_STATIC_ASSERT(offsetof(VtblOwner_00424B50, At_17C)    == 0x17C);

struct VtblAnim_00424B50;

struct Anim_00424B50
{
    VtblAnim_00424B50* Vptr;                    // +0x0000
    char               _pad0004[0x74 - 4];      // +0x0004
    char               unknown_74;              // +0x0074  display-list membership
    char               _pad0075[0xCC - 0x75];   // +0x0075
    Owner_00424B50*    OwnerObject;             // +0x00CC

    // FUNCTION: GAMEMD 0x424B50 -- AnimClass::SetOwnerObject.
    void SetOwnerObject(Owner_00424B50* owner);
};
GG_STATIC_ASSERT(offsetof(Anim_00424B50, unknown_74)  == 0x74);
GG_STATIC_ASSERT(offsetof(Anim_00424B50, OwnerObject) == 0xCC);

typedef Coord_00424B50* (Anim_00424B50::*Fn48A_00424B50)(Coord_00424B50* out);
typedef void (Anim_00424B50::*Fn1B4_00424B50)(const Coord_00424B50* delta);

struct VtblAnim_00424B50
{
    char _pad000[0x48];              // +0x0000
    Fn48A_00424B50 GetCoords;        // +0x0048
    char _pad04C[0x1B4 - 0x4C];      // +0x004C
    Fn1B4_00424B50 At_1B4;           // +0x01B4
};
GG_STATIC_ASSERT(offsetof(VtblAnim_00424B50, GetCoords) == 0x48);
GG_STATIC_ASSERT(offsetof(VtblAnim_00424B50, At_1B4)    == 0x1B4);

// GLOBAL: GAMEMD 0xA8E9AC / 0xA8E9B8 -- AnimClass::Array Items / Count.
extern Anim_00424B50** DAT_00A8E9AC;
extern int             DAT_00A8E9B8;

struct Display_00424B50
{
    // FUNCTION: GAMEMD 0x4A9720 (decl; reloc) -- DisplayClass::Submit.
    void Submit(Anim_00424B50* object);
    // FUNCTION: GAMEMD 0x4A9770 (decl; reloc) -- DisplayClass::Remove.
    void Remove(Anim_00424B50* object);
};

// GLOBAL: GAMEMD 0x87F7E8 -- DisplayClass::Instance (used by address, ECX).
extern Display_00424B50 DAT_0087F7E8;

#endif  // GG_MATCH_COMBAT_ANIM_CLASS_OWNER_METHODS_H
