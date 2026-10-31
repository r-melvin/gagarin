// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below (Radar.CPP code range
//   0x652680-0x658E7F). Layout and evidence for the members: input_controls/ui_display_chain.h.
//   The members are declared on a TU-local derived view so the shared header stays untouched.
//
// Address index: 0x656BE0

#include "radar_class.h"
#include "../core/vector_class_operations.h"

struct RadarView_R16 : public RadarClass
{
    void FUN_00656BE0(bool on, bool sound);
};


// GLOBAL: GAMEMD 0x8871E0 -- the rules object.
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log, printf style.
void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x750920 (decl; reloc) -- play a sound effect.
void* FUN_00750920(int voc, float volume, unsigned int pan, void* controller);

// FUNCTION: GAMEMD 0x656BE0
// Switch the radar between its on and off transition, optionally playing the matching sound.
void RadarView_R16::FUN_00656BE0(bool on, bool sound)
{
    if (on == true) {
        if (unknown_14AC == 0 || unknown_14AC == 2) {
            unknown_14AC = 3;
            unknown_14C0.EndLooping();
            if (sound) {
                FUN_00750920(DAT_008871E0->RadarOn, 1.0f, 0x2000, 0);
            }
            FUN_004068E0("Radar: ACTIVATING\n");
        }
    } else {
        unknown_14C0.EndLooping();
        unknown_14AC = 2;
        if (sound) {
            FUN_00750920(DAT_008871E0->RadarOff, 1.0f, 0x2000, 0);
        }
        FUN_004068E0("Radar: DEACTIVING\n");
    }
}

