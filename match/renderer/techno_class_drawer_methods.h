// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, vtable slots and globals read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x705D70:
//   `CALL [EAX+0x84]` (GetTechnoType slot), `[ESI+0x21C]` (TechnoClass::Owner),
//   `[EAX+0xDF0]` (TechnoTypeClass::Palette, a DynamicVectorClass*),
//   `[EDX+4]` (its Items), `[ECX+0x16054]` (HouseClass::ColorSchemeIndex),
//   `[..+0x30C]` (ColorScheme::LightConvert), `CALL [EDX+0x440]` with
//   `[0xA83D4C]` pushed (HouseClass::CurrentPlayer), `CALL [EDX+0xD0]` with 1
//   pushed (GetDisguiseHouse slot), and `[0xB054D4]` (ColorScheme::Array.Items,
//   i.e. the vector object at 0xB054D0 plus 4).
//   Owner @0x21C agrees with the committed spine match/_layout/techno_class.h;
//   Palette @0xDF0 agrees with match/_layout/techno_type_class.h (not includable
//   next to the TechnoClass spine — both define TurretControl — so a local
//   placeholder carries it). Names from YRpp TechnoClass.h / ColorScheme.h /
//   HouseClass.h (consult-only) and docs/decomp_spec/re_findings/
//   unit_render_faithful.md §1.3.
#ifndef GG_MATCH_RENDERER_TECHNO_CLASS_DRAWER_METHODS_H
#define GG_MATCH_RENDERER_TECHNO_CLASS_DRAWER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/techno_class.h"   // TechnoClass (Owner @0x21C)

struct LightConvertClass;

// ColorScheme view: only the per-house remap drawer touched here.
struct ColorScheme_00705D70
{
    char               _pad000[0x30C];   // +0x0000
    LightConvertClass* LightConvert;     // +0x030C
};
GG_STATIC_ASSERT(offsetof(ColorScheme_00705D70, LightConvert) == 0x30C);

// DynamicVectorClass<ColorScheme*> view (vptr @0, Items @4 as in the spine's
// DynamicVectorClass). The element access MUST go through the inlined
// operator[] — a raw `Items[i]` compiles to the same instructions but VC6
// then chains the loads through one register (global->ECX, element->EDX)
// where retail keeps them apart (global->EAX, element->ECX, result->EAX).
struct ColorSchemeVec_00705D70
{
    void*                   _vtable;   // +0x0000
    ColorScheme_00705D70**  Items;     // +0x0004

    ColorScheme_00705D70*& operator[](int index) { return this->Items[index]; }
};
GG_STATIC_ASSERT(offsetof(ColorSchemeVec_00705D70, Items) == 0x04);

// HouseClass view: only the colour-scheme index touched here.
struct House_00705D70
{
    char _pad000[0x16054];    // +0x00000
    int  ColorSchemeIndex;    // +0x16054
};
GG_STATIC_ASSERT(offsetof(House_00705D70, ColorSchemeIndex) == 0x16054);

// TechnoTypeClass view: only the optional per-type palette list touched here.
struct TechnoType_00705D70
{
    char                     _pad000[0xDF0];   // +0x0000
    ColorSchemeVec_00705D70* Palette;          // +0x0DF0  DynamicVectorClass<ColorScheme*>*
};
GG_STATIC_ASSERT(offsetof(TechnoType_00705D70, Palette) == 0xDF0);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_00705D70* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xB054D0 — ColorScheme::Array (its Items pointer is 0xB054D4).
extern ColorSchemeVec_00705D70 DAT_00B054D0;

// Declaration order matters — see match/_rt/gg_vslot.h. The class must be
// complete before the member-function-pointer types, or VC6 uses the 8-byte
// multiple-inheritance representation and emits a `this` adjustment.
struct Vtbl_00705D70;

// The spine's TechnoClass is data-only; this view adds the matched method on
// the identical layout (single inheritance at offset 0, no adjustment). The
// vptr @0 is reached by a raw cast on `this`: the spine's `class TechnoClass;`
// forward declaration makes VC6 treat its RadioClass base as private.
struct Techno_00705D70 : TechnoClass
{
    // FUNCTION: GAMEMD 0x705D70 — TechnoClass::GetDrawer
    LightConvertClass* GetDrawer();
};
GG_STATIC_ASSERT(offsetof(Techno_00705D70, Owner) == 0x21C);
GG_STATIC_ASSERT(sizeof(Techno_00705D70)          == 0x520);

typedef TechnoType_00705D70* (Techno_00705D70::*Fn084_00705D70)();
typedef House_00705D70*      (Techno_00705D70::*Fn0D0_00705D70)(int fromLocalPlayer);
typedef bool                 (Techno_00705D70::*Fn440_00705D70)(House_00705D70* house);

struct Vtbl_00705D70
{
    char           _pad000[0x84];             // +0x0000
    Fn084_00705D70 At_084;                    // +0x0084  GetTechnoType()
    char           _pad088[0xD0 - 0x88];      // +0x0088
    Fn0D0_00705D70 At_0D0;                    // +0x00D0  GetDisguiseHouse(bool)
    char           _pad0D4[0x440 - 0xD4];     // +0x00D4
    Fn440_00705D70 At_440;                    // +0x0440  IsClearlyVisibleTo(HouseClass*)
};
GG_STATIC_ASSERT(offsetof(Vtbl_00705D70, At_084) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_00705D70, At_0D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(Vtbl_00705D70, At_440) == 0x440);

#endif  // GG_MATCH_RENDERER_TECHNO_CLASS_DRAWER_METHODS_H
