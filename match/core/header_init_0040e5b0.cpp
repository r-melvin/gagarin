// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// The header initialiser group that opens the retail block at 0x40E5B0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order, then two count-up timers.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//   /Ob2: retail folds each timer's atexit registration into its initialiser.
#include "header_init_shapes.h"
#include "winmm_timer_methods.h"
#include "../platform/system_query_methods.h"

// GLOBAL: GAMEMD 0x887288
extern double DAT_00887288;
// GLOBAL: GAMEMD 0x7E1B10
const double DAT_007E1B10 = 60.0;

// SYNTHETIC: GAMEMD 0x40E5B0
// GLOBAL: GAMEMD 0x8872F0
double DAT_008872F0 = DAT_00887288 / DAT_007E1B10;
// SYNTHETIC: GAMEMD 0x40E5D0
// GLOBAL: GAMEMD 0x8872D8
double DAT_008872D8 = 1.0 / DAT_008872F0;
// SYNTHETIC: GAMEMD 0x40E750
// GLOBAL: GAMEMD 0x8872E0
HeaderCoordInit DAT_008872E0(128, 128, 0);

// A count-up timer: the start stamp is read from the clock member before that
// member is constructed (declaration order), then the accumulator is cleared.
// Placeholder names.
template<class Clock> class HeaderTimer
{
public:
    HeaderTimer() : Started(Timer.Now()), Accumulated(0) {}

    long  Started;       // +0x00
    Clock Timer;         // +0x04
    long  Accumulated;   // +0x08
};

// The multimedia-timer clock (timeGetTime through 0x5D5890).
class WinmmClock : public TimerResolution
{
public:
    long Now() const { return FUN_005D5890(); }
};

// The game clock (Timer_GetTime, 0x6C8C40); its destructor is empty.
class GameClock
{
public:
    ~GameClock() {}
    long Now() const { return Timer_GetTime(); }
};

// SYNTHETIC: GAMEMD 0x40EB90 -- initialiser: DAT_00887328, registers 0x40EBC0.
// SYNTHETIC: GAMEMD 0x40EBC0 -- atexit cleanup: ~TimerResolution on +0x04.
// GLOBAL: GAMEMD 0x887328
HeaderTimer<WinmmClock> DAT_00887328;
// SYNTHETIC: GAMEMD 0x40EBD0 -- initialiser: DAT_00887338, registers 0x40EC00.
//   Not exact: retail calls 0x6C8C40 with ECX = the clock member (a member
//   call), while the tree models 0x6C8C40 as the free __fastcall Timer_GetTime.
// SYNTHETIC: GAMEMD 0x40EC00 -- atexit cleanup: the empty clock destructor.
// GLOBAL: GAMEMD 0x887338
HeaderTimer<GameClock> DAT_00887338;
