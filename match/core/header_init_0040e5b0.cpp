// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// The header initialiser group that opens the retail block at 0x40E5B0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order, then two count-up timers.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//   /Ob2: retail folds each timer's atexit registration into its initialiser.
#include <math.h>
#include "header_init_shapes.h"
#include "winmm_timer_methods.h"
#include "../platform/system_query_methods.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E1B10
const double DAT_007E1B10 = 60.0;
// GLOBAL: GAMEMD 0x7E1B18 -- degrees to radians
const double DAT_007E1B18 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x40E580
// GLOBAL: GAMEMD 0x887288
double DAT_00887288 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x40E5B0
// GLOBAL: GAMEMD 0x8872F0
double DAT_008872F0 = DAT_00887288 / DAT_007E1B10;
// SYNTHETIC: GAMEMD 0x40E5D0
// GLOBAL: GAMEMD 0x8872D8
double DAT_008872D8 = 1.0 / DAT_008872F0;
// SYNTHETIC: GAMEMD 0x40E5F0
// GLOBAL: GAMEMD 0x8872D0
double DAT_008872D0 = DAT_007E1B18 * 45.0;
// SYNTHETIC: GAMEMD 0x40E610
// GLOBAL: GAMEMD 0x887290
double DAT_00887290 = DAT_007E1B18 * 60.0;
// SYNTHETIC: GAMEMD 0x40E630
// GLOBAL: GAMEMD 0x887278
double DAT_00887278 = DAT_007E1B18 * 90.0;
// SYNTHETIC: GAMEMD 0x40E650
// GLOBAL: GAMEMD 0x8872F8
int DAT_008872F8 = (int)(FUN_004CAD50(DAT_00887278 - DAT_00887290) * DAT_00887288 * 0.5);
// SYNTHETIC: GAMEMD 0x40E690
// GLOBAL: GAMEMD 0x887298
double DAT_00887298 = FUN_004CADE0(DAT_008872F8 * 0.00390625);
// SYNTHETIC: GAMEMD 0x40E6C0
// GLOBAL: GAMEMD 0x8872C8
double DAT_008872C8 = FUN_004CADE0((DAT_008872F8 * 2) / DAT_00887288);
// SYNTHETIC: GAMEMD 0x40E6F0
// GLOBAL: GAMEMD 0x8872EC
int DAT_008872EC = (int)(DAT_008872F8 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x40E720
// GLOBAL: GAMEMD 0x887280
HeaderCellInit DAT_00887280(0, 0);
// SYNTHETIC: GAMEMD 0x40E730
// GLOBAL: GAMEMD 0x8872A0
HeaderCoordInit DAT_008872A0(0, 0, 0);
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

// The game clock (0x6C8C40, called with ECX = the clock member); its destructor
// is empty.
class GameClock
{
public:
    ~GameClock() {}
    // FUNCTION: GAMEMD 0x6C8C40 (decl; reloc) -- timeGetTime() >> 4.
    long Now() const;
};

// SYNTHETIC: GAMEMD 0x40EB50 -- initialiser: DAT_00887348, registers 0x40EB80
//   (the empty clock destructor).
// GLOBAL: GAMEMD 0x887348
HeaderTimer<GameClock> DAT_00887348;
// SYNTHETIC: GAMEMD 0x40EB90 -- initialiser: DAT_00887328, registers 0x40EBC0.
// SYNTHETIC: GAMEMD 0x40EBC0 -- atexit cleanup: ~TimerResolution on +0x04.
// GLOBAL: GAMEMD 0x887328
HeaderTimer<WinmmClock> DAT_00887328;
// SYNTHETIC: GAMEMD 0x40EBD0 -- initialiser: DAT_00887338, registers 0x40EC00.
// SYNTHETIC: GAMEMD 0x40EC00 -- atexit cleanup: the empty clock destructor.
// GLOBAL: GAMEMD 0x887338
HeaderTimer<GameClock> DAT_00887338;
