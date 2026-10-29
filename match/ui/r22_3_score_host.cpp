// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x6904C0.
//
// Address index: 0x6904C0

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

// GLOBAL: GAMEMD 0xA8ED80 -- set once the pending operation has completed.
extern bool DAT_00A8ED80;

// FUNCTION: GAMEMD 0x5D4D50 (decl; reloc) -- pump pending window messages.
void FUN_005D4D50();

// A child object stored in the host's list (only vtable slots 1 and 2 are used here).
struct Child_006904C0 {
    virtual void Slot0();
    virtual void Begin();
    virtual void End();
};

struct Host_006904C0 {
    char _pad00[0x20];
    Child_006904C0** Children;   // +0x20
    char _pad24[0x08];
    int ChildCount;              // +0x2C

    // FUNCTION: GAMEMD 0x6904C0 (__thiscall)
    void FUN_006904C0();
};

// FUNCTION: GAMEMD 0x6904C0
// Tell every child to begin, wait (pumping messages) until the completion flag is set, then
// tell every child to end. Does nothing when the flag is already set.
void Host_006904C0::FUN_006904C0()
{
    if (DAT_00A8ED80 != true) {
        for (int i = 0; i < ChildCount; i++) {
            Children[i]->Begin();
        }
        while (!DAT_00A8ED80) {
            Sleep(500);
            FUN_005D4D50();
        }
        for (int j = 0; j < ChildCount; j++) {
            Children[j]->End();
        }
    }
}
