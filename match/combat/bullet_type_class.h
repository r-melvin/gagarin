// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI-confirmed-inheritance
// Retail RTTI CHD identifies ObjectTypeClass as the direct base; field widths
// and accessed tail offsets are pinned below from the native Bullet methods.
#ifndef GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
#define GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_type_class.h"

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
    virtual void* vf_35(void* house);                             // slot 35, table 0x7E4948

    // Boolean fields: native 0x46BEE0 reads them through 0x5295F0;
    // 0x46C560 passes their bytes directly to Boolean checksum 0x4A1CA0.
    bool unknown_294;
    bool unknown_295;
    bool unknown_296;
    bool unknown_297;
    bool unknown_298;
    bool unknown_299;
    bool unknown_29A;
    bool unknown_29B;
    bool unknown_29C;
    bool unknown_29D;
    bool unknown_29E;
    bool unknown_29F;
    bool unknown_2A0;
    bool unknown_2A1;
    bool unknown_2A2;
    bool unknown_2A3;
    bool unknown_2A4;
    bool unknown_2A5;
    bool unknown_2A6;
    bool unknown_2A7;
    bool unknown_2A8;
    bool unknown_2A9;
    unsigned char unknown_2AA[2];
    int unknown_2AC;
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
    int unknown_2BC;
    bool unknown_2C0;
    unsigned char unknown_2C1[7];
    double unknown_2C8;
    int unknown_2D0;
    int unknown_2D4; // Native Color reader 0x474A90 at 0x46BFA5 uses a DWORD fallback.
    AnimTypeClass* unknown_2D8;
    int unknown_2DC;
    int unknown_2E0;
    int unknown_2E4;
    int ScaledSpawnDelay;
    bool unknown_2EC;
    unsigned char unknown_2ED[3];
    int unknown_2F0;
    unsigned char unknown_2F4;
    unsigned char unknown_2F5;
    unsigned char unknown_2F6;
    bool unknown_2F7;
};

GG_STATIC_ASSERT(sizeof(ObjectTypeClass) == 0x294);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_294) == 0x294);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_294) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_295) == 0x295);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_295) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_296) == 0x296);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_296) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_297) == 0x297);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_297) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_298) == 0x298);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_298) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_299) == 0x299);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_299) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29A) == 0x29A);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29A) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29B) == 0x29B);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29B) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29C) == 0x29C);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29C) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29D) == 0x29D);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29D) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29E) == 0x29E);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29E) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29F) == 0x29F);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29F) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A0) == 0x2A0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A0) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A1) == 0x2A1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A1) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A2) == 0x2A2);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A2) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A3) == 0x2A3);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A3) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A4) == 0x2A4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A5) == 0x2A5);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A5) == 1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A4) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A6) == 0x2A6);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A6) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A7) == 0x2A7);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A7) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A8) == 0x2A8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A8) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A9) == 0x2A9);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A9) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2AC) == 0x2AC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2AC) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, AirburstWeapon) == 0x2B0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->AirburstWeapon) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ShrapnelWeapon) == 0x2B4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ShrapnelWeapon) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ShrapnelCount) == 0x2B8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ShrapnelCount) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2BC) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C0) == 0x2C0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C0) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) == 0x2C1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C1) == 7);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) + 0 == 0x2C1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C1[0]) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) + 1 == 0x2C2);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C1) + 2 == 0x2C3);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C8) == 0x2C8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C8) == 8);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2D0) == 0x2D0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2D0) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2D4) == 0x2D4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2D4) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2D8) == 0x2D8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2D8) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2DC) == 0x2DC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2DC) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2E0) == 0x2E0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2E0) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2E4) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ScaledSpawnDelay) == 0x2E8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ScaledSpawnDelay) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2EC) == 0x2EC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2EC) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F0) == 0x2F0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F0) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F4) == 0x2F4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F4) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F5) == 0x2F5);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F5) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F6) == 0x2F6);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F6) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F7) == 0x2F7);
GG_STATIC_ASSERT(sizeof(BulletTypeClass) == 0x2F8);

template<class T> class DynamicVectorClass;
typedef DynamicVectorClass<BulletTypeClass*> BulletTypeVector;
// Shared storage is emitted in static_vector_dtor_stubs.cpp, where the
// canonical GLOBAL annotation lives. Consumers use its actual linker symbol.
extern BulletTypeVector DAT_00A83C80;

#endif  // GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
