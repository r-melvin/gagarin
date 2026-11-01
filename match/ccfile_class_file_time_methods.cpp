// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x473E50 (name from the
//   YRpp method map).

#include "ccfile_class.h"
#include "mix_file_class.h"

// FUNCTION: GAMEMD 0x4739F0  (__thiscall)
// Construct the CD-file base and an empty buffer, then name the file through
// CDFileClass's SetFileName (a direct call to 0x47AE10, not the slot).
CCFileClass::CCFileClass(const char* pFileName) :
    Buffer(0, 0),
    Position(0)
{
    Availability = 0;
    CDFileClass::SetFileName(pFileName);
}

// FUNCTION: GAMEMD 0x473E50
unsigned long CCFileClass::GetFileTime()
{
    MixFileClass* mix = 0;
    unsigned long time = RawFileClass::GetFileTime();
    if (time == 0) {
        if (MixFileClass_Offset(GetFileName(), 0, &mix, 0, 0)) {
            const char* archiveName = mix->FileName;
            CCFileClass file(archiveName);
            // Retail 0x473EC6 dispatches through FileClass slot +0x38.
            time = static_cast<FileClass&>(file).GetFileTime();
            return time;
        }
    }
    return time;
}

// FUNCTION: GAMEMD 0x473F00
bool CCFileClass::SetFileTime(unsigned long fileTime)
{
    MixFileClass* mix = 0;
    bool ok = RawFileClass::SetFileTime(fileTime);
    if (!ok) {
        if (MixFileClass_Offset(GetFileName(), 0, &mix, 0, 0)) {
            const char* archiveName = mix->FileName;
            CCFileClass file(archiveName);
            // Retail 0x473F7F dispatches through FileClass slot +0x3C.
            ok = static_cast<FileClass&>(file).SetFileTime(fileTime);
        }
    }
    return ok;
}
