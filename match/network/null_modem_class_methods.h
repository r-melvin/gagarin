// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   The class was identified from its own runtime type information: the
//   vtable at 0x7EEFDC carries 0x5F1950 in slot 4, its complete object locator
//   sits one dword below at 0x7EEFD8 -> 0x8073B0, whose type descriptor at
//   +0xC is 0x832370, and the name eight bytes into that reads
//   ".?AVNullModemClass@@". The COM1..COM4 device-name constants the port
//   detector selects (0x832340 / 0x832345 / 0x83234A / 0x83234F) confirm it.
//   Every offset below was read numerically from the user's own retail
//   gamemd.exe v1.001. Shutdown is named by a binary string; NumConnections,
//   SendOverflows, SetTiming, RetryDelta, MaxRetries and Timeout are
//   YRpp-cross-checked names whose role the bodies below confirm. Members and
//   methods with no such attestation keep unknown_XX / FUN_XXXXXXXX names.
//
// Offsets confirmed numerically (all from the 0x5F1950-0x5F1C4E run):
//   +0x04 unknown_04        `MOV 0x4(%ESI),%EAX` then freed in 0x5F1960
//   +0x0C unknown_0C         `MOV 0xC(%ESI),%EAX` then freed in 0x5F1960
//   +0x34 unknown_34   deleted and rebuilt in the port detector 0x5F19E0
//   +0x38 Connection      `MOV 0x38(%ESI),%ECX` + slot-0 delete in 0x5F1960,
//                         and the slot-2 / slot-4 packet calls in 0x5F1BF0 /
//                         0x5F1C30
//   +0x3C NumConnections  returned whole by 0x5F1950, zeroed by 0x5F1960,
//                         and the zero guard of 0x5F1BF0 and 0x5F1C30
//   +0x40 unknown_40      compared with -1 and reset to -1 by 0x5F1B70
//   +0x50 unknown_50           freed in 0x5F1960; the read base in 0x5F1C60
//   +0x54 unknown_54 / +0x58 unknown_58  the `MOV 0x58,%EAX / MOV 0x54,%ECX` pair
//   +0x5C RetryDelta / +0x60 MaxRetries / +0x64 Timeout   stored by 0x5F1BC0
//   +0x68 SendOverflows   `INCL 0x68(%ESI)` on a failed send in 0x5F1BF0
// The connection object's own +0x04 (its packet queue), +0x28, +0x2C and +0x30
// (its copies of the three timing values) are read off the same bodies.
#ifndef GG_MATCH_NETWORK_NULL_MODEM_CLASS_METHODS_H
#define GG_MATCH_NETWORK_NULL_MODEM_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "win_modem_class.h"
#include "transport/connman_class.h"

// The connection's packet queue. Only the queue reset at 0x48B390 is reached
// from this translation unit, as a direct (non-virtual) call.
struct NullModemQueueClass
{
    // FUNCTION: GAMEMD 0x48B390 (decl; reloc) — CommBufferClass send-queue reset.
    void FUN_0048B390();
};

// The NULL-modem connection object. Modelled with its used vtable slots in
// order so the indirect calls land on the right displacements: slot 0 is the
// scalar deleting destructor VC6 puts there, slot 2 sends a packet and slot 4
// pops one. The intervening slots are stand-ins and are never called here.
class NullModemConnClass
{
public:
    virtual ~NullModemConnClass();                                   // slot 0
    virtual int Slot1();                                             // slot 1
    // VTABLE slot 2 — send one packet; zero means the send queue was full.
    virtual int vf_2(void* buf, int buflen, int ackReq,
                           int extra);                               // slot 2
    virtual int Slot3();                                             // slot 3
    // VTABLE slot 4 — pop one received packet.
    virtual int vf_4(void* buf, int* buflen);                    // slot 4

    NullModemQueueClass* Queue;   // +0x0004
    char unknown_08[0x20];        // +0x0008
    int  RetryDelta;              // +0x0028
    int  MaxRetries;              // +0x002C
    int  Timeout;                 // +0x0030
};
GG_STATIC_ASSERT(offsetof(NullModemConnClass, Queue) == 0x4 &&
                 offsetof(NullModemConnClass, RetryDelta) == 0x28 &&
                 offsetof(NullModemConnClass, MaxRetries) == 0x2C &&
                 offsetof(NullModemConnClass, Timeout) == 0x30);

// One entry of the Win32 modem registry enumeration: 0x1C bytes, built from a
// zero-based index. Only the two name accessors are reached here, at +0x00 and
// +0x04. The no-throw specification was load-bearing under `/GX`, the tree's
// earlier flag set:
// without it the `new ModemEntry_005BB6E0(i)` below emits the unwind frame
// that would free the block if the constructor threw, and retail has none.
struct ModemEntry_005BB6E0
{
    char* ModemName;         // +0x0000
    char* DeviceName;   // +0x0004
    char  unknown_08[0x14];  // +0x0008

    // FUNCTION: GAMEMD 0x5BB6E0 (decl; reloc) — the index constructor.
    ModemEntry_005BB6E0(int index) throw();
    // FUNCTION: GAMEMD 0x5BBED0 (decl; reloc) — the destructor.
    ~ModemEntry_005BB6E0() throw();

    char* GetModemName() const { return ModemName; }
    char* Inline_005F16E0() const { return DeviceName; }
};
GG_STATIC_ASSERT(offsetof(ModemEntry_005BB6E0, ModemName) == 0x0 &&
                 offsetof(ModemEntry_005BB6E0, DeviceName) == 0x4 &&
                 sizeof(ModemEntry_005BB6E0) == 0x1C);

// The serial settings block the port detector is handed. Only the port
// address, the baud rate and the device-name buffer are read here.
struct SerialSettings_005F19E0
{
    int  Port;                // +0x0000
    int  unknown_04;          // +0x0004
    int  Baud;                // +0x0008
    char unknown_0C[0x24];    // +0x000C
    char ModemName[1];        // +0x0030
};
GG_STATIC_ASSERT(offsetof(SerialSettings_005F19E0, Port) == 0x0 &&
                 offsetof(SerialSettings_005F19E0, Baud) == 0x8 &&
                 offsetof(SerialSettings_005F19E0, ModemName) == 0x30);

// WinModemClass (the serial-port wrapper) lives in win_modem_class.h.

// GLOBAL: GAMEMD 0xB72D20 — the one shared WinModemClass instance.
extern WinModemClass* WinModem_00B72D20;

// RTTI: COL8073B0/CHD8073A0 proves ConnManClass at offset0.
// ev_05a1717de609b2762dade452be4adf4b19ca03738c4b8a9c9448c90288aa46ba;
// ev_cdf89b66192ca72a3586b91a9bb61b0ac34ba6347011b95490426280282b722f.
// VTABLE: GAMEMD 0x7EEFDC
class NullModemClass : public ConnManClass
{
public:
    // Declaration: GAMEMD 0x5F1650 -- ordinary destructor
    // Declaration: GAMEMD 0x5F3650 -- scalar deleting destructor
    virtual ~NullModemClass();                                           // slot0
    virtual int Service();                                               // slot1,5F1C60
    virtual int vf_2(void*, int, int, int);                                // slot2,5F3560
    virtual int vf_3(void*, int*, int*);                                   // slot3,5F35A0
    virtual int vf_4();                                                   // slot4,5F1950
    virtual int vf_5(int);                                                // slot5,5F3520
    virtual int vf_6(int);                                                // slot6,5F3530
    virtual int vf_7();                                                   // slot7,5F35D0
    virtual int vf_8();                                                   // slot8,5F35F0
    virtual int vf_9(int);                                                // slot9,5F3610
    virtual int vf_10(int);                                               // slot10,5F3630
    virtual void vf_11(bool);                                             // slot11,5F1F00
    virtual int ResponseTime();                                          // slot12,5F1EE0
    virtual void SetTiming(int, int, int, bool);                           // slot13,5F1BC0
    virtual void vf_14(int, int, int);                                    // slot14,5F3540
    virtual void vf_15(int, int, int, int, int, int);                       // slot15,5F1F70
    char*  unknown_04;                 // +0x0004
    int    unknown_08;                   // +0x0008
    char*  unknown_0C;                  // +0x000C
    int    unknown_10;                 // +0x0010
    int    unknown_14;                // +0x0014
    char   unknown_18[0x1C];         // +0x0018
    ModemEntry_005BB6E0* unknown_34;   // +0x0034
    NullModemConnClass* Connection;  // +0x0038
    int    NumConnections;           // +0x003C
    int    unknown_40;               // +0x0040
    char   unknown_44[0xC];          // +0x0044
    char*  unknown_50;                    // +0x0050
    int    unknown_54;                   // +0x0054
    int    unknown_58;                  // +0x0058
    int    RetryDelta;               // +0x005C
    int    MaxRetries;               // +0x0060
    int    Timeout;                  // +0x0064
    int    SendOverflows;            // +0x0068

    // FUNCTION: GAMEMD 0x5F1960
    int FUN_005F1960();
    // FUNCTION: GAMEMD 0x5F19C0
    int FUN_005F19C0();
    // FUNCTION: GAMEMD 0x5F19E0
    int FUN_005F19E0(SerialSettings_005F19E0* settings);
    // FUNCTION: GAMEMD 0x5F1B70
    void Shutdown();
    // FUNCTION: GAMEMD 0x5F1BF0
    int FUN_005F1BF0(void* buf, int buflen, int ackReq);
    // FUNCTION: GAMEMD 0x5F1C30
    int FUN_005F1C30(void* buf, int* buflen);
};
GG_STATIC_ASSERT(offsetof(NullModemClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(NullModemClass, unknown_04) == 0x04 &&
                 offsetof(NullModemClass, unknown_0C) == 0x0C &&
                 offsetof(NullModemClass, unknown_34) == 0x34 &&
                 offsetof(NullModemClass, Connection) == 0x38 &&
                 offsetof(NullModemClass, NumConnections) == 0x3C);
GG_STATIC_ASSERT(offsetof(NullModemClass, unknown_40) == 0x40 &&
                 offsetof(NullModemClass, unknown_50) == 0x50 &&
                 offsetof(NullModemClass, unknown_54) == 0x54 &&
                 offsetof(NullModemClass, unknown_58) == 0x58 &&
                 offsetof(NullModemClass, RetryDelta) == 0x5C &&
                 offsetof(NullModemClass, MaxRetries) == 0x60 &&
                 offsetof(NullModemClass, Timeout) == 0x64 &&
                 offsetof(NullModemClass, SendOverflows) == 0x68);

// GLOBAL: GAMEMD 0xA8EA70
extern NullModemClass DAT_00A8EA70;

#endif  // GG_MATCH_NETWORK_NULL_MODEM_CLASS_METHODS_H
