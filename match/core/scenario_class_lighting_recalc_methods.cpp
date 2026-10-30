// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x53AD00.

#include "scenario_class_lighting_recalc_methods.h"

// FUNCTION: GAMEMD 0x53AD00
//
// Push a new ambient tint through every light converter: the registry of
// converters, the converter of each colour scheme that has more than one
// remap level, and the converters of every per-palette scheme vector the hash
// iterator yields. Then the map re-sweeps its cell lighting and the sidebar is
// flagged for redraw.
void ScenarioClass::RecalcLighting(int r, int g, int b, bool tint)
{
    int i;

    for (i = 0; i < DAT_0087F698.Count; i++) {
        LightConvert_0053AD00* lc = DAT_0087F698.Items[i];
        (lc->*lc->Vtbl->At_04)(r, g, b, tint);
    }

    for (i = 0; i < DAT_00B054D0.Count; i++) {
        ColorScheme_0053AD00* scheme = DAT_00B054D0.Items[i];
        if (scheme->At_310 > 1) {
            LightConvert_0053AD00* lc = scheme->LightConvert;
            (lc->*lc->Vtbl->At_04)(r, g, b, tint);
        }
    }

    HashIterator_0053AD00 it;
    it.At_00 = 0;
    it.At_04 = 0;
    it.At_08 = 0;
    ColorSchemeVec_0053AD00* vec = FUN_00626690(&it);
    while (vec != 0) {
        int count = FUN_00626C60();
        for (i = 0; i < count; i++) {
            LightConvert_0053AD00* lc = vec->Items[i]->LightConvert;
            (lc->*lc->Vtbl->At_04)(r, g, b, tint);
        }
        vec = FUN_00626690(&it);
    }

    MapInstance.FUN_004AE4C0();
    MapInstance.FlagToRedraw(1);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F698
LightConvertVec_0053AD00 DAT_0087F698;
// GLOBAL: GAMEMD 0xB054D0
ColorSchemeVec_0053AD00 DAT_00B054D0;
// END defined globals
