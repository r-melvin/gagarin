// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The single declaration of the global at 0x887628. Kept apart from
//   winsock_interface_class.h so that headers which only compare or null-test
//   the pointer need not pull in the winsock headers (their library pragmas
//   would change the object's linker directives).
#ifndef GG_MATCH_NETWORK_TRANSPORT_PACKET_INTERFACE_GLOBAL_H
#define GG_MATCH_NETWORK_TRANSPORT_PACKET_INTERFACE_GLOBAL_H

class WinsockInterfaceClass;

// GLOBAL: GAMEMD 0x887628 -- the packet interface: a UDPInterfaceClass or an
// IPXInterfaceClass, created by the network setup. Cast down to call slots
// that only the derived class declares.
extern WinsockInterfaceClass* Interface_00887628;

#endif
