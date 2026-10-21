// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x472640 (see the RE dossier at
//   docs/decomp_spec/re_findings/next_targets_2026-08-07.md §8). Every offset
//   already exists in a committed model and is reconfirmed here from the
//   member accesses: ObjectClass::IsSelected @0x83, TechnoClass::Transporter
//   @0x11C, CaptureManagerClass::ControlNodes_Items @0x28 / _Count @0x34, and
//   the frame-counter global 0x00A8ED84.
//
// This TU retains its local CaptureManager receiver and Techno field views;
// the ControlNode record is shared with the other consumers.
#ifndef GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_DRAW_METHODS_H
#define GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_DRAW_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass
{
public:
    char         _pad00[0x83];      // +0x0000
    bool         IsSelected;        // +0x0083  ObjectClass
    char         _pad84[0x11C - 0x84];
    TechnoClass* Transporter;       // +0x011C  TechnoClass
};
GG_STATIC_ASSERT(offsetof(TechnoClass, IsSelected)  == 0x83);
GG_STATIC_ASSERT(offsetof(TechnoClass, Transporter) == 0x11C);

// Shared node frame fields are pinned by the canonical record assertions.
#include "../_layout/control_node.h"

// GLOBAL: GAMEMD 0x00A8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

struct CaptureManagerClass
{
    char          _pad00[0x28];        // +0x0000
    ControlNode** ControlNodes_Items;  // +0x0028
    char          _pad2C[0x34 - 0x2C];
    int           ControlNodes_Count;  // +0x0034
    char          _pad38[0x48 - 0x38];
    TechnoClass*  Owner;               // +0x0048

    bool NeedsToDrawLinks();           // GAMEMD 0x472640
};
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes_Items) == 0x28);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes_Count) == 0x34);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, Owner)              == 0x48);

#endif  // GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_DRAW_METHODS_H
