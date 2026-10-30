// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small functions read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. Receivers are placeholder views named after their address.
//   Address index: 0x6E8180, 0x718090, 0x747370, 0x75A810, 0x7B6630.

#include <string.h>

// ---------------------------------------------------------------------------
// 0x6E8180: the item of a named array whose name (at +0x24) matches, else null.
struct Named_006E8180
{
    char unknown_00[0x24];
    char Name[1];   // +0x24
};
// GLOBAL: GAMEMD 0xA8E8D4 / 0xA8E8E0 -- the array's items and count.
extern Named_006E8180** DAT_00A8E8D4;
extern int DAT_00A8E8E0;

// FUNCTION: GAMEMD 0x6E8180
Named_006E8180* __fastcall FUN_006E8180(const char* name)
{
    if (name) {
        for (int i = 0; i < DAT_00A8E8E0; i++) {
            if (_stricmp(name, DAT_00A8E8D4[i]->Name) == 0)
                return DAT_00A8E8D4[i];
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x747370: the index of the item of a named array whose name (at +0x24) matches, else -1.
struct Named_00747370
{
    char unknown_00[0x24];
    char Name[1];   // +0x24
};
// GLOBAL: GAMEMD 0xA83CE4 / 0xA83CF0 -- the array's items and count.
extern Named_00747370** DAT_00A83CE4;
extern int DAT_00A83CF0;

// FUNCTION: GAMEMD 0x747370
int __fastcall FUN_00747370(const char* name)
{
    if (name) {
        for (int i = 0; i < DAT_00A83CF0; i++) {
            if (_stricmp(DAT_00A83CE4[i]->Name, name) == 0)
                return i;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x718090: whether the embedded COM step refuses the request (slot 4, `this` pushed).
class Step_00718090
{
public:
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual bool __stdcall Refuses();
};
struct Loco_00718090
{
    int unknown_00;
    Step_00718090 Step;   // +0x04
    bool Refuse();        // 0x718090
};

// FUNCTION: GAMEMD 0x718090
bool Loco_00718090::Refuse()
{
    return Step.Refuses() ? false : true;
}

// ---------------------------------------------------------------------------
// 0x75A810: whether a bit of the array at 0xB45BA8 is set.
// GLOBAL: GAMEMD 0xB45BA8
extern unsigned char DAT_00B45BA8[];

// FUNCTION: GAMEMD 0x75A810
bool __fastcall FUN_0075A810(int bit)
{
    unsigned char mask = 1 << ((char)bit & 7);
    return (DAT_00B45BA8[bit >> 3] & mask) ? true : false;
}

// ---------------------------------------------------------------------------
// 0x7B6630: whether the string holds any of the given characters.
// FUNCTION: GAMEMD 0x7CD790 (decl; reloc) -- strcspn.
unsigned int __cdecl FUN_007CD790(const char* s, const char* set);

struct Str_007B6630
{
    const char* Text;
    bool HasAnyOf(const char* set);   // 0x7B6630
};

// FUNCTION: GAMEMD 0x7B6630
bool Str_007B6630::HasAnyOf(const char* set)
{
    if (set && Text) {
        const char* t = Text;
        unsigned int len = strlen(t);
        return FUN_007CD790(t, set) < len;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83CF0
int DAT_00A83CF0;
// GLOBAL: GAMEMD 0xA8E8D4
Named_006E8180** DAT_00A8E8D4;
// GLOBAL: GAMEMD 0xA8E8E0
int DAT_00A8E8E0;
// GLOBAL: GAMEMD 0xA83CE4
Named_00747370** DAT_00A83CE4;
// END defined globals
