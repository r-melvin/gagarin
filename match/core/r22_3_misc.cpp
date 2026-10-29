// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below.
//
// Address index: 0x5D9060 0x661640

#include "../network/transport/udp_interface_class.h"
#include "../_layout/session_class.h"


struct Obj_005D9060 {
    int f00, f04, f08, f0c;
    int Counter;
    short FUN_005D9060(int step);
};

// FUNCTION: GAMEMD 0x5D9060
// Advance the id counter by step (default 1), wrapping at 0xFFFF to 0x800, and in network mode
// ask the global object to accept the id, retrying up to 255 times.
short Obj_005D9060::FUN_005D9060(int step)
{
    short id;
    if (step == 0) {
        step = 1;
    }
    int tries = 0xff;
    do {
        Counter += step;
        id = (short)Counter;
        if (Counter > 0xffff) {
            Counter = 0x800;
        }
        if (Interface_00887628 && Session_00A8B238.GameMode == 4) {
            if (!static_cast<UDPInterfaceClass*>(Interface_00887628)->OpenSpareSocket(id)) {
                continue;
            }
            static_cast<UDPInterfaceClass*>(Interface_00887628)->CloseSpareSocket(id);
        }
        return id;
    } while (tries-- != 0);
    return id;
}

// FUNCTION: GAMEMD 0x661640
// Expand a zero-run-length packed block: a 16-bit total size (inclusive), then bytes where a
// zero is followed by a run length of zeroes. Returns the number of bytes written.
int __stdcall FUN_00661640(const unsigned char* packed, unsigned char* out)
{
    int remaining = *(const unsigned short*)packed - 2;
    const unsigned char* src = packed + 2;
    unsigned char* dst = out;
    while (remaining > 0) {
        unsigned char value = *src++;
        remaining--;
        if (value == 0) {
            int run = *src++;
            remaining--;
            if (run > 0) {
                memset(dst, 0, run);
                dst += run;
            }
        } else {
            *dst++ = value;
        }
    }
    return dst - out;
}
