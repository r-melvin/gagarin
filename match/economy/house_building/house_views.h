// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   House-cluster-scoped ABI views shared by house_class_core.h / house_class_core.cpp. Nothing here claims to be a
//   canonical class: the real base classes and the helpers below are READ-ONLY dependencies bound by
//   address (the manifest rows). Facts were read from the retail gamemd.exe v1.001:
//     HouseClass RTTI .?AVHouseClass@@ (TD 0x824500): seven locators (COL 0x802A28 / 0x802918 /
//       0x802900 / 0x8028E8 / 0x8028D0 / 0x8028B8 / 0x8028A0) for the tables 0x7EA8A0 (primary, 24
//       slots) / 0x7EA884 (+0x04) / 0x7EA87C (+0x08) / 0x7EA874 (+0x0C) / 0x7EA834 (+0x24) /
//       0x7EA80C (+0x28) / 0x7EA7F4 (+0x2C); chain HouseClass -> AbstractClass -> IPersistStream ->
//       IPersist -> IUnknown, IRTTITypeInfo -> IUnknown, INoticeSink, INoticeSource, IHouse ->
//       IUnknown, IPublicHouse -> IUnknown, IConnectionPointContainer -> IUnknown.
//   The IPersistStream slots 0-7 are __stdcall with `this` on the stack; every other primary slot is
//   __thiscall. A virtual that overrides slots in several bases is compiled once, with `this` folded
//   to the first base that holds it, and the later bases reach it through `sub [esp+4], N; jmp`
//   adjustor thunks (the 0x510A20..0x510AF0 entries).
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_VIEWS_H

#include <stddef.h>
#include <windows.h>
#include <objidl.h>    // IStream, IPersistStream, CLSID, HRESULT (VC98 SDK, LIBRARY)
#include <ocidl.h>     // IConnectionPointContainer, IConnectionPoint (VC98 SDK, LIBRARY)
#include <oleauto.h>   // SysAllocString (VC98 SDK, LIBRARY)
#include <olectl.h>    // CONNECT_E_NOCONNECTION (VC98 SDK, LIBRARY)
#include "../../_rt/gg_static_assert.h"
#include "house_building_com_bases.h"
#include "house_building_com_bases.h"
#include "house_building_com_bases.h"

class HouseClusterView;

// Secondary base at +0x24: the IHouse table (0x7EA834, 15 slots). 0-2 IUnknown (thunks 0x510A50 /
// 0x510A60 / 0x510A70); slot 3 (0x4F6E60) and slot 4 (0x4F6950) are the same bodies IPublicHouse
// reaches through the 0x510AB0 / 0x510AC0 thunks, so both bases declare them under one name.
struct __declspec(novtable) HouseIHouseBase : public IUnknown
{
    virtual int __stdcall GetIndex() = 0;                         // 3   0x4F6E60
    virtual BSTR __stdcall GetName() = 0;                         // 4   0x4F6950
    virtual IUnknown* __stdcall GetMainInterface() = 0;           // 5   0x4F6930
    virtual int __stdcall GetCredits() = 0;                       // 6   0x4F6990
    virtual int __stdcall GetTiberiumStored() = 0;                // 7   0x4F69D0
    virtual int __stdcall GetPowerOutput() = 0;                   // 8   0x4F6A00
    virtual int __stdcall GetPowerDrain() = 0;                    // 9   0x4F6A10
    virtual int __stdcall CountOwnedOfCategory(int category) = 0; // 10  0x4F6A20
    virtual int __stdcall SumScoreOfCategory(int category) = 0;   // 11  0x4F6AE0
    virtual void* __stdcall GetBaseCenter(void* cell) = 0;        // 12  0x4F6BC0
    virtual int __stdcall SellAllBuildings() = 0;                 // 13  0x5013A0
    virtual int __stdcall DestroyAllTechnos() = 0;               // 14  0x501400
};
GG_STATIC_ASSERT(sizeof(HouseIHouseBase) == 4);

// Secondary base at +0x28: the IPublicHouse table (0x7EA80C, 9 slots). 0-2 IUnknown (thunks
// 0x510A80 / 0x510A90 / 0x510AA0), 3-4 shared with IHouse, 5-8 bodies 0x4F6A80 / 0x4F6B50 /
// 0x4F6D10 / 0x4F6910.
struct __declspec(novtable) HousePublicHouseBase : public IUnknown
{
    virtual int __stdcall GetIndex() = 0;                         // 3   0x4F6E60 (via 0x510AB0)
    virtual BSTR __stdcall GetName() = 0;                         // 4   0x4F6950 (via 0x510AC0)
    virtual int __stdcall PublicCountOwnedOfCategory(int category) = 0;   // 5   0x4F6A80
    virtual int __stdcall PublicSumScoreOfCategory(int category) = 0;     // 6   0x4F6B50
    virtual void* __stdcall PublicGetBaseCenter(void* cell) = 0;          // 7   0x4F6D10
    virtual bool __stdcall HasEnoughPower() = 0;                          // 8   0x4F6910
};
GG_STATIC_ASSERT(sizeof(HousePublicHouseBase) == 4);

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_VIEWS_H
