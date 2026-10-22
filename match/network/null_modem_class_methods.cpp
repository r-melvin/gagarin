// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001; the class name
//   comes from its own runtime type information (see the header); methods
//   without a binary-attested name are FUN_XXXXXXXX. Bodies ordered ascending
//   by retail address.
#include <string.h>
#include "null_modem_class_methods.h"

// GLOBAL: GAMEMD 0xB72D20 — the shared WinModemClass the serial layer owns.
// STRING: GAMEMD 0x832340 — "COM1"
// STRING: GAMEMD 0x832345 — "COM2"
// STRING: GAMEMD 0x83234A — "COM3"
// STRING: GAMEMD 0x83234F — "COM4"

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
