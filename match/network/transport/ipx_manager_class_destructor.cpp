// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
#include "connman_class.h"
// FUNCTION: GAMEMD 0x53F5B0 (decl; reloc)
// This caller supplies no arguments and discards the result; name and return
// type remain unestablished. This is a shared-address call view only.
void __cdecl FUN_0053F5B0();
// FUNCTION: GAMEMD 0x5409F0 -- complete body through both return paths; 0x8D bytes.
IPXManagerClass::~IPXManagerClass()
{
    if (Active) {
        FUN_0053F5B0();
        Active = 0;
    }
    if (GlobalChannel) {
        delete GlobalChannel;
        GlobalChannel = 0;
    }
    if (RouterChannel) {
        delete RouterChannel;
        RouterChannel = 0;
    }
    if (MulticastChannel) {
        delete MulticastChannel;
        MulticastChannel = 0;
    }
    for (int i = 0; i < NumConn; ++i) {
        delete Connection[i];
        Connection[i] = 0;
    }
    NumConn = 0;
}

// SYNTHETIC: GAMEMD 0x5430E0
// IPXManagerClass scalar deleting destructor emitted by VC6 from this definition.

// SYNTHETIC: GAMEMD 0x543100
// ConnManClass scalar deleting destructor emitted for the shared inline base.
