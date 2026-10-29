// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x568350. It uses the same +0xF4 origin and
//   half-extent at +0xF8 as the projection helpers in map_class_iso_coord_methods.cpp.
//
// Address index: 0x568350

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Lepton X/Y pair read by FUN_00568350.
struct LeptonPair_00568350
{
    int X;
    int Y;
};

// Same projection members, for the on-map test below.
class MapView_00568350
{
public:
    char unknown_000[0xF4];
    int  unknown_F4;      // +0xF4  projection origin
    int  unknown_F8;      // +0xF8  half-extent

    bool FUN_00568350(const LeptonPair_00568350* lepton) const;
};
GG_STATIC_ASSERT(offsetof(MapView_00568350, unknown_F8) == 0xF8);

// FUNCTION: GAMEMD 0x568350
// PARTIAL: 92.7% -- same instruction multiset; retail sign-extends the X cell into ESI before the Y
// cell into EAX and adds them as Y+X, the compiler orders the two movsx the other way round.
// True when the leptons fall inside the map's diamond after conversion to cells.
bool MapView_00568350::FUN_00568350(const LeptonPair_00568350* lepton) const
{
    short cx = (short)(lepton->X / 256);
    short cy = (short)(lepton->Y / 256);
    int origin = unknown_F4;
    int sum = cy + cx;
    if (sum > origin) {
        if (cx - cy < origin) {
            if (cy - cx < origin) {
                if (sum <= origin + unknown_F8 * 2) {
                    return true;
                }
            }
        }
    }
    return false;
}
