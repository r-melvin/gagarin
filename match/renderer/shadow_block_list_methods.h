// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Every offset, global, vtable slot and convention below was read numerically
//   off the user's retail gamemd.exe v1.001 through the local Ghidra CLI at
//   0x5FF250 / 0x5FF2D0 / 0x5FF390 / 0x5FF420 / 0x5FF800.
//
//   Class identity of the surface array came from RTTI, not from a guess: the
//   three vtables the builder at 0x5FF420 seats (0x7E2070, 0x7E2104,
//   0x7E2198) each carry a complete-object-locator dword four bytes below
//   them, and the locator's +0xC type descriptor's name string (eight bytes
//   into the descriptor) reads ".?AVBSurface@@", ".?AVXSurface@@" and
//   ".?AVSurface@@". So the 74 pointers torn down at 0x5FF800 are BSurface
//   objects and the `(**(void**)p)(1)` call is an ordinary polymorphic
//   `delete`, not a hand-rolled free.
//
//   NAMING RECONCILED: this file and match/renderer/effect_array_update_
//   methods.h were independently modelling the SAME retail class. The
//   registry this file called `DAT_00AC1678 : BlockList_005FF250` is
//   effect_array_update_methods.h's `SpotlightArray : DynamicVectorClass`
//   (both read Items @0xAC167C, Count @0xAC1688 off the SAME address), and
//   the element this file called `Entry_005FF250` is that file's forward-
//   declared `SpotlightClass` (both own the 0x5FF850 `Draw()` / 0x5FFFA0
//   `DrawAll()` pair). `SpotlightClass` is the YRpp-cross-checked name, so it
//   wins here; this header is now the one canonical definition and
//   effect_array_update_methods.h includes it instead of re-declaring either
//   type.
//
//   Disasm-derived facts:
//     * The registry at 0xAC1678 is one DynamicVectorClass: Items +0x04
//       (0xAC167C), Capacity +0x08 (0xAC1680), IsInitialized +0x0C (0xAC1684),
//       IsAllocated +0x0D (0xAC1685), Count +0x10 (0xAC1688) and
//       CapacityIncrement +0x14 (0xAC168C) all appear as absolute operands.
//       Its virtuals are reached as `CALL [vptr+0x08]` (SetCapacity, slot 2)
//       and `CALL [vptr+0x10]` (FindItemIndex, slot 4).
//     * 0x5FF250 is `RET 0x10` with `MOV ESI,ECX`: __thiscall taking a 12-byte
//       by-value struct plus one int. It writes +0x00/+0x04/+0x08 from the
//       struct, +0x10 from the int, and zeroes +0x0C and +0x14, then appends
//       `this` to the registry. sizeof is 0x18 — the `PUSH 0x18` ahead of
//       operator new at the call site 0x48A6BD.
//     * 0x5FF390 reads the age at +0x0C, adds 8, stores it back, and retires
//       the entry once it reaches 0x50. The null test lands *after* the age
//       test, which is `delete`'s own guard, so the unregister-and-free pair is
//       a destructor cl flattened into the sweep.
//     * The BSurface table runs from 0xAC1698 to 0xAC17C0 exclusive — 0x128
//       bytes, 74 pointers (the loop bound is an absolute `CMP ...,0xAC17C0`).
//       0xAC1798 (index 64) is the same table, not a second global: the raw
//       byte sweep (4096-byte chunks, objdump -D -b binary) that located
//       0x5FF420's real 0x3D7-byte body (its own `RET`, not the listed ~0x3E0
//       upper bound) also confirmed the builder's two loops both walk this one
//       array, the second starting at &DAT_00AC1698[64].
//     * 0x5FF420 (0x3D7 bytes) is the table's one-shot lazy builder: for each
//       of the 74 slots it (a) ensures a cached low-res BSurface exists, (b)
//       builds a throwaway high-res BSurface on the stack via the textbook
//       MSVC /GX three-phase constructor (vtable seated to Surface, then to
//       XSurface before the Buffer sub-object's own constructor can throw,
//       then finally to BSurface once construction can no longer fail — the
//       exact three pokes RTTI already dated to this address), rasterises a
//       gradient into it, downsamples it row-by-row into the cached entry via
//       Surface::CopyFromPart (slot 2), and destroys the throwaway. It then
//       one-shot-latches DAT_00AC1834 and, gated by the separate per-call
//       config probe at 0x4E6150, builds the 65536-entry packed-pixel fade
//       table at DAT_00AC1838 from the live pixel-format shift/mask globals.
#ifndef GG_MATCH_RENDERER_SHADOW_BLOCK_LIST_METHODS_H
#define GG_MATCH_RENDERER_SHADOW_BLOCK_LIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// CRT/game-heap (de)allocators. Declared, never reimplemented in this TU.
void* __cdecl operator new(unsigned int size);      // GAMEMD 0x7C8E17 (LIBRARY)
void  __cdecl operator delete(void* p);             // GAMEMD 0x7C8B3D (LIBRARY)

class SpotlightClass;

// GLOBAL: GAMEMD 0xAC1678 — SpotlightClass::Array, one
// DynamicVectorClass<SpotlightClass*>. Reused verbatim from
// match/_layout/vector_class.h so this and effect_array_update_methods.h
// agree on one name and one type for the same retail global.
extern DynamicVectorClass SpotlightArray;

// SpotlightArray's two called virtuals (SetCapacity slot 2, FindItemIndex
// slot 4) are reached through DynamicVectorClass's own `_vtable` field via the
// project's member-function-pointer vtable-slot idiom (match/_rt/gg_vslot.h):
// DynamicVectorClass is a complete type above, so VC6 uses the compact 4-byte
// member-pointer form and the calls come out byte-identical to retail's
// `CALL [ECX+8]` / `CALL [ECX+0x10]`.
struct Vtbl_SpotlightArray;
typedef bool (DynamicVectorClass::*FnSetCapacity_SpotlightArray)(int capacity, void* pMem);
typedef int  (DynamicVectorClass::*FnFindItemIndex_SpotlightArray)(SpotlightClass* const& item) const;
struct Vtbl_SpotlightArray
{
    char                            _pad00[0x08];     // slots 0..1
    FnSetCapacity_SpotlightArray    SetCapacity;       // slot 2 [+0x08]
    char                            _pad0C[0x04];      // slot 3
    FnFindItemIndex_SpotlightArray  FindItemIndex;     // slot 4 [+0x10]
};
GG_STATIC_ASSERT(offsetof(Vtbl_SpotlightArray, SetCapacity)   == 0x08);
GG_STATIC_ASSERT(offsetof(Vtbl_SpotlightArray, FindItemIndex) == 0x10);

// DynamicVectorClass::AddItem, expanded inline at 0x5FF278.
inline bool SpotlightArray_AddItem(SpotlightClass* item)
{
    int cap = SpotlightArray.Capacity;
    if (SpotlightArray.Count < cap
        // Retail reads this as the single IsAllocated byte at +0xD, not the
        // full 4-byte cell DynamicVectorClass's shared layout names
        // IsAllocated as (that cell also holds IsInitialized at +0xC) --
        // reading the whole int here regresses to a DWORD compare (97.6%).
        || ((*((unsigned char*)&SpotlightArray.IsAllocated + 1) || cap == 0)
            && SpotlightArray.CapacityIncrement > 0
            && (SpotlightArray.*((Vtbl_SpotlightArray*)SpotlightArray._vtable)->SetCapacity)
                   (SpotlightArray.CapacityIncrement + cap, 0))) {
        // `++Count` on its own line, not `Count = index + 1`: retail
        // increments the loaded register and stores it back, where the
        // computed form emits a `LEA` and hoists the Items load above the
        // Count store (73.2% versus 100%).
        int index = SpotlightArray.Count;
        ++SpotlightArray.Count;
        ((SpotlightClass**)SpotlightArray.Items)[index] = item;
        return true;
    }
    return false;
}

// DynamicVectorClass::RemoveItem, expanded inline at 0x5FF2D1 and again
// inside the sweep at 0x5FF3BC.
inline bool SpotlightArray_RemoveItem(SpotlightClass* const& item)
{
    int index = (SpotlightArray.*((Vtbl_SpotlightArray*)SpotlightArray._vtable)->FindItemIndex)(item);
    if (index != -1 && index < SpotlightArray.Count) {
        SpotlightArray.Count = SpotlightArray.Count - 1;
        for (; index < SpotlightArray.Count; ++index)
            ((SpotlightClass**)SpotlightArray.Items)[index] = ((SpotlightClass**)SpotlightArray.Items)[index + 1];
        return true;
    }
    return false;
}

// The 12-byte by-value payload the constructor copies into +0x00..+0x0B.
struct Payload_005FF250
{
    int Field0;   // +0x00
    int Field4;   // +0x04
    int Field8;   // +0x08
};
GG_STATIC_ASSERT(sizeof(Payload_005FF250) == 0x0C);

// The registered 0x18-byte entry. YRpp-cross-checked name (Surface.h /
// SpotlightClass.h, consult-only): SpotlightClass. See the reconciliation
// note above the file header for why this superseded the guessed
// `Entry_005FF250`.
class SpotlightClass
{
public:
    // FUNCTION: GAMEMD 0x5FF250 (__thiscall)
    SpotlightClass(Payload_005FF250 payload, int nFlags) throw();

    // FUNCTION: GAMEMD 0x5FF2D0 (__thiscall) — the unregistering destructor.
    ~SpotlightClass() throw();

    // FUNCTION: GAMEMD 0x5FF850 __thiscall (declared; matched separately)
    void Draw();
    // FUNCTION: GAMEMD 0x5FFFA0 (declared; matched separately)
    static void __fastcall DrawAll();

    Payload_005FF250 Payload;      // +0x00
    int              Age;          // +0x0C  zeroed by the ctor, +8 per sweep
    int              Flags;        // +0x10
    int              unknown_14;   // +0x14  zeroed by the ctor; blend-mode bits read by Draw()
};
GG_STATIC_ASSERT(offsetof(SpotlightClass, Age)        == 0x0C);
GG_STATIC_ASSERT(offsetof(SpotlightClass, Flags)      == 0x10);
GG_STATIC_ASSERT(offsetof(SpotlightClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(SpotlightClass)               == 0x18);

// A BSurface, torn down through slot 0 (the scalar-deleting destructor).
// VTABLE: GAMEMD 0x7E2070 — BSurface.
struct BSurface_005FF800
{
    virtual ~BSurface_005FF800();
};

// GLOBAL: GAMEMD 0xAC1698 — the 74-entry BSurface table (ends at 0xAC17C0).
// Index 64 (address 0xAC1798) begins the "near" half the 0x5FF420 builder
// fills second; it is the same array, not a separate global (see above).
extern BSurface_005FF800* DAT_00AC1698[74];
// GLOBAL: GAMEMD 0xAC1838 — a single heap block released alongside it.
extern void* DAT_00AC1838;

// ---------------------------------------------------------------------------
// 0x5FF420's raw building blocks. The cached table entries and the builder's
// own stack temporary are the *same* 0x20-byte BSurface layout; modelled as a
// plain POD rather than a polymorphic class because nothing here ever
// dispatches on it dynamically -- the four slots retail calls through it
// (Fill +0x18, CopyFromPart +0x08, Unlock +0x60, GetPitch +0x74) are reached
// with the project's explicit vtable-slot member-pointer idiom below, exactly
// like the already-matched match/combat/ion_blast_draw_methods.h.
struct RawSurface_005FF420
{
    void* VTable;         // +0x00
    int   Width;          // +0x04
    int   Height;         // +0x08
    int   LockLevel;      // +0x0C
    int   BytesPerPixel;  // +0x10
    int   Buffer[3];       // +0x14  MemoryBuffer sub-object (opaque; ctor 0x43AD00, dtor 0x43AE50)
};
GG_STATIC_ASSERT(offsetof(RawSurface_005FF420, Width)         == 0x04);
GG_STATIC_ASSERT(offsetof(RawSurface_005FF420, Height)        == 0x08);
GG_STATIC_ASSERT(offsetof(RawSurface_005FF420, LockLevel)     == 0x0C);
GG_STATIC_ASSERT(offsetof(RawSurface_005FF420, BytesPerPixel) == 0x10);
GG_STATIC_ASSERT(offsetof(RawSurface_005FF420, Buffer)        == 0x14);
GG_STATIC_ASSERT(sizeof(RawSurface_005FF420)                  == 0x20);

// A generic 4-int band descriptor: the builder repurposes Surface's
// RectangleStruct-shaped CopyFromPart arguments as {X, Y, Width, Height}
// intensity-ramp bands rather than screen rectangles.
struct Quad_005FF420 { int A, B, C, D; };

// Vtbl_Surface: only the four slots 0x5FF420/0x5FF850 reach. Fn08/Fn18 are
// called through a cached table entry's own vtable (Surface's, seated by the
// builder itself); Fn60/Fn74 are called on externally-owned Surface objects
// (the temp ramp, DSurface::Temp) that this TU never constructs.
struct Vtbl_Surface;
typedef bool (RawSurface_005FF420::*FnCopyFromPart_005FF420)(Quad_005FF420*, RawSurface_005FF420*, Quad_005FF420*, int, int);
typedef bool (RawSurface_005FF420::*FnFill_005FF420)(unsigned);
typedef bool (RawSurface_005FF420::*FnUnlock_005FF420)();
typedef int  (RawSurface_005FF420::*FnGetPitch_005FF420)();
struct Vtbl_Surface
{
    char                     _pad00[0x08];   // slots 0..1
    FnCopyFromPart_005FF420  CopyFromPart;    // slot 2  [+0x08]
    char                     _pad0C[0x0C];    // slots 3..5
    FnFill_005FF420          Fill;            // slot 6  [+0x18]
    char                     _pad1C[0x44];    // slots 7..23
    FnUnlock_005FF420        Unlock;          // slot 24 [+0x60]
    char                     _pad64[0x10];    // slots 25..28
    FnGetPitch_005FF420      GetPitch;        // slot 29 [+0x74]
};
GG_STATIC_ASSERT(offsetof(Vtbl_Surface, CopyFromPart) == 0x08);
GG_STATIC_ASSERT(offsetof(Vtbl_Surface, Fill)         == 0x18);
GG_STATIC_ASSERT(offsetof(Vtbl_Surface, Unlock)       == 0x60);
GG_STATIC_ASSERT(offsetof(Vtbl_Surface, GetPitch)     == 0x74);

// Stand-in for the shared field/vtable initialiser at 0x4AEC60: sets
// Width/Height and re-seats the vtable to plain Surface's own (0x7E2198).
// Declared only -- matched separately, not reimplemented in this TU.
struct SurfaceFieldInit_004AEC60
{
    void Init(int width, int height);   // GAMEMD 0x4AEC60 __thiscall (declared; reloc)
};

// Stand-in for the embedded MemoryBuffer sub-object's constructor/destructor.
// Declared only -- matched separately, not reimplemented in this TU.
struct MemoryBufferRaw_0043AD00
{
    void Construct(int initial, unsigned size);   // GAMEMD 0x43AD00 __thiscall (declared; reloc)
    void Destruct();                              // GAMEMD 0x43AE50 __fastcall (declared; reloc)
};

// Stand-in for the finalizer 0x5FF420 calls once its stack-temporary surface
// finishes construction. Declared only -- matched separately.
struct SurfaceFinalize_007BBAB0
{
    void Finalize(int flag);   // GAMEMD 0x7BBAB0 __thiscall (declared; reloc)
};

// Stand-in for the gradient rasteriser at 0x7BB920 -- __thiscall is only
// legal on VC6 as a member function, so the receiver becomes a stand-in
// method (see match/_rt/gg_vslot.h's note on this). Declared only, not
// reimplemented in this TU.
struct SurfaceSpread_007BB920
{
    void Spread(int width, int height, int band, int flag);   // GAMEMD 0x7BB920 (decl; reloc)
};

// FUNCTION: GAMEMD 0x4BBC90 (decl; reloc). GAMEMD 0x4E6150 (decl; reloc) --
// the config probe gating the fade-table (re)build. Neither is reimplemented
// in this TU.
extern "C" int  __stdcall FUN_004BBC90();
extern "C" void __fastcall FUN_004E6150(int* param1, char* outFlag, char* param3, unsigned param4);

// GLOBAL: GAMEMD 0xAC1834 -- one-shot "gradient cache built" latch.
extern unsigned char DAT_00AC1834;
// GLOBAL: GAMEMD 0x833588 -- the config probe's own cached result.
extern int DAT_00833588;
// GLOBAL: GAMEMD 0x8871E0 -- a scenario-ish singleton read for the "near"
// band's radius bias (offset +0x7A8 off it).
extern char* DAT_008871E0;
// GLOBAL: GAMEMD 0x7EF6F8 -- the fixed-point-to-float scale the near band's
// radius bias is multiplied by before truncation.
extern float DAT_007EF6F8;

// GLOBAL: GAMEMD 0x8A0DD0/D4/D8/DC/E0/E4 -- the live pixel-format shift/mask
// sextet the fade table is built from. Reused verbatim from
// match/renderer/drawing.cpp (RedShiftLeft/Right, BlueShiftLeft/Right) plus
// the two green-channel globals this file adds.
extern int RedShiftLeft;     // GAMEMD 0x8A0DD0
extern int RedShiftRight;    // GAMEMD 0x8A0DD4
extern int BlueShiftLeft;    // GAMEMD 0x8A0DD8
extern int BlueShiftRight;   // GAMEMD 0x8A0DDC
extern int GreenShiftLeft;   // GAMEMD 0x8A0DE0
extern int GreenShiftRight;  // GAMEMD 0x8A0DE4

// FUNCTION: GAMEMD 0x5FF390
void FUN_005FF390();
// FUNCTION: GAMEMD 0x5FF420
void FUN_005FF420();
// FUNCTION: GAMEMD 0x5FF800
void FUN_005FF800();

#endif  // GG_MATCH_RENDERER_SHADOW_BLOCK_LIST_METHODS_H
