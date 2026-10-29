// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TubeClass (scalar deleting destructor 0x728710; constructor from a start cell and a direction). Offsets are
//   those the destructor and registry code read; the step array holds 100 entries and the count follows at 0x1C0.
#ifndef GG_MATCH_LAYOUT_TUBE_CLASS_H
#define GG_MATCH_LAYOUT_TUBE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"

// A tube's start and end cells are copied from one dword.
struct TubeCell
{
    short X;
    short Y;
};

class TubeClass : public AbstractClass
{
public:
    TubeClass(const TubeCell* cell, int direction);
    virtual ~TubeClass();
    TubeCell StartCell;      // +0x24
    TubeCell EndCell;        // +0x28
    int Direction;           // +0x2C
    int Steps[100];          // +0x30
    int StepCount;           // +0x1C0
};
GG_STATIC_ASSERT(offsetof(TubeClass, StartCell) == 0x24);
GG_STATIC_ASSERT(offsetof(TubeClass, Steps) == 0x30);
GG_STATIC_ASSERT(offsetof(TubeClass, StepCount) == 0x1C0);

#endif  // GG_MATCH_LAYOUT_TUBE_CLASS_H
