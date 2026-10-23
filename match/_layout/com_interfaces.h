// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The game's COM-style interfaces in one place. Each name and class-key is
//   the retail RTTI TypeDescriptor's (all are ".?AU" structs except the two
//   notice interfaces, ".?AV" classes), and every interface's base list is its
//   class hierarchy descriptor's. Slot names are placeholders unless the slot
//   is a standard OLE method; argument counts come from RET n of each slot's
//   target.
//
//   Declared elsewhere and gathered here:
//     IRTTITypeInfo, INoticeSink, INoticeSource   abstract_interfaces.h
//     ILinkStream                                 i_link_stream.h
//     IHouse, IPublicHouse                        house_interfaces.h
//     ILocomotion, IPiggyback                     ../movement/loco_interfaces.h
//   IUnknown / IPersist / IPersistStream / IStream / IConnectionPointContainer
//   are the VC98 SDK's.
#ifndef GG_MATCH_LAYOUT_COM_INTERFACES_H
#define GG_MATCH_LAYOUT_COM_INTERFACES_H

#include <objidl.h>
#include <ocidl.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_interfaces.h"
#include "i_link_stream.h"
#include "house_interfaces.h"
#include "../movement/loco_interfaces.h"

// IFlyControl (".?AUIFlyControl@@", one base IUnknown): AircraftClass's second
// base at +0x6C0 (COL 0x7E2250 base offset 0x6C0). Table 0x7E2250: slots 0-2
// are AircraftClass's IUnknown adjustor thunks 0x41C670 / 0x41C680 / 0x41C690
// (this -= 0x6C0); slots 3-8 are 0x41B6A0 / 0x41B760 / 0x41B7D0 / 0x41B7F0 /
// 0x41B840 / 0x41B860, each RET 4 (no argument besides the interface).
struct __declspec(novtable) IFlyControl : public IUnknown
{
    virtual int __stdcall vf_03() = 0;   // 3
    virtual int __stdcall vf_04() = 0;   // 4
    virtual int __stdcall vf_05() = 0;   // 5
    virtual int __stdcall vf_06() = 0;   // 6
    virtual int __stdcall vf_07() = 0;   // 7
    virtual int __stdcall vf_08() = 0;   // 8
};
GG_STATIC_ASSERT(sizeof(IFlyControl) == 4);

#endif  // GG_MATCH_LAYOUT_COM_INTERFACES_H
