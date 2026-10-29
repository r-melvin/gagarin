// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU056 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x48e290-0x49b17f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   neighbours. Functions are ordered ascending by retail address.
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; function extents and touched fields confirmed from entry-origin disassembly.
// The same 32 methods were also exact under /O2 /DNDEBUG /Gy without /GX; use
// the project default after the flag bisection. Definitions are explicit
// <unsigned short> member specializations, sorted by retail address. No whole
// class instantiations, deleting destructors or derived vtables are emitted.
//
//   Provenance note: own-binary-via-Ghidra; frozen milestone-2 b-lucent50 method bodies.
// Method-only source subset for the eight BlitTransLucent50 leaves, unsigned short only.
// The 32 methods are in ascending retail-address order. This source does not claim
// constructors, deleting destructors, vtables, or alpha-pool ownership.
// PARTIAL: 0x492830 remains the frozen readable body; it is not rewritten here.
// Its frozen check reports 0.0% by diff_retail instruction count (32 emitted vs 40 retail).
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; the retained method bodies, complete spans and field accesses were checked against the frozen M2 evidence and pinned retail image.
// Paired compile with /O2 /DNDEBUG /Gy also reproduces all retained methods; the project default applies because both object sets match.
// Explicit <unsigned short> member specializations emit only the 32 ordinary methods. This TU does not claim constructors, deleting destructors, or derived vtable emission.
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// Production-only ordinary method subset from the frozen M3 r-darken-remap
// evidence. The nine harness deleting-destructor bodies and nine harness
// vtable bodies are deliberately excluded. Three capped RLE bodies are kept
// byte-for-byte source-identical to the frozen candidate and remain partial.
//
// Scalar deleting destructors of the remaining blitter and RLE blitter
// instantiations in the retail wrapper run at 0x499D20-0x49A9E0 (see
// blitter_ddtors.cpp for the shape). Each explicit instantiation compiles the
// class's inline constructor, which emits its vtable and the `??_G` wrapper;
// the blitter methods are only declared, so cl reports C4661 for each.
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// The 20 method bodies below are entry-origin, raw-byte verified. They touch
// the documented mask/xlat fields and, for Z variants, the shared row-wrap
// global. Explicit specializations keep this TU from emitting unverified
// deleting-destructor wrappers or derived vtables.
// Paired /GX and no-/GX production compiles produced identical bytes for all
// 20 functions; use the project default set.
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// Source facts: frozen milestone 3 production-only r-lucent25 reconstruction;
// every body below is tied to its retail entry and full CFG-closed span by the
// corresponding TEMPLATE marker. No pool ownership, constructor/destructor,
// deleting-destructor, or leaf-vtable body is emitted by this translation unit.
//
// /GX is off for this TU: /O2 /DNDEBUG /Gy /GX emits non-retail bodies. Cluster b-translucent:
// BlitTranslucent50NonzeroAlpha<us>, BlitTranslucent50ZeroAlpha<us>,
// BlitTranslucentWriteAlpha<us>. Slots 2-4 are forwarding shims (slot 1, warp = 0).
// Entry-origin CFG-closed spans (entry, length):
//   50NonzeroAlpha<us> BlitCopy 0x494920 (0x83)
//   50ZeroAlpha<us>    BlitCopy 0x494A40 (0x83)
//   WriteAlpha<us>     BlitCopy 0x494690 (0x1F5; frozen partial)
//
// Candidate rows cover the twelve native method bodies in this source only.
// Compiler-emitted constructor/destructor and vtable COMDATs are not claimed by
// the function rows; harness-only deleting-wrapper evidence is excluded.
// Levers that matched the 50% pair: copy abuf into a local (`ap`) BEFORE the
// `if (len > 0)`; wrap the alpha row through the inline BTranslucentWrapRow(ap + 1)
// after ++d (retail adds to abuf second); table/mask read inside the loop.
// PARTIAL 0x494690 BlitTranslucentWriteAlpha<us>::BlitCopy 88.0% (125/142 instruction
// positions; multiset identical, 427/501 raw bytes): dest and src are the running
// pointers themselves (parameters advanced in place, no d/s locals), while `abuf`
// and the count are copied to locals `ap` and `n` ahead of use, which is what makes
// retail's self-stores of the abuf and len slots appear. Residual: retail evaluates
// the channel-0 term first and keeps it in EDX with the cached pos0/loss0 registers
// (EBX/EBP) for the final OR, and loads dc[0] before sc[0] for the first multiply;
// ours shifts the third channel first through memory loads and swaps EAX/EDX in the
// first multiply. Measured with no effect: all 6 declaration orders of r/g/b, all 6
// clamp orders, g2 temp or in-place, all 8 per-channel sum operand orders, all 6 OR
// operand orders (plain and parenthesised), and building the pixel in a local.
//
// Retail PAVConvertClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
// Cluster r-alpha (all <unsigned short>): RLEBlitTransXlatAlpha, ...ZRead, ...ZReadWrite
// and RLEBlitTransZRemapXlatAlpha, ...ZRead, ...ZReadWrite. No /GX. Layouts in r_alpha.h.
// Explicit member specializations only; this TU does not emit leaf vtables or lifetime code.
//
// The alpha level is clamped to >= 0, scaled by 261/2048, capped at 0xFE and used as
// a 512-byte row offset into the alpha-buffer table (+8, or +0xC for the ZRemap leaves); a drawn
// pixel is table[row[*abuf] | src byte] (ZRemap: the source byte goes through *remap first).
//
// CFG-closed spans (entry, length):
//   XlatAlpha            RLEBlit 0x4978C0 (0x109) slot 2 0x4979D0 (0x3A)
//   ZRemapXlatAlpha      RLEBlit 0x497A10 (0x122) slot 2 0x497B40 (0x3A)
//   XlatAlphaZRead       RLEBlit 0x497FD0 (0x17D) slot 2 0x498150 (0x182)
//   ZRemapXlatAlphaZRead RLEBlit 0x4982E0 (0x1AA) slot 2 0x498490 (0x3A)
//   XlatAlphaZReadWrite  RLEBlit 0x4990E0 (0x19F) slot 2 0x499280 (0x1A4)
//   ZRemapXlatAlphaZReadWrite RLEBlit 0x499430 (0x1D4) slot 2 0x499610 (0x3A)
//
// Slot 2 is a forwarding shim (drops tint) except for the XlatAlphaZRead and
// XlatAlphaZReadWrite leaves, where it is a full body that ORs tint into the pixel.
//
// Recipe that matched (see r_lucent25_alpha.cpp for the same family shape): skip loop
// with no byte variable; locals copied from the parameters (z, ab, zs), declared in
// retail load order; `unsigned short idx = ... | c;` as a separate local in the Z leaves;
// the alpha-row pointer built in two steps (clamp first, scale and table pointer after
// d/z/ab/zs are loaded); abuf wrapped through RLEAlphaWrapRow after every iteration.
//
// PARTIAL 0x497A10 RLEBlitTransZRemapXlatAlpha::RLEBlit 89.7% (was 83.2%; the skip
//   loop now reads the RLE byte into a named local, as the closed leaves do): multiset
//   identical (107/107); the residual is register choice around `skip` (retail EDX,
//   loaded after the alpha-row store; ours ESI, loaded before it). Tried: every
//   declaration order of {s,d,a,row/at,ab,rm}, with and without ab/sk/n copies, idx
//   inline vs local, six spellings of the row expression, clamp and scale split in two,
//   alvl modified in place instead of a local.
//
//   Provenance note: frozen M3 r-lucent75 method packet, SHA-verified; method spans
// are checked against pinned gamemd.exe v1.001. This TU contains only the
// explicit unsigned-short RLE leaf method specializations below. It does not
// claim constructors, deleting destructors, alpha-pool ownership or vtable emission.
//
//   Provenance note: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe.
// Cluster r-lucent50, families RLEBlitTransLucent50AlphaZRead / AlphaZReadWarp /
// AlphaZReadWrite <us>. No /GX. See r_lucent50.h for the layout.
//
// Spans: AlphaZRead 0x4986D0 (0x1AC), AlphaZReadWarp 0x498CD0 (0x1B1),
// AlphaZReadWrite 0x499860 (0x1E5); Tint shims 0x498880 / 0x498E90 / 0x499A50 (0x3A).
// Tint shims 100%. RLEBlit bodies:
//   AlphaZReadWrite 0x499860  MATCHED: the skip loop reads the RLE byte into a
//                   named local, the Z store is `*z++ = zval - *zs++`, and len-- comes
//                   before d++ in the drawn arm. The previous section was 5 bytes short.
//   AlphaZRead      0x4986D0  PARTIAL 22.8% (was 20.1%); multiset retail-only {lea},
//                   ours-only {add}.
//   AlphaZReadWarp  0x498CD0  PARTIAL 22.7% (was 12.7%). Correction: the translucent
//                   term is `t >> 1` (retail `SHR AX,1` at 0x498E1F), not `>> 2`.
// All three index the alpha row as `row[*ab]` (a `unsigned short*` into the table);
// an earlier byte-pointer form with a reinterpret_cast scored the same and is gone.
// Remaining delta in the two partials: retail keeps the RLE byte c and s in stack
// slots and re-reads this, zshape and len from the argument area under register
// pressure; no declaration order reached it (all 120 orders of z / zs / s / d /
// alpha-row block were tried earlier, plus the advance orders and wrap forms).
//
//   Provenance note: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe.
// Cluster r-lucent50, families RLEBlitTransLucent50ZRead / ZReadWarp /
// ZReadWrite <us>. No /GX. See r_lucent50.h for the layout and
// r_shared_zwrap.h for the Z row wrap.
//
// Spans: ZRead 0x496A80 (0xFF), ZReadWarp 0x496E60 (0x104), ZReadWrite 0x497610 (0x10F);
// Tint shims 0x496B80 / 0x496F70 / 0x497720 (0x3A). All 100%.
// Levers that mattered: z / zs locals declared before s / d; the transparent run
// advances d, zs, z in that order; both branches of the depth test repeat their own
// len / d (and ReadWrite zs / z) steps instead of sharing a tail; ReadWrite re-reads
// *zs for the depth store.
//
//   Provenance note: frozen M3 r-lucent75 method packet, SHA-verified; method spans
// are checked against pinned gamemd.exe v1.001. This TU contains only the
// explicit unsigned-short RLE leaf method specializations below. It does not
// claim constructors, deleting destructors, alpha-pool ownership or vtable emission.
//
//   Provenance note: frozen M3 candidate; instructions revalidated against pinned retail gamemd.exe.
// Cluster r-lucent50, families RLEBlitTransLucent50<us> and
// RLEBlitTransLucent50Alpha<us> (no depth test). No /GX, as the other blitter
// families. See r_lucent50.h for the layout.
//
// Spans (entry, length): Lucent50 RLEBlit 0x4963F0 (0x9A), Tint 0x496490 (0x3A);
// Alpha RLEBlit 0x497CF0 (0x12B), Tint 0x497E20 (0x3A).
// Results: Lucent50 RLEBlit and both Tint shims 100%.
// Alpha RLEBlit 0x497CF0 now 100% using the r_lucent25_alpha.cpp body structure.
//
// Paired /GX and no-/GX builds leave all twelve ordinary method spans identical;
// the exception-handling flag is not determined by these methods.
// Cluster r-zremap, family RLEBlitTransZRemapXlat<T> (no depth test). See r_zremap.h for the layout.
//
// Full entry-to-RET spans for the ordinary methods in this TU; current Ghidra
// extents and raw REA input lengths agree. Harness deleting wrappers are excluded.
//   0x4918E0 unsigned char RLEBlit (0x89)
//   0x491970 unsigned char RLEBlitTint (0x3A)
//   0x496170 unsigned short RLEBlit (0x91)
//   0x496210 unsigned short RLEBlitTint (0x3A)
//
// Paired /GX and no-/GX builds leave all twelve ordinary method spans identical;
// the exception-handling flag is not determined by these methods.
// Cluster r-zremap, family RLEBlitTransZRemapXlatZRead<T> (depth test, no
// depth write). See r_zremap.h for the layout and r_shared_zwrap.h for
// the Z row wrap.
//
// Full entry-to-RET spans for the ordinary methods in this TU; current Ghidra
// extents and raw REA input lengths agree. Harness deleting wrappers are excluded.
//   0x491C50 unsigned char RLEBlit (0xF6)
//   0x491D50 unsigned char RLEBlitTint (0x3A)
//   0x4966D0 unsigned short RLEBlit (0x101)
//   0x4967E0 unsigned short RLEBlitTint (0x3A)
//
// Paired /GX and no-/GX builds leave all twelve ordinary method spans identical;
// the exception-handling flag is not determined by these methods.
// Cluster r-zremap, family RLEBlitTransZRemapXlatZReadWrite<T> (depth test and
// depth write). See r_zremap.h for the layout and r_shared_zwrap.h for
// the Z row wrap.
//
// Full entry-to-RET spans for the ordinary methods in this TU; current Ghidra
// extents and raw REA input lengths agree. Harness deleting wrappers are excluded.
//   0x492100 unsigned char RLEBlit (0x108)
//   0x492210 unsigned char RLEBlitTint (0x3A)
//   0x497230 unsigned short RLEBlit (0x111)
//   0x497350 unsigned short RLEBlitTint (0x3A)
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; M3 frozen source, full-entry spans and raw-byte verification records.
// No /GX; this is the locked M3 candidate flag set. Paired compile verification awaits root's compiler-free signal.
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; M3 frozen source, full-entry spans and raw-byte verification records.
// No /GX; this is the locked M3 candidate flag set. Paired compile verification awaits root's compiler-free signal.
//
//   Provenance note: retail gamemd.exe v1.001 SHA-256 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c; M3 frozen source, full-entry spans and raw-byte verification records.
// No /GX; this is the locked M3 candidate flag set. Paired compile verification awaits root's compiler-free signal.
//
//   Provenance note: frozen M3 r-lucent75 method packet, SHA-verified; method spans
// are checked against pinned gamemd.exe v1.001. This TU contains only the
// explicit unsigned-short RLE leaf method specializations below. It does not
// claim constructors, deleting destructors, alpha-pool ownership or vtable emission.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// Static data members of vector type: each retail definition is guarded by a
// bit in a shared byte, so the exit-time destructor stub tests that bit before
// restoring the VectorClass<T> vtable and releasing the array. Every member here
// is the lowest bit of its guard byte (a single-member group), so each is given
// its own placeholder holder; the owning classes are not recoverable. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored
// by the matching initialiser. The initialisers (__xc table entries) are left to
// the translation-unit migration and compile here as a by-product, unclaimed.

#include "../core/cached_resource_dtor_family_methods.h"

#include "../render/blitters/b_lucent25_blit.h"
#include "../render/blitters/r_shared_zwrap.h"

// Alpha row wrapping uses the observed pointer/byte-step fields in the global at 0x87E8A4.
inline unsigned short* BlitAlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

// Blend: 3/4 of the source pixel plus 1/4 of the destination, per channel mask.
inline unsigned short Lucent25Mix(unsigned short p, unsigned short b, unsigned short m)
{
    return (unsigned short)((((p >> 2) & m) * 3) + ((b >> 2) & m));
}

// Alpha table row for this level: (alvl clamped to >= 0) * 261 >> 11, capped at 0xFE, 512 bytes per row.
inline int Lucent25AlphaRow(int alvl)
{
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE) a = 0xFE;
    return a << 9;
}

#include "../render/blitters/b_lucent50.h"
#include "../render/blitters/r_shared_zwrap.h"

// Alpha row wrap: same shape as the Z row wrap, against the block at 0x87E8A4
// (b_shared_alpha.h).
static inline unsigned short* AlphaWrapRow(unsigned short* row)
{
    if (row >= gg_blit_alpha_wrap_global->wrap_end)
        row = (unsigned short*)((unsigned char*)row - gg_blit_alpha_wrap_global->wrap_step);
    return row;
}

// Alpha level -> row index: clamp > 0, (a * 261) >> 11, cap at 0xFE.
static inline int AlphaRowIndex(int alvl)
{
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    return a;
}

#include "../render/blitters/b_lucent75_blit.h"
#include "../render/blitters/r_shared_zwrap.h"

#include "../render/blitters/r_darken_remap.h"

// Explicit instantiation emits the methods from these nine specializations.
// The production candidate rows cover only the 18 ordinary methods. VC6 also
// emits constructor/destructor and vtable symbols for these class instantiations;
// this package makes no claims for those artifacts or the harness-only rows.
template class RLEBlitTransDarken<unsigned short>;
template class RLEBlitTransDarkenZRead<unsigned short>;
template class RLEBlitTransDarkenZReadWrite<unsigned short>;
template class RLEBlitTransRemapDest<unsigned char>;
template class RLEBlitTransRemapDestZRead<unsigned char>;
template class RLEBlitTransRemapDestZReadWrite<unsigned char>;
template class RLEBlitTransRemapXlat<unsigned char>;
template class RLEBlitTransRemapXlatZRead<unsigned char>;
template class RLEBlitTransRemapXlatZReadWrite<unsigned char>;

#include "../render/blitters/blitter.h"
#include "../render/blitters/rle_blitter.h"
#include "../render/blitters/b_zremap.h"
#include "../render/blitters/b_lucent75_blit.h"
#include "../render/blitters/b_lucent25_blit.h"
#include "../render/blitters/r_lucent75.h"
#include "../render/blitters/r_lucent50.h"
#include "../render/blitters/r_lucent25.h"

#include "../render/blitters/b_darken_xlatz.h"
#include "../render/blitters/r_shared_zwrap.h"

#include "../render/blitters/r_lucent25.h"

// Explicitly instantiate the eight leaf specializations. VC6 emits their
// ordinary virtual methods from these declarations.
template class RLEBlitTransLucent25<unsigned short>;
template class RLEBlitTransLucent25ZRead<unsigned short>;
template class RLEBlitTransLucent25ZReadWarp<unsigned short>;
template class RLEBlitTransLucent25ZReadWrite<unsigned short>;
template class RLEBlitTransLucent25Alpha<unsigned short>;
template class RLEBlitTransLucent25AlphaZRead<unsigned short>;
template class RLEBlitTransLucent25AlphaZReadWarp<unsigned short>;
template class RLEBlitTransLucent25AlphaZReadWrite<unsigned short>;

#include "../render/blitters/b_translucent.h"

// VC6 requires class instantiation to emit these member bodies. The object also
// contains compiler-generated support COMDATs; they are not reviewed candidate
// rows and no deleting-wrapper/vtable ownership is claimed here.
template class BlitTranslucent50NonzeroAlpha<unsigned short>;
template class BlitTranslucent50ZeroAlpha<unsigned short>;
template class BlitTranslucentWriteAlpha<unsigned short>;

#include "../core/vector_class_operations.h"

class ConvertClass;

// VTABLE: GAMEMD 0x7E5338 -- VectorClass<ConvertClass*>.
template class VectorClass<ConvertClass*>;
typedef VectorClass<ConvertClass*> GgConvertClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConvertClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E5318 -- DynamicVectorClass<ConvertClass*>.
template class DynamicVectorClass<ConvertClass*>;
typedef DynamicVectorClass<ConvertClass*> GgConvertClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgConvertClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ConvertClass*) == 4);

#include "../render/blitters/r_alpha.h"

#include "../render/blitters/r_lucent75.h"

#include "../render/blitters/r_lucent50.h"

#include "../render/blitters/r_lucent50.h"

#include "../render/blitters/r_lucent75.h"

#include "control_class.h"

#include "../render/blitters/r_lucent50.h"

#include "../render/blitters/r_zremap.h"

#include "../render/blitters/r_zremap.h"

#include "../render/blitters/r_zremap.h"

#include "../render/blitters/r_xlat.h"

template class RLEBlitTransXlat<unsigned char>;

#include "../render/blitters/r_xlat.h"

template class RLEBlitTransXlatZRead<unsigned char>;

#include "../render/blitters/r_xlat.h"

template class RLEBlitTransXlatZReadWrite<unsigned char>;

#include "../render/blitters/r_lucent75.h"

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/vector_class_operations.h"

class ConvertClass;

#include "../_layout/staticvectorholder_0089ecf8.h"

#include "../render/trivial_tu056_methods.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48E520
ControlClass::ControlClass(int id, int x, int y, int width, int height,
                           unsigned int flags, char sticky)
    : GadgetClass(x, y, width, height, flags, sticky), ID(id), Peer(0)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48E570
ControlClass::ControlClass(const ControlClass& other)
    : GadgetClass(other), ID(other.ID), Peer(other.Peer)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48E5A0
int ControlClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (flags != 0) {
        unsigned int id = ID;
        if (id != 0) {
            id |= 0x8000;
            *key = id;
            if ((flags & 0x40) != 0 && (Flags & 0x10) != 0) {
                id |= 0x4000;
                *key = id;
            }
        } else {
            *key = 0;
        }
    }

    if (Peer != 0) {
        Peer->PeerToPeer(flags, key, this);
    }

    return GadgetClass::Action(flags, key, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48E600
void ControlClass::SetPeer(GadgetClass* gadget)
{
    Peer = gadget;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48E610
unsigned int ControlClass::GetID()
{
    return ID;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48E620
int ControlClass::Draw(int forced)
{
    if (Peer) {
        Peer->Draw(0);
    }
    return GadgetClass::Draw(forced);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48E650
// Empty function that pops its stack arguments. Vtable slot 19 of GadgetClass (RTTI) and 14 derived vtable(s).
void Obj_0048E650::FUN_0048E650(int a1, int a2, int a3)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x491390
// DynamicVectorClass<ConvertClass*>::Clear

// FUNCTION: GAMEMD 0x4913C0
// DynamicVectorClass<ConvertClass*>::Slot5

// FUNCTION: GAMEMD 0x4913E0
// VectorClass<ConvertClass*>::Slot6

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491820
// Span: 0x7e bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlat<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransXlat<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int, unsigned short*, unsigned short*, int, int,
                                  const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);

    // Left clip: a nonzero byte uses one skip, a zero byte is followed by a
    // transparent run. An overshoot past zero is transparent output.
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d++ = table[c];
            len--;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4918a0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlat<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransXlat<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4918E0
// RLEBlitTransZRemapXlat<unsigned char>::RLEBlit
template <>
void RLEBlitTransZRemapXlat<unsigned char>::RLEBlit(void* dest, const void* src, int len,
                                        int skip, int, unsigned short*,
                                        unsigned short*, int, int,
                                        const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    typedef unsigned char T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d++ = table[rm[c]];
            len--;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491970
// RLEBlitTransZRemapXlat<unsigned char>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlat<unsigned char>::RLEBlitTint(void* dest, const void* src, int len,
                                            int skip, int zval,
                                            unsigned short* zbuf,
                                            unsigned short* abuf, int alvl,
                                            int warp, const signed char* zshape,
                                            unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4919B0
// Span: 0x74 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDest<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapDest<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int, unsigned short*, unsigned short*, int, int,
                         const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d = table[*d];
            len--;
            d++;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491A30
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDest<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapDest<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491A70
// Span: 0x88 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlat<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapXlat<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int, unsigned short*, unsigned short*, int, int,
                         const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d = table2[table1[c]];
            d++;
            len--;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491B00
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlat<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapXlat<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491b40
// Span: 0xcf bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZRead<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransXlatZRead<T>::RLEBlit(void* dest, const void* src, int len,
                                       int skip, int zval, unsigned short* zbuf,
                                       unsigned short*, int, int,
                                       const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            z += c;
            zs += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = table[c];
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491c10
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZRead<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransXlatZRead<T>::RLEBlitTint(void* dest, const void* src, int len,
                                           int skip, int zval,
                                           unsigned short* zbuf,
                                           unsigned short* abuf, int alvl,
                                           int warp, const signed char* zshape,
                                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491C50
// RLEBlitTransZRemapXlatZRead<unsigned char>::RLEBlit
template <>
void RLEBlitTransZRemapXlatZRead<unsigned char>::RLEBlit(void* dest, const void* src,
                                             int len, int skip, int zval,
                                             unsigned short* zbuf,
                                             unsigned short*, int, int,
                                             const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    typedef unsigned char T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;
    unsigned short* z = zbuf;

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = table[rm[c]];
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491D50
// RLEBlitTransZRemapXlatZRead<unsigned char>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatZRead<unsigned char>::RLEBlitTint(void* dest, const void* src,
                                                 int len, int skip, int zval,
                                                 unsigned short* zbuf,
                                                 unsigned short* abuf, int alvl,
                                                 int warp,
                                                 const signed char* zshape,
                                                 unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491D90
// Span: 0xCA bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZRead<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapDestZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = table[*d];
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491E60
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZRead<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapDestZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491EA0
// Span: 0xE9 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZRead<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapXlatZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = table2[table1[c]];
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491F90
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZRead<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapXlatZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x491fd0
// Span: 0xe1 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZReadWrite<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransXlatZReadWrite<T>::RLEBlit(void* dest, const void* src, int len,
                                       int skip, int zval, unsigned short* zbuf,
                                       unsigned short*, int, int,
                                       const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            unsigned char r = *s++;
            if (r == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                *d++ = table[c];
                *z = zval - *zs;
                z++;
                zs++;
                len--;
            }
            else
            {
                d++;
                z++;
                zs++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4920c0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransXlatZReadWrite<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransXlatZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len,
                                           int skip, int zval,
                                           unsigned short* zbuf,
                                           unsigned short* abuf, int alvl,
                                           int warp, const signed char* zshape,
                                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492100
// RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlit
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlit(void* dest, const void* src,
                                             int len, int skip, int zval,
                                             unsigned short* zbuf,
                                             unsigned short*, int, int,
                                             const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    typedef unsigned char T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;
    unsigned short* z = zbuf;

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z)
            {
                *d++ = table[rm[c]];
                *z++ = zval - *zs++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492210
// RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned char>::RLEBlitTint(void* dest, const void* src,
                                                 int len, int skip, int zval,
                                                 unsigned short* zbuf,
                                                 unsigned short* abuf, int alvl,
                                                 int warp,
                                                 const signed char* zshape,
                                                 unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492250
// Span: 0xDD bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZReadWrite<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapDestZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z)
            {
                *d = table[*d];
                *z = zval - *zs++;
                z++;
                len--;
                d++;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492330
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapDestZReadWrite<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapDestZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492370
// Span: 0x109 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZReadWrite<unsigned char>::RLEBlit
template <class T>
void RLEBlitTransRemapXlatZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                *d++ = table2[table1[c]];
                *z++ = zval - *zs++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492480
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransRemapXlatZReadWrite<unsigned char>::RLEBlitTint
template <class T>
void RLEBlitTransRemapXlatZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492670
// BlitTransDarken<unsigned short>::BlitCopy
template <>
void BlitTransDarken<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    if (len > 0) {
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) *(unsigned short*)dest = (*(unsigned short*)dest >> 1) & mask;
            dest = (unsigned short*)dest + 1;
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4926B0
// BlitTransDarken<unsigned short>::BlitMove
template <>
void BlitTransDarken<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4926E0
// BlitTransDarken<unsigned short>::BlitCopyTint
template <>
void BlitTransDarken<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492710
// BlitTransDarken<unsigned short>::BlitMoveTint
template <>
void BlitTransDarken<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492740
// BlitTransLucent75<unsigned short>::BlitCopy
template <>
void BlitTransLucent75<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c) {
                unsigned short t = xlat[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + 3 * ((*d >> 2) & m);
            }
            ++d;
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4927A0
// BlitTransLucent75<unsigned short>::BlitMove
template <>
void BlitTransLucent75<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4927D0
// BlitTransLucent75<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492800
// BlitTransLucent75<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492830
// BlitTransLucent50<unsigned short>::BlitCopy
template <>
void BlitTransLucent50<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    const unsigned short* table = xlat;
    unsigned m = mask;
    const unsigned char* s = (const unsigned char*)src;
    unsigned short* d = (unsigned short*)dest;
    do {
        unsigned c = *s;
        if (c) {
            unsigned a = table[c] >> 1;
            unsigned b = *d >> 1;
            *d = (unsigned short)((a & m) + (b & m));
        }
        ++s;
        ++d;
    } while (--len > 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492890
// BlitTransLucent50<unsigned short>::BlitMove
template <>
void BlitTransLucent50<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4928C0
// BlitTransLucent50<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4928F0
// BlitTransLucent50<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492920
// BlitTransLucent25<unsigned short>::BlitCopy
template <>
void BlitTransLucent25<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short*, int, int)
{
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c) *d = Lucent25Mix(xlat[c], *d, mask);
            ++d;
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492980
// BlitTransLucent25<unsigned short>::BlitMove
template <>
void BlitTransLucent25<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4929B0
// BlitTransLucent25<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4929E0
// BlitTransLucent25<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492B00
// BlitTransXlatZRead<unsigned short>::BlitCopy
template <>
void BlitTransXlatZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) *(unsigned short*)dest = xlat[c];
            }
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492B70
// BlitTransXlatZRead<unsigned short>::BlitMove
template <>
void BlitTransXlatZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492BA0
// BlitTransXlatZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492BD0
// BlitTransXlatZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492D20
// BlitTransDarkenZRead<unsigned short>::BlitCopy
template <>
void BlitTransDarkenZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        do {
            if (zval < *z++) {
                if (*s) *d = (*d >> 1) & mask;
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492D80
// BlitTransDarkenZRead<unsigned short>::BlitMove
template <>
void BlitTransDarkenZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492DB0
// BlitTransDarkenZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransDarkenZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492DE0
// BlitTransDarkenZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransDarkenZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492E10
// BlitTransLucent75ZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *s;
                if (c) {
                    unsigned short t = xlat[c];
                    unsigned short m = mask;
                    *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492EA0
// BlitTransLucent75ZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492ED0
// BlitTransLucent75ZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x492F00
// BlitTransLucent75ZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75ZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492F30
// BlitTransLucent50ZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *s;
                if (c) {
                    unsigned short a = xlat[c] >> 1;
                    unsigned short b = *d >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492FC0
// BlitTransLucent50ZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x492FF0
// BlitTransLucent50ZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x493020
// BlitTransLucent50ZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493050
// BlitTransLucent25ZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* zp = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *s;
                if (c) *d = Lucent25Mix(xlat[c], *d, mask);
            }
            ++s;
            ++d;
            zp = RLEZWrapRow(zp);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4930E0
// BlitTransLucent25ZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493110
// BlitTransLucent25ZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493140
// BlitTransLucent25ZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25ZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493170
// BlitTransLucent75ZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int warp)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *s;
                if (c) {
                    unsigned short t = xlat[c];
                    unsigned short m = mask;
                    *d = ((d[warp] >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493210
// BlitTransLucent75ZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493240
// BlitTransLucent75ZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493270
// BlitTransLucent75ZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75ZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4932A0
// BlitTransLucent50ZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int warp)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *s;
                if (c) {
                    unsigned short a = xlat[c] >> 1;
                    unsigned short b = d[warp] >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x493340
// BlitTransLucent50ZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x493370
// BlitTransLucent50ZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4933A0
// BlitTransLucent50ZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50ZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4933D0
// BlitTransLucent25ZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int warp)
{
    unsigned short* zp = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *s;
                if (c) *d = Lucent25Mix(xlat[c], d[warp], mask);
            }
            ++s;
            ++d;
            zp = RLEZWrapRow(zp);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493470
// BlitTransLucent25ZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4934A0
// BlitTransLucent25ZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4934D0
// BlitTransLucent25ZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493600
// BlitTransXlatZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        do {
            if (zval < *z) {
                unsigned char c = *s;
                if (c) {
                    *d = xlat[c];
                    *z = zval;
                }
            }
            ++z;
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493680
// BlitTransXlatZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4936B0
// BlitTransXlatZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4936E0
// BlitTransXlatZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransXlatZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493830
// BlitTransDarkenZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        int n = len;
        unsigned short* d = (unsigned short*)dest;
        const unsigned char* s = (const unsigned char*)src;
        do {
            if (zval < *z) {
                if (*s) {
                    *d = (*d >> 1) & mask;
                    *z = zval;
                }
            }
            ++z;
            ++s;
            ++d;
            z = RLEZWrapRow(z);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4938A0
// BlitTransDarkenZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4938D0
// BlitTransDarkenZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493900
// BlitTransDarkenZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransDarkenZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493930
// BlitTransLucent75ZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short t = xlat[c];
                    unsigned short m = mask;
                    *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
                    *z = zval;
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4939D0
// BlitTransLucent75ZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493A00
// BlitTransLucent75ZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493A30
// BlitTransLucent75ZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75ZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x493A60
// BlitTransLucent50ZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* z = zbuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *s;
                if (c) {
                    unsigned short a = xlat[c] >> 1;
                    unsigned short b = *d >> 1;
                    *d = (a & mask) + (b & mask);
                    *z = (unsigned short)zval;
                }
            }
            ++s;
            ++d;
            z = RLEZWrapRow(z + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x493B00
// BlitTransLucent50ZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x493B30
// BlitTransLucent50ZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x493B60
// BlitTransLucent50ZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50ZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493B90
// BlitTransLucent25ZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short*, int, int)
{
    unsigned short* zp = zbuf;
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            int z = *zp;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    *d = Lucent25Mix(xlat[c], *d, mask);
                    *zp = (unsigned short)zval;
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            zp = RLEZWrapRow(zp + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493C30
// BlitTransLucent25ZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493C60
// BlitTransLucent25ZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x493C90
// BlitTransLucent25ZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25ZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494080
// BlitTransLucent75Alpha<unsigned short>::BlitCopy
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) {
                unsigned short m = mask;
                unsigned short t = xlat[row[*a] | c];
                *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
            }
            ++d;
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494150
// BlitTransLucent75Alpha<unsigned short>::BlitMove
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494180
// BlitTransLucent75Alpha<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4941B0
// BlitTransLucent75Alpha<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75Alpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4941E0
// BlitTransLucent50Alpha<unsigned short>::BlitCopy
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) {
                unsigned short a = xlat[row->v[*ap] | c] >> 1;
                unsigned short b = *d >> 1;
                *d = (a & mask) + (b & mask);
            }
            ++d;
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4942A0
// BlitTransLucent50Alpha<unsigned short>::BlitMove
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4942D0
// BlitTransLucent50Alpha<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494300
// BlitTransLucent50Alpha<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50Alpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494330
// BlitTransLucent25Alpha<unsigned short>::BlitCopy
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int alvl, int)
{
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            const unsigned char* s = (const unsigned char*)src;
            unsigned char c = *s++;
            src = s;
            if (c) *d = Lucent25Mix(xlat[tab[*ap] | c], *d, mask);
            ++d;
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494400
// BlitTransLucent25Alpha<unsigned short>::BlitMove
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494430
// BlitTransLucent25Alpha<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494460
// BlitTransLucent25Alpha<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494690
// BlitTranslucentWriteAlpha<unsigned short>::BlitCopy
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int, int)
{
    unsigned short* ap = abuf;
    if (len > 0) {
        int n = len;
        do {
            unsigned char c = *(const unsigned char*)src;
            src = (const unsigned char*)src + 1;
            if (c) {
                int a = *ap;
                int ia = 255 - a;
                if (a == 255) a = 256;
                unsigned char sc[3];
                unsigned char dc[3];
                T sp = table[c];
                sc[0] = (sp >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
                sc[1] = (sp >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
                sc[2] = (sp >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
                T dp = *(T*)dest;
                dc[0] = (dp >> gg_b_translucent_pixel_format.pos0) << gg_b_translucent_pixel_format.loss0;
                dc[1] = (dp >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1;
                dc[2] = (dp >> gg_b_translucent_pixel_format.pos2) << gg_b_translucent_pixel_format.loss2;
                int r = (dc[0] * ia + sc[0] * a) >> 8;
                int g = (dc[1] * ia + sc[1] * a) >> 8;
                int b = (dc[2] * ia + sc[2] * a) >> 8;
                if (b > 255) b = 255;
                int g2 = g > 255 ? 255 : g;
                if (r > 255) r = 255;
                *(T*)dest = ((r >> gg_b_translucent_pixel_format.loss0) << gg_b_translucent_pixel_format.pos0)
                   | ((g2 >> gg_b_translucent_pixel_format.loss1) << gg_b_translucent_pixel_format.pos1)
                   | ((b >> gg_b_translucent_pixel_format.loss2) << gg_b_translucent_pixel_format.pos2);
            }
            dest = (T*)dest + 1;
            ap = BTranslucentWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494890
// BlitTranslucentWriteAlpha<unsigned short>::BlitMove
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4948C0
// BlitTranslucentWriteAlpha<unsigned short>::BlitCopyTint
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4948F0
// BlitTranslucentWriteAlpha<unsigned short>::BlitMoveTint
template <class T>
void BlitTranslucentWriteAlpha<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494920
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitCopy
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int, int)
{
    unsigned short* ap = abuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        T* d = (T*)dest;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c && *ap) {
                T m = mask;
                *d = ((table[c] >> 1) & m) + ((*d >> 1) & m);
            }
            ++d;
            ap = BTranslucentWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4949B0
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitMove
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4949E0
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitCopyTint
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494A10
// BlitTranslucent50NonzeroAlpha<unsigned short>::BlitMoveTint
template <class T>
void BlitTranslucent50NonzeroAlpha<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494A40
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitCopy
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitCopy(void* dest, const void* src, int len, int, unsigned short*, unsigned short* abuf, int, int)
{
    unsigned short* ap = abuf;
    if (len > 0) {
        const unsigned char* s = (const unsigned char*)src;
        T* d = (T*)dest;
        int n = len;
        do {
            unsigned char c = *s++;
            if (c && !*ap) {
                T m = mask;
                *d = ((table[c] >> 1) & m) + ((*d >> 1) & m);
            }
            ++d;
            ap = BTranslucentWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494AD0
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitMove
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494B00
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitCopyTint
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x494B30
// BlitTranslucent50ZeroAlpha<unsigned short>::BlitMoveTint
template <class T>
void BlitTranslucent50ZeroAlpha<T>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x494F20
// BlitTransLucent75AlphaZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short m = mask;
                    unsigned short t = xlat[row[*a] | c];
                    *d = ((*d >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495030
// BlitTransLucent75AlphaZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495060
// BlitTransLucent75AlphaZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495090
// BlitTransLucent75AlphaZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75AlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4950C0
// BlitTransLucent50AlphaZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short a = xlat[row->v[*ap] | c] >> 1;
                    unsigned short b = *d >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4951C0
// BlitTransLucent50AlphaZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4951F0
// BlitTransLucent50AlphaZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x495220
// BlitTransLucent50AlphaZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50AlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495250
// BlitTransLucent25AlphaZRead<unsigned short>::BlitCopy
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* zp = zbuf;
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) *d = Lucent25Mix(xlat[tab[*ap] | c], *d, mask);
            }
            ++d;
            src = (const unsigned char*)src + 1;
            zp = RLEZWrapRow(zp);
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495360
// BlitTransLucent25AlphaZRead<unsigned short>::BlitMove
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495390
// BlitTransLucent25AlphaZRead<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4953C0
// BlitTransLucent25AlphaZRead<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25AlphaZRead<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4953F0
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int warp)
{
    unsigned short* z = zbuf;
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short m = mask;
                    unsigned short t = xlat[row[*a] | c];
                    *d = ((d[warp] >> 2) & m) * 3 + ((t >> 2) & m);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495500
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495530
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495560
// BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75AlphaZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x495590
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int warp)
{
    unsigned short* z = zbuf;
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            if (zval < *z++) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short a = xlat[row->v[*ap] | c] >> 1;
                    unsigned short b = d[warp] >> 1;
                    *d = (a & mask) + (b & mask);
                }
            }
            src = (const unsigned char*)src + 1;
            ++d;
            z = RLEZWrapRow(z);
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4956A0
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4956D0
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x495700
// BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50AlphaZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495730
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopy
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int warp)
{
    unsigned short* zp = zbuf;
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        unsigned short* d = (unsigned short*)dest;
        int n = len;
        do {
            int z = *zp++;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) *d = Lucent25Mix(xlat[tab[*ap] | c], d[warp], mask);
            }
            ++d;
            src = (const unsigned char*)src + 1;
            zp = RLEZWrapRow(zp);
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495840
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMove
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495870
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4958A0
// BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25AlphaZReadWarp<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495BC0
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* a = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 0xFE)
        level = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (level << 9));
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short m = mask;
                    unsigned short t = xlat[row[*a] | c];
                    *(unsigned short*)dest = ((*(unsigned short*)dest >> 2) & m) * 3 + ((t >> 2) & m);
                    *z = zval;
                }
            }
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z + 1);
            a = BLucent75AlphaWrapRow(a + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495CD0
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495D00
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495D30
// BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent75AlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x495D60
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* z = zbuf;
    unsigned short* ap = abuf;
    const BlitAlphaRow256* row = alpha + AlphaRowIndex(alvl);
    if (len > 0) {
        int n = len;
        do {
            if (zval < *z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    unsigned short a = xlat[row->v[*ap] | c] >> 1;
                    unsigned short b = *(unsigned short*)dest >> 1;
                    *(unsigned short*)dest = (a & mask) + (b & mask);
                    *z = (unsigned short)zval;
                }
            }
            src = (const unsigned char*)src + 1;
            dest = (unsigned short*)dest + 1;
            z = RLEZWrapRow(z + 1);
            ap = AlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Slots 2-4: forwarding shims (call slot 1 with warp = 0), one group per class.
// TEMPLATE: GAMEMD 0x495E70
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x495EA0
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x495ED0
// BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent50AlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x495F00
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopy
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopy(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int)
{
    unsigned short* zp = zbuf;
    unsigned short* ap = abuf;
    const unsigned short* tab = (const unsigned short*)((const unsigned char*)alpha + Lucent25AlphaRow(alvl));
    if (len > 0) {
        int n = len;
        do {
            int z = *zp;
            if (zval < z) {
                unsigned char c = *(const unsigned char*)src;
                if (c) {
                    *(unsigned short*)dest = Lucent25Mix(xlat[tab[*ap] | c], *(unsigned short*)dest, mask);
                    *zp = (unsigned short)zval;
                }
            }
            dest = (unsigned short*)dest + 1;
            src = (const unsigned char*)src + 1;
            zp = RLEZWrapRow(zp + 1);
            ap = BlitAlphaWrapRow(ap + 1);
        } while (--n);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x496010
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMove
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMove(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x496040
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopyTint
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitCopyTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, int, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x496070
// BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMoveTint
template <>
void BlitTransLucent25AlphaZReadWrite<unsigned short>::BlitMoveTint(void* dest, const void* src, int len, int zval, unsigned short* zbuf, unsigned short* abuf, int alvl, unsigned short)
{
    BlitCopy(dest, src, len, zval, zbuf, abuf, alvl, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496170
// RLEBlitTransZRemapXlat<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlat<unsigned short>::RLEBlit(void* dest, const void* src, int len,
                                        int skip, int, unsigned short*,
                                        unsigned short*, int, int,
                                        const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    typedef unsigned short T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d++ = table[rm[c]];
            len--;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496210
// RLEBlitTransZRemapXlat<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlat<unsigned short>::RLEBlitTint(void* dest, const void* src, int len,
                                            int skip, int zval,
                                            unsigned short* zbuf,
                                            unsigned short* abuf, int alvl,
                                            int warp, const signed char* zshape,
                                            unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496250
// Span: 0x79 bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarken<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransDarken<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int, unsigned short*, unsigned short*, int, int,
                         const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d = (*d >> 1) & mask;
            len--;
            d++;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4962D0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarken<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransDarken<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496310
// RLEBlitTransLucent75<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75<unsigned short>::RLEBlit(void* dest, const void* src, int len,
                                      int skip, int, unsigned short*,
                                      unsigned short*, int, int,
                                      const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            unsigned short t = table[c];
            unsigned short m = mask;
            *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
            d++;
            len--;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4963B0
// RLEBlitTransLucent75<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75<unsigned short>::RLEBlitTint(void* dest, const void* src, int len,
                                          int skip, int zval,
                                          unsigned short* zbuf,
                                          unsigned short* abuf, int alvl,
                                          int warp, const signed char* zshape,
                                          unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4963F0
// RLEBlitTransLucent50<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int, unsigned short*, unsigned short*, int, int,
                                      const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d = ((table[c] >> 1) & mask) + ((*d >> 1) & mask);
            len--;
            d++;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496490
// RLEBlitTransLucent50<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                          int zval, unsigned short* zbuf,
                                          unsigned short* abuf, int alvl, int warp,
                                          const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4964D0
// Span: 0x9F bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25<T>::RLEBlit(void* dest, const void* src, int len,
                                      int skip, int, unsigned short*,
                                      unsigned short*, int, int,
                                      const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            *d = 3 * ((palette[c] >> 2) & mask) + ((*d >> 2) & mask);
            d++;
            len--;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496570
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25<T>::RLEBlitTint(void* dest, const void* src, int len,
                                          int skip, int zval,
                                          unsigned short* zbuf,
                                          unsigned short* abuf, int alvl,
                                          int warp, const signed char* zshape,
                                          unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4966D0
// RLEBlitTransZRemapXlatZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatZRead<unsigned short>::RLEBlit(void* dest, const void* src,
                                             int len, int skip, int zval,
                                             unsigned short* zbuf,
                                             unsigned short*, int, int,
                                             const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    typedef unsigned short T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;
    unsigned short* z = zbuf;

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = table[rm[c]];
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4967E0
// RLEBlitTransZRemapXlatZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatZRead<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                                 int len, int skip, int zval,
                                                 unsigned short* zbuf,
                                                 unsigned short* abuf, int alvl,
                                                 int warp,
                                                 const signed char* zshape,
                                                 unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496820
// Span: 0xCB bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZRead<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransDarkenZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    unsigned short* zb = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    const signed char* zs = zshape;
    if (skip > 0) {
        do {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        } while (skip > 0);
        int over = -skip;
        len -= over;
        d += over;
        zb = RLEZWrapRow(zb + over);
    }
    while (len > 0) {
        if (*s++ == 0) {
            unsigned char run = *s++;
            len -= run;
            d += run;
            zs += run;
            zb += run;
        } else {
            if (zval - *zs++ < *zb++) {
                *d = (T)((*d >> 1) & mask);
                len--;
                d++;
            } else {
                len--;
                d++;
            }
        }
        zb = RLEZWrapRow(zb);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4968F0
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZRead<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransDarkenZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496930
// RLEBlitTransLucent75ZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75ZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short*, int,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short t = table[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496A40
// RLEBlitTransLucent75ZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75ZRead<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short* abuf, int alvl,
                                               int warp,
                                               const signed char* zshape,
                                               unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496A80
// RLEBlitTransLucent50ZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50ZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf, unsigned short*,
                                  int, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(z + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = ((table[c] >> 1) & mask) + ((*d >> 1) & mask);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496B80
// RLEBlitTransLucent50ZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50ZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf,
                                  unsigned short* abuf, int alvl, int warp,
                                  const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496BC0
// Span: 0x106 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZRead<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25ZRead<T>::RLEBlit(void* dest, const void* src, int len,
                                           int skip, int zval,
                                           unsigned short* zbuf,
                                           unsigned short*, int, int,
                                           const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = 3 * ((palette[c] >> 2) & mask) + ((*d >> 2) & mask);
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496CD0
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZRead<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25ZRead<T>::RLEBlitTint(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short* abuf, int alvl,
                                               int warp,
                                               const signed char* zshape,
                                               unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496D10
// RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short*, int,
                       int warp, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short t = table[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + ((d[warp] >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496E20
// RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75ZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                                   int len, int skip, int zval,
                                                   unsigned short* zbuf,
                                                   unsigned short* abuf,
                                                   int alvl, int warp,
                                                   const signed char* zshape,
                                                   unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496E60
// RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf, unsigned short*,
                                  int, int warp, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(z + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = ((table[c] >> 1) & mask) + ((d[warp] >> 1) & mask);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496F70
// RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50ZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf,
                                  unsigned short* abuf, int alvl, int warp,
                                  const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x496FB0
// Span: 0x10B bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWarp<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25ZReadWarp<T>::RLEBlit(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short*, int, int warp,
                                               const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                *d = 3 * ((palette[c] >> 2) & mask) + ((d[warp] >> 2) & mask);
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4970C0
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWarp<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25ZReadWarp<T>::RLEBlitTint(void* dest, const void* src,
                                                   int len, int skip, int zval,
                                                   unsigned short* zbuf,
                                                   unsigned short* abuf,
                                                   int alvl, int warp,
                                                   const signed char* zshape,
                                                   unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497230
// RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src,
                                             int len, int skip, int zval,
                                             unsigned short* zbuf,
                                             unsigned short*, int, int,
                                             const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    typedef unsigned short T;
    T* d = static_cast<T*>(dest);
    const unsigned char* rm = *remap;
    unsigned short* z = zbuf;

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs++ < *z)
            {
                *d++ = table[rm[c]];
                *z++ = zval - *zs++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497350
// RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                                 int len, int skip, int zval,
                                                 unsigned short* zbuf,
                                                 unsigned short* abuf, int alvl,
                                                 int warp,
                                                 const signed char* zshape,
                                                 unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497390
// Span: 0xDD bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZReadWrite<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransDarkenZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short*, int, int,
                         const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }
    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                *d = (*d >> 1) & mask;
                *z = zval - *zs++;
                z++;
                len--;
                d++;
            }
            else
            {
                zs++;
                len--;
                z++;
                d++;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497470
// Span: 0x3a bytes from the retail entry, including the complete RET immediate.
// RLEBlitTransDarkenZReadWrite<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransDarkenZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                         int zval, unsigned short* zbuf, unsigned short* abuf,
                         int alvl, int warp, const signed char* zshape,
                         unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4974B0
// RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short*, int,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    unsigned short* d = static_cast<unsigned short*>(dest);
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short t = table[c];
                unsigned short m = mask;
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                *z = zval - *zs;
                zs++;
                d++;
                z++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4975D0
// RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75ZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                                    int len, int skip, int zval,
                                                    unsigned short* zbuf,
                                                    unsigned short* abuf,
                                                    int alvl, int warp,
                                                    const signed char* zshape,
                                                    unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497610
// RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf, unsigned short*,
                                  int, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(z + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                *d = ((table[c] >> 1) & mask) + ((*d >> 1) & mask);
                *z = zval - *zs;
                z++;
                zs++;
                len--;
                d++;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497720
// RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50ZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                  int zval, unsigned short* zbuf,
                                  unsigned short* abuf, int alvl, int warp,
                                  const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497760
// Span: 0x116 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWrite<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25ZReadWrite<T>::RLEBlit(void* dest, const void* src,
                                                int len, int skip, int zval,
                                                unsigned short* zbuf,
                                                unsigned short*, int, int,
                                                const signed char* zshape)
{
    unsigned short* z = zbuf;
    T* d = static_cast<T*>(dest);
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);


    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                *d = 3 * ((palette[c] >> 2) & mask) + ((*d >> 2) & mask);
                *z = zval - *zs;
                zs++;
                d++;
                z++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
        }
        z = RLEZWrapRow(z);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497880
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25ZReadWrite<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25ZReadWrite<T>::RLEBlitTint(void* dest, const void* src,
                                                    int len, int skip, int zval,
                                                    unsigned short* zbuf,
                                                    unsigned short* abuf,
                                                    int alvl, int warp,
                                                    const signed char* zshape,
                                                    unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4978C0
// RLEBlitTransXlatAlpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransXlatAlpha<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                       int, unsigned short*, unsigned short* abuf,
                                       int alvl, int, const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    int idx = (a * 261) >> 11;
    if (idx > 0xFE)
        idx = 0xFE;
    const unsigned short* row = (const unsigned short*)((const unsigned char*)alpha + (idx << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        ab += over;
        ab = RLEAlphaWrapRow(ab);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            ab += c;
        }
        else
        {
            *d++ = table[row[*ab] | c];
            len--;
            ab++;
        }
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4979D0
// RLEBlitTransXlatAlpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransXlatAlpha<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497A10
// RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlit(void* dest, const void* src, int len,
                                                          int skip, int, unsigned short*,
                                                          unsigned short* abuf, int alvl, int,
                                                          const signed char*)
{
    const unsigned char* s = (const unsigned char*)src;
    unsigned short* d = (unsigned short*)dest;
    const unsigned char* rt = *remap;
    unsigned short* ab = abuf;
    int level = alvl > 0 ? alvl : 0;
    level = (level * 261) >> 11;
    if (level > 254)
        level = 254;
    unsigned short* row = alpha + (level << 8);
    if (skip > 0) {
        do {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        } while (skip > 0);
        int over = -skip;
        len -= over;
        d += over;
        ab = ab + over;
        if (ab >= gg_blit_alpha_wrap_global->wrap_end)
            ab = (unsigned short*)((unsigned char*)ab - gg_blit_alpha_wrap_global->wrap_step);
    }
    while (len > 0) {
        unsigned char c = *s++;
        if (c == 0) {
            c = *s++;
            len -= c;
            d += c;
            ab += c;
        } else {
            *d++ = table[row[*ab] | rt[c]];
            len--;
            ab++;
        }
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497B40
// RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatAlpha<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497B80
// RLEBlitTransLucent75Alpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75Alpha<unsigned short>::RLEBlit(void* dest, const void* src, int len,
                                           int skip, int, unsigned short*,
                                           unsigned short* abuf, int alvl, int,
                                           const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ap = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    unsigned short* ar = (unsigned short*)((unsigned char*)rows + (a << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        ap = RLELucent75AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            ap += c;
        }
        else
        {
            unsigned short m = mask;
            unsigned short t = table[ar[*ap] | c];
            *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
            d++;
            len--;
            ap++;
        }
        ap = RLELucent75AlphaWrapRow(ap);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497CB0
// RLEBlitTransLucent75Alpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75Alpha<unsigned short>::RLEBlitTint(void* dest, const void* src,
                                               int len, int skip, int zval,
                                               unsigned short* zbuf,
                                               unsigned short* abuf, int alvl,
                                               int warp,
                                               const signed char* zshape,
                                               unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497CF0
// RLEBlitTransLucent50Alpha<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50Alpha<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                                           int, unsigned short*, unsigned short* abuf,
                                           int alvl, int, const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_handle) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        ab = RLELucent50AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            ab += c;
        }
        else
        {
            unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
            *d = ((table[idx] >> 1) & mask) + ((*d >> 1) & mask);
            d++;
            len--;
            ab++;
        }
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497E20
// RLEBlitTransLucent50Alpha<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50Alpha<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                               int zval, unsigned short* zbuf,
                                               unsigned short* abuf, int alvl, int warp,
                                               const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497E60
// Span: 0x12D bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25Alpha<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25Alpha<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int, unsigned short*, unsigned short* abuf, int alvl, int,
                                      const signed char*)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    T* d = static_cast<T*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        ab = RLEL25AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            ab += c;
        }
        else
        {
            unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
            *d = 3 * ((palette[idx] >> 2) & mask) + ((*d >> 2) & mask);
            d++;
            len--;
            ab++;
        }
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497F90
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25Alpha<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25Alpha<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x497FD0
// RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEAlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d++ = table[idx];
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498150
// RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransXlatAlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape, unsigned short tint)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEAlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d++ = (unsigned short)(table[idx] | tint);
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4982E0
// RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    const unsigned char* rm = *remap;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEAlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | rm[c];
                *d++ = table[idx];
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498490
// RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatAlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4984D0
// RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(rows) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent75AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short m = mask;
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent75AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498690
// RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75AlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                           int zval, unsigned short* zbuf, unsigned short* abuf,
                           int alvl, int warp, const signed char* zshape,
                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4986D0
// RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf, unsigned short* abuf,
                        int alvl, int, const signed char* zshape)
{
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned short* row = (const unsigned short*)((char*)alpha_handle + (a << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            unsigned char r = *s++;
            if (r == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent50AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            zs += c;
            z += c;
            d += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short m = mask;
                unsigned short t = table[row[*ab] | c];
                *d = ((t >> 1) & m) + ((*d >> 1) & m);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498880
// RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50AlphaZRead<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                            int zval, unsigned short* zbuf,
                            unsigned short* abuf, int alvl, int warp,
                            const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4988C0
// Span: 0x1BB bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZRead<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25AlphaZRead<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf, unsigned short* abuf,
                                      int alvl, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEL25AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = 3 * ((palette[idx] >> 2) & mask) + ((*d >> 2) & mask);
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498A80
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZRead<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25AlphaZRead<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498AC0
// RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int warp, const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(rows) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent75AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            zs += c;
            z += c;
            d += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short m = mask;
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 2) & m) + ((d[warp] >> 2) & m) * 3;
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent75AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498C90
// RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75AlphaZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                           int zval, unsigned short* zbuf, unsigned short* abuf,
                           int alvl, int warp, const signed char* zshape,
                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498CD0
// RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int warp, const signed char* zshape)
{
    const signed char* zs = zshape;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned short* row = (const unsigned short*)((char*)alpha_handle + (a << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            unsigned char r = *s++;
            if (r == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent50AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            zs += c;
            z += c;
            d += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short m = mask;
                unsigned short t = table[row[*ab] | c];
                *d = ((t >> 1) & m) + ((d[warp] >> 1) & m);
                len--;
                d++;
            }
            else
            {
                len--;
                d++;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498E90
// RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50AlphaZReadWarp<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                            int zval, unsigned short* zbuf,
                            unsigned short* abuf, int alvl, int warp,
                            const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x498ED0
// Span: 0x1C6 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWarp<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25AlphaZReadWarp<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf, unsigned short* abuf,
                                      int alvl, int warp, const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEL25AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            zs += c;
            z += c;
            d += c;
            ab += c;
        }
        else
        {
            if (zval - *zs++ < *z++)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = 3 * ((palette[idx] >> 2) & mask) + ((d[warp] >> 2) & mask);
                d++;
                len--;
            }
            else
            {
                d++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4990A0
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWarp<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25AlphaZReadWarp<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x4990E0
// RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEAlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = table[idx];
                *z = zval - *zs;
                d++;
                zs++;
                z++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499280
// RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransXlatAlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape, unsigned short tint)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEAlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = (unsigned short)(table[idx] | tint);
                *z = zval - *zs;
                d++;
                zs++;
                z++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499430
// RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
    unsigned short* zbuf, unsigned short* abuf, int alvl, int warp,
    const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const unsigned char* rm = *remap;
    int a = alvl > 0 ? alvl : 0;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    const signed char* zs = zshape;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha) + (a << 9);
    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEAlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | rm[c];
                *d = table[idx];
                *z = zval - *zs;
                d++;
                zs++;
                z++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEAlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499610
// RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                        int zval, unsigned short* zbuf,
                        unsigned short* abuf, int alvl, int warp,
                        const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499650
// RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    unsigned short* d = static_cast<unsigned short*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(rows) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent75AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short m = mask;
                unsigned short t = table[*reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c];
                *d = ((t >> 2) & m) + ((*d >> 2) & m) * 3;
                *z = zval - *zs;
                d++;
                zs++;
                z++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent75AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499820
// RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                           int zval, unsigned short* zbuf, unsigned short* abuf,
                           int alvl, int warp, const signed char* zshape,
                           unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499860
// RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlit
template <>
void RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlit(void* dest, const void* src, int len, int skip, int zval,
                       unsigned short* zbuf, unsigned short* abuf, int alvl,
                       int, const signed char* zshape)
{
    const unsigned char* s = static_cast<const unsigned char*>(src);
    unsigned short* d = static_cast<unsigned short*>(dest);
    const signed char* zs = zshape;
    unsigned short* z = zbuf;
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned short* row = (const unsigned short*)((char*)alpha_handle + (a << 9));

    if (skip > 0)
    {
        while (skip > 0)
        {
            unsigned char r = *s++;
            if (r == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLELucent50AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short m = mask;
                unsigned short t = table[row[*ab] | c];
                *d = ((t >> 1) & m) + ((*d >> 1) & m);
                *z++ = zval - *zs++;
                len--;
                d++;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLELucent50AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499A50
// RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlitTint
template <>
void RLEBlitTransLucent50AlphaZReadWrite<unsigned short>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                            int zval, unsigned short* zbuf,
                            unsigned short* abuf, int alvl, int warp,
                            const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499A90
// Span: 0x1C9 bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWrite<unsigned short>::RLEBlit
template <class T>
void RLEBlitTransLucent25AlphaZReadWrite<T>::RLEBlit(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf, unsigned short* abuf,
                                      int alvl, int, const signed char* zshape)
{
    unsigned short* z = zbuf;
    const unsigned char* s = static_cast<const unsigned char*>(src);
    const signed char* zs = zshape;
    T* d = static_cast<T*>(dest);
    unsigned short* ab = abuf;
    int a = alvl > 0 ? alvl : 0;
    a = (a * 261) >> 11;
    if (a > 0xFE)
        a = 0xFE;
    const unsigned char* atab = reinterpret_cast<const unsigned char*>(alpha_tab) + (a << 9);

    if (skip > 0)
    {
        while (skip > 0)
        {
            if (*s++ == 0)
                skip -= *s++;
            else
                skip--;
        }
        int over = -skip;
        d += over;
        len -= over;
        z = RLEZWrapRow(zbuf + over);
        ab = RLEL25AlphaWrapRow(abuf + over);
    }

    while (len > 0)
    {
        unsigned char c = *s++;
        if (c == 0)
        {
            c = *s++;
            len -= c;
            d += c;
            zs += c;
            z += c;
            ab += c;
        }
        else
        {
            if (zval - *zs < *z)
            {
                unsigned short idx = *reinterpret_cast<const unsigned short*>(atab + *ab * 2) | c;
                *d = 3 * ((palette[idx] >> 2) & mask) + ((*d >> 2) & mask);
                *z = zval - *zs;
                d++;
                zs++;
                z++;
                len--;
            }
            else
            {
                zs++;
                d++;
                z++;
                len--;
            }
            ab++;
        }
        z = RLEZWrapRow(z);
        ab = RLEL25AlphaWrapRow(ab);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x499C60
// Span: 0x3A bytes from the retail entry, including its complete RET immediate.
// RLEBlitTransLucent25AlphaZReadWrite<unsigned short>::RLEBlitTint
template <class T>
void RLEBlitTransLucent25AlphaZReadWrite<T>::RLEBlitTint(void* dest, const void* src, int len, int skip,
                                      int zval, unsigned short* zbuf,
                                      unsigned short* abuf, int alvl, int warp,
                                      const signed char* zshape, unsigned short)
{
    RLEBlit(dest, src, len, skip, zval, zbuf, abuf, alvl, warp, zshape);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x499D20
// BlitTransZRemapXlat<unsigned char> scalar deleting destructor
template class BlitTransZRemapXlat<unsigned char>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x499D80
// RLEBlitTransXlat<unsigned char> scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x499DA0
// RLEBlitter scalar deleting destructor

// SYNTHETIC: GAMEMD 0x499DE0
// RLEBlitTransRemapDest<unsigned char> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x499E00
// RLEBlitTransRemapXlat<unsigned char> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x499E20
// RLEBlitTransXlatZRead<unsigned char> scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x499E60
// RLEBlitTransRemapDestZRead<unsigned char> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x499E80
// RLEBlitTransRemapXlatZRead<unsigned char> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x499EA0
// RLEBlitTransXlatZReadWrite<unsigned char> scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x499EE0
// RLEBlitTransRemapDestZReadWrite<unsigned char> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x499F00
// RLEBlitTransRemapXlatZReadWrite<unsigned char> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x499F40
// BlitTransZRemapXlat<unsigned short> scalar deleting destructor
template class BlitTransZRemapXlat<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x499F80
// BlitTransLucent75<unsigned short> scalar deleting destructor
template class BlitTransLucent75<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x499FC0
// BlitTransLucent25<unsigned short> scalar deleting destructor
template class BlitTransLucent25<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A020
// BlitTransZRemapXlatZRead<unsigned short> scalar deleting destructor
template class BlitTransZRemapXlatZRead<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A060
// BlitTransLucent75ZRead<unsigned short> scalar deleting destructor
template class BlitTransLucent75ZRead<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A0A0
// BlitTransLucent25ZRead<unsigned short> scalar deleting destructor
template class BlitTransLucent25ZRead<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A0C0
// BlitTransLucent75ZReadWarp<unsigned short> scalar deleting destructor
template class BlitTransLucent75ZReadWarp<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A100
// BlitTransLucent25ZReadWarp<unsigned short> scalar deleting destructor
template class BlitTransLucent25ZReadWarp<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A160
// BlitTransZRemapXlatZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransZRemapXlatZReadWrite<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A1A0
// BlitTransLucent75ZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransLucent75ZReadWrite<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A1E0
// BlitTransLucent25ZReadWrite<unsigned short> scalar deleting destructor
template class BlitTransLucent25ZReadWrite<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A200
//
// The scalar-deleting destructor of one of these objects. It reseats the
// vtable to this class, drops the reference the object holds on its registry
// handle, clears the handle, lets the inlined empty base destructor reseat the
// vtable to the base class, and finally frees the object itself when the
// caller set the deleting bit. The rest of this file is the same body once per
// class, which is how retail lays the family out: a run of identical 0x3B-byte
// functions differing only in the two vtables they store.
void* CachedResourceOwner8::FUN_0049A200(char flags)
{
    Vptr = &VT_007E57F8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A240
//
// As above, for the class whose vtable is at 0x007E57E0.
void* CachedResourceOwner8::FUN_0049A240(char flags)
{
    Vptr = &VT_007E57E0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A280
//
// As above, for the class whose vtable is at 0x007E57C8.
void* CachedResourceOwnerC::FUN_0049A280(char flags)
{
    Vptr = &VT_007E57C8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A2C0
//
// As above, for the class whose vtable is at 0x007E57B0.
void* CachedResourceOwner8::FUN_0049A2C0(char flags)
{
    Vptr = &VT_007E57B0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A300
//
// As above, for the class whose vtable is at 0x007E5798.
void* CachedResourceOwner8::FUN_0049A300(char flags)
{
    Vptr = &VT_007E5798;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A340
//
// As above, for the class whose vtable is at 0x007E5780.
void* CachedResourceOwner8::FUN_0049A340(char flags)
{
    Vptr = &VT_007E5780;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A3C0
// BlitTranslucentWriteAlpha<unsigned short> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x49A3E0
// BlitTranslucent50NonzeroAlpha<unsigned short> scalar deleting destructor
// SYNTHETIC: GAMEMD 0x49A400
// BlitTranslucent50ZeroAlpha<unsigned short> scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A420
//
// As above, for the class whose vtable is at 0x007E56F0.
void* CachedResourceOwner8::FUN_0049A420(char flags)
{
    Vptr = &VT_007E56F0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A460
//
// As above, for the class whose vtable is at 0x007E56D8.
void* CachedResourceOwnerC::FUN_0049A460(char flags)
{
    Vptr = &VT_007E56D8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A4A0
//
// As above, for the class whose vtable is at 0x007E56C0.
void* CachedResourceOwner8::FUN_0049A4A0(char flags)
{
    Vptr = &VT_007E56C0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A4E0
//
// As above, for the class whose vtable is at 0x007E56A8.
void* CachedResourceOwner8::FUN_0049A4E0(char flags)
{
    Vptr = &VT_007E56A8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A520
//
// As above, for the class whose vtable is at 0x007E5690.
void* CachedResourceOwner8::FUN_0049A520(char flags)
{
    Vptr = &VT_007E5690;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A560
//
// As above, for the class whose vtable is at 0x007E5678.
void* CachedResourceOwner8::FUN_0049A560(char flags)
{
    Vptr = &VT_007E5678;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A5A0
//
// As above, for the class whose vtable is at 0x007E5660.
void* CachedResourceOwner8::FUN_0049A5A0(char flags)
{
    Vptr = &VT_007E5660;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A5E0
//
// As above, for the class whose vtable is at 0x007E5648.
void* CachedResourceOwner8::FUN_0049A5E0(char flags)
{
    Vptr = &VT_007E5648;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A620
//
// As above, for the class whose vtable is at 0x007E5630.
void* CachedResourceOwner8::FUN_0049A620(char flags)
{
    Vptr = &VT_007E5630;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A660
//
// As above, for the class whose vtable is at 0x007E5618.
void* CachedResourceOwnerC::FUN_0049A660(char flags)
{
    Vptr = &VT_007E5618;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A6A0
//
// As above, for the class whose vtable is at 0x007E5600.
void* CachedResourceOwner8::FUN_0049A6A0(char flags)
{
    Vptr = &VT_007E5600;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A6E0
//
// As above, for the class whose vtable is at 0x007E55E8.
void* CachedResourceOwner8::FUN_0049A6E0(char flags)
{
    Vptr = &VT_007E55E8;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049A720
//
// As above, for the class whose vtable is at 0x007E55D0.
void* CachedResourceOwner8::FUN_0049A720(char flags)
{
    Vptr = &VT_007E55D0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5B88;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A7A0
// RLEBlitTransDarken<unsigned short> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x49A7C0
// RLEBlitTransLucent75<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A7E0
// RLEBlitTransLucent50<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A800
// RLEBlitTransLucent25<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A860
// RLEBlitTransDarkenZRead<unsigned short> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x49A880
// RLEBlitTransLucent75ZRead<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75ZRead<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A8A0
// RLEBlitTransLucent50ZRead<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50ZRead<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A8C0
// RLEBlitTransLucent25ZRead<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25ZRead<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A8E0
// RLEBlitTransLucent75ZReadWarp<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75ZReadWarp<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A900
// RLEBlitTransLucent50ZReadWarp<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50ZReadWarp<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A920
// RLEBlitTransLucent25ZReadWarp<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25ZReadWarp<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A980
// RLEBlitTransDarkenZReadWrite<unsigned short> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x49A9A0
// RLEBlitTransLucent75ZReadWrite<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent75ZReadWrite<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A9C0
// RLEBlitTransLucent50ZReadWrite<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent50ZReadWrite<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x49A9E0
// RLEBlitTransLucent25ZReadWrite<unsigned short> scalar deleting destructor
template class RLEBlitTransLucent25ZReadWrite<unsigned short>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AA00
//
// As above, for the class whose vtable is at 0x007E5470.
void* CachedResourceOwner8::FUN_0049AA00(char flags)
{
    Vptr = &VT_007E5470;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AA40
//
// As above, for the class whose vtable is at 0x007E5460.
void* CachedResourceOwnerC::FUN_0049AA40(char flags)
{
    Vptr = &VT_007E5460;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AA80
//
// As above, for the class whose vtable is at 0x007E5450.
void* CachedResourceOwner8::FUN_0049AA80(char flags)
{
    Vptr = &VT_007E5450;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AAC0
//
// As above, for the class whose vtable is at 0x007E5440.
void* CachedResourceOwner8::FUN_0049AAC0(char flags)
{
    Vptr = &VT_007E5440;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AB00
//
// As above, for the class whose vtable is at 0x007E5430.
void* CachedResourceOwner8::FUN_0049AB00(char flags)
{
    Vptr = &VT_007E5430;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AB40
//
// As above, for the class whose vtable is at 0x007E5420.
void* CachedResourceOwner8::FUN_0049AB40(char flags)
{
    Vptr = &VT_007E5420;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AB80
//
// As above, for the class whose vtable is at 0x007E5410.
void* CachedResourceOwnerC::FUN_0049AB80(char flags)
{
    Vptr = &VT_007E5410;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049ABC0
//
// As above, for the class whose vtable is at 0x007E5400.
void* CachedResourceOwner8::FUN_0049ABC0(char flags)
{
    Vptr = &VT_007E5400;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AC00
//
// As above, for the class whose vtable is at 0x007E53F0.
void* CachedResourceOwner8::FUN_0049AC00(char flags)
{
    Vptr = &VT_007E53F0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AC40
//
// As above, for the class whose vtable is at 0x007E53E0.
void* CachedResourceOwner8::FUN_0049AC40(char flags)
{
    Vptr = &VT_007E53E0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AC80
//
// As above, for the class whose vtable is at 0x007E53D0.
void* CachedResourceOwner8::FUN_0049AC80(char flags)
{
    Vptr = &VT_007E53D0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049ACC0
//
// As above, for the class whose vtable is at 0x007E53C0.
void* CachedResourceOwner8::FUN_0049ACC0(char flags)
{
    Vptr = &VT_007E53C0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AD00
//
// As above, for the class whose vtable is at 0x007E53B0.
void* CachedResourceOwner8::FUN_0049AD00(char flags)
{
    Vptr = &VT_007E53B0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AD40
//
// As above, for the class whose vtable is at 0x007E53A0.
void* CachedResourceOwner8::FUN_0049AD40(char flags)
{
    Vptr = &VT_007E53A0;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AD80
//
// As above, for the class whose vtable is at 0x007E5390.
void* CachedResourceOwnerC::FUN_0049AD80(char flags)
{
    Vptr = &VT_007E5390;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049ADC0
//
// As above, for the class whose vtable is at 0x007E5380.
void* CachedResourceOwner8::FUN_0049ADC0(char flags)
{
    Vptr = &VT_007E5380;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AE00
//
// As above, for the class whose vtable is at 0x007E5370.
void* CachedResourceOwner8::FUN_0049AE00(char flags)
{
    Vptr = &VT_007E5370;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0049AE40
//
// As above, for the class whose vtable is at 0x007E5360.
void* CachedResourceOwner8::FUN_0049AE40(char flags)
{
    Vptr = &VT_007E5360;
    TheResourceRegistry.Release(Resource);
    Resource = 0;
    Vptr = &VT_007E5BA0;
    if (flags & 1) {
        gg_free(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x49AE80
// VectorClass<ConvertClass*>::operator==

// FUNCTION: GAMEMD 0x49AEC0
// VectorClass<ConvertClass*>::SetCapacity

// FUNCTION: GAMEMD 0x49AF70
// VectorClass<ConvertClass*>::Clear

// FUNCTION: GAMEMD 0x49AFA0
// VectorClass<ConvertClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x49AFE0
// VectorClass<ConvertClass*>::Slot5

// FUNCTION: GAMEMD 0x49B000
// DynamicVectorClass<ConvertClass*>::SetCapacity

// FUNCTION: GAMEMD 0x49B0B0
// DynamicVectorClass<ConvertClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x49B0E0
// VectorClass<ConvertClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x49B130
// DynamicVectorClass<ConvertClass*>::scalar deleting destructor


// SYNTHETIC: GAMEMD 0x48E660 -- ControlClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E8A8
ResourceRegistry TheResourceRegistry;
// END defined globals
