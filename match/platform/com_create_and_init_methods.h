// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x46B050. `RET 0x14` gives five stack parameters on top of the
//   two register ones, and the forwarding call pushes all seven with the created
//   object in ECX. Imports resolved from the IAT thunk at 0x7E15FC.
#ifndef GG_MATCH_PLATFORM_COM_CREATE_AND_INIT_METHODS_H
#define GG_MATCH_PLATFORM_COM_CREATE_AND_INIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// OLE32, dllimport so the call goes indirect through the IAT.
extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(
    const void* rclsid, void* outer, unsigned long context,
    const void* riid, void** ppv);

// GLOBAL: GAMEMD 0x7E96E0 — the class id created here.
extern const char rclsid_007E96E0[16];
// GLOBAL: GAMEMD 0x7F7C90 — the interface asked for.
extern const char riid_007F7C90[16];

struct Target_0046B050
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x4664C0 — configure the freshly created object.
    void FUN_004664C0(int a, int b, int c, int d, int e, int f, int g);
};

// FUNCTION: GAMEMD 0x46B050
Target_0046B050* __fastcall FUN_0046B050(int a, int b, int c, int d, int e,
                                         int f, int g);

#endif  // GG_MATCH_PLATFORM_COM_CREATE_AND_INIT_METHODS_H
