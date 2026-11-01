// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Button table globals are referenced by retail 0x6CFD40; command globals
//   by 0x6CFCC0; tooltip descriptor stores and manager calls by 0x6D09C0.
//   ToolTip member offsets are fixed by the stores at 0x6D09C0 and the
//   resulting 0x1C-byte stack object passed to ToolTipManager::Add.
#ifndef GG_MATCH_UI_SHAPE_BUTTON_CLASS_SUPPORT_H
#define GG_MATCH_UI_SHAPE_BUTTON_CLASS_SUPPORT_H

#include "shape_button_class.h"
#include "tooltip_manager_shared.h"

// GLOBAL: GAMEMD 0x00B0CB78 (index-to-slot table)
extern int ButtonIndexTable[];
// GLOBAL: GAMEMD 0x00B0C1C0 (25 objects at 0x60-byte stride)
extern ShapeButtonClass ButtonArray[];

// GLOBAL: GAMEMD 0x00887368
extern ToolTipManager* ToolTipManager_Instance;
// GLOBAL: GAMEMD 0x008427D0
extern const char* const CommandNames[11];
// GLOBAL: GAMEMD 0x008427CC
extern int DefaultCommandIndex;

#endif  // GG_MATCH_UI_SHAPE_BUTTON_CLASS_SUPPORT_H
