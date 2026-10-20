// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5F3DB0.

#include "abstract_class_target_direction_methods.h"

// FUNCTION: GAMEMD 0x5F3DB0
//
// The facing from this object to another, as a binary angle. Both positions
// come through the GetCoords slot into stack buffers; the differences are
// taken on the FPU (`FILD`/`FISUB`) with the Y difference running self-to-
// target and the X difference target-to-self, then the same pi/2 shift and
// scale as 0x4265B0. The result is copied out as a dword through the buffer
// argument, which is also returned.
//
// The X halves go through int locals and the Y halves do not: retail loads
// both X values into registers and spills them (`MOV ECX,[EDI]; MOV EDX,[EAX];
// MOV [ESP+0x2C],ECX; MOV [ESP+8],EDX`) before the `FILD`/`FISUB`, while the Y
// pair is read straight off the pointers. Reading X straight off the pointers
// too drops the four moves and shrinks the frame to 0x18 (30.0%); declaring
// the locals target-first swaps ECX/EDX (90.0%); self-first is exact. The
// target's X lands in the dead `target` parameter slot.
Dir_005F3DB0* Obj_005F3DB0::FUN_005F3DB0(Dir_005F3DB0* result,
                                         Obj_005F3DB0* target)
{
    Coord_005F3DB0 targetBuf;
    Coord_005F3DB0 selfBuf;

    Coord_005F3DB0* t = (target->*target->Vtbl->At_48)(&targetBuf);
    Coord_005F3DB0* s = (this->*this->Vtbl->At_48)(&selfBuf);

    int sx = s->X;
    int tx = t->X;

    double radians = FUN_004CAE30((double)s->Y - t->Y,
                                  (double)tx - sx);

    Dir_005F3DB0 dir;

    dir.Value = (short)((radians - 1.5707963267948966) * -10430.060040584269);

    *result = dir;

    return result;
}
