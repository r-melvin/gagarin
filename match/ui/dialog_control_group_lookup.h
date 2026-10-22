// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 at 0x600CA0,
//   0x6015E0, 0x601D20 and 0x602490. All four take a key in ECX and a window
//   handle in EDX with no stack cleanup, so all four are __fastcall, and all
//   four open with the same inlined hash-table probe already proven at
//   0x602B90 / 0x603240 (see dialog_type_lookup_predicates.h for the map
//   layout, which this file reuses rather than restating).
//
//   Disasm-derived facts specific to this cluster:
//     * The category arrives in EDI (`MOV EDI,[EAX+0x6C]` on the hit path,
//       `XOR EDI,EDI` on the miss path) and the control ID in ESI, straight
//       out of `CALL [0x7E13B4]`, i.e. USER32!GetDlgCtrlID.
//     * The bodies are flat chains of `CMP reg,imm32; JZ` in comparison
//       order, with no jump table anywhere: the source is a disjunction of
//       equality tests, transcribed verbatim.
//     * Return widths differ inside the family and only the exit says so.
//       0x600CA0, 0x6015E0 and 0x601D20 end `MOV EAX,imm` (a full dword);
//       0x602490 ends `MOV AL,1` / `XOR AL,AL`, a one-byte bool.
//     * 0x602490 also reads a flag through `MOV ECX,0xA8B238; CALL 0x69BBE0`.
//       0x69BBE0 is the seven-byte accessor `MOV AL,[ECX+0x30D8]; RET`, so
//       the flag is at +0x30D8 of the object based at 0xA8B238.
//     * 0x602490's first clause widens its category set with the out-of-line
//       test at 0x602AE0 and consumes the result with `TEST AL,AL`, while
//       0x602AE0's own exit is `MOV EAX,1`. The value is therefore narrowed
//       at the call site, which is why the call is written `(char)FUN_...`
//       here and the shared declaration stays `int`.
//     * The tail guard `FUN_00601360(category) && nCtlID == 0x695` appears in
//       all four. In 0x600CA0 both of its arms answer 0xF, so cl folded both
//       tests away and only the call survives; the other three keep the test.
#ifndef GG_MATCH_UI_DIALOG_CONTROL_GROUP_LOOKUP_H
#define GG_MATCH_UI_DIALOG_CONTROL_GROUP_LOOKUP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "dialog_type_lookup_predicates.h"
#include "control_id_predicate_methods.h"
// The object at 0xA8B238, modelled only as far as the one flag 0x602490
// reads. The offset is the displacement in the accessor's single load.
struct SessionFlags_00A8B238
{
    char _pad0000[0x30D8];   // +0x0000
    bool Flag30D8;           // +0x30D8

    // FUNCTION: GAMEMD 0x69BBE0 (__thiscall)  MOV AL,[ECX+0x30D8]; RET
    bool FUN_0069BBE0();
};
GG_STATIC_ASSERT(offsetof(SessionFlags_00A8B238, Flag30D8) == 0x30D8);

// The hash-table offsets this TU depends on, re-asserted here rather than
// taken on trust from the header that defines them: each is the displacement
// in one of the four bodies' own instructions — `MOV EAX,[0xAC1B04]` (Count),
// `MOV ECX,[0xAC1B0C]` (Shift), `CALL [0xAC1B18]` (Hash), `MOV EAX,[EAX+0x204]`
// (Next), `ADD EAX,4` (Value) and `MOV EDI,[EAX+0x6C]` (Field6C).
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Count) == 0x04);
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Shift) == 0x0C);
GG_STATIC_ASSERT(offsetof(HashMap_00602B90, Hash) == 0x18);
GG_STATIC_ASSERT(offsetof(MapNode_00602B90, Value) == 0x04);
GG_STATIC_ASSERT(offsetof(MapNode_00602B90, Next) == 0x204);
GG_STATIC_ASSERT(offsetof(MapValue_00602B90, Field6C) == 0x6C);

// GLOBAL: GAMEMD 0xA8B238 — the session object.
extern SessionFlags_00A8B238 DAT_00A8B238_Session;

// FUNCTION: GAMEMD 0x600CA0 (__fastcall)
int FUN_00600CA0(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x6015E0 (__fastcall)
int FUN_006015E0(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x601D20 (__fastcall)
int FUN_00601D20(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x602490 (__fastcall)
bool FUN_00602490(int nKey, GG_HWND hCtl);

#endif  // GG_MATCH_UI_DIALOG_CONTROL_GROUP_LOOKUP_H
