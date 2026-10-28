// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, IAT slots, string addresses and the vtable at 0x7F7488 read off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI. The class name
//   and the Read_Serial_Chars / Enter_Failsafe_Mode names come from the
//   binary's own log strings (0x849934, 0x849A58, 0x8498B0).
//
// The Win32 serial-port wrapper. Layout recovered from the bodies below:
// error counters at +0x04..+0x18, the last queue depths at +0x1C/+0x20, the
// receive ring (0x2000 bytes, masked 0x1FFF) at +0x24 with its head at +0x58,
// the read/write OVERLAPPED blocks at +0x28/+0x3C, the pending flags at
// +0x50/+0x51, the port handle at +0x5C, the dial type at +0x60 (vtable slot
// 2 stores it), an abort callback at +0x68, the read chunk at +0x6C and the
// saved DCB at +0x206C (seven dwords copied by 0x774410).
#include <stddef.h>
#include <string.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// GLOBAL: GAMEMD 0xA8ED80 -- gate the response reader polls each pass.
extern bool DAT_00A8ED80;

// STRING: GAMEMD 0x81FD14 -- "OK"
extern const char STR_0081FD14[];
// STRING: GAMEMD 0x82BFAC -- "0"
extern const char STR_0082BFAC[];
// STRING: GAMEMD 0x832678 -- "AT"
extern const char STR_00832678[];
// STRING: GAMEMD 0x8327A0 -- "\r"
extern const char STR_008327A0[];
// STRING: GAMEMD 0x83ED58 -- "P"
extern const char STR_0083ED58[];
// STRING: GAMEMD 0x83ED5C -- "T"
extern const char STR_0083ED5C[];
// STRING: GAMEMD 0x8497A4 -- "Closing serial port\n"
extern const char STR_008497A4[];
// STRING: GAMEMD 0x8497DC -- "SetCommTimeouts returned error code %s.\n"
extern const char STR_008497DC[];
// STRING: GAMEMD 0x849808 -- "GetCommState returned error code %s.\n"
extern const char STR_00849808[];
// STRING: GAMEMD 0x849830 -- "SetCommState returned error %s.\n"
extern const char STR_00849830[];
// STRING: GAMEMD 0x849854 -- "Port opened OK\n"
extern const char STR_00849854[];
// STRING: GAMEMD 0x849864 -- "Failed to get valid port handle. Error: %s\n"
extern const char STR_00849864[];
// STRING: GAMEMD 0x849890 -- "Opening serial port %s\n"
extern const char STR_00849890[];
// STRING: GAMEMD 0x8498B0 -- "Enter_Failsafe_Mode - EscapeCommFunction failed to set state..."
extern const char STR_008498B0[];
// STRING: GAMEMD 0x849910 -- "GetCommState returned error %s.\n"
extern const char STR_00849910[];
// STRING: GAMEMD 0x849934 -- "WinModemClass - Entering failsafe mode\n"
extern const char STR_00849934[];
// STRING: GAMEMD 0x849A28 -- "Reading from port handle failed with error %s\n"
extern const char STR_00849A28[];
// STRING: GAMEMD 0x849A58 -- "GetOverlappedResult in WinModemClass::Read_Serial_Chars retu..."
extern const char STR_00849A58[];
// STRING: GAMEMD 0x849AA4 -- "Writing to port handle failed with error %s\n"
extern const char STR_00849AA4[];
// STRING: GAMEMD 0x849AD4 -- "Send to modem: %s..."
extern const char STR_00849AD4[];
// STRING: GAMEMD 0x849AE8 -- "Appending carriag..."
extern const char STR_00849AE8[];
// STRING: GAMEMD 0x849B04 -- "Appending dial st..."
extern const char STR_00849B04[];
// STRING: GAMEMD 0x849B1C -- "Dial type is puls..."
extern const char STR_00849B1C[];
// STRING: GAMEMD 0x849B30 -- "Dial type is tone..."
extern const char STR_00849B30[];
// STRING: GAMEMD 0x849B44 -- "ATD"
extern const char STR_00849B44[];
// STRING: GAMEMD 0x849B48 -- "Creating dial str..."
extern const char STR_00849B48[];
// STRING: GAMEMD 0x849B60 -- "ERROR"
extern const char STR_00849B60[];
// STRING: GAMEMD 0x849B68 .. 0x849DB4 -- the comm status / error report lines.
extern const char STR_00849B68[];
extern const char STR_00849B90[];
extern const char STR_00849BB4[];
extern const char STR_00849BE0[];
extern const char STR_00849C10[];
extern const char STR_00849C3C[];
extern const char STR_00849C68[];
extern const char STR_00849C94[];
extern const char STR_00849CCC[];
extern const char STR_00849CF8[];
extern const char STR_00849D34[];
extern const char STR_00849D68[];
extern const char STR_00849D90[];
extern const char STR_00849DB4[];

// The tick clock: an empty object whose __thiscall GetTime ignores `this`.
struct Clock_00774B30
{
    int GetTime();   // GAMEMD 0x6C8C40 (decl; reloc)
};

// A countdown on the tick clock: start tick, clock object, delay.
struct Countdown_00774B30
{
    int              Started;   // +0x00
    Clock_00774B30 Clock;     // +0x04
    int              Delay;     // +0x08

    Countdown_00774B30(int delay = 0)
    {
        Started = Clock.GetTime();
        Delay = delay;
    }
    int Time()
    {
        int remain = Delay;
        if (Started != -1) {
            int elapsed = Clock.GetTime() - Started;
            if (elapsed >= remain) {
                return 0;
            }
            remain -= elapsed;
        }
        return remain;
    }
};
GG_STATIC_ASSERT(offsetof(Countdown_00774B30, Delay) == 0x08);

typedef int (*AbortFn_unknown_68)();

class WinModemClass
{
public:
    virtual ~WinModemClass();                                         // 0x775610
    virtual HANDLE FUN_00774410(char* device, int baud, int parity,
                                    int wordLength, int stopBits);    // 0x774410
    virtual void FUN_007748A0(int type);                             // 0x7748A0
    virtual unsigned Get_Modem_Status();                              // 0x7748B0
    virtual void Set_Serial_DTR(bool state);                          // 0x774900
    virtual int Get_Modem_Result(int timeout, char* buffer, int length,
                                 int perCharTimeout);                    // 0x774CD0
    virtual void Dial_Modem(char* number);                            // 0x774F50
    virtual int FUN_00775110(char* command, char terminator,
                                      char* reply, int replyBytes,
                                      int timeout, int retries,
                                      int perCharTimeout);               // 0x775110
    virtual void Slot8();                                             // 0x7754A0
    virtual void Slot9();                                             // 0x7754B0

    bool Enter_Failsafe_Mode();
    bool Read_Serial_Chars();
    int  FUN_00774B30(char* buffer, int length);                        // 0x774B30
    void FUN_00774BC0();                                     // 0x774BC0
    void FUN_007754D0(DWORD errors, COMSTAT status);

    int          unknown_4;      // +0x0004
    int          unknown_8;           // +0x0008
    int          unknown_C;      // +0x000C
    int          unknown_10;   // +0x0010
    int          unknown_14;       // +0x0014
    int          unknown_18;       // +0x0018
    DWORD        unknown_1C;            // +0x001C
    DWORD        unknown_20;           // +0x0020
    char*        unknown_24;           // +0x0024
    OVERLAPPED   unknown_28;        // +0x0028
    OVERLAPPED   unknown_3C;       // +0x003C
    bool         unknown_50;        // +0x0050
    bool         unknown_51;       // +0x0051
    char         unknown_52[6];      // +0x0052
    int          unknown_58;             // +0x0058
    HANDLE       PortHandle;         // +0x005C
    int          unknown_60;           // +0x0060
    int          unknown_64;         // +0x0064
    AbortFn_unknown_68 unknown_68; // +0x0068
    char         unknown_6C[0x2000];  // +0x006C
    DCB          unknown_206C;          // +0x206C
};
GG_STATIC_ASSERT(offsetof(WinModemClass, unknown_4) == 0x04 &&
                 offsetof(WinModemClass, unknown_18) == 0x18 &&
                 offsetof(WinModemClass, unknown_1C) == 0x1C &&
                 offsetof(WinModemClass, unknown_24) == 0x24 &&
                 offsetof(WinModemClass, unknown_28) == 0x28 &&
                 offsetof(WinModemClass, unknown_3C) == 0x3C &&
                 offsetof(WinModemClass, unknown_50) == 0x50 &&
                 offsetof(WinModemClass, unknown_51) == 0x51 &&
                 offsetof(WinModemClass, unknown_58) == 0x58 &&
                 offsetof(WinModemClass, PortHandle) == 0x5C &&
                 offsetof(WinModemClass, unknown_60) == 0x60 &&
                 offsetof(WinModemClass, unknown_68) == 0x68 &&
                 offsetof(WinModemClass, unknown_6C) == 0x6C &&
                 offsetof(WinModemClass, unknown_206C) == 0x206C);
// `PUSH 0x2088` before the constructor call in 0x5F19E0.
GG_STATIC_ASSERT(sizeof(WinModemClass) == 0x2088);

// LIBRARY: GAMEMD 0x7C8D20 -- CRT string comparison.
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

// FUNCTION: GAMEMD 0x7741C0
//
// Walk the subkeys of `key`, open the one named `name` for reading and return
// it (0 when none matches). The parent is closed afterwards on request.
HKEY FUN_007741C0(HKEY key, const char* name, bool closeParent)
{
    char className[0x400];
    DWORD classLength;
    DWORD subKeys;
    DWORD maxSubKeyLength;
    DWORD maxClassLength;
    DWORD values;
    DWORD maxValueName;
    DWORD maxValueData;
    DWORD securityLength;
    FILETIME written;
    HKEY result;

    classLength = sizeof(className);
    if (RegQueryInfoKeyA(key, className, &classLength, NULL, &subKeys,
                         &maxSubKeyLength, &maxClassLength, &values,
                         &maxValueName, &maxValueData, &securityLength,
                         &written) != ERROR_SUCCESS) {
        return 0;
    }

    DWORD nameSize = maxSubKeyLength + 16;
    char* keyName = new char[nameSize];
    char* keyClass = new char[maxClassLength + 1];

    for (DWORD i = 0; i < subKeys; i++) {
        keyName[0] = '\0';
        maxSubKeyLength = nameSize;
        RegEnumKeyExA(key, i, keyName, &maxSubKeyLength, NULL, keyClass,
                      &maxClassLength, &written);
        if (FUN_007C8D20(name, keyName) == 0 &&
            RegOpenKeyExA(key, keyName, 0, KEY_READ, &result) == ERROR_SUCCESS) {
            if (closeParent) {
                RegCloseKey(key);
            }
            delete keyName;
            delete keyClass;
            return result;
        }
    }

    if (closeParent) {
        RegCloseKey(key);
    }
    delete keyName;
    delete keyClass;
    return 0;
}

// FUNCTION: GAMEMD 0x774410
//
// Open `\\.\<device>` for overlapped I/O, size and purge its queues, make the
// two overlapped events, program the line (baud, parity, word length, stop
// bits, CTS and RTS handshaking, DTR on) and the timeouts, raise DTR and
// report any pending line errors. Returns the handle or INVALID_HANDLE_VALUE.
HANDLE WinModemClass::FUN_00774410(char* device, int baud, int parity,
                                       int wordLength, int stopBits)
{
    char path[266] = "\\\\.\\";
    DCB state;
    COMMTIMEOUTS timeouts;
    DWORD errors;
    COMSTAT status;

    strcat(path, device);

    if (PortHandle != INVALID_HANDLE_VALUE) {
        FUN_004068E0(STR_008497A4);
        CloseHandle(PortHandle);
        PortHandle = INVALID_HANDLE_VALUE;
    }

    FUN_004068E0(STR_00849890, path);
    HANDLE handle = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if (handle == INVALID_HANDLE_VALUE) {
        FUN_004068E0(STR_00849864, 0);
        return INVALID_HANDLE_VALUE;
    }

    FUN_004068E0(STR_00849854);
    PortHandle = handle;
    SetupComm(handle, 0x2000, 0x2000);
    PurgeComm(PortHandle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

    unknown_28.Internal = 0;
    unknown_28.InternalHigh = 0;
    unknown_28.Offset = 0;
    unknown_28.OffsetHigh = 0;
    unknown_28.hEvent = CreateEventA(NULL, TRUE, TRUE, NULL);
    unknown_3C.Internal = 0;
    unknown_3C.InternalHigh = 0;
    unknown_3C.Offset = 0;
    unknown_3C.OffsetHigh = 0;
    unknown_3C.hEvent = CreateEventA(NULL, TRUE, TRUE, NULL);

    if (GetCommState(handle, &state)) {
        state.BaudRate = baud;
        state.Parity = (BYTE)parity;
        state.ByteSize = (BYTE)wordLength;
        state.StopBits = (BYTE)(stopBits - 1);
        state.fBinary = TRUE;
        state.fParity = FALSE;
        state.fOutxCtsFlow = TRUE;
        state.fOutxDsrFlow = FALSE;
        state.fDtrControl = DTR_CONTROL_ENABLE;
        state.fOutX = FALSE;
        state.fInX = FALSE;
        state.fErrorChar = FALSE;
        state.fRtsControl = RTS_CONTROL_HANDSHAKE;
        state.fAbortOnError = FALSE;
        if (!SetCommState(handle, &state)) {
            FUN_004068E0(STR_00849830, 0);
        } else {
            unknown_206C = state;
        }
    } else {
        FUN_004068E0(STR_00849808, 0);
    }

    timeouts.ReadIntervalTimeout = 1000;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.ReadTotalTimeoutConstant = 3000;
    timeouts.WriteTotalTimeoutMultiplier = 500;
    timeouts.WriteTotalTimeoutConstant = 1000;
    if (!SetCommTimeouts(handle, &timeouts)) {
        FUN_004068E0(STR_008497DC, 0);
    }

    Set_Serial_DTR(true);

    if (ClearCommError(PortHandle, &errors, &status)) {
        unknown_1C = status.cbInQue;
        unknown_20 = status.cbOutQue;
        if (errors) {
            FUN_007754D0(errors, status);
        }
    }
    return handle;
}

// FUNCTION: GAMEMD 0x774670
//
// Drop to a plain 9600 8-N-1 line without hardware handshaking, raise RTS
// and report any pending line errors. False only when the line could not be
// reprogrammed.
bool WinModemClass::Enter_Failsafe_Mode()
{
    DCB state;
    DWORD mask;
    DWORD errors;
    COMSTAT status;

    FUN_004068E0(STR_00849934);
    PurgeComm(PortHandle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
    ResetEvent(unknown_28.hEvent);
    ResetEvent(unknown_3C.hEvent);
    unknown_50 = false;
    unknown_51 = false;

    if (GetCommState(PortHandle, &state)) {
        state.BaudRate = 9600;
        state.Parity = NOPARITY;
        state.ByteSize = 8;
        state.StopBits = ONESTOPBIT;
        state.fBinary = TRUE;
        state.fParity = FALSE;
        state.fOutxCtsFlow = FALSE;
        state.fOutxDsrFlow = FALSE;
        state.fDtrControl = DTR_CONTROL_ENABLE;
        state.fOutX = FALSE;
        state.fInX = FALSE;
        state.fErrorChar = FALSE;
        state.fRtsControl = RTS_CONTROL_ENABLE;
        state.fAbortOnError = FALSE;
        if (!SetCommState(PortHandle, &state)) {
            FUN_004068E0(STR_00849830, 0);
            return false;
        }
    } else {
        FUN_004068E0(STR_00849910, 0);
    }

    GetCommMask(PortHandle, &mask);
    Set_Serial_DTR(true);
    Get_Modem_Status();
    if (!EscapeCommFunction(PortHandle, SETRTS)) {
        FUN_004068E0(STR_008498B0, GetLastError(), 0);
    }

    if (ClearCommError(PortHandle, &errors, &status)) {
        unknown_1C = status.cbInQue;
        unknown_20 = status.cbOutQue;
        if (errors) {
            FUN_007754D0(errors, status);
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x7748A0
// Stores the value in the field at +0x60.
void WinModemClass::FUN_007748A0(int type)
{
    unknown_60 = type;
}

// FUNCTION: GAMEMD 0x774980
//
// Finish any pending overlapped read, then read whatever the driver queue
// holds into the receive ring until a read goes pending or fails. True when
// at least one byte arrived.
bool WinModemClass::Read_Serial_Chars()
{
    DWORD got;
    DWORD total = 0;
    DWORD errors;
    COMSTAT status;

    if (unknown_50) {
        got = 0;
        if (GetOverlappedResult(PortHandle, &unknown_28, &got, FALSE)) {
            unknown_50 = false;
            if (got) {
                for (DWORD i = 0; i < got; i++) {
                    unknown_24[unknown_58] = unknown_6C[i];
                    unknown_58 = (unknown_58 + 1) & 0x1FFF;
                }
                total = got;
            }
        } else {
            if (GetLastError() == ERROR_IO_INCOMPLETE) {
                return false;
            }
            FUN_004068E0(STR_00849A58, 0);
        }
    }

    ResetEvent(unknown_28.hEvent);

    int wanted = 1;
    if (ClearCommError(PortHandle, &errors, &status)) {
        unknown_1C = status.cbInQue;
        unknown_20 = status.cbOutQue;
        if (errors) {
            FUN_007754D0(errors, status);
        }
        wanted = status.cbInQue;
        if (wanted >= 0x2000) {
            wanted = 0x2000;
        } else if (wanted == 0) {
            wanted = 1;
        }
    }

    bool ok;
    do {
        got = 0;
        ok = ReadFile(PortHandle, unknown_6C, wanted, &got, &unknown_28) != 0;
        if (ok) {
            if (got) {
                for (DWORD i = 0; i < got; i++) {
                    unknown_24[unknown_58] = unknown_6C[i];
                    unknown_58 = (unknown_58 + 1) & 0x1FFF;
                }
                total += got;
            }
            wanted = 1;
        } else {
            if (GetLastError() != ERROR_IO_PENDING) {
                FUN_004068E0(STR_00849A28, 0);
            } else {
                unknown_50 = true;
                return total != 0;
            }
        }
    } while (ok == true);

    return total != 0;
}

// FUNCTION: GAMEMD 0x774CD0
//
// Collect a modem reply into `buffer` until the overall timeout runs out, the
// buffer fills, or a carriage return arrives and the per-character timeout
// lapses. A leading echo of the "AT" command and leading line breaks are
// stripped and collection restarts; the last carriage return is cut off.
// Returns the time left (or the abort callback's non-zero result).
int WinModemClass::Get_Modem_Result(int timeout, char* buffer, int length,
                                    int perCharTimeout)
{
    Countdown_00774B30 total;
    int got = 0;
    Countdown_00774B30 quiet;
    char* p;

    memset(buffer, 0, length);
    quiet = Countdown_00774B30(perCharTimeout);

    do {
        total = Countdown_00774B30(timeout);
        for (;;) {
            if (unknown_68) {
                int result = unknown_68();
                if (result) {
                    return result;
                }
            }
            if (!DAT_00A8ED80) {
                return 0;
            }
            int n = FUN_00774B30(buffer + got,
                               length - got >= 0 ? length - got : 0);
            if (n) {
                got += n;
                quiet = Countdown_00774B30(perCharTimeout);
            }
            if (!total.Time() || got >= length) {
                break;
            }
            if (!strchr(buffer, '\r')) {
                continue;
            }
            if (perCharTimeout == -1 || !quiet.Time()) {
                break;
            }
        }

        buffer[length - 1] = '\0';
        p = strstr(buffer, STR_00832678);
        if (p && buffer[0] == 'A' && buffer[1] == 'T' && strchr(buffer, '\r')) {
            p = strchr(buffer, '\r');
        }
        if (!p && (buffer[0] == '\r' || buffer[0] == '\n')) {
            p = strchr(buffer, '\r');
            char* lf = strchr(buffer, '\n');
            if (!p || (lf && lf < p)) {
                p = strchr(buffer, '\n');
            }
        }
        if (!p) {
            break;
        }
        while (*p == '\r' || *p == '\n') {
            p++;
        }
        if (p != buffer) {
            int skip = p - buffer;
            memmove(buffer, p, length - skip);
            got -= skip;
        }
    } while (p);

    if (strrchr(buffer, '\r')) {
        *strrchr(buffer, '\r') = '\0';
    }
    return total.Time();
}

// FUNCTION: GAMEMD 0x774F50
//
// Build "ATD" + tone/pulse prefix + number + CR and send it to the modem.
void WinModemClass::Dial_Modem(char* number)
{
    char dial[0x50];

    FUN_004068E0(STR_00849B48);
    strcpy(dial, STR_00849B44);
    if (unknown_60 == 0) {
        strcat(dial, STR_0083ED5C);
        FUN_004068E0(STR_00849B30);
    } else {
        FUN_004068E0(STR_00849B1C);
        strcat(dial, STR_0083ED58);
    }
    FUN_004068E0(STR_00849B04);
    strcat(dial, number);
    FUN_004068E0(STR_00849AE8);
    strcat(dial, STR_008327A0);
    FUN_004068E0(STR_00849AD4, dial);

    int len = strlen(dial);
    FUN_00774BC0();
    // PARTIAL 92.1%: retail hands WriteFile the dead `number` parameter slot
    // (`LEA EDX,[ESP+0x64]`) as the byte-count pointer; this uses a local.
    DWORD written;
    if (!WriteFile(PortHandle, dial, len, &written, &unknown_3C)) {
        if (GetLastError() == ERROR_IO_PENDING) {
            unknown_51 = true;
            FUN_00774BC0();
            return;
        }
        FUN_004068E0(STR_00849AA4, 0);
    }
    FUN_00774BC0();
}

// FUNCTION: GAMEMD 0x775110
//
// Send `command` + `terminator`, wait for a reply and classify it: 3 for "0",
// 2 for "OK" or a three-digit result code (copied to `reply`), 1 for
// "ERROR"; any other reply is copied out and a bare CR is sent before the
// next retry. 0 once the retries or the timeout run out.
int WinModemClass::FUN_00775110(char* command, char terminator,
                                         char* reply, int replyBytes,
                                         int timeout, int retries,
                                         int perCharTimeout)
{
    char tail[2];
    DWORD written;
    DWORD crWritten;
    char response[0x50];
    char line[0x50];
    char flush[0x50];

    tail[0] = terminator;
    tail[1] = '\0';
    strcpy(line, command);
    strcat(line, tail);

    FUN_00774B30(flush, sizeof(flush));
    Sleep(100);
    FUN_00774B30(flush, sizeof(flush));

    for (int i = 0; i < retries; i++) {
        Countdown_00774B30 wait(timeout);
        int len = strlen(line);
        FUN_00774BC0();
        if (!WriteFile(PortHandle, line, len, &written, &unknown_3C)) {
            if (GetLastError() == ERROR_IO_PENDING) {
                unknown_51 = true;
            } else {
                FUN_004068E0(STR_00849AA4, 0);
            }
        }
        FUN_00774BC0();

        if (wait.Time() <= 0) {
            return 0;
        }
        int left = wait.Time() < 1 ? 1 : wait.Time();
        memset(response, 0, sizeof(response));
        Get_Modem_Result(left, response, sizeof(response), perCharTimeout);

        if (strcmp(response, STR_0082BFAC) == 0) {
            return 3;
        }
        if (strstr(response, STR_0081FD14)) {
            return 2;
        }
        if (strstr(response, STR_00849B60)) {
            return 1;
        }
        if (strlen(response) == 3 &&
            response[0] >= '0' && response[0] <= '9' &&
            response[1] >= '0' && response[1] <= '9' &&
            response[2] >= '0' && response[2] <= '9') {
            strncpy(reply, response, replyBytes < 0x50 ? replyBytes : 0x50);
            return 2;
        }

        strncpy(reply, response, replyBytes < 0x50 ? replyBytes : 0x50);
        Sleep(100);
        FUN_00774BC0();
        if (!WriteFile(PortHandle, STR_008327A0, 1, &crWritten, &unknown_3C)) {
            if (GetLastError() == ERROR_IO_PENDING) {
                unknown_51 = true;
            } else {
                FUN_004068E0(STR_00849AA4, 0);
            }
        }
        FUN_00774BC0();
        Sleep(100);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7754D0
//
// Log each error bit of a ClearCommError result (counting the ones that have
// a counter) and each hold reason of its status block.
void WinModemClass::FUN_007754D0(DWORD errors, COMSTAT status)
{
    if (errors) {
        if (errors & CE_FRAME) {
            FUN_004068E0(STR_00849DB4);
            unknown_4++;
        }
        if (errors & CE_BREAK) {
            FUN_004068E0(STR_00849D90);
        }
        if (errors & CE_IOE) {
            FUN_004068E0(STR_00849D68);
            unknown_8++;
        }
        if (errors & CE_OVERRUN) {
            FUN_004068E0(STR_00849D34);
            unknown_C++;
        }
        if (errors & CE_RXOVER) {
            FUN_004068E0(STR_00849CF8);
            unknown_10++;
        }
        if (errors & CE_RXPARITY) {
            FUN_004068E0(STR_00849CCC);
            unknown_14++;
        }
        if (errors & CE_TXFULL) {
            FUN_004068E0(STR_00849C94);
            unknown_18++;
        }
    }
    if (status.fCtsHold) {
        FUN_004068E0(STR_00849C68);
    }
    if (status.fDsrHold) {
        FUN_004068E0(STR_00849C3C);
    }
    if (status.fRlsdHold) {
        FUN_004068E0(STR_00849C10);
    }
    if (status.fXoffHold) {
        FUN_004068E0(STR_00849BE0);
    }
    if (status.fXoffSent) {
        FUN_004068E0(STR_00849BB4);
    }
    if (status.fEof) {
        FUN_004068E0(STR_00849B90);
    }
    if (status.fTxim) {
        FUN_004068E0(STR_00849B68);
    }
}
