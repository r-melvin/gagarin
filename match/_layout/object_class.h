// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ObjectClass ctor FUN_0x005F3900 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0). Every member offset below is read directly
//   from a field-init write in that ctor; cross-checked vs YRpp.
//   Key confirmations: NextObject @0x30 (param[0xC]), AmbientSoundController
//   ctor FUN_0x00405BE0(this+0x3C) / CustomSoundController(this+0x50) prove
//   sizeof(AudioController)==0x14, Location.{X,Y,Z} @0x9C/0xA0/0xA4,
//   LineTrailer @0xA8 (last member) -> sizeof(ObjectClass)==0xAC.
//   The retail RTTI TypeDescriptor at 0x00817AF8 is named ".?AVObjectClass@@",
//   confirming the class-key; offsets and fields remain grounded in the
//   constructor stores below.
//
// ObjectClass — base of every drawable/placeable game-object INSTANCE (units,
// buildings, infantry, aircraft, anims, bullets, terrain, ...). Derives
// AbstractClass (the four COM vptrs + UniqueID/AbstractFlags/RefCount/Dirty)
// at offset 0 and adds the shared instance bookkeeping from 0x24.
#ifndef GG_MATCH_LAYOUT_OBJECT_CLASS_H
#define GG_MATCH_LAYOUT_OBJECT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"

class TagClass;
class HouseClass;
class AnimClass;
class ObjectTypeClass;
// Returned by value from slots 110 and 112 (defined by the TUs that need it;
// several unguarded definitions exist across the tree).
struct CellStruct;
class TechnoTypeClass;
class CellClass;
struct RectangleStruct;   // geometry2d.h
struct Point2D;           // geometry2d.h

// --- shared instance-side leaf components -----------------------------------
// Self-guarded so a downstream layer in the same chain can reuse them.

// CoordStruct — absolute 3D lepton coordinate (3 ints, sizeof = 0xC).
#include "coord_struct.h"
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// AudioController — the "mofo" audio-event controller (sizeof = 0x14). Size
// proven by the two back-to-back ctor calls FUN_0x00405BE0(this+0x3C) and
// (this+0x50): the 0x14 stride is the AudioController size.
#ifndef GG_MATCH_LAYOUT_AUDIOCONTROLLER_DEFINED
#define GG_MATCH_LAYOUT_AUDIOCONTROLLER_DEFINED
struct AudioController
{
    void* Event;        // +0x00  AudioEventTag* (truncation)
    int   Stamp;        // +0x04
    void* EventType;    // +0x08  VocClass* (truncation)
    void* AudioIndex;   // +0x0C  AudioIDXData** (truncation)
    int   Unused;       // +0x10

    // FUNCTION: GAMEMD 0x405D40 (declaration)
    void FUN_00405D40();
    // FUNCTION: GAMEMD 0x405FD0 (declaration)
    void FUN_00405FD0();
};
GG_STATIC_ASSERT(offsetof(AudioController, Stamp)     == 0x04);
GG_STATIC_ASSERT(offsetof(AudioController, EventType) == 0x08);
GG_STATIC_ASSERT(sizeof(AudioController)              == 0x14);
#endif  // GG_MATCH_LAYOUT_AUDIOCONTROLLER_DEFINED

// ObjectClass  (0x24..0xAB, sizeof = 0xAC)
// VTABLE: GAMEMD 0x7EF060
// VTABLE: GAMEMD 0x7EF044
// VTABLE: GAMEMD 0x7EF03C
// VTABLE: GAMEMD 0x7EF034
class ObjectClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x005F3E50 (decl; reloc)
    // ObjectClass::FUN_005F3E50
    bool FUN_005F3E50(const char* text);
    // FUNCTION: GAMEMD 0x5F3900 (declaration; native base constructor)
    ObjectClass();
    // FUNCTION: GAMEMD 0x5F3B50 -- restores class tables without member stores.
    ObjectClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x5F3B80 (declaration; destructor)
    virtual ~ObjectClass();
    // FUNCTION: GAMEMD 0x5F5B50
    bool AttachTrigger(TagClass* tag);
    // FUNCTION: GAMEMD 0x5F5C60
    double GetHealthPercentage() const;
    // FUNCTION: GAMEMD 0x5F5C80
    void SetHealthPercentage(double percentage);
    // FUNCTION: GAMEMD 0x5F5CD0
    bool IsRedHP() const;
    // FUNCTION: GAMEMD 0x5F5D20 (original name unconfirmed)
    int FUN_005F5D20() const;
    // FUNCTION: GAMEMD 0x5F5DD0
    int GetHealthStatus() const;
    // FUNCTION: GAMEMD 0x5F5F00
    int GetCellLevel() const;
    // FUNCTION: GAMEMD 0x5F6220 (original name unconfirmed)
    bool FUN_005F6220(ObjectClass* other);
    // CALLEE: GAMEMD 0x5F6360 (decl; Bullet's native call passes an
    // AbstractClass target and receives the scalar distance in EAX.
    int FUN_005F6360(AbstractClass* target);
    // FUNCTION: GAMEMD 0x5F6CD0
    bool IsCrushable(ObjectClass* crusher);

    // Overrides of AbstractClass slots (primary table 0x7EF060).
    // FUNCTION: GAMEMD 0x5F5E80 (declaration; slot 5)
    virtual HRESULT __stdcall Load(IStream* pStm);
    // FUNCTION: GAMEMD 0x5F5230 (declaration; slot 10)
    virtual void vf_10(void* a1, bool a2);
    // FUNCTION: GAMEMD 0x5F6250 (declaration; slot 13)
    virtual void vf_13(Obj_004A1D30* crc);
    // FUNCTION: GAMEMD 0x5F6690 (declaration; slot 17)
    virtual bool vf_17();
    // FUNCTION: GAMEMD 0x5F65A0 (declaration; slot 18)
    virtual CoordStruct vf_18();
    // FUNCTION: GAMEMD 0x5F6B60
    virtual bool IsOnFloor() const;                    // 20
    // FUNCTION: GAMEMD 0x5F6B90
    virtual bool IsInAir() const;                      // 21
    // FUNCTION: GAMEMD 0x5F3E70 (declaration; slot 23)
    virtual void vf_23();

    // Slots 24-121, introduced by ObjectClass (122 slots in all, RTTI
    // ".?AVObjectClass@@" on 0x7EF060). Names are placeholders except where a
    // tree row already carries one; argument counts come from RET n and the
    // return types from each base body's EAX/AL use.
    virtual void vf_24(void* a1);                              // 24  0x5F6DA0
    virtual bool vf_25();                                      // 25  0x426390: returns false
    virtual int vf_26(int a1, int a2);                         // 26  0x4263A0: returns 0
    virtual void* vf_27();                                     // 27  0x5F3E30: forwards to the type's slot 39
    virtual int vf_28(int a1, int a2, int a3);                 // 28  0x5F4250: returns 0
    virtual int vf_29(int a1, int a2);                         // 29  0x5F4240: returns 0
    virtual int vf_30();                                       // 30  0x5F4260: layer
    virtual bool vf_31();                                      // 31  0x5F6C10
    virtual bool vf_32();                                      // 32  0x4263B0: returns false
    virtual TechnoTypeClass* vf_33();                          // 33  0x5F6BC0
    virtual ObjectTypeClass* vf_34();                          // 34  0x4E0130: returns null; every class overrides it
    virtual int vf_35();                                       // 35  0x5F42A0: returns 0x7FFFFFFF
    virtual const wchar_t* vf_36();                            // 36  0x4263C0: returns L"No name"
    virtual bool vf_37();                                      // 37  0x5F42B0: returns false
    virtual bool vf_38();                                      // 38  0x5F42C0: returns false
    virtual bool vf_39();                                      // 39  0x5F42D0: returns false
    virtual bool vf_40();                                      // 40  0x5F42E0: returns false
    virtual CoordStruct vf_41();                               // 41  0x41BDD0: returns vf_18()
    virtual CoordStruct vf_42(AbstractClass* target);          // 42  0x5F6C80; BuildingClass 0x447E00 passes the object whose slot 18 it reads
    virtual CoordStruct vf_43();                               // 43  0x41BE00: returns vf_18()
    virtual CoordStruct vf_44(int a1, int a2, int a3, int a4); // 44  0x4263D0: vf_18() raised by 50
    virtual CoordStruct vf_45(int a1);                         // 45  0x41BE30: returns vf_18()
    virtual int GetYSort() const;                              // 46  0x5F6BD0
    virtual bool vf_47(AbstractClass* target);                 // 47  0x5F6A70: forwards its argument to slot 19
    virtual bool vf_48();                                      // 48  0x426410: returns true
    virtual bool vf_49();                                      // 49  0x426420: returns false
    virtual bool vf_50(HouseClass* house);                     // 50  0x426430: returns false
    virtual ObjectTypeClass* vf_51(bool a1);                   // 51  0x41BE60: returns 0
    virtual HouseClass* vf_52(bool a1);                        // 52  0x41BE70: returns 0
    virtual bool vf_53();                                      // 53  0x5F4D30
    virtual bool vf_54(const CoordStruct& coord, int a2);       // 54  0x5F4EC0
    virtual void vf_55(bool removed);                          // 55  0x5F5280
    virtual void vf_56(void* source);                          // 56  0x5F42F0: bare RET 4; vf_91 passes the attacker
    virtual void vf_57(void* house);                           // 57  0x5F4300: bare RET 4; vf_91 passes the house
    virtual bool vf_58(const CoordStruct& coord);              // 58  0x5F5940
    virtual void vf_59();                                      // 59  0x5F4160
    virtual void vf_60(CoordStruct* coord);                    // 60  0x5F60A0
    virtual void vf_61(CoordStruct* coord);                    // 61  0x5F6120
    virtual void vf_62();                                      // 62  0x5F65F0
    virtual void vf_63();                                      // 63  0x5F4310: bare RET
    virtual int vf_64(int a1, int a2);                         // 64  0x5F4320: returns 0
    virtual bool vf_65(RectangleStruct* rect, bool force, int a3); // 65  0x5F4B10
    virtual void* vf_66(int a1);                               // 66  0x5F5B90
    // 6D9076/6D9134 push viewport and point addresses for slots67/68.
    virtual void vf_67(Point2D* point, RectangleStruct* clip);                        // 67  0x426440: bare RET 8
    virtual void vf_68(Point2D* point, RectangleStruct* clip);                        // 68  0x426450: bare RET 8
    virtual void vf_69(Point2D* point, RectangleStruct* clip); // 69  0x5B3A50: bare RET 8; vf_65 passes (&point, rect)
    virtual void vf_70(Point2D* point, RectangleStruct* clip); // 70  0x5F65D0: forwards to vf_69
    virtual void vf_71();                                      // 71  0x5F4330: bare RET
    virtual void vf_72(int a1, int a2);                        // 72  0x5F4340: bare RET 8
    virtual bool vf_73(int mode);                              // 73  0x5F5850
    virtual RectangleStruct vf_74();                           // 74  0x5F4730
    virtual RectangleStruct vf_75();                           // 75  0x5F4870
    virtual void vf_76(int a1);                                // 76  0x41BE80: bare RET 4
    virtual void vf_77();                                      // 77  0x5F4D10
    virtual bool vf_78();                                      // 78  0x5F6C30
    virtual bool vf_79();                                      // 79  0x5F6C70: returns vf_78()
    virtual bool vf_80(int a1, int a2, int a3, int a4);        // 80  0x5F4360: returns false
    virtual bool vf_81(int a1, int a2, int a3);                // 81  0x5F4350: returns false
    virtual void vf_82(int a1);                                // 82  0x5F4370: bare RET 4
    virtual bool vf_83();                                      // 83  0x5F4520
    virtual void vf_84();                                      // 84  0x5F44A0
    virtual void vf_85(int a1, int a2, bool a3);               // 85  0x426460: bare RET 0xC
    virtual void vf_86();                                      // 86  0x426470: bare RET
    virtual void vf_87(int a1);                                // 87  0x426480: bare RET 4
    virtual bool vf_88();                                      // 88  0x426490: returns false
    virtual bool vf_89(const CoordStruct& coord, int a2);      // 89  0x5F4380: returns false
    virtual int vf_90(int a1);                                 // 90  0x5F4390: returns 0
    virtual int vf_91(int* damage, int distance, void* warhead, void* source, bool a5, bool a6, void* house); // 91  0x5F5390
    virtual void vf_92();                                      // 92  0x4264A0: bare RET
    virtual void vf_93(int a1, int a2, int a3);                // 93  0x5F43A0: bare RET 0xC
    virtual bool vf_94();                                      // 94  0x5F43B0: returns false
    virtual void vf_95();                                      // 95  0x5F43C0: bare RET
    virtual int vf_96();                                       // 96  0x5F43D0: returns 0
    virtual int vf_97();                                       // 97  0x5F43E0: returns -1
    virtual void vf_98(int a1);                                // 98  0x41BE90: bare RET 4
    virtual void vf_99(int a1);                                // 99  0x4264B0: bare RET 4
    virtual void vf_100(bool a1, bool a2);                     // 100 0x5F5C20
    virtual int vf_101(int a1, int event, int a3);             // 101 0x5F5320
    virtual bool vf_102(HouseClass* house);                    // 102 0x5F5930: TechnoClass 0x6F4960 tests its AL
    virtual void vf_103(int a1);                               // 103 0x5F43F0: bare RET 4
    virtual void vf_104(int a1);                               // 104 0x5F4400: bare RET 4
    virtual void vf_105(int a1, int a2);                       // 105 0x5F6B50: bare RET 8
    virtual void vf_106(int a1);                               // 106 0x5F4410
    virtual int vf_107(CellClass* cell, int a2, int a3, int a4, int a5); // 107 0x4264C0: returns 0
    virtual int vf_108(int a1, int a2, int a3, int a4, int a5); // 108 0x4264D0: returns 0
    virtual void vf_109(const CoordStruct& coord);             // 109 0x5F6940
    virtual CellStruct vf_110();                               // 110 0x41BEA0: the cell under Location
    virtual CellClass* vf_111();                               // 111 0x5F6960
    virtual CellStruct vf_112();                               // 112 0x5F69C0
    virtual CellClass* vf_113();                                     // 113 0x5F6A10
    virtual int vf_114();                                      // 114 0x5F5F40
    virtual void vf_115(int height);                           // 115 0x5F5FA0
    virtual int FUN_005F5F30() const;                          // 116 0x5F5F30
    virtual bool vf_117();                                     // 117 0x4264E0: returns false
    virtual bool vf_118();                                     // 118 0x4264F0: returns false
    virtual bool vf_119();                                     // 119 0x426500: returns false
    virtual bool vf_120();                                     // 120 0x426510: returns true
    virtual void* vf_121();                                    // 121 0x426520: returns null

    int             unknown_24;                  // +0x24
    int             unknown_28;                  // +0x28
    int             FallRate;                    // +0x2C
    void*           NextObject;                  // +0x30  ObjectClass* (cell/transport list)
    TagClass*       AttachedTag;                 // +0x34
    void*           AttachedBomb;                // +0x38  BombClass*
    AudioController AmbientSoundController;       // +0x3C  (0x14)
    AudioController CustomSoundController;        // +0x50  (0x14)
    int             CustomSound;                 // +0x64  (ctor = -1)
    bool            BombVisible;                 // +0x68
    unsigned char   align_69[3];                 // +0x69
    int             Health;                      // +0x6C
    int             EstimatedHealth;             // +0x70
    bool            IsOnMap;                     // +0x74
    unsigned char   align_75[3];                 // +0x75
    int             unknown_78;                  // +0x78  (ctor = 1)
    int             unknown_7C;                  // +0x7C
    bool            NeedsRedraw;                 // +0x80
    bool            InLimbo;                     // +0x81  (ctor = 1)
    bool            InOpenToppedTransport;       // +0x82
    bool            IsSelected;                  // +0x83
    bool            HasParachute;                // +0x84
    unsigned char   align_85[3];                 // +0x85
    AnimClass*      Parachute;                   // +0x88
    bool            OnBridge;                    // +0x8C
    bool            IsFallingDown;               // +0x8D
    bool            WasFallingDown;              // +0x8E
    bool            IsABomb;                     // +0x8F
    bool            IsAlive;                     // +0x90  (ctor = 1)
    unsigned char   align_91[3];                 // +0x91
    int             LastLayer;                   // +0x94  (Layer enum, ctor = -1)
    bool            IsInLogic;                   // +0x98
    bool            IsVisible;                   // +0x99  (ctor = 1)
    unsigned char   align_9A[2];                 // +0x9A
    CoordStruct     Location;                    // +0x9C  (0xC)
    void*           LineTrailer;                 // +0xA8  LineTrail*

};

GG_STATIC_ASSERT(offsetof(ObjectClass, unknown_24)             == 0x24);
GG_STATIC_ASSERT(offsetof(ObjectClass, FallRate)               == 0x2C);
GG_STATIC_ASSERT(offsetof(ObjectClass, NextObject)             == 0x30);
GG_STATIC_ASSERT(offsetof(ObjectClass, AttachedTag)            == 0x34);
GG_STATIC_ASSERT(offsetof(ObjectClass, AttachedBomb)           == 0x38);
GG_STATIC_ASSERT(offsetof(ObjectClass, AmbientSoundController) == 0x3C);
GG_STATIC_ASSERT(offsetof(ObjectClass, CustomSoundController)  == 0x50);
GG_STATIC_ASSERT(offsetof(ObjectClass, CustomSound)            == 0x64);
GG_STATIC_ASSERT(offsetof(ObjectClass, BombVisible)            == 0x68);
GG_STATIC_ASSERT(offsetof(ObjectClass, Health)                 == 0x6C);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->Health)               == 4);
GG_STATIC_ASSERT(offsetof(ObjectClass, EstimatedHealth)        == 0x70);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsOnMap)                == 0x74);
GG_STATIC_ASSERT(offsetof(ObjectClass, unknown_78)             == 0x78);
GG_STATIC_ASSERT(offsetof(ObjectClass, NeedsRedraw)            == 0x80);
GG_STATIC_ASSERT(offsetof(ObjectClass, InLimbo)               == 0x81);
GG_STATIC_ASSERT(offsetof(ObjectClass, Parachute)              == 0x88);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsAlive)                == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->IsAlive)              == 1);
GG_STATIC_ASSERT(offsetof(ObjectClass, LastLayer)              == 0x94);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsVisible)              == 0x99);
GG_STATIC_ASSERT(offsetof(ObjectClass, Location)               == 0x9C);
GG_STATIC_ASSERT(sizeof(((ObjectClass*)0)->Location)             == 0x0C);
GG_STATIC_ASSERT(offsetof(ObjectClass, LineTrailer)            == 0xA8);
GG_STATIC_ASSERT(sizeof(ObjectClass)                           == 0xAC);

#endif  // GG_MATCH_LAYOUT_OBJECT_CLASS_H
