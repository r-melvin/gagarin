// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing ConnStat declaration extracted from connman_class.cpp; extra
// stall counters are DWORD reads in6516F0 ev_e88e51e43a5aecdccd75ad04b582065dc9c93b66956cfd2febd45a8477798040.
#ifndef GG_MATCH_LAYOUT_CONN_STAT_H
#define GG_MATCH_LAYOUT_CONN_STAT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ipx_address_class.h"

// One row of the per-connection statistics table at 0xA8B574 (stride 0x68).
struct ConnStat
{
    char            Name[0x40];     // +0x00 name-output view; capacity modeled
    int             PeakMs;         // +0x40
    int             unknown_44;     // +0x44
    int             unknown_48;     // +0x48
    int             unknown_4C;     // +0x4C
    int             AvgMs;          // +0x50
    int             unknown_54; //6519E3 frame-sync stalls
    int             unknown_58; //6519F2 command-count stalls
    IPXAddressClass Address;        // +0x5C
};
GG_STATIC_ASSERT(offsetof(ConnStat, Name) == 0x00);
GG_STATIC_ASSERT(offsetof(ConnStat, PeakMs)  == 0x40);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(ConnStat, AvgMs)   == 0x50);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(ConnStat, Address) == 0x5C);
GG_STATIC_ASSERT(sizeof(ConnStat)            == 0x68);

// GLOBAL: GAMEMD 0xA8B574 -- per-connection statistics rows.
extern ConnStat ConnStats_00A8B574[];
#endif
