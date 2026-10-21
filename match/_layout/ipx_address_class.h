// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 instructions prove the 12-byte object extent:
//   IPXGlobalConnClass construction at 0x53FAFD..0x53FB25 allocates and walks
//   address elements at a 0xC stride; IPXConnClass construction at 0x53F45D
//   initializes an address at +0x4C, copies through +0x54, and starts the
//   following field at +0x58. The IPXAddressClass constructor at 0x53ECB0
//   writes only bytes +0..+9. The six-byte node view at +4 is read/written by
//   0x53EDA0, and the same entry is called by EventClass at 0x4C6C50. The
//   comparison view at 0x53EE70 reads at most +0..+9 and is called by the
//   lobby code at 0x5E92E1. Byte meanings beyond these observed accesses are
//   intentionally left unnamed.
#ifndef GG_MATCH_LAYOUT_IPX_ADDRESS_CLASS_H
#define GG_MATCH_LAYOUT_IPX_ADDRESS_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class IPXAddressClass
{
public:
    // FUNCTION: GAMEMD 0x53ECB0 (decl; reloc) — initializes bytes +0..+9.
    IPXAddressClass();

    // FUNCTION: GAMEMD 0x53EDA0 (decl; reloc) — two output pointers; RET 8.
    void GetAddress(unsigned char* network, unsigned char* node);

    // FUNCTION: GAMEMD 0x53EE70 (decl; reloc) — one pointer argument; RET 4.
    bool Is_Address(const IPXAddressClass* other) const;

    unsigned char NetworkNumber[4]; // +0x00 (network / port storage)
    unsigned char NodeAddress[6];   // +0x04
    unsigned char unknown_0A[2];    // +0x0A (within the proven 12-byte extent)
};

GG_STATIC_ASSERT(offsetof(IPXAddressClass, NetworkNumber) == 0x00);
GG_STATIC_ASSERT(offsetof(IPXAddressClass, NodeAddress) == 0x04);
GG_STATIC_ASSERT(offsetof(IPXAddressClass, unknown_0A) == 0x0A);
GG_STATIC_ASSERT(sizeof(IPXAddressClass) == 0x0C);

#endif
