// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-pinned-PE and RTTI. TD 0x81BFE8 and COL | behaviour-confirmed-name
// 0x7FCD80 identify FilePipe with Pipe at offset zero. Entry-origin bodies
// 0x7BA420/0x7BA450/0x7BA480 establish the fields and slot-call ABI below.
#ifndef GG_MATCH_LAYOUT_FILE_PIPE_H
#define GG_MATCH_LAYOUT_FILE_PIPE_H
#include <stddef.h>
#include "pipe.h"
#include "../_rt/gg_static_assert.h"

// Constructor-established native input is a canonical file: RawFileClass
// at 0x5EE1BC -> FilePipe +0x0C at 0x47443E, and CCFileClass
// at 0x49BE70 -> FileStraw +0x0C at 0x47421B. Both RTTI chains
// contain FileClass at offset zero; original member spelling remains unknown.
class FileClass;

class FilePipe : public Pipe
{
public:
    // SYNTHETIC: GAMEMD 0x477790 -- compiler-generated scalar deleting
    // destructor; its body calls the ordinary destructor at 0x7BA420.
    virtual ~FilePipe();

    // Inline construction as built on the stack at 0x526420.
    FilePipe(FileClass* file) : File(file), HasOpened(0) {}

    // Slot +0x08; returns the inherited slot +0x04 result after optional
    // file cleanup.
    // FUNCTION: GAMEMD 0x7BA450
    virtual int FUN_00477740();

    // Slot +0x10; names and argument types remain an ABI view.
    // FUNCTION: GAMEMD 0x7BA480
    virtual int FUN_00631D10(int first, int second);

    FileClass* File; // +0x0C
    char HasOpened;          // +0x10
    char unknown_11[3]; // modeled prefix padding; full object size unproven
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(FilePipe, File) == 0x0C);
GG_STATIC_ASSERT(offsetof(FilePipe, HasOpened) == 0x10);
// VTABLE: GAMEMD 0x7E4DA0 -- five slots; generated deleting alias is conditional.
#endif
