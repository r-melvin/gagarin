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

struct MapClass
{
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
// placeholder virtuals (after MissionClass's slot 156) pad the table to slot 342 (+0x558).
struct InfantryView_5F5390 : InfantryClass
{
    virtual void vf_157();
    virtual void vf_158();
    virtual void vf_159();
    virtual void vf_160();
    virtual void vf_161();
    virtual void vf_162();
    virtual void vf_163();
    virtual void vf_164();
    virtual void vf_165();
    virtual void vf_166();
    virtual void vf_167();
    virtual void vf_168();
    virtual void vf_169();
    virtual void vf_170();
    virtual void vf_171();
    virtual void vf_172();
    virtual void vf_173();
    virtual void vf_174();
    virtual void vf_175();
    virtual void vf_176();
    virtual void vf_177();
    virtual void vf_178();
    virtual void vf_179();
    virtual void vf_180();
    virtual void vf_181();
    virtual void vf_182();
    virtual void vf_183();
    virtual void vf_184();
    virtual void vf_185();
    virtual void vf_186();
    virtual void vf_187();
    virtual void vf_188();
    virtual void vf_189();
    virtual void vf_190();
    virtual void vf_191();
    virtual void vf_192();
    virtual void vf_193();
    virtual void vf_194();
    virtual void vf_195();
    virtual void vf_196();
    virtual void vf_197();
    virtual void vf_198();
    virtual void vf_199();
    virtual void vf_200();
    virtual void vf_201();
    virtual void vf_202();
    virtual void vf_203();
    virtual void vf_204();
    virtual void vf_205();
    virtual void vf_206();
    virtual void vf_207();
    virtual void vf_208();
    virtual void vf_209();
    virtual void vf_210();
    virtual void vf_211();
    virtual void vf_212();
    virtual void vf_213();
    virtual void vf_214();
    virtual void vf_215();
    virtual void vf_216();
    virtual void vf_217();
    virtual void vf_218();
    virtual void vf_219();
    virtual void vf_220();
    virtual void vf_221();
    virtual void vf_222();
    virtual void vf_223();
    virtual void vf_224();
    virtual void vf_225();
    virtual void vf_226();
    virtual void vf_227();
    virtual void vf_228();
    virtual void vf_229();
    virtual void vf_230();
    virtual void vf_231();
    virtual void vf_232();
    virtual void vf_233();
    virtual void vf_234();
    virtual void vf_235();
    virtual void vf_236();
    virtual void vf_237();
    virtual void vf_238();
    virtual void vf_239();
    virtual void vf_240();
    virtual void vf_241();
    virtual void vf_242();
    virtual void vf_243();
    virtual void vf_244();
    virtual void vf_245();
    virtual void vf_246();
    virtual void vf_247();
    virtual void vf_248();
    virtual void vf_249();
    virtual void vf_250();
    virtual void vf_251();
    virtual void vf_252();
    virtual void vf_253();
    virtual void vf_254();
    virtual void vf_255();
    virtual void vf_256();
    virtual void vf_257();
    virtual void vf_258();
    virtual void vf_259();
    virtual void vf_260();
    virtual void vf_261();
    virtual void vf_262();
    virtual void vf_263();
    virtual void vf_264();
    virtual void vf_265();
    virtual void vf_266();
    virtual void vf_267();
    virtual void vf_268();
    virtual void vf_269();
    virtual void vf_270();
    virtual void vf_271();
    virtual void vf_272();
    virtual void vf_273();
    virtual void vf_274();
    virtual void vf_275();
    virtual void vf_276();
    virtual void vf_277();
    virtual void vf_278();
    virtual void vf_279();
    virtual void vf_280();
    virtual void vf_281();
    virtual void vf_282();
    virtual void vf_283();
    virtual void vf_284();
    virtual void vf_285();
    virtual void vf_286();
    virtual void vf_287();
    virtual void vf_288();
    virtual void vf_289();
    virtual void vf_290();
    virtual void vf_291();
    virtual void vf_292();
    virtual void vf_293();
    virtual void vf_294();
    virtual void vf_295();
    virtual void vf_296();
    virtual void vf_297();
    virtual void vf_298();
    virtual void vf_299();
    virtual void vf_300();
    virtual void vf_301();
    virtual void vf_302();
    virtual void vf_303();
    virtual void vf_304();
    virtual void vf_305();
    virtual void vf_306();
    virtual void vf_307();
    virtual void vf_308();
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
