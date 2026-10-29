// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only) | behaviour-confirmed-name
//   Partial views of the retail base classes shared by the whole terrain-objects module, each declared
//   once: ObjectClass (MapObjClassView, retained by OverlayClass and SmudgeClass),
//   ObjectTypeClass (MapObjTypeClassView, retained by OverlayTypeClass and SmudgeTypeClass),
//   the secondary interfaces, CRC engine and INI reader. TerrainClass and TerrainTypeClass
//   now use canonical ObjectClass and ObjectTypeClass bases. Foreign APIs below still use views.
//   pointer-swizzle manager, and the map / cell / tactical / rules / scenario / anim / shape objects the
//   bodies read, together with the retail globals and out-of-partition functions bound by address.
//   Everything was read from the retail gamemd.exe v1.001:
//     OverlayClass      RTTI .?AVOverlayClass@@ (TD 0x833458): COLs 0x807638 / 0x8075C8 / 0x8075B0 /
//                       0x807598 for the tables 0x7EF3D4 (122 slots) / 0x7EF3B0 (6) / 0x7EF3CC (1) /
//                       0x7EF3A8 (1); chain OverlayClass -> ObjectClass -> AbstractClass ->
//                       IPersistStream -> IPersist -> IUnknown, IRTTITypeInfo -> IUnknown, INoticeSink,
//                       INoticeSource.
//     OverlayTypeClass  RTTI .?AVOverlayTypeClass@@ (TD 0x8334B0): COLs 0x8076F0 / 0x807680 / 0x807668 /
//                       0x807650 for the tables 0x7EF600 (41 slots) / 0x7EF5E4 (6) / 0x7EF5DC (1) /
//                       0x7EF5D4 (1); chain OverlayTypeClass -> ObjectTypeClass -> AbstractTypeClass ->
//                       AbstractClass -> the same interface bases.
//     SmudgeClass       RTTI .?AVSmudgeClass@@ (TD 0x83FFE0), COLs 0x8098E8 / 0x809878 / 0x809860 /
//                       0x809848, tables 0x7F32FC (122 slots) / 0x7F32D8 / 0x7F32F4 / 0x7F32D0 (the
//                       vptr stores of the constructor 0x6B4A50 and of the deleting destructor 0x6B4FA0
//                       confirm the four tables)
//     SmudgeTypeClass   RTTI .?AVSmudgeTypeClass@@ (TD 0x840008), COLs 0x8099A0 / 0x809930 / 0x809918 /
//                       0x809900, tables 0x7F3528 (41 slots) / 0x7F350C / 0x7F3504 / 0x7F34FC
//                       (constructor 0x6B5260, deleting destructor 0x6B6160)
//     TerrainClass      RTTI .?AVTerrainClass@@ (TD 0x842D48), COLs 0x80C3E0 (offset 0, table 0x7F522C,
//                       122 slots) / 0x80C370 (offset 4, 0x7F5200, 6 slots) / 0x80C358 (offset 8,
//                       0x7F5224, 1 slot) / 0x80C340 (offset 12, 0x7F521C, 1 slot). The class hierarchy
//                       0x80C3D0 lists TerrainClass, ObjectClass, AbstractClass, IPersistStream, IPersist,
//                       IUnknown, IRTTITypeInfo, IUnknown, INoticeSink, INoticeSource and, last, StageClass
//                       at member displacement 172 (0xAC).
//     TerrainTypeClass  RTTI .?AVTerrainTypeClass@@ (TD 0x8445E8), COLs 0x80C498 (table 0x7F5458, 40
//                       slots) / 0x80C428 (0x7F543C) / 0x80C410 (0x7F5434) / 0x80C3F8 (0x7F542C);
//                       hierarchy 0x80C488: TerrainTypeClass, ObjectTypeClass, AbstractTypeClass,
//                       AbstractClass and the same interface bases.
//   and the ObjectClass / ObjectTypeClass constructors 0x5F3900 / 0x5F3B50 / 0x5F7090 / 0x5F7320.
//
// The views never claim to be ObjectClass / ObjectTypeClass: the inherited slots and the base-class
// bodies are READ-ONLY dependencies of the module, bound by address (see the *.rows.tsv files). Slot
// numbers are the retail primary-table indices. MapObjClassView carries slots 0..121, which every
// object class shares; MapObjTypeClassView carries slots 0..39 (the type tables of Overlay and Smudge
// have a 41st slot that those classes add themselves, Terrain's table ends at slot 39).
//
// Calling conventions (proven by the prologues/epilogues of the bodies): the IPersistStream slots 0-7
// are __stdcall with `this` as the first stack argument; every other slot is __thiscall (this in ECX,
// callee pops its arguments). Slot names that carry a meaning are the ones a recovered body proves; the
// rest are positional (vf_N). Where the three families recovered the same slot with different spellings
// (a pointer versus a reference, a hidden return pointer versus a by-value return) the slot is declared
// ONCE here, in the spelling the largest number of bodies needed, and the other families' bodies use it.
//
// The address after each slot is the retail body of the slot in the base-class table ("base"); the
// slots a concrete class overrides list the retail entry of each overrider.
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VIEWS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VIEWS_H

#include "../../_layout/cell.h"
#include "terrain_common_types.h"
#include "terrain_vtable_layout.h"
#include "terrain_common_vectors.h"

class MapObjTypeClassView;
class MapObjSurfaceView;
class HouseClass;
struct MapObjHouseView;

// An object asking about a placement (partial): the cell it stands on is at +0x24.
struct MapObjOccupierView
{
    char        unknown_00[0x24];   // +0x00
    MapObjCell  Cell;               // +0x24
};
GG_STATIC_ASSERT(offsetof(MapObjOccupierView, Cell) == 0x24);

// WarheadTypeClass (partial; read-only here).
struct MapObjWarheadView
{
    char          unknown_00[0x147];   // +0x00
    unsigned char unknown_147;         // +0x147
};
GG_STATIC_ASSERT(offsetof(MapObjWarheadView, unknown_147) == 0x147);

// Secondary base at +0x04: the IRTTITypeInfo table (6 slots; 0x7EF3B0 / 0x7EF5E4 / 0x7F32D8 / 0x7F350C /
// 0x7F5200 / 0x7F543C). Slots 0-2 are the IUnknown adjustor thunks (0x4105E0 / 0x4105F0 / 0x410600),
// slots 3-5 are the bodies 0x410210 / 0x410220 / 0x410230, implemented once for every object and
// compiled with the subobject `this`.
struct MapObjRttiBase
{
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0  0x4105E0 (thunk)
    virtual ULONG __stdcall AddRef();                                     // 1  0x4105F0 (thunk)
    virtual ULONG __stdcall Release();                                    // 2  0x410600 (thunk)
    virtual int __stdcall What_Am_I();                                    // 3  0x410210
    virtual int __stdcall Fetch_ID();                                     // 4  0x410220
    // 5  0x410230: stores the id (global 0xA8B230 based) into the subobject's +0x0C. The constructors
    //    call it once, bound directly (the final overrider is known there).
    virtual void __stdcall Create_ID();
};
GG_STATIC_ASSERT(sizeof(MapObjRttiBase) == 4);

// Secondary base at +0x08: INoticeSink table (0x7EF3CC / 0x7EF5DC / 0x7F32F4 / 0x7F3504 / 0x7F5224 /
// 0x7F5434), one slot (0x410580: `XOR AL,AL; RET 8`).
struct MapObjNoticeSinkBase
{
    virtual bool __stdcall NoticeSink(int arg);   // 0  0x410580
};
GG_STATIC_ASSERT(sizeof(MapObjNoticeSinkBase) == 4);

// Secondary base at +0x0C: INoticeSource table (0x7EF3A8 / 0x7EF5D4 / 0x7F32D0 / 0x7F34FC / 0x7F521C /
// 0x7F542C), one slot (0x410590: bare `RET 4`).
struct MapObjNoticeSourceBase
{
    virtual void __stdcall NoticeSource();   // 0  0x410590
};
GG_STATIC_ASSERT(sizeof(MapObjNoticeSourceBase) == 4);

// The CRC accumulator the CRC slots feed (read-only here). Each entry takes one value.
class MapObjCrcView
{
public:
    // FUNCTION: GAMEMD 0x4A1CA0 (decl; reloc)
    void AddBool(bool value);
    // FUNCTION: GAMEMD 0x4A1D50 (decl; reloc)
    void AddInt(int value);
    // FUNCTION: GAMEMD 0x4A1D70 (decl; reloc)
    void AddFloat(float value);
};

// The rules / art INI reader (read-only here). Every Read* is __thiscall with the section name and the
// key as the first two arguments and the default value last.
class MapObjIniView
{
public:
    // FUNCTION: GAMEMD 0x526B00 (decl; reloc) - clears the reader's two cached positions
    void ClearCache();
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc)
    int ReadInt(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x5283D0 (decl; reloc)
    double ReadDouble(const char* section, const char* key, double defaultValue);
    // FUNCTION: GAMEMD 0x5295F0 (decl; reloc)
    bool ReadBool(const char* section, const char* key, bool defaultValue);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) - the length read, 0 when the key is absent.
    int ReadString(const char* section, const char* key, const char* defaultValue, char* buffer, int size);
    // FUNCTION: GAMEMD 0x4754B0 (decl; reloc) - a named-value (enumeration) read.
    int ReadEnum(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474DA0 (decl; reloc) - the foundation index named by the key, default given.
    int ReadFoundation(const char* section, const char* key, int defaultIndex);
    // FUNCTION: GAMEMD 0x474B50 (decl; reloc) - a colour read; the result comes back through a
    // hidden pointer (three bytes), the default is passed by reference.
    MapObjColor ReadColor(const char* section, const char* key, const MapObjColor& defaultValue);
};
// GLOBAL: GAMEMD 0x887180 - the art INI reader object (read-only here; its address is `this`).
extern MapObjIniView MapObjArtIni;



// FUNCTION: GAMEMD 0x7258D0 (decl; reloc) - announces that a pointer is going away. __fastcall: the
// object in ECX, the flag in DL. Every destructor calls it with 1 (the object is gone) to tell each
// holder to drop its pointer.
void MapObjAnnouncePointerExpired(void* object, bool removed);

// A map cell coordinate with the one out-of-partition method that takes the cell the object stands on
// as its receiver (FUNCTION: GAMEMD 0x489270, a bare RET). Slot 110 returns this.
struct MapObjCellRef : public MapObjCell
{
    // FUNCTION: GAMEMD 0x489270 (decl; reloc)
    void Func_489270();
};

// ObjectClass-shaped base of OverlayClass, SmudgeClass and TerrainClass (sizeof 0xAC).
// VTABLE: GAMEMD 0x7EF3D4 / 0x7F32FC / 0x7F522C (IPersistStream side, 122 slots), GAMEMD 0x7EF3B0 /
//         0x7F32D8 / 0x7F5200 (IRTTITypeInfo side, 6 slots), GAMEMD 0x7EF3CC / 0x7F32F4 / 0x7F5224
//         (INoticeSink side, 1 slot), GAMEMD 0x7EF3A8 / 0x7F32D0 / 0x7F521C (INoticeSource side, 1 slot)
//
// Layout (from the ObjectClass constructor 0x5F3900 and the bodies of the module):
//   +0x00 IPersistStream vptr (primary), +0x04 IRTTITypeInfo vptr, +0x08 INoticeSink vptr,
//   +0x0C INoticeSource vptr, +0x10..+0x9B AbstractClass / ObjectClass members (+0x44 an int, +0x6C an
//   int the TerrainClass constructor sets from its type, +0x74 a byte flag cleared by Mark, +0x80 /
//   +0x81 byte flags (+0x81 is the IsAlive-style byte that the OverlayClass constructor sets to 1),
//   +0x90 IsAlive), +0x9C Location (three dwords), +0xA8 last ObjectClass member.
class MapObjClassView : public IPersistStream, public MapObjRttiBase, public MapObjNoticeSinkBase,
                        public MapObjNoticeSourceBase
{
public:
    // FUNCTION: GAMEMD 0x5F3900 (ObjectClass constructor; read-only here)
    MapObjClassView();
    // FUNCTION: GAMEMD 0x5F3B50 (ObjectClass no-init constructor; read-only here)
    MapObjClassView(const MapObjNoInit& noInit);

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);                           // 0   base 0x410260
    virtual ULONG __stdcall AddRef();                                                            // 1   base 0x410300
    virtual ULONG __stdcall Release();                                                           // 2   base 0x410310
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                                       // 3   base body not recovered; overridden by Overlay 0x5FDF10, Smudge 0x6B4F50, Terrain 0x71D310
    virtual HRESULT __stdcall IsDirty();                                                         // 4   base 0x410450
    virtual HRESULT __stdcall Load(IStream* pStm);                                               // 5   base 0x5F5E80; overridden by Overlay 0x5FD8F0, Smudge 0x6B4EA0, Terrain 0x71CDA0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);                             // 6   base 0x410320; overridden by Overlay 0x5FD950, Smudge 0x6B4F00, Terrain 0x71CF30
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);                               // 7   base 0x4103E0
    virtual ~MapObjClassView();                                                                  // 8   base 0x5F3B80; overridden by Overlay 0x5FDF70, Smudge 0x6B4FA0, Terrain 0x71D350
    virtual void vf_9();                                                                         // 9   base 0x410470
    virtual void PointerExpired(void* ptr, bool removed);                                        // 10  base 0x5F5230; overridden by Terrain 0x71CFD0
    virtual int WhatAmI();                                                                       // 11  base body not recovered; overridden by Overlay 0x5FDF50, Smudge 0x6B4F40, Terrain 0x71D300
    virtual int Size();                                                                          // 12  base body not recovered; overridden by Overlay 0x5FDF00, Smudge 0x6B4F30, Terrain 0x71D2F0
    virtual void ComputeCRC(MapObjCrcView& crc);                                                 // 13  base 0x5F6250; overridden by Terrain 0x71CF50
    virtual void vf_14();                                                                        // 14  base 0x410490
    virtual void vf_15();                                                                        // 15  base 0x4104A0
    virtual void vf_16();                                                                        // 16  base 0x4104B0
    virtual bool IsFinished();                                                                   // 17  base 0x5F6690
    virtual MapObjCoord GetCoords();                                                             // 18  base 0x5F65A0
    virtual void vf_19();                                                                        // 19  base 0x4104F0
    virtual void vf_20();                                                                        // 20  base 0x5F6B60
    virtual void vf_21();                                                                        // 21  base 0x5F6B90
    virtual void vf_22();                                                                        // 22  base 0x410540
    virtual void Update();                                                                       // 23  base 0x5F3E70; overridden by Terrain 0x71C730
    virtual void vf_24();                                                                        // 24  base 0x5F6DA0
    virtual void vf_25();                                                                        // 25  base 0x426390
    virtual void vf_26();                                                                        // 26  base 0x4263A0
    virtual void* GetImage();                                                                    // 27  base 0x5F3E30
    virtual void vf_28();                                                                        // 28  base 0x5F4250
    virtual void vf_29();                                                                        // 29  base 0x5F4240
    virtual int InWhichLayer();                                                                  // 30  base 0x5F4260
    virtual void vf_31();                                                                        // 31  base 0x5F6C10
    virtual void vf_32();                                                                        // 32  base 0x4263B0
    virtual void vf_33();                                                                        // 33  base 0x5F6BC0
    virtual MapObjTypeClassView* GetType();                                                      // 34  base body not recovered; overridden by Overlay 0x5FDDE0, Smudge 0x6B4F20, Terrain 0x71D150
    virtual void vf_35();                                                                        // 35  base 0x5F42A0
    virtual void vf_36();                                                                        // 36  base 0x4263C0
    virtual void vf_37();                                                                        // 37  base 0x5F42B0
    virtual void vf_38();                                                                        // 38  base 0x5F42C0
    virtual void vf_39();                                                                        // 39  base 0x5F42D0
    virtual void vf_40();                                                                        // 40  base 0x5F42E0
    virtual void vf_41();                                                                        // 41  base 0x41BDD0
    virtual void vf_42();                                                                        // 42  base 0x5F6C80
    virtual MapObjCoord vf_43();                                                                 // 43  base 0x41BE00
    virtual void vf_44();                                                                        // 44  base 0x4263D0
    virtual void vf_45();                                                                        // 45  base 0x41BE30
    virtual void vf_46();                                                                        // 46  base 0x5F6BD0
    virtual void vf_47();                                                                        // 47  base 0x5F6A70
    virtual void vf_48();                                                                        // 48  base 0x426410
    virtual void vf_49();                                                                        // 49  base 0x426420
    virtual void vf_50();                                                                        // 50  base 0x426430
    virtual void vf_51();                                                                        // 51  base 0x41BE60
    virtual void vf_52();                                                                        // 52  base 0x41BE70
    virtual bool vf_53();                                                                        // 53  base 0x5F4D30; overridden by Terrain 0x71C930
    virtual bool Unlimbo(const MapObjCoord* where, int facing);                                  // 54  base 0x5F4EC0; overridden by Overlay 0x5FD270, Terrain 0x71D000
    virtual void vf_55(int arg);                                                                 // 55  base 0x5F5280
    virtual void vf_56();                                                                        // 56  base 0x5F42F0
    virtual void vf_57();                                                                        // 57  base 0x5F4300
    virtual void vf_58();                                                                        // 58  base 0x5F5940
    virtual void vf_59();                                                                        // 59  base 0x5F4160
    virtual void vf_60(MapObjCoord* where);                                                      // 60  base 0x5F60A0; overridden by Terrain 0x71C110
    virtual void vf_61(MapObjCoord* where);                                                      // 61  base 0x5F6120; overridden by Terrain 0x71C070
    virtual void UnInit();                                                                       // 62  base 0x5F65F0
    virtual void vf_63();                                                                        // 63  base 0x5F4310
    virtual void vf_64();                                                                        // 64  base 0x5F4320
    virtual bool vf_65(MapObjRect* rect, bool force, int unused);                                // 65  base 0x5F4B10; overridden by Terrain 0x71CC50
    virtual MapObjCell* vf_66(int arg);                                                          // 66  base 0x5F5B90
    virtual void vf_67();                                                                        // 67  base 0x426440
    virtual void vf_68();                                                                        // 68  base 0x426450
    virtual void vf_69(MapObjPoint* where, MapObjRect* clip);                                    // 69  base body not recovered; overridden by Overlay 0x5FDF60, Smudge 0x6B4F90, Terrain 0x71C1B0
    virtual void vf_70(MapObjPoint* where, MapObjRect* clip);                                    // 70  base 0x5F65D0; overridden by Overlay 0x5FD970, Terrain 0x71C360
    virtual void vf_71();                                                                        // 71  base 0x5F4330
    virtual void vf_72();                                                                        // 72  base 0x5F4340
    virtual bool Mark(int markType);                                                             // 73  base 0x5F5850; overridden by Overlay 0x5FC570, Smudge 0x6B4BE0, Terrain 0x71BFB0
    virtual void vf_74();                                                                        // 74  base 0x5F4730
    virtual MapObjRect vf_75();                                                                  // 75  base 0x5F4870; overridden by Terrain 0x71D160
    virtual void vf_76();                                                                        // 76  base 0x41BE80
    virtual void vf_77();                                                                        // 77  base 0x5F4D10
    virtual void vf_78();                                                                        // 78  base 0x5F6C30
    virtual void vf_79();                                                                        // 79  base 0x5F6C70
    virtual void vf_80();                                                                        // 80  base 0x5F4360
    virtual void vf_81();                                                                        // 81  base 0x5F4350
    virtual void vf_82();                                                                        // 82  base 0x5F4370
    virtual void vf_83();                                                                        // 83  base 0x5F4520
    virtual void vf_84();                                                                        // 84  base 0x5F44A0
    virtual void vf_85();                                                                        // 85  base 0x426460
    virtual void vf_86();                                                                        // 86  base 0x426470
    virtual void vf_87();                                                                        // 87  base 0x426480
    virtual void vf_88();                                                                        // 88  base 0x426490
    virtual void vf_89();                                                                        // 89  base 0x5F4380
    virtual void vf_90();                                                                        // 90  base 0x5F4390
    virtual int vf_91(int* damage, int distance, MapObjWarheadView* warhead, void* source, bool a5, bool a6, void* house); // 91  base 0x5F5390; overridden by Terrain 0x71B920
    virtual void vf_92();                                                                        // 92  base 0x4264A0
    virtual void vf_93();                                                                        // 93  base 0x5F43A0
    virtual bool vf_94();                                                                        // 94  base 0x5F43B0; overridden by Terrain 0x71C5B0
    virtual void vf_95();                                                                        // 95  base 0x5F43C0; overridden by Terrain 0x71C6B0
    virtual void vf_96();                                                                        // 96  base 0x5F43D0
    virtual void vf_97();                                                                        // 97  base 0x5F43E0
    virtual void vf_98();                                                                        // 98  base 0x41BE90
    virtual void vf_99();                                                                        // 99  base 0x4264B0
    virtual void vf_100();                                                                       // 100 base 0x5F5C20
    virtual void vf_101();                                                                       // 101 base 0x5F5320
    virtual void vf_102();                                                                       // 102 base 0x5F5930
    virtual void vf_103();                                                                       // 103 base 0x5F43F0
    virtual void vf_104();                                                                       // 104 base 0x5F4400
    virtual void vf_105();                                                                       // 105 base 0x5F6B50
    virtual void vf_106();                                                                       // 106 base 0x5F4410
    virtual int vf_107(MapObjOccupierView* who, int a2, int a3, int a4, int a5);                 // 107 base 0x4264C0; overridden by Terrain 0x71C4D0
    virtual void vf_108();                                                                       // 108 base 0x4264D0
    virtual void vf_109(const MapObjCoord* where);                                               // 109 base 0x5F6940; IsometricTileClass passes its Unlimbo coordinate
    virtual MapObjCell* vf_110(MapObjCell* out);                                                              // 110 base 0x41BEA0
    virtual void vf_111();                                                                       // 111 base 0x5F6960
    virtual void vf_112();                                                                       // 112 base 0x5F69C0
    virtual void vf_113();                                                                       // 113 base 0x5F6A10
    virtual void vf_114();                                                                       // 114 base 0x5F5F40
    virtual void vf_115();                                                                       // 115 base 0x5F5FA0
    virtual int vf_116();                                                                        // 116 base 0x5F5F30
    virtual void vf_117();                                                                       // 117 base 0x4264E0
    virtual void vf_118();                                                                       // 118 base 0x4264F0
    virtual void vf_119();                                                                       // 119 base 0x426500
    virtual void vf_120();                                                                       // 120 base 0x426510
    virtual void vf_121();                                                                       // 121 base 0x426520

    // Slot 110 is declared in its true calling form: a hidden return pointer (the cell is written through
    // `out`, which is also returned). Callers that want the cell by value pass the address of a
    // compiler temporary, `*vf_110(MapObjCell().Address())`, which gives the buffer exactly the lifetime
    // and stack slot a by-value return would (a named scratch local keeps its own slot and changes the
    // frame); OverlayClass::Mark passes a named scratch local instead (its frame has one).

    // The object's coordinate by value (inline accessor: expands to a three-dword copy).
    MapObjCoord CurrentLocation() const { return Location; }

    // ---- members (complete-object offsets) --------------------------------------------------
    char            unknown_10[0x34];    // +0x10..+0x43  AbstractClass / ObjectClass members
    int             unknown_44;          // +0x44
    char            unknown_48[0x6C - 0x48];   // +0x48..+0x6B
    int             unknown_6C;          // +0x6C
    char            unknown_70[4];       // +0x70
    unsigned char   unknown_74;          // +0x74
    char            unknown_75[0x80 - 0x75];   // +0x75..+0x7F
    unsigned char   unknown_80;          // +0x80
    unsigned char   unknown_81;          // +0x81
    char            unknown_82[0x90 - 0x82];   // +0x82..+0x8F
    unsigned char   IsAlive;             // +0x90
    char            unknown_91[0x9C - 0x91];   // +0x91..+0x9B
    MapObjCoord     Location;            // +0x9C         ObjectClass::Location
    int             unknown_A8;          // +0xA8         last ObjectClass member (ctor 0)
};

GG_STATIC_ASSERT(sizeof(IPersistStream) == 4);
GG_STATIC_ASSERT(offsetof(MapObjClassView, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MapObjClassView, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(MapObjClassView, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(MapObjClassView, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(MapObjClassView, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(MapObjClassView, unknown_81) == 0x81);
GG_STATIC_ASSERT(offsetof(MapObjClassView, IsAlive) == 0x90);
GG_STATIC_ASSERT(offsetof(MapObjClassView, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(MapObjClassView, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(sizeof(MapObjClassView) == 0xAC);

// ObjectTypeClass-shaped legacy base of OverlayTypeClass and SmudgeTypeClass (sizeof 0x294).
// TerrainTypeClass now derives canonical ObjectTypeClass; foreign APIs can still expose this prefix.
// Slot numbers are the retail primary-table indices (tables 0x7EF600 / 0x7F3528 with 41 slots and
// 0x7F5458 with 40: slots 0..39 are the ObjectTypeClass part, Overlay and Smudge add slot 40 themselves).
// VTABLE: GAMEMD 0x7EF600 / 0x7F3528 / 0x7F5458 (IPersistStream side), GAMEMD 0x7EF5E4 / 0x7F350C /
//         0x7F543C (IRTTITypeInfo side), GAMEMD 0x7EF5DC / 0x7F3504 / 0x7F5434 (INoticeSink side),
//         GAMEMD 0x7EF5D4 / 0x7F34FC / 0x7F542C (INoticeSource side)
class MapObjTypeClassView : public IPersistStream, public MapObjRttiBase, public MapObjNoticeSinkBase,
                            public MapObjNoticeSourceBase
{
public:
    // FUNCTION: GAMEMD 0x5F7090 (ObjectTypeClass named constructor; read-only here)
    MapObjTypeClassView(const char* id);
    // FUNCTION: GAMEMD 0x5F7320 (ObjectTypeClass no-init constructor; read-only here)
    MapObjTypeClassView(const MapObjNoInit& noInit);

    // FUNCTION: GAMEMD 0x5F8110 (decl; reloc) - ObjectTypeClass work after a load (called by Load
    // before PostLoad; purpose not recovered).
    void LoadFixup();
    // FUNCTION: GAMEMD 0x5F9070 (decl; reloc) - ObjectTypeClass work after a load.
    void PostLoad();

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);                           // 0   base 0x410260
    virtual ULONG __stdcall AddRef();                                                            // 1   base 0x410300
    virtual ULONG __stdcall Release();                                                           // 2   base 0x410310
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                                       // 3   base body not recovered; overridden by Overlay 0x5FEC30, Smudge 0x6B58D0, Terrain 0x71E260
    virtual HRESULT __stdcall IsDirty();                                                         // 4   base 0x410450
    virtual HRESULT __stdcall Load(IStream* pStm);                                               // 5   base 0x5F9720; overridden by Overlay 0x5FEAF0, Smudge 0x6B5850, Terrain 0x71E1D0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);                             // 6   base 0x5F9950; overridden by Overlay 0x5FEC10, Smudge 0x6B58B0, Terrain 0x71E240
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);                               // 7   base 0x5F9970
    virtual ~MapObjTypeClassView();                                                              // 8   base 0x5F7400; overridden by Overlay 0x5FEF30, Smudge 0x6B6160, Terrain 0x71E360
    virtual void vf_9();                                                                         // 9   base 0x410470
    virtual void PointerExpired(void* ptr, bool removed);                                        // 10  base 0x410480
    virtual int WhatAmI();                                                                       // 11  base body not recovered; overridden by Overlay 0x5FEF00, Smudge 0x6B6130, Terrain 0x71E330
    virtual int Size();                                                                          // 12  base body not recovered; overridden by Overlay 0x5FEF10, Smudge 0x6B6140, Terrain 0x71E340
    virtual void ComputeCRC(MapObjCrcView& crc);                                                 // 13  base 0x410BE0; overridden by Overlay 0x5FEA50, Smudge 0x6B57F0, Terrain 0x71E140
    virtual void vf_14();                                                                        // 14  base 0x410490
    virtual void vf_15();                                                                        // 15  base 0x4104A0
    virtual int vf_16();                                                                         // 16  base 0x4104B0; overridden by Overlay 0x5FEF20, Smudge 0x6B6150, Terrain 0x71E350
    virtual void vf_17();                                                                        // 17  base 0x410440
    virtual void vf_18();                                                                        // 18  base 0x4104C0
    virtual void vf_19();                                                                        // 19  base 0x4104F0
    virtual void vf_20();                                                                        // 20  base 0x410520
    virtual void vf_21();                                                                        // 21  base 0x410530
    virtual void vf_22();                                                                        // 22  base 0x410540
    virtual void vf_23();                                                                        // 23  base 0x410570
    virtual void vf_24();                                                                        // 24  base 0x410C20
    virtual bool ReadINI(MapObjIniView* ini);                                                    // 25  base 0x5F92D0; overridden by Overlay 0x5FE770, Smudge 0x6B56D0, Terrain 0x71DEA0
    virtual void vf_26();                                                                        // 26  base 0x410B90
    virtual MapObjCoord* vf_27(MapObjCoord* out, const MapObjCoord* coord);                      // 27  base 0x41CF80; overridden by Overlay 0x5FEA30, Terrain 0x71E0D0
    virtual void vf_28();                                                                        // 28  base 0x428E40
    virtual void vf_29();                                                                        // 29  base 0x5F75B0
    virtual void vf_30();                                                                        // 30  base 0x5F75C0
    virtual void vf_31();                                                                        // 31  base 0x5F75E0
    virtual bool vf_32(const MapObjCell* cell, MapObjHouseView* house);                          // 32  base body not recovered; overridden by Overlay 0x5FE530, Smudge 0x6B5550, Terrain 0x71DDD0
    virtual int vf_33(HouseClass* owner);                                                        // 33  base 0x5F7610
    virtual void vf_34();                                                                        // 34  base 0x5F7620
    virtual void* vf_35(MapObjHouseView* house);                                                 // 35  base body not recovered; overridden by Overlay 0x5FE570, Smudge 0x6B55C0, Terrain 0x71DE10
    virtual CellStruct* vf_36(int arg);                                                          // 36  base 0x5F7640; overridden by Overlay 0x5FE4C0, Terrain 0x71DE40
    virtual void vf_37();                                                                        // 37  base 0x5F7900
    virtual void vf_38();                                                                        // 38  base 0x5F7630
    virtual void* vf_39();                                                                       // 39  base 0x41CFA0; overridden by Overlay 0x5FEDE0

    // ---- members (complete-object offsets) --------------------------------------------------
    char unknown_10[0x14];    // +0x10..+0x23  AbstractClass members
    char ID[0x18];            // +0x24         AbstractTypeClass::ID, the INI section name
    char unknown_3C[0x28];    // +0x3C..+0x63
    char Name[0x38];          // +0x64..+0x9B  the display name (passed to the demand-load trace)
    int  unknown_9C;          // +0x9C         set to 6 by the Overlay / Terrain readers and constructors
    int  unknown_A0;          // +0xA0         TerrainTypeClass: -1, then the rules default
    void* Image;              // +0xA4         the loaded shape (read by the draw slots)
    unsigned char ImageAllocated;   // +0xA8
    char unknown_A9[0x1F8 - 0xA9];  // +0xA9..+0x1F7
    char ImageFile[0x34];     // +0x1F8..+0x22B  the art file name (without extension)
    bool Theater;             // +0x22C        true: the image uses the theater extension
    char unknown_22D[2];      // +0x22D..+0x22E
    bool unknown_22F;         // +0x22F  derived constructors store 1
    bool unknown_230;         // +0x230  derived constructors store 0
    bool unknown_231;         // +0x231
    bool unknown_232;         // +0x232  derived constructors store 1
    bool unknown_233;         // +0x233
    bool unknown_234;         // +0x234
    bool unknown_235;         // +0x235  derived constructors store 0
    unsigned char unknown_236;   // +0x236
    unsigned char NewTheater; // +0x237
    char unknown_238[0x294 - 0x238];   // +0x238..+0x293
};

GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, Name) == 0x64);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, Image) == 0xA4);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, Theater) == 0x22C);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_22F) == 0x22F);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_230) == 0x230);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_231) == 0x231);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_232) == 0x232);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_233) == 0x233);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_234) == 0x234);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, unknown_235) == 0x235);
GG_STATIC_ASSERT(offsetof(MapObjTypeClassView, NewTheater) == 0x237);
GG_STATIC_ASSERT(sizeof(MapObjTypeClassView) == 0x294);

// ---- the map, cell, tactical, rules, scenario, theater, anim and shape objects -----------------------

// The cell object (CellClass, partial; read-only here).
class MapObjCellView
{
public:
    // FUNCTION: GAMEMD 0x47C550 (decl; reloc)
    int Func_47C550(int arg);
    // FUNCTION: GAMEMD 0x47C620 (decl; reloc)
    bool Func_47C620(int a, int b, int c);
    // FUNCTION: GAMEMD 0x47D2B0 (decl; reloc)
    void Func_47D2B0(int arg);
    // FUNCTION: GAMEMD 0x47E040 (decl; reloc)
    void Func_47E040(int a, int b);
    // FUNCTION: GAMEMD 0x47E470 (decl; reloc)
    void Func_47E470(int a, int b);
    // FUNCTION: GAMEMD 0x480630 (decl; reloc)
    void Func_480630(int arg);
    // FUNCTION: GAMEMD 0x481810 (decl; reloc) - the neighbouring cell in that direction.
    MapObjCellView* GetNeighbour(int direction);
    // FUNCTION: GAMEMD 0x4818E0 (decl; reloc)
    void Func_4818E0(int arg);
    // FUNCTION: GAMEMD 0x4834A0 (decl; reloc)
    bool Func_4834A0(int a, int b, int c, int d, int e, int f, int g);
    // FUNCTION: GAMEMD 0x483780 (decl; reloc)
    void Func_483780(bool arg);
    // FUNCTION: GAMEMD 0x483E30 (decl; reloc)
    void Func_483E30(int a1, int a2, int a3, int a4, int a5, int a6);
    // FUNCTION: GAMEMD 0x485010 (decl; reloc) - the tiberium type index of this cell's overlay.
    int Func_485010();
    // FUNCTION: GAMEMD 0x485AF0 (decl; reloc)
    void Func_485AF0();

    char  unknown_00[0x24];     // +0x00
    MapObjCell MapCoords;       // +0x24
    char  unknown_28[0x34 - 0x28];
    void* Convert;              // +0x34  the colour converter the draw call takes
    char  unknown_38[0x44 - 0x38];
    int   OverlayTypeIndex;     // +0x44  the overlay placed on the cell (-1 for none)
    char  unknown_48[0x50 - 0x48];
    int   unknown_50;           // +0x50
    char  unknown_54[0xEC - 0x54];
    int   unknown_EC;           // +0xEC
    char  unknown_F0[0x10A - 0xF0];
    short unknown_10A;          // +0x10A
    short Light;                // +0x10C the cell's light level (the shape drawer's tint argument)
    char  unknown_10E[0x11C - 0x10E];
    unsigned char unknown_11C;  // +0x11C
    unsigned char unknown_11D;  // +0x11D
    unsigned char OverlayFrame; // +0x11E the frame of the overlay placed on the cell
    char  unknown_11F[0x121 - 0x11F];
    unsigned char unknown_121;  // +0x121
    unsigned char unknown_122;  // +0x122  occupation counter
    char  unknown_123;          // +0x123
    union {
        unsigned int  Flags;    // +0x124
        unsigned char FlagBytes[4];
    };
};
GG_STATIC_ASSERT(offsetof(MapObjCellView, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(MapObjCellView, Convert) == 0x34);
GG_STATIC_ASSERT(offsetof(MapObjCellView, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(MapObjCellView, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(MapObjCellView, unknown_EC) == 0xEC);
GG_STATIC_ASSERT(offsetof(MapObjCellView, unknown_10A) == 0x10A);
GG_STATIC_ASSERT(offsetof(MapObjCellView, Light) == 0x10C);
GG_STATIC_ASSERT(offsetof(MapObjCellView, unknown_11C) == 0x11C);
GG_STATIC_ASSERT(offsetof(MapObjCellView, unknown_11D) == 0x11D);
GG_STATIC_ASSERT(offsetof(MapObjCellView, OverlayFrame) == 0x11E);
GG_STATIC_ASSERT(offsetof(MapObjCellView, unknown_121) == 0x121);
GG_STATIC_ASSERT(offsetof(MapObjCellView, unknown_122) == 0x122);
GG_STATIC_ASSERT(offsetof(MapObjCellView, Flags) == 0x124);

// The map object at the global 0x87F7E8 (MapClass, partial; read-only here).
class MapObjMapView
{
public:
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) - the cell at a map cell coordinate (index
    // Y * 512 + X into the cell table, bounds checked). Taken by reference: OverlayClass passes
    // temporaries, and an inline pointer forwarder for the other families changes their register
    // allocation, so every caller passes the cell itself.
    MapObjCellView* GetCellAt(const MapObjCell& cell);
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) - the cell at a lepton coordinate.
    MapObjCellView* GetCellAtCoord(const MapObjCoord& coord);
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) - true when the cell coordinate is on the map.
    bool IsValid(const MapObjCell& cell);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) - the ground height at a lepton coordinate.
    int GetHeight(const MapObjCoord* coord);
    // FUNCTION: GAMEMD 0x56D460 (decl; reloc)
    void Func_56D460(const MapObjCell* cell);
    // FUNCTION: GAMEMD 0x56D5A0 (decl; reloc)
    void Func_56D5A0(const MapObjCell* cell);
    // FUNCTION: GAMEMD 0x584550 (decl; reloc)
    void Func_584550(const MapObjCell* cell);
    // FUNCTION: GAMEMD 0x6551C0 (decl; reloc)
    void Func_6551C0(const MapObjCell* cell);
    // FUNCTION: GAMEMD 0x5683C0 (decl; reloc) - puts an object on the map at a coordinate.
    void Func_5683C0(const MapObjCell* cell, MapObjClassView* object);
    // FUNCTION: GAMEMD 0x5687F0 (decl; reloc) - takes an object off the map.
    void Func_5687F0(const MapObjCell* cell, MapObjClassView* object);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapObjMapView MapObjMap;
// GLOBAL: GAMEMD 0x87F8DC - the map's far edge coordinate (the clamp used when a point is off-map).
extern short MapObjMapEdge;

// The tactical (view) object (global pointer 0x887324; read-only here).
class MapObjTacticalView
{
public:
    char unknown_00[0xB0];   // +0x00
    MapObjPoint Offset;      // +0xB0

    // FUNCTION: GAMEMD 0x6D2140 (decl; reloc) - lepton coordinate to client position.
    bool CoordsToClient(const MapObjCoord& coord, MapObjPoint* out);
    // FUNCTION: GAMEMD 0x6D2790 (decl; reloc)
    void Func_6D2790(MapObjRect rect, int arg);
    // FUNCTION: GAMEMD 0x6D6590 (decl; reloc) - the cell under a screen point, written to `out`
    // (which is also returned).
    MapObjCell* FUN_006D6590(MapObjCell* out, const MapObjPoint* point);
};
GG_STATIC_ASSERT(offsetof(MapObjTacticalView, Offset) == 0xB0);
// GLOBAL: GAMEMD 0x887324
extern MapObjTacticalView* MapObjTactical;

// The drawing surface (global pointer 0x887314; read-only here); only its pointer is passed on.
// GLOBAL: GAMEMD 0x887314
extern MapObjSurfaceView* MapObjSurface;

// The rules object (global pointer 0x8871E0; read-only here).
struct MapObjRulesView
{
    char unknown_000[0xF8];
    OverlayTypeClass* unknown_F8;     // +0xF8   three overlay types the Mark body compares against
    OverlayTypeClass* unknown_FC;     // +0xFC
    OverlayTypeClass* unknown_100;    // +0x100
    char   unknown_104[0xB94 - 0x104];
    void** unknown_B94;         // +0xB94   array of anim type pointers (the fire anims)
    char   unknown_B98[0x410];  // +0xB98
    void*  unknown_FA8;         // +0xFA8   anim type table
    char   unknown_FAC[0x198];  // +0xFAC
    int    unknown_1144;        // +0x1144  default for ObjectTypeClass +0xA0
};
GG_STATIC_ASSERT(offsetof(MapObjRulesView, unknown_F8) == 0xF8);
GG_STATIC_ASSERT(offsetof(MapObjRulesView, unknown_FC) == 0xFC);
GG_STATIC_ASSERT(offsetof(MapObjRulesView, unknown_100) == 0x100);
GG_STATIC_ASSERT(offsetof(MapObjRulesView, unknown_B94) == 0xB94);
GG_STATIC_ASSERT(offsetof(MapObjRulesView, unknown_FA8) == 0xFA8);
GG_STATIC_ASSERT(offsetof(MapObjRulesView, unknown_1144) == 0x1144);
// GLOBAL: GAMEMD 0x8871E0
extern MapObjRulesView* MapObjRules;

// The scenario object (global pointer 0xA8B230; read-only here). Its random number generator is
// embedded at +0x218.
class MapObjRandomView
{
public:
    // FUNCTION: GAMEMD 0x65C780 (decl; reloc) - the next raw value.
    unsigned int Random();
};
struct MapObjScenarioView
{
    char unknown_000[0x218];
    MapObjRandomView Random;    // +0x218
    char unknown_21C[0x1258 - 0x21C];
    int  TheaterIndex;          // +0x1258
};
GG_STATIC_ASSERT(offsetof(MapObjScenarioView, Random) == 0x218);
GG_STATIC_ASSERT(offsetof(MapObjScenarioView, TheaterIndex) == 0x1258);
// GLOBAL: GAMEMD 0xA8B230
extern MapObjScenarioView* MapObjScenario;

// Theater - one 0x70-byte record of the per-theater table; only Extension is read here.
struct MapObjTheaterView
{
    char unknown_00[0x4E];   // +0x00  names / file names
    char Extension[4];       // +0x4E  the theater's file extension
    char unknown_52[0x70 - 0x52];
};
GG_STATIC_ASSERT(offsetof(MapObjTheaterView, Extension) == 0x4E);
GG_STATIC_ASSERT(sizeof(MapObjTheaterView) == 0x70);
// GLOBAL: GAMEMD 0x7E1B78 - the theater table (entry 0's Extension is 0x7E1BC6).
extern MapObjTheaterView MapObjTheaters[];

// A loaded shape file (read-only here).
class MapObjShapeView
{
public:
    char  unknown_00[2];     // +0x00
    short Width;             // +0x02
    short Height;            // +0x04
    short FrameCount;        // +0x06
    // FUNCTION: GAMEMD 0x69E7E0 (decl; reloc) - the pixel bounds of one frame.
    MapObjRect* GetBounds(MapObjRect* out, unsigned int frame);
};
GG_STATIC_ASSERT(offsetof(MapObjShapeView, Width) == 0x2);
GG_STATIC_ASSERT(offsetof(MapObjShapeView, Height) == 0x4);
GG_STATIC_ASSERT(offsetof(MapObjShapeView, FrameCount) == 0x6);

// An animation object (AnimClass, partial; read-only here), sizeof 0x1C8.
class MapObjAnimView
{
public:
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc)
    MapObjAnimView(void* type, const MapObjCoord& where, int a, int b, unsigned int flags, int c, bool d);
    // FUNCTION: GAMEMD 0x424B50 (decl; reloc)
    void Func_424B50(MapObjClassView* object);

    char unknown_00[0xD4];      // +0x00
    void* Convert;              // +0xD4
    char unknown_D8[0xFC - 0xD8];
    int  unknown_FC;            // +0xFC
    int  unknown_100;           // +0x100
    char unknown_104[0x1C8 - 0x104];
};
GG_STATIC_ASSERT(offsetof(MapObjAnimView, Convert) == 0xD4);
GG_STATIC_ASSERT(offsetof(MapObjAnimView, unknown_FC) == 0xFC);
GG_STATIC_ASSERT(offsetof(MapObjAnimView, unknown_100) == 0x100);
GG_STATIC_ASSERT(sizeof(MapObjAnimView) == 0x1C8);

// ---- retail functions and globals bound by address -------------------------------------------------

// LIBRARY: GAMEMD 0x7C9FF0 - CRT _makepath, __cdecl.
extern "C" void __cdecl _makepath(char* path, const char* drive, const char* dir, const char* fname,
                                  const char* ext);
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) - loads the shape file of that path and returns the loaded
// image; the flag selects the load mode. __fastcall: the path in ECX, the flag in DL.
void* MapObjLoadShape(const char* path, bool flag);
// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) - draws a shape; __fastcall (surface, context), 14 stack
// dwords. The last two are one screen offset passed by value: every caller builds it from two
// zeros held in registers (`xor ecx,ecx; xor eax,eax; push ecx; push eax`) and reuses one of them
// for the other zero arguments, which is what cl does for a by-value point built from (0, 0).
void MapObjDrawShape(MapObjSurfaceView* surface, void* context, void* shape, int frame,
                     MapObjPoint* where, MapObjRect* clip, int flags, int a6, int zAdjust,
                     int a8, int a9, int a10, int a11, int a12, MapObjPoint offset);
// FUNCTION: GAMEMD 0x6D20E0 (decl; reloc) - a height scaled by a float constant, __fastcall (ECX).
int MapObjHeightScale(int value);

// GLOBAL: GAMEMD 0x886FA0 - the clip rectangle intersected with by TerrainClass::vf_65; its first two
// dwords (0x886FA0 / 0x886FA4) are the screen offset OverlayClass adds to projected positions.
extern MapObjRect MapObjClipRect;
// GLOBAL: GAMEMD 0x89F688 - the eight facing offsets (one cell step each).
extern MapObjCell MapObjFacingStep[8];
// GLOBAL: GAMEMD 0xA8E7AC - gates the map-wide fix-ups of OverlayClass::Mark and the cell placement of
// SmudgeClass::Mark (zero outside special game modes).
extern int MapObjMarkGate;
// GLOBAL: GAMEMD 0xA8ED6B - second gate of the cell placement of Mark.
extern bool MapObjMarkGateFlag;
// GLOBAL: GAMEMD 0xA8E9A0 - gates the removal work (the unplace slot) of the destructors.
extern bool MapObjRemovalEnabled;

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_COMMON_VIEWS_H
