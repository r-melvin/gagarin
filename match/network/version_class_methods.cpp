// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x74FD20   VersionClass::Version_Protocol  (__thiscall)
//   FUNCTION: GAMEMD 0x74FD50   VersionClass::InitClipping      (__thiscall)
//   FUNCTION: GAMEMD 0x74FD60   VersionClass::Clip_Version      (__thiscall)
//   FUNCTION: GAMEMD 0x74FDA0   VersionClass::MinVersion        (__thiscall)
//   FUNCTION: GAMEMD 0x74FDB0   VersionClass::MaxVersion        (__thiscall)
//   GLOBAL:   GAMEMD 0x846140   VersionProtocol[3]  (VersionProtocolType)

#include "../_layout/version_class.h"

// GLOBAL: GAMEMD 0x846140 — the engine's version->protocol lookup table.
// Confirmed from memory: {0x1000,0}, {0x2000,1}, {0x10000,2}. The default
// fall-through returns VersionProtocol[2].Protocol (direct load of 0x846154).
extern VersionProtocolType VersionProtocol[3];

// FUNCTION: GAMEMD 0x74FD20  VersionClass::Version_Protocol (__thiscall)
// `this` (ECX) is unused; the function selects the protocol for the highest
// table entry whose Version is <= the requested version. cl strength-reduces
// the descending index loop to a pointer-walk (SUB EAX,8) while indexing the
// Protocol return via ECX*8, matching the retail codegen.
CommProtocolType VersionClass::Version_Protocol(unsigned int version)
{
    for (int i = 2; i >= 0; i--) {
        if (version >= VersionProtocol[i].Version) {
            return VersionProtocol[i].Protocol;
        }
    }
    return VersionProtocol[2].Protocol;
}

// FUNCTION: GAMEMD 0x74FD50  VersionClass::InitClipping (__thiscall)
// Reopen the clip window to this build's full supported range. Retail loads the
// constant once into EAX and stores it to both fields.
void VersionClass::InitClipping()
{
    MinClipVer = VERSION_CLASS_VERSION;
    MaxClipVer = VERSION_CLASS_VERSION;
}

// FUNCTION: GAMEMD 0x74FD60  VersionClass::Clip_Version (__thiscall)
// Intersects [minver,maxver] with the current [MinClipVer,MaxClipVer] window.
unsigned int VersionClass::Clip_Version(unsigned int minver, unsigned int maxver)
{
    if (minver > MaxClipVer) {
        return (unsigned int)-1;
    }
    if (maxver < MinClipVer) {
        return 0;
    }
    if (minver > MinClipVer) {
        MinClipVer = minver;
    }
    if (maxver < MaxClipVer) {
        MaxClipVer = maxver;
    }
    return MaxClipVer;
}

// FUNCTION: GAMEMD 0x74FDA0  VersionClass::MinVersion (__thiscall)
// The theoretical lowest version this build will connect to, before any
// clipping the hand-shake has applied.
unsigned int VersionClass::MinVersion()
{
    return VERSION_CLASS_VERSION;
}

// FUNCTION: GAMEMD 0x74FDB0  VersionClass::MaxVersion (__thiscall)
unsigned int VersionClass::MaxVersion()
{
    return VERSION_CLASS_VERSION;
}
