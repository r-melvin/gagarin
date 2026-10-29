// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The List<MixFileClass*> global at 0xABEFD8; defined in w2_mix_file_list_global_r15.cpp.
#ifndef GG_MATCH_CORE_MIX_FILE_LIST_00ABEFD8_H
#define GG_MATCH_CORE_MIX_FILE_LIST_00ABEFD8_H
#include "../_layout/generic_list.h"

class MixFileClass;

struct MixFileListValue_00ABEFD8 : List<MixFileClass*> {
    ~MixFileListValue_00ABEFD8() { DestroyList(); }
};

struct MixFileListHolder_00ABEFD8 {
    // GLOBAL: GAMEMD 0xABEFD8
    static MixFileListValue_00ABEFD8 DAT_00ABEFD8;
};

#endif
