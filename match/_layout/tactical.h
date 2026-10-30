// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Tactical RTTI and four base interfaces: primary table 0x7F4348.
// RTTI COL 0x80B9A8 -> descriptor 0x842A38 (.?AVTactical@@).
// Hierarchy 0x80B998 -> base descriptor 0x7FB0C8 -> AbstractClass at +0.
// Size: 0x6DC460 returns 0xE18. Bounds read by 0x6D8AE0.
// Pair fields read/written by 0x6D9F80, 0x6D9FC0 and 0x6DA160.
#ifndef GG_MATCH_LAYOUT_TACTICAL_H
#define GG_MATCH_LAYOUT_TACTICAL_H
#include "abstract_class.h"
#include "elapsed_timer.h"
#include "../renderer/tactical_class_client_to_coords_methods.h"
GG_STATIC_ASSERT(offsetof(Point2D_006D2280, X) == 0);
GG_STATIC_ASSERT(offsetof(Point2D_006D2280, Y) == 4);
GG_STATIC_ASSERT(offsetof(Coord_006D2280, X) == 0);
GG_STATIC_ASSERT(offsetof(Coord_006D2280, Y) == 4);
GG_STATIC_ASSERT(offsetof(Coord_006D2280, Z) == 8);

// External call target GAMEMD 0x00731D00: ECX supplies the value.
void FUN_00731D00(int value);

#include "pair_006d9f80.h"
class Surface;
class Cell;
class CellClass;
struct CellStruct;
class ObjectClass;
// Raw callback ABI: one object in ECX, no stack args; source member/free identity unproved.
typedef void (__fastcall *Callback_006DA5C0)(ObjectClass* object);
template<class T> class TRect;
struct RectangleStruct;
class Point2D;
// VTABLE: GAMEMD 0x007F4348
// VTABLE: GAMEMD 0x007F432C
// VTABLE: GAMEMD 0x007F4324
// VTABLE: GAMEMD 0x007F431C
class Tactical : public AbstractClass
{
public:
    void FUN_006D59D0(unsigned char mode, CellStruct origin); // 0x6D59D0, RET8
    void FUN_006D5C50(unsigned char mode, CellStruct origin); // 0x6D5C50, RET8
    void FUN_006D5730(unsigned char mode, CellStruct origin); // 0x6D5730, RET8
    void FUN_006D3D10(Surface* surface, bool full, int mode); // 0x6D3D10, RET12
    void FUN_006DAD60(bool flag); // RET4
    void FUN_006DA9D0(bool flag); // RET4
    void FUN_006D5030(bool flag); // RET4
    void FUN_006D7840(const RectangleStruct* first, const RectangleStruct* second); // RET8
    void FUN_006D8DB0(bool flag); // RET4
    void FUN_006DB210(); // 0x6DB210, RET0
    void FUN_006DB620(); // 0x6DB620, RET0
    void FUN_006DBE20();
    void FUN_006DA180();
    void FUN_006D4E20(const unsigned short* text);
    // Declarations: native 6D2DE0 RET12; render helpers6D7560/6D7F20 RET8.
    void FUN_006D2DE0(const RectangleStruct* first, const RectangleStruct* second, bool fullScreen);
    void FUN_006D7560(const RectangleStruct* rectangle, const RectangleStruct* clip);
    void FUN_006D7F20(const CellStruct* coordinate, const RectangleStruct* clip);
    // Declarations: native6D3040 RET12 and renderer6D7C00 RET8.
    void FUN_006D3040(const RectangleStruct* first, const RectangleStruct* second, bool fullScreen);
    // First stack argument is unused; its original type is unproved (RET8).
    void FUN_006D8260(void* unused, const RectangleStruct* rectangle);
    int FUN_006D8700(const CellStruct* coordinate, int layer); // RET8; layer low byte
    void FUN_006D7C00(const RectangleStruct* rectangle, const RectangleStruct* clip);
    // Declarations: native dispatchers6D3290/6D3470 RET12; helper6D6D10 RET4.
    void FUN_006D3290(const RectangleStruct* first, const RectangleStruct* second, bool fullScreen);
    void FUN_006D3470(const RectangleStruct* first, const RectangleStruct* second, bool fullScreen);
    void FUN_006D6D10(const RectangleStruct* rectangle);
    // Declarations: native6D3660 RET16,6DA7D0 RET4,6D71E0 RET4.
    void FUN_006D3660(const RectangleStruct* first, const RectangleStruct* second, const RectangleStruct* clip, bool fullScreen);
    void FUN_006DA7D0(CellClass* cell);
    void FUN_006D71E0(const RectangleStruct* rectangle);
    // Declarations: native6D3870 and6D9920 each RET12.
    void FUN_006D3870(const RectangleStruct* first, const RectangleStruct* second, bool fullScreen);
    void FUN_006D9920(bool force, const RectangleStruct* view, const RectangleStruct* clip);
    // Declarations: native6D3AC0 and6D97D0 each RET12.
    void FUN_006D3AC0(const RectangleStruct* first, const RectangleStruct* second, bool fullScreen);
    void FUN_006D97D0(bool force, const RectangleStruct* view, const RectangleStruct* clip);
    Point2D CoordsToScreen(const CoordStruct* coordinate); // 0x6D1F10, hidden result + coordinate, RET8
    bool FUN_006D2140(const CoordStruct* coordinate, Point2D* point); // 0x6D2140, AL result, RET8
    static int AdjustForZ(int Height); // 0x6D20E0; ECX height under /Gr
    Tactical(); // 0x6D1C20
    Tactical(const AbstractNoInit& noInit); // 0x6D1E30
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID); // slot3,0x6DBCE0
    virtual HRESULT __stdcall Load(IStream* stream); // slot5,0x6DBD20
    virtual HRESULT __stdcall Save(IStream* stream, BOOL clearDirty); // slot6,0x6DBE00
    virtual ~Tactical(); // slot8 deleting body0x6DC470; ordinary0x6D1E80
    virtual void vf_10(void* target, bool removed); // slot10,0x6DA560
    virtual int vf_11(); // slot11,0x6DC450
    virtual int vf_12(); // slot12,0x6DC460
    virtual void vf_23(); // slot23,0x6D2540
    virtual bool vf_24(const CoordStruct* first, const CoordStruct* second,
                       unsigned int color, bool mode); // slot24,0x6DBB60,RET16; Surface forwards low byte
    void FUN_006D2B60(bool fullScreen, int dx, int dy, const RectangleStruct* clip); // 0x6D2B60, RET0x10
    void FUN_006D2790(RectangleStruct requested, bool flag); // 0x6D2790, RET0x14
    bool FUN_006D8AE0(const Cell* cell) const;
    Coord_006D2280* FUN_006D2360(Coord_006D2280* out, const Point2D_006D2280* point);
    CoordStruct* FUN_006D2360(CoordStruct* out, const int* xyz);   // 0x6D2360, the same entry on a coordinate triple
    Pair_006D9F80 FUN_006D6190() const;
    // Hidden CellStruct result then input pointer; both entries RET8.
    CellStruct FUN_006D6410(const CoordStruct* coordinate); // 0x6D6410
    CellStruct FUN_006D6590(const Point2D* where); // 0x6D6590
    void FUN_006D4DB0(const unsigned short* text, int mode); // 0x6D4DB0
    void FUN_006D4E00(); // 0x6D4E00
    void FUN_006D5F60(const TRect<int>* bounds); // 0x6D5F60; RET4
    void FUN_006D6070(const CoordStruct* coordinate); // 0x6D6070; RET 4
    void FUN_006D6000(const Pair_006D9F80* point);
    void FUN_006D8530(int direction, int distance); // 0x6D8530; RET8
    bool FUN_006D8640(Pair_006D9F80* point); // 0x6D8640; RET 4
    void FUN_006D8B30(); // 0x6D8B30
    void FUN_006D9A50(RectangleStruct viewport); // 0x6D9A50, RET16
    bool FUN_006D9B50(RectangleStruct viewport); // RET16
    void FUN_006D9CE0(int x, int y, int width, int height); // RET16
    void FUN_006D9F80(const Pair_006D9F80* value);
    void FUN_006D9FC0(const Pair_006D9F80* value);
    void FUN_006DA160();
    void FUN_006DA980(); // GAMEMD 0x6DA980, caller0x6853C4; no arguments
    int FUN_006DA230(int direction); // 0x6DA230; RET4
    int FUN_006DC420(); // 0x6DC420; no stack arguments
    ObjectClass* FUN_006DC430(int index); // 0x6DC430; RET 4
    ObjectClass* FUN_006DA380(const Point2D* point); // RET4
    void FUN_006DA740(); // 0x6DA740
    bool FUN_006DA770(); // 0x6DA770
    int FUN_006DA080() const;
    void FUN_006D9FF0(Callback_006DA5C0 callback);
    void FUN_006DA5C0(const TRect<int>* rectangle, Callback_006DA5C0 callback); // 0x6DA5C0; RET 8
    // Methods recovered in the renderer/ and ui/ TUs (consolidated from per-TU views).
    bool CoordsToClient(const CoordStruct* coord, Point2D* point);
    int* AdjustForZShapeMove(int* pDest, const int* pClient);
    int* ApplyMatrix_Pixel(int* pOut, const int* pIn);
    bool AddSelectable(void* pTechno, int x, int y);
    Point2D* AdjustForZShapeMove(Point2D* out, const Point2D* in);
    // FUNCTION: GAMEMD 0x6D2070 (decl; reloc) -- writes the projected point into `out` and returns it.
    Point2D* FUN_006D2070(Point2D* out, const Point2D* in);
    void FUN_006D2140(const CoordStruct& coord, Point2D* out);   // 0x6D2140, void-result view
    Point2D FUN_006D2140(const CoordStruct& coord);   // 0x6D2140, the same entry with the point returned through the hidden pointer
    unsigned short unknown_24[64];
    int unknown_A4;
    int unknown_A8;
    bool unknown_AC;
    bool unknown_AD;
    char unknown_AE[2];
    Pair_006D9F80 unknown_B0;
    Pair_006D9F80 unknown_B8;
    double unknown_C0;
    Pair_006D9F80 unknown_C8;
    Pair_006D9F80 unknown_D0;
    float unknown_D8;
    float unknown_DC;
    int unknown_E0;
    // 6DA949 stores the original cell argument;6D369B consumes it as CellClass.
    CellClass* unknown_E4[800];
    Pair_006D9F80 unknown_D64;
    Pair_006D9F80 unknown_D6C;
    Pair_006D9F80 unknown_D74;
    unsigned char unknown_D7C;
    bool unknown_D7D;
    bool unknown_D7E;
    char unknown_D7F;
    int unknown_D80;
    int unknown_D84;
    int unknown_D88;
    int unknown_D8C;
    Pair_006D9F80 unknown_D90;
    Pair_006D9F80 unknown_D98;
    int unknown_DA0;
    ScenarioElapsedTimer unknown_DA4;
    int unknown_DB0;
    Matrix3D unknown_DB4;
    Matrix3D unknown_DE4;
    char unknown_E14[4];
};
GG_STATIC_ASSERT(offsetof(Tactical, unknown_24) == 0x24);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_24) == 0x80);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_24[0]) == 2);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_AD) == 0xAD);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_C0) == 0xC0);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D8) == 0xD8);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_E0) == 0xE0);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_E4) == 0xE4);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D6C) == 0xD6C);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D7C) == 0xD7C);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D7E) == 0xD7E);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DA0) == 0xDA0);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DA4) == 0xDA4);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DB4) == 0xDB4);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_E4) == 0xC80);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_B0.unknown_04) == 0xB4);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DB0) == 0xDB0);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D64) == 0xD64);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D74) == 0xD74);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D7D) == 0xD7D);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D64.unknown_04) == 0xD68);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D74.unknown_04) == 0xD78);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D80) == 0xD80);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D84) == 0xD84);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D88) == 0xD88);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D8C) == 0xD8C);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D90) == 0xD90);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D90.unknown_04) == 0xD94);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D98) == 0xD98);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D98.unknown_04) == 0xD9C);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DE4) == 0xDE4);
GG_STATIC_ASSERT(sizeof(Tactical) == 0xE18);

GG_STATIC_ASSERT(offsetof(Tactical, unknown_C8) + offsetof(Pair_006D9F80, unknown_04) == 0xCC);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_D0) + offsetof(Pair_006D9F80, unknown_04) == 0xD4);
// Widths and nested timer offsets used by native update0x6D2540.
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_A8) == 4);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_C8) == 8);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_D0) == 8);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_D8) == 4);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_DC) == 4);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_D64) == 8);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_D74) == 8);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_D7D) == 1);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_DA0) == 4);
GG_STATIC_ASSERT(sizeof(((Tactical*)0)->unknown_DA4) == 12);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DA4) + offsetof(ScenarioElapsedTimer, unknown_00) == 0xDA4);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DA4) + offsetof(ScenarioElapsedTimer, unknown_04) == 0xDA8);
GG_STATIC_ASSERT(offsetof(Tactical, unknown_DA4) + offsetof(ScenarioElapsedTimer, unknown_08) == 0xDAC);

// Slot layouts read at 0x7F4348 and 0x7F432C; actual emitted tables are
// separately checked with verify_vtable.py. Pointers are four bytes.
struct TacticalPrimaryVtableLayout
{
    void* vf_00;
    void* vf_01;
    void* vf_02;
    void* vf_03;
    void* vf_04;
    void* vf_05;
    void* vf_06;
    void* vf_07;
    void* vf_08;
    void* vf_09;
    void* vf_10;
    void* vf_11;
    void* vf_12;
    void* vf_13;
    void* vf_14;
    void* vf_15;
    void* vf_16;
    void* vf_17;
    void* vf_18;
    void* vf_19;
    void* vf_20;
    void* vf_21;
    void* vf_22;
    void* vf_23;
    void* vf_24;
};
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_00) == 0x0);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_01) == 0x4);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_02) == 0x8);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_03) == 0xc);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_04) == 0x10);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_05) == 0x14);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_06) == 0x18);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_07) == 0x1c);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_08) == 0x20);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_09) == 0x24);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_10) == 0x28);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_11) == 0x2c);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_12) == 0x30);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_13) == 0x34);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_14) == 0x38);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_15) == 0x3c);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_16) == 0x40);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_17) == 0x44);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_18) == 0x48);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_19) == 0x4c);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_20) == 0x50);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_21) == 0x54);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_22) == 0x58);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_23) == 0x5c);
GG_STATIC_ASSERT(offsetof(TacticalPrimaryVtableLayout, vf_24) == 0x60);
GG_STATIC_ASSERT(sizeof(TacticalPrimaryVtableLayout) == 0x64);
struct TacticalRTTIVtableLayout
{
    void* vf_0;
    void* vf_1;
    void* vf_2;
    void* vf_3;
    void* vf_4;
    void* vf_5;
};
GG_STATIC_ASSERT(offsetof(TacticalRTTIVtableLayout, vf_0) == 0x0);
GG_STATIC_ASSERT(offsetof(TacticalRTTIVtableLayout, vf_1) == 0x4);
GG_STATIC_ASSERT(offsetof(TacticalRTTIVtableLayout, vf_2) == 0x8);
GG_STATIC_ASSERT(offsetof(TacticalRTTIVtableLayout, vf_3) == 0xc);
GG_STATIC_ASSERT(offsetof(TacticalRTTIVtableLayout, vf_4) == 0x10);
GG_STATIC_ASSERT(offsetof(TacticalRTTIVtableLayout, vf_5) == 0x14);
GG_STATIC_ASSERT(sizeof(TacticalRTTIVtableLayout) == 0x18);
struct TacticalNoticeVtableLayout { void* vf_0; };
GG_STATIC_ASSERT(offsetof(TacticalNoticeVtableLayout, vf_0) == 0);
GG_STATIC_ASSERT(sizeof(TacticalNoticeVtableLayout) == 4);

// GLOBAL: GAMEMD 0x887324 -- the Tactical object pointer (458 references; the one canonical spelling).
extern Tactical* DAT_00887324;

#endif
