// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Scalar deleting destructors of the blitter and RLE blitter instantiations
// whose methods are written as explicit specialisations elsewhere, so no TU
// emits their tables. Retail keeps all of these wrappers together at
// 0x499CE0-0x49A9E0 and 0x7BC640-0x7BC6A0, the layout of one translation
// unit that constructs every blitter. Each wrapper stores the root vtable
// (Blitter 0x7E5B88 or RLEBlitter 0x7E5BA0: the leaf destructors are empty),
// frees the object when bit 0 of the flag is set and returns `this`.
//
// They are compiler output: each explicit instantiation below compiles the
// class's inline constructor, which emits its vtable and `??_G`. The blitter
// methods are only declared in these headers, so the instantiations emit no
// method bodies (cl reports C4661 for each; that is expected). The inline
// constructors used are either the argument constructors whose member stores
// retail inlines at the allocation site (BlitTransLucent50 0x48F12C,
// BlitPlainXlat 0x48F062), or the empty constructors of member-free classes,
// whose retail construction sites store only the vptr (BlitPlain 0x7BBCAF,
// BlitTrans 0x7BBC5C,
// BlitTransXlatWriteAlpha 0x48F600, BlitTransXlatMultWriteAlpha 0x48F61E).
// The RLEBlitter destructor is inline and empty: retail's `??_G` wrappers
// store the RLEBlitter vtable directly instead of calling a destructor.

#include "blitter.h"
#include "rle_blitter.h"
#include "blit_plain.h"
#include "b_plainxlat.h"
#include "b_zremap.h"
#include "b_darken_xlatz.h"
#include "b_lucent75_blit.h"
#include "b_lucent50.h"
#include "b_lucent25_blit.h"
#include "b_xlatalpha.h"
#include "r_zremap.h"
#include "r_lucent75.h"
#include "r_lucent50.h"

// SYNTHETIC: GAMEMD 0x499CE0
// BlitPlainXlat<unsigned char> scalar deleting destructor
template class BlitPlainXlat<unsigned char>;

// SYNTHETIC: GAMEMD 0x499DC0
// RLEBlitTransZRemapXlat<unsigned char> scalar deleting destructor
template class RLEBlitTransZRemapXlat<unsigned char>;

// SYNTHETIC: GAMEMD 0x499E40
// RLEBlitTransZRemapXlatZRead<unsigned char> scalar deleting destructor
template class RLEBlitTransZRemapXlatZRead<unsigned char>;

// SYNTHETIC: GAMEMD 0x499EC0
// RLEBlitTransZRemapXlatZReadWrite<unsigned char> scalar deleting destructor
template class RLEBlitTransZRemapXlatZReadWrite<unsigned char>;

// SYNTHETIC: GAMEMD 0x499F20
// BlitPlainXlat<unsigned short> scalar deleting destructor
template class BlitPlainXlat<unsigned short>;

// SYNTHETIC: GAMEMD 0x499F60
// BlitTransDarken<unsigned short> scalar deleting destructor
template class BlitTransDarken<unsigned short>;

// SYNTHETIC: GAMEMD 0x499FA0
// BlitTransLucent50<unsigned short> scalar deleting destructor
template class BlitTransLucent50<unsigned short>;

// SYNTHETIC: GAMEMD 0x499FE0
// BlitPlainXlatZRead<unsigned short> scalar deleting destructor
template class BlitPlainXlatZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A000
// BlitTransXlatZRead<unsigned short> scalar deleting destructor
template class BlitTransXlatZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A040
// BlitTransDarkenZRead<unsigned short> scalar deleting destructor
template class BlitTransDarkenZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A080
// BlitTransLucent50ZRead<unsigned short> scalar deleting destructor
template class BlitTransLucent50ZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A0E0
// BlitTransLucent50ZReadWarp<unsigned short> scalar deleting destructor
template class BlitTransLucent50ZReadWarp<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A120
// BlitPlainXlatZReadWrite<unsigned short> scalar deleting destructor
template class BlitPlainXlatZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A140
// BlitTransXlatZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransXlatZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A180
// BlitTransDarkenZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransDarkenZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A1C0
// BlitTransLucent50ZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransLucent50ZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A380
// BlitTransXlatWriteAlpha<unsigned short> scalar deleting destructor
template class BlitTransXlatWriteAlpha<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A3A0
// BlitTransXlatMultWriteAlpha<unsigned short> scalar deleting destructor
template class BlitTransXlatMultWriteAlpha<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A780
// RLEBlitTransZRemapXlat<unsigned short> scalar deleting destructor
template class RLEBlitTransZRemapXlat<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A840
// RLEBlitTransZRemapXlatZRead<unsigned short> scalar deleting destructor
template class RLEBlitTransZRemapXlatZRead<unsigned short>;

// SYNTHETIC: GAMEMD 0x49A960
// RLEBlitTransZRemapXlatZReadWrite<unsigned short> scalar deleting destructor
template class RLEBlitTransZRemapXlatZReadWrite<unsigned short>;

// SYNTHETIC: GAMEMD 0x7BC640
// BlitPlain<unsigned char> scalar deleting destructor
template class BlitPlain<unsigned char>;

// SYNTHETIC: GAMEMD 0x7BC660
// BlitPlain<unsigned short> scalar deleting destructor
template class BlitPlain<unsigned short>;
