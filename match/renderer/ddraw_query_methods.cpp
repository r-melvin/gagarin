// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 0x4A45C0: with the DirectDraw object at 0x8A0094, fill a capability block
// whose first dword is 0x13C (`MOV [ESP],0x13C`) through COM slot +0x2C with
// a null second argument, format the dword at +0x40 of the block into a local
// 256-byte buffer with sprintf 0x7C8EF4 and the string at 0x81FE6C, and return
// that dword. The block sits at [ESP+0x00] and the text buffer at [ESP+0x13C]
// of a 0x23C-byte frame, which bounds the block at 0x13C bytes.
// 0x4A4830: poll COM slot +0x34 of the surface at 0x8A009C with argument 2
// until it returns 0 or 0x887601C2.
// The COM views below declare only the slots these bodies reach; names of
// the functions and globals are descriptive placeholders.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8EF4 (decl; reloc) -- CRT sprintf.
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

struct CapsBlock_004A45C0
{
    unsigned long Size;            // +0x00
    char          unknown_04[0x3C];
    unsigned long VideoMemoryFree; // +0x40
    char          unknown_44[0xF8];
};
GG_STATIC_ASSERT(offsetof(CapsBlock_004A45C0, VideoMemoryFree) == 0x40);
GG_STATIC_ASSERT(sizeof(CapsBlock_004A45C0) == 0x13C);

class DirectDrawView_008A0094
{
public:
    virtual long __stdcall unknown_slot00() = 0;
    virtual long __stdcall unknown_slot04() = 0;
    virtual long __stdcall unknown_slot08() = 0;
    virtual long __stdcall unknown_slot0C() = 0;
    virtual long __stdcall unknown_slot10() = 0;
    virtual long __stdcall unknown_slot14() = 0;
    virtual long __stdcall unknown_slot18() = 0;
    virtual long __stdcall unknown_slot1C() = 0;
    virtual long __stdcall unknown_slot20() = 0;
    virtual long __stdcall unknown_slot24() = 0;
    virtual long __stdcall unknown_slot28() = 0;
    virtual long __stdcall GetCaps(CapsBlock_004A45C0* driver, CapsBlock_004A45C0* emulated) = 0;   // +0x2C
};

class SurfaceView_008A009C
{
public:
    virtual long __stdcall unknown_slot00() = 0;
    virtual long __stdcall unknown_slot04() = 0;
    virtual long __stdcall unknown_slot08() = 0;
    virtual long __stdcall unknown_slot0C() = 0;
    virtual long __stdcall unknown_slot10() = 0;
    virtual long __stdcall unknown_slot14() = 0;
    virtual long __stdcall unknown_slot18() = 0;
    virtual long __stdcall unknown_slot1C() = 0;
    virtual long __stdcall unknown_slot20() = 0;
    virtual long __stdcall unknown_slot24() = 0;
    virtual long __stdcall unknown_slot28() = 0;
    virtual long __stdcall unknown_slot2C() = 0;
    virtual long __stdcall unknown_slot30() = 0;
    virtual long __stdcall GetStatus(unsigned long flags) = 0;   // +0x34
};

// GLOBAL: GAMEMD 0x8A0094
extern DirectDrawView_008A0094* DirectDraw_008A0094;
// GLOBAL: GAMEMD 0x8A009C
extern SurfaceView_008A009C* Surface_008A009C;

// FUNCTION: GAMEMD 0x4A45C0
unsigned long Get_Free_Video_Memory()
{
    if (DirectDraw_008A0094 != 0) {
        CapsBlock_004A45C0 caps;
        char text[256];
        caps.Size = sizeof(caps);
        if (DirectDraw_008A0094->GetCaps(&caps, 0) == 0) {
            // STRING: GAMEMD 0x81FE6C
            sprintf(text, "In Get_Free_Video_Memory. About to return %d bytes", caps.VideoMemoryFree);
            return caps.VideoMemoryFree;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4A4830
void FUN_004A4830()
{
    long result;
    do {
        result = Surface_008A009C->GetStatus(2);
    } while (result != 0 && result != (long)0x887601C2);
}
