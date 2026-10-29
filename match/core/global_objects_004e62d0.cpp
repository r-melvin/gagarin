// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Part of the unit at retail 0x4E62D0..0x4E8268 that defines many of the
// engine's global objects. Each definition below produces one compiler-
// generated run-time initialiser (and, for objects with destructors, the
// cleanup callback it registers through atexit 0x7C978A), in retail __xc order
// (0x8131C4..0x813320). The unit's other globals are not defined here yet.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT

#include <objbase.h>
#include "../_rt/gg_static_assert.h"
#include "header_tuning_globals.h"
#include "mission_class_methods.h"
#include "version_class_ctor_methods.h"
#include "../combat/random_straw.h"
#include "../ui/game_options_class_methods.h"
#include "../network/event_queue.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xA83D40
extern double DAT_00A83D40;
// GLOBAL: GAMEMD 0x7E9B50
const double DAT_007E9B50 = 60.0;

// SYNTHETIC: GAMEMD 0x4E6300
// GLOBAL: GAMEMD 0xA8EC98
double DAT_00A8EC98 = DAT_00A83D40 / DAT_007E9B50;
// SYNTHETIC: GAMEMD 0x4E6320
// GLOBAL: GAMEMD 0xA8EB58
double DAT_00A8EB58 = 1.0 / DAT_00A8EC98;
// SYNTHETIC: GAMEMD 0x4E64A0
// GLOBAL: GAMEMD 0xA8EC68
TuningCoordInit DAT_00A8EC68(128, 128, 0);

// ---- the COM class factory -------------------------------------------------------------------------------------------

// The process's class factory (RTTI at 0x7EA564's locator). Its constructor only
// installs the table; LockServer (slot 4) is defined here.
// VTABLE: GAMEMD 0x7EA564
class TiberianSunClassFactory : public IClassFactory
{
public:
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);                        // 0  0x429210
    virtual ULONG __stdcall AddRef();                                                          // 1  0x4E8240
    virtual ULONG __stdcall Release();                                                         // 2  0x4E8250
    virtual HRESULT __stdcall CreateInstance(IUnknown* outer, REFIID riid, void** ppv);        // 3  0x429270
    virtual HRESULT __stdcall LockServer(BOOL lock);                                           // 4  0x4E8260
};

// SYNTHETIC: GAMEMD 0x4E7CE0
// GLOBAL: GAMEMD 0xA8E8C8
TiberianSunClassFactory DAT_00A8E8C8;

// ---- an array of 32 records with an out-of-line constructor ----------------------------------------------------------

// SYNTHETIC: GAMEMD 0x4E7CF0
// GLOBAL: GAMEMD 0xA8E3A8
MissionControlClass DAT_00A8E3A8[32];

// ---- objects with destructors ----------------------------------------------------------------------------------------

// The random-number straw at 0xA8E7B0: built by 0x6616B0, torn down by 0x661700.
struct Straw_00A8E7B0 : RandomStraw
{
    Straw_00A8E7B0() { Construct(); }
    ~Straw_00A8E7B0() { Destruct(); }
};
// SYNTHETIC: GAMEMD 0x4E7D10
// SYNTHETIC: GAMEMD 0x4E7D30 -- atexit callback
// GLOBAL: GAMEMD 0xA8E7B0
Straw_00A8E7B0 DAT_00A8E7B0;

// SYNTHETIC: GAMEMD 0x4E7DC0
// SYNTHETIC: GAMEMD 0x4E7DE0 -- atexit callback
// GLOBAL: GAMEMD 0xA8ECE0
VersionClass DAT_00A8ECE0;

// Two cleared dwords with an out-of-line destructor 0x5F61A0.
struct Obj_00A8ECD8
{
    Obj_00A8ECD8() { unknown_00 = 0; unknown_04 = 0; }
    // FUNCTION: GAMEMD 0x5F61A0 (decl; reloc)
    ~Obj_00A8ECD8();
    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
};
// SYNTHETIC: GAMEMD 0x4E7DF0
// SYNTHETIC: GAMEMD 0x4E7E10 -- atexit callback
// GLOBAL: GAMEMD 0xA8ECD8
Obj_00A8ECD8 DAT_00A8ECD8;

// SYNTHETIC: GAMEMD 0x4E7E20
// GLOBAL: GAMEMD 0xA8EB60
GameOptionsClass DAT_00A8EB60;

struct Obj_00A83E18
{
    // FUNCTION: GAMEMD 0x4A2350 (decl; reloc)
    Obj_00A83E18();
};
// SYNTHETIC: GAMEMD 0x4E7E90
// GLOBAL: GAMEMD 0xA83E18
Obj_00A83E18 DAT_00A83E18;

// ---- the event queues ------------------------------------------------------------------------------------------------

// SYNTHETIC: GAMEMD 0x4E7EA0
// GLOBAL: GAMEMD 0xA802C8
EventQueue<128> DAT_00A802C8;
// SYNTHETIC: GAMEMD 0x4E7ED0
// GLOBAL: GAMEMD 0x8B41F8
EventQueue<0x4000> DAT_008B41F8;
// SYNTHETIC: GAMEMD 0x4E7F00
// GLOBAL: GAMEMD 0xA83ED0
EventQueue<256> DAT_00A83ED0;

// ---- more objects with destructors ----------------------------------------------------------------------------------

struct Obj_00A8B238
{
    // FUNCTION: GAMEMD 0x6970A0 (decl; reloc)
    Obj_00A8B238();
    // FUNCTION: GAMEMD 0x697840 (decl; reloc)
    ~Obj_00A8B238();
};
// SYNTHETIC: GAMEMD 0x4E8030
// SYNTHETIC: GAMEMD 0x4E8050 -- atexit callback
// GLOBAL: GAMEMD 0xA8B238
Obj_00A8B238 DAT_00A8B238;

struct Obj_00A8EA70
{
    // FUNCTION: GAMEMD 0x5F15C0 (decl; reloc) -- RET 0x10.
    Obj_00A8EA70(int a1, int a2, int a3, int a4);
    // FUNCTION: GAMEMD 0x5F1650 (decl; reloc)
    ~Obj_00A8EA70();
};
// SYNTHETIC: GAMEMD 0x4E8060
// SYNTHETIC: GAMEMD 0x4E8090 -- atexit callback
// GLOBAL: GAMEMD 0xA8EA70
Obj_00A8EA70 DAT_00A8EA70(16, 16, 0xEC, 0x1234);

// The IPX connection manager (IPXManagerClass, connman_class.h): constructor 0x5408F0, destructor 0x5409F0.
struct IPXManager_00A8E9C0
{
    // FUNCTION: GAMEMD 0x5408F0 (decl; reloc)
    IPXManager_00A8E9C0(int a1, int a2, int a3, int a4, int a5, int a6);
    // FUNCTION: GAMEMD 0x5409F0 (decl; reloc)
    ~IPXManager_00A8E9C0();
};
// SYNTHETIC: GAMEMD 0x4E80A0
// SYNTHETIC: GAMEMD 0x4E80E0 -- atexit callback
// GLOBAL: GAMEMD 0xA8E9C0
IPXManager_00A8E9C0 DAT_00A8E9C0(0x1C7, 0x22E, 0xA0, 0x20, 0x8813, 0xAA04);

struct Obj_00A8E8E8
{
    // FUNCTION: GAMEMD 0x4E6070 (decl; reloc)
    Obj_00A8E8E8();
    // FUNCTION: GAMEMD 0x4E6140 (decl; reloc)
    ~Obj_00A8E8E8();
};
// SYNTHETIC: GAMEMD 0x4E80F0
// SYNTHETIC: GAMEMD 0x4E8110 -- atexit callback
// GLOBAL: GAMEMD 0xA8E8E8
Obj_00A8E8E8 DAT_00A8E8E8;

// ---- three-byte colours ----------------------------------------------------------------------------------------------

// A colour stored at run time byte by byte (red, green, blue).
struct ColorInit
{
    unsigned char R;   // +0x0
    unsigned char G;   // +0x1
    unsigned char B;   // +0x2
    ColorInit(unsigned char r, unsigned char g, unsigned char b) { R = r; G = g; B = b; }
};
GG_STATIC_ASSERT(sizeof(ColorInit) == 3);

// SYNTHETIC: GAMEMD 0x4E8120
// GLOBAL: GAMEMD 0xA83CD9
ColorInit DAT_00A83CD9(0, 0, 0);
// SYNTHETIC: GAMEMD 0x4E8140
// GLOBAL: GAMEMD 0xA83CD4
ColorInit DAT_00A83CD4(0x7F, 0x7F, 0x7F);
// SYNTHETIC: GAMEMD 0x4E8160
// GLOBAL: GAMEMD 0xA80220
ColorInit DAT_00A80220(0xFF, 0xFF, 0xFF);
// SYNTHETIC: GAMEMD 0x4E8180
// GLOBAL: GAMEMD 0xA8EAE4
ColorInit DAT_00A8EAE4(0xFF, 0, 0);
// SYNTHETIC: GAMEMD 0x4E81A0
// GLOBAL: GAMEMD 0xA83EC8
ColorInit DAT_00A83EC8(0, 0xFF, 0);
// SYNTHETIC: GAMEMD 0x4E81C0
// GLOBAL: GAMEMD 0xA8E8C4
ColorInit DAT_00A8E8C4(0, 0, 0xFF);
// SYNTHETIC: GAMEMD 0x4E81E0
// GLOBAL: GAMEMD 0xA83DC0
ColorInit DAT_00A83DC0(0, 0xFF, 0xFF);
// SYNTHETIC: GAMEMD 0x4E8200
// GLOBAL: GAMEMD 0x8B40E0
ColorInit DAT_008B40E0(0xFF, 0, 0xFF);
// SYNTHETIC: GAMEMD 0x4E8220
// GLOBAL: GAMEMD 0xA8E980
ColorInit DAT_00A8E980(0xFF, 0xFF, 0);

// FUNCTION: GAMEMD 0x4E8260
HRESULT __stdcall TiberianSunClassFactory::LockServer(BOOL lock)
{
    return S_OK;
}
