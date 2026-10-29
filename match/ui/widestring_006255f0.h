// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH_UI_WIDESTRING_006255F0_H_H
#define GG_MATCH_UI_WIDESTRING_006255F0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class WideString_006255F0
{
public:
    unsigned short* Buffer;   // +0x00

    // FUNCTION: GAMEMD 0x7B66C0 (decl; reloc)
    WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B6760 (decl; reloc)
    ~WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B6720 (decl; reloc)
    WideString_006255F0(const WideString_006255F0& other);
    // FUNCTION: GAMEMD 0x7B68E0 (decl; reloc)
    WideString_006255F0& operator=(const WideString_006255F0& other);
};
GG_STATIC_ASSERT(sizeof(WideString_006255F0) == 4);

#endif
