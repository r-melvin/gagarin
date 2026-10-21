// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// No /GX: the four emitted leaf deleting wrappers match only without it.
// Paired flags leave all 24 ordinary method sections unchanged. Cluster: BlitTrans<uc|us>,
// BlitTransXlat<uc|us>, BlitTransRemapDest<uc>, BlitTransRemapXlat<uc>.
//
// Slots 2-4 of every class are the forwarding methods (call slot 1 with warp = 0).
// Slot 1 is the loop body. CFG-closed spans (entry, length), in address order:
//   BlitTransXlat<us>       BlitCopy 0x4912B0 (0x46)
//   BlitTransXlat<uc>       BlitCopy 0x4914C0 (0x3B)
//   BlitTransRemapDest<uc>  BlitCopy 0x491670 (0x32)
//   BlitTransRemapXlat<uc>  BlitCopy 0x491740 (0x46)
//   BlitTrans<uc>           BlitCopy 0x7BC610 (0x2D)
//   BlitTrans<us>           BlitCopy 0x7BC890 (0x2B)
//
// Frozen harness-backed summary: four of six slot-1 bodies and all forwarding methods match;
// its six deleting-destructor rows match and six table checks are conditional.
// Production emission additionally supplies the base and four leaf deleting
// wrappers below with an inline empty Blitter destructor; no probe is present.
// The base table and Xlat<uc>/RemapDest<uc>/RemapXlat<uc> tables pass
// conditional five-slot checks. Xlat<us> slot 1 remains a partial body; neither
// BlitTrans leaf table is emitted. These are scoped checks, not link closure.
// Loop shape that matched: `if (len > 0) { locals; do { ... } while (--n); }`
// with `int n = len` as a separate counter, locals declared in retail load
// order, and the table member read inside the loop (retail reloads [this+4]).
// CAPS:
//  0x491670 BlitTransRemapDest<uc>::BlitCopy now 100%: the dest/src PARAMETERS are
//    the running pointers (no local copies), so VC6 reuses the param slots as
//    retail does. Earlier local-copy variants capped at 56.0% (register naming).
//  0x4912B0 BlitTransXlat<us>::BlitCopy 0% and 0x7BC610 BlitTrans<uc>::BlitCopy 0%:
//    retail has an EBP frame, spills `this`, an INC ECX/DEC ECX count idiom,
//    OR AL,AL and a biased dest pointer (DEC EDI before the loop). This is
//    consistent with inline asm disabling global optimization, but does not
//    prove that the original used asm. Tried: plain do/while with
//    counter copy; pre-decrement count (len+1, while(--n)) with biased pointer
//    (the optimiser rewrites it to an indexed loop, 18 vs 27 insns);
//    #pragma optimize("", off) (full /Od, 34 insns, 5.9%). The kept body is the
//    first readable hypothesis; a complete byte match is not established.
#include "b_trans_impl.h"

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.
// LIBRARY: GAMEMD 0x4C9150 -- compiler runtime pure-method binding only.

// Address-ordered instantiated functions; generic definitions are in the implementation header.
// TEMPLATE: GAMEMD 0x4912B0
// BlitTransXlat<unsigned short>::BlitCopy
// TEMPLATE: GAMEMD 0x491300
// BlitTransXlat<unsigned short>::BlitMove
// TEMPLATE: GAMEMD 0x491330
// BlitTransXlat<unsigned short>::BlitCopyTint
// TEMPLATE: GAMEMD 0x491360
// BlitTransXlat<unsigned short>::BlitMoveTint
// TEMPLATE: GAMEMD 0x4914C0
// BlitTransXlat<unsigned char>::BlitCopy
// TEMPLATE: GAMEMD 0x491500
// BlitTransXlat<unsigned char>::BlitMove
// TEMPLATE: GAMEMD 0x491530
// BlitTransXlat<unsigned char>::BlitCopyTint
// TEMPLATE: GAMEMD 0x491560
// BlitTransXlat<unsigned char>::BlitMoveTint
// TEMPLATE: GAMEMD 0x491670
// BlitTransRemapDest<unsigned char>::BlitCopy
// TEMPLATE: GAMEMD 0x4916B0
// BlitTransRemapDest<unsigned char>::BlitMove
// TEMPLATE: GAMEMD 0x4916E0
// BlitTransRemapDest<unsigned char>::BlitCopyTint
// TEMPLATE: GAMEMD 0x491710
// BlitTransRemapDest<unsigned char>::BlitMoveTint
// TEMPLATE: GAMEMD 0x491740
// BlitTransRemapXlat<unsigned char>::BlitCopy
// TEMPLATE: GAMEMD 0x491790
// BlitTransRemapXlat<unsigned char>::BlitMove
// TEMPLATE: GAMEMD 0x4917C0
// BlitTransRemapXlat<unsigned char>::BlitCopyTint
// TEMPLATE: GAMEMD 0x4917F0
// BlitTransRemapXlat<unsigned char>::BlitMoveTint
// SYNTHETIC: GAMEMD 0x499ca0
// BlitTransXlat<unsigned short> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499cc0
// Blitter scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499d00
// BlitTransXlat<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499d40
// BlitTransRemapDest<unsigned char> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x499d60
// BlitTransRemapXlat<unsigned char> scalar deleting destructor
// TEMPLATE: GAMEMD 0x7BC610
// BlitTrans<unsigned char>::BlitCopy
// TEMPLATE: GAMEMD 0x7BC6C0
// BlitTrans<unsigned char>::BlitMove
// TEMPLATE: GAMEMD 0x7BC6F0
// BlitTrans<unsigned char>::BlitCopyTint
// TEMPLATE: GAMEMD 0x7BC720
// BlitTrans<unsigned char>::BlitMoveTint
// TEMPLATE: GAMEMD 0x7BC890
// BlitTrans<unsigned short>::BlitCopy
// TEMPLATE: GAMEMD 0x7BC8C0
// BlitTrans<unsigned short>::BlitMove
// TEMPLATE: GAMEMD 0x7BC8F0
// BlitTrans<unsigned short>::BlitCopyTint
// TEMPLATE: GAMEMD 0x7BC920
// BlitTrans<unsigned short>::BlitMoveTint
template class BlitTransXlat<unsigned short>;
template class BlitTransXlat<unsigned char>;
template class BlitTransRemapDest<unsigned char>;
template class BlitTransRemapXlat<unsigned char>;
template class BlitTrans<unsigned char>;
template class BlitTrans<unsigned short>;
