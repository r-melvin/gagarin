// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// File-scope object next to the CD drive code (initialiser 0x4796E0, exit stub
// 0x479700). It is a 26-word record that the constructor zeroes and whose
// destructor is empty; nothing else in the binary references the instance.
// /Ob2 fuses the constructor and the atexit registration into one initialiser.

struct CDGlobal_0089E3A8
{
    int Words[26];
    CDGlobal_0089E3A8()
    {
        for (int i = 0; i < 26; ++i)
        {
            Words[i] = 0;
        }
    }
    ~CDGlobal_0089E3A8() {}
};

// SYNTHETIC: GAMEMD 0x4796E0
// SYNTHETIC: GAMEMD 0x479700 -- exit-time destructor stub
// GLOBAL: GAMEMD 0x89E3A8
CDGlobal_0089E3A8 DAT_0089E3A8;
