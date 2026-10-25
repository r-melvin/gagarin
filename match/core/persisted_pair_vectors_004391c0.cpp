// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001; focused Ghidra/REA entry evidence:
//   0x4391C0 (0x95 bytes) and 0x439260 (0x16A bytes). The save path writes
//   each vector count and 4-byte item through stream vtable slot +0x10. The
//   load path reads the same sequences through slot +0x0C, appends with the
//   vector's +0x08 capacity slot, then registers each loaded pointer through
//   0x006CF240 and the global at 0x00B0C110.

#include "persisted_pair_vectors_004391c0.h"

// DAT_00B0C110 is declared and binary-annotated by stream_persist_methods.h.
// FUNCTION: GAMEMD 0x006CF240 (decl; reloc) -- external direct call.
// Its __stdcall ABI and (registry, pointer-address) argument order are also
// visible in the matched load paths at 0x438B40 and 0x439260.
extern "C" long __stdcall FUN_006CF240(void* registry, void** pointer);

// FUNCTION: GAMEMD 0x004391C0
long PairVectorOwnerView_004391C0::Save(Stream_00410320* stream)
{
    long result;
    int index;
    int count = first.count;
    result = STREAM_WRITE(stream, &count, 4);
    if (result < 0)
        return result;

    for (index = 0; index < count; ++index) {
        result = STREAM_WRITE(stream, &first.items[index], 4);
        if (result < 0)
            return result;
    }

    count = second.count;
    result = STREAM_WRITE(stream, &count, 4);
    if (result < 0)
        return result;

    for (index = 0; index < count; ++index) {
        result = STREAM_WRITE(stream, &second.items[index], 4);
        if (result < 0)
            return result;
    }
    return result;
}

// FUNCTION: GAMEMD 0x00439260
long PairVectorOwnerView_004391C0::Load(Stream_00410320* stream)
{
    long result;
    int count;
    void* firstItem;
    void* secondItem;

    result = STREAM_READ(stream, &count, 4);
    if (result < 0)
        return result;

    {
        for (int firstIndex = 0; firstIndex < count; ++firstIndex) {
            result = STREAM_READ(stream, &firstItem, 4);
            if (result < 0)
                return result;

            if (first.count < first.capacity ||
                ((first.isAllocated != 0 || first.capacity == 0) &&
                 first.capacityIncrement > 0 &&
                 first.setCapacity_08(first.capacity + first.capacityIncrement, 0))) {
                int oldCount = first.count;
                first.count = oldCount + 1;
                first.items[oldCount] = firstItem;
            }
        }
    }

    {
        for (int firstSwizzleIndex = 0; firstSwizzleIndex < count; ++firstSwizzleIndex)
            FUN_006CF240(&DAT_00B0C110, &first.items[firstSwizzleIndex]);
    }

    result = STREAM_READ(stream, &count, 4);
    if (result < 0)
        return result;

    {
        for (int secondIndex = 0; secondIndex < count; ++secondIndex) {
            result = STREAM_READ(stream, &secondItem, 4);
            if (result < 0)
                return result;

            PairVectorView_004391C0* secondView = &second;
            if (secondView->count < secondView->capacity ||
                ((secondView->isAllocated != 0 || secondView->capacity == 0) &&
                 secondView->capacityIncrement > 0 &&
                 secondView->setCapacity_08(
                     secondView->capacity + secondView->capacityIncrement, 0))) {
                int oldCount = secondView->count;
                secondView->count = oldCount + 1;
                secondView->items[oldCount] = secondItem;
            }
        }
    }

    {
        for (int secondSwizzleIndex = 0; secondSwizzleIndex < count; ++secondSwizzleIndex)
            FUN_006CF240(&DAT_00B0C110, &second.items[secondSwizzleIndex]);
    }

    return result;
}
