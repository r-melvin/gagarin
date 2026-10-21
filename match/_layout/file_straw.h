// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-PE and RTTI.
// The retail RTTI record .?AVFileStraw@@ (TD 0x81BFC8) names Straw as its
// sole base at offset zero. Entry-origin bodies at 0x7BA530 and 0x7BA590
// access the File pointer at +0x0C and state byte at +0x10. These are the
// observed member offsets; no complete FileStraw size is asserted.
#ifndef GG_MATCH_LAYOUT_FILE_STRAW_H
#define GG_MATCH_LAYOUT_FILE_STRAW_H

#include <stddef.h>
#include "straw.h"
#include "../_rt/gg_static_assert.h"

// Slot-only ABI view for the indirect calls observed in FileStraw's method
// and destructor. These names/types describe call shapes and offsets only;
// they do not claim the pointee's original C++ class or method names.
class FileStrawFileView
{
public:
    virtual void FUN_slot00() = 0;
    virtual void FUN_slot04() = 0;
    virtual void FUN_slot08() = 0;
    virtual void FUN_slot0C() = 0;
    virtual void FUN_slot10() = 0;
    virtual bool FUN_slot14(int arg) = 0;
    virtual bool FUN_slot18() = 0;
    virtual int FUN_slot1C(int arg) = 0;
    virtual void FUN_slot20() = 0;
    virtual int FUN_slot24(int first, int second) = 0;
    virtual int FUN_slot28(int arg) = 0;
    virtual void FUN_slot2C() = 0;
    virtual void FUN_slot30() = 0;
    virtual void FUN_slot34() = 0;
};

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

    FileStrawFileView* File; // +0x0C
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
