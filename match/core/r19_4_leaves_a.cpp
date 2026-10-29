// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. The owned-connection
//   list holder (a DynamicVectorClass of pointers, vtable 0x7F0C2C, then a flag byte at +0x18
//   and a dword at +0x1C) as a stand-alone constructor, clear and destructor.
//
// Address index: 0x6638E0 0x663910 0x663960 0x664750

#include "vector_class_operations.h"
#include "../network/transport/connman_class.h"

// STRING: GAMEMD 0x839CEC
extern const char STR_00839CEC[];

// The 0x152-byte kind-6 message: kind byte, one value byte, zero padding.
struct Kind6Packet_00664750
{
    unsigned char Kind;
    unsigned char Value;
    char unknown_02[0x150];
};

class OwnerTalkClass {
public:
    struct ConnectionListStruct;
};

// Record fields touched by this file's lookups: +0x00 id byte, +0x28 status byte.
struct OwnerTalkClass::ConnectionListStruct {
    char Id;
    char unknown_01[0x27];
    char Status;
};

struct ConnListView_006638E0 {
    DynamicVectorClass<OwnerTalkClass::ConnectionListStruct*> List;
    bool Flag;
    int Extra;

    ConnListView_006638E0();
    ~ConnListView_006638E0();
    void Clear();
    void SendKind6(unsigned char value);
};

// FUNCTION: GAMEMD 0x6638E0
// Construct the empty list.
ConnListView_006638E0::ConnListView_006638E0() : Flag(false), Extra(0)
{
}

// FUNCTION: GAMEMD 0x663960
// Free every element, then the vector storage (inlined vector destructor).
ConnListView_006638E0::~ConnListView_006638E0()
{
    while (List.Count != 0) {
        delete List.Items[0];
        List.Delete(0);
    }
}

// FUNCTION: GAMEMD 0x663910
// Free every element, then reset the flag and extra word.
void ConnListView_006638E0::Clear()
{
    while (List.Count != 0) {
        delete List.Items[0];
        List.Delete(0);
    }
    Flag = false;
    Extra = 0;
}

// FUNCTION: GAMEMD 0x664750
// When the flag is set, log and send the kind-6 message carrying `value`.
void ConnListView_006638E0::SendKind6(unsigned char value)
{
    Kind6Packet_00664750 packet = { 0 };
    if (Flag) {
        packet.Kind = 6;
        packet.Value = value;
        FUN_004068E0(STR_00839CEC);
        Manager_00A8E9C0.FUN_00541410(&packet, sizeof(packet), 1);
    }
}
