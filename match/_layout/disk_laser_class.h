// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: DiskLaserClass default ctor 0x004A7A30 (chains AbstractClass ctor
//   0x00410170 at offset 0; stores the four vptrs 0x7E5FB8 / 0x7E5F9C /
//   0x7E5F94 / 0x7E5F8C and zeroes +0x24..+0x3C). sizeof: `PUSH 0x40` before
//   operator new in TClassFactory<DiskLaserClass>::CreateInstance 0x006C0E90.
//   Primary vtable 0x007E5FB8 overrides slots 3/5/6/8/11/12/13/23.
//   Owner / Target are the two ends compared by PointerGotInvalid 0x4A7900
//   (`CMP EDI,[ESI+0x24]` / `CMP EDI,[ESI+0x28]`), which stores -1 at +0x30.
//
// DiskLaserClass -- the Magnetron / disk-laser beam. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_DISK_LASER_CLASS_H
#define GG_MATCH_LAYOUT_DISK_LASER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"

// VTABLE: GAMEMD 0x007E5FB8  DiskLaserClass
// VTABLE: GAMEMD 0x007E5F9C  DiskLaserClass::(+0x04)
// VTABLE: GAMEMD 0x007E5F94  DiskLaserClass::(+0x08)
// VTABLE: GAMEMD 0x007E5F8C  DiskLaserClass::(+0x0C)
class DiskLaserClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x4A7A30 (declaration; default constructor)
    DiskLaserClass();
    // FUNCTION: GAMEMD 0x4A7AD0 (no-initialisation constructor)
    DiskLaserClass(const AbstractNoInit& noInit);
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x4A7C30
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x4A7B90
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x4A7C10
    virtual int vf_11();                                                  // 11  0x4A7C80
    virtual int vf_12();                                                  // 12  0x4A7C70
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x4A7B80
    virtual void vf_23();                                                 // 23  0x4A7340

    void*        Owner;          // +0x24 ctor 0
    void*        Target;         // +0x28 ctor 0
    int          unknown_2C;     // +0x2C ctor 0
    int          unknown_30;     // +0x30 ctor 0; PointerGotInvalid stores -1
    int          unknown_34;     // +0x34 ctor 0
    int          unknown_38;     // +0x38 ctor 0
    int          unknown_3C;     // +0x3C ctor 0
};
GG_STATIC_ASSERT(offsetof(DiskLaserClass, Owner)      == 0x24);
GG_STATIC_ASSERT(offsetof(DiskLaserClass, Target)     == 0x28);
GG_STATIC_ASSERT(offsetof(DiskLaserClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(DiskLaserClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(DiskLaserClass)               == 0x40);

#endif  // GG_MATCH_LAYOUT_DISK_LASER_CLASS_H
