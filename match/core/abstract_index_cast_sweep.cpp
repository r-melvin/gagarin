// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at each address below.
//
// The eighteen members of the 204-byte index-lookup-and-cast family, ordered
// ascending by retail address. Each checks the owner's abstract tag, looks the
// owner's ID up in the global IndexClass at 0xB0E840 and dynamic-casts the
// stored AbstractClass pointer to its own target type. Only the target RTTI
// type descriptor differs between them.
//
// The lookup body that makes these match is in the header; the three phrasing
// levers it needed are documented there. Getting from the first working shape
// to 100% took five failed spellings first -- structured if/early-return
// (10.5%), a flat goto-threaded body (34.7%), all six declaration orders of
// {node, base, count} (34.7% each), the lookup as a free function rather than a
// member (34.7%), the key passed by value (2.8%) and the whole thing flattened
// into the caller with a `slot` local (1.4%). The residual at 34.7% looked like
// a pure register-colouring tie-break, and it was, but the cause was source
// visible: cl merging two identical `return 0` exits. Splitting the search into
// its own inline function un-merged them and the colouring fell into line.

// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line helper behind a jump).

#include "abstract_index_cast_sweep.h"
#include "../_layout/abstract_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/object_class.h"
#include "header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xB0E838
extern double DAT_00B0E838;
// GLOBAL: GAMEMD 0x7F4630
const double DAT_007F4630 = 60.0;

// SYNTHETIC: GAMEMD 0x6E6870
// GLOBAL: GAMEMD 0xB0E8A0
double DAT_00B0E8A0 = DAT_00B0E838 / DAT_007F4630;
// SYNTHETIC: GAMEMD 0x6E6890
// GLOBAL: GAMEMD 0xB0E888
double DAT_00B0E888 = 1.0 / DAT_00B0E8A0;
// SYNTHETIC: GAMEMD 0x6E6A10
// GLOBAL: GAMEMD 0xB0E890
TuningCoordInit DAT_00B0E890(128, 128, 0);

// GLOBAL: GAMEMD 0xB0E830 -- this unit's copy of the "no cell" value.
extern CellStruct DAT_00B0E830;

// GLOBAL: GAMEMD 0x87F7E8 -- the map; 0x5657A0 returns the cell at a coordinate.
struct Map_0087F7E8
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    CellClass* FUN_005657A0(const CellStruct* cell);
};
extern Map_0087F7E8 DAT_0087F7E8;

// FUNCTION: GAMEMD 0x40DD70 (decl; reloc) -- __fastcall, object in ECX.
void* __fastcall FUN_0040DD70(void* object);

// FUNCTION: GAMEMD 0x6E6AB0
AbstractIdOwner::AbstractIdOwner(AbstractClass* object)
{
    if (object) {
        if (object->vf_11() == 0x0B) {
            Rtti = 0x0B;
            CellStruct cell = static_cast<CellClass*>(object)->MapCoords;
            ID = cell.X + cell.Y * 1000;
        } else {
            Rtti = 0x34;
            ID = object->vf_rtti_4();
        }
    } else {
        Rtti = 0;
        ID = 0;
    }
}

// FUNCTION: GAMEMD 0x6E6B20
AbstractIdOwner::AbstractIdOwner(const CellStruct& cell)
{
    if (cell.X == DAT_00B0E830.X && cell.Y == DAT_00B0E830.Y) {
        Rtti = 0;
    } else {
        Rtti = 0x0B;
        ID = cell.X + cell.Y * 1000;
    }
}

// FUNCTION: GAMEMD 0x6E6B70
AbstractIdOwner::AbstractIdOwner(const CoordStruct& coord)
{
    Rtti = 0x0B;
    ID = coord.X / 256 + (coord.Y / 256) * 1000;
}

// FUNCTION: GAMEMD 0x6E6BB0
void* AbstractIdOwner::AsAbstractTypeClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_AbstractTypeClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E6C80
void* AbstractIdOwner::AsTagClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TagClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E6D50
void* AbstractIdOwner::AsTagTypeClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TagTypeClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E6E20
AbstractClass* AbstractIdOwner::FUN_006E6E20()
{
    if (Rtti == 0x34) {
        return (AbstractClass*)FUN_007CAAE4(*AbstractIndex.FetchIndex(ID), 0,
                                            TypeDesc_AbstractClass,
                                            TypeDesc_AbstractClass, 0);
    }
    if (Rtti == 0x0B) {
        CellStruct cell;
        cell.X = (short)(ID % 1000);
        cell.Y = (short)(ID / 1000);
        return DAT_0087F7E8.FUN_005657A0(&cell);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6E6F20
void* AbstractIdOwner::FUN_006E6F20()
{
    if (Rtti == 0x34) {
        return FUN_0040DD70(*AbstractIndex.Fetch(this));
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6E6FF0
void* AbstractIdOwner::AsObjectClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_ObjectClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E70C0
void* AbstractIdOwner::AsFootClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_FootClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7190
void* AbstractIdOwner::AsTriggerClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TriggerClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7260
void* AbstractIdOwner::AsHouseClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_HouseClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7330
void* AbstractIdOwner::AsTechnoTypeClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TechnoTypeClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7400
void* AbstractIdOwner::AsTriggerTypeClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TriggerTypeClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E74D0
void* AbstractIdOwner::AsTeamTypeClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TeamTypeClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E75A0
void* AbstractIdOwner::AsTerrainClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TerrainClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7670
void* AbstractIdOwner::AsBulletClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_BulletClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7740
void* AbstractIdOwner::AsAnimClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_AnimClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7810
void* AbstractIdOwner::AsTeamClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_TeamClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E78E0
void* AbstractIdOwner::AsInfantryClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_InfantryClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E79B0
void* AbstractIdOwner::AsUnitClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_UnitClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7A80
void* AbstractIdOwner::AsBuildingClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_BuildingClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7B50
void* AbstractIdOwner::AsAircraftClass()
{
    if (Rtti == 0x34) {
        return FUN_007CAAE4(*AbstractIndex.Fetch(this), 0,
                            TypeDesc_AbstractClass,
                            TypeDesc_AircraftClass, 0);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6E7C20
CellClass* AbstractIdOwner::FUN_006E7C20()
{
    if (Rtti == 0x0B) {
        CellStruct cell;
        cell.X = (short)(ID % 1000);
        cell.Y = (short)(ID / 1000);
        return DAT_0087F7E8.FUN_005657A0(&cell);
    }
    return 0;
}
