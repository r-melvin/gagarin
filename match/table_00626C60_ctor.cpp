// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x628070.
//   PLACEMENT LEAD (inference): its caller 0x6269A0 in ownrdraw.cpp reaches it by a
//   real CALL. At /Ob2 cl inlines any body it can see, so the retail call implies the
//   body was compiled in a different original object than that caller. This file is
//   that separate object; the original file name is not known and is not claimed.
#include "color_scheme_count_methods.h"
#include "scratch_buffer_vector_methods.h"

// TUSPLIT: GAMEMD 0x6269A0 same-file 0.0% separate 100.0%
// FUNCTION: GAMEMD 0x628070
Table_00626C60::Table_00626C60(int nStep, int numBuckets, HashFn_00626C60 hash) throw()
{
    Hash = hash; NumBuckets = numBuckets; At_0C = nStep;
    Buckets = (Bucket_00626C60*)new DynamicVectorClass<ScratchEntry>[numBuckets];
    for (int i = 0; i < this->NumBuckets; i++) {
        this->Buckets[i].CapacityIncrement = nStep;
    }
}
