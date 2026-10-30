// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0083F8A8 `.?AVSideClass@@`; class hierarchy descriptor 0x008094B0.
//   Bases in RTTI (declaration) order: AbstractTypeClass +0x0.
// VTABLE: GAMEMD 0x7F2EC0 (27 slots)
// VTABLE: GAMEMD 0x7F2EA4 (6 slots, subobject +0x4)
// VTABLE: GAMEMD 0x7F2E9C (1 slots, subobject +0x8)
// VTABLE: GAMEMD 0x7F2E94 (1 slots, subobject +0xC)
//   Allocation: operator new (0x7C8E17) of 0xB4 bytes at 0x475729, 0x67249C, 0x6BFE3C.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_SIDE_CLASS_H
#define GG_MATCH_LAYOUT_SIDE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "../core/type_list.h"

class SideClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x006A4550 (decl; reloc) -- name argument, null for the factory.
    SideClass(const char* id = 0);
    virtual HRESULT __stdcall GetClassID(CLSID *pClassID);      // 3  0x6A4740: override (SDK declaration)
    virtual HRESULT __stdcall Load(IStream* pStm);              // 5  0x6A4780: override (declaration from the base header)
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);// 6  0x6A48A0: override (declaration from the base header)
    virtual ~SideClass();                                       // 8  0x6A4930: deleting destructor override
    virtual int vf_11();                                        // 11  0x6A4920: override (declaration from the base header)
    virtual int vf_12();                                        // 12  0x6A4910: override (declaration from the base header)
    virtual void vf_13(struct Obj_004A1D30 *);                  // 13  0x6A4710: override of AbstractTypeClass
    TypeList<int> unknown_98;  // +0x98; +0xB0 tail meaning remains unknown.

};
typedef TypeList<int> SideTypeList;
GG_STATIC_ASSERT(offsetof(SideClass, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(SideClass, unknown_98) + offsetof(SideTypeList, Items) == 0x9C);
GG_STATIC_ASSERT(offsetof(SideClass, unknown_98) + offsetof(SideTypeList, Count) == 0xA8);
GG_STATIC_ASSERT(sizeof(((SideClass*)0)->unknown_98.Items) == 4);
GG_STATIC_ASSERT(sizeof(((SideClass*)0)->unknown_98.Count) == 4);
GG_STATIC_ASSERT(sizeof(((SideClass*)0)->unknown_98) == 0x1C);
GG_STATIC_ASSERT(sizeof(SideClass) == 0xB4);

#endif  // GG_MATCH_LAYOUT_SIDE_CLASS_H
