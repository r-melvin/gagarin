// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// The List<MixFileClass*> static data member at 0xABEFD8 (RTTI vtable 0x7EDF38, a one-slot
// table whose slot zero is 0x5B46E0). Retail's fused constructor + atexit initialiser is
// 0x5B3AC0; the exit stub at 0x5B3B10 tests bit 0 of the guard byte 0xABF008, then runs the
// inlined list teardown (GenericList table 0x7E1B04, drain, both sentinels).
#include "mix_file_list_00abefd8.h"
#include "../_layout/generic_list_inline.h"

class MixFileClass;

// SYNTHETIC: GAMEMD 0x005B46E0 -- List<MixFileClass*> scalar deleting destructor (vtable 0x7EDF38).
// SYNTHETIC: GAMEMD 0x005B3AC0 -- initialiser of DAT_00ABEFD8 (fused ctor + atexit)
// SYNTHETIC: GAMEMD 0x005B3B10 -- exit-time stub of DAT_00ABEFD8, guard byte 0x00ABF008 bit 0
List<MixFileClass*> MixFileListHolder_00ABEFD8::DAT_00ABEFD8;
