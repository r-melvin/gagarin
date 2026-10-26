// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry-bounded retail evidence: 0x43AF70 reads doubles at 0x89C820 and
// 0x7E3E78, then stores to 0x89C880; 0x43AF90 reads 0x7E1718 and 0x89C880,
// then stores to 0x89C868. Both complete entry spans are 19 bytes.
// Further entry-bounded operations through 0x43B130 are grouped here for
// organization only. The 0x7E inputs are read-only .rdata. Original owners,
// source-file boundaries and startup registration are not established.
// Helper declarations model the observed stack-double input and x87 result;
// float versus double in the original return declaration is not established.
#include "../_rt/gg_static_assert.h"
#include "../_layout/global_0089c818.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(int) == 4);

extern "C" double DAT_0089C820; // GLOBAL: GAMEMD 0x0089C820
extern "C" const double DAT_007E3E78; // GLOBAL: GAMEMD 0x007E3E78
extern "C" double DAT_0089C880; // GLOBAL: GAMEMD 0x0089C880
extern "C" double DAT_0089C868; // GLOBAL: GAMEMD 0x0089C868

extern "C" const double DAT_007E3E80; // GLOBAL: GAMEMD 0x007E3E80
extern "C" const double DAT_007E1720; // GLOBAL: GAMEMD 0x007E1720
extern "C" double DAT_0089C860; // GLOBAL: GAMEMD 0x0089C860
extern "C" const double DAT_007E1728; // GLOBAL: GAMEMD 0x007E1728
extern "C" double DAT_0089C830; // GLOBAL: GAMEMD 0x0089C830
extern "C" const double DAT_007E1730; // GLOBAL: GAMEMD 0x007E1730
extern "C" double DAT_0089C7F8; // GLOBAL: GAMEMD 0x0089C7F8
extern "C" const double DAT_007E1738; // GLOBAL: GAMEMD 0x007E1738
extern "C" int DAT_0089C888; // GLOBAL: GAMEMD 0x0089C888
extern "C" double __cdecl FUN_004CAD50(double value); // FUNCTION: GAMEMD 0x004CAD50 (decl; reloc)
extern "C" const double DAT_007E1740; // GLOBAL: GAMEMD 0x007E1740
extern "C" double DAT_0089C840; // GLOBAL: GAMEMD 0x0089C840
extern "C" double __cdecl FUN_004CADE0(double value); // FUNCTION: GAMEMD 0x004CADE0 (decl; reloc)
// LIBRARY: GAMEMD 0x7C5F00 -- VC6 __ftol conversion helper.

extern "C" double DAT_0089C858; // GLOBAL: GAMEMD 0x0089C858
extern "C" int DAT_0089C87C; // GLOBAL: GAMEMD 0x0089C87C

extern "C" int DAT_0089C848; // GLOBAL: GAMEMD 0x0089C848
extern "C" int DAT_0089C84C; // GLOBAL: GAMEMD 0x0089C84C
extern "C" int DAT_0089C850; // GLOBAL: GAMEMD 0x0089C850

extern "C" int DAT_0089C878; // GLOBAL: GAMEMD 0x0089C878
extern "C" int DAT_0089C870; // GLOBAL: GAMEMD 0x0089C870
extern "C" int DAT_0089C874; // GLOBAL: GAMEMD 0x0089C874
extern "C" int DAT_0089C808; // GLOBAL: GAMEMD 0x0089C808
extern "C" int DAT_0089C80C; // GLOBAL: GAMEMD 0x0089C80C
extern "C" int DAT_0089C810; // GLOBAL: GAMEMD 0x0089C810
extern "C" int DAT_0089C814; // GLOBAL: GAMEMD 0x0089C814

// FUNCTION: GAMEMD 0x43AF70
extern "C" void FUN_0043AF70()
{
    DAT_0089C880 = DAT_0089C820 / DAT_007E3E78;
}

// FUNCTION: GAMEMD 0x43AF90
extern "C" void FUN_0043AF90()
{
    DAT_0089C868 = 1.0 / DAT_0089C880;
}

// FUNCTION: GAMEMD 0x43AFB0
extern "C" void FUN_0043AFB0()
{
    DAT_0089C860 = DAT_007E1720 * DAT_007E3E80;
}

// FUNCTION: GAMEMD 0x43AFD0
extern "C" void FUN_0043AFD0()
{
    DAT_0089C830 = DAT_007E1728 * DAT_007E3E80;
}

// FUNCTION: GAMEMD 0x43AFF0
extern "C" void FUN_0043AFF0()
{
    DAT_0089C7F8 = DAT_007E1730 * DAT_007E3E80;
}

// FUNCTION: GAMEMD 0x43B010
extern "C" void FUN_0043B010()
{
    DAT_0089C888 = (int)(FUN_004CAD50(DAT_0089C7F8 - DAT_0089C830)
                         * DAT_007E1738 * DAT_0089C820);
}

// FUNCTION: GAMEMD 0x43B050
extern "C" void FUN_0043B050()
{
    DAT_0089C840 = FUN_004CADE0((double)DAT_0089C888 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x43B080
extern "C" void FUN_0043B080()
{
    DAT_0089C858 = FUN_004CADE0((double)(DAT_0089C888 * 2) / DAT_0089C820);
}

// FUNCTION: GAMEMD 0x43B0B0
extern "C" void FUN_0043B0B0()
{
    DAT_0089C87C = (int)(DAT_0089C888 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x43B0E0
extern "C" void FUN_0043B0E0()
{
    DAT_0089C818.words.word_00 = 0;
    DAT_0089C818.words.word_02 = 0;
}

// FUNCTION: GAMEMD 0x43B0F0
extern "C" void FUN_0043B0F0()
{
    DAT_0089C848 = 0;
    DAT_0089C84C = 0;
    DAT_0089C850 = 0;
}

// FUNCTION: GAMEMD 0x43B110
extern "C" void FUN_0043B110()
{
    DAT_0089C878 = 0;
    DAT_0089C870 = 0x80;
    DAT_0089C874 = 0x80;
}
// FUNCTION: GAMEMD 0x43B130
extern "C" void FUN_0043B130()
{
    DAT_0089C808 = 0;
    DAT_0089C80C = 0;
    DAT_0089C810 = 0;
    DAT_0089C814 = 0;
}
