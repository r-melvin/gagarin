// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
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

// ABI-sized transport views used by the M1 connection callers: the binary
// passes one four-byte network value and one six-byte node value.
struct NetworkNumberType
{
    unsigned long Number;
};
struct NodeAddressType
{
    unsigned char Node[6];
};
GG_STATIC_ASSERT(offsetof(NetworkNumberType, Number) == 0);
GG_STATIC_ASSERT(offsetof(NodeAddressType, Node) == 0);
GG_STATIC_ASSERT(sizeof(NetworkNumberType) == 0x4);
GG_STATIC_ASSERT(sizeof(NodeAddressType) == 0x6);

class IPXAddressClass
{
public:
    // FUNCTION: GAMEMD 0x53ECB0 (decl; reloc) — initializes bytes +0..+9.
    IPXAddressClass();

    // FUNCTION: GAMEMD 0x53EDA0 (decl; reloc) — two output pointers; RET 8.
    void GetAddress(unsigned char* network, unsigned char* node);

    // FUNCTION: GAMEMD 0x53EDA0 (decl; reloc) — transport reference call view.
    void FUN_0053EDA0(NetworkNumberType& network, NodeAddressType& node);
    // FUNCTION: GAMEMD 0x53ED20 (decl; reloc) — transport reference call view.
    void FUN_0053ED20(NetworkNumberType& network, NodeAddressType& node,
                     unsigned short port);
    // FUNCTION: GAMEMD 0x53EE70 (decl; reloc) — existing pointer-compare API.
    bool FUN_0053EE70(const IPXAddressClass* other) const;
    // FUNCTION: GAMEMD 0x53EE70 (decl; reloc) — transport reference call view.
    bool Equals_EE70(IPXAddressClass& other);
    // FUNCTION: GAMEMD 0x53EE70 (decl; reloc) — transport pointer call view.
    bool FUN_0053EE70(const IPXAddressClass* other);
    // FUNCTION: GAMEMD 0x53EF30 (decl; reloc) — transport reference call view.
    bool Equals_EF30(IPXAddressClass& other);
    // FUNCTION: GAMEMD 0x53EF30 (decl; reloc) — transport pointer call view.
    bool FUN_0053EF30(const IPXAddressClass* other);
    // FUNCTION: GAMEMD 0x53EF60 (decl; reloc).
    bool FUN_0053EF60(const IPXAddressClass* other);
    // FUNCTION: GAMEMD 0x53EE00 (decl; reloc).
    int IsBroadcast();
    // FUNCTION: GAMEMD 0x53F0E0 (decl; reloc).
    char* FUN_0053F0E0(int a1);
    // FUNCTION: GAMEMD 0x53F200 (decl; reloc).
    void FUN_0053F200(unsigned short port);

    union {
        unsigned char NetworkNumber[4]; // +0x00 (network / port storage)
        unsigned short Port;            // +0x00 transport view
    };
    unsigned char NodeAddress[6];       // +0x04
    unsigned char unknown_0A[2];         // +0x0A (within the proven 12-byte extent)
};

GG_STATIC_ASSERT(offsetof(IPXAddressClass, NetworkNumber) == 0x00);
GG_STATIC_ASSERT(offsetof(IPXAddressClass, Port) == 0x00);
GG_STATIC_ASSERT(offsetof(IPXAddressClass, NodeAddress) == 0x04);
GG_STATIC_ASSERT(offsetof(IPXAddressClass, unknown_0A) == 0x0A);
GG_STATIC_ASSERT(sizeof(IPXAddressClass) == 0x0C);

#endif
