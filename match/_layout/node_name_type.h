// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing NodeNameType declaration extracted unchanged from netshare_slot_nodes.h.
// RTTI7EE370/7EE390 confirms vector pointee name; native allocation5E87A0
// and existing offset assertions pin this byte-packed record.
#ifndef GG_MATCH_LAYOUT_NODE_NAME_TYPE_H
#define GG_MATCH_LAYOUT_NODE_NAME_TYPE_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ipx_address_class.h"
#pragma pack(push, 1)
// ---------------------------------------------------------------------------
// One lobby player slot entry. 133 bytes, byte-packed.
// ---------------------------------------------------------------------------
struct NodeNameType
{
    wchar_t Name[20];                 // +0x00
    IPXAddressClass Address;          // +0x28
    unsigned char unknown_34[0x17];   // +0x34
    int unknown_4B;                   // +0x4B  set to 1 by 0x796FC0
    unsigned char unknown_4F[0x04];   // +0x4F
    int unknown_53;                   // +0x53  set to 2 by 0x796FC0
    unsigned char unknown_57[0x14];   // +0x57
    int unknown_6B;                   // +0x6B  (-1 == observer)
    unsigned char unknown_6F[0x08];   // +0x6F
    int unknown_77;                   // +0x77  tested against 1 at 0x5EA905 and 0x5EA3A5, cleared at 0x5E98DD
    int unknown_7B;                   // +0x7B  set to -1 by 0x796FC0
    int unknown_7F;                   // +0x7F  stored by 0x5E3A36 (0 = no map, 2 = map transfer)
    unsigned char unknown_83[0x02];   // +0x83

    // Declaration: GAMEMD 0x696F20 (decl; reloc) -- __thiscall, no arguments: a
    // choice reader (the fallback of 0x46F810).
    int FUN_00696F20();
    // Declaration: GAMEMD 0x696F50 (decl; reloc) -- __thiscall, no arguments: a
    // choice reader (the fallback of 0x46F880).
    int FUN_00696F50();
    // Declaration: GAMEMD 0x696F90 (decl; reloc) -- __thiscall, one argument: store
    // a choice pair at +0x4B/+0x4F (-2 stores 0 and -2, anything else stores the
    // value and -1); called with the start-position control's value.
    void FUN_00696F90(int value);
    // Declaration: GAMEMD 0x696FC0 (decl; reloc) -- __thiscall, one argument: the
    // same pair store at +0x53/+0x57 (-2 stores -1 and -2).
    void FUN_00696FC0(int value);
    // Declaration: GAMEMD 0x696FF0 (decl; reloc) -- __thiscall, one argument: the
    // same pair store at +0x5B/+0x5F.
    void FUN_00696FF0(int value);
    // Declaration: GAMEMD 0x697020 (decl; reloc) -- __thiscall, one argument: the
    // same pair store at +0x63/+0x67.
    void FUN_00697020(int value);
};
#pragma pack(pop)

GG_STATIC_ASSERT(offsetof(NodeNameType, Address) == 0x28 &&
                 offsetof(NodeNameType, unknown_34) == 0x34 &&
                 offsetof(NodeNameType, unknown_4B) == 0x4B &&
                 offsetof(NodeNameType, unknown_53) == 0x53 &&
                 offsetof(NodeNameType, unknown_6B) == 0x6B &&
                 offsetof(NodeNameType, unknown_7B) == 0x7B &&
                 offsetof(NodeNameType, unknown_77) == 0x77 &&
                 offsetof(NodeNameType, unknown_7F) == 0x7F &&
                 sizeof(NodeNameType) == 0x85);
#endif
