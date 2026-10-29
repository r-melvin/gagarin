// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH_UI_LISTENTRY_006255F0_H_H
#define GG_MATCH_UI_LISTENTRY_006255F0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "widestring_006255f0.h"

struct ListEntry_006255F0
{
    int Id;                       // +0x00
    WideString_006255F0 Name;     // +0x04
    WideString_006255F0 Text;     // +0x08
    int unknown_0C;               // +0x0C
    int unknown_10;               // +0x10
    int unknown_14;               // +0x14

    ListEntry_006255F0() { Id = 0; unknown_0C = -1; unknown_10 = 0; unknown_14 = -1; }
    // FUNCTION: GAMEMD 0x6247D0 (decl; reloc)
    ListEntry_006255F0(const ListEntry_006255F0& other);
    // FUNCTION: GAMEMD 0x624460
    // Retail destroys an entry by expanding the two string destructors inline
    // (EntryRecord's copy constructor 0x6255F0), and also holds one standalone
    // copy at 0x624460. Users get the implicit inline destructor; only the TU
    // that holds the standalone copy defines GG_LISTENTRY_006255F0_OUT_OF_LINE_DTOR
    // to declare it (the object layout is the same in both).
#ifdef GG_LISTENTRY_006255F0_OUT_OF_LINE_DTOR
    ~ListEntry_006255F0();
#endif
};
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, Name) == 0x04);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, Text) == 0x08);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(ListEntry_006255F0) == 0x18);

#endif
