// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x540C60 / 0x542450
//   (Ghidra disasm). Names cross-checked against YRpp IPXManagerClass.h
//   (consult-only, no LICENSE; every offset reconfirmed against the binary).
//
// Translation unit: IPXManagerClass timing/diagnostics.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x540C60   IPXManagerClass::SetTiming     (__thiscall)
//   FUNCTION: GAMEMD 0x542450   IPXManagerClass::ResponseTime  (__thiscall)
//   STRING:   GAMEMD 0x8283A8   "IPX Manager: RetryDelta = %d\n"
//   STRING:   GAMEMD 0x828398   "MaxAhead is %d\n"
//   GLOBAL:   GAMEMD 0xA8B550   MaxAhead (int)
//   LIBRARY:  GAMEMD 0x4068E0   Debug_Printf (variadic; release stub)
//   FUNCTION: GAMEMD 0x48BA80   CommQueueClass::Get_Response_Time

#include "ipx_manager_class.h"

// Release-build debug printf (0x4068E0 is a bare RET stub). cdecl/variadic so
// the two diagnostic calls push exactly { format, value }. Reloc-normalised.
extern "C" int __cdecl Debug_Printf(const char* fmt, ...);

// GLOBAL: GAMEMD 0xA8B550 — engine MaxAhead frame count (read for diagnostics).
extern int MaxAhead;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x540C60  (__thiscall)
//
// Record the retry/timeout timing triple on the manager, log it, optionally
// notify via the virtual Set_Timing hook, then push the values down onto every
// live connection and the multicast/global channel.
// ---------------------------------------------------------------------------
void IPXManagerClass::SetTiming(int retrydelta, int maxretries, int timeout, bool a5)
{
    this->RetryDelta = retrydelta;
    this->MaxRetries = maxretries;
    this->Timeout    = timeout;

    Debug_Printf("IPX Manager: RetryDelta = %d\n", retrydelta);
    Debug_Printf("MaxAhead is %d\n", MaxAhead);

    if (a5) {
        this->Set_Timing(this->RetryDelta, this->MaxRetries, this->Timeout);
    }

    for (int i = 0; i < this->NumConnections; ++i) {
        this->Connection[i]->RetryDelta = this->RetryDelta;
        this->Connection[i]->MaxRetries = this->MaxRetries;
        this->Connection[i]->Timeout    = this->Timeout;
    }

    if (this->MulticastConnection != 0) {
        this->MulticastConnection->RetryDelta = this->RetryDelta;
        this->MulticastConnection->MaxRetries = this->MaxRetries;
        this->MulticastConnection->Timeout    = this->Timeout;
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x542450  (__thiscall)
//
// Worst-case (maximum) average response time across every live connection and
// the multicast/global channel. Compared unsigned throughout.
// ---------------------------------------------------------------------------
int IPXManagerClass::ResponseTime()
{
    unsigned int maxv = 0;

    for (int i = 0; i < this->NumConnections; ++i) {
        unsigned int v = this->Connection[i]->Queue->Get_Response_Time();
        if (v > maxv) {
            maxv = v;
        }
    }

    unsigned int result;
    if (this->MulticastConnection == 0 ||
        (result = this->MulticastConnection->Queue->Get_Response_Time()) <= maxv) {
        result = maxv;
    }
    return (int)result;
}
