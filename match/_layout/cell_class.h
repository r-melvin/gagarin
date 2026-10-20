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
//   Cross-read against YRpp CellClass.h: 48 named members claimed, 48
//   confirmed. No disagreement found.
//
// CellClass — one map cell. Derives AbstractClass at offset 0.
#ifndef GG_MATCH_LAYOUT_CELL_CLASS_H
#define GG_MATCH_LAYOUT_CELL_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "foot_class.h"        // CellStruct
#include "building_class.h"    // RectangleStruct

struct CellClass : AbstractClass
{
    // FUNCTION: GAMEMD 0x486840
    // Primary retail vtable slot +0x48. This layout currently represents vptrs
    // explicitly; the entry body is bound as a const method until the full
    // virtual hierarchy is reconstructed. CoordStruct uses a hidden result.
    CoordStruct GetCoords() const;
    // FUNCTION: GAMEMD 0x47B3A0 (decl; reloc)
    int GetFloorHeight(const Point2D& subcoords) const;

    CellStruct      MapCoords;               // +0x24 ctor MOV [ESI+0x24],EAX(=[0x0089E748]) @0x0047BC02
    void*           FoggedObjects;           // +0x28 ctor @0x0047BC05 (=0)
    void*           BridgeOwnerCell;         // +0x2C CellClass*; ctor @0x0047BC08
    unsigned int    unknown_30;              // +0x30 ctor @0x0047BC0B
    void*           LightConvert;            // +0x34 LightConvertClass*; ctor @0x0047BC0E
    int             IsoTileTypeIndex;        // +0x38 ctor MOV [ESI+0x38],0xFFFF @0x0047BC11
    void*           AttachedTag;             // +0x3C TagClass*; ctor @0x0047BC18
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
    void*           PixelFX;                 // +0xFC PixelFXClass*; ctor @0x0047BCDB
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
    unsigned char   unknown_11D;             // +0x11D ctor @0x0047BD16
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
    unsigned int    OccupationFlags;         // +0x124  (see above)
    unsigned int    AltOccupationFlags;      // +0x128  (see above)
    unsigned int    AltFlags;                // +0x12C ctor read-modify-write AND 0xFFFFFFE0
                                             //   @0x0047BC52..0x0047BC60 (a bitfield, low 5 bits cleared)
    int             ShroudCounter;           // +0x130 ctor MOV [ESI+0x130],1 @0x0047BD3A
    unsigned int    GapsCoveringThisCell;    // +0x134 ctor @0x0047BD44
    unsigned char   VisibilityChanged;       // +0x138 ctor @0x0047BD4A
    unsigned char   align_139[3];            // +0x139 (PROTECTED_PROPERTY)
    unsigned int    unknown_13C;             // +0x13C ctor @0x0047BD50
    unsigned int    Flags;                   // +0x140 ctor read-modify-write AND 0xFF800000
                                             //   @0x0047BCC9..0x0047BD56 (a bitfield, low 23 bits cleared)
    unsigned char   padding_144[4];          // +0x144 (PROTECTED_PROPERTY; closes the object at 0x148)
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
GG_STATIC_ASSERT(offsetof(CellClass, AltObject)               == 0xE8);
GG_STATIC_ASSERT(offsetof(CellClass, LandType)                == 0xEC);
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
