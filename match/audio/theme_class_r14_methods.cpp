// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (Ghidra disasm) at the
//   addresses annotated below: 0x720E80 0x720F70 0x720FD0 0x721010.
//   Layout and stream callees repeat match/audio/theme_class_stop_methods.h.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ThemeStream_00720EA0
{
    void FUN_00407F40();
    int  FUN_00408070() const;
    void FUN_004080C0();
    int  FUN_004080D0() const;
};

struct ThemeSaveStream_00721010
{
    virtual long __stdcall q0();
    virtual long __stdcall q1();
    virtual long __stdcall q2();
    virtual long __stdcall q3();
    virtual long __stdcall Write(const void* buf, unsigned long cb, unsigned long* written);
};

struct ThemeClass
{
    int  CurrentTheme;          // +0x00
    int  LastTheme;             // +0x04
    int  QueuedTheme;           // +0x08
    int  Volume;                // +0x0C
    bool IsScoreRepeat;         // +0x10
    bool IsFading;              // +0x11
    bool IsScoreShuffle;        // +0x12
    char _pad13[0x2C - 0x13];   // +0x13
    ThemeStream_00720EA0* Stream;  // +0x2C

    void FadeStream();                                   // 0x720E80
    void Suspend();                                      // 0x720F70
    bool FUN_00720FD0();                                 // 0x720FD0
    long SaveIndexes(ThemeSaveStream_00721010* stm);     // 0x721010
};
GG_STATIC_ASSERT(offsetof(ThemeClass, CurrentTheme) == 0x00);
GG_STATIC_ASSERT(offsetof(ThemeClass, LastTheme)    == 0x04);
GG_STATIC_ASSERT(offsetof(ThemeClass, QueuedTheme)  == 0x08);
GG_STATIC_ASSERT(offsetof(ThemeClass, IsFading)     == 0x11);
GG_STATIC_ASSERT(offsetof(ThemeClass, Stream)       == 0x2C);

extern bool ScoresPresent_00A8EC74;
extern bool DAT_00A8ED64;
int __cdecl FUN_00407000();
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x720E80
//
// Start fading the current stream out and flag the jukebox as fading.
void ThemeClass::FadeStream()
{
    if (this->Stream != 0) {
        this->Stream->FUN_004080C0();
    }
    this->IsFading = true;
}

// FUNCTION: GAMEMD 0x720F70
//
// Suspend the current score: same gates as Stop, then the stream is stopped,
// the current index is parked in the queued slot and the current/last
// indexes are cleared.
void ThemeClass::Suspend()
{
    if (!ScoresPresent_00A8EC74) {
        return;
    }
    if (!FUN_00407000()) {
        return;
    }
    if (DAT_00A8ED64) {
        return;
    }
    if (this->CurrentTheme == -1) {
        return;
    }
    // STRING: GAMEMD 0x84484C
    FUN_004068E0("Theme::Suspend(%d)\n", this->LastTheme);
    if (this->Stream != 0) {
        this->Stream->FUN_00407F40();
    }
    this->CurrentTheme = -1;
    this->QueuedTheme = this->LastTheme;
    this->LastTheme = -1;
}

// FUNCTION: GAMEMD 0x720FD0
//
// True while the stream is still playing; a pending fade that has finished
// is cleared first. False when there is no stream.
bool ThemeClass::FUN_00720FD0()
{
    if (this->Stream != 0) {
        if (this->IsFading) {
            if (this->Stream->FUN_004080D0() == 0) {
                this->Stream->FUN_00407F40();
            }
        }
        return this->Stream->FUN_00408070() != 0;
    }
    return false;
}

// FUNCTION: GAMEMD 0x721010
//
// Write the last and queued theme indexes to the save stream, stopping at the
// first failing HRESULT.
long ThemeClass::SaveIndexes(ThemeSaveStream_00721010* stm)
{
    long hr = stm->Write(&this->LastTheme, 4, 0);
    if (hr >= 0) {
        hr = stm->Write(&this->QueuedTheme, 4, 0);
    }
    return hr;
}
