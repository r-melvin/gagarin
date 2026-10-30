// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5FF250, 0x5FF2D0,
//   0x5FF390 and 0x5FF800; 0x5FF420 added and iterated in this pass. See the
//   header for the RTTI derivation of BSurface, the SpotLightClass naming
//   reconciliation, and the numeric origin of every offset.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5FF250  SpotLightClass::SpotLightClass (__thiscall)
//   FUNCTION: GAMEMD 0x5FF2D0  SpotLightClass::~SpotLightClass (__thiscall)
//   FUNCTION: GAMEMD 0x5FF320  SpotLightClass::AgeStep (__thiscall)
//   FUNCTION: GAMEMD 0x5FF390  FUN_005FF390
//   FUNCTION: GAMEMD 0x5FF420  FUN_005FF420
//   FUNCTION: GAMEMD 0x5FF800  FUN_005FF800
//   FUNCTION: GAMEMD 0x5FFFA0  SpotLightClass::DrawAll (__fastcall, static)
//   VTABLE:   GAMEMD 0x7E2070  BSurface
//   VTABLE:   GAMEMD 0x7E2104  XSurface
//   VTABLE:   GAMEMD 0x7E2198  Surface
//   GLOBAL:   GAMEMD 0xAC1678  SpotLightClass::Array (DynamicVectorClassLayout)
//   GLOBAL:   GAMEMD 0xAC1698  the 74-entry BSurface gradient table
//   GLOBAL:   GAMEMD 0xAC1834  the gradient-cache one-shot latch
//   GLOBAL:   GAMEMD 0xAC1838  the companion heap block / fade table
//   LIBRARY:  GAMEMD 0x7C8B3D  operator delete (CRT; excluded from the match)
//   LIBRARY:  GAMEMD 0x7C8E17  operator new (CRT; excluded from the match)

#include "shadow_block_list_methods.h"

// FUNCTION: GAMEMD 0x5FF250  SpotLightClass::SpotLightClass (__thiscall)
// Build one entry from its 12-byte payload and its flag word, start it at age
// zero, and register it in the global list so the periodic sweep can retire it.
// Retail ignores the append's success, which is why no boolean survives.
SpotLightClass::SpotLightClass(Payload_005FF250 payload, int nFlags) throw()
{
    Payload = payload;
    Age = 0;
    unknown_14 = 0;
    Flags = nFlags;

    SpotlightArray_AddItem(this);
}

// FUNCTION: GAMEMD 0x5FF2D0  SpotLightClass::~SpotLightClass (__thiscall)
// Unregister the entry. The list slot is found through the vector's own
// FindItemIndex virtual and the tail is shifted down over it.
SpotLightClass::~SpotLightClass() throw()
{
    SpotlightArray_RemoveItem(this);
}

// FUNCTION: GAMEMD 0x5FF320
// Age this entry by one sweep step; once it has reached 0x50, unregister and free it.
void SpotLightClass::AgeStep()
{
    Age += 8;
    if (Age >= 0x50 && this != 0) {
        SpotlightArray_RemoveItem(this);
        operator delete(this);
    }
}


// DynamicVectorClass<T>::RemoveItem again, but reached as a free function over the
// container with the element taken *by value*. Both shapes are needed: the
// destructor above matches only as the member call with the element bound by
// reference, and this sweep matches only in this form. The difference is where
// the element lives — as a member call with a reference parameter cl homes the
// element in the virtual call's own argument slot from the top of the loop,
// where retail holds it in a callee-saved register and copies it into that slot
// only at the call. 18.8% versus 100% on one edit.
static inline bool RemoveFrom(DynamicVectorClassLayout& list,
                                     SpotLightClass* item)
{
    int index = (list.*((Vtbl_SpotlightArray*)list._vtable)->FindItemIndex)(item);
    if (index != -1 && index < list.Count) {
        list.Count = list.Count - 1;
        for (; index < list.Count; ++index)
            ((SpotLightClass**)list.Items)[index] = ((SpotLightClass**)list.Items)[index + 1];
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5FF390  FUN_005FF390
// Age every registered entry by one sweep step and destroy the ones that have
// run out. The walk is backwards because destroying an entry compacts the list
// underneath the cursor.
//
// The unregister-and-free pair is spelled out here rather than written as
// `delete entry`: retail has the destructor body expanded into this function,
// and with a real `delete` cl emits an out-of-line call to it instead (0%).
// Retail tests for null after the age comparison; this source preserves
// that observed order without inferring its original source expression.
void FUN_005FF390()
{
    for (int i = SpotlightArray.Count - 1; i >= 0; --i)
    {
        SpotLightClass* entry = ((SpotLightClass**)SpotlightArray.Items)[i];

        // The age must be incremented in place: bound to a named local it
        // loses the `MOV EAX,ECX` that feeds the comparison from the register.
        entry->Age += 8;

        if (entry->Age >= 0x50 && entry != 0)
        {
            RemoveFrom(SpotlightArray, entry);
            operator delete(entry);
        }
    }
}

// Shared by both of 0x5FF420's table-filling loops: build a cached low-res
// BSurface into `*slot` the first time it is needed. Left as a distinct
// inline helper (rather than folded into the caller) because the
// builder calls it twice, once per table half, on the same literal
// (0x100, 0x80) dimensions and 0x8000-byte buffer.
static inline void EnsureGradientSurface(BSurface_005FF800** slot)
{
    if (*slot == 0)
    {
        RawSurface_005FF420* entry = (RawSurface_005FF420*)operator new(0x20);
        RawSurface_005FF420* built;
        if (entry != 0)
        {
            ((SurfaceFieldInit_004AEC60*)entry)->Init(0x100, 0x80);
            entry->LockLevel = 0;
            entry->VTable = (void*)0x7E2104;
            entry->BytesPerPixel = 1;
            ((MemoryBufferRaw_0043AD00*)&entry->Buffer)->Construct(0, 0x8000);
            entry->VTable = (void*)0x7E2070;
            built = entry;
        }
        else
        {
            built = 0;
        }
        *slot = (BSurface_005FF800*)built;
    }
}

// Shared by both loops: seat a throwaway high-res BSurface on the stack via
// observed Surface/XSurface/BSurface vptr writes. Their sequence alone
// does not establish the original exception-safety rationale.
static inline void ConstructRamp(RawSurface_005FF420* ramp)
{
    ((SurfaceFieldInit_004AEC60*)ramp)->Init(0x100, 0x100);
    ramp->LockLevel = 0;
    ramp->VTable = (void*)0x7E2104;
    ramp->BytesPerPixel = 1;
    ((MemoryBufferRaw_0043AD00*)&ramp->Buffer)->Construct(0, 0x10000);
    ramp->VTable = (void*)0x7E2070;
    ((SurfaceFinalize_007BBAB0*)ramp)->Finalize(0);
}

// Downsample the 0x100-tall ramp into the cached 0x80-tall entry, one row at a
// time, via the cached BSurface table's slot 2: source row is always double the
// destination row.
static inline void DownsampleInto(BSurface_005FF800** slot, RawSurface_005FF420* ramp)
{
    for (int row = 0; row < 0x80; ++row)
    {
        Quad_005FF420 dst = { 0, row, 0xff, 1 };
        Quad_005FF420 src = { 0, row * 2, 0xff, 1 };
        RawSurface_005FF420* cached = (RawSurface_005FF420*)*slot;
        Vtbl_Surface* cachedVtbl = (Vtbl_Surface*)cached->VTable;
        (cached->*cachedVtbl->CopyFromPart)(&dst, ramp, &src, 0, 1);
    }
}

// FUNCTION: GAMEMD 0x5FF420  FUN_005FF420
// One-shot lazy builder for the spotlight gradient cache: see the header for
// the full derivation. `DAT_00AC1834` makes every table-build step run at
// most once; the trailing fade-table build is gated separately by the config
// probe at 0x4E6150, which retail (and this TU) still calls unconditionally
// every time.
//
// PARTIAL (second look: instruction multiset gap now 2 of 279 -- retail-only AND/OR, ours MOV/XOR --
// positional 6.5%; best positional variant 16.8% kept out of this file). Findings this pass, all read
// from the retail disassembly:
//   * 0x7BB920 takes (width, height, band, Quad area BY VALUE, limit): the second 16-byte
//     {0,0,0xFF,0xFF} block is that by-value area, and the fifth argument is min(0xC + 4k, 0xFF) in the
//     near loop and the running `farBand` (0x80, 0x7A, ...) in the far loop.
//   * the bias multiply reads a qword at 0x7EF6F8 (double), not a float.
//   * the downsample loop re-reads `*slot` every row (the cached pointer is not hoisted).
//   * the gradient entry is built in `if (entry) { ... built = entry } else built = 0` form.
//   * the table-pack tail combines red<<16 | green<<8 | blue (shift operands are the retail words at
//     0x8A0DD0/D4, DE0/E4, DD8/DC).
// Remaining delta: register assignment -- retail keeps `slot` in EBP and the constant 1 in EDI (reloaded
// after the band loop), ours spills `slot` and keeps the 1 in EBP; retail's 64K-entry pack loop counts in
// EBX (so the byte temporaries spill to [ESP+0x19/0x1A]) where ours counts in ESI.
void FUN_005FF420()
{
    if (DAT_00AC1834 == 0)
    {
        // Both loops below are `do`/`while`, not `for`: retail's back edge
        // jumps to the *body's* first statement (the slot-null test), with no
        // separate entry test ahead of it -- the loop-rotation shape a `for`
        // (which MSVC does not prove non-empty here) does not reproduce.
        int radius = 1;
        BSurface_005FF800** slot = &DAT_00AC1698[0];
        do
        {
            int limit = 12;
            EnsureGradientSurface(slot);
            (((RawSurface_005FF420*)*slot)->*((Vtbl_Surface*)((RawSurface_005FF420*)*slot)->VTable)->Fill)(0);

            RawSurface_005FF420 ramp;
            ConstructRamp(&ramp);
            for (int band = radius; band > 0; band -= 2)
            {
                Quad_005FF420 area = { 0, 0, 0xff, 0xff };
                int clamped = limit;
                if (clamped > 0xff)
                    clamped = 0xff;
                ((SurfaceSpread_007BB920*)&ramp)->Spread(0x80, 0x80, band, area, clamped);
                limit += 4;
            }
            DownsampleInto(slot, &ramp);
            ((MemoryBufferRaw_0043AD00*)&ramp.Buffer)->Destruct();

            ++slot;
            radius += 2;
        } while (radius < 0x81);

        slot = &DAT_00AC1698[64];
        int farBand = 0x80;
        int i = 0;
        do
        {
            EnsureGradientSurface(slot);
            (((RawSurface_005FF420*)*slot)->*((Vtbl_Surface*)((RawSurface_005FF420*)*slot)->VTable)->Fill)(0);

            RawSurface_005FF420 ramp;
            ConstructRamp(&ramp);
            int fieldScaled = *(int*)(DAT_008871E0 + 0x7A8) * 0x3C;
            int bias = (int)((double)fieldScaled * DAT_007EF6F8);
            Quad_005FF420 area = { 0, 0, 0xff, 0xff };
            ((SurfaceSpread_007BB920*)&ramp)->Spread(0x80, 0x80, i - bias, area, farBand);
            DownsampleInto(slot, &ramp);
            ((MemoryBufferRaw_0043AD00*)&ramp.Buffer)->Destruct();

            farBand -= 6;
            ++i;
            ++slot;
        } while (farBand > 0x44);

        DAT_00AC1834 = 1;
    }

    DAT_00833588 = FUN_004BBC90();
    int probeLen = 5;
    char probeFlag = 0;
    FUN_004E6150(&probeLen, &probeFlag, 0, 0);
    if (probeFlag != 0 && DAT_00AC1838 == 0)
    {
        DAT_00AC1838 = operator new(0x40000);
        for (int i = 0; i < 0x10000; ++i)
        {
            unsigned short lo = (unsigned short)i;
            unsigned char redSample  = (unsigned char)((char)(lo >> gg_b_translucent_pixel_format.pos0)   << gg_b_translucent_pixel_format.loss0);
            unsigned char grnSample  = (unsigned char)((char)(lo >> gg_b_translucent_pixel_format.pos1) << gg_b_translucent_pixel_format.loss1);
            unsigned char bluSample  = (unsigned char)((char)(lo >> gg_b_translucent_pixel_format.pos2)  << gg_b_translucent_pixel_format.loss2);
            ((unsigned*)DAT_00AC1838)[i] =
                ((unsigned)redSample << 8 | grnSample) << 8 | bluSample;
        }
    }
}

// FUNCTION: GAMEMD 0x5FF800  FUN_005FF800
// Release the whole cached surface set at shutdown: the companion block first,
// then every BSurface in the table, clearing each slot as it goes so a second
// call is harmless.
void FUN_005FF800()
{
    if (DAT_00AC1838 != 0)
    {
        operator delete(DAT_00AC1838);
        DAT_00AC1838 = 0;
    }

    for (int i = 0; i < 74; ++i)
    {
        if (DAT_00AC1698[i] != 0)
            delete DAT_00AC1698[i];

        DAT_00AC1698[i] = 0;
    }
}

// FUNCTION: GAMEMD 0x5FFFA0  SpotLightClass::DrawAll (__fastcall, static)
void SpotLightClass::DrawAll()
{
    for (int i = SpotlightArray.Count - 1; i >= 0; i--) {
        ((SpotLightClass**)SpotlightArray.Items)[i]->Draw();
    }
}


// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAC1698
BSurface_005FF800* DAT_00AC1698[74];
// GLOBAL: GAMEMD 0xAC1838
void* DAT_00AC1838;
// END defined globals
