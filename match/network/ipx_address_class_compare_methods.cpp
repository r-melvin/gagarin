// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x53F020..0x53F0B0.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x53F020  IPXAddressClass::operator>
//   FUNCTION: GAMEMD 0x53F050  IPXAddressClass::operator<
//   FUNCTION: GAMEMD 0x53F080  IPXAddressClass::operator>=
//   FUNCTION: GAMEMD 0x53F0B0  IPXAddressClass::operator<=
//   FUNCTION: GAMEMD 0x53EE00  IPXAddressClass::IsBroadcast
//   FUNCTION: GAMEMD 0x53ED20  IPXAddressClass::FUN_0053ED20
//   FUNCTION: GAMEMD 0x53EF30  IPXAddressClass::FUN_0053EF30
//   FUNCTION: GAMEMD 0x53ECE0  IPXAddressClass::IPXAddressClass(network, node, port)
//   FUNCTION: GAMEMD 0x53ED60  IPXAddressClass::FUN_0053ED60

#include <string.h>
#pragma intrinsic(memcmp)
#include "../_layout/ipx_address_class.h"

// FUNCTION: GAMEMD 0x53F020
bool IPXAddressClass::operator>(const IPXAddressClass& other) const
{
    return memcmp(this, &other, 10) > 0;
}

// FUNCTION: GAMEMD 0x53F050
bool IPXAddressClass::operator<(const IPXAddressClass& other) const
{
    return memcmp(this, &other, 10) < 0;
}

// FUNCTION: GAMEMD 0x53F080
bool IPXAddressClass::operator>=(const IPXAddressClass& other) const
{
    return memcmp(this, &other, 10) >= 0;
}

// FUNCTION: GAMEMD 0x53F0B0
bool IPXAddressClass::operator<=(const IPXAddressClass& other) const
{
    return memcmp(this, &other, 10) <= 0;
}

// GLOBAL: GAMEMD 0x828140 -- transport mode; 1 selects the full-address forms.
extern int DAT_00828140;

// FUNCTION: GAMEMD 0x53EE00
// An address is the broadcast address when every byte that counts in the
// current mode is 0xFF: all ten in mode 1, only the node bytes otherwise.
int IPXAddressClass::IsBroadcast()
{
    unsigned char ff = 0xFF;
    if (DAT_00828140 == 1) {
        return NetworkNumber[0] == ff && NetworkNumber[1] == ff
            && NetworkNumber[2] == ff && NetworkNumber[3] == ff
            && NodeAddress[0] == ff && NodeAddress[1] == ff
            && NodeAddress[2] == ff && NodeAddress[3] == ff
            && NodeAddress[4] == ff && NodeAddress[5] == ff;
    }
    return NodeAddress[0] == ff && NodeAddress[1] == ff
        && NodeAddress[2] == ff && NodeAddress[3] == ff
        && NodeAddress[4] == ff && NodeAddress[5] == ff;
}

// FUNCTION: GAMEMD 0x53ED20
// Store the node address, then either the network number (mode 1) or just the
// port with the rest of the number cleared.
void IPXAddressClass::FUN_0053ED20(const NetworkNumberType* network, const NodeAddressType* node,
                                   unsigned short port)
{
    *(NodeAddressType*)NodeAddress = *node;
    if (DAT_00828140 == 1) {
        *(unsigned long*)NetworkNumber = network->Number;
    } else {
        *(unsigned long*)NetworkNumber = 0;
        Port = port;
    }
}

// FUNCTION: GAMEMD 0x53EF30
// Compare the node bytes: four of them in mode 2, six otherwise.
bool IPXAddressClass::FUN_0053EF30(const IPXAddressClass* other)
{
    return memcmp(NodeAddress, other->NodeAddress, DAT_00828140 == 2 ? 4 : 6) == 0;
}

// FUNCTION: GAMEMD 0x53ECE0
// Build an address from its parts: the node always, then the network number
// (mode 1) or only the port.
IPXAddressClass::IPXAddressClass(const NetworkNumberType& network, const NodeAddressType& node,
                                 unsigned short port)
{
    *(NodeAddressType*)NodeAddress = node;
    if (DAT_00828140 == 1) {
        *(unsigned long*)NetworkNumber = network.Number;
    } else {
        *(unsigned long*)NetworkNumber = 0;
        Port = port;
    }
}

// FUNCTION: GAMEMD 0x53ED60
// Hand the parts back: the node always, then the network number (mode 1) or
// only the port.
void IPXAddressClass::FUN_0053ED60(NetworkNumberType* network, NodeAddressType* node,
                                   unsigned short* port)
{
    *node = *(NodeAddressType*)NodeAddress;
    if (DAT_00828140 == 1) {
        network->Number = *(unsigned long*)NetworkNumber;
    } else {
        *port = Port;
    }
}
