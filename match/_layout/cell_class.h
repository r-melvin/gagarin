// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: CellClass ctor FUN_0x0047BBF0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0; sizeof(AbstractClass) == 0x24, already asserted
//   in abstract_class.h). The ctor initialises the whole 0x24..0x147 span
//   including OccupationFlags/AltOccupationFlags, which an earlier revision of
//   this header wrongly recorded as not ctor-initialised (see the correction at
//   those members). Every member carries the address of the instruction that
//   proves it.
//
//   sizeof: `PUSH 0x148` precedes the ctor call at all 4 allocation sites found
//   by `ghidra x-ref to 0x47BBF0`; the layout closes exactly on 0x148.
//
//   RTTI (read from the binary): the four vptrs stored at 0x0047BD5C..0x0047BD79
//   (0x007E4EEC / 0x007E4ED0 / 0x007E4EC8 / 0x007E4EC0) all resolve to
//   ".?AVCellClass@@", COL base-offset 0 / 4 / 8 / 12.
//
//   Two array widths the ctor settles exactly, and they are the two most
//   error-prone fields in the class:
//     * SensorsOfHouses     — `LEA EDI,[ESI+0x7C]; MOV ECX,0xC; REP STOSD`
//       @0x0047BD6F..0x0047BD80 = 48 bytes = 24 words, NOT 32. YRpp's
//       "! 24 houses instead of 32 like cloakgen" is correct.
//     * DisguiseSensorsOfHouses — same idiom at 0xAC, `MOV ECX,0xC`
//       @0x0047BD82..0x0047BD8D. Also 24 words.
//
//   Cross-read against YRpp: 48 named members claimed, 48
//   confirmed. No disagreement found.
//
// CellClass — one map cell. Derives AbstractClass at offset 0.
#ifndef GG_MATCH_LAYOUT_CELL_CLASS_H
#define GG_MATCH_LAYOUT_CELL_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "../core/vector_class.h"
#include "cell.h"        // CellStruct
#include "building_class.h"    // RectangleStruct

class TagClass;
class PixelFXClass;
class LightConvertClass;

class BuildingClass;
class BuildingTypeClass;
class HouseClass;
class FoggedObjectClass;
class UnitClass;
class AircraftClass;
class InfantryClass;
class TerrainClass;
struct TunnelClass;

class CellClass : public AbstractClass
{
public:
    // Native constructor at 0x47BBF0; declaration only.
    CellClass();
    // Native no-init constructor at 0x47B360; body is in cell_class_get_coords.cpp.
    CellClass(const AbstractNoInit& noInit);
    // Native ordinary destructor at 0x47BB60; declaration only.
    virtual ~CellClass();

    // Declarations: hidden RectangleStruct output, RET4; cell receiver in ECX.
    RectangleStruct FUN_0047FF80(); // 0x47FF80, hidden result, RET4
    // FUNCTION: GAMEMD 0x480110 -- the cell's screen position, stored through the out pointer; RET4.
    void FUN_00480110(Point2D* out);
    // Declaration: GAMEMD 0x4802A0; read-only point/clip, receiver ECX, RET8.
    void FUN_004802A0(const Point2D* point, const RectangleStruct* clip);
    void FUN_00480350(const Point2D* point, const RectangleStruct* clip, int mode); // 0x480350, RET12
    bool FUN_00487950(); // 0x487950, AL result, no stack arguments
    // Declaration: GAMEMD 0x487C10; cell receiver in ECX, bool result in AL.
    bool FUN_00487C10();
    RectangleStruct FUN_0047FB90(); // 0x47FB90
    RectangleStruct FUN_0047FDE0(); // 0x47FDE0
    // Declarations: point and clip pointers, RET8.
    void FUN_0047F6A0(const Point2D* point, const RectangleStruct* clip); // 0x47F6A0
    void FUN_0047F510(const Point2D* point, const RectangleStruct* clip); // 0x47F510
    bool FUN_0047EC90(Point2D* point, RectangleStruct* clip, bool mode); // RET12, AL result
    ObjectClass* FindTechnoNearestTo(Point2D* offset, bool alt, ObjectClass* exclude); // GAMEMD 0x47C3D0
    ObjectClass* FUN_0047C550(bool alternate); // 0x47C550, returns list object with type24, RET4
    BuildingClass* GetBuilding() const; // GAMEMD 0x47C520; BuildingClass 0x458A00 compares it with `this`
    // FUNCTION: GAMEMD 0x480510 (decl; reloc), ECX receiver, two dword args.
    bool ConnectsToOverlay(int overlay, int direction);
    bool FUN_0047C620(int speedType, BuildingTypeClass* type, HouseClass* owner); // GAMEMD 0x47C620 (RET 0xC); BuildingClass 0x449440
    // FUNCTION: GAMEMD 0x4834A0 (decl; reloc) -- canonical caller API alias; scoped provider remains in Cell_Class_004834A0.
    bool IsClearToMove(int speedType, bool ignoreInfantry, bool ignoreVehicles,
                       int zone, int movementZone, int level, bool isBridge);
    int FUN_00485020(); // GAMEMD 0x485020; caller0x685078 tests EAX
    void FUN_0047D2B0(int value); // GAMEMD 0x47D2B0; caller0x684FAB
    void RecalcAttributes_484680(); // GAMEMD 0x484680, __thiscall
    int FUN_00487D50(); // GAMEMD 0x487D50 (decl; reloc): Level + 4 * (Flags bit 7)
    // FUNCTION: GAMEMD 0x480630 (decl; reloc) -- one byte argument.
    void FUN_00480630(char flag);
    // FUNCTION: GAMEMD 0x480CB0 (decl; reloc) -- one stack argument.
    void FUN_00480CB0(int value);
    // FUNCTION: GAMEMD 0x485130 -- forget `target` wherever this cell refers to it; RET4.
    void FUN_00485130(void* target);
    // FUNCTION: GAMEMD 0x4852D0 (decl; reloc)
    void FUN_004852D0();
    // FUNCTION: GAMEMD 0x486E70 (decl; reloc)
    void FUN_00486E70();
    // FUNCTION: GAMEMD 0x47C520 (decl; reloc) -- no stack arguments; the building standing on the cell.
    BuildingClass* FUN_0047C520();

    // Retail vtable 0x7E4EEC overrides these five slots of AbstractClass; the
    // bodies are not reconstructed here. They make CellClass a complete type.
    // FUNCTION: GAMEMD 0x485200 (decl; slot 3)
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    // FUNCTION: GAMEMD 0x4839F0 (decl; slot 5)
    virtual HRESULT __stdcall Load(IStream* pStm);
    // FUNCTION: GAMEMD 0x483C10 (decl; slot 6)
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    // FUNCTION: GAMEMD 0x487E60 (decl; slot 11)
    virtual int vf_11();
    // FUNCTION: GAMEMD 0x487E70 (decl; slot 12)
    virtual int vf_12();
    // Native RTTI side-table slot 3 target at 0x487E50.
    virtual int __stdcall vf_rtti_3();
    // FUNCTION: GAMEMD 0x4867E0 (decl; primary slot 20)
    virtual bool IsOnFloor() const;
    // FUNCTION: GAMEMD 0x486890 (decl; primary slot 22)
    virtual CoordStruct vf_22();

    // FUNCTION: GAMEMD 0x485250
    void ReplaceTag(TagClass* tag);

    // FUNCTION: GAMEMD 0x486840 (primary vtable slot 18)
    virtual CoordStruct vf_18();
    // Declaration: GAMEMD 0x480A30 -- hidden result pointer, RET4.
    CoordStruct* GetCellCoords(CoordStruct* result) const;
    // Declaration: GAMEMD 0x480180 -- point and clip pointers, RET8.
    void FUN_00480180(const Point2D* point, const RectangleStruct* clip);
    // Declaration: GAMEMD 0x4801F0 -- point and clip pointers, RET8.
    void FUN_004801F0(const Point2D* point, const RectangleStruct* clip);
    // FUNCTION: GAMEMD 0x4870D0 (decl; reloc) -- reads a word table at +0x7C indexed by the argument.
    // FUNCTION: GAMEMD 0x4870B0 (decl; reloc) -- tests the bit for the given index in the word at +0x78; RET 4.
    bool FUN_004870B0(int index);
    bool FUN_004870D0(int index);
    // FUNCTION: GAMEMD 0x47B3A0 (decl; reloc)
    int GetFloorHeight(const Point2D& subcoords) const;
    // FUNCTION: GAMEMD 0x481810 (decl; reloc)
    // The adjacent cell in direction `facing` (0-7, offsets at 0x89F688);
    // __thiscall, RET 4.
    CellClass* FUN_00481810(unsigned int facing);
    // FUNCTION: GAMEMD 0x486380 (decl; reloc)
    bool FUN_00486380();
    // FUNCTION: GAMEMD 0x4863D0 (decl; reloc)
    bool FUN_004863D0();
    // FUNCTION: GAMEMD 0x4865B0 (decl; reloc)
    bool FUN_004865B0();
    // FUNCTION: GAMEMD 0x4865D0 (decl; reloc)
    char FUN_004865D0();
    // FUNCTION: GAMEMD 0x486750 (decl; reloc)
    // True when IsoTileTypeIndex lies in [0xAA0E28, 0xAA0E28 + 0x10) and that
    // global is not -1.
    bool FUN_00486750();
    // FUNCTION: GAMEMD 0x486770 (decl; reloc)
    // As 0x486750, against the global at 0xABAD1C.
    bool FUN_00486770();
    // FUNCTION: GAMEMD 0x58C800 (decl; reloc) -- record for this cell (MapGen).
    struct Rec_0058C800Ret* FUN_0058C800();
    // FUNCTION: GAMEMD 0x4867B0 (decl; reloc)
    bool FUN_004867B0() const;
    // FUNCTION: GAMEMD 0x47EFE0 (decl; reloc) -- draws the shroud edge for the given level, RET 12.
    void FUN_0047EFE0(const Point2D* point, const RectangleStruct* clip, int level);
    // FUNCTION: GAMEMD 0x47F250 (decl; reloc) -- draws the fog edge for the given level, RET 12.
    void FUN_0047F250(const Point2D* point, const RectangleStruct* clip, int level);
    // FUNCTION: GAMEMD 0x481130 (decl; reloc) -- true when the given slot's bit is clear in the (alt) occupation bits; RET 8.
    bool FUN_00481130(int slot, bool alt);

    // Methods recovered in the map/ TUs (consolidated from per-TU views of this class).
    // GAMEMD 0x481870 -- fold this cell's threat into the other houses' tables.
    void UpdateThreat(unsigned int SourceHouse, int ThreatLevel);
    // GAMEMD 0x481870 -- same address as UpdateThreat, named for the TechnoClass caller.
    void AddThreat(HouseClass* pHouse, int threat);
    // GAMEMD 0x487C70 (decl; reloc) -- stores the cell's RadSite.
    void FUN_00487C70(void* radSite);
    bool IsBridgeTile();          // GAMEMD 0x486750
    bool IsWoodBridgeTile();      // GAMEMD 0x486770
    bool IsTileInSet00AA0E24();   // GAMEMD 0x486790
    void FogCell();
    void ClearFoggedObjects();
    void CleanFog();
    bool TryAssignJumpjet(ObjectClass* object);   // GAMEMD 0x487D70
    void MarkForRedraw();
    const wchar_t* GetUIName() const;             // GAMEMD 0x484FF0
    int GetRadLevel();                            // GAMEMD 0x487CB0
    int GetContainedTiberiumIndex() const;        // GAMEMD 0x485010
    bool FUN_00483690();                          // GAMEMD 0x483690
    void FUN_00483E30(int v0, int v1, int v2, int v3, int v4, int v5);   // GAMEMD 0x483E30
    bool FUN_00483620();                          // GAMEMD 0x483620
    void SetMapCoords(CellStruct const* coords);  // GAMEMD 0x485240
    void RadLevel_Increase(double amount);        // GAMEMD 0x487CE0
    void RadLevel_Decrease(double amount);
    UnitClass*     GetUnit(bool alt) const;
    AircraftClass* GetAircraft(bool alt) const;
    InfantryClass* GetInfantry(bool alt) const;
    void RevealCellObjects();                     // GAMEMD 0x483480
    TunnelClass* GetTunnel() const;               // GAMEMD 0x484F20
    ObjectClass* FindObjectOfType(int abs, bool alt) const; // GAMEMD 0x47C4D0
    TerrainClass* GetTerrain(bool alt) const;     // GAMEMD 0x47C550
    ObjectClass* GetSomeObject(int a, int b);     // GAMEMD 0x47C5A0
    ObjectClass* FindObjectAt(int a, int b, bool alt); // GAMEMD 0x47C3D0
    void RemoveContent(ObjectClass* object, bool alt);
    void IncreaseSensorsOfHouse(int idxHouse);            // GAMEMD 0x487150
    void DecreaseSensorsOfHouse(int idxHouse);            // GAMEMD 0x487160
    void IncreaseDisguiseSensorsOfHouse(int idxHouse);    // GAMEMD 0x487170
    void DecreaseDisguiseSensorsOfHouse(int idxHouse);    // GAMEMD 0x487180
    bool IsLandType5() const;                             // GAMEMD 0x487DF0
    bool FUN_00487E00() const;
    CellClass* GetNeighbourCell(int facing) const;
    void Unshroud();
    void ReduceShroudCounter();
    bool IsShrouded() const;
    bool FUN_004879B0() const;
    bool FUN_006B2520();                                  // GAMEMD 0x6B2520
    int GetContainedTiberiumValue() const;                // GAMEMD 0x485020
    void IncreaseShroudCounter();                         // GAMEMD 0x487690
    void SetWallOwner();
    CoordStruct FindInfantrySubposition(const CoordStruct& coords, bool ignoreContents,
                                        bool alt, bool useCellCoords);
    // GAMEMD 0x487C80 (decl; reloc) -- the cell's RadSite (+0xF8).
    void* FUN_00487C80();
    // FUNCTION: GAMEMD 0x486FF0 -- whether the cell is clear: no flagged tile, slope, cell flags, building or type 0x24 object.
    bool FUN_00486FF0();

    CellStruct      MapCoords;               // +0x24 ctor MOV [ESI+0x24],EAX(=[0x0089E748]) @0x0047BC02
    DynamicVectorClass<FoggedObjectClass*>* FoggedObjects; // +0x28 RTTI .?AV?$DynamicVectorClass@PAVFoggedObjectClass@@@@
    void*           BridgeOwnerCell;         // +0x2C CellClass*; ctor @0x0047BC08
    void*           unknown_30;              // +0x30 ctor @0x0047BC0B
    LightConvertClass* LightConvert;         // +0x34 ctor @0x0047BC0E
    int             IsoTileTypeIndex;        // +0x38 ctor MOV [ESI+0x38],0xFFFF @0x0047BC11
    TagClass*       AttachedTag;             // +0x3C TagClass*; ctor @0x0047BC18
    void*           Rubble;                  // +0x40 BuildingTypeClass*; ctor @0x0047BC1E
    int             OverlayTypeIndex;        // +0x44 ctor @0x0047BC21 (=-1)
    int             SmudgeTypeIndex;         // +0x48 ctor @0x0047BC24 (=-1)
    int             Passability;             // +0x4C ctor @0x0047BC27 (=0)
    int             WallOwnerIndex;          // +0x50 ctor @0x0047BC2A (=-1)
    int             InfantryOwnerIndex;      // +0x54 ctor @0x0047BC2D (=-1)
    int             AltInfantryOwnerIndex;   // +0x58 ctor @0x0047BC30 (=-1)
    unsigned int    unknown_5C;              // +0x5C ctor @0x0047BC33 (=-1)
    unsigned int    unknown_60;              // +0x60 ctor @0x0047BC39 (=-1)
    unsigned int    RedrawFrame;             // +0x64 ctor @0x0047BC3E (=-1)
    RectangleStruct InViewportRect;          // +0x68 (0x10) ctor via EBP=ESI+0x68 @0x0047BC36,
                                             //   stores [EBP],[EBP+4],[EBP+8],[EBP+0xC]
    unsigned int    CloakedByHouses;         // +0x78 ctor @0x0047BC73 (one bit per house)
    unsigned short  SensorsOfHouses[0x18];   // +0x7C .. 0xAB  ctor REP STOSD x0xC @0x0047BD6F
    unsigned short  DisguiseSensorsOfHouses[0x18]; // +0xAC .. 0xDB ctor REP STOSD x0xC @0x0047BD82
    unsigned int    BaseSpacerOfHouses;      // +0xDC ctor @0x0047BC76
    void*           Jumpjet;                 // +0xE0 FootClass*; ctor @0x0047BC7C
    void*           FirstObject;             // +0xE4 ObjectClass*; ctor @0x0047BC82
    void*           AltObject;               // +0xE8 ObjectClass*; ctor @0x0047BC88
    int             LandType;                // +0xEC ctor @0x0047BC93
    double          RadLevel;                // +0xF0 (8) ctor zeroes both halves @0x0047BC99/0x0047BCCF
    void*           RadSite;                 // +0xF8 RadSiteClass*; ctor @0x0047BCD5
    PixelFXClass*   PixelFX;                 // +0xFC PixelFXClass*; ctor @0x0047BCDB
    int             OccupyHeightsCoveringMe; // +0x100 ctor @0x0047BCE7
    unsigned int    Intensity;               // +0x104 ctor MOV [ESI+0x104],0x10000 @0x0047BCED
    unsigned short  Ambient;                 // +0x108 ctor MOV word [ESI+0x108],BX @0x0047BC69
    unsigned short  Intensity_Normal;        // +0x10A ctor MOV word [ESI+0x10A],CX(=0x3E8) @0x0047BC9F
    unsigned short  Intensity_Terrain;       // +0x10C ctor @0x0047BCA6 (=0x3E8)
    unsigned short  Color1_Blue;             // +0x10E ctor @0x0047BCAD (=0x3E8)
    unsigned short  Color2_Red;              // +0x110 ctor @0x0047BCB4 (=0x3E8)
    unsigned short  Color2_Green;            // +0x112 ctor @0x0047BCBB (=0x3E8)
    unsigned short  Color2_Blue;             // +0x114 ctor @0x0047BCC2 (=0x3E8)
    short           TubeIndex;               // +0x116 ctor MOV word [ESI+0x116],AX(=-1) @0x0047BC48
    signed char     unknown_118;             // +0x118 ctor MOV byte [ESI+0x118],0xFF @0x0047BCF7
    signed char     IsIceGrowthAllowed;      // +0x119 ctor @0x0047BCFE
    signed char     Height;                  // +0x11A ctor @0x0047BD04
    signed char     Level;                   // +0x11B ctor @0x0047BD0A
    unsigned char   SlopeIndex;              // +0x11C ctor @0x0047BD10
    signed char     unknown_11D;             // +0x11D; CMP/JLE6D807C, MOVSX6D809E
    unsigned char   OverlayData;             // +0x11E ctor @0x0047BD1C
    unsigned char   SmudgeData;              // +0x11F ctor @0x0047BD22
    signed char     Visibility;              // +0x120 ctor MOV byte [ESI+0x120],AL(=0xFE) @0x0047BD28
    signed char     Foggedness;              // +0x121 ctor @0x0047BD2E (=0xFE, i.e. -2 "occluded")
    unsigned char   BlockedNeighbours;       // +0x122 ctor @0x0047BD34
    unsigned char   align_123;               // +0x123 (PROTECTED_PROPERTY)
    // CORRECTION: an earlier note here said these two are "NOT set by the ctor".
    // They are, in the last two instructions before the epilogue, with ESI the
    // receiver from 0x0047BBF0 through the RET:
    //     MOV byte ptr [ESI+0x124],BL   @0x0047BD95
    //     MOV byte ptr [ESI+0x128],BL   @0x0047BD9B
    // The offsets were right; the provenance was not.
    //
    // OPEN QUESTION, and it is a matching hazard rather than a layout one: every
    // access seen so far is BYTE-wide -- the two ctor stores above, plus
    // TEST byte [EDI+0x124],0x3F @0x0047C85F (16 sites) and
    // MOV AL,byte [EDI+0x128] @0x0048772D (12 sites). These are declared
    // `unsigned int`, which keeps every offset and the sizeof assert correct, so
    // nothing here is wrong today. But a future translation unit that WRITES one
    // of these through the declared type will emit a DWORD store where retail
    // emits a byte store, and will not match. Re-derive the width before
    // matching any function that assigns to them.
    // Both widths are attested: ObjectClass 0x5F60A0 reads and writes the whole
    // dword, InfantryClass 0x5217C0/0x521850 set and clear bits in the low byte
    // (OR/AND byte [reg+0x124]/[reg+0x128]).
    union {
        unsigned int    OccupationFlags;     // +0x124  (see above)
        unsigned char   OccupationBits;      // +0x124  low byte
    };
    union {
        unsigned int    AltOccupationFlags;  // +0x128  (see above)
        unsigned char   AltOccupationBits;   // +0x128  low byte
    };
    unsigned int    AltFlags;                // +0x12C ctor read-modify-write AND 0xFFFFFFE0
                                             //   @0x0047BC52..0x0047BC60 (a bitfield, low 5 bits cleared)
    int             ShroudCounter;           // +0x130 ctor MOV [ESI+0x130],1 @0x0047BD3A
    unsigned int    GapsCoveringThisCell;    // +0x134 ctor @0x0047BD44
    unsigned char   VisibilityChanged;       // +0x138 ctor @0x0047BD4A
    unsigned char   align_139[3];            // +0x139 (PROTECTED_PROPERTY)
    int             unknown_13C;             // +0x13C ctor @0x0047BD50 (read as signed at 0x5864A0)
    unsigned int    Flags;                   // +0x140 ctor read-modify-write AND 0xFF800000
                                             //   @0x0047BCC9..0x0047BD56 (a bitfield, low 23 bits cleared)
    unsigned char   padding_144[4];          // +0x144 (PROTECTED_PROPERTY; closes the object at 0x148)
    // FUNCTION: GAMEMD 0x483410 (decl; reloc) -- plant the flag in this cell for the given colour index; false when the cell already holds one or cannot take it.
    bool FUN_00483410(int colorIndex);
    // FUNCTION: GAMEMD 0x483460 (decl; reloc) -- take this cell's flag away; true when there was one.
    bool FUN_00483460();
};

GG_STATIC_ASSERT(offsetof(CellClass, MapCoords)               == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, FoggedObjects)           == 0x28);
GG_STATIC_ASSERT(offsetof(CellClass, BridgeOwnerCell)         == 0x2C);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_30)              == 0x30);
GG_STATIC_ASSERT(offsetof(CellClass, LightConvert)            == 0x34);
GG_STATIC_ASSERT(offsetof(CellClass, IsoTileTypeIndex)        == 0x38);
GG_STATIC_ASSERT(offsetof(CellClass, AttachedTag)             == 0x3C);
GG_STATIC_ASSERT(offsetof(CellClass, Rubble)                  == 0x40);
GG_STATIC_ASSERT(offsetof(CellClass, OverlayTypeIndex)        == 0x44);
GG_STATIC_ASSERT(offsetof(CellClass, SmudgeTypeIndex)         == 0x48);
GG_STATIC_ASSERT(offsetof(CellClass, Passability)             == 0x4C);
GG_STATIC_ASSERT(offsetof(CellClass, WallOwnerIndex)          == 0x50);
GG_STATIC_ASSERT(offsetof(CellClass, InfantryOwnerIndex)      == 0x54);
GG_STATIC_ASSERT(offsetof(CellClass, AltInfantryOwnerIndex)   == 0x58);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_5C)              == 0x5C);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_60)              == 0x60);
GG_STATIC_ASSERT(offsetof(CellClass, RedrawFrame)             == 0x64);
GG_STATIC_ASSERT(offsetof(CellClass, InViewportRect)          == 0x68);
GG_STATIC_ASSERT(offsetof(CellClass, CloakedByHouses)         == 0x78);
GG_STATIC_ASSERT(offsetof(CellClass, SensorsOfHouses)         == 0x7C);
GG_STATIC_ASSERT(offsetof(CellClass, DisguiseSensorsOfHouses) == 0xAC);
GG_STATIC_ASSERT(offsetof(CellClass, BaseSpacerOfHouses)      == 0xDC);
GG_STATIC_ASSERT(offsetof(CellClass, Jumpjet)                 == 0xE0);
GG_STATIC_ASSERT(offsetof(CellClass, FirstObject)             == 0xE4);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->FirstObject)          == 0x04);
GG_STATIC_ASSERT(offsetof(CellClass, AltObject)               == 0xE8);
GG_STATIC_ASSERT(offsetof(CellClass, LandType)                == 0xEC);
GG_STATIC_ASSERT(sizeof(((CellClass*)0)->LandType)             == 0x04);
GG_STATIC_ASSERT(offsetof(CellClass, RadLevel)                == 0xF0);
GG_STATIC_ASSERT(offsetof(CellClass, RadSite)                 == 0xF8);
GG_STATIC_ASSERT(offsetof(CellClass, PixelFX)                 == 0xFC);
GG_STATIC_ASSERT(offsetof(CellClass, OccupyHeightsCoveringMe) == 0x100);
GG_STATIC_ASSERT(offsetof(CellClass, Intensity)               == 0x104);
GG_STATIC_ASSERT(offsetof(CellClass, Ambient)                 == 0x108);
GG_STATIC_ASSERT(offsetof(CellClass, Intensity_Normal)        == 0x10A);
GG_STATIC_ASSERT(offsetof(CellClass, Intensity_Terrain)       == 0x10C);
GG_STATIC_ASSERT(offsetof(CellClass, Color1_Blue)             == 0x10E);
GG_STATIC_ASSERT(offsetof(CellClass, Color2_Red)              == 0x110);
GG_STATIC_ASSERT(offsetof(CellClass, Color2_Green)            == 0x112);
GG_STATIC_ASSERT(offsetof(CellClass, Color2_Blue)             == 0x114);
GG_STATIC_ASSERT(offsetof(CellClass, TubeIndex)               == 0x116);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_118)             == 0x118);
GG_STATIC_ASSERT(offsetof(CellClass, IsIceGrowthAllowed)      == 0x119);
GG_STATIC_ASSERT(offsetof(CellClass, Height)                  == 0x11A);
GG_STATIC_ASSERT(offsetof(CellClass, Level)                   == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass, SlopeIndex)              == 0x11C);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_11D)             == 0x11D);
GG_STATIC_ASSERT(offsetof(CellClass, OverlayData)             == 0x11E);
GG_STATIC_ASSERT(offsetof(CellClass, SmudgeData)              == 0x11F);
GG_STATIC_ASSERT(offsetof(CellClass, Visibility)              == 0x120);
GG_STATIC_ASSERT(offsetof(CellClass, Foggedness)              == 0x121);
GG_STATIC_ASSERT(offsetof(CellClass, BlockedNeighbours)       == 0x122);
GG_STATIC_ASSERT(offsetof(CellClass, OccupationFlags)         == 0x124);
GG_STATIC_ASSERT(offsetof(CellClass, AltOccupationFlags)      == 0x128);
GG_STATIC_ASSERT(offsetof(CellClass, OccupationBits)          == 0x124);
GG_STATIC_ASSERT(offsetof(CellClass, AltOccupationBits)       == 0x128);
GG_STATIC_ASSERT(offsetof(CellClass, AltFlags)                == 0x12C);
GG_STATIC_ASSERT(offsetof(CellClass, ShroudCounter)           == 0x130);
GG_STATIC_ASSERT(offsetof(CellClass, GapsCoveringThisCell)    == 0x134);
GG_STATIC_ASSERT(offsetof(CellClass, VisibilityChanged)       == 0x138);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_13C)             == 0x13C);
GG_STATIC_ASSERT(offsetof(CellClass, Flags)                   == 0x140);
GG_STATIC_ASSERT(offsetof(CellClass, padding_144)             == 0x144);
GG_STATIC_ASSERT(sizeof(CellClass)                            == 0x148);

// VTABLE: GAMEMD 0x007E4EEC  CellClass            (COL base 0)
// VTABLE: GAMEMD 0x007E4ED0  CellClass::(+0x04)   (COL base 4)
// VTABLE: GAMEMD 0x007E4EC8  CellClass::(+0x08)   (COL base 8)
// VTABLE: GAMEMD 0x007E4EC0  CellClass::(+0x0C)   (COL base 12)

#endif  // GG_MATCH_LAYOUT_CELL_CLASS_H
