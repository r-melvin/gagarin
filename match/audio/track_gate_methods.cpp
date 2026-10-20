// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x405AC0.

#include "track_gate_methods.h"

// FUNCTION: GAMEMD 0x405AC0
//
// Decide whether a track's handle stays attached. Below the 0x21 threshold the
// handle is handed straight back and nothing is recorded; above it the handle is
// detached first and then re-tested against the mixer's own figure for the same
// pair of descriptor values. Only if that second figure also clears 0x21 does
// the track keep the handle and remember the figure.
//
// The middle guard reads as three alternatives but is one idea: a positional
// descriptor with no handle and nothing at +0x268 is the only case that skips
// the mixer entirely.
//
// The descriptor is re-read after the detach call — retail loads `[ESI+0x24]`
// again at 0x405AF5 — because the call could have replaced it. It is then held
// across the whole second block, so that one is a local.
int __fastcall FUN_00405AC0(Owner_00405AC0* self)
{
    Track_00405AC0* track = self->Track;
    void* handle = FUN_004047B0(track);

    if (track->Desc->At_5C < 0x21) {
        FUN_00402790(self, handle);
        return 0;
    }

    FUN_00402790(self, 0);

    Desc_00405AC0* desc = track->Desc;
    if ((desc->Flags & 0x88) == 0 || handle != 0 || track->At_268 != 0) {
        // Both arguments are named in locals, and in *push* order — the
        // second argument first. Passed as expressions VC6 loads the first
        // argument into EDX where retail uses EAX; declaring them in the order
        // they go on the stack reproduces retail's assignment.
        unsigned int span = desc->At_5C;
        int base = desc->At_58;
        unsigned int level = DAT_00886B88.FUN_0065C7E0(base, span);
        if (level < 0x21) {
            FUN_00402790(self, handle);
            return 0;
        }
        track->At_13C = level;
        track->At_148 = handle;
    }

    return 0;
}
