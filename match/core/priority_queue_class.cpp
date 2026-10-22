// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x42B1C0 / 0x42B1F0 (Ghidra
//   disasm). Names cross-checked against YRpp (consult-only,
//   no LICENSE; each offset/address reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x42B1C0   PriorityQueueClassNode::ToSurfaceIndex   (__fastcall)
//   FUNCTION: GAMEMD 0x42B1F0   PriorityQueueClassNode::SurfaceDataCount (__stdcall)
//   GLOBAL:   GAMEMD 0x87F8DC   int  g_SurfaceWidth   (multiplier g_dc)
//   GLOBAL:   GAMEMD 0x87F8E0   int  g_SurfaceHeight  (g_e0)

#include "priority_queue_class.h"

// GLOBAL: GAMEMD 0x87F8DC — surface "width" multiplier (read as a signed int by
// both helpers: IMUL EAX,dword[0x87F8DC]).
extern int g_SurfaceWidth;
// GLOBAL: GAMEMD 0x87F8E0 — surface "height" addend (MOV EAX,[0x87F8E0]).
extern int g_SurfaceHeight;

// FUNCTION: GAMEMD 0x42B1C0  (__fastcall — CellStruct& in ECX)
//
// Linear surface index of an iso cell. Mirrors the retail expression exactly:
//   ((X - W - 1 + Y) * W) + ((X - Y - 1 + W) >> 1)
// where X = mapCoord.X (MOVSX word[ECX]), Y = mapCoord.Y (MOVSX word[ECX+2]),
// W = g_SurfaceWidth (0x87F8DC). The second term is an arithmetic SAR by 1.
int __fastcall PriorityQueueClassNode::ToSurfaceIndex(const CellStruct& mapCoord)
{
    return ((mapCoord.X - g_SurfaceWidth) - 1 + (int)mapCoord.Y) * g_SurfaceWidth
         + (((int)mapCoord.X - (int)mapCoord.Y) - 1 + g_SurfaceWidth >> 1);
}

// FUNCTION: GAMEMD 0x42B1F0  (__stdcall — no args)
//
//   (g_SurfaceHeight + 4) * g_SurfaceWidth * 2
// MOV EAX,[0x87F8E0]; ADD EAX,4; IMUL EAX,[0x87F8DC]; SHL EAX,1; RET.
int __stdcall PriorityQueueClassNode::SurfaceDataCount()
{
    return (g_SurfaceHeight + 4) * g_SurfaceWidth * 2;
}
