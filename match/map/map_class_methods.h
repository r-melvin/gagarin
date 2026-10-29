// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Signatures
//   cross-checked against YRpp:
//     static void __fastcall MapClass::UnselectAll()
//     static LandType __fastcall MapClass::GetLandTypeFromName(const char* name)
#ifndef GG_MATCH_MAP_MAP_CLASS_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// Minimal view of MapClass: only the two free-standing statics matched in this
// TU. Both are register-passing (__fastcall) free functions in retail; modelled
// as static members so the mangled names carry the MapClass scope.
struct CoordStruct;
struct CellStruct;
class CellClass;

class MapView_5865E0
{
public:
    static void UnselectAll();
    static int  GetLandTypeFromName(const char* name);  // LandType (enum=int)

    // FUNCTION: GAMEMD 0x5865E0  MapClass::IsLocationFogged (__thiscall, ret 4)
    // A non-static __thiscall taking one pointer argument. Retail is the
    // two-instruction stub `XOR AL,AL; RET 0x4` — fog-of-war querying is
    // compiled out of the retail build, so the predicate is a constant false.
    bool IsLocationFogged(CoordStruct const* coords) const;

    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the cell at a cell coordinate (RET 4).
    CellClass* FUN_005657A0(const CellStruct& cell);
    // FUNCTION: GAMEMD 0x574000 (decl; reloc) -- one stack argument.
    void FUN_00574000(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x574C20 (decl; reloc) -- one stack argument.
    void FUN_00574C20(const CellStruct* cell);
};

#endif  // GG_MATCH_MAP_MAP_CLASS_METHODS_H
