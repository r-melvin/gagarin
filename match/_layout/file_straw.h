// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-PE and RTTI. | behaviour-confirmed-name
// The retail RTTI record .?AVFileStraw@@ (TD 0x81BFC8) names Straw as its
// sole base at offset zero. Entry-origin bodies at 0x7BA530 and 0x7BA590
// access the File pointer at +0x0C and state byte at +0x10. These are the
// observed member offsets; no complete FileStraw size is asserted.
#ifndef GG_MATCH_LAYOUT_FILE_STRAW_H
#define GG_MATCH_LAYOUT_FILE_STRAW_H

#include <stddef.h>
#include "straw.h"
#include "../_rt/gg_static_assert.h"

// Constructor-established native input is a canonical file: RawFileClass
// at 0x5EE1BC -> FilePipe +0x0C at 0x47443E, and CCFileClass
// at 0x49BE70 -> FileStraw +0x0C at 0x47421B. Both RTTI chains
// contain FileClass at offset zero; original member spelling remains unknown.
class FileClass;

class FileStraw : public Straw
{
public:
    // SYNTHETIC: GAMEMD 0x477770 -- VC6 scalar deleting destructor emitted
    // for this virtual destructor; its 0x1E-byte wrapper was checked in the
    // pinned PE. It calls the ordinary destructor at 0x7BA590.
    virtual ~FileStraw();

    // Slot +0x08, inherited ABI signature from Straw. The original method
    // name and argument types are unknown; int parameters model two stack
    // words, the first used as a buffer pointer by the entry body.
    // FUNCTION: GAMEMD 0x7BA530
    virtual int FUN_006C98E0(int buffer, int size);

    FileClass* File; // +0x0C
    char HasOpened;          // +0x10
    char unknown_11[3];      // reserved layout-view bytes; extent not asserted
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(FileStraw, File) == 0x0C);
GG_STATIC_ASSERT(offsetof(FileStraw, HasOpened) == 0x10);

// VTABLE: GAMEMD 0x7E4D90 -- slot 0 scalar deleting destructor, slot 1
// inherited Straw::SetChainTo, slot 2 FileStraw::FUN_006C98E0. The isolated
// COFF table mapped 3/3 slots to these retail addresses. Project verification
// must resolve the generated deleting alias; weak defaults are conditional.

#endif // GG_MATCH_LAYOUT_FILE_STRAW_H
