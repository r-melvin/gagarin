// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   SuperWeaponTypeClass construction for loading, destruction and stream loading, read off
//   retail gamemd.exe v1.001 (vtable 0x7F4090). /Ob2: the scalar deleting destructor
//   carries the destructor body inline.
//   Address index: 0x6CE700 no-init ctor, 0x6CE740 dtor, 0x6CE800 Load, 0x6CEFE0 deleting dtor.

#include <new.h>
#include <stdlib.h>
#include "../_layout/abstract_type_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"

// The members the stream loader touches; the rest of the class is not laid out here.
class SuperWeaponTypeClass : public AbstractTypeClass
{
public:
    SuperWeaponTypeClass(const AbstractNoInit& noInit);
    virtual ~SuperWeaponTypeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);      // 3   0x6CE7C0
    virtual HRESULT __stdcall Load(IStream* pStm);              // 5   0x6CE800
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty); // 6 0x6CE8D0
    virtual int vf_11();                                        // 11  0x6CE8F0
    virtual int vf_12();                                        // 12  0x6CE900
    char unknown_98[0x4];
    void* unknown_9C;           // +0x9C
    char unknown_A0[0x18];
    void* AltImage;             // +0xB8
    char unknown_BC[0xC];
    void* unknown_C8;           // +0xC8
    char CameoFile[0x19];       // +0xCC
};
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, AltImage) == 0xB8);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, CameoFile) == 0xCC);

// GLOBAL: GAMEMD 0xA8E330 -- the super weapon type registry.
extern DynamicVectorClass<SuperWeaponTypeClass*> DAT_00A8E330;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;
// STRING: GAMEMD 0x81834C -- ".SHP".
extern const char STR_0081834C[];
// STRING: GAMEMD 0x8204FC -- "XXICON.SHP".
extern const char STR_DEFAULT_ICON[];

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- loads a shape file by path.
void* __fastcall FUN_005B40B0(const char* name, bool flag);

// FUNCTION: GAMEMD 0x6CE700
SuperWeaponTypeClass::SuperWeaponTypeClass(const AbstractNoInit& noInit)
    : AbstractTypeClass(noInit), AltImage(0)
{
}

// FUNCTION: GAMEMD 0x6CE740
SuperWeaponTypeClass::~SuperWeaponTypeClass()
{
    DAT_00A8E330.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6CE800
// Reads the stream, rebuilds the object in place and reloads the cameo shape.
HRESULT __stdcall SuperWeaponTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) SuperWeaponTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_9C);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_C8);
    char path[0x200];
    _makepath(path, 0, 0, CameoFile, STR_0081834C);
    AltImage = FUN_005B40B0(path, false);
    if (AltImage == 0) {
        AltImage = FUN_005B40B0(STR_DEFAULT_ICON, false);
    }
    return 0;
}

// SYNTHETIC: GAMEMD 0x6CEFE0
// SuperWeaponTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
