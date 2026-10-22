// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Class names from the retail RTTI, read off the user's gamemd.exe v1.001
//   with `ghidra memory read` through each vtable's locator:
//     0x7EE124 -> `.?AVMovieHandle@@`     (11 slots, slots 1-10 _purecall)
//     0x7EE0F4 -> `.?AVVQMovieHandle@@`
//     0x7EE154 -> `.?AVBinkMovieHandle@@`
//   Slot shapes come from the RET n and argument reads of the two leaf
//   tables; no slot is named by a string, so they keep placeholders.
//   Field offsets from the constructors 0x5C0240 (VQ), 0x5C0510 (Bink) and
//   the VQ state block's constructor/destructor 0x5C01A0/0x5C01F0.
#ifndef GG_MATCH_PLATFORM_MOVIE_HANDLE_CLASS_H
#define GG_MATCH_PLATFORM_MOVIE_HANDLE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/geometry2d.h"

// The VQ player object owned by the state block (+0x00). Only the calls the
// movie code makes are declared; each is a __thiscall body elsewhere.
struct Obj_00759510
{
    ~Obj_00759510();                    // GAMEMD 0x759510 (decl; reloc)
    bool FUN_00759C30(void* rect);      // GAMEMD 0x759C30 (decl; reloc)
    void FUN_00759E10();                // GAMEMD 0x759E10 (decl; reloc)
    void FUN_00759E50();                // GAMEMD 0x759E50 (decl; reloc)
    void FUN_00759E60();                // GAMEMD 0x759E60 (decl; reloc)
    void FUN_00759E80();                // GAMEMD 0x759E80 (decl; reloc)
    void FUN_007598D0(int a);           // GAMEMD 0x7598D0 (decl; reloc)
    void FUN_00759EB0(int a, int b);    // GAMEMD 0x759EB0 (decl; reloc)
    int  FUN_00759F70();                // GAMEMD 0x759F70 (decl; reloc)
    int  FUN_00759F80();                // GAMEMD 0x759F80 (decl; reloc)
    char _pad000[0x550];
    bool unknown_550;                   // +0x550
};
GG_STATIC_ASSERT(offsetof(Obj_00759510, unknown_550) == 0x550);

// The helper at +0x48 of the state block.
struct Obj_006C9AE0
{
    ~Obj_006C9AE0();                    // GAMEMD 0x6C9AE0 (decl; reloc)
    void FUN_006C9D30(void* callback);  // GAMEMD 0x6C9D30 (decl; reloc)
    int   unknown_00;                   // +0x00
    char  _pad04[0x0C];                 // +0x04
    void* unknown_10;                   // +0x10  a surface
};
GG_STATIC_ASSERT(offsetof(Obj_006C9AE0, unknown_10) == 0x10);


// The VQ state block a VQMovieHandle points at (+0x10); 0x4C bytes.
struct Obj_005C01A0
{
    Obj_005C01A0();                     // GAMEMD 0x5C01A0
    ~Obj_005C01A0();                    // GAMEMD 0x5C01F0

    Obj_00759510* Player;   // +0x00
    int  unknown_04;        // +0x04
    void* unknown_08;       // +0x08
    int  unknown_0C;        // +0x0C
    int  unknown_10;        // +0x10
    int  unknown_14;        // +0x14
    int  unknown_18;        // +0x18
    int  unknown_1C;        // +0x1C
    int  unknown_20;        // +0x20
    RectangleStruct unknown_24;   // +0x24
    RectangleStruct unknown_34;   // +0x34
    bool unknown_44;        // +0x44
    bool unknown_45;        // +0x45
    Obj_006C9AE0* unknown_48;   // +0x48
};
GG_STATIC_ASSERT(offsetof(Obj_005C01A0, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_005C01A0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_005C01A0, unknown_45) == 0x45);
GG_STATIC_ASSERT(offsetof(Obj_005C01A0, unknown_48) == 0x48);
GG_STATIC_ASSERT(sizeof(Obj_005C01A0) == 0x4C);

// Release what the state block holds; null-safe (0x5BFF00).
inline void Release_005BFF00(Obj_005C01A0* data)
{
    if (data != 0) {
        if (data->Player != 0) {
            data->Player->FUN_00759E60();
            delete data->Player;
            data->Player = 0;
        }
        if (data->unknown_48 != 0) {
            delete data->unknown_48;
            data->unknown_48 = 0;
        }
        data->unknown_45 = false;
    }
}

// VTABLE: GAMEMD 0x7EE124
class MovieHandle
{
public:
    virtual ~MovieHandle();
    virtual bool vt_entry_04() = 0;
    virtual void vt_entry_08() = 0;
    virtual void vt_entry_0C(bool a) = 0;
    virtual void vt_entry_10() = 0;
    virtual bool vt_entry_14() = 0;
    virtual void vt_entry_18(int a, int b) = 0;
    virtual void vt_entry_1C(int a) = 0;
    virtual void vt_entry_20(void* a) = 0;
    virtual int  vt_entry_24() = 0;
    virtual void vt_entry_28() = 0;

    bool unknown_04;        // +0x04
    int  unknown_08;        // +0x08
    int  unknown_0C;        // +0x0C
};
GG_STATIC_ASSERT(offsetof(MovieHandle, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(MovieHandle, unknown_0C) == 0x0C);

// VTABLE: GAMEMD 0x7EE0F4
class VQMovieHandle : public MovieHandle
{
public:
    VQMovieHandle(Obj_005C01A0* data);
    virtual ~VQMovieHandle();
    virtual bool vt_entry_04();
    virtual void vt_entry_08();
    virtual void vt_entry_0C(bool a);
    virtual void vt_entry_10();
    virtual bool vt_entry_14();
    virtual void vt_entry_18(int a, int b);
    virtual void vt_entry_1C(int a);
    virtual void vt_entry_20(void* a);
    virtual int  vt_entry_24();
    virtual void vt_entry_28();

    Obj_005C01A0* Data;     // +0x10
    bool unknown_14;        // +0x14
};
GG_STATIC_ASSERT(offsetof(VQMovieHandle, Data) == 0x10);
GG_STATIC_ASSERT(offsetof(VQMovieHandle, unknown_14) == 0x14);

// The Bink player a BinkMovieHandle forwards to (match/platform/
// bink_player_teardown_methods.h models its teardown).
struct BinkInfo_005C0510
{
    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
};
struct Obj_00432700
{
    Obj_00432700(const char* name);                  // GAMEMD 0x432690 (decl; reloc)
    Obj_00432700(const char* name, void* surface);   // GAMEMD 0x4326C0 (decl; reloc)
    ~Obj_00432700();                       // GAMEMD 0x432700 (decl; reloc)
    void FUN_00432AB0(int a, int b);       // GAMEMD 0x432AB0 (decl; reloc)
    void FUN_00432BD0(int a);              // GAMEMD 0x432BD0 (decl; reloc)
    int  FUN_00432BF0();                   // GAMEMD 0x432BF0 (decl; reloc)
    void FUN_00432C10(void* a);            // GAMEMD 0x432C10 (decl; reloc)
    void FUN_00432C30(bool a);             // GAMEMD 0x432C30 (decl; reloc)
    bool FUN_00432C50();                   // GAMEMD 0x432C50 (decl; reloc)
    void FUN_00432C70();                   // GAMEMD 0x432C70 (decl; reloc)
    void FUN_00433020();                   // GAMEMD 0x433020 (decl; reloc)
    bool FUN_00433040();                   // GAMEMD 0x433040 (decl; reloc)
    void FUN_00433060();                   // GAMEMD 0x433060 (decl; reloc)
    bool unknown_00;                       // +0x00
    char _pad01[3];                        // +0x01
    BinkInfo_005C0510* Info;               // +0x04
    char _pad08[0x34 - 0x08];              // +0x08
};
GG_STATIC_ASSERT(offsetof(Obj_00432700, Info) == 0x04);
GG_STATIC_ASSERT(sizeof(Obj_00432700) == 0x34);   // `PUSH 0x34` at 0x5C0862

// VTABLE: GAMEMD 0x7EE154
class BinkMovieHandle : public MovieHandle
{
public:
    BinkMovieHandle(Obj_00432700* player);
    virtual ~BinkMovieHandle();
    virtual bool vt_entry_04();
    virtual void vt_entry_08();
    virtual void vt_entry_0C(bool a);
    virtual void vt_entry_10();
    virtual bool vt_entry_14();
    virtual void vt_entry_18(int a, int b);
    virtual void vt_entry_1C(int a);
    virtual void vt_entry_20(void* a);
    virtual int  vt_entry_24();
    virtual void vt_entry_28();

    Obj_00432700* Player;   // +0x10
};
GG_STATIC_ASSERT(offsetof(BinkMovieHandle, Player) == 0x10);

#endif  // GG_MATCH_PLATFORM_MOVIE_HANDLE_CLASS_H
