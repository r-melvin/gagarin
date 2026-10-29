// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Each function writes
//   one or two values of the [MultiPlayer] section into RA2MD.INI through the global INI object.
//
// Address index: 0x5EE1B0 0x5D9360 0x5D8FD0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../platform/ccfile_class.h"
#include "../platform/ccini_class_methods.h"

extern CCINIClass DAT_008870C0;
// GLOBAL: GAMEMD 0xAC10C8
extern int DAT_00AC10C8;

// FUNCTION: GAMEMD 0x5EE1B0
// Save the observer-mode option to RA2MD.INI.
void FUN_005EE1B0()
{
    RawFileClass file("RA2MD.INI");
    DAT_008870C0.WriteInteger("MultiPlayer", "ObserverMode", DAT_00AC10C8, 0);
    DAT_008870C0.WriteCCFile(&file, false);
}

// Firewall detection block: result code at +0x00, delta at +0x08.
struct FirewallInfo_005D8FD0
{
    unsigned Settings;     // +0x00
    int unknown_04;        // +0x04
    int Delta;             // +0x08

    unsigned Detect(bool* needSave);   // GAMEMD 0x5D9410 (decl; reloc)
    void Save();
    void DetectAndSave();
};
GG_STATIC_ASSERT(offsetof(FirewallInfo_005D8FD0, Delta) == 0x08);

// FUNCTION: GAMEMD 0x5D9360
// Write the firewall settings and delta to RA2MD.INI.
void FirewallInfo_005D8FD0::Save()
{
    RawFileClass file("RA2MD.INI");
    DAT_008870C0.WriteInteger("MultiPlayer", "FirewallSettings", Settings, 0);
    DAT_008870C0.WriteInteger("MultiPlayer", "FirewallDelta", Delta, 0);
    DAT_008870C0.WriteCCFile(&file, false);
}

// FUNCTION: GAMEMD 0x5D8FD0
// Detect the firewall type once; when detection asks for it, write the result to RA2MD.INI.
void FirewallInfo_005D8FD0::DetectAndSave()
{
    bool needSave = false;
    if (Settings == 0) {
        Settings = Detect(&needSave);
        if (needSave) {
            RawFileClass file("RA2MD.INI");
            DAT_008870C0.WriteInteger("MultiPlayer", "FirewallSettings", Settings, 0);
            DAT_008870C0.WriteInteger("MultiPlayer", "FirewallDelta", Delta, 0);
            DAT_008870C0.WriteCCFile(&file, false);
        }
    }
}
