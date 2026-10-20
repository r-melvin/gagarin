// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x626C60.
//   LIBRARY: GAMEMD 0x7C8E17  operator new  (CRT; reloc)

#include "color_scheme_count_methods.h"

// The hash table's constructor: hash routine, bucket count, growth step 10,
// then the bucket array (vector-new with the count cookie in front and the
// strided constructor iterator, spelt out because cl 8804 expands the loop
// inline instead) and each bucket's growth step.
inline Table_00626C60::Table_00626C60(HashFn_00626C60 hash, int numBuckets) throw()
    : Hash(hash), NumBuckets(numBuckets), At_0C(10)
{
    int* raw = (int*)FUN_007C8E17(4 + 31 * sizeof(Bucket_00626C60));
    Bucket_00626C60* buckets;
    if (raw != 0) {
        buckets = (Bucket_00626C60*)(raw + 1);
        raw[0] = 31;
        FUN_004068F0((char*)buckets, sizeof(Bucket_00626C60), 31, FUN_00628740);
    } else {
        buckets = 0;
    }
    this->Buckets = buckets;

    for (int i = 0; i < this->NumBuckets; i++) {
        this->Buckets[i].CapacityIncrement = 10;
    }
}

inline Owner_00626C60::Owner_00626C60() throw()
    : At_00(-1),
      VecA(new VecA_00626C60()),
      VecB(new VecB_00626C60()),
      Table(new Table_00626C60(FUN_00626660, 31))
{
}

// FUNCTION: GAMEMD 0x626C60
//
// Number of colour schemes: lazily builds the palette-table owner on first
// use and answers the count of its first scheme vector.
int ColorScheme_00626C60::GetNumberOfSchemes()
{
    if (DAT_00AC48F0 == 0) {
        DAT_00AC48F0 = new Owner_00626C60();
    }
    return DAT_00AC48F0->VecA->Count;
}
