// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x6F3330 in retail gamemd.exe v1.001 (Techno.CPP range): picks the weapon
//   slot a techno uses against a target, from the two weapons' warheads and projectiles, the
//   target's kind (building, cell or other) and the owner's state. Result is a weapon index.

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"
#include "../_layout/warhead_type_class.h"
#include "weapon_type_class.h"
#include "bullet_type_class.h"

// GLOBAL: GAMEMD 0x7E2800 -- 0.0, read from memory rather than FLDZ.
extern const double DAT_007E2800;

static inline BuildingClass* AsBuilding(AbstractClass* object)
{
    return object->vf_11() == 6 ? (BuildingClass*)object : 0;
}

// FUNCTION: GAMEMD 0x6F3330
// The weapon index to use against a target.
int TechnoClass::vf_185(AbstractClass* target)
{
    if (vf_33()->FUN_00717880() && !vf_33()->IsGattling) {
        return CurrentWeaponNumber == -1 ? 0 : CurrentWeaponNumber;
    }
    if (!vf_256()) {
        WeaponTypeClass* secondary = vf_254(1)->WeaponType;
        if (secondary) {
            WeaponTypeClass* primary = vf_254(0)->WeaponType;
            if (primary && !secondary->unknown_136 && target) {
                if (InOpenToppedTransport && vf_33()->OpenTransportWeapon != -1) {
                    return vf_33()->OpenTransportWeapon;
                }
                TechnoClass* techno = target->Flags.IsTechno ? (TechnoClass*)target : 0;
                if (vf_33()->IsGattling) {
                    int stage = CurrentGattlingStage;
                    if (secondary->Projectile->unknown_2A4 && techno && techno->IsInAir()) {
                        return stage * 2 + 1;
                    }
                    return stage * 2;
                }
                if (secondary->Warhead->Airstrike) {
                    if (target->vf_11() == 6) {
                        if (AsBuilding(target)->Type->bools_1570[7]) {
                            if (AsBuilding(target)->vf_33()->ResourceDestination) {
                                if (!AsBuilding(target)->vf_33()->ResourceGatherer) {
                                    return 1;
                                }
                            } else {
                                return 1;
                            }
                        }
                    }
                } else {
                    if (primary->Warhead->IsLocomotor && techno && techno->vf_11() == 6) {
                        return 1;
                    }
                    if (secondary->unknown_142 && techno && techno->vf_33()->Drainable
                        && !DrainTarget && !Owner->FUN_004F9A90(techno)) {
                        return 1;
                    }
                    if (secondary->unknown_150 && vf_97() == 0x10) {
                        return 1;
                    }
                    if (vf_11() == 6 && ((BuildingClass*)this)->IsOverpowered) {
                        return 1;
                    }
                    if (target->vf_11() == 6 && Owner->CanOverpower((TechnoClass*)target)
                        && secondary->Warhead->ElectricAssault
                        && ((BuildingClass*)target)->Type->bools_1570[5]) {
                        return 1;
                    }
                    if (vf_11() == 2 && ((AircraftClass*)this)->IsKamikaze) {
                        return 1;
                    }
                    if (target->vf_11() == 0xB) {
                        CellClass* cell = (CellClass*)target;
                        if (((cell->LandType != 2 && target->IsOnFloor())
                                || ((cell->Flags & 0x100) && vf_33()->Naval))
                            && !target->IsInAir() && vf_33()->LandTargeting == 2) {
                            return 1;
                        }
                    }
                    if (techno) {
                        if (secondary->Warhead->Verses[techno->vf_33()->Armor] != DAT_007E2800) {
                            if (primary->Warhead->Verses[techno->vf_33()->Armor] == DAT_007E2800) {
                                return 1;
                            }
                            bool ground = techno->vf_111()->LandType == 2 || techno->vf_111()->LandType == 6;
                            if (techno->IsInAir()) {
                                ground = false;
                            }
                            if (!techno->OnBridge && ground) {
                                int weapon = vf_186((TechnoClass*)target);
                                if (weapon == -1) {
                                    weapon = 0;
                                }
                                return weapon;
                            } else {
                                if (!techno->IsInAir() && vf_33()->LandTargeting == 2) {
                                    return 1;
                                }
                                if (secondary->Projectile->unknown_2A4 && techno->IsInAir()) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
