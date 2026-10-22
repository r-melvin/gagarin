// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The COM secondary bases every AbstractClass-derived object of the module carries after its
//   IPersistStream primary base (HouseClass, HouseTypeClass, BuildingTypeClass, BuildingClass), declared
//   once. Needs the VC98 SDK's objidl.h (HRESULT, REFIID).
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_COM_BASES_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_COM_BASES_H

#include <objidl.h>   // HRESULT, REFIID, ULONG (VC98 SDK, LIBRARY)
#include "../../_rt/gg_static_assert.h"

// Secondary base at +0x04: the IRTTITypeInfo table (6 slots). Slots 0-2 are the IUnknown adjustor
// thunks, slots 3-5 the bodies 0x410210 / 0x410220 / 0x410230, implemented once for every object and
// compiled with the subobject `this` (read-only here). Slot 5 stores the id (global 0xA8B230 based)
// into the subobject's +0x0C; the type constructors call it once, bound directly.
struct HBRttiBase
{
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0
    virtual ULONG __stdcall AddRef();                                     // 1
    virtual ULONG __stdcall Release();                                    // 2
    virtual int __stdcall What_Am_I();                                    // 3  0x410210
    virtual int __stdcall Fetch_ID();                                     // 4  0x410220
    virtual void __stdcall Create_ID();                                   // 5  0x410230
};
GG_STATIC_ASSERT(sizeof(HBRttiBase) == 4);

// Secondary base at +0x08: INoticeSink table, one slot (0x410580: `XOR AL,AL; RET 8`).
struct HBNoticeSinkBase
{
    virtual bool __stdcall NoticeSink(int arg);   // 0  0x410580
};
GG_STATIC_ASSERT(sizeof(HBNoticeSinkBase) == 4);

// Secondary base at +0x0C: INoticeSource table, one slot (0x410590: bare `RET 4`).
struct HBNoticeSourceBase
{
    virtual void __stdcall NoticeSource();   // 0  0x410590
};
GG_STATIC_ASSERT(sizeof(HBNoticeSourceBase) == 4);

#endif
