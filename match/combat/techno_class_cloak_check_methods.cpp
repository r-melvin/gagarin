// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6FBC90.

#include "techno_class_cloak_check_methods.h"

#define GG_VTBL_006FBC90(self) (*(Vtbl_006FBC90**)(self))

// Rank-granted cloak: a veteran whose type grants the cloak ability at the
// veteran tier, or an elite granted it at either tier. Expanded inline; the
// type is fetched only once a rank test has passed.
static inline bool CloaksByRank_006FBC90(Techno_006FBC90* self)
{
    VeterancyStruct* vet = &self->Veterancy;
    TechnoType_006FBC90* type;
    return (FUN_0074FF90(vet) || FUN_00750010(vet))
        && (type = (self->*GG_VTBL_006FBC90(self)->GetTechnoType)(),
            (FUN_0074FF90(vet) && type->VeteranAbilities[6])
            || (FUN_00750010(vet) && (type->VeteranAbilities[6] || type->EliteAbilities[6])));
}

// FUNCTION: GAMEMD 0x6FBC90
//
// Should this object be visible even though it could cloak? An object that
// can cloak (by its virtual or its Cloakable flag) stays hidden while any of
// the four state tests at +0x37C, +0x380, +0x1D4 and +0x1D8 holds; if none
// does it is not to be cloaked. A veteran whose type grants the cloak
// ability at the veteran tier, or an elite granted it at either tier, is
// always allowed to cloak. Otherwise the object is uncloaked exactly when
// its cell is under its own house's sensors.
//
// Phrasing that matters: retail emits every false result as one shared
// `XOR AL,AL` tail with the single `MOV AL,1` inline before it, so the whole
// body is one `&&` chain (the rank check as an expression-bodied inline
// helper, the cell conversion under the comma operator) falling through to
// one `return false`; the same tests as early `return false` statements
// each get their own epilogue (28.6%). The Veterancy address is taken
// inside the helper: a top-level `vet` local hoists the LEA above the first
// virtual call (74.3%).
bool Techno_006FBC90::ShouldNotBeCloaked()
{
    Coord_006FBC90 buf;
    Cell_006FBC90 cell;
    if ((!((this->*GG_VTBL_006FBC90(this)->IsCloakable)() || this->Cloakable != 0)
         || (this->*GG_VTBL_006FBC90(this)->At_37C)()
         || (this->*GG_VTBL_006FBC90(this)->At_380)()
         || (this->*GG_VTBL_006FBC90(this)->At_1D4)()
         || (this->*GG_VTBL_006FBC90(this)->At_1D8)())
        && !CloaksByRank_006FBC90(this)
        && (cell = CoordToCell_006FBC90((this->*GG_VTBL_006FBC90(this)->GetCoords)(&buf)),
            !DAT_0087F7E8.GetCellAt(cell)->FUN_004870B0(((House_006FBC90*)this->Owner)->ArrayIndex))) {
        return true;
    }
    return false;
}
