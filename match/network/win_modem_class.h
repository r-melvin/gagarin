// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
//   RTTI: vtable 0x7F7488 -> .?AVWinModemClass@@, ten slots
//   [0x775610, 0x774410, 0x7748A0, 0x7748B0, 0x774900, 0x774CD0, 0x774F50,
//    0x775110, 0x7754A0, 0x7754B0]. sizeof 0x2088 from `PUSH 0x2088; CALL
//   0x7C8E17` at 0x5F19F7 followed by the constructor call 0x774120 on the
//   result (0x5F1A0A). The constructor stores -1 at +0x5C (port handle) and
//   zero at +0x64/+0x68; 0x7748B0 passes +0x5C to GetCommModemStatus.
//   Slot 1 opens the named device (its use in 0x5F19E0 compares the result
//   with -1). Slot names other than the recovered ones are placeholders.
#ifndef GG_MATCH_NETWORK_WIN_MODEM_CLASS_H
#define GG_MATCH_NETWORK_WIN_MODEM_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The Win32 serial-port wrapper the port detector and the shutdown path share
// through the global at 0xB72D20. Declared `struct` because the existing
// consumers' decorated names already spell it that way.
class WinModemClass
{
public:
    virtual ~WinModemClass();   // slot 0
    // VTABLE slot 1 — open the named device; -1 is the invalid handle.
    virtual int vf_1(char* device, int baud, int parity,
                               int a4, int a5);
    virtual void FUN_slot08();
    // FUNCTION: GAMEMD 0x7748B0
    virtual int Get_Modem_Status();
    virtual void FUN_slot10();
    virtual void FUN_slot14();
    virtual void FUN_slot18();
    // Slot 7 (+0x1C): stdcall, seven arguments (name, id, out buffer, length, timeout, flag, -1).
    virtual int FUN_slot1C(const char* name, int a2, char* out, int length, int timeout, int flag, int a7);
    // FUNCTION: GAMEMD 0x7754A0
    virtual void Set_Value_64(int value);
    // FUNCTION: GAMEMD 0x7754B0
    virtual void Set_Value_68(int value);

    // FUNCTION: GAMEMD 0x774120 (decl; reloc) — the constructor.
    WinModemClass() throw();
    // FUNCTION: GAMEMD 0x774950 (decl; reloc) — WinModemClass::FUN_00774950.
    void FUN_00774950();

    char  unknown_04[0x58];   // +0x04
    void* PortHandle;         // +0x5C
    int   unknown_60;         // +0x60
    int   unknown_64;         // +0x64
    int   unknown_68;         // +0x68
    char  unknown_6C[0x201C]; // +0x6C
};
GG_STATIC_ASSERT(offsetof(WinModemClass, PortHandle) == 0x5C);
GG_STATIC_ASSERT(offsetof(WinModemClass, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(WinModemClass, unknown_68) == 0x68);
GG_STATIC_ASSERT(sizeof(WinModemClass) == 0x2088);
// VTABLE: GAMEMD 0x7F7488

#endif // GG_MATCH_NETWORK_WIN_MODEM_CLASS_H
