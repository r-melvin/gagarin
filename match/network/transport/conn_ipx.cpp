// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /Ob1
#include "conn_types.h"
#include "winsock_interface_class.h"
#include "connman_class.h"

// VTABLE: GAMEMD 0x7EC0CC  IPXConnClass (11 slots)
// migrated from match/core/derived_sdd_family_methods.cpp (DerivedSdd<Base_ConnectionClass,
// Tag_IPXConnClass>, 0x53F850 len 0x24); integrator retires the old row.

// FUNCTION: GAMEMD 0x53F430
IPXConnClass::IPXConnClass(int numsend, int numreceive, int maxlen,
                           unsigned short magicnum, IPXAddressClass* address,
                           int id, wchar_t* name, int extralen)
    : ConnectionClass(numsend, numreceive, maxlen, magicnum, 2, -1, 0x3C, extralen)
{
    if (address) {
        Address = *address;
    }
    ID = id;
    wcscpy(Name, name);
    NodeAddressType node;
    NetworkNumberType net;
    Address.Get_Address(net, node);
    unknown_58 = node;
    unknown_60 = 0;
}

// FUNCTION: GAMEMD 0x53F4E0
void IPXConnClass::Init()
{
    ConnectionClass::Init();
}

// FUNCTION: GAMEMD 0x53F5D0
int IPXConnClass::Send_To(void* buf, int buflen, void* extrabuf, int extralen,
                          bool is_global, unsigned short unknown_6)
{
    return Send_To_Address(buf, buflen, &Address, 0, is_global, 0);
}

// FUNCTION: GAMEMD 0x53F650
// PARTIAL 57.9% (was 52.0%). The header-stamping half is a plain if/else on
// `is_global || !Flag_00A8DBA0` (the goto labels are gone), which lines it up with
// retail up to the ConnectionIndexOf call. Residual: the connection-index chain
// (retail `cmp -4; je; jle` then a repeated `test esi,esi`), and retail clears
// the header dword through a separate `LEA` of hdr+8. That LEA is the shape of an
// intrinsic 4-byte memset; it is not reproduced here because the field's type
// (array or dword) has no independent evidence yet.
int IPXConnClass::Send_To_Address(void* buf, int buflen, IPXAddressClass* address,
                                  unsigned long* network, bool is_global,
                                  unsigned short unknown_6)
{
    IPXAddressClass local;
    local = *address;
    if (network) {
        NodeAddressType node;
        NetworkNumberType net;
        address->Get_Address(net, node);
        net.Number = *network;
        local.Set_Address(net, node, 0);
    }

    unsigned short port = 0;
    CommHeaderType* hdr;
    if (is_global || !Flag_00A8DBA0) {
        hdr = (CommHeaderType*)buf;
        hdr->unknown_0C = 0;
        hdr->unknown_08 = 0;
    } else {
        hdr = (CommHeaderType*)buf;
        if (hdr->unknown_03 == 0) {
            unsigned char id = IdMap_00B052D0.FUN_00663D60(ID);
            if (!id) {
                return 0;
            }
            hdr->unknown_03 = id;
        }
        local = Address_00A8DBA4;
        port = Port_00841F3C;
        if (Address_00A8DBB0.Equals_EE70(Players_00A8DA78[0]->Address)
            && local.Equals_EF30(Players_00A8DA78[0]->Address)) {
            hdr->unknown_0C = 0;
            hdr->unknown_08 = 0;
        } else {
            hdr->unknown_0C = (unsigned short)Port_00841F3C;
            port = Port_00A8DBBC;
            hdr->unknown_08 = 0;
        }
    }

    if (Session_00A8B238.GameMode == 4 && !Flag_00A8DBA0) {
        int idx = Manager_00A8E9C0.IPXManagerClass::ConnectionIndexOf(this);
        if (idx == -4) {
            if ((unsigned short)Port_00A8DBBC) {
                port = Port_00A8DBBC;
            }
        } else if (idx >= 0) {
            if (idx == 0 && Flag_00A8DBA0) {
                if ((unsigned short)Port_00A8DBBC) {
                    port = Port_00A8DBBC;
                }
            } else if (idx < Manager_00A8E9C0.IPXManagerClass::NumConnections()) {
                port = Session_00A8B238.FUN_0069BC20(Manager_00A8E9C0.IPXManagerClass::ConnectionId(idx));
            }
        }
    }

    if (Interface_00887628) {
        Interface_00887628->SendPacket(buf, buflen, &local, 0xC, is_global, 0, port);
    }
    return 1;
}

// SYNTHETIC: GAMEMD 0x53F850  IPXConnClass::`scalar deleting destructor'
