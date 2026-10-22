// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x7207F0: the two gate bytes 0xA8EC74 and 0xA8ED64
//   with the probe 0x407000 between them, the Themes vector at `[EDI+0x18]`
//   (Items) / `[EDI+0x24]` (Count), each entry's Sound name at `+0x100`,
//   its Exists byte at `+0x28A` and its Length float at `+0x284`, the
//   0x200-byte path buffer filled by `_makepath` 0x7C9FF0 with the ".WAV"
//   extension at 0x844768, the 0x6C-byte stack CCFileClass built by the
//   0x4739F0 constructor and torn down inline (vtable 0x7E16B0, Position
//   zeroed, 0x43AE50 on the +0x58 buffer, vtable 0x7E1668, 0x431B80), its
//   Exists 0x473C50 (0 pushed) and Open 0x473D10 (1 pushed), the audio
//   object built by 0x4085A0 with 0x408610 and 0x408560, and the 64-bit
//   divide by 1000 through __aulldiv 0x7C9380. The ThemeControl and
//   ThemeClass offsets match the committed model in
//   match/audio/theme_class_find_methods.h and the CCFileClass offsets
//   match match/platform/ccfile_class_open_mix_methods.h. Names
//   cross-checked against YRpp.
#ifndef GG_MATCH_AUDIO_THEME_CLASS_SCAN_METHODS_H
#define GG_MATCH_AUDIO_THEME_CLASS_SCAN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/memory_buffer.h"

// GLOBAL: GAMEMD 0xA8EC74 — the first scan gate.
extern char DAT_00A8EC74;
// GLOBAL: GAMEMD 0xA8ED64 — the second scan gate.
extern char DAT_00A8ED64;
// FUNCTION: GAMEMD 0x407000 (decl; reloc) — the audio-available probe.
int __cdecl FUN_00407000();
// STRING: GAMEMD 0x844768 — ".WAV".
extern const char STR_00844768[];

// LIBRARY: GAMEMD 0x7C9FF0 (decl; reloc) — CRT _makepath.
extern "C" void __cdecl gg_makepath(char* path, const char* drive,
                                    const char* dir, const char* fname,
                                    const char* ext);
// LIBRARY: GAMEMD 0x7C9380 (decl; reloc) — CRT __aulldiv. The 64-bit
// helpers pop their own arguments, so it is declared __stdcall.
extern "C" unsigned __int64 __stdcall gg_aulldiv(unsigned __int64 a,
                                                 unsigned __int64 b);

// FUNCTION: GAMEMD 0x431B80 (decl; reloc) — the base destructor.
void FUN_00431B80(void* self);

extern char VT_007E16B0;   // VTABLE: GAMEMD 0x7E16B0 — CCFileClass
extern char VT_007E1668;   // VTABLE: GAMEMD 0x7E1668 — CDFileClass

// The stack CCFileClass; only the members this teardown touches are named.
struct File_007207F0
{
    char* Vtbl;                    // +0x0000
    char  _pad004[0x58 - 0x04];    // +0x0004
    char  Buffer[0x64 - 0x58];     // +0x0058
    int   Position;                // +0x0064
    int   Availability;            // +0x0068

    // FUNCTION: GAMEMD 0x4739F0 (decl; reloc) — CCFileClass::CCFileClass.
    void Construct(const char* name);
    // FUNCTION: GAMEMD 0x473C50 (decl; reloc) — CCFileClass::Exists.
    bool Exists(int flag);
    // FUNCTION: GAMEMD 0x473D10 (decl; reloc) — CCFileClass::Open.
    int Open(unsigned int mode);

    // The destructor, expanded inline by retail: this class's vtable and a
    // zeroed Position, the buffer released, then the base's vtable and its
    // destructor.
    void Destruct()
    {
        this->Vtbl = &VT_007E16B0;
        this->Position = 0;
        reinterpret_cast<MemoryBuffer*>(this->Buffer)->Clear();
        this->Vtbl = &VT_007E1668;
        FUN_00431B80(this);
    }
};
GG_STATIC_ASSERT(offsetof(File_007207F0, Buffer)   == 0x58);
GG_STATIC_ASSERT(offsetof(File_007207F0, Position) == 0x64);
GG_STATIC_ASSERT(sizeof(File_007207F0) == 0x6C);

// The sample reader built on the stack next to the file.
struct Audio_007207F0
{
    char opaque[0x20];

    // FUNCTION: GAMEMD 0x4085A0 (decl; reloc) — construct the reader.
    void Construct();
};
GG_STATIC_ASSERT(sizeof(Audio_007207F0) == 0x20);

// FUNCTION: GAMEMD 0x408610 (decl; reloc) — read the sample header from the
// open file into the reader, __fastcall: the file in ECX, the reader in EDX
// and the length out-pointer pushed.
int FUN_00408610(File_007207F0* file, Audio_007207F0* audio, int* length);
// FUNCTION: GAMEMD 0x408560 (decl; reloc) — the sample's duration in
// milliseconds as a 64-bit value, __fastcall.
unsigned __int64 FUN_00408560(Audio_007207F0* audio, int length);

// ThemeControl — one registered score.
struct ThemeControl_007207F0
{
    char    ID[0x100];       // +0x0000
    char    Sound[0x100];    // +0x0100
    char    _pad200[0x80];   // +0x0200  UIName
    int     Scenario;        // +0x0280
    float   Length;          // +0x0284
    char    Normal;          // +0x0288
    char    Repeat;          // +0x0289
    char    Exists;          // +0x028A
    char    _pad28B;         // +0x028B
    int     Side;            // +0x028C
};
GG_STATIC_ASSERT(offsetof(ThemeControl_007207F0, Sound)  == 0x100);
GG_STATIC_ASSERT(offsetof(ThemeControl_007207F0, Length) == 0x284);
GG_STATIC_ASSERT(offsetof(ThemeControl_007207F0, Exists) == 0x28A);

struct ThemeVector_007207F0
{
    void*                    _vtable;   // +0x00
    ThemeControl_007207F0**  Items;     // +0x04
    int                      Capacity;  // +0x08
    int                      IsAllocated; // +0x0C
    int                      Count;     // +0x10
    int                      CapacityIncrement; // +0x14
};
GG_STATIC_ASSERT(offsetof(ThemeVector_007207F0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeVector_007207F0, Count) == 0x10);

struct Theme_007207F0
{
    char                 _pad000[0x14];   // +0x0000
    ThemeVector_007207F0 Themes;          // +0x0014

    // FUNCTION: GAMEMD 0x7207F0 — ThemeClass::Scan.
    void Scan();
};
GG_STATIC_ASSERT(offsetof(Theme_007207F0, Themes) + offsetof(ThemeVector_007207F0, Items) == 0x18);
GG_STATIC_ASSERT(offsetof(Theme_007207F0, Themes) + offsetof(ThemeVector_007207F0, Count) == 0x24);

#endif  // GG_MATCH_AUDIO_THEME_CLASS_SCAN_METHODS_H
