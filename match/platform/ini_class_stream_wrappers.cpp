// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry-origin retail evidence at 0x525A10 and 0x526420 (stack FileStraw
//   vtable 0x7E4D90 / FilePipe vtable 0x7E4DA0, destructors 0x7BA590/0x7BA420).

#include "../_layout/ini_class.h"
#include "../_layout/file_straw.h"
#include "../_layout/file_pipe.h"

// SYNTHETIC: GAMEMD 0x477770 -- FileStraw scalar deleting destructor, emitted
// here beside the stack FileStraw below; it calls the out-of-line destructor
// at 0x7BA590 and operator delete.
// SYNTHETIC: GAMEMD 0x477790 -- FilePipe scalar deleting destructor, emitted
// here beside the stack FilePipe below; it calls the out-of-line destructor
// at 0x7BA420 and operator delete.

// FUNCTION: GAMEMD 0x525A10
// Reset the two list links, then load the INI through a stack FileStraw.
int INIClass::FUN_00525A10(FileClass* file, unsigned long options)
{
    unknown_04 = 0;
    unknown_08 = 0;
    FileStraw straw(file);
    return LoadStraw(&straw, options);
}

// FUNCTION: GAMEMD 0x526420
// Reset the two list links, then save the INI through a stack FilePipe.
int INIClass::FUN_00526420(FileClass* file)
{
    unknown_04 = 0;
    unknown_08 = 0;
    FilePipe pipe(file);
    return SavePipe(&pipe);
}
