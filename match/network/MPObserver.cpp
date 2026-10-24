// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MPObserver.cpp. The name is the source-file string at 0x82fd40
//   in retail gamemd.exe v1.001, passed by the assert at 0x5c9476 inside this object's
//   code range (0x5c91f0-0x5c950f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The header initialiser group at 0x5C9220, 0x5C9240 and 0x5C93C0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE5E0 reads 60.0 (ghidra memory read).
//
//   block of MPObserver.cpp (its __FILE__ string 0x82FD40).

#include "../core/deleting_dtor_sweep.h"
#include "transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF8F8
extern double DAT_00ABF8F8;
// GLOBAL: GAMEMD 0x7EE5E0
const double DAT_007EE5E0 = 60.0;

#include "mp_game_mode_leaf_classes.h"
#include "../ui/input_controls/ui_display_chain.h"

// SYNTHETIC: GAMEMD 0x5C9220
// GLOBAL: GAMEMD 0xABF948
double DAT_00ABF948 = DAT_00ABF8F8 / DAT_007EE5E0;

// SYNTHETIC: GAMEMD 0x5C9240
// GLOBAL: GAMEMD 0xABF930
double DAT_00ABF930 = 1.0 / DAT_00ABF948;

// SYNTHETIC: GAMEMD 0x5C93C0
// GLOBAL: GAMEMD 0xABF938
HeaderCoordInit DAT_00ABF938(128, 128, 0);

// FUNCTION: GAMEMD 0x5C93E0
Megawealth::Megawealth(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, e, f)
{
}

// FUNCTION: GAMEMD 0x5C9420
Megawealth::~Megawealth()
{
}

// FUNCTION: GAMEMD 0x5C9430
// Slot 35: call the map's 0x577F30 with no house, and succeed.
bool Megawealth::vf_35()
{
    Map_0087F7E8.FUN_00577F30(0);
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C94D0
void* Obj_5C94D0::FUN_5C94D0(unsigned int flags)
{
    FUN_005D8C80(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
