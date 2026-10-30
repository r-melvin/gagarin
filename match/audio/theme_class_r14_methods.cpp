// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   ThemeClass methods consolidated here after P14. Native TU attribution is
//   unknown in scripts/data/original_tu_map.json. Addresses and method bodies
//   are confirmed against retail gamemd.exe v1.001; layout/callees are pinned
//   by match/_layout/theme_class.h and the method headers below.
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob1
// Reason: native 0x720A80 calls ThemeClass::IsAvailable at 0x721140; the merged
// same-TU body is auto-inlined under /Ob2, while /Ob1 keeps that call and all
// twelve rows pass raw/strict checks.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"
#include "../_layout/theme_class.h"
#include "theme_class_ai_methods.h"
#include "theme_class_queue_methods.h"
#include "theme_class_random_methods.h"
#include "theme_class_scan_methods.h"
#include "theme_class_stop_methods.h"

struct ThemeSaveStream_00721010
{
    virtual long __stdcall q0();
    virtual long __stdcall q1();
    virtual long __stdcall q2();
    virtual long __stdcall q3();
    virtual long __stdcall Write(const void* buf, unsigned long cb, unsigned long* written);
};


// FUNCTION: GAMEMD 0x720770
// Delete every registered score, then shut down and release the stream.
void ThemeClass::Clear()
{
    while (Themes.Count > 0) {
        delete Themes.Items[0];
        Themes.Delete(0);
    }
    if (Stream != 0) {
        Stream->FUN_004080C0();
        Stream->FUN_004080F0();
        Stream->FUN_00407F40();
        Stream->FUN_00407A90();
        Stream = 0;
    }
}

// FUNCTION: GAMEMD 0x7207F0
//
// Note which registered scores are actually present and how long they run.
// Each entry's sound name becomes a ".WAV" path, a stack file object answers
// whether it exists, and for the ones that do the sample header gives a
// length in milliseconds that is divided down into the entry's Length.
//
// Load-bearing: the element slot is taken into a pointer local before each
// call whose result is stored through it (retail computes the address
// first and keeps it in a callee-saved register across the call), the
// sample duration is bound before the divide so the call happens before
// the divisor is pushed, and the CRT 64-bit divide pops its own arguments
// (__stdcall) so no stack adjustment follows it.
void ThemeClass::Scan()
{
    if (DAT_00A8EC74 && FUN_00407000() && !DAT_00A8ED64) {
        for (int i = 0; i < Themes.Count; i++) {
            char path[0x200];
            gg_makepath(path, 0, 0, Themes.Items[i]->Sound, STR_00844768);

            File_007207F0 file;
            file.Construct(path);

            ThemeControl** slot = &Themes.Items[i];
            (*slot)->Exists = file.Exists(0);

            if (Themes.Items[i]->Exists) {
                Audio_007207F0 audio;
                audio.Construct();
                file.Open(1);
                int length;
                if (FUN_00408610(&file, &audio, &length)) {
                    ThemeControl** entry = &Themes.Items[i];
                    unsigned __int64 millis = FUN_00408560(&audio, length);
                    int seconds = (int)gg_aulldiv(millis, 1000);
                    (*entry)->Length = (float)seconds;
                }
            }
            file.Destruct();
        }
    }
}

// FUNCTION: GAMEMD 0x720960
// No score playing or queued, full volume, no flags, an empty score list and no stream.
ThemeClass::ThemeClass()
    : CurrentTheme(-1), LastTheme(-1), QueuedTheme(-1), Volume(0xFF),
      IsScoreRepeat(false), IsFading(false), IsScoreShuffle(false), Stream(0)
{
}

// FUNCTION: GAMEMD 0x7209D0
//
// One tick of the score jukebox. Nothing happens unless the audio engine is
// up, the suppress byte is clear, scores are present and the volume is
// audible. With a live stream, a fade that has finished is stopped, and a
// stream that is still playing ends the tick. Otherwise a queued score (not
// the -1 / -3 sentinels, and not while the dword gate is set) is started: the
// "pick one" sentinel -2 is first resolved through the random picker and
// logged, then the score is played and the queue reset to -2.
//
// The "still playing" flag is a bool declared before the stream block, set
// inside it and tested after it: that merge is what makes retail materialise
// the stream call's int result (`TEST EAX,EAX; SETNZ AL; TEST AL,AL; JNZ`).
// Testing the call directly, a local inside the block, a cast, a ternary or
// an inline bool wrapper all fold to a bare `TEST EAX,EAX; JNZ`.
void ThemeClass::AI()
{
    if (FUN_00407000() && !DAT_00A8ED64 && ScoresPresent_00A8EC74
        && this->Volume > 0) {
        bool playing = false;
        if (this->Stream != 0) {
            if (this->IsFading) {
                if (this->Stream->FUN_004080D0() == 0)
                    this->Stream->FUN_00407F40();
            }
            playing = this->Stream->FUN_00408070() != 0;
        }
        if (playing)
            return;

        int theme = this->QueuedTheme;
        if (theme != -1 && theme != -3 && DAT_00A8E7AC == 0) {
            if (theme == -2) {
                this->QueuedTheme = this->GetRandomIndex(this->LastTheme);
                // STRING: GAMEMD 0x8447B8
                FUN_004068E0("Theme::AI(Next song = %d)\n", this->QueuedTheme);
            }
            this->PlaySong(this->QueuedTheme);
            this->QueuedTheme = -2;
        }
    }
}

// FUNCTION: GAMEMD 0x720A80
//
// Pick the next score after `index`. A valid index whose score (or the whole
// jukebox) is set to repeat is handed straight back. Otherwise, in shuffle
// mode, up to 1000 random draws are made until one differs from `index` and
// is available (0 if none was found); in sequential mode the list is walked
// forward with wrap-around, at most Count+1 steps, until an available score
// turns up (again 0 if none).
//
// The `last` local is load-bearing: written inline as the call argument the
// Count-1 temporary lands in EDX, through a named local it takes EAX as retail.
int ThemeClass::GetRandomIndex(int index)
{
    if ((index > -1 && !this->Themes.Items[index]->Repeat && !this->IsScoreRepeat)
        || index < 0)
    {
        if (this->IsScoreShuffle == true)
        {
            int tries = 0;
            int pick;
            do {
                int last = this->Themes.Count - 1;
                pick = DAT_00886B88.RandomRanged(0, last);
                tries++;
            } while (tries < 1000 && (pick == index || !this->IsAvailable(pick)));

            if (tries == 1000)
                pick = 0;
            return pick;
        }

        int tries = this->Themes.Count + 1;
        do {
            index++;
            if (index >= this->Themes.Count)
                index = 0;
            tries--;
            if (tries == 0)
                return 0;
        } while (!this->IsAvailable(index));
    }
    return index;
}

// FUNCTION: GAMEMD 0x720B20
//
// Queue a score to play next; the function's own trace names it
// Theme::QueueSong. Gated on scores being present, the audio engine
// being up and the suppress byte being clear; the request is recorded before
// the "no-op" indexes (-1 / -2 / already-last) are filtered out. With a live
// stream, a fade already in progress that has finished is cleared, and if the
// stream reports it is playing it is told to fade and the flag is set.
//
// The bool round-trip after the 0x408070 call (`TEST EAX,EAX; SETNZ AL; CMP
// AL,1; JNZ`) is a flag declared before the stream block, assigned inside it
// and compared `== true` after it; every same-block spelling folds to a bare
// TEST/JZ (61.7%). The engine probe 0x407000 returns int (retail tests EAX).
void ThemeClass::QueueSong(int theme)
{
    if (ScoresPresent_00A8EC74) {
        if (FUN_00407000() && !DAT_00A8ED64) {
            this->QueuedTheme = theme;
            if (theme != -1 && theme != -2 && theme != this->LastTheme) {
                // STRING: GAMEMD 0x8447D4
                FUN_004068E0("Theme::QueueSong(%d)\n", theme);
                bool playing = false;
                if (this->Stream != 0) {
                    if (this->IsFading) {
                        if (this->Stream->FUN_004080D0() == 0)
                            this->Stream->FUN_00407F40();
                    }
                    playing = this->Stream->FUN_00408070() != 0;
                }
                if (playing == true) {
                    if (this->Stream != 0)
                        this->Stream->FUN_004080C0();
                    this->IsFading = true;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x720E80
//
// Start fading the current stream out and flag the jukebox as fading.
void ThemeClass::FadeStream()
{
    ThemeStream* stream = this->Stream;
    if (stream != 0) {
        stream->FUN_004080C0();
    }
    this->IsFading = true;
}

// FUNCTION: GAMEMD 0x720EA0  ThemeClass::Stop (__thiscall, ret 0x4)
//
// Stop the current score. Gated on scores being present, the audio engine
// being up, the suppress byte being clear and a score actually being current.
// With `fade` and a live stream, a finished fade is first cleared, and if the
// stream reports it is playing it is told to fade out and the fading flag is
// set; otherwise the stream is stopped outright. Either way the current, last
// and queued indexes are reset.
//
// The bool round-trip after the 0x408070 call (`TEST EAX,EAX; SETNZ AL; CMP
// AL,1; JNZ`) is a flag declared before the fade block, assigned inside it
// and compared `== true` after it; every same-block spelling folds to a bare
// TEST/JZ (41.4%). The three -1 stores are one tail reached by `goto`; a
// duplicated copy makes VC6 hoist -1 into EDI.
void ThemeClass::Stop(bool fade)
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

    bool playing = false;
    if (fade && this->Stream != 0) {
        if (this->IsFading) {
            if (this->Stream->FUN_004080D0() == 0) {
                this->Stream->FUN_00407F40();
            }
        }
        playing = this->Stream->FUN_00408070() != 0;
    }
    if (playing == true) {
        // STRING: GAMEMD 0x844830
        FUN_004068E0("Theme::Stop(%d) - Fading\n", this->LastTheme);
        if (this->Stream != 0) {
            this->Stream->FUN_004080C0();
        }
        this->IsFading = true;
        goto reset;
    }

    // STRING: GAMEMD 0x84481C
    FUN_004068E0("Theme::Stop(%d)\n", this->LastTheme);
    if (this->Stream != 0) {
        this->Stream->FUN_00407F40();
    }

reset:
    this->CurrentTheme = -1;
    this->LastTheme = -1;
    this->QueuedTheme = -1;
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
    ThemeStream* stream = this->Stream;
    if (stream != 0) {
        stream->FUN_00407F40();
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

// FUNCTION: GAMEMD 0x721140
//
// Whether `theme` may be played now. The two sentinels (-3 / -2) are always
// available. A real index must be inside the vector (unsigned compare), the
// entry must exist and be a normal score, its side (if any) must match the
// current player's, and outside campaign mode its scenario gate must not
// exceed the scenario's counter.
bool ThemeClass::IsAvailable(int theme) const
{
    if (theme == -3 || theme == -2)
        return true;
    if ((unsigned int)theme >= (unsigned int)this->Themes.Count)
        return false;

    ThemeControl* control = this->Themes.Items[theme];
    if (!control->Exists)
        return false;
    if (!control->Normal)
        return false;
    if (DAT_00A83D4C != 0 && control->Side != -1
        && DAT_00A83D4C->Type->SideIndex != control->Side)
        return false;
    if (Session_00A8B238.GameMode == 0
        && DAT_00A8B230->unknown_1254 < control->Scenario)
        return false;
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8EC74
bool ScoresPresent_00A8EC74;
// GLOBAL: GAMEMD 0xA8ED64
bool DAT_00A8ED64;
// END defined globals
