// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x526960. Name from
//   YRpp (consult-only).

#include "ccini_class_key_count_methods.h"

// FUNCTION: GAMEMD 0x526960
//
// Number of keys in a section. The section name is CRC'd, the section index
// is probed (IsPresent, then operator[] -- both inlined, so the probe runs
// twice), and the found section's key count is returned; a null name, an
// unknown section or an empty slot all answer zero.
int INIClass::GetKeyCount(const char* section)
{
    if (section != 0) {
        CRC_00526960 engine;
        int crc = engine(section, strlen(section));

        Index_00526960* index = reinterpret_cast<Index_00526960*>(&SectionIndex);
        if (index->IsPresent(crc)) {
            INIClass::INISection* sec = (*index)[crc];
            if (sec != 0)
                return sec->EntryIndex.IndexCount;
        }
    }

    return 0;
}
