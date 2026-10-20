// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI: `MOV EAX,[ESP+4]; MOV [ECX+off],EAX; RET 4`. Each of these
//   ten is a one-line setter storing its pushed argument into one member; the
//   member offset is the only thing that varies, and every one of the ten is
//   distinct. The offsets run to 0x54F0, so the modelled object is a byte
//   array that far with the stores written through it at the confirmed
//   offsets.
#ifndef GG_MATCH_CORE_MEMBER_SETTER_FAMILY_METHODS_H
#define GG_MATCH_CORE_MEMBER_SETTER_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Setter_00487C70
{
    char Bytes[0x54F4];
};
GG_STATIC_ASSERT(sizeof(Setter_00487C70) == 0x54F4);

// FUNCTION: GAMEMD 0x00487C70 — stores into +0xF8
void __fastcall FUN_00487C70(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x0050DA00 — stores into +0x54F0
void __fastcall FUN_0050DA00(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x0050DFE0 — stores into +0x5494
void __fastcall FUN_0050DFE0(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x0050E000 — stores into +0x5490
void __fastcall FUN_0050E000(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x006301F0 — stores into +0xEC
void __fastcall FUN_006301F0(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x00681110 — stores into +0x188
void __fastcall FUN_00681110(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x00681130 — stores into +0x18C
void __fastcall FUN_00681130(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x006812C0 — stores into +0x3F0
void __fastcall FUN_006812C0(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x00705D10 — stores into +0x514
void __fastcall FUN_00705D10(Setter_00487C70* self, int, int value);
// FUNCTION: GAMEMD 0x00759F20 — stores into +0x510
void __fastcall FUN_00759F20(Setter_00487C70* self, int, int value);

#endif  // GG_MATCH_CORE_MEMBER_SETTER_FAMILY_METHODS_H
