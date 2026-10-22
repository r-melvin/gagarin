// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Scalar deleting destructors of the remaining blitter and RLE blitter
// instantiations in the retail wrapper run at 0x499D20-0x49A9E0 (see
// blitter_ddtors.cpp for the shape). Each explicit instantiation compiles the
// class's inline constructor, which emits its vtable and the `??_G` wrapper;
// the blitter methods are only declared, so cl reports C4661 for each.

#include "blitter.h"
#include "rle_blitter.h"
#include "b_zremap.h"
#include "b_lucent75_blit.h"
#include "b_lucent25_blit.h"
#include "r_lucent75.h"
#include "r_lucent50.h"
#include "r_lucent25.h"

// SYNTHETIC: GAMEMD 0x499D20
// BlitTransZRemapXlat<unsigned char> scalar deleting destructor
template class BlitTransZRemapXlat<unsigned char>;

// SYNTHETIC: GAMEMD 0x499F40
// BlitTransZRemapXlat<unsigned short> scalar deleting destructor
template class BlitTransZRemapXlat<unsigned short>;

// SYNTHETIC: GAMEMD 0x499F80
// BlitTransLucent75<unsigned short> scalar deleting destructor
template class BlitTransLucent75<unsigned short>;

// SYNTHETIC: GAMEMD 0x499FC0
// BlitTransLucent25<unsigned short> scalar deleting destructor
template class BlitTransLucent25<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A020
// BlitTransZRemapXlatZRead<unsigned short> scalar deleting destructor
template class BlitTransZRemapXlatZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A060
// BlitTransLucent75ZRead<unsigned short> scalar deleting destructor
template class BlitTransLucent75ZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A0A0
// BlitTransLucent25ZRead<unsigned short> scalar deleting destructor
template class BlitTransLucent25ZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A0C0
// BlitTransLucent75ZReadWarp<unsigned short> scalar deleting destructor
template class BlitTransLucent75ZReadWarp<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A100
// BlitTransLucent25ZReadWarp<unsigned short> scalar deleting destructor
template class BlitTransLucent25ZReadWarp<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A160
// BlitTransZRemapXlatZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransZRemapXlatZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A1A0
// BlitTransLucent75ZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransLucent75ZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A1E0
// BlitTransLucent25ZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransLucent25ZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A7C0
// RLEBlitTransLucent75<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A7E0
// RLEBlitTransLucent50<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A800
// RLEBlitTransLucent25<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A880
// RLEBlitTransLucent75ZRead<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75ZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A8A0
// RLEBlitTransLucent50ZRead<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50ZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A8C0
// RLEBlitTransLucent25ZRead<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25ZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A8E0
// RLEBlitTransLucent75ZReadWarp<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75ZReadWarp<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A900
// RLEBlitTransLucent50ZReadWarp<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50ZReadWarp<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A920
// RLEBlitTransLucent25ZReadWarp<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25ZReadWarp<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A9A0
// RLEBlitTransLucent75ZReadWrite<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75ZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A9C0
// RLEBlitTransLucent50ZReadWrite<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50ZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A9E0
// RLEBlitTransLucent25ZReadWrite<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25ZReadWrite<unsigned short>;

