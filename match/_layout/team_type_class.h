// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail vtable 0x7F47D0 (primary; +4 0x7F47B4, +8 0x7F47AC, +0xC 0x7F47A4) names
//   .?AVTeamTypeClass@@ in its locator. The constructor 0x6F06E0 initialises every
//   member from 0x98 to 0xF7, slot 12 (0x6F20B0) returns the object size 0xF8, and the
//   stream loader 0x6F1BB0 queues four pointer fields (+0xC4, +0xD0, +0xE0, +0xE4) for
//   swizzling. Field meanings past the pointer kinds are not proven, so they keep
//   offset-based names.
#ifndef GG_MATCH_LAYOUT_TEAM_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_TEAM_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "../core/vector_class.h"

class TeamTypeClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x6F06E0 (constructor)
    TeamTypeClass(const char* id);
    // The stream loader's in-place construction.
    TeamTypeClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}
    // FUNCTION: GAMEMD 0x6F08F0 (destructor; scalar deleting form 0x6F20D0)
    virtual ~TeamTypeClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6F1C40
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6F1BB0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6F1B90
    virtual void vf_10(void* target, bool removed);                       // 10  0x6F1030
    virtual int vf_11();                                                  // 11  0x6F20A0
    virtual int vf_12();                                                  // 12  0x6F20B0
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6F1C80
    virtual int vf_16();                                                  // 16  0x6F20C0
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x6F1090
    virtual bool vf_26(CCINIClass* ini);                                  // 26  0x6F1550

    int            ArrayIndex;      // +0x98  index in the type array
    int            Group;           // +0x9C
    int            unknown_A0;      // +0xA0
    bool           Flag_A4;         // +0xA4
    bool           Flag_A5;         // +0xA5
    bool           Flag_A6;         // +0xA6
    bool           Flag_A7;         // +0xA7
    bool           Flag_A8;         // +0xA8
    bool           Flag_A9;         // +0xA9
    bool           Flag_AA;         // +0xAA
    bool           Flag_AB;         // +0xAB
    bool           Flag_AC;         // +0xAC
    bool           Flag_AD;         // +0xAD
    bool           Flag_AE;         // +0xAE
    bool           Flag_AF;         // +0xAF
    bool           Flag_B0;         // +0xB0
    bool           Flag_B1;         // +0xB1
    bool           Flag_B2;         // +0xB2
    bool           Flag_B3;         // +0xB3
    int            unknown_B4;      // +0xB4
    int            unknown_B8;      // +0xB8
    int            unknown_BC;      // +0xBC
    int            unknown_C0;      // +0xC0
    AbstractClass* Ptr_C4;          // +0xC4
    int            unknown_C8;      // +0xC8
    int            unknown_CC;      // +0xCC
    AbstractClass* Ptr_D0;          // +0xD0
    int            unknown_D4;      // +0xD4
    int            unknown_D8;      // +0xD8
    int            unknown_DC;      // +0xDC
    AbstractClass* Ptr_E0;          // +0xE0
    AbstractClass* Ptr_E4;          // +0xE4
    int            unknown_E8;      // +0xE8
    int            unknown_EC;      // +0xEC
    bool           Flag_F0;         // +0xF0
    bool           Flag_F1;         // +0xF1
    bool           Flag_F2;         // +0xF2
    bool           Flag_F3;         // +0xF3
    bool           Flag_F4;         // +0xF4
    bool           Flag_F5;         // +0xF5
    bool           Flag_F6;         // +0xF6
    bool           Flag_F7;         // +0xF7
};

GG_STATIC_ASSERT(offsetof(TeamTypeClass, ArrayIndex) == 0x98);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Group) == 0x9C);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Flag_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Ptr_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Ptr_D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Ptr_E0) == 0xE0);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Ptr_E4) == 0xE4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Flag_F7) == 0xF7);
GG_STATIC_ASSERT(sizeof(TeamTypeClass) == 0xF8);

#endif
