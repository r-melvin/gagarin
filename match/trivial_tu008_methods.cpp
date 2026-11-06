// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Five CCINIClass objects at 0x887180, 0x887208, 0x887128, 0x887058 and 0x8870C0 (vtable
//   0x7E1AF4 is CCINIClass by RTTI), each with a dynamic initialiser and an atexit cleanup
//   that tail-calls the INIClass destructor at 0x5256F0. The initialiser expands the head
//   sentinel in place and calls the tail sentinel constructor (0x40E320) and Link (0x40E340).
//
//   Ordered ascending by retail address.

#include "_layout/generic_list_ctor_first_inline.h"
#include "ccini_class_methods.h"

// SYNTHETIC: GAMEMD 0x40DFB0 -- initialiser: constructs DAT_00887180, registers 0x40E050.
// SYNTHETIC: GAMEMD 0x40E050 -- atexit cleanup: destroys DAT_00887180.
// GLOBAL: GAMEMD 0x887180
CCINIClass DAT_00887180((INIClass::SectionIndexClass::InlineIndex()));

// SYNTHETIC: GAMEMD 0x40E060 -- initialiser: constructs DAT_00887208, registers 0x40E100.
// SYNTHETIC: GAMEMD 0x40E100 -- atexit cleanup: destroys DAT_00887208.
// GLOBAL: GAMEMD 0x887208
CCINIClass DAT_00887208((INIClass::SectionIndexClass::InlineIndex()));

// SYNTHETIC: GAMEMD 0x40E110 -- initialiser: constructs DAT_00887128, registers 0x40E1B0.
// SYNTHETIC: GAMEMD 0x40E1B0 -- atexit cleanup: destroys DAT_00887128.
// GLOBAL: GAMEMD 0x887128
CCINIClass DAT_00887128((INIClass::SectionIndexClass::InlineIndex()));

// SYNTHETIC: GAMEMD 0x40E1C0 -- initialiser: constructs DAT_00887058, registers 0x40E260.
// SYNTHETIC: GAMEMD 0x40E260 -- atexit cleanup: destroys DAT_00887058.
// GLOBAL: GAMEMD 0x887058
CCINIClass DAT_00887058((INIClass::SectionIndexClass::InlineIndex()));

// SYNTHETIC: GAMEMD 0x40E270 -- initialiser: constructs DAT_008870C0, registers 0x40E310.
// SYNTHETIC: GAMEMD 0x40E310 -- atexit cleanup: destroys DAT_008870C0.
// GLOBAL: GAMEMD 0x8870C0
CCINIClass DAT_008870C0((INIClass::SectionIndexClass::InlineIndex()));
