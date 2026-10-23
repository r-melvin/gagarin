// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 (Ghidra CLI
//   disassembly from each entry) in the retail block 0x5BED20..0x5BF5BF: the
//   movie playback entry points. Play_Movie is named by its own debug string
//   at 0x82D9B4 ("Play_Movie() as Bink!\n"); everything else is a placeholder.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// /Ob2: the two sound/pause helpers 0x5BF530 and 0x5BF580 are called from
// other units yet expanded inside 0x5BF180 and 0x5BF450, and 0x5BF2B0 is
// expanded inside 0x5BF390: out-of-line bodies inlined automatically.
#include "movie_handle_class.h"
#include "../core/vector_class_operations.h"
#include <string.h>

// LIBRARY: GAMEMD 0x7C8D20 -- _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
void __cdecl FUN_004068E0(const char* format, ...);

// The mouse singleton at 0x887640: slot +0x0C hides, +0x10 shows.
struct Mouse_005BED40
{
    virtual void vt_00(); virtual void vt_04(); virtual void vt_08();
    virtual void vt_0C();
    virtual void vt_10();
};
// GLOBAL: GAMEMD 0x887640
extern Mouse_005BED40* DAT_00887640;

class GScreenClass
{
public:
    void FlagToRedraw(int which);       // GAMEMD 0x4F42F0 (decl; reloc)
};
// GLOBAL: GAMEMD 0x87F7E8
extern GScreenClass DAT_0087F7E8;

// GLOBAL: GAMEMD 0x887310
extern void* DAT_00887310;
// GLOBAL: GAMEMD 0xA8EB94
extern bool DAT_00A8EB94;
// GLOBAL: GAMEMD 0xA8EB9C
extern float DAT_00A8EB9C;
// GLOBAL: GAMEMD 0x8A0DEE
extern bool DAT_008A0DEE;
// GLOBAL: GAMEMD 0x886FB8
extern int DAT_00886FB8;
// GLOBAL: GAMEMD 0x886FBC
extern int DAT_00886FBC;

void FUN_00406EA0();                                     // GAMEMD 0x406EA0 (decl; reloc)
void FUN_00406EC0();                                     // GAMEMD 0x406EC0 (decl; reloc)
void FUN_0040A850();                                     // GAMEMD 0x40A850 (decl; reloc)
void FUN_0040A7C0(int rate, int bits, int channels);   // GAMEMD 0x40A7C0 (decl; reloc)
bool FUN_005C0640(const char* name, char* out, int unused);   // GAMEMD 0x5C0640 (decl; reloc)
Obj_005C01A0* FUN_005BFAA0(const char* name, void* surface,
                           RectangleStruct a, RectangleStruct b, int c, int d);   // GAMEMD 0x5BFAA0 (decl; reloc)
void FUN_005BFF00(Obj_005C01A0* data);        // GAMEMD 0x5BFF00 (decl; reloc)
void FUN_005BFF60(Obj_005C01A0* data, bool a, int b, int c);   // GAMEMD 0x5BFF60 (decl; reloc)
void FUN_005BF530();
void FUN_005BF580();

// The surfaces these entry points draw on: only slot +0x18 is called.
struct Surface_005BF180
{
    virtual void vt_00(); virtual void vt_04(); virtual void vt_08(); virtual void vt_0C();
    virtual void vt_10(); virtual void vt_14();
    virtual void vt_18(int a);
};

struct InputManagerClass
{
    void DoSomething();                 // GAMEMD 0x54F720 (decl; reloc)
};

// The object the movie callback posts to (0xA8BC60).
struct Obj_005D3BA0
{
    void FUN_005D3BA0(int a, int b, int c, int d, int e, int f, int g);   // GAMEMD 0x5D3BA0 (decl; reloc)
};

// The argument the movie callback receives.
struct Obj_005BF360
{
    int _pad00;          // +0x00
    int unknown_04;      // +0x04
    char _pad08[0x0C];   // +0x08
    int unknown_14;      // +0x14
};

// GLOBAL: GAMEMD 0xABF35C -- set while playback has the sound/scroll state paused.
extern bool DAT_00ABF35C;
// GLOBAL: GAMEMD 0xABF394 -- movie name table.
extern char** DAT_00ABF394;
// GLOBAL: GAMEMD 0xABF3A0 -- its entry count.
extern int DAT_00ABF3A0;
// GLOBAL: GAMEMD 0xA8E378
extern bool DAT_00A8E378;
// GLOBAL: GAMEMD 0xA8B238 -- the session game mode (0 = campaign).
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0x887300
extern void* DAT_00887300;
// GLOBAL: GAMEMD 0x88730C
extern Surface_005BF180* DAT_0088730C;
// GLOBAL: GAMEMD 0x8809D8
extern int DAT_008809D8;
// GLOBAL: GAMEMD 0x8809DC
extern int DAT_008809DC;
// GLOBAL: GAMEMD 0x87F770
extern InputManagerClass* DAT_0087F770;
// GLOBAL: GAMEMD 0x87E750
extern void* DAT_0087E750;
// GLOBAL: GAMEMD 0x87E758
extern void* DAT_0087E758;
// GLOBAL: GAMEMD 0xA8BC60
extern Obj_005D3BA0 DAT_00A8BC60;
// GLOBAL: GAMEMD 0xB45B58 -- the movie handles started by 0x5BF2B0.
extern DynamicVectorClass<MovieHandle*> DAT_00B45B58;

void FUN_00408200();                                     // GAMEMD 0x408200 (decl; reloc)
void FUN_00408230();                                     // GAMEMD 0x408230 (decl; reloc)
void FUN_00408270();                                     // GAMEMD 0x408270 (decl; reloc)
void FUN_004082F0();                                     // GAMEMD 0x4082F0 (decl; reloc)
void FUN_004083D0();                                     // GAMEMD 0x4083D0 (decl; reloc)
void FUN_007535B0();                                     // GAMEMD 0x7535B0 (decl; reloc)
void FUN_00753620();                                     // GAMEMD 0x753620 (decl; reloc)
void FUN_00407170(void* obj, int flag);       // GAMEMD 0x407170 (decl; reloc)
void FUN_004F4780(bool a, void* surface, int b);   // GAMEMD 0x4F4780 (decl; reloc)
MovieHandle* FUN_005C07D0(const char* name, void* surface, int a);   // GAMEMD 0x5C07D0 (decl; reloc)
void Play_Movie(const char* name, int x, int a, int b, int c, int d);

// FUNCTION: GAMEMD 0x5BED20
void FUN_005BED20(const char* name, int x, int a, int b, int c)
{
    Play_Movie(name, x, a, b, c, 1);
}

// FUNCTION: GAMEMD 0x5BED40
// PARTIAL (9.6% positional, 90.1% aligned): one attempt. cl keeps the
// constant 1 in ESI from the first call on, which shifts the register
// assignment of the whole body.
// Play a movie by name, full screen: Bink files through a local Bink player,
// everything else through a VQ state block (stretched to the screen when
// the options ask for it).
void Play_Movie(const char* name, int x, int a, int b, int c, int d)
{
    char buffer[256];
    if (!FUN_005C0640(name, buffer, true) || DAT_00A8B238 != 0)
        return;
    DAT_0087F770->DoSomething();
    char* ext = strrchr(buffer, '.');
    if (ext != 0 && _stricmp(ext, ".bik") == 0) {
        FUN_004068E0("Play_Movie() as Bink!\n");
        DAT_00887640->vt_0C();
        if (c != 0) {
            DAT_0088730C->vt_18(0);
            FUN_004F4780(true, DAT_0088730C, 0);
        }
        Obj_00432700 player(buffer);
        if (d == 1)
            player.unknown_00 = true;
        FUN_005BF580();
        FUN_00406EA0();
        FUN_0040A7C0(0xAC44, 0x10, 2);
        player.FUN_00432C70();
        FUN_0040A850();
        FUN_00406EC0();
        FUN_005BF530();
        if (a == 1) {
            DAT_0088730C->vt_18(0);
            FUN_004F4780(true, DAT_0088730C, 0);
        }
        DAT_0087F770->DoSomething();
        DAT_00887640->vt_10();
        DAT_0087F7E8.FlagToRedraw(2);
        return;
    }
    DAT_0087F770->DoSomething();
    RectangleStruct none;
    none.X = 0;
    none.Y = 0;
    none.Width = 0;
    none.Height = 0;
    RectangleStruct area;
    area.X = 0;
    area.Y = 0;
    area.Width = 0;
    area.Height = 0;
    Obj_005C01A0* data = FUN_005BFAA0(buffer, DAT_00887310, none, area,
                                      (int)(DAT_00A8EB9C * 255.0), 1);
    if (data == 0)
        return;
    if (data->Player->FUN_00759F70() < 320 && data->Player->FUN_00759F80() < 200) {
        FUN_005BFF00(data);
        delete data;
        return;
    }
    bool stretch = b == 1 && DAT_00A8EB94 == true;
    if (DAT_008A0DEE == true && stretch == true) {
        int width = data->unknown_24.Width;
        if (width < DAT_00886FB8) {
            int height = data->unknown_24.Height;
            if (height < DAT_00886FBC) {
                data->unknown_34.Width = DAT_00886FB8;
                int newHeight = (int)(height * ((double)DAT_00886FB8 / width));
                data->unknown_34.X = 0;
                data->unknown_34.Height = newHeight;
                data->unknown_34.Y = (DAT_00886FBC - newHeight) / 2;
                FUN_004068E0("Stretching movie %dx%d -> %dx%d\n", width, height,
                             data->unknown_34.Width, newHeight);
            }
        }
    }
    DAT_00887640->vt_0C();
    if (c != 0) {
        DAT_0088730C->vt_18(0);
        FUN_004F4780(true, DAT_0088730C, 0);
    }
    FUN_005BF580();
    FUN_00406EA0();
    FUN_0040A7C0(0xAC44, 0x10, 2);
    FUN_005BFF60(data, true, x, 0);
    FUN_0040A850();
    FUN_00406EC0();
    FUN_005BF530();
    FUN_005BFF00(data);
    delete data;
    if (a == 1) {
        DAT_0088730C->vt_18(0);
        FUN_004F4780(true, DAT_0088730C, 0);
    }
    DAT_00887640->vt_10();
    DAT_0087F7E8.FlagToRedraw(2);
    DAT_0087F770->DoSomething();
}

// FUNCTION: GAMEMD 0x5BF530
void FUN_005BF530()
{
    if (DAT_00ABF35C) {
        FUN_00408230();
        FUN_004082F0();
        FUN_004083D0();
        FUN_00407170(DAT_0087E758, 0x4000);
        FUN_00407170(DAT_0087E750, 0x4000);
        FUN_00753620();
        DAT_00ABF35C = false;
    }
}

// FUNCTION: GAMEMD 0x5BF580
void FUN_005BF580()
{
    if (!DAT_00ABF35C) {
        FUN_007535B0();
        FUN_00408200();
        FUN_00408270();
        FUN_00407170(DAT_0087E758, 0x2000);
        FUN_00407170(DAT_0087E750, 0x2000);
        DAT_00ABF35C = true;
    }
}

// FUNCTION: GAMEMD 0x5BF180
void FUN_005BF180(const char* name)
{
    MovieHandle* movie = FUN_005C07D0(name, DAT_0088730C, 0);
    if (movie != 0) {
        DAT_0088730C->vt_18(0);
        FUN_004F4780(true, DAT_0088730C, 0);
        DAT_0087F770->DoSomething();
        FUN_005BF580();
        movie->vt_entry_10();
        FUN_005BF530();
        DAT_0087F770->DoSomething();
        delete movie;
    }
}

// FUNCTION: GAMEMD 0x5BF260
// The caller's EDX (always -1 at the call sites) is not read; Play_Movie
// gets its own -1.
void FUN_005BF260(int index, int unused, int a, int b, int c)
{
    if (index >= 0 && index < DAT_00ABF3A0) {
        bool saved = DAT_00A8E378;
        DAT_00A8E378 = false;
        Play_Movie(DAT_00ABF394[index], -1, a, b, c, 0);
        DAT_00A8E378 = saved;
    }
}

// FUNCTION: GAMEMD 0x5BF360
void FUN_005BF360(Obj_005BF360* arg)
{
    if (arg != 0)
        DAT_00A8BC60.FUN_005D3BA0(0, 0, arg->unknown_14, 0, 0x4046, arg->unknown_04, 0);
}

// FUNCTION: GAMEMD 0x5BF2B0
// PARTIAL (72.2%): the inlined DynamicVectorClass::AddItem differs from the
// canonical one in vector_class_operations.h -- retail adds Capacity to the
// increment (`ADD ECX,EAX`) and stores through `Items[Count++]` (MOV/INC),
// where the canonical body emits `ADD EAX,ECX` and LEA. Not rewritten here:
// the fix belongs in the shared header (see the packet notes).
void FUN_005BF2B0(const char* name, bool flag)
{
    if (DAT_00A8B238 == 0) {
        MovieHandle* movie = FUN_005C07D0(name, DAT_00887300, 0);
        if (movie != 0) {
            movie->vt_entry_18(DAT_008809D8 - 3, DAT_008809DC - 1);
            movie->vt_entry_20((void*)FUN_005BF360);
            movie->unknown_04 = flag;
            DAT_00B45B58.AddItem(movie);
        }
    }
}

// FUNCTION: GAMEMD 0x5BF390
// PARTIAL (68.3%): the inlined 0x5BF2B0 carries the same AddItem difference.
void FUN_005BF390(int index, bool flag)
{
    if (index >= 0 && index < DAT_00ABF3A0)
        FUN_005BF2B0(DAT_00ABF394[index], flag);
}

// FUNCTION: GAMEMD 0x5BF450
// PARTIAL (18.4%): retail tests each element twice (`CMP ECX,EBX` x2) and
// keeps Items in EAX across the loop. Tried: a named element (18.4%),
// indexing twice (18.4%).
void FUN_005BF450()
{
    for (int i = 0; i < DAT_00B45B58.Count; i++) {
        if (DAT_00B45B58.Items[i] != 0)
            delete DAT_00B45B58.Items[i];
    }
    DAT_00B45B58.Clear();
    FUN_005BF530();
}
