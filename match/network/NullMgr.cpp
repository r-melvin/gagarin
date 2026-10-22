// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit NullMgr.CPP. The name is the source-file string at 0x832730
//   in retail gamemd.exe v1.001, passed by the assert at 0x5f1fdb inside this object's
//   code range (0x5f13d0-0x5f36ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Bytes matched against the user's retail gamemd.exe v1.001; the class name
//   comes from its own runtime type information (see the header); methods
//   without a binary-attested name are FUN_XXXXXXXX. Bodies ordered ascending
//   by retail address.
//
//   NullModemClass's port open / connection setup and its packet pump.
//   Reuses the canonical header read-only. Members and callees the header does
//   not declare are TU-local views below.

#include "../core/empty_function_family_methods.h"

#include <string.h>
#include "null_modem_class_methods.h"

// GLOBAL: GAMEMD 0xB72D20 — the shared WinModemClass the serial layer owns.
// STRING: GAMEMD 0x832340 — "COM1"
// STRING: GAMEMD 0x832345 — "COM2"
// STRING: GAMEMD 0x83234A — "COM3"
// STRING: GAMEMD 0x83234F — "COM4"

#include <string.h>
#include "null_modem_class_methods.h"

// Debug trace (cdecl, one string argument).
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// The connection constructor (0x5EF100, `PUSH 0x54` allocation) and its port
// attach (0x5EF170), both direct thiscalls.
struct ConnBuild_005F16E0
{
    char unknown_00[0x1C];
    int  unknown_1C;            // +0x001C — read at 0x5F176B
    char unknown_20[0x34];

    ConnBuild_005F16E0(int a, int b, int maxLen, short d) throw();  // 0x5EF100 (decl)
    void Attach(int handle);                                       // 0x5EF170 (decl)
};
GG_STATIC_ASSERT(offsetof(ConnBuild_005F16E0, unknown_1C) == 0x1C
              && sizeof(ConnBuild_005F16E0) == 0x54);   // `PUSH 0x54` at 0x5F1723

// The port handle query on the shared serial object (0x7754C0, thiscall).
struct ModemQuery_005F16E0
{
    int GetHandle();                                               // 0x7754C0 (decl)
};

// TU-local stand-in adding the members this file defines.
struct NullModemInitView : public NullModemClass
{
    int Init(int port, int unused, char* modemName, int baud, char parity,
             int wordLength, int stopBits);
    bool FUN_005f3170();
};

// The modem command slots of the shared serial object reached by
// FUN_005f3170: slot 4 (`CALL [EAX+0x10]`), slot 5 (`CALL [EDX+0x14]`) and
// slot 7 (`CALL [EAX+0x1C]`), plus the direct raw write at 0x774C70.
struct ModemCommandTable_005F16E0
{
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void vf_4(int on);                                          // slot 4
    virtual int  vf_5(int count, char* buf, int bufLen, int wait);    // slot 5
    virtual void Slot6();
    // Sends cmd and waits for a reply; 2 means the expected answer arrived.
    virtual int  Command(const char* cmd, int term, char* buf, int bufLen,
                         int timeout, int a, int b);                       // slot 7

    void Write(const char* data, int length);                              // 0x774C70 (decl)
};

// The dial settings read at 0x5F322E (+0x2C), 0x5F324F (+0x30) and 0x5F32AF
// (+0x28), all inside the header's unknown_18 run.
struct NullModemDialView
{
    char unknown_00[0x28];
    int  unknown_28;        // +0x0028
    int  unknown_2C;           // +0x002C
    char unknown_30;           // +0x0030
};
GG_STATIC_ASSERT(offsetof(NullModemDialView, unknown_28) == 0x28
              && offsetof(NullModemDialView, unknown_2C) == 0x2C
              && offsetof(NullModemDialView, unknown_30) == 0x30);

// Short pause helper (fastcall, one argument).
void FUN_004a50a0(int ticks);

// The pump-enable flags, used here as a whole dword (bit 0 cleared while the
// modem is driven directly); same declaration as core/unsorted_callback_methods.h.
// GLOBAL: GAMEMD 0xA8DAB8
extern unsigned int DAT_00A8DAB8;

// The three settings words the connection constructor takes (+0x44, +0x48,
// +0x4C), read at 0x5F1731..0x5F173D.
struct NullModemSettingsView
{
    char  unknown_00[0x44];
    int   Setting44;           // +0x0044
    int   Setting48;           // +0x0048
    short Setting4C;           // +0x004C
};
GG_STATIC_ASSERT(offsetof(NullModemSettingsView, Setting44) == 0x44
              && offsetof(NullModemSettingsView, Setting48) == 0x48
              && offsetof(NullModemSettingsView, Setting4C) == 0x4C);

#include "trivial_tu164_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EEFC8
extern const double DAT_007EEFC8;
// GLOBAL: GAMEMD 0xAC12E0
extern double DAT_00AC12E0;
// GLOBAL: GAMEMD 0xAC1320
extern double DAT_00AC1320;
// GLOBAL: GAMEMD 0xAC1328
extern int DAT_00AC1328;
// GLOBAL: GAMEMD 0xAC132C
extern int DAT_00AC132C;
// GLOBAL: GAMEMD 0xAC1330
extern int DAT_00AC1330;
// GLOBAL: GAMEMD 0xAC1338
extern double DAT_00AC1338;

// FUNCTION: GAMEMD 0x5F1400
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005F1400()
{
    DAT_00AC1338 = DAT_00AC12E0 / DAT_007EEFC8;
}

// FUNCTION: GAMEMD 0x5F1420
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005F1420()
{
    DAT_00AC1320 = DAT_007E1718 / DAT_00AC1338;
}

// FUNCTION: GAMEMD 0x5F15A0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_005F15A0()
{
    DAT_00AC1330 = 0;
    DAT_00AC1328 = 0x80;
    DAT_00AC132C = 0x80;
}

// FUNCTION: GAMEMD 0x005f16e0
// Builds the connection and its buffers on first use, opens the serial device
// selected by port (I/O address, or 1 for a registry modem matched by name)
// and attaches the connection to it. Returns 1 on success, 0 when the open
// fails.
int NullModemInitView::Init(int port, int unused, char* modemName, int baud,
                            char parity, int wordLength, int stopBits)
{
    static char com_ids[4][5] = { "COM1", "COM2", "COM3", "COM4" };
    char* device;
    int i;

    FUN_004068E0("NullModemClass::Init\n");

    if (WinModem_00B72D20 != 0) {
        unknown_40 = ((ModemQuery_005F16E0*)WinModem_00B72D20)->GetHandle();
    } else {
        unknown_40 = -1;
    }

    if (Connection == 0) {
        FUN_004068E0("Creating connection class\n");
        NullModemSettingsView* s = (NullModemSettingsView*)this;
        Connection = (NullModemConnClass*)new ConnBuild_005F16E0(
            s->Setting44, s->Setting48, unknown_08, s->Setting4C);
        Connection->RetryDelta = RetryDelta;
        Connection->MaxRetries = MaxRetries;
        Connection->Timeout = Timeout;
        unknown_54 = (((ConnBuild_005F16E0*)Connection)->unknown_1C + 11) * s->Setting48;
        unknown_50 = new char[unknown_54];
        unknown_04 = new char[unknown_08];
        unknown_0C = new char[unknown_10];
    } else {
        FUN_004068E0("Connection already exists\n");
    }

    unknown_58 = 0;
    unknown_14 = 0;

    if (WinModem_00B72D20 == 0) {
        WinModem_00B72D20 = new WinModemClass;
    }

    switch (port) {
        case 0x3f8:
            device = com_ids[0];
            break;

        case 0x2f8:
            device = com_ids[1];
            break;

        case 0x3e8:
            device = com_ids[2];
            break;

        case 0x2e8:
            device = com_ids[3];
            break;

        case 1:
            device = modemName;

            if (unknown_34) {
                delete unknown_34;
                unknown_34 = 0;
            }
            for (i = 0; i < 10; i++) {
                unknown_34 = new ModemEntry_005BB6E0(i);
                if (unknown_34->GetModemName()) {
                    if (!strcmp(modemName, unknown_34->GetModemName())) {
                        device = unknown_34->Inline_005F16E0();
                        break;
                    }
                }
                delete unknown_34;
                unknown_34 = 0;
            }
            break;

        default:
            device = 0;
            break;
    }

    unknown_40 = WinModem_00B72D20->vf_1(device, baud, parity, wordLength, stopBits);
    if (unknown_40 == -1) {
        return 0;
    }

    FUN_004068E0("Ready to initialise connection\n");
    ((ConnBuild_005F16E0*)Connection)->Attach(unknown_40);
    NumConnections = 1;
    return 1;
}

// How many connection objects are live (zero when the link is down).
// FUNCTION: GAMEMD 0x5F1950
int NullModemClass::FUN_005F1950() const
{
    return NumConnections;
}

// Tear the link down: destroy the connection object, release the three packet
// buffers and forget the connection count.
// FUNCTION: GAMEMD 0x5F1960
int NullModemClass::FUN_005F1960()
{
    if (Connection != 0) {
        delete Connection;
        Connection = 0;
    }
    if (unknown_50 != 0) {
        delete [] unknown_50;
        unknown_50 = 0;
    }
    if (unknown_04 != 0) {
        delete [] unknown_04;
        unknown_04 = 0;
    }
    if (unknown_0C != 0) {
        delete [] unknown_0C;
        unknown_0C = 0;
    }
    NumConnections = 0;
    return 1;
}

// Empty the connection's outgoing packet queue.
// FUNCTION: GAMEMD 0x5F19C0
int NullModemClass::FUN_005F19C0()
{
    if (Connection != 0) {
        Connection->Queue->FUN_0048B390();
    }
    return 1;
}

// Check that the requested serial device exists and can be opened. The port
// address selects one of the four COM device names; the special value 1 means
// the settings carry a device name instead, which is matched against the Win32
// modem registry so the registry's own device name can be used when it is
// known. Returns 1 when the port is not usable, 0 when it is.
// FUNCTION: GAMEMD 0x5F19E0
// STRING: GAMEMD 0x832340
// STRING: GAMEMD 0x832345
// STRING: GAMEMD 0x83234A
// STRING: GAMEMD 0x83234F
int NullModemClass::FUN_005F19E0(SerialSettings_005F19E0* settings)
{
    static char comNames[4][5] = { "COM1", "COM2", "COM3", "COM4" };
    int i;

    if (!WinModem_00B72D20) {
        WinModem_00B72D20 = new WinModemClass;
    } else {
        WinModem_00B72D20->FUN_00774950();
    }

    int baud = settings->Baud;
    char* device;

    switch (settings->Port) {
        case 0x3f8:
            device = comNames[0];
            break;

        case 0x2f8:
            device = comNames[1];
            break;

        case 0x3e8:
            device = comNames[2];
            break;

        case 0x2e8:
            device = comNames[3];
            break;

        case 1:
            device = settings->ModemName;

            if (unknown_34) {
                delete unknown_34;
                unknown_34 = 0;
            }
            for (i = 0; i < 10; i++) {
                unknown_34 = new ModemEntry_005BB6E0(i);
                if (unknown_34->GetModemName()) {
                    if (!strcmp(device, unknown_34->GetModemName())) {
                        device = unknown_34->Inline_005F16E0();
                        break;
                    }
                }
                delete unknown_34;
                unknown_34 = 0;
            }
            break;

        default:
            return 1;
    }

    if (WinModem_00B72D20->vf_1(device, baud, 0, 8, 1) == -1) {
        return 1;
    }

    WinModem_00B72D20->FUN_00774950();
    return 0;
}

// Close the serial port, drop the port wrapper and tear the link down.
// FUNCTION: GAMEMD 0x5F1B70
void NullModemClass::Shutdown()
{
    if (unknown_40 != -1 && WinModem_00B72D20 != 0) {
        WinModem_00B72D20->FUN_00774950();
        delete WinModem_00B72D20;
        WinModem_00B72D20 = 0;
        unknown_40 = -1;
        FUN_005F1960();
    }
}

// Publish new retry timing, both here and on the connection object.
// FUNCTION: GAMEMD 0x5F1BC0
void NullModemClass::SetTiming(int retryDelay, int retryLimit, int timeout,
                               int)
{
    RetryDelta = retryDelay;
    MaxRetries = retryLimit;
    Timeout = timeout;
    Connection->RetryDelta = retryDelay;
    Connection->MaxRetries = MaxRetries;
    Connection->Timeout = Timeout;
}

// Queue one outgoing message; a full send queue is counted, not retried.
// FUNCTION: GAMEMD 0x5F1BF0
int NullModemClass::FUN_005F1BF0(void* buf, int buflen, int ackReq)
{
    if (NumConnections == 0) {
        return 0;
    }

    int rc = Connection->vf_2(buf, buflen, ackReq, 0);
    if (!rc) {
        SendOverflows++;
    }
    return rc;
}

// Pop one received message, if the link is up.
// FUNCTION: GAMEMD 0x5F1C30
int NullModemClass::FUN_005F1C30(void* buf, int* buflen)
{
    if (NumConnections == 0) {
        return 0;
    }
    return Connection->vf_4(buf, buflen);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005f3170
// Hangs up the modem: probes it with "AT" (twice, toggling the line between),
// drains pending replies, sends the escape sequence, waits for "OK", then
// "ATH" and "ATZ". Returns true when the modem answered the probe or the
// reset. Pump-enable bit 0 is cleared for the duration.
bool NullModemInitView::FUN_005f3170()
{
    char escape[4];
    char reply[81];

    if (unknown_40 == -1 || WinModem_00B72D20 == 0) {
        return false;
    }

    DAT_00A8DAB8 &= ~1;

    ModemCommandTable_005F16E0* modem = (ModemCommandTable_005F16E0*)WinModem_00B72D20;
    if (modem->Command("AT", 13, reply, 81, 90, 1, -1) == 2) {
        DAT_00A8DAB8 |= 1;
        return true;
    }

    ((ModemCommandTable_005F16E0*)WinModem_00B72D20)->vf_4(0);
    FUN_004a50a0(53);
    ((ModemCommandTable_005F16E0*)WinModem_00B72D20)->vf_4(1);

    if (((ModemCommandTable_005F16E0*)WinModem_00B72D20)->Command("AT", 13, reply, 81, 90, 1, -1) == 2) {
        DAT_00A8DAB8 |= 1;
        return true;
    }

    NullModemDialView* dial = (NullModemDialView*)this;
    int n = dial->unknown_2C;
    while (n > 0) {
        n = ((ModemCommandTable_005F16E0*)WinModem_00B72D20)->vf_5(n, reply, 81, -1);
    }

    escape[0] = dial->unknown_30;
    escape[1] = dial->unknown_30;
    escape[2] = dial->unknown_30;
    escape[3] = '\0';
    ((ModemCommandTable_005F16E0*)WinModem_00B72D20)->Write(escape, 3);

    n = dial->unknown_2C;
    while (n > 0) {
        n = ((ModemCommandTable_005F16E0*)WinModem_00B72D20)->vf_5(n, reply, 81, -1);
        if (strncmp(reply, "OK", 2) == 0) {
            break;
        }
    }

    if (((ModemCommandTable_005F16E0*)WinModem_00B72D20)->Command("ATH", 13, reply, 81, dial->unknown_28, 1, -1) == 2) {
        if (((ModemCommandTable_005F16E0*)WinModem_00B72D20)->Command("ATZ", 13, reply, 81, 60, 1, -1) != 2) {
            DAT_00A8DAB8 |= 1;
            return false;
        }
        DAT_00A8DAB8 |= 1;
        return true;
    }

    DAT_00A8DAB8 |= 1;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005F3340
void FUN_005F3340()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F3440
// Returns zero; pops its stack arguments.
int __stdcall FUN_005F3440(int a1)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F3520
// Returns zero; pops its stack arguments. Vtable slot 5 of NullModemClass (RTTI).
int Obj_005F3520::FUN_005F3520(int a1) const
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F3530
// Returns zero; pops its stack arguments. Vtable slot 6 of NullModemClass (RTTI).
int Obj_005F3530::FUN_005F3530(int a1) const
{
    return 0;
}
