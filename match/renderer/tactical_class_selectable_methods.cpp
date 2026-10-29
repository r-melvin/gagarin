// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6D9EF0.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x6D9EF0  Tactical::AddSelectable (__thiscall)
//   GLOBAL:   GAMEMD 0xB0CEC8  TacticalSelectables[500]
//   GLOBAL:   GAMEMD 0x886FA8  view bound width
//   GLOBAL:   GAMEMD 0x886FAC  view bound height

#include "tactical_class_selectable_methods.h"

// FUNCTION: GAMEMD 0x6D9EF0
//
// Queues an object for selection at a client point. Refused when the queue is
// full (500) or the point is more than 32 pixels outside the view bound; on
// success the point is converted to tactical space by adding the view origin,
// stored with the object at the old count, and the count is bumped.
//
// Two struct copies carry the match: the view origin is read as one Point2D
// (both `[ECX+0xB0]`/`[ECX+0xB4]` loads land before either add), and the
// point is stored into the queue entry as one Point2D, which is what makes
// VC6 re-read the count once and address both stores as `[EAX*4+disp]` off a
// single `LEA EAX,[EAX+EAX*2]` instead of hoisting `&entry` with a SHL.
bool Tactical::AddSelectable(void* pTechno, int x, int y)
{
    int count = this->unknown_DB0;

    if (count != 500
        && x >= -32 && x <= DAT_00886FA8 + 32
        && y >= -32 && y <= DAT_00886FAC + 32)
    {
        TacticalSelectables[count].Techno = pTechno;

        Point2D pos;
        pos.X = this->unknown_B0.unknown_00;
        pos.Y = this->unknown_B0.unknown_04;
        Point2D pt;
        pt.X = x + pos.X;
        pt.Y = y + pos.Y;
        TacticalSelectables[this->unknown_DB0].Point = pt;

        this->unknown_DB0 = this->unknown_DB0 + 1;
        return true;
    }
    return false;
}
