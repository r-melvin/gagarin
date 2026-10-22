// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
// Entry-origin retail spans establish pool initialization, field widths,
// virtual cleanup dispatch and vector destruction. /Ob2 preserves the retail
// inline copies while the ordinary functions each have one out-of-line definition.
#include "winsock_interface_class.h"
#include "../../core/vector_class_operations.h"
// STRING: GAMEMD 0x84DE48
// FUNCTION: GAMEMD 0x7B19C0
WinsockInterfaceClass::WinsockInterfaceClass()
{
    Socket = -1;
    unknown_3F070 = -1;
    WinsockInitialised = false;
    for (int i = 0; i < 128; i++)
    {
        StaticInBuffers[i].InUse = 0;
        StaticInBuffers[i].IsAllocated = 0;
        StaticOutBuffers[i].InUse = 0;
        StaticOutBuffers[i].IsAllocated = 0;
        StaticOutBuffers[i].unknown_17 = 0;
        StaticOutBuffers[i].unknown_18 = 0;
        StaticAltOutBuffers[i].InUse = 0;
        StaticAltOutBuffers[i].IsAllocated = 0;
        StaticAltOutBuffers[i].unknown_17 = 1;
        StaticAltOutBuffers[i].unknown_18 = 0;
    }
    StaticInBuffersInUse = 0;
    StaticOutBuffersInUse = 0;
    StaticAltOutBuffersInUse = 0;
    StaticInBufferPos = 0;
    StaticOutBufferPos = 0;
    unknown_04 = 0x240;
    FUN_004068E0("WinsockInterface constructed\n");
}

// FUNCTION: GAMEMD 0x7B1AB0
WinsockInterfaceClass::~WinsockInterfaceClass()
{
    ShutdownWinsock();
}

// FUNCTION: GAMEMD 0x7B1B50
void WinsockInterfaceClass::ShutdownWinsock()
{
    if (WinsockInitialised)
    {
        StopListening();
        vf_1();
        WSACleanup();
        WinsockInitialised = false;
    }
}

// SYNTHETIC: GAMEMD 0x7B2780
// Scalar deleting destructor emitted naturally from the native base definition.
