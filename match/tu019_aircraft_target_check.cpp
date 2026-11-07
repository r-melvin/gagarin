// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x41A9E0 (ghidra CLI).
//
// AircraftClass movement-check helper: the base TechnoClass answer (slot 240) wins when non-zero; a loaded
// transport with nobody aboard answers 1; otherwise a non-fighter whose turret facing differs from the
// direction to the target by more than half a quadrant answers 2.
//
// Address index: 0x413D20, 0x41A9E0
//
// The constructor (0x413D20) runs the FootClass constructor, stores the type and the member defaults, then
// creates the locomotor through the smart pointer's CreateInstance (inlined on the member: CoCreateInstance,
// OleRun, QueryInterface, Release), links it, runs vf_9 and joins the aircraft list and the abstract index.

#include <stdlib.h>
#include "_layout/aircraft_class.h"
#include "_layout/aircraft_type_class.h"
#include "abstract_index_cast_sweep.h"
#include "vector_class_mutation.h"

// GLOBAL: GAMEMD 0xA8E390 -- every AircraftClass joins this list.
extern DynamicVectorClass<AircraftClass*> DAT_00A8E390;

// FUNCTION: GAMEMD 0x413D20
AircraftClass::AircraftClass(AircraftTypeClass* type, HouseClass* owner)
    : FootClass(owner),
      Type(type),
      ShouldLoseAmmo(0),
      HasPassengers(0),
      IsKamikaze(0),
      DockNowHeadingTo(0),
      unknown_bool_6D0(0),
      unknown_bool_6D1(0),
      IsLocked(0),
      NumParadropsLeft(5),
      IsCarryallNotLanding(1),
      IsReturningFromAttackRun(1)
{
    vf_rtti_5();
    if (Type) {
        Locomotor.CreateInstance(Type->Locomotor, 0, 7);
        Locomotor->LinkToObject(this);
    }
    vf_9();
    DAT_00A8E390.AddItem(this);
    AbstractIndex.AddIndex(vf_rtti_4(), this);
}

// FUNCTION: GAMEMD 0x41A9E0
int AircraftClass::FUN_0041A9E0(AbstractClass* target, int a2, bool a3)
{
    int result = TechnoClass::vf_240(target, a2, a3);
    if (result != 0)
        return result;
    if (HasPassengers && Passengers.FirstPassenger == 0)
        return 1;
    DirStruct scratch;
    DirStruct turret = *SecondaryFacing.FUN_004C93D0(&scratch);
    if (vf_07() == 0) {
        DirStruct* toTarget = FUN_005F3DB0(&scratch, target);
        short diff = (short)(turret.Raw - toTarget->Raw);
        if (abs(0x800) < abs(diff))
            return 2;
    }
    return 0;
}

// SYNTHETIC: GAMEMD 0x41C640 -- compiler-generated IRTTITypeInfo QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x41C650 -- compiler-generated IRTTITypeInfo AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x41C660 -- compiler-generated IRTTITypeInfo Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x41C670 -- compiler-generated IFlyControl QI adjustor thunk (this -= 0x6C0).
// SYNTHETIC: GAMEMD 0x41C680 -- compiler-generated IFlyControl AddRef adjustor thunk (this -= 0x6C0).
// SYNTHETIC: GAMEMD 0x41C690 -- compiler-generated IFlyControl Release adjustor thunk (this -= 0x6C0).
