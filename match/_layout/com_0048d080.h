// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared ABI prefix of the existing guarded COM devices. Interface identity
// and fields beyond the observed prefix remain unknown.
#ifndef GG_MATCH_LAYOUT_COM_0048D080_H
#define GG_MATCH_LAYOUT_COM_0048D080_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The two COM objects the guard pokes; each call pushes the receiver.
struct ComVtbl_0048D080;
struct Com_0048D080
{
    ComVtbl_0048D080* Vptr;   // +0x0000
};
struct ComVtbl_0048D080
{
    char  _pad000[0x0C];                                   // +0x0000
    void (__stdcall* At_0C)(Com_0048D080* self);           // +0x000C
    char  _pad010[0x18 - 0x10];                            // +0x0010
    // 0x64B013..0x64B023: pushed self,opaque buffer,timeout,opaque output.
    // ev_b5c969df5a0afe76e5bcb471c429133475d21e9580df611904208e1c9f0498be.
    void (__stdcall* At_18)(Com_0048D080*, void*, int, void*); // +0x0018
    void (__stdcall* At_1C)(Com_0048D080* self);           // +0x001C
};
GG_STATIC_ASSERT(offsetof(ComVtbl_0048D080, At_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ComVtbl_0048D080, At_1C) == 0x1C);
// GLOBAL: GAMEMD 0xAC116C — the first guarded device.
extern Com_0048D080* DAT_00AC116C;
// GLOBAL: GAMEMD 0xAC1170 — the second guarded device.
extern Com_0048D080* DAT_00AC1170;

GG_STATIC_ASSERT(offsetof(Com_0048D080, Vptr) == 0);
GG_STATIC_ASSERT(sizeof(Com_0048D080) == 4);
GG_STATIC_ASSERT(offsetof(ComVtbl_0048D080, At_18) == 0x18);
GG_STATIC_ASSERT(sizeof(ComVtbl_0048D080) == 0x20);

#endif
