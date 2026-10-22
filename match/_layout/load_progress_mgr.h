// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x00829898 `.?AVLoadProgressMgr@@`; class hierarchy descriptor 0x00804F00.
//   Bases in RTTI (declaration) order: INoticeSink +0x0.
// VTABLE: GAMEMD 0x7ECF64 (1 slots)
//   Allocation: operator new (0x7C8E17) of 0x64 bytes at 0x552A4C.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_LOAD_PROGRESS_MGR_H
#define GG_MATCH_LAYOUT_LOAD_PROGRESS_MGR_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_interfaces.h"

class LoadProgressMgr : public INoticeSink
{
public:
    virtual bool Notice(int id, int arg);                       // 0  0x554400: override (declaration from the base header)
    int unknown_04;  // +0x4 store at 0x552ADA
    int unknown_08;  // +0x8 store at 0x552ADD
    unsigned char unknown_0C[48];  // +0xC
    int unknown_3C;  // +0x3C store at 0x552AE0
    int unknown_40;  // +0x40 store at 0x552AE3
    int unknown_44;  // +0x44 store at 0x552AE6
    int unknown_48;  // +0x48 store at 0x552AE9
    int unknown_4C;  // +0x4C store at 0x552AEC
    unsigned char unknown_50;  // +0x50 store at 0x552AEF
    unsigned char unknown_51;  // +0x51 store at 0x552AF2
    unsigned char unknown_52;  // +0x52 store at 0x552AF5
    unsigned char unknown_53[1];  // +0x53
    int unknown_54;  // +0x54 store at 0x552AF8
    int unknown_58;  // +0x58 store at 0x552AFB
    int unknown_5C;  // +0x5C store at 0x552AFE
    int unknown_60;  // +0x60 store at 0x552B01
};
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_51) == 0x51);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_52) == 0x52);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(LoadProgressMgr, unknown_60) == 0x60);
GG_STATIC_ASSERT(sizeof(LoadProgressMgr) == 0x64);

#endif  // GG_MATCH_LAYOUT_LOAD_PROGRESS_MGR_H
