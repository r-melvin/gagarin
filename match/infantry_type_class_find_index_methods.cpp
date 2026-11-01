// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail 0x523C90: the name is tested against "<none>" (0x817474) and "none" (0x817694) with
//   _strcmpi (0x7C8D20), then compared with the ID (+0x24) of each entry of the infantry type
//   array at 0xA8E348 (Items +4, Count +0x10).

#include "_layout/infantry_type_class.h"
#include "_layout/rules_class.h"
#include "vector_class.h"
#include "vector_class_dynamic_ctor.h"
#include "vector_class_mutation.h"
#include "vector_class_search.h"
#include "header_init_shapes.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT _strcmpi.
extern "C" int __cdecl _strcmpi(const char*, const char*);

// GLOBAL: GAMEMD 0xA8E348 -- every InfantryTypeClass.
extern DynamicVectorClass<InfantryTypeClass*> DAT_00A8E348;

// Two cell values: an empty cell and the 0x7FFF "no cell" marker.
struct CellPairStatic_00A8F28C
{
    CellStruct First;
    CellStruct Second;
    CellPairStatic_00A8F28C()
    {
        First = HeaderCellInit(0, 0);
        Second = HeaderCellInit(0x7FFF, 0x7FFF);
    }
    ~CellPairStatic_00A8F28C() {}
};

// FUNCTION: GAMEMD 0x5236A0
// PARTIAL: 80.5% (169 of 169 instructions, identical multiset). The only delta is the schedule of the inlined AddItem at the registry
// append: the canonical member loads Capacity first, retail loads Count first (the register roles and the cmp operand order then differ).
InfantryTypeClass::InfantryTypeClass(const char* id)
    : TechnoTypeClass(id, 0), ArrayIndex(-1), Pip(1), OccupyPip(7), Sequence(0), FireUp(0), FireProne(0),
      SecondaryFire(0), SecondaryProne(0), DeadBodies(0, 0), DeathAnims(0, 0), VoiceComment(0, 0),
      EnterWaterSound(-1), LeaveWaterSound(-1), Cyborg(false), NotHuman(false), Ivan(false),
      DetectionDistance(0), Occupier(false), Assaulter(false), HarvestRate(1), Fearless(false), Crawls(true),
      Infiltrate(false), Fraidycat(false), TiberiumProof(false), Civilian(false), C4(false), Engineer(false),
      Agent(false), Thief(false), VehicleThief(false), Doggie(false), Deployer(false), DeployedCrushable(true),
      UseOwnName(false), JumpJetTurn(false)
{
    vf_rtti_5();
    DAT_00A8E348.AddItem(this);
    ArrayIndex = DAT_00A8E348.FindItemIndex(this);
    OccupyWeapon.WeaponType = 0;
    OccupyWeapon.FLH = CoordStructInit(0, 0, 0);
    OccupyWeapon.BarrelLength = 0;
    OccupyWeapon.BarrelThickness = 0;
    OccupyWeapon.TurretLocked = false;
    EliteOccupyWeapon.WeaponType = 0;
    EliteOccupyWeapon.FLH = CoordStructInit(0, 0, 0);
    EliteOccupyWeapon.BarrelLength = 0;
    EliteOccupyWeapon.BarrelThickness = 0;
    EliteOccupyWeapon.TurretLocked = false;
    RotCount = 8;
    RadarVisible = false;
    Crushable = true;
    Repairable = false;
    Crewed = false;
    ImmuneToPsionics = false;
    ImmuneToPsionicWeapons = false;
    ImmuneToPoison = false;
    Parasiteable = true;
    Organic = true;
    ConsideredAircraft = false;
    Bunkerable = false;
    Sequence = new SequenceStruct[42];
    for (int i = 0; i < 42; i++) {
        Sequence[i].unknown_00 = 0;
        Sequence[i].unknown_04 = 0;
        Sequence[i].unknown_08[0] = 0;
        Sequence[i].unknown_08[1] = -1;
        Sequence[i].unknown_08[2] = 0;
    }
}

// FUNCTION: GAMEMD 0x523C20
// SYNTHETIC: GAMEMD 0x523C80 -- exit-time destructor stub of the static below
// GLOBAL: GAMEMD 0xA8F28C
// Return the lazily constructed pair; the argument is ignored.
CellStruct* InfantryTypeClass::vf_36(int)
{
    static CellPairStatic_00A8F28C instance;
    return &instance.First;
}

// FUNCTION: GAMEMD 0x523C90
int InfantryTypeClass::FUN_00523C90(const char* name)
{
    if (_strcmpi(name, "<none>") != 0 && _strcmpi(name, "none") != 0) {
        for (int i = 0; i < DAT_00A8E348.Count; i++) {
            if (_strcmpi(DAT_00A8E348.Items[i]->ID, name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x524790
int InfantryTypeClass::vf_45()
{
    return RulesInstance->IRepairStep;
}

// FUNCTION: GAMEMD 0x524D70
InfantryTypeClass::~InfantryTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A8E348.RemoveItem(this);
    delete Sequence;
    Sequence = 0;
}
