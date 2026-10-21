// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; retail gamemd.exe v1.001 SHA-256
// 1cdd1180e49024fbda8ad568caac2e86e856063ff67ab38f62b7d2c7bb84298c.
// RTTI TypeDescriptor 0x825B90 / COL 0x8037A8 identifies Base64Pipe with
// Pipe at PMD mdisp=0. Entry 0x42DF40 tests Mode +0x0C and reads/clears
// Pending +0x10; it forms addresses +0x14 and +0x18 for codec calls. This
// view asserts these offsets only; it makes no complete-size, destructor or
// vtable-match claim.
#ifndef GG_MATCH_NETWORK_BASE64_PIPE_FLUSH_METHODS_H
#define GG_MATCH_NETWORK_BASE64_PIPE_FLUSH_METHODS_H

#include "../_layout/pipe.h"

class Base64Pipe : public Pipe
{
public:
    int Mode;                 // +0x0C, loaded at 0x42DF4D.
    int Pending;              // +0x10, loaded and cleared at 0x42DF46/7D.
    unsigned char At_14[4];   // +0x14, address formed at 0x42DF54/6A.
    unsigned char At_18[4];   // +0x18, address formed at 0x42DF5A/64.

    // Retail slot-1 override; original method name is unknown.
    // FUNCTION: GAMEMD 0x42DF40
    virtual int FUN_00631D30();

    // Retail slot-4 override declaration needed to preserve the typed class
    // vtable view; the separate body at 0x42DDB0 is capped and excluded here.
    // FUNCTION: GAMEMD 0x42DDB0 -- declaration/call-site identity only.
    virtual int FUN_00631D10(int source, int length);
};

GG_STATIC_ASSERT(offsetof(Base64Pipe, Mode) == 0x0C);
GG_STATIC_ASSERT(offsetof(Base64Pipe, Pending) == 0x10);
GG_STATIC_ASSERT(offsetof(Base64Pipe, At_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Base64Pipe, At_18) == 0x18);

// VTABLE: GAMEMD 0x7EB774 -- RTTI identity/address point only. Its full slot
// check is not claimed here (the deleting entry and Put body are unresolved).

#endif // GG_MATCH_NETWORK_BASE64_PIPE_FLUSH_METHODS_H
