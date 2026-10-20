// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   The class was identified from its own runtime type information: the
//   vtable at 0x7EEFDC carries 0x5F1950 in slot 4, its complete object locator
//   sits one dword below at 0x7EEFD8 -> 0x8073B0, whose type descriptor at
//   +0xC is 0x832370, and the name eight bytes into that reads
//   ".?AVNullModemClass@@". The COM1..COM4 device-name constants the port
//   detector selects (0x832340 / 0x832345 / 0x83234A / 0x83234F) confirm it.
//   EA's GPLv3 Red Alert 1 NULLMGR.CPP/NULLMGR.H were read for member and
//   method NAMES only (Delete_Connection, Init_Send_Queue, Num_Connections,
//   Shutdown, Set_Timing, Send_Message, Get_Message, BuildBuf, EchoBuf,
//   RXBuf, Connection, NumConnections, SendOverflows); every offset below was
//   re-derived numerically from the user's own retail gamemd.exe v1.001 and
//   RA2's layout is NOT RA1's.
//
// Offsets confirmed numerically (all from the 0x5F1950-0x5F1C4E run):
//   +0x04 BuildBuf        `MOV 0x4(%ESI),%EAX` then freed in 0x5F1960
//   +0x0C EchoBuf         `MOV 0xC(%ESI),%EAX` then freed in 0x5F1960
//   +0x34 ModemRegistry   deleted and rebuilt in the port detector 0x5F19E0
//   +0x38 Connection      `MOV 0x38(%ESI),%ECX` + slot-0 delete in 0x5F1960,
//                         and the slot-2 / slot-4 packet calls in 0x5F1BF0 /
//                         0x5F1C30
//   +0x3C NumConnections  returned whole by 0x5F1950, zeroed by 0x5F1960,
//                         and the zero guard of 0x5F1BF0 and 0x5F1C30
//   +0x40 PortHandle      compared with -1 and reset to -1 by 0x5F1B70
//   +0x50 RXBuf           freed in 0x5F1960; the read base in 0x5F1C60
//   +0x54 RXSize / +0x58 RXCount  the `MOV 0x58,%EAX / MOV 0x54,%ECX` pair
//   +0x5C RetryDelta / +0x60 MaxRetries / +0x64 Timeout   stored by 0x5F1BC0
//   +0x68 SendOverflows   `INCL 0x68(%ESI)` on a failed send in 0x5F1BF0
// The connection object's own +0x04 (its packet queue), +0x28, +0x2C and +0x30
// (its copies of the three timing values) are read off the same bodies.
#ifndef GG_MATCH_NETWORK_NULL_MODEM_CLASS_METHODS_H
#define GG_MATCH_NETWORK_NULL_MODEM_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The connection's packet queue. Only Init_Send_Queue is reached from this
// translation unit, as a direct (non-virtual) call.
struct NullModemQueueClass
{
    // FUNCTION: GAMEMD 0x48B390 (decl; reloc) — CommBufferClass::Init_Send_Queue.
    void InitSendQueue();
};

// The NULL-modem connection object. Modelled with its used vtable slots in
// order so the indirect calls land on the right displacements: slot 0 is the
// scalar deleting destructor VC6 puts there, slot 2 sends a packet and slot 4
// pops one. The intervening slots are stand-ins and are never called here.
struct NullModemConnClass
{
    virtual ~NullModemConnClass();                                   // slot 0
    virtual int Slot1();                                             // slot 1
    // VTABLE slot 2 — send one packet; zero means the send queue was full.
    virtual int SendPacket(void* buf, int buflen, int ackReq,
                           int extra);                               // slot 2
    virtual int Slot3();                                             // slot 3
    // VTABLE slot 4 — pop one received packet.
    virtual int GetPacket(void* buf, int* buflen);                    // slot 4

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
// +0x04. The no-throw specification is load-bearing under the locked `/GX`:
// without it the `new ModemRegistryEntryClass(i)` below emits the unwind frame
// that would free the block if the constructor threw, and retail has none.
struct ModemRegistryEntryClass
{
    char* ModemName;         // +0x0000
    char* ModemDeviceName;   // +0x0004
    char  unknown_08[0x14];  // +0x0008

    // FUNCTION: GAMEMD 0x5BB6E0 (decl; reloc) — the index constructor.
    ModemRegistryEntryClass(int index) throw();
    // FUNCTION: GAMEMD 0x5BBED0 (decl; reloc) — the destructor.
    ~ModemRegistryEntryClass() throw();

    char* GetModemName() const { return ModemName; }
    char* GetModemDeviceName() const { return ModemDeviceName; }
};
GG_STATIC_ASSERT(offsetof(ModemRegistryEntryClass, ModemName) == 0x0 &&
                 offsetof(ModemRegistryEntryClass, ModemDeviceName) == 0x4 &&
                 sizeof(ModemRegistryEntryClass) == 0x1C);

// The serial settings block the port detector is handed. Only the port
// address, the baud rate and the device-name buffer are read here.
struct SerialSettingsType
{
    int  Port;                // +0x0000
    int  unknown_04;          // +0x0004
    int  Baud;                // +0x0008
    char unknown_0C[0x24];    // +0x000C
    char ModemName[1];        // +0x0030
};
GG_STATIC_ASSERT(offsetof(SerialSettingsType, Port) == 0x0 &&
                 offsetof(SerialSettingsType, Baud) == 0x8 &&
                 offsetof(SerialSettingsType, ModemName) == 0x30);

// The Win32 serial-port wrapper the port detector and the shutdown path share
// through the global at 0xB72D20. Slot 0 is its deleting destructor; the port
// close is a direct call.
struct WinModemClass
{
    virtual ~WinModemClass();   // slot 0
    // VTABLE slot 1 — open the named device; -1 is the invalid handle.
    virtual int SerialPortOpen(char* device, int baud, int parity,
                               int wordLength, int stopBits);

    char unknown_04[0x2084];    // +0x0004 — `PUSH 0x2088` in 0x5F19E0.

    // FUNCTION: GAMEMD 0x774120 (decl; reloc) — the constructor.
    WinModemClass() throw();
    // FUNCTION: GAMEMD 0x774950 (decl; reloc) — WinModemClass::SerialPortClose.
    void SerialPortClose();
};
GG_STATIC_ASSERT(sizeof(WinModemClass) == 0x2088);

// GLOBAL: GAMEMD 0xB72D20 — the one shared WinModemClass instance.
extern WinModemClass* SerialPort;

// NullModemClass itself. The base's virtuals are not modelled here (no body in
// this translation unit constructs the object), so slot zero is carried as a
// plain vtable-pointer member and every offset below is the retail one.
struct NullModemClass
{
    void*  Vptr;                     // +0x0000
    char*  BuildBuf;                 // +0x0004
    int    MaxLen;                   // +0x0008
    char*  EchoBuf;                  // +0x000C
    int    EchoSize;                 // +0x0010
    int    EchoCount;                // +0x0014
    char   unknown_18[0x1C];         // +0x0018
    ModemRegistryEntryClass* ModemRegistry;   // +0x0034
    NullModemConnClass* Connection;  // +0x0038
    int    NumConnections;           // +0x003C
    int    PortHandle;               // +0x0040
    char   unknown_44[0xC];          // +0x0044
    char*  RXBuf;                    // +0x0050
    int    RXSize;                   // +0x0054
    int    RXCount;                  // +0x0058
    int    RetryDelta;               // +0x005C
    int    MaxRetries;               // +0x0060
    int    Timeout;                  // +0x0064
    int    SendOverflows;            // +0x0068

    // FUNCTION: GAMEMD 0x5F1950
    int NumConnectionsGet() const;
    // FUNCTION: GAMEMD 0x5F1960
    int DeleteConnection();
    // FUNCTION: GAMEMD 0x5F19C0
    int InitSendQueue();
    // FUNCTION: GAMEMD 0x5F19E0
    int DetectPort(SerialSettingsType* settings);
    // FUNCTION: GAMEMD 0x5F1B70
    void Shutdown();
    // FUNCTION: GAMEMD 0x5F1BC0
    void SetTiming(int retryDelta, int maxRetries, int timeout, int unused);
    // FUNCTION: GAMEMD 0x5F1BF0
    int SendMessage(void* buf, int buflen, int ackReq);
    // FUNCTION: GAMEMD 0x5F1C30
    int GetMessage(void* buf, int* buflen);
};
GG_STATIC_ASSERT(offsetof(NullModemClass, BuildBuf) == 0x04 &&
                 offsetof(NullModemClass, EchoBuf) == 0x0C &&
                 offsetof(NullModemClass, ModemRegistry) == 0x34 &&
                 offsetof(NullModemClass, Connection) == 0x38 &&
                 offsetof(NullModemClass, NumConnections) == 0x3C);
GG_STATIC_ASSERT(offsetof(NullModemClass, PortHandle) == 0x40 &&
                 offsetof(NullModemClass, RXBuf) == 0x50 &&
                 offsetof(NullModemClass, RXSize) == 0x54 &&
                 offsetof(NullModemClass, RXCount) == 0x58 &&
                 offsetof(NullModemClass, RetryDelta) == 0x5C &&
                 offsetof(NullModemClass, MaxRetries) == 0x60 &&
                 offsetof(NullModemClass, Timeout) == 0x64 &&
                 offsetof(NullModemClass, SendOverflows) == 0x68);

#endif  // GG_MATCH_NETWORK_NULL_MODEM_CLASS_METHODS_H
