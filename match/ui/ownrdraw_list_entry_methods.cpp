// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x624460 destroys the two wide strings at +0x08 and +0x04 of a list entry, in that
//   order, through the string destructor 0x7B6760; 0x6247D0 is its copy constructor.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

#define GG_LISTENTRY_006255F0_OUT_OF_LINE_DTOR
#include "listentry_006255f0.h"

// FUNCTION: GAMEMD 0x624460
ListEntry_006255F0::~ListEntry_006255F0()
{
}

// FUNCTION: GAMEMD 0x6247D0
ListEntry_006255F0::ListEntry_006255F0(const ListEntry_006255F0& other)
    : Id(other.Id), Name(other.Name), Text(other.Text),
      unknown_0C(other.unknown_0C), unknown_10(other.unknown_10), unknown_14(other.unknown_14)
{
}
