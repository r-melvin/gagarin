// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU196 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x65f7a0-0x661caf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI TypeDescriptors 0x00839920 and 0x00839958 identify
// VectorClass<RadarEventClass*> and DynamicVectorClass<RadarEventClass*>;
// the dynamic hierarchy records the former as its zero-offset base.
// Complete function spans and the two slot arrays were checked against the
// pinned retail PE. This TU recovers the vector specialization only; it makes
// no constructor, original-TU, or complete RadarEventClass layout claim.
// The derived deleting-dtor full span requires /GX off; the base dtor also
// matches with /GX. Both table checks rely on VC6 weak defaults, so final-link
// resolution is not established here.
//
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI.
//
// RandomStraw - the retail address run 0x6616B0-0x661CA9, bodies ascending by address.
//
// Leaf bodies that repeat byte for byte at several addresses and touch only
// globals: store of the ECX argument, indexed table reads, constant stores,
// and a two-value test. Each address binds to its own global (named by
// retail address, typed only as far as the instructions show) and was
// verified separately. Record structs name only the fields the bodies read.
//
// Two translation units each carry an identical "delete everything" sweep over
// one global registry of objects: walk the registry from the back, and for
// each live entry delete it. The object's own destructor (inlined) takes the
// entry out of the registry through the virtual find slot and the by-index
// removal, so the live count shrinks as the sweep goes.
//
// 256-entry three-byte color table and its color element. Layout read off the
// bodies at 0x626070 (0x100 three-byte zeroing loop, then a 0xC0-dword copy)
// and 0x661350 (byte reads at +0/+1/+2). Names are descriptive placeholders.
//
// RGB -> HSV conversion, a __thiscall member on a 3-byte colour triple
// returning a 3-byte triple through the hidden return pointer (`ret 4`).
// Byte reads at [ECX+0..2] fix the field order; the result stores
// [ret+0..1] as a word (H, S) and [ret+2] as the maximum channel (V).
//
// Static data members of vector type: each retail definition is guarded by a
// bit in a shared byte, so the exit-time destructor stub tests that bit before
// restoring the VectorClass<T> vtable and releasing the array. Every member here
// is the lowest bit of its guard byte (a single-member group), so each is given
// its own placeholder holder; the owning classes are not recoverable. T is the
// element type of the vector's RTTI TypeDescriptor, read through the vptr stored
// by the matching initialiser. The initialisers (__xc table entries) are left to
// the translation-unit migration and compile here as a by-product, unclaimed.

#include "../core/vector_class_operations.h"

class RadarEventClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<RadarEventClass*>;

// VTABLE: GAMEMD 0x007F0ACC -- VectorClass<RadarEventClass*>.
// VTABLE: GAMEMD 0x007F0AAC -- DynamicVectorClass<RadarEventClass*>.

typedef VectorClass<RadarEventClass*> GgRadarEventVector;
typedef DynamicVectorClass<RadarEventClass*> GgRadarEventDynamicVector;
GG_STATIC_ASSERT(sizeof(RadarEventClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgRadarEventVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgRadarEventDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, CapacityIncrement) == 0x14);

#include "../combat/random_straw.h"

// ---------------------------------------------------------------------------
// The shapes retail expands at every use site.
// ---------------------------------------------------------------------------

// The SHA-1 engine's constructor. Retail's store order - the unknown_00 byte,
// then Length, then PendingCount, then the five chaining seeds - is the
// initialiser list followed by the body, so it is written that way.
__forceinline Sha1State::Sha1State() : unknown_00(false), Length(0), PendingCount(0)
{
    Chain[0] = GG_SHA_SA;
    Chain[1] = GG_SHA_SB;
    Chain[2] = GG_SHA_SC;
    Chain[3] = GG_SHA_SD;
    Chain[4] = GG_SHA_SE;
}

// Clear the object back to its post-construction state, so no seed material is
// left behind. The pool clear is a constant-sized dword-aligned memset, which
// is where retail's `REP STOSD` of 0x40 dwords comes from.
__forceinline void RandomStraw::ResetInline()
{
    BitsSeeded = 0;
    Current = 0;
    memset(Random, '\0', sizeof(Random));
}

// Hash the seed pool over itself twenty bytes at a time, so every seed bit ends
// up influencing every other one. `count` is an unsigned comparison because
// both arms are sizeof expressions, which is what makes 0x661BDD a `JBE`.
__forceinline void RandomStraw::ScrambleInline()
{
    Sha1State sha;

    for (int index = 0; index < sizeof(Random); index++) {
        char digest[20];

        sha.Hash(&Random[0], sizeof(Random));
        sha.Result(digest);

        int count = sizeof(digest) < (sizeof(Random) - index) ? sizeof(digest) : (sizeof(Random) - index);
        FUN_007CA090(((char*)&Random[0]) + index, digest, count);
    }
}

// Fold one bit of entropy into the pool. The byte index is a signed divide by
// eight wrapped into the pool's length, which is the `CDQ; AND EDX,7; SAR 3;
// AND EAX,0xFF` run at 0x66177C. The bit is only formed inside the guarded arm,
// which is where retail sinks it too.
__forceinline void RandomStraw::AddBitInline(int seed)
{
    char* ptr = ((char*)&Random[0]) + ((BitsSeeded / 8) % sizeof(Random));

    if (seed & 0x01) {
        char bit = (char)(1 << (BitsSeeded & (8 - 1)));
        *ptr ^= bit;
    }
    BitsSeeded++;

    if (BitsSeeded == (sizeof(Random) * 8)) {
        ScrambleInline();
    }
}

// ---------------------------------------------------------------------------
// The retail bodies, ascending by address.
// ---------------------------------------------------------------------------

extern int DAT_00816108;
struct Rec12_008B4040 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B4040 DAT_008B4040[];
struct Rec12_008B3F38 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B3F38 DAT_008B3F38[];
struct Rec12_008B3FC8 { int key; int unknown_04; int unknown_08; };
extern Rec12_008B3FC8 DAT_008B3FC8[];
extern unsigned char DAT_00A9FAB4;
extern unsigned char DAT_00ABCD58;
extern int DAT_00ABED0C;
extern int DAT_00ABF168[];
struct Rec28_0082D028 { int f00; int f04; int unknown_08[5]; };
extern Rec28_0082D028 DAT_0082D028[];
extern int DAT_00AC4B80;
extern int DAT_00AC4C90;
extern int DAT_00AC4C38;
extern int DAT_00AC4BF0;
extern int DAT_007F0248[];
struct Rec16_007F0998 { int f00; int f04; int f08; int f0C; };
extern Rec16_007F0998 DAT_007F0998[];
extern int DAT_00B0CB78[];
extern int DAT_008449F8[];
extern unsigned char DAT_00B0FE58;
extern unsigned char DAT_008464AC;
extern int DAT_00B780A0;

#include <string.h>
// Zero-run byte codec. The caller at 0x6C8BB7 passes ECX = a stack local and
// three stack arguments (source, destination, length); none of the three
// bodies reads ECX, so the owning object carries no state touched here.
// A zero byte is emitted as {0, run} with run capped at 0xFF (0x66155A);
// other bytes are copied through. Names are descriptive placeholders.

struct ZeroRunCodec_00661530
{
    int FUN_00661530(const unsigned char* source, unsigned char* dest, int length);
    int Encode(const unsigned char* source, unsigned char* dest, int length);
    int Decode(const unsigned char* source, unsigned char* dest, int length);
};

#include "../core/vector_class_operations.h"

struct Item_0065FD50;
// GLOBAL: GAMEMD 0xB04DA8 -- the registry.
extern DynamicVectorClass<Item_0065FD50*> DAT_00B04DA8;
struct Item_0065FD50 {
    ~Item_0065FD50() { Item_0065FD50* self = this; DAT_00B04DA8.RemoveItem(self); }
};

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0065FB60;

// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];

// FUNCTION: GAMEMD 0x6562D0 (decl; reloc)
void FUN_006562D0(void*, int, Obj_0065FB60*);

struct Obj_0065FB60
{
};


void __cdecl FUN_0065FA60();
void FUN_0065FB60(Obj_0065FB60* a1, int a2);


#include "../_rt/gg_static_assert.h"
#include <stddef.h>

struct ColorRGB_00661350
{
    unsigned char unknown_00;   // +0x00
    unsigned char unknown_01;   // +0x01
    unsigned char unknown_02;   // +0x02

    ColorRGB_00661350() : unknown_00(0), unknown_01(0), unknown_02(0) {}

    // retail thiscall helper, matched elsewhere in main as a separate view.
    void Blend(int ratio, const ColorRGB_00661350& target);
    int Difference(const ColorRGB_00661350& other) const;
};

GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_01) == 0x01);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_02) == 0x02);
// 0x626070 steps the element loop by 3.
GG_STATIC_ASSERT(sizeof(ColorRGB_00661350) == 0x03);

// GLOBAL: GAMEMD 0x00A83CD9 -- fixed target color pushed by 0x626170.
extern ColorRGB_00661350 DAT_00A83CD9;

struct ColorTable_00626070
{
    ColorRGB_00661350 Colors[256];   // +0x000

    ColorTable_00626070(const ColorTable_00626070& other);

    const ColorRGB_00661350& operator[](int index) const { return Colors[index % 256]; }

    void FUN_00626120(int ratio, const ColorTable_00626070& target);
    void FUN_00626170(int ratio, const char* marks);
    void FUN_006261B0(int ratio, const ColorTable_00626070& target, const char* marks);
    int Nearest(const ColorRGB_00661350& color) const;
};

GG_STATIC_ASSERT(offsetof(ColorTable_00626070, Colors) == 0x000);

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HSVClass
{
    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02
};
GG_STATIC_ASSERT(offsetof(HSVClass, Hue) == 0);
GG_STATIC_ASSERT(offsetof(HSVClass, Saturation) == 1);
GG_STATIC_ASSERT(offsetof(HSVClass, Value) == 2);

#include "../_layout/rgb_class.h"

#include "../core/vector_class_operations.h"

class AnimClass;
class IonBlastClass;
class RadarEventClass;
class ShadowControlClass;
class VeinholeMonsterClass;

struct StaticVectorHolder_00A9F9D0 {
    // GLOBAL: GAMEMD 0x00A9F9D0
    static DynamicVectorClass<const AnimClass*> DAT_00A9F9D0;
};

struct StaticVectorHolder_00AA0118 {
    // GLOBAL: GAMEMD 0x00AA0118
    static DynamicVectorClass<IonBlastClass*> DAT_00AA0118;
};

struct StaticVectorHolder_00B04DA8 {
    // GLOBAL: GAMEMD 0x00B04DA8
    static DynamicVectorClass<RadarEventClass*> DAT_00B04DA8;
};

struct StaticVectorHolder_00B0CDE8 {
    // GLOBAL: GAMEMD 0x00B0CDE8
    static DynamicVectorClass<ShadowControlClass*> DAT_00B0CDE8;
};

struct StaticVectorHolder_00B1D290 {
    // GLOBAL: GAMEMD 0x00B1D290
    static DynamicVectorClass<VeinholeMonsterClass*> DAT_00B1D290;
};

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F0980
extern const double DAT_007F0980;
// GLOBAL: GAMEMD 0xB04D70
extern double DAT_00B04D70;

// SYNTHETIC: GAMEMD 0x65F7D0
// GLOBAL: GAMEMD 0xB04DF0
double DAT_00B04DF0 = DAT_00B04D70 / DAT_007F0980;

// SYNTHETIC: GAMEMD 0x65F7F0
// GLOBAL: GAMEMD 0xB04DD0
double DAT_00B04DD0 = DAT_007E1718 / DAT_00B04DF0;

// SYNTHETIC: GAMEMD 0x0065F9F0 -- exit-time destructor stub of DAT_00B04DA8, guard byte 0x00B04D28 bit 0
DynamicVectorClass<RadarEventClass*> StaticVectorHolder_00B04DA8::DAT_00B04DA8;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x65FA60
// Empty function.
void __cdecl FUN_0065FA60()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x65FB60
// Calls other functions.
void FUN_0065FB60(Obj_0065FB60* a1, int a2)
{
    FUN_006562D0(DAT_0087F7E8, a2, a1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0065FD50
void FUN_0065FD50()
{
    for (int i = DAT_00B04DA8.Count - 1; i >= 0; --i) {
        Item_0065FD50* item = DAT_00B04DA8.Items[i];
        if (item != 0) {
            delete item;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00660AD0
int FUN_00660AD0(const int* index)
{
    return DAT_007F0998[*index].f04;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00660AE0
int FUN_00660AE0(const int* index)
{
    return DAT_007F0998[*index].f08;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00660AF0
int FUN_00660AF0(const int* index)
{
    return DAT_007F0998[*index].f00;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00660B00
void FUN_00660B00()
{
    for (int i = DAT_00B04DA8.Count - 1; i >= 0; --i) {
        Item_0065FD50* item = DAT_00B04DA8.Items[i];
        if (item != 0) {
            delete item;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00660C80
// FUNCTION: GAMEMD 0x00660CB0
// FUNCTION: GAMEMD 0x00660CD0
// FUNCTION: GAMEMD 0x00660CE0
// FUNCTION: GAMEMD 0x00660D20
// FUNCTION: GAMEMD 0x00660DD0
// FUNCTION: GAMEMD 0x00660E00
// FUNCTION: GAMEMD 0x00660E40
// FUNCTION: GAMEMD 0x00660E60
// FUNCTION: GAMEMD 0x00660F50
// FUNCTION: GAMEMD 0x00660F80
// FUNCTION: GAMEMD 0x00660FD0
template class VectorClass<RadarEventClass*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x661350
int ColorRGB_00661350::Difference(const ColorRGB_00661350& other) const
{
    int r = unknown_00 - other.unknown_00;
    if (r < 0) r = -r;
    int g = unknown_01 - other.unknown_01;
    if (g < 0) g = -g;
    int b = unknown_02 - other.unknown_02;
    if (b < 0) b = -b;
    return r * 2 + g * 4 + b * 3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6613A0
// PARTIAL (97.5%). Saturation is cleared after the channel minimum is found,
// not at its declaration; that order gives retail's register assignment. The
// remaining delta is the stack slot of the result temporary (retail [ESP+0x1C],
// ours [ESP+0x10]).
HSVClass RGBClass::FUN_006613A0() const
{
    HSVClass hsv;
    int red = Red;
    int green = Green;
    int blue = Blue;
    unsigned int hue = 0;
    int saturation;
    unsigned int rc, gc, bc;

    int value = (red > green) ? red : green;
    if (blue > value) value = blue;
    int low = (red < green) ? red : green;
    if (blue < low) low = blue;

    saturation = 0;

    if (value != 0) {
        saturation = ((value - low) * 255) / value;
        if (saturation != 0) {
            unsigned int delta = value - low;
            rc = (unsigned int)(value * 255 - red * 255) / delta;
            gc = (unsigned int)(value * 255 - green * 255) / delta;
            bc = (unsigned int)(value * 255 - blue * 255) / delta;
            if (value == red) {
                hue = (low == green) ? 0x500 + bc : 0x100 - gc;
            } else if (value == green) {
                hue = (low == blue) ? 0x100 + rc : 0x300 - bc;
            } else {
                hue = (low == red) ? 0x300 + gc : 0x500 - rc;
            }
            hue /= 6;
        }
    }

    hsv.Hue = (unsigned char)hue;
    hsv.Saturation = (unsigned char)saturation;
    hsv.Value = (unsigned char)value;
    return hsv;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x661530
int ZeroRunCodec_00661530::FUN_00661530(const unsigned char* source, unsigned char* dest, int length)
{
    int written = 0;
    while (length > 0) {
        unsigned char value = *source;
        if (value == 0) {
            int run = 0;
            while (run <= length) {
                if (source[++run] != 0) break;
            }
            if (run >= 255) {
                run = 255;
            }
            if (dest != 0) {
                *dest++ = 0;
                *dest++ = (unsigned char)run;
            }
            written += 2;
            source += run;
            length -= run;
        } else {
            if (dest != 0) {
                *dest++ = value;
            }
            source++;
            written++;
            length--;
        }
    }
    return written;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x661590
int ZeroRunCodec_00661530::Encode(const unsigned char* source, unsigned char* dest, int length)
{
    if (dest != 0) {
        int size = FUN_00661530(source, dest + 2, length) + 2;
        *(unsigned short*)dest = (unsigned short)size;
        return size;
    }
    return FUN_00661530(source, 0, length) + 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6615D0
int ZeroRunCodec_00661530::Decode(const unsigned char* source, unsigned char* dest, int length)
{
    unsigned char* out = dest;
    while (length > 0) {
        unsigned char value = *source++;
        length--;
        if (value == 0) {
            unsigned char count = *source++;
            length--;
            int run = count;
            if (run > 0) {
                memset(out, 0, run);
                out += run;
            }
        } else {
            *out++ = value;
        }
    }
    return out - dest;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Build a RandomStraw in a known - and cryptographically useless - state. The
// Straw base's two chain links are zeroed and its vtable seated first, then the
// two counters are initialised, then the 32 generators are default-constructed
// in a loop, then the derived vtable is seated and the pool cleared.
// FUNCTION: GAMEMD 0x6616B0
RandomStraw* RandomStraw::Construct()
{
    ChainTo = 0;
    ChainFrom = 0;
    Vtable = &GG_VTABLE_STRAW;

    BitsSeeded = 0;
    Current = 0;

    Generator_0065C890* gen = &Random[0];
    for (int index = 0; index < 32; index++) {
        gen->Construct(0, 0);
        gen++;
    }

    Vtable = &GG_VTABLE_RANDOMSTRAW;
    ResetInline();
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Tear a RandomStraw down. The pool is cleared before the base runs so that no
// sensitive seed material survives in the freed memory.
// FUNCTION: GAMEMD 0x661700
void RandomStraw::Destruct()
{
    Vtable = &GG_VTABLE_RANDOMSTRAW;
    ResetInline();
    ((Straw*)this)->Straw::~Straw();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The out-of-line copy of the pool clear.
// FUNCTION: GAMEMD 0x661730
void RandomStraw::Reset()
{
    ResetInline();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// How many more seed bits the pool still wants. `total` is bound to a const int
// rather than left as the unsigned sizeof product, which is what makes the
// compare at 0x661759 a signed `JGE`.
// FUNCTION: GAMEMD 0x661750
int RandomStraw::FUN_00661750() const
{
    const int total = sizeof(Random) * 8;
    if (BitsSeeded < total) {
        return total - BitsSeeded;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The out-of-line copy of the single-bit seed step.
// FUNCTION: GAMEMD 0x661770
void RandomStraw::FUN_00661770(int seed)
{
    AddBitInline(seed);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Feed eight bits, lowest first. The shift is an eight-bit `SAR` on the
// parameter's own stack home because the parameter really is a char.
// FUNCTION: GAMEMD 0x661850
void RandomStraw::FUN_00661850(char seed)
{
    for (int index = 0; index < 8; index++) {
        AddBitInline(seed);
        seed >>= 1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Feed sixteen bits, lowest first.
// FUNCTION: GAMEMD 0x661960
void RandomStraw::FUN_00661960(short seed)
{
    for (int index = 0; index < (sizeof(seed) * 8); index++) {
        AddBitInline(seed);
        seed >>= 1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Feed a full thirty-two bits, lowest first.
// FUNCTION: GAMEMD 0x661A60
void RandomStraw::FUN_00661A60(long seed)
{
    for (int index = 0; index < (sizeof(seed) * 8); index++) {
        AddBitInline(seed);
        seed >>= 1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The out-of-line copy of the SHA-1 pool scramble.
// FUNCTION: GAMEMD 0x661B70
void RandomStraw::FUN_00661B70()
{
    ScrambleInline();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Serve random bytes. A null buffer or a non-positive length is handed back to
// the base straw, which is what terminates the chain; otherwise the generators
// are walked round-robin, one byte per call, and the pool never runs dry.
// FUNCTION: GAMEMD 0x661C10
int RandomStraw::Get(void* source, int slen)
{
    if (source == 0 || slen < 1) {
        return ((Straw*)this)->Straw::FUN_006C98E0((int)source, slen);
    }

    int total = 0;
    while (slen > 0) {
        *(char*)source = (char)Random[Current++].Next();
        Current = Current % (sizeof(Random) / sizeof(Random[0]));
        source = (char*)source + sizeof(char);
        slen--;
        total++;
    }
    return total;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Vtable slot zero: the scalar deleting thunk, with the destructor expanded
// into it rather than called. Retail carries both this copy and the out-of-line
// one at 0x661700.
// FUNCTION: GAMEMD 0x661C70
void* RandomStraw::ScalarDeletingDestructor(unsigned char flags)
{
    Vtable = &GG_VTABLE_RANDOMSTRAW;
    ResetInline();
    ((Straw*)this)->Straw::~Straw();
    if (flags & 0x01) {
        FUN_007C8B3D(this);
    }
    return this;
}
