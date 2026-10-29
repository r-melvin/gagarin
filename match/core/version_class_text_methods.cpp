// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x74FA20. Offsets and
//   callees read off the retail disassembly with the local Ghidra CLI; the
//   VersionClass layout is the one pinned in version_class_ctor_methods.h.
//
// Address index:
//   0x74FA20  VersionClass::FUN_0074FA20

#include <string.h>
#include "../_layout/version_class.h"
#include "../platform/ccfile_class.h"

// STRING: GAMEMD 0x84635C -- the version text file name.
extern const char STR_0084635C[];

// FUNCTION: GAMEMD 0x74FA20
//
// On first use read the sixteen-byte version text file into VersionText,
// terminate it, strip trailing carriage returns and mark the text read (an
// absent file leaves it empty). Then answer the minor version, which is
// computed as 1 the first time it is asked for.
unsigned short VersionClass::FUN_0074FA20()
{
    if (!TextInit) {
        {
            RawFileClass file(STR_0084635C);
            if (file.Exists(0)) {
                file.ReadBytes(VersionText, 0x10);
                VersionText[0xF] = '\0';
                while (VersionText[strlen(VersionText) - 1] == '\r') {
                    VersionText[strlen(VersionText) - 1] = '\0';
                }
            } else {
                VersionText[0] = '\0';
            }
        }
        TextInit = 1;
    }
    if (MinorInit) {
        return MinorVersion;
    }
    MinorVersion = 1;
    MinorInit = 1;
    return 1;
}
