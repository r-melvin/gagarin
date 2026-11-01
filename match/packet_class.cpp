// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp / FieldClass.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4CB8B0  FieldClass::HostToNet  (__thiscall)
//   FUNCTION: GAMEMD 0x4CB920  FieldClass::NetToHost  (__thiscall)

#include "packet_class.h"

// Winsock byte-order helpers (__stdcall imports). Declared (no body) so the
// harness reloc-normalises the call thunks at 0x7C8962/0x7C8968/0x7C896E/
// 0x7C8974.
extern "C" unsigned short __stdcall htons(unsigned short netshort);
extern "C" unsigned long  __stdcall htonl(unsigned long  hostlong);
extern "C" unsigned short __stdcall ntohs(unsigned short netshort);
extern "C" unsigned long  __stdcall ntohl(unsigned long  netlong);

// FUNCTION: GAMEMD 0x4CB8B0  (__thiscall)
// Convert this field from host to network byte order. The switch runs first on
// the still-host-order DataType, swapping the payload; then DataType and Size
// are swapped.
void FieldClass::HostToNet()
{
    switch (DataType)
    {
    case 3:
    case 4:
        *(unsigned short*)Data = htons(*(unsigned short*)Data);
        break;
    case 5:
    case 6:
        *(unsigned long*)Data = htonl(*(unsigned long*)Data);
        break;
    }

    DataType = htons(DataType);
    Size = htons(Size);
}

// FUNCTION: GAMEMD 0x4CB920  (__thiscall)
// Convert this field from network to host byte order. Size and DataType are
// swapped first, then the now-host-order DataType selects the payload swap.
void FieldClass::NetToHost()
{
    Size = ntohs(Size);
    DataType = ntohs(DataType);

    switch (DataType)
    {
    case 3:
    case 4:
        *(unsigned short*)Data = ntohs(*(unsigned short*)Data);
        break;
    case 5:
    case 6:
        *(unsigned long*)Data = ntohl(*(unsigned long*)Data);
        break;
    }
}
