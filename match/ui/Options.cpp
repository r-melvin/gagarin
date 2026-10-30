// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Options.CPP. The name is the source-file string at 0x833370
//   in retail gamemd.exe v1.001, passed by the assert at 0x5fbb56 inside this object's
//   code range (0x5fa0d0-0x5fc16f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "../core/triple_timer_init_methods.h"
#include "../core/empty_function_family_methods.h"
#include "../core/mathtbl_init_shapes.h"

#include "../core/trivial_tu167_methods.h"

#include "game_options_class_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7EF378
extern const double DAT_007EF378;
// GLOBAL: GAMEMD 0xAC14B0
extern double DAT_00AC14B0;

// SYNTHETIC: GAMEMD 0x005FA100
// dynamic initializer for DAT_00AC1500
// GLOBAL: GAMEMD 0x00AC1500
double DAT_00AC1500 = DAT_00AC14B0 / DAT_007EF378;

// SYNTHETIC: GAMEMD 0x005FA120
// dynamic initializer for DAT_00AC14E8
// GLOBAL: GAMEMD 0x00AC14E8
double DAT_00AC14E8 = 1.0 / DAT_00AC1500;

GG_STATIC_ASSERT(sizeof(DAT_00AC1500) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00AC14E8) == 8);

// SYNTHETIC: GAMEMD 0x005FA2A0
// GLOBAL: GAMEMD 0x00AC14F0
MathTblCoord DAT_00AC14F0;

// FUNCTION: GAMEMD 0x005FA430
void FUN_005FA430()
{
}

// FUNCTION: GAMEMD 0x5FB2E0  GameOptionsClass::GetAnimSpeed (__thiscall, ret 0x4)
// Rates 1..4 come out of the tuned table; anything faster is computed instead,
// as eight ticks divided by the game speed (plus one, so speed 0 is safe). Rate
// 0 means "no animation" and short-circuits.
//
// The original assigns back into the `rate` parameter and falls out of the
// bottom, which is why the rate-0 exit shares the trailing RET with the
// computed path instead of getting its own. A separate `result` local scores
// 6.7% and an early `return 0;` 13.3%.
//
// MATCHED (100%, 14/14). The last two instructions were the index register:
// retail computes the table index into EDX (`LEA EDX,[ECX+EAX*8]`) and cl put
// it in EAX. It is not the subscript that chooses this but the *scope of the
// game-speed local*. Hoisting `GameSpeed` into a named `speed` above the
// rate<5 branch makes it live across both arms, so cl recycles EAX for the
// address; reading the member inline in the table path and naming `speed`
// only inside the divide path, where the `+1` needs it, gives retail's EDX
// exactly. Eight other spellings all sat at 85.7%: a named index, a named row
// pointer, a named element pointer, the addition written speed-first, the
// result assigned back through `rate`, a two-armed assignment with one
// fallthrough return, a 2D row cast, a shift instead of the multiply, an
// unsigned index, char-scaled address arithmetic, and volatile reads of both
// the member and the table.
int GameOptionsClass::GetAnimSpeed(int rate)
{
    if (rate != 0) {
        if (rate < 5)
            return AnimSpeedTable[rate * 8 + GameSpeed];

        int speed = GameSpeed;
        rate = (rate * 8) / (speed + 1);
    }
    return rate;
}

// FUNCTION: GAMEMD 0x5FBF70
// Member getter (dword).
int Obj_005FBF70::FUN_005FBF70() const
{
    return unknown_0C;
}

// A selectable entry of the intro-movie and score option tables: the key it is stored
// under, the label of its display text, and a third word.
struct OptionEntry_005FBF80
{
    const char* Name;       // +0x00 zero ends a table
    const char* Label;      // +0x04
    int unknown_08;         // +0x08
};
GG_STATIC_ASSERT(sizeof(OptionEntry_005FBF80) == 0xC);

// GLOBAL: GAMEMD 0x832C20 -- the intro-movie entry.
extern OptionEntry_005FBF80 DAT_00832C20;
// GLOBAL: GAMEMD 0x832CA0 -- the soviet campaign movie entries.
extern OptionEntry_005FBF80 DAT_00832CA0[];
// GLOBAL: GAMEMD 0x832C30 -- the allied campaign movie entries.
extern OptionEntry_005FBF80 DAT_00832C30[];

// The movie-pick state: the furthest entry unlocked in each campaign table.
#include "../_layout/obj_005fbf80.h"

// LIBRARY: GAMEMD 0x7C8D20 -- _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- the localised text of a label.
const wchar_t* __fastcall FUN_00734E60(const char* label, int flags, const char* file, int line);

// The index of the entry stored under a key, or -1 when the table has none.
static int FindOptionEntry(const OptionEntry_005FBF80* table, const char* name)
{
    int index = 0;
    for (const OptionEntry_005FBF80* entry = table; entry->Name != 0; entry++, index++) {
        if (_stricmp(name, entry->Name) == 0) {
            return index;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5FBF80
// Note a movie as unlocked: find its key in each campaign table and keep the larger index.
void Obj_005FBF80::FUN_005FBF80(const char* name)
{
    int index = FindOptionEntry(DAT_00832CA0, name);
    if (index > unknown_4C) {
        unknown_4C = index;
    }
    index = FindOptionEntry(DAT_00832C30, name);
    if (index > unknown_50) {
        unknown_50 = index;
    }
}

// GLOBAL: GAMEMD 0x833370 -- "D:\\ra2mdpost\\Options.CPP", the build path handed to the label lookup.
extern const char DAT_00833370[];

// Add the entry's display text to the list, with the entry itself as its item data.
static void AddOptionEntry(HWND list, OptionEntry_005FBF80* entry)
{
    const wchar_t* text = FUN_00734E60(entry->Label, 0, DAT_00833370, 0x4F1);
    unsigned int item = SendMessageA(list, 0x4CD, 0, (LPARAM)text);
    if (item != 0xFFFFFFFF) {
        SendMessageA(list, 0x19A, item, (LPARAM)entry);
    }
}

// FUNCTION: GAMEMD 0x5FC000
// Fill the movie list: the intro movie, then each campaign table up to the furthest entry unlocked.
void Obj_005FBF80::FUN_005FC000(HWND list)
{
    if (DAT_00832C20.Name != 0 && DAT_00832C20.Label != 0) {
        AddOptionEntry(list, &DAT_00832C20);
    }
    if (unknown_4C >= 0) {
        OptionEntry_005FBF80* entry = DAT_00832CA0;
        for (int count = unknown_4C + 1; entry->Name != 0 && count > 0; count--, entry++) {
            if (entry->Name != 0 && entry->Label != 0) {
                AddOptionEntry(list, entry);
            }
        }
    }
    if (unknown_50 >= 0) {
        OptionEntry_005FBF80* entry = DAT_00832C30;
        for (int count = unknown_50 + 1; entry->Name != 0 && count > 0; count--, entry++) {
            if (entry->Name != 0 && entry->Label != 0) {
                AddOptionEntry(list, entry);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log (format, args...).
void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x407150 (decl; reloc) -- set a channel's volume (fastcall: channel, value).
struct Obj_00401000;


// FUNCTION: GAMEMD 0x752AB0 (decl; reloc) -- set the global voice level.
void __fastcall FUN_00752AB0(int level);

// Score jukebox object at 0xA83D10; its level setter is 0x721290.
struct ScoreJukebox_00721290
{
    // FUNCTION: GAMEMD 0x721290 (decl; reloc)
    void FUN_00721290(int level);
};

// GLOBAL: GAMEMD 0xA83D10
extern ScoreJukebox_00721290 DAT_00A83D10;
// GLOBAL: GAMEMD 0x87E740 -- voice channel.
extern Obj_00401000* DAT_0087E740;
// GLOBAL: GAMEMD 0x87E744 -- score channel.
extern Obj_00401000* DAT_0087E744;
// GLOBAL: GAMEMD 0x87E748 -- sound channel.
extern Obj_00401000* DAT_0087E748;

// GLOBAL: GAMEMD 0x7E1718 -- 1.0.
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EAA50 -- level scale (double).
extern const double DAT_007EAA50;

// STRING: GAMEMD 0x832F9C -- "ScoreVolume = %f\n"
extern char STR_00832F9C[];
// STRING: GAMEMD 0x832FB0 -- "SoundVolume = %f\n"
extern char STR_00832FB0[];
// STRING: GAMEMD 0x832FC4 -- "VoiceVolume = %f\n"
extern char STR_00832FC4[];

// GLOBAL: GAMEMD 0x8871E0 -- rules.
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// VocClass::PlayGlobal 0x750920, called with a sound index, pan and volume.
#include "../audio/voc_class_play_global_methods.h"

// FUNCTION: GAMEMD 0x5FA4A0
// Clamp and store the score volume, push it to the score channel and the jukebox, log it.
void GameOptionsClass::SetScoreVolume(float volume, bool unused)
{
    ScoreVolume = volume < DAT_007E1718 ? volume : DAT_007E1718;
    FUN_00407150(&DAT_0087E744->First, (int)(ScoreVolume * 16384.0f));
    DAT_00A83D10.FUN_00721290((int)(ScoreVolume * DAT_007EAA50));
    FUN_004068E0(STR_00832F9C, (double)ScoreVolume);
}

// FUNCTION: GAMEMD 0x5FA510
// Clamp and store the sound volume, push it to the sound channel, play the feedback sample, log it.
void GameOptionsClass::SetSoundVolume(float volume, bool playSample)
{
    SoundVolume = volume < DAT_007E1718 ? volume : DAT_007E1718;
    FUN_00407150(&DAT_0087E748->First, (int)(SoundVolume * 16384.0f));
    if (playSample)
        VocClass::PlayGlobal(DAT_008871E0->GenericBeep, 1.0f, 0x2000, 0);
    FUN_004068E0(STR_00832FB0, (double)SoundVolume);
}

// FUNCTION: GAMEMD 0x5FA590
// Clamp and store the voice volume, push it to the voice level and channel, play the feedback sample, log it.
void GameOptionsClass::SetVoiceVolume(float volume, bool playSample)
{
    VoiceVolume = volume < DAT_007E1718 ? volume : DAT_007E1718;
    FUN_00752AB0((int)(VoiceVolume * DAT_007EAA50));
    FUN_00407150(&DAT_0087E740->First, (int)(VoiceVolume * 16384.0f));
    if (playSample)
        VocClass::PlayGlobal(DAT_008871E0->GenericBeep, VoiceVolume, 0x2000, 0);
    FUN_004068E0(STR_00832FC4, (double)VoiceVolume);
}

// The options INI object (the settings file the game reads at start-up).
#include "../platform/ccini_class_methods.h"
// GLOBAL: GAMEMD 0x8870C0 -- the options INI.
extern CCINIClass DAT_008870C0;
// GLOBAL: GAMEMD 0xA83D20 -- score repeat flag mirrored for the jukebox.
extern bool DAT_00A83D20;
// GLOBAL: GAMEMD 0xA83D22 -- score shuffle flag mirrored for the jukebox.
extern bool DAT_00A83D22;
// GLOBAL: GAMEMD 0xA8ED63 -- mode toggle flag.
extern bool DAT_00A8ED63;
// GLOBAL: GAMEMD 0x8A0DEE -- movie stretch capability.
extern bool DAT_008A0DEE;
// GLOBAL: GAMEMD 0x887734 -- the empty wide string.
extern const wchar_t DAT_00887734[];
// STRING: GAMEMD 0x82083C -- the wide separator " " (the int 0x20 read as a wide string).
extern const wchar_t STR_0082083C[];
// STRING: GAMEMD 0x889F64 -- the shared empty default text.
extern const char STR_00889F64[];
// LIBRARY: GAMEMD 0x7CB911 (decl; reloc) -- CRT wide string tokeniser.
wchar_t* __cdecl FUN_007CB911(wchar_t* string, const wchar_t* separators);
// LIBRARY: GAMEMD 0x7CB9B8 (decl; reloc) -- CRT wide string to long.
long __cdecl FUN_007CB9B8(const wchar_t* string, wchar_t** end, int radix);
// The side bar object at 0x87F7E8; its 0x6A4FF0 takes the cameo text flag.
struct Sidebar_0087F7E8
{
    // FUNCTION: GAMEMD 0x6A4FF0 (decl; reloc)
    void FUN_006A4FF0(bool cameoText);
};
// GLOBAL: GAMEMD 0x87F7E8
extern Sidebar_0087F7E8 DAT_0087F7E8;
// FUNCTION: GAMEMD 0x70D180 (decl; reloc) -- __fastcall, one byte flag.
void __fastcall FUN_0070D180(bool flag);

// FUNCTION: GAMEMD 0x5FA620
// Reads the [Options], [Video], [Audio] and [Network] settings from the options INI, clamping and
// logging each one, applies the volumes through the setters, then finishes through 0x5FB050.
void GameOptionsClass::FUN_005FA620()
{
    wchar_t netId[200];

    FUN_004068E0("--------- Loading SUN.INI settings ---------------\n");
    GameSpeed = DAT_008870C0.ReadInteger("Options", "GameSpeed", GameSpeed);
    FUN_004068E0("GameSpeed = %d\n", GameSpeed);
    Difficulty = DAT_008870C0.ReadInteger("Options", "Difficulty", Difficulty);
    Difficulty = Difficulty < 4 ? Difficulty : 4;
    Difficulty = Difficulty > 0 ? Difficulty : 0;
    FUN_004068E0("Difficulty = %d\n", Difficulty);
    CampDifficulty = DAT_008870C0.ReadInteger("Options", "CampDifficulty", CampDifficulty);
    CampDifficulty = CampDifficulty < 2 ? CampDifficulty : 2;
    CampDifficulty = CampDifficulty > 0 ? CampDifficulty : 0;
    FUN_004068E0("CampDifficulty = %d\n", CampDifficulty);
    ScrollMethod = DAT_008870C0.ReadInteger("Options", "ScrollMethod", ScrollMethod);
    FUN_004068E0("ScrollMethod = %d\n", ScrollMethod);
    ScrollRate = DAT_008870C0.ReadInteger("Options", "ScrollRate", ScrollRate);
    FUN_004068E0("ScrollRate = %d\n", ScrollRate);
    AutoScroll = DAT_008870C0.ReadBool("Options", "AutoScroll", AutoScroll);
    FUN_004068E0("AutoScroll is %s\n", AutoScroll == true ? "ON" : "OFF");
    DetailLevel = DAT_008870C0.ReadInteger("Options", "DetailLevel", DetailLevel);
    DetailLevel = DetailLevel < 2 ? DetailLevel : 2;
    DetailLevel = DetailLevel > 0 ? DetailLevel : 0;
    FUN_004068E0("DetailLevel = %d\n", DetailLevel);
    SidebarOnRight = true;
    FUN_004068E0("SideBar on %s\n", "RIGHT");
    SidebarCameoText = DAT_008870C0.ReadBool("Options", "SidebarCameoText", SidebarCameoText);
    FUN_004068E0("Sidebar Text is %s\n", SidebarCameoText == true ? "ON" : "OFF");
    UnitActionLines = DAT_008870C0.ReadBool("Options", "UnitActionLines", UnitActionLines);
    FUN_004068E0("ActionLines are %s\n", UnitActionLines == true ? "ON" : "OFF");
    ShowHidden = DAT_008870C0.ReadBool("Options", "ShowHidden", ShowHidden);
    FUN_004068E0("ShowHidden is %s\n", ShowHidden == true ? "ON" : "OFF");
    ToolTips = DAT_008870C0.ReadBool("Options", "ToolTips", ToolTips);
    FUN_004068E0("ToolTips are %s\n", ToolTips == true ? "ON" : "OFF");
    ScreenWidth = DAT_008870C0.ReadInteger("Video", "ScreenWidth", ScreenWidth);
    ScreenHeight = DAT_008870C0.ReadInteger("Video", "ScreenHeight", ScreenHeight);
    FUN_004068E0("Resolution = %d X %d\n", ScreenWidth, ScreenHeight);
    StretchMovies = DAT_008870C0.ReadBool("Video", "StretchMovies", StretchMovies);
    StretchMovies = StretchMovies == true && DAT_008A0DEE == true;
    FUN_004068E0("StretchMovies is %s\n", StretchMovies == true ? "ON" : "OFF");
    AllowHiResModes = DAT_008870C0.ReadBool("Video", "AllowHiResModes", AllowHiResModes);
    FUN_004068E0("AllowHiRes is %s\n", AllowHiResModes == true ? "ON" : "OFF");
    DAT_00A8ED63 = DAT_008870C0.ReadBool("Video", "AllowModeToggle", DAT_00A8ED63);
    AllowVRAMSidebar = DAT_008870C0.ReadBool("Video", "AllowVRAMSidebar", AllowVRAMSidebar);
    SetSoundVolume((float)DAT_008870C0.ReadDouble("Audio", "SoundVolume", SoundVolume), false);
    SetVoiceVolume((float)DAT_008870C0.ReadDouble("Audio", "VoiceVolume", VoiceVolume), false);
    SetScoreVolume((float)DAT_008870C0.ReadDouble("Audio", "ScoreVolume", ScoreVolume), false);
    DAT_00A83D20 = IsScoreRepeat = DAT_008870C0.ReadBool("Audio", "IsScoreRepeat", IsScoreRepeat);
    FUN_004068E0("ScoreRepeat is %s\n", IsScoreRepeat == true ? "ON" : "OFF");
    DAT_00A83D22 = IsScoreShuffle = DAT_008870C0.ReadBool("Audio", "IsScoreShuffle", IsScoreShuffle);
    FUN_004068E0("ScoreShuffle is %s\n", IsScoreShuffle == true ? "ON" : "OFF");
    InGameMusic = DAT_008870C0.ReadBool("Audio", "InGameMusic", InGameMusic);
    NetID[0] = -1;
    NetID[1] = -1;
    DAT_008870C0.FUN_00528F00("Network", "NetID", DAT_00887734, netId, 200);
    if (netId[0] != 0) {
        wchar_t* character = netId;
        do {
            *character = ~*character;
            if (*character == 0)
                *character = 0xFFFF;
            character++;
        } while (*character != 0);
        wchar_t* token = FUN_007CB911(netId, STR_0082083C);
        if (token != 0) {
            NetID[0] = FUN_007CB9B8(token, 0, 10) - 1;
            token = FUN_007CB911(0, STR_0082083C);
            if (token != 0)
                NetID[1] = FUN_007CB9B8(token, 0, 10) - 1;
        }
    }
    if (NetID[0] < -1 || NetID[0] >= 8)
        NetID[0] = -1;
    if (NetID[1] < -1 || NetID[1] >= 8)
        NetID[1] = -1;
    SoundLatency = DAT_008870C0.ReadInteger("Audio", "SoundLatency", SoundLatency);
    FUN_004068E0("Emulated sound card latency default = %d\n", SoundLatency);
    Socket = DAT_008870C0.ReadInteger("Network", "Socket", Socket);
    NetCard = DAT_008870C0.ReadInteger("Network", "NetCard", NetCard);
    DAT_008870C0.ReadString("Network", "DestNet", STR_00889F64, DestNet, 0x40);
    FUN_004068E0("--------- Complete -------------------------------\n");
    DAT_0087F7E8.FUN_006A4FF0(SidebarCameoText);
    FUN_0070D180(UnitActionLines);
    FUN_005FB050();
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EAA50
extern const double DAT_007EAA50 = 255.0;
// GLOBAL: GAMEMD 0x7EF378
extern const double DAT_007EF378 = 60.0;
// GLOBAL: GAMEMD 0x833370
extern const char DAT_00833370[] = "D:\\ra2mdpost\\Options.CPP";
// END defined globals
