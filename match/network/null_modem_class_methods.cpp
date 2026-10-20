// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bytes matched against the user's retail gamemd.exe v1.001; the class name
//   comes from its own runtime type information (see the header) and the
//   method names from EA's GPLv3 RA1 NULLMGR.CPP, used as a naming reference
//   only. Bodies ordered ascending by retail address.
#include <string.h>
#include "null_modem_class_methods.h"

// GLOBAL: GAMEMD 0xB72D20 — the shared WinModemClass the serial layer owns.
// STRING: GAMEMD 0x832340 — "COM1"
// STRING: GAMEMD 0x832345 — "COM2"
// STRING: GAMEMD 0x83234A — "COM3"
// STRING: GAMEMD 0x83234F — "COM4"

// How many connection objects are live (zero when the link is down).
// FUNCTION: GAMEMD 0x5F1950
int NullModemClass::NumConnectionsGet() const
{
    return NumConnections;
}

// Tear the link down: destroy the connection object, release the three packet
// buffers and forget the connection count.
// FUNCTION: GAMEMD 0x5F1960
int NullModemClass::DeleteConnection()
{
    if (Connection != 0) {
        delete Connection;
        Connection = 0;
    }
    if (RXBuf != 0) {
        delete [] RXBuf;
        RXBuf = 0;
    }
    if (BuildBuf != 0) {
        delete [] BuildBuf;
        BuildBuf = 0;
    }
    if (EchoBuf != 0) {
        delete [] EchoBuf;
        EchoBuf = 0;
    }
    NumConnections = 0;
    return 1;
}

// Empty the connection's outgoing packet queue.
// FUNCTION: GAMEMD 0x5F19C0
int NullModemClass::InitSendQueue()
{
    if (Connection != 0) {
        Connection->Queue->InitSendQueue();
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
int NullModemClass::DetectPort(SerialSettingsType* settings)
{
    static char com_ids[4][5] = { "COM1", "COM2", "COM3", "COM4" };
    int i;

    if (!SerialPort) {
        SerialPort = new WinModemClass;
    } else {
        SerialPort->SerialPortClose();
    }

    int baud = settings->Baud;
    char* device;

    switch (settings->Port) {
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
            device = settings->ModemName;

            if (ModemRegistry) {
                delete ModemRegistry;
                ModemRegistry = 0;
            }
            for (i = 0; i < 10; i++) {
                ModemRegistry = new ModemRegistryEntryClass(i);
                if (ModemRegistry->GetModemName()) {
                    if (!strcmp(device, ModemRegistry->GetModemName())) {
                        device = ModemRegistry->GetModemDeviceName();
                        break;
                    }
                }
                delete ModemRegistry;
                ModemRegistry = 0;
            }
            break;

        default:
            return 1;
    }

    if (SerialPort->SerialPortOpen(device, baud, 0, 8, 1) == -1) {
        return 1;
    }

    SerialPort->SerialPortClose();
    return 0;
}

// Close the serial port, drop the port wrapper and tear the link down.
// FUNCTION: GAMEMD 0x5F1B70
void NullModemClass::Shutdown()
{
    if (PortHandle != -1 && SerialPort != 0) {
        SerialPort->SerialPortClose();
        delete SerialPort;
        SerialPort = 0;
        PortHandle = -1;
        DeleteConnection();
    }
}

// Publish new retry timing, both here and on the connection object.
// FUNCTION: GAMEMD 0x5F1BC0
void NullModemClass::SetTiming(int retryDelta, int maxRetries, int timeout,
                               int)
{
    RetryDelta = retryDelta;
    MaxRetries = maxRetries;
    Timeout = timeout;
    Connection->RetryDelta = retryDelta;
    Connection->MaxRetries = MaxRetries;
    Connection->Timeout = Timeout;
}

// Queue one outgoing message; a full send queue is counted, not retried.
// FUNCTION: GAMEMD 0x5F1BF0
int NullModemClass::SendMessage(void* buf, int buflen, int ackReq)
{
    if (NumConnections == 0) {
        return 0;
    }

    int rc = Connection->SendPacket(buf, buflen, ackReq, 0);
    if (!rc) {
        SendOverflows++;
    }
    return rc;
}

// Pop one received message, if the link is up.
// FUNCTION: GAMEMD 0x5F1C30
int NullModemClass::GetMessage(void* buf, int* buflen)
{
    if (NumConnections == 0) {
        return 0;
    }
    return Connection->GetPacket(buf, buflen);
}
