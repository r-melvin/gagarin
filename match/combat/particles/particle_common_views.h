// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only) | behaviour-confirmed-name
//   Partial views of the retail base classes shared by the whole particle module, each declared once:
//   ObjectClass (ParticleObjectView, the base of ParticleClass and ParticleSystemClass),
//   ObjectTypeClass (ParticleTypeObjectView, the base of ParticleTypeClass and
//   ParticleSystemTypeClass), the three secondary interface bases, the CRC engine, the INI reader,
//   the pointer-swizzle manager, and the map / cell / house objects the bodies read.
//   Everything was read from the retail gamemd.exe v1.001:
//     ParticleClass          RTTI .?AVParticleClass@@ (TD 0x8366E8), COLs 0x807BE8 / 0x807B78 /
//                            0x807B60 / 0x807B48, tables 0x7EF954 (123 slots) / 0x7EF938 / 0x7EF930 /
//                            0x7EF928
//     ParticleSystemClass    RTTI .?AVParticleSystemClass@@ (TD 0x836748), COLs 0x807CA0 / 0x807C30 /
//                            0x807C18 / 0x807C00, tables 0x7EFB9C (122 slots) / 0x7EFB80 / 0x7EFB78 /
//                            0x7EFB70
//     ParticleTypeClass      RTTI .?AVParticleTypeClass@@ (TD 0x8370D0), tables 0x7F0188 (40 slots) /
//                            0x7F016C / 0x7F0164 / 0x7F015C
//     ParticleSystemTypeClass tables 0x7F00A8 (40 slots) / 0x7F008C / 0x7F0084 / 0x7F007C
//   and the ObjectClass / ObjectTypeClass / AbstractClass constructors 0x5F3900 / 0x5F7090 / 0x410170.
//
// The views never claim to be ObjectClass / ObjectTypeClass: the inherited slots and the base-class
// bodies are READ-ONLY dependencies of the module, bound by address (see the rows files). Slot numbers
// are the retail primary-table indices. ParticleObjectView carries slots 0..121, which both object
// classes share; ParticleClass adds slot 122 itself.
//
// Calling conventions (proven by the prologues/epilogues of the bodies): the IPersistStream slots 0-7
// are __stdcall with `this` as the first stack argument; every other slot is __thiscall (this in ECX,
// callee pops its arguments). The slot names that carry a meaning (PointerExpired, WhatAmI, Size,
// ComputeCRC, IsFinished, GetCoords, Update, InWhichLayer, GetType, Unlimbo, MarkFinished, ReadINI) are
// the ones a recovered body proves; the rest are positional (vf_N).
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_VIEWS_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_VIEWS_H

#include "particle_common_types.h"
#include "particle_common_vectors.h"

class ParticleColorList;
class ParticleTypeObjectView;

// Secondary base at +0x04: the IRTTITypeInfo table (6 slots; 0x7EF938 / 0x7EFB80 / 0x7F016C /
// 0x7F008C). Slots 0-2 are the IUnknown adjustor thunks (0x4105E0 / 0x4105F0 / 0x410600), slots 3-5 are
// the bodies 0x410210 (`RET 4`, calls slot 11) / 0x410220 (`MOV EAX,[ECX+0xC]; RET 4`) / 0x410230,
// implemented once for every object and compiled with the subobject `this`.
struct ParticleRttiBase
{
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0  0x4105E0 (thunk)
    virtual ULONG __stdcall AddRef();                                     // 1  0x4105F0 (thunk)
    virtual ULONG __stdcall Release();                                    // 2  0x410600 (thunk)
    virtual int __stdcall What_Am_I();                                    // 3  0x410210
    virtual int __stdcall Fetch_ID();                                     // 4  0x410220
    // 5  0x410230: stores the id (global 0xA8B230 based) into the subobject's +0x0C. The
    //    constructors call it once, bound directly (the final overrider is known there).
    virtual void __stdcall Create_ID();
};
GG_STATIC_ASSERT(sizeof(ParticleRttiBase) == 4);

// Secondary base at +0x08: INoticeSink table (0x7EF930 / 0x7EFB78 / 0x7F0164 / 0x7F0084), one slot
// (0x410580: `XOR AL,AL; RET 8`).
struct ParticleNoticeSinkBase
{
    virtual bool __stdcall NoticeSink(int arg);   // 0  0x410580
};
GG_STATIC_ASSERT(sizeof(ParticleNoticeSinkBase) == 4);

// Secondary base at +0x0C: INoticeSource table (0x7EF928 / 0x7EFB70 / 0x7F015C / 0x7F007C), one slot
// (0x410590: bare `RET 4`).
struct ParticleNoticeSourceBase
{
    virtual void __stdcall NoticeSource();   // 0  0x410590
};
GG_STATIC_ASSERT(sizeof(ParticleNoticeSourceBase) == 4);

// The CRC accumulator the CRC slots feed (read-only here). Each entry takes one value.
class ParticleCrcView
{
public:
    // FUNCTION: GAMEMD 0x4A1C10 (read-only here)
    void AddByte(unsigned char value);
    // FUNCTION: GAMEMD 0x4A1CA0 (read-only here)
    void AddBool(bool value);
    // FUNCTION: GAMEMD 0x4A1D50 (read-only here)
    void AddInt(int value);
    // FUNCTION: GAMEMD 0x4A1D70 (read-only here)
    void AddFloat(float value);
    // FUNCTION: GAMEMD 0x4A1D90 (read-only here)
    void AddDouble(double value);
};

// The rules INI reader (read-only here). Every Read* is __thiscall with the section name and the key
// as the first two arguments and the default value last; the value types are returned by value
// (through a hidden pointer for the aggregate ones).
class ParticleIniView
{
public:
    // FUNCTION: GAMEMD 0x526B00 (read-only here) - clears the reader's two cached positions
    void ClearCache();
    // FUNCTION: GAMEMD 0x5276D0 (read-only here)
    int ReadInt(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x5283D0 (read-only here)
    double ReadDouble(const char* section, const char* key, double defaultValue);
    // FUNCTION: GAMEMD 0x5295F0 (read-only here)
    bool ReadBool(const char* section, const char* key, bool defaultValue);
    // FUNCTION: GAMEMD 0x528A10 (read-only here) - the length read, 0 when the key is absent.
    int ReadString(const char* section, const char* key, const char* defaultValue, char* buffer, int size);
    // FUNCTION: GAMEMD 0x476420 (read-only here)
    ParticleCoord ReadCoord(const char* section, const char* key, const ParticleCoord& defaultValue);
    // FUNCTION: GAMEMD 0x476340 (read-only here) - a different entry from ReadCoord (0x476420); the
    // system type's reader calls this one.
    ParticleCoord ReadPoint3D(const char* section, const char* key, const ParticleCoord& defaultValue);
    // FUNCTION: GAMEMD 0x474B50 (read-only here)
    ParticleColor ReadColor(const char* section, const char* key, const ParticleColor& defaultValue);
    // FUNCTION: GAMEMD 0x476B20 (read-only here) - a comma-separated colour list.
    ParticleColorList ReadColors(const char* section, const char* key, ParticleColorList defaultValue);
};

// GLOBAL: GAMEMD 0xB0C110 - the pointer-swizzle manager object used by every Load (read-only here).
// The entry below is __stdcall with the manager as the first stack argument (`this`).
class ParticleSwizzleView
{
public:
    // FUNCTION: GAMEMD 0x6CF240 (read-only here) - registers one pointer field for fix-up after a load.
    void __stdcall Swizzle(void** pointerField);
};
extern ParticleSwizzleView ParticleSwizzle;

// FUNCTION: GAMEMD 0x7258D0 (read-only here) - announces that a pointer is going away. __fastcall:
// the object in ECX, the flag in DL. Every destructor calls it with 1 (the object is gone) to tell
// each holder to drop its pointer.
void ParticleAnnouncePointerExpired(void* object, bool removed);

// HouseClass (partial): only the field ParticleSystemClass reads.
struct ParticleHouseView
{
    unsigned char unknown_00[0x2B4];
    int           unknown_2B4;
};
GG_STATIC_ASSERT(offsetof(ParticleHouseView, unknown_2B4) == 0x2B4);

// CellClass (partial).
struct ParticleCellView
{
    unsigned char unknown_00[0x140];
    unsigned int  Flags;             // +0x140
};
GG_STATIC_ASSERT(offsetof(ParticleCellView, Flags) == 0x140);

// The map object at the global 0x87F7E8 (MapClass, partial; read-only here).
class ParticleMapView
{
public:
    // FUNCTION: GAMEMD 0x578080 (read-only here) - the ground height at a lepton coordinate.
    int GetHeight(const ParticleCoord* coord);
    // FUNCTION: GAMEMD 0x5865E0 (read-only here) - true when the position is hidden by the shroud.
    bool FUN_005865E0(const ParticleCoord* coord);
    // FUNCTION: GAMEMD 0x565730 (read-only here) - the cell at a lepton coordinate.
    ParticleCellView* GetCellAt(const ParticleCoord& coord);
};
// GLOBAL: GAMEMD 0x87F7E8
extern ParticleMapView ParticleMap;

// ObjectClass-shaped base of ParticleClass and ParticleSystemClass (sizeof 0xAC). The address after
// each slot is the retail body of that slot in the base table; the classes of this module override
// some of them (0x62xxxx / 0x63xxxx bodies are defined by the module, anything else is inherited and
// READ-ONLY here).
// VTABLE: GAMEMD 0x7EF954 / 0x7EFB9C (IPersistStream side, 123 / 122 slots), GAMEMD 0x7EF938 /
//         0x7EFB80 (IRTTITypeInfo side, 6 slots), GAMEMD 0x7EF930 / 0x7EFB78 (INoticeSink side, 1
//         slot), GAMEMD 0x7EF928 / 0x7EFB70 (INoticeSource side, 1 slot)
//
// Layout (from the ObjectClass constructor's stores):
//   +0x00 IPersistStream vptr (primary), +0x04 IRTTITypeInfo vptr, +0x08 INoticeSink vptr,
//   +0x0C INoticeSource vptr, +0x10..+0x23 AbstractClass members, +0x24..+0x9B ObjectClass members
//   (+0x90 IsAlive, ctor 1), +0x9C Location (three dwords), +0xA8 last ObjectClass member.
class ParticleObjectView : public IPersistStream, public ParticleRttiBase,
                           public ParticleNoticeSinkBase, public ParticleNoticeSourceBase
{
public:
    // FUNCTION: GAMEMD 0x5F3900 (ObjectClass constructor; read-only here)
    ParticleObjectView();
    // FUNCTION: GAMEMD 0x5F3B50 (ObjectClass no-init constructor; read-only here)
    ParticleObjectView(const ParticleNoInit& noInit);

    // FUNCTION: GAMEMD 0x40DD70 (read-only here) - the house that owns the object.
    ParticleHouseView* GetOwnerHouse();

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);       // 0   0x410260
    virtual ULONG __stdcall AddRef();                                        // 1   0x410300
    virtual ULONG __stdcall Release();                                       // 2   0x410310
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                   // 3   overridden by both module classes (base body not recovered)
    virtual HRESULT __stdcall IsDirty();                                     // 4   0x410450
    virtual HRESULT __stdcall Load(IStream* pStm);                           // 5   base 0x5F5E80; overridden in the module
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);         // 6   base 0x410320; overridden in the module
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);           // 7   0x4103E0
    virtual ~ParticleObjectView();                                           // 8   base 0x5F3B80; overridden in the module
    virtual void vf_9();                                                     // 9   0x410470
    virtual void PointerExpired(void* ptr, bool removed);                    // 10  base 0x5F5230; overridden in the module
    virtual int WhatAmI();                                                   // 11  overridden by both module classes (base body not recovered)
    virtual int Size();                                                      // 12  overridden by both module classes (base body not recovered)
    virtual void ComputeCRC(ParticleCrcView& crc);                           // 13  base 0x5F6250; overridden in the module
    virtual void vf_14();                                                    // 14  0x410490
    virtual void vf_15();                                                    // 15  0x4104A0
    virtual void vf_16();                                                    // 16  0x4104B0
    virtual bool IsFinished();                                               // 17  base 0x5F6690; overridden in the module
    virtual ParticleCoord GetCoords();                                       // 18  0x5F65A0
    virtual void vf_19();                                                    // 19  0x4104F0
    virtual void vf_20();                                                    // 20  0x5F6B60
    virtual void vf_21();                                                    // 21  0x5F6B90
    virtual void vf_22();                                                    // 22  0x410540
    virtual void Update();                                                   // 23  base 0x5F3E70; overridden in the module
    virtual void vf_24();                                                    // 24  0x5F6DA0
    virtual void vf_25();                                                    // 25  0x426390
    virtual void vf_26();                                                    // 26  0x4263A0
    virtual void* vf_27();                                                   // 27  0x5F3E30
    virtual void vf_28();                                                    // 28  0x5F4250
    virtual void vf_29();                                                    // 29  0x5F4240
    virtual int InWhichLayer();                                              // 30  overridden by both module classes (base body not recovered)
    virtual void vf_31();                                                    // 31  0x5F6C10
    virtual void vf_32();                                                    // 32  0x4263B0
    virtual void vf_33();                                                    // 33  0x5F6BC0
    virtual ParticleTypeObjectView* GetType();                               // 34  overridden by both module classes (base body not recovered)
    virtual void vf_35();                                                    // 35  0x5F42A0
    virtual void vf_36();                                                    // 36  0x4263C0
    virtual void vf_37();                                                    // 37  0x5F42B0
    virtual void vf_38();                                                    // 38  0x5F42C0
    virtual void vf_39();                                                    // 39  0x5F42D0
    virtual void vf_40();                                                    // 40  0x5F42E0
    virtual void vf_41();                                                    // 41  0x41BDD0
    virtual void vf_42();                                                    // 42  0x5F6C80
    virtual void vf_43();                                                    // 43  0x41BE00
    virtual void vf_44();                                                    // 44  0x4263D0
    virtual void vf_45();                                                    // 45  0x41BE30
    virtual void vf_46();                                                    // 46  0x5F6BD0
    virtual void vf_47();                                                    // 47  0x5F6A70
    virtual void vf_48();                                                    // 48  0x426410
    virtual void vf_49();                                                    // 49  0x426420
    virtual void vf_50();                                                    // 50  0x426430
    virtual void vf_51();                                                    // 51  0x41BE60
    virtual void vf_52();                                                    // 52  0x41BE70
    virtual void vf_53();                                                    // 53  0x5F4D30
    virtual bool Unlimbo(ParticleCoord* where, int facing);                  // 54  0x5F4EC0
    virtual void vf_55();                                                    // 55  0x5F5280
    virtual void vf_56();                                                    // 56  0x5F42F0
    virtual void vf_57();                                                    // 57  0x5F4300
    virtual void vf_58();                                                    // 58  0x5F5940
    virtual void vf_59();                                                    // 59  0x5F4160
    virtual void vf_60();                                                    // 60  0x5F60A0
    virtual void vf_61();                                                    // 61  0x5F6120
    virtual void MarkFinished();                                             // 62  base 0x5F65F0; overridden in the module
    virtual void vf_63();                                                    // 63  0x5F4310
    virtual void vf_64();                                                    // 64  0x5F4320
    virtual void vf_65();                                                    // 65  0x5F4B10
    virtual ParticleCellCoord* vf_66(void* unused);                          // 66  base 0x5F5B90; overridden in the module
    virtual void vf_67();                                                    // 67  0x426440
    virtual void vf_68();                                                    // 68  0x426450
    virtual void vf_69(void* where, ParticleRect* clip);                     // 69  overridden by both module classes (base body not recovered)
    virtual void vf_70();                                                    // 70  0x5F65D0
    virtual void vf_71();                                                    // 71  0x5F4330
    virtual void vf_72();                                                    // 72  0x5F4340
    virtual bool vf_73(int arg);                                             // 73  base 0x5F5850; overridden in the module
    virtual void vf_74();                                                    // 74  0x5F4730
    virtual void vf_75();                                                    // 75  0x5F4870
    virtual void vf_76();                                                    // 76  0x41BE80
    virtual void vf_77();                                                    // 77  0x5F4D10
    virtual void vf_78();                                                    // 78  0x5F6C30
    virtual void vf_79();                                                    // 79  0x5F6C70
    virtual void vf_80();                                                    // 80  0x5F4360
    virtual void vf_81();                                                    // 81  0x5F4350
    virtual void vf_82();                                                    // 82  0x5F4370
    virtual void vf_83();                                                    // 83  0x5F4520
    virtual void vf_84();                                                    // 84  0x5F44A0
    virtual void vf_85();                                                    // 85  0x426460
    virtual void vf_86();                                                    // 86  0x426470
    virtual void vf_87();                                                    // 87  0x426480
    virtual void vf_88();                                                    // 88  0x426490
    virtual void vf_89();                                                    // 89  0x5F4380
    virtual void vf_90();                                                    // 90  0x5F4390
    virtual void vf_91();                                                    // 91  0x5F5390
    virtual void vf_92();                                                    // 92  0x4264A0
    virtual void vf_93();                                                    // 93  0x5F43A0
    virtual void vf_94();                                                    // 94  0x5F43B0
    virtual void vf_95();                                                    // 95  0x5F43C0
    virtual void vf_96();                                                    // 96  0x5F43D0
    virtual void vf_97();                                                    // 97  0x5F43E0
    virtual void vf_98();                                                    // 98  0x41BE90
    virtual void vf_99();                                                    // 99  0x4264B0
    virtual void vf_100();                                                   // 100 0x5F5C20
    virtual void vf_101();                                                   // 101 0x5F5320
    virtual void vf_102();                                                   // 102 0x5F5930
    virtual void vf_103();                                                   // 103 0x5F43F0
    virtual void vf_104();                                                   // 104 0x5F4400
    virtual void vf_105();                                                   // 105 0x5F6B50
    virtual void vf_106();                                                   // 106 0x5F4410
    virtual void vf_107();                                                   // 107 0x4264C0
    virtual void vf_108();                                                   // 108 0x4264D0
    virtual void vf_109(ParticleCoord* where);                               // 109 0x5F6940
    virtual void vf_110();                                                   // 110 0x41BEA0
    virtual void vf_111();                                                   // 111 0x5F6960
    virtual void vf_112();                                                   // 112 0x5F69C0
    virtual void vf_113();                                                   // 113 0x5F6A10
    virtual void vf_114();                                                   // 114 0x5F5F40
    virtual void vf_115();                                                   // 115 0x5F5FA0
    virtual int vf_116();                                                    // 116 0x5F5F30
    virtual void vf_117();                                                   // 117 0x4264E0
    virtual void vf_118();                                                   // 118 0x4264F0
    virtual void vf_119();                                                   // 119 0x426500
    virtual void vf_120();                                                   // 120 0x426510
    virtual void vf_121();                                                   // 121 0x426520

    // ---- members (complete-object offsets) --------------------------------------------------
    char            unknown_10[0x80];    // +0x10..+0x8F  AbstractClass / ObjectClass members
    unsigned char   IsAlive;             // +0x90         ObjectClass, ctor 1
    unsigned char   unknown_91[0xB];     // +0x91..+0x9B
    ParticleCoord   Location;            // +0x9C         ObjectClass::Location (ctor copy of 0xAC1380)
    int             unknown_A8;          // +0xA8         last ObjectClass member (ctor 0)
};

GG_STATIC_ASSERT(sizeof(IPersistStream) == 4);
GG_STATIC_ASSERT(offsetof(ParticleObjectView, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ParticleObjectView, IsAlive) == 0x90);
GG_STATIC_ASSERT(offsetof(ParticleObjectView, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(ParticleObjectView, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(sizeof(ParticleObjectView) == 0xAC);

// ObjectTypeClass-shaped base of ParticleTypeClass and ParticleSystemTypeClass (sizeof 0x294). Slot
// numbers are the retail primary-table indices (tables 0x7F0188 / 0x7F00A8, 40 slots); the address
// after each slot is the retail body in the base table.
// VTABLE: GAMEMD 0x7F0188 / 0x7F00A8 (IPersistStream side, 40 slots), GAMEMD 0x7F016C / 0x7F008C
//         (IRTTITypeInfo side), GAMEMD 0x7F0164 / 0x7F0084 (INoticeSink side), GAMEMD 0x7F015C /
//         0x7F007C (INoticeSource side)
class ParticleTypeObjectView : public IPersistStream, public ParticleRttiBase,
                               public ParticleNoticeSinkBase, public ParticleNoticeSourceBase
{
public:
    // FUNCTION: GAMEMD 0x5F7090 (ObjectTypeClass named constructor; read-only here)
    ParticleTypeObjectView(const char* id);
    // FUNCTION: GAMEMD 0x5F7320 (ObjectTypeClass no-init constructor; read-only here)
    ParticleTypeObjectView(const ParticleNoInit& noInit);
    // FUNCTION: GAMEMD 0x5F9070 (read-only here) - ObjectTypeClass work after a load.
    void PostLoad();

    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);       // 0   0x410260
    virtual ULONG __stdcall AddRef();                                        // 1   0x410300
    virtual ULONG __stdcall Release();                                       // 2   0x410310
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                   // 3   overridden by both module classes (base body not recovered)
    virtual HRESULT __stdcall IsDirty();                                     // 4   0x410450
    virtual HRESULT __stdcall Load(IStream* pStm);                           // 5   base 0x5F9720; overridden in the module
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);         // 6   base 0x5F9950; overridden in the module
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);           // 7   0x5F9970
    virtual ~ParticleTypeObjectView();                                       // 8   base 0x5F7400; overridden in the module
    virtual void vf_9();                                                     // 9   0x410470
    virtual void PointerExpired(void* ptr, bool removed);                    // 10  base 0x410480; overridden in the module
    virtual int WhatAmI();                                                   // 11  overridden by both module classes (base body not recovered)
    virtual int Size();                                                      // 12  overridden by both module classes (base body not recovered)
    virtual void ComputeCRC(ParticleCrcView& crc);                           // 13  base 0x410BE0; overridden in the module
    virtual void vf_14();                                                    // 14  0x410490
    virtual void vf_15();                                                    // 15  0x4104A0
    virtual void vf_16();                                                    // 16  0x4104B0
    virtual void vf_17();                                                    // 17  0x410440
    virtual void vf_18();                                                    // 18  0x4104C0
    virtual void vf_19();                                                    // 19  0x4104F0
    virtual void vf_20();                                                    // 20  0x410520
    virtual void vf_21();                                                    // 21  0x410530
    virtual void vf_22();                                                    // 22  0x410540
    virtual void vf_23();                                                    // 23  0x410570
    virtual void vf_24();                                                    // 24  0x410C20
    virtual bool ReadINI(ParticleIniView* ini);                              // 25  base 0x5F92D0; overridden in the module
    virtual void vf_26();                                                    // 26  0x410B90
    virtual void vf_27();                                                    // 27  0x41CF80
    virtual void vf_28();                                                    // 28  0x428E40
    virtual void vf_29();                                                    // 29  0x5F75B0
    virtual void vf_30();                                                    // 30  0x5F75C0
    virtual void vf_31();                                                    // 31  0x5F75E0
    virtual bool vf_32(int a, int b);                                        // 32  overridden by both module classes (base body not recovered)
    virtual void vf_33();                                                    // 33  0x5F7610
    virtual void vf_34();                                                    // 34  0x5F7620
    virtual int vf_35(int a);                                                // 35  overridden by both module classes (base body not recovered)
    virtual void vf_36();                                                    // 36  0x5F7640
    virtual void vf_37();                                                    // 37  0x5F7900
    virtual void vf_38();                                                    // 38  0x5F7630
    virtual void vf_39();                                                    // 39  0x41CFA0

    char unknown_10[0x14];    // +0x10..+0x23  AbstractClass members
    char ID[0x18];            // +0x24         AbstractTypeClass::ID, the INI section name
    char unknown_3C[0x1F8];   // +0x3C..+0x233  AbstractTypeClass / ObjectTypeClass members
    unsigned char unknown_234; // +0x234        ctor 0 (the derived constructors store 0 / 1 here)
    char unknown_235[0x5F];   // +0x235..+0x293
};

GG_STATIC_ASSERT(offsetof(ParticleTypeObjectView, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ParticleTypeObjectView, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(ParticleTypeObjectView, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(ParticleTypeObjectView, unknown_234) == 0x234);
GG_STATIC_ASSERT(sizeof(ParticleTypeObjectView) == 0x294);

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_VIEWS_H
