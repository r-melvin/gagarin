// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x74F730. YRpp consulted
//   for the class name only.

#include "../_layout/version_class.h"

// FUNCTION: GAMEMD 0x74F730
//
// Reset every cached field: the numeric version, both halves, the clip window,
// the four computed bits, and the first byte of each text buffer.
//
// The split between initializer list and body is load-bearing. Retail stores
// the dword/word fields and the bit clear first, the vtable next, and the two
// text bytes last with VersionText before VersionName. Putting everything in
// the body keeps our cl's stores in source order and sinks the vtable store to
// the end (35.7%); the initializer list for the scalars with the two byte
// stores in the body reproduces retail exactly. The four bit clears fold into
// one `AND EDX,0xFFFFFFF0` either way.
VersionClass::VersionClass()
    : Version(0), MajorVersion(0), MinorVersion(0), MinClipVer(0), MaxClipVer(0),
      VersionInit(0), MajorInit(0), MinorInit(0), TextInit(0)
{
    VersionText[0] = '\0';
    VersionName[0] = '\0';
}

// SYNTHETIC: GAMEMD 0x4E8270
// VersionClass scalar deleting destructor, emitted with the vtable 0x7EA57C by the constructor above.
