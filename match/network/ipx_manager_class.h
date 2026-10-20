// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x540C60 / 0x542450),
//   cross-checked against YRpp IPXManagerClass.h (consult-only, no LICENSE;
//   every offset reconfirmed numerically below).
//
// IPXManagerClass — the legacy IPX/UDP network manager. Holds the per-game
// connection table (Connection[7] + a multicast/global channel) and the
// retry-delta / max-retries / timeout timing parameters that it fans out to
// every live connection.
#ifndef GG_MATCH_NETWORK_IPX_MANAGER_CLASS_H
#define GG_MATCH_NETWORK_IPX_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// The comm-buffer/queue object hanging off ConnectionClass+0x4. ResponseTime
// reads its average response time via a leaf accessor at 0x48BA80
// (MOV EAX,[ECX+0x1c] / RET): an unsigned-returning __thiscall getter.
// ---------------------------------------------------------------------------
class CommQueueClass
{
public:
    // FUNCTION: GAMEMD 0x48BA80  CommQueueClass::Get_Response_Time (__thiscall)
    unsigned int Get_Response_Time();   // returns *(unsigned*)(this+0x1c)
};

// ---------------------------------------------------------------------------
// ConnectionClass — one peer connection (and the multicast/global channel use
// the same touched layout). SetTiming writes RetryDelta/MaxRetries/Timeout at
// +0x28/+0x2c/+0x30; ResponseTime reads the queue pointer at +0x4.
// ---------------------------------------------------------------------------
class ConnectionClass
{
public:
    char            _pad00[0x04];          // +0x00 vtable
    CommQueueClass* Queue;                 // +0x04
    char            _pad08[0x28 - 0x08];   // +0x08 .. +0x27
    int             RetryDelta;            // +0x28
    int             MaxRetries;            // +0x2C
    int             Timeout;               // +0x30
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ConnectionClass, Queue)      == 0x04);
GG_STATIC_ASSERT(offsetof(ConnectionClass, RetryDelta) == 0x28);
GG_STATIC_ASSERT(offsetof(ConnectionClass, MaxRetries) == 0x2C);
GG_STATIC_ASSERT(offsetof(ConnectionClass, Timeout)    == 0x30);
#endif

// ---------------------------------------------------------------------------
// IPXManagerClass. The class is polymorphic: its vtable pointer sits at +0x00.
// SetTiming dispatches a virtual at vtable slot 14 (byte offset 0x38) — the
// `Set_Timing` notify hook. Only the slots up to and including that one need to
// exist for the indexed call to land at [vtbl+0x38]; slots 1..13 are modelled
// as opaque placeholders (their identity does not affect this TU's bytes).
// ---------------------------------------------------------------------------
class IPXManagerClass
{
public:
    virtual ~IPXManagerClass();                       // slot 0  (+0x00)
    virtual void _vslot01();                          // slot 1  (+0x04)
    virtual void _vslot02();                          // slot 2  (+0x08)
    virtual void _vslot03();                          // slot 3  (+0x0C)
    virtual void _vslot04();                          // slot 4  (+0x10)
    virtual void _vslot05();                          // slot 5  (+0x14)
    virtual void _vslot06();                          // slot 6  (+0x18)
    virtual void _vslot07();                          // slot 7  (+0x1C)
    virtual void _vslot08();                          // slot 8  (+0x20)
    virtual void _vslot09();                          // slot 9  (+0x24)
    virtual void _vslot10();                          // slot 10 (+0x28)
    virtual void _vslot11();                          // slot 11 (+0x2C)
    virtual void _vslot12();                          // slot 12 (+0x30)
    virtual void _vslot13();                          // slot 13 (+0x34)
    virtual void Set_Timing(int retrydelta, int maxretries, int timeout); // slot 14 (+0x38)

    // FUNCTION: GAMEMD 0x540C60  IPXManagerClass::SetTiming     (__thiscall)
    void SetTiming(int retrydelta, int maxretries, int timeout, bool a5);
    // FUNCTION: GAMEMD 0x542450  IPXManagerClass::ResponseTime  (__thiscall)
    int  ResponseTime();

    // ---- layout (vtable pointer occupies +0x00..+0x03) -------------------
    char             _pad04[0x28 - 0x04];  // +0x04 .. +0x27
    ConnectionClass* Connection[7];        // +0x28 .. +0x43
    int              NumConnections;       // +0x44
    char             _pad48[0x50 - 0x48];  // +0x48 .. +0x4F  (incl. global channels)
    ConnectionClass* MulticastConnection;  // +0x50
    char             _pad54[0x58 - 0x54];  // +0x54  (CurConnection)
    int              RetryDelta;           // +0x58
    int              MaxRetries;           // +0x5C
    int              Timeout;              // +0x60
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(IPXManagerClass, Connection)          == 0x28);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, NumConnections)      == 0x44);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, MulticastConnection) == 0x50);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, RetryDelta)          == 0x58);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, MaxRetries)          == 0x5C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, Timeout)             == 0x60);
#endif

#endif  // GG_MATCH_NETWORK_IPX_MANAGER_CLASS_H
