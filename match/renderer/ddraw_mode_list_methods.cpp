// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// Enumerates the DirectDraw display modes into a DynamicVectorClass of
// surface descriptions (vtables 0x7E5E0C / 0x7E5DEC, enumeration callback
// 0x4A4850) and returns a new, zero-terminated array of {width, height}
// pairs for the modes within [min, max] at the requested depth, sorted by
// 0x4A48C0; 0 when DirectDraw is absent or nothing fits. Each description
// is freed as it is visited.

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"

// Surface description as filled by the enumeration callback.
struct DDModeDesc
{
    unsigned long Size;          // +0x00
    unsigned long Flags;         // +0x04
    unsigned long Height;        // +0x08
    unsigned long Width;         // +0x0C
    char          unknown_10[0x44];
    unsigned long BitCount;      // +0x54 (pixel format at +0x48)
};
GG_STATIC_ASSERT(offsetof(DDModeDesc, Height) == 0x08);
GG_STATIC_ASSERT(offsetof(DDModeDesc, Width) == 0x0C);
GG_STATIC_ASSERT(offsetof(DDModeDesc, BitCount) == 0x54);

// The VectorClass capacity constructor stays out of line (0x4A4E30); the
// DynamicVectorClass one is expanded in place.
template<> inline DynamicVectorClass<DDModeDesc*>::DynamicVectorClass(int capacity, DDModeDesc** pMem)
    : VectorClass<DDModeDesc*>(capacity, pMem)
{
    this->CapacityIncrement = 10;
    this->Count = 0;
}

struct DDrawEnumView;

struct DDrawEnumVtbl
{
    void* unknown_00[8];
    long (__stdcall* EnumDisplayModes)(DDrawEnumView* self, unsigned long flags, void* desc,
                                       void* context, void* callback);   // +0x20
};
GG_STATIC_ASSERT(offsetof(DDrawEnumVtbl, EnumDisplayModes) == 0x20);

struct DDrawEnumView
{
    DDrawEnumVtbl const* lpVtbl;
};

// GLOBAL: GAMEMD 0x8A0094 -- the DirectDraw object.
extern DDrawEnumView* DAT_008A0094;

// FUNCTION: GAMEMD 0x4A4850 (decl; reloc) -- appends a copy of each mode.
long __stdcall FUN_004a4850(DDModeDesc* desc, void* context);
// FUNCTION: GAMEMD 0x4A48C0 (decl; reloc) -- qsort comparator over the pairs.
int __cdecl FUN_004a48c0(void const* a, void const* b);

// FUNCTION: GAMEMD 0x4A4900
unsigned long* FUN_004a4900(unsigned long min_width, unsigned long min_height,
                            unsigned long max_width, unsigned long max_height,
                            unsigned long bit_count)
{
    if (DAT_008A0094 == 0)
    {
        return 0;
    }
    DynamicVectorClass<DDModeDesc*> modes;
    if (DAT_008A0094->lpVtbl->EnumDisplayModes(DAT_008A0094, 0, 0, &modes, FUN_004a4850) != 0 || modes.GetCount() == 0)
    {
        return 0;
    }
    unsigned long* list = (unsigned long*)operator new(modes.GetCount() * 8 + 4);
    memset(list, 0, modes.GetCount() * 8 + 4);
    unsigned long* out = list;
    int found = 0;
    for (int i = 0; i < modes.GetCount(); i++)
    {
        DDModeDesc* desc = modes.Items[i];
        if (desc->Width <= max_width && desc->Height <= max_height
            && desc->Width >= min_width && desc->Height >= min_height
            && desc->BitCount == bit_count)
        {
            *out++ = desc->Width;
            *out++ = desc->Height;
            found++;
        }
        operator delete(modes.Items[i]);
    }
    if (out == list)
    {
        operator delete(list);
        return 0;
    }
    qsort(list, found, 8, FUN_004a48c0);
    return list;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A0094
DDrawEnumView* DAT_008A0094;
// END defined globals
