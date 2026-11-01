// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI-confirmed-inheritance
// Retail RTTI CHD identifies ObjectTypeClass as the direct base; field widths
// and accessed tail offsets are pinned below from the native Bullet methods.
#ifndef GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
#define GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/object_type_class.h"

class HouseClass;
class AnimTypeClass;
class WeaponTypeClass;

class BulletTypeClass : public ObjectTypeClass
{
public:
    // CALLEE: GAMEMD 0x0046BBC0 (decl; reloc) -- constructor as the class factory calls it.
    BulletTypeClass(int unknown_arg0 = 0);
    // The four native primary/COM tables have complete-object offsets 0, 4,
    // 8 and 0xC, respectively.  The offsets and targets are checked against
    // the retail RTTI and table contents by the constructor evidence packet.
    // VTABLE: GAMEMD 0x7E4948
    // VTABLE: GAMEMD 0x7E492C
    // VTABLE: GAMEMD 0x7E4924
    // VTABLE: GAMEMD 0x7E491C

    // Native no-init construction forwards this argument to ObjectTypeClass.
    BulletTypeClass(const AbstractNoInit& noInit);
    // Native construction with an identifier delegates to ObjectTypeClass(id)
    // and registers the completed object in the two native pointer vectors.
    BulletTypeClass(const char* id);

    // Slot 8 in the primary table is the native scalar-deleting entry at
    // 0x46C890, generated from the ordinary destructor body at 0x46BE10.
    virtual ~BulletTypeClass();

    // Native overrides are declared here to preserve the four emitted tables.
    // Their source bodies remain in their existing providers or unclaimed.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID); // slot 3, 0x46C750
    virtual HRESULT __stdcall Load(IStream* pStm);         // slot 5, 0x46C6A0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL clearDirty); // slot 6, 0x46C730
    virtual void vf_10(void* target, bool removed);        // slot 10, 0x46C820
    virtual int vf_11();                                   // slot 11, 0x46C850
    virtual int vf_12();                                   // slot 12, 0x46C860
    virtual void vf_13(Obj_004A1D30* crc);                 // slot 13, 0x46C560
    virtual bool vf_25(CCINIClass* ini);                   // slot 25, 0x46BEE0
    virtual CoordStruct vf_27(const CoordStruct& coord);   // slot 27, 0x46C4F0

    // STATIC: GAMEMD 0x46C790 (__fastcall)
    static BulletTypeClass* FindOrAllocate(const char* id);
    // Implemented at the native address 0x46C840 in the owning source TU.
    void SetScaledSpawnDelay(int delay);

    // ObjectTypeClass's two pure slots have concrete BulletType table entries.
    virtual bool vf_32(const CellStruct* cell, HouseClass* house); // slot 32, table 0x7E4948
    virtual ObjectClass* vf_35(HouseClass* house);                             // slot 35, table 0x7E4948

    // Boolean fields: native 0x46BEE0 reads them through 0x5295F0;
    // 0x46C560 passes their bytes directly to Boolean checksum 0x4A1CA0.
    bool Airburst;
    bool Floater;
    bool SubjectToCliffs;
    bool SubjectToElevation;
    bool SubjectToWalls;
    bool VeryHigh;
    bool Shadow;
    bool Arcing;
    bool Dropping;
    bool Level;
    bool Inviso;
    bool Proximity;
    bool Ranged;
    bool Rotates;
    bool Inaccurate;
    bool FlakScatter;
    bool AA;
    bool AG;
    bool Degenerates;
    bool Bouncy;
    bool AnimPalette;
    bool FirersPalette;
    unsigned char unknown_2AA[2];
    int Cluster;
    // FUNCTION 0x46BEE0 reads the AirburstWeapon INI key at 0x81B04C,
    // resolves it through the WeaponTypeClass factory at 0x772FA0, and writes
    // its result here at 0x46C2DB.
    WeaponTypeClass* AirburstWeapon; // +0x2B0
    // The native INI writer at 0x46C2E1..0x46C31F reads key "ShrapnelWeapon"
    // (STRING 0x81B03C), resolves it with WeaponTypeClass::FindOrAllocate
    // (0x772FA0), and stores its returned pointer here.
    WeaponTypeClass* ShrapnelWeapon;  // +0x2B4
    // The native INI writer at 0x46C310..0x46C32A reads/writes the DWORD value for
    // INI key "ShrapnelCount" (STRING 0x81B02C).
    int ShrapnelCount;               // +0x2B8
    int DetonationAltitude;
    bool Vertical;
    unsigned char unknown_2C1[7];
    double Elasticity;
    int Acceleration;
    int Color; // Native Color reader 0x474A90 at 0x46BFA5 uses a DWORD fallback.
    AnimTypeClass* Trailer;
    int ROT;
    int CourseLockDuration;
    int SpawnDelay;
    int ScaledSpawnDelay;
    bool Scalable;
    unsigned char unknown_2ED[3];
    int Arm;
    unsigned char AnimLow;
    unsigned char AnimHigh;
    unsigned char AnimRate;
    bool Flat;
};

GG_STATIC_ASSERT(sizeof(ObjectTypeClass) == 0x294);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Airburst) == 0x294);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Airburst) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Floater) == 0x295);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Floater) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, SubjectToCliffs) == 0x296);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->SubjectToCliffs) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, SubjectToElevation) == 0x297);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->SubjectToElevation) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, SubjectToWalls) == 0x298);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->SubjectToWalls) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, VeryHigh) == 0x299);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->VeryHigh) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Shadow) == 0x29A);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Shadow) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Arcing) == 0x29B);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Arcing) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Dropping) == 0x29C);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Dropping) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Level) == 0x29D);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Level) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Inviso) == 0x29E);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Inviso) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Proximity) == 0x29F);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Proximity) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Ranged) == 0x2A0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Ranged) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Rotates) == 0x2A1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Rotates) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Inaccurate) == 0x2A2);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Inaccurate) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, FlakScatter) == 0x2A3);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->FlakScatter) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AA) == 0x2A4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AG) == 0x2A5);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AG) == 1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AA) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Degenerates) == 0x2A6);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Degenerates) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Bouncy) == 0x2A7);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Bouncy) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AnimPalette) == 0x2A8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AnimPalette) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, FirersPalette) == 0x2A9);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->FirersPalette) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Cluster) == 0x2AC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Cluster) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AirburstWeapon) == 0x2B0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AirburstWeapon) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ShrapnelWeapon) == 0x2B4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ShrapnelWeapon) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ShrapnelCount) == 0x2B8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ShrapnelCount) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, DetonationAltitude) == 0x2BC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->DetonationAltitude) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Vertical) == 0x2C0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Vertical) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) == 0x2C1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C1) == 7);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) + 0 == 0x2C1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C1[0]) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) + 1 == 0x2C2);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) + 2 == 0x2C3);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Elasticity) == 0x2C8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Elasticity) == 8);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Acceleration) == 0x2D0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Acceleration) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Color) == 0x2D4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Color) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Trailer) == 0x2D8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Trailer) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ROT) == 0x2DC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ROT) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, CourseLockDuration) == 0x2E0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->CourseLockDuration) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, SpawnDelay) == 0x2E4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->SpawnDelay) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ScaledSpawnDelay) == 0x2E8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ScaledSpawnDelay) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Scalable) == 0x2EC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Scalable) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Arm) == 0x2F0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->Arm) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AnimLow) == 0x2F4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AnimLow) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AnimHigh) == 0x2F5);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AnimHigh) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AnimRate) == 0x2F6);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AnimRate) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Flat) == 0x2F7);
GG_STATIC_ASSERT(sizeof(BulletTypeClass) == 0x2F8);

template<class T> class DynamicVectorClass;
typedef DynamicVectorClass<BulletTypeClass*> BulletTypeVector;
// Shared storage is emitted in static_vector_dtor_stubs.cpp, where the
// canonical GLOBAL annotation lives. Consumers use its actual linker symbol.
extern BulletTypeVector DAT_00A83C80;

#endif  // GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
