// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TechnoClass bodies for primary-table (0x7F4960) slots 164, 177, 188-190,
// 200, 205, 207-211, 224, 247 and 270, emitted together at 0x459D80..0x459E62
// inside the building code. Slot numbers come from the RTTI-located table;
// names are placeholders (techno_class.h).
#include "../_layout/techno_class.h"

// CellStruct — 2D short cell coordinate (sizeof = 4). Self-guarded for reuse.
#ifndef GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
#endif  // GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED

// GLOBAL: GAMEMD 0x89C818
// The cell value slot 189 returns; its static initialiser 0x43B0E0 writes both
// words.
extern CellStruct DAT_0089C818;

// FUNCTION: GAMEMD 0x459D80
bool TechnoClass::vf_164()
{
    return false;
}

// FUNCTION: GAMEMD 0x459D90
bool TechnoClass::vf_177(int a1)
{
    return true;
}

// FUNCTION: GAMEMD 0x459DA0
int TechnoClass::vf_188()
{
    return 2;
}

// FUNCTION: GAMEMD 0x459DB0
CellStruct TechnoClass::vf_189()
{
    return DAT_0089C818;
}

// FUNCTION: GAMEMD 0x459DC0
void TechnoClass::vf_190(int a1)
{
}

// FUNCTION: GAMEMD 0x459DD0
bool TechnoClass::vf_200()
{
    return false;
}

// FUNCTION: GAMEMD 0x459DE0
void TechnoClass::vf_205()
{
}

// FUNCTION: GAMEMD 0x459DF0
bool TechnoClass::vf_207()
{
    return false;
}

// FUNCTION: GAMEMD 0x459E00
bool TechnoClass::vf_208()
{
    return false;
}

// FUNCTION: GAMEMD 0x459E10
bool TechnoClass::vf_209()
{
    return false;
}

// FUNCTION: GAMEMD 0x459E20
bool TechnoClass::vf_210()
{
    return false;
}

// FUNCTION: GAMEMD 0x459E30
bool TechnoClass::vf_211()
{
    return false;
}

// FUNCTION: GAMEMD 0x459E40
bool TechnoClass::vf_224()
{
    return false;
}

// FUNCTION: GAMEMD 0x459E50
bool TechnoClass::vf_247(int a1)
{
    return false;
}

// FUNCTION: GAMEMD 0x459E60
void TechnoClass::vf_270(int a1, int a2)
{
}
