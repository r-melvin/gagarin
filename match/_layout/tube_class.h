// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TubeClass (scalar deleting destructor 0x728710; constructor from a start cell and a direction). Offsets are
//   those the destructor and registry code read; the step array holds 100 entries and the count follows at 0x1C0.
#ifndef GG_MATCH_LAYOUT_TUBE_CLASS_H
#define GG_MATCH_LAYOUT_TUBE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "cell.h"

// GLOBAL: GAMEMD 0xB0BC68 -- the cell record the class factory passes to the constructor.
extern CellStruct DAT_00B0BC68;

class TubeClass : public AbstractClass
{
public:
    TubeClass(const CellStruct* cell = &DAT_00B0BC68, int direction = 0);
    virtual ~TubeClass();
    // The stream loader's in-place construction: the base only (retail 0x410170).
    struct LoadTag {};
    TubeClass(LoadTag) {}
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);                     // 5   0x7281A0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);   // 6   0x7281E0
    virtual int vf_11();
    virtual int vf_12();
    virtual void vf_13(struct Obj_004A1D30* crc);                      // 13  0x728630
    CellStruct StartCell;      // +0x24
    CellStruct EndCell;        // +0x28
    int Direction;           // +0x2C
    int Steps[100];          // +0x30
    int StepCount;           // +0x1C0
};
GG_STATIC_ASSERT(offsetof(TubeClass, StartCell) == 0x24);
GG_STATIC_ASSERT(offsetof(TubeClass, Steps) == 0x30);
GG_STATIC_ASSERT(offsetof(TubeClass, StepCount) == 0x1C0);

#endif  // GG_MATCH_LAYOUT_TUBE_CLASS_H
