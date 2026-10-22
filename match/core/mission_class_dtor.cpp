// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//   /Ob2: retail's scalar deleting destructor 0x5B3A60 carries the empty
//   MissionClass destructor inline (four vptr stores, then CALL 0x5F3B80).
// MissionClass tables (RTTI ".?AVMissionClass@@" on 0x7EDCC0): 0x7EDCC0,
// 0x7EDCA4, 0x7EDC9C, 0x7EDC94.
#include "../_layout/mission_class.h"

MissionClass::~MissionClass()
{
}

// SYNTHETIC: GAMEMD 0x5B3A60 -- compiler-generated scalar deleting destructor.
