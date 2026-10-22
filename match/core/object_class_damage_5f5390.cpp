// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// ObjectClass slot 91 (0x5F5390): apply damage to the object and report the
// outcome (0 none, 1 hurt, 2 below half, 3 below the rules ratio, 4 destroyed,
// 5 the object died during a tag event).
#include "../_layout/object_class.h"
#include "../_layout/object_type_class.h"
#include "../_layout/anim_class.h"
#include "../_layout/infantry_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/building_class.h"

class MapClass
{
public:
    // FUNCTION: GAMEMD 0x489180 (declaration) -- the damage after armour and distance.
    static int __fastcall FUN_00489180(int damage, void* warhead, int armor, int distance);
};

struct AnimCallView
{
    // FUNCTION: GAMEMD 0x424B50 (declaration) -- set the anim's owner object.
    void FUN_00424B50(ObjectClass* owner);
};

// The rules fields read here.
struct RulesView_5F5390
{
    char           unknown_0000[0x9C];
    AnimTypeClass* unknown_009C;     // +0x9C  the anim for a cyborg brought down
    char           unknown_00A0[0x1708 - 0xA0];
    double         unknown_1708;     // +0x1708  the health ratio for result 3
};
GG_STATIC_ASSERT(offsetof(RulesView_5F5390, unknown_009C) == 0x9C);
GG_STATIC_ASSERT(offsetof(RulesView_5F5390, unknown_1708) == 0x1708);
// GLOBAL: GAMEMD 0x8871E0
extern RulesView_5F5390* DAT_008871E0;

// The InfantryClass members reached after slot 11 reports 0xF. The
// placeholder virtuals pad the table from the last slot RadioClass and TechnoClass declare
// to slot 342 (+0x558).
struct InfantryView_5F5390 : InfantryClass
{
    virtual void vf_309();
    virtual void vf_310();
    virtual void vf_311();
    virtual void vf_312();
    virtual void vf_313();
    virtual void vf_314();
    virtual void vf_315();
    virtual void vf_316();
    virtual void vf_317();
    virtual void vf_318();
    virtual void vf_319();
    virtual void vf_320();
    virtual void vf_321();
    virtual void vf_322();
    virtual void vf_323();
    virtual void vf_324();
    virtual void vf_325();
    virtual void vf_326();
    virtual void vf_327();
    virtual void vf_328();
    virtual void vf_329();
    virtual void vf_330();
    virtual void vf_331();
    virtual void vf_332();
    virtual void vf_333();
    virtual void vf_334();
    virtual void vf_335();
    virtual void vf_336();
    virtual void vf_337();
    virtual void vf_338();
    virtual void vf_339();
    virtual void vf_340();
    virtual void vf_341();
    virtual void vf_342(int a1, bool a2, int a3);
};

// The InfantryTypeClass fields read here.
struct InfantryTypeView_5F5390
{
    char unknown_0000[0xA0];
    int  Strength;                   // +0xA0
    char unknown_00A4[0xEAC - 0xA4];
    bool Cyborg;                     // +0xEAC
};
GG_STATIC_ASSERT(offsetof(InfantryTypeView_5F5390, Cyborg) == 0xEAC);

// The BuildingTypeClass field read here.
struct BuildingTypeView_5F5390
{
    char unknown_0000[0x1577];
    bool unknown_1577;               // +0x1577
};
GG_STATIC_ASSERT(offsetof(BuildingTypeView_5F5390, unknown_1577) == 0x1577);

// The object as a building when slot 11 reports 6, otherwise null.
static inline BuildingClass* AsBuilding(ObjectClass* object)
{
    return object->vf_11() == 6 ? (BuildingClass*)object : 0;
}

// GLOBAL: GAMEMD 0xAC1360 -- the cell passed with every tag event here.
extern CellStruct DAT_00AC1360;


// FUNCTION: GAMEMD 0x5F5390
// PARTIAL 76.1% (94.6% aligned): every exit after a tag event that killed the
// object shares one `return 5` epilogue, reached here through `died`. The
// remaining delta is the last of those exits: retail branches to the shared
// block and re-reads Health; cl lays the block out in line there. Tried nested
// tests and an else-if on the Health == 0 test (both 76.1%).
int ObjectClass::vf_91(int* damage, int distance, void* warhead, void* source, bool a5, bool a6, void* house)
{
    int result = 0;
    int health = Health;
    if (health > 0 && *damage != 0 && (a5 || !vf_34()->Immune)) {
        int strength = vf_34()->Strength;
        if (!a5) {
            *damage = MapClass::FUN_00489180(*damage, warhead, vf_34()->Armor, distance);
        }
        if (this != 0 && vf_11() == 6 && !((BuildingTypeView_5F5390*)AsBuilding(this)->Type)->unknown_1577) {
            *damage = *damage < 1 ? 1 : *damage;
        }
        if (*damage == 0) {
            return 0;
        }
        if (*damage < 0) {
            int old = Health;
            Health = old - *damage;
            if (Health > strength) {
                Health = strength;
            }
            if (old != Health) {
                vf_82(7);
            }
            return 0;
        }

        result = 1;
        if (health > *damage) {
            if (health >= strength >> 1 && health - *damage < strength >> 1) {
                result = 2;
            }
        } else {
            *damage = health;
        }
        double threshold = strength * DAT_008871E0->unknown_1708;
        if (health > threshold && health - *damage < threshold) {
            result = 3;
        }
        Health = health - *damage;
        if (Health <= 0 && vf_11() == 0xF && !a5) {
            InfantryView_5F5390* infantry = (InfantryView_5F5390*)this;
            if (((InfantryTypeView_5F5390*)infantry->Type)->Cyborg && !infantry->Crawling) {
                new AnimClass(DAT_008871E0->unknown_009C, CoordStruct(Location), 0, 1, 0x600, 0, false);
                Health = (int)(((InfantryTypeView_5F5390*)infantry->Type)->Strength * 0.25);
                Health = Health > 1 ? Health : 1;
                infantry->Crawling = true;
                infantry->vf_342(6, true, 0);
                result = 3;
            }
        }

        int newHealth = Health;
        if (result == 2) {
            if (source != 0 && AttachedTag != 0) {
                ((TagClass*)AttachedTag)->FUN_006E53A0(0x27, this, DAT_00AC1360, false, 0);
            }
            if (!IsAlive) {
                goto died;
            }
            if (AttachedTag != 0) {
                ((TagClass*)AttachedTag)->FUN_006E53A0(0x2A, this, DAT_00AC1360, false, 0);
            }
        }
        if (!IsAlive) {
            goto died;
        }
        if (result == 3) {
            if (source != 0 && AttachedTag != 0) {
                ((TagClass*)AttachedTag)->FUN_006E53A0(0x28, this, DAT_00AC1360, false, 0);
            }
            if (!IsAlive) {
                goto died;
            }
            if (AttachedTag != 0) {
                ((TagClass*)AttachedTag)->FUN_006E53A0(0x2B, this, DAT_00AC1360, false, 0);
            }
        }
        if (!IsAlive) {
            goto died;
        }
        if (Health != health && vf_34() != 0 && health == vf_34()->Strength) {
            if (source != 0 && AttachedTag != 0) {
                ((TagClass*)AttachedTag)->FUN_006E53A0(0x26, this, DAT_00AC1360, false, 0);
            }
            if (AttachedTag != 0 && IsAlive) {
                ((TagClass*)AttachedTag)->FUN_006E53A0(0x29, this, DAT_00AC1360, false, 0);
            }
            if (AttachedTag != 0) {
                if (!IsAlive) {
                    goto died;
                }
                if (source != 0) {
                    ((TagClass*)AttachedTag)->FUN_006E53A0(0x29, this, DAT_00AC1360, false, (int)source);
                }
            }
        }
        if (!IsAlive) {
            goto died;
        }
        if (newHealth > 0 && Health <= 0) {
            goto died;
        } else if (Health == 0) {
            void* owner = 0;
            if (source != 0) {
                owner = ((TechnoClass*)source)->Owner;
            }
            if (house == 0 || (source != 0 && house == owner)) {
                vf_56(source);
            } else {
                vf_57(house);
            }
            result = 4;
            vf_55(1);
        }
        if (IsAlive) {
            if (source != 0 && AttachedTag != 0 && result != 4) {
                ((TagClass*)AttachedTag)->FUN_006E53A0(6, this, DAT_00AC1360, false, (int)source);
            }
            if (IsAlive) {
                if (source != 0 && AttachedTag != 0 && result != 4) {
                    ((TagClass*)AttachedTag)->FUN_006E53A0(0x2C, this, DAT_00AC1360, false, (int)source);
                }
                if (IsAlive && result != 0 && IsSelected) {
                    vf_73(2);
                }
            }
        }
    }
    return result;

died:
    return 5;
}
