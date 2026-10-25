// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The two COM interfaces HouseClass implements besides IConnectionPointContainer.
//   RTTI names both `.?AU` structs with a single IUnknown base (CHD at COL
//   0x802A28: IHouse at +0x24, IPublicHouse at +0x28). Slot names are
//   placeholders; argument counts come from RET n of each slot's target:
//     IHouse table 0x7EA834: slots 3-9 and 13-14 RET 4, 10-12 RET 8;
//     IPublicHouse table 0x7EA80C: slots 3-4 are adjustor thunks 0x510AB0 /
//     0x510AC0 onto IHouse 3-4 (0x4F6E60 / 0x4F6950: one shared override),
//     5-7 RET 8, 8 RET 4.
//   IHouse slot 8 (0x4F6A00, returns the dword at interface +0x5380 = House +0x53A4) and
//   IPublicHouse slot 8 (0x4F6910, a different body) are two implementations,
//   so the two slots carry interface-specific names and a class overrides each
//   separately. IPublicHouse 5-7 are named per interface for the same reason.
//   Bounded native entry reads establish the pointer/BSTR returns below and
//   the byte bool result at 0x4F6910. Other return contracts remain provisional.
//   IHouse slot 14 is stdcall (stack receiver, RET 4 at 0x501400), distinct
//   from AbstractClass::vf_14 thiscall (0x410490); its placeholder is qualified
//   by interface to permit both native contracts on one actual class.
#ifndef GG_MATCH_LAYOUT_HOUSE_INTERFACES_H
#define GG_MATCH_LAYOUT_HOUSE_INTERFACES_H

#include <unknwn.h>
#include <wtypes.h>

struct IHouse : public IUnknown
{
    virtual HRESULT __stdcall vf_03() = 0;                      // 3  0x4F6E60
    virtual BSTR __stdcall vf_04() = 0;                         // 4  0x4F6950
    virtual IUnknown* __stdcall vf_05() = 0;                    // 5  0x4F6930
    virtual HRESULT __stdcall vf_06() = 0;                      // 6  0x4F6990
    virtual HRESULT __stdcall vf_07() = 0;                      // 7  0x4F69D0
    virtual HRESULT __stdcall IHouse_vf_08() = 0;               // 8  0x4F6A00
    virtual HRESULT __stdcall vf_09() = 0;                      // 9  0x4F6A10
    virtual HRESULT __stdcall vf_10(int a1) = 0;                // 10 0x4F6A20
    virtual HRESULT __stdcall vf_11(int a1) = 0;                // 11 0x4F6AE0
    virtual void* __stdcall vf_12(void* a1) = 0;                // 12 0x4F6BC0
    virtual HRESULT __stdcall vf_13() = 0;                      // 13 0x5013A0
    virtual HRESULT __stdcall IHouse_vf_14() = 0;               // 14 0x501400
};

struct IPublicHouse : public IUnknown
{
    virtual HRESULT __stdcall vf_03() = 0;                      // 3 (shared with IHouse 3)
    virtual BSTR __stdcall vf_04() = 0;                         // 4 (shared with IHouse 4)
    virtual HRESULT __stdcall IPublicHouse_vf_05(int a1) = 0;   // 5  0x4F6A80
    virtual HRESULT __stdcall IPublicHouse_vf_06(int a1) = 0;   // 6  0x4F6B50
    virtual void* __stdcall IPublicHouse_vf_07(void* a1) = 0;   // 7  0x4F6D10
    virtual bool __stdcall IPublicHouse_vf_08() = 0;            // 8  0x4F6910
};

#endif  // GG_MATCH_LAYOUT_HOUSE_INTERFACES_H
