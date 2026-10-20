// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ObjectClass ctor FUN_0x005F3900 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0). Every member offset below is read directly
//   from a field-init write in that ctor; cross-checked vs YRpp ObjectClass.h.
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

// --- shared instance-side leaf components -----------------------------------
// Self-guarded so a downstream layer in the same chain can reuse them.

// CoordStruct — absolute 3D lepton coordinate (3 ints, sizeof = 0xC).
#ifndef GG_MATCH_LAYOUT_COORDSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_COORDSTRUCT_DEFINED
struct CoordStruct
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);
#endif  // GG_MATCH_LAYOUT_COORDSTRUCT_DEFINED

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
};
GG_STATIC_ASSERT(offsetof(AudioController, Stamp)     == 0x04);
GG_STATIC_ASSERT(offsetof(AudioController, EventType) == 0x08);
GG_STATIC_ASSERT(sizeof(AudioController)              == 0x14);
#endif  // GG_MATCH_LAYOUT_AUDIOCONTROLLER_DEFINED

// ObjectClass  (0x24..0xAB, sizeof = 0xAC)
class ObjectClass : public AbstractClass
{
public:
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
    // FUNCTION: GAMEMD 0x5F6B60
    bool IsOnFloor() const;
    // FUNCTION: GAMEMD 0x5F6B90
    bool IsInAir() const;
    // FUNCTION: GAMEMD 0x5F6BD0
    int GetYSort() const;
    // FUNCTION: GAMEMD 0x5F6CD0
    bool IsCrushable(ObjectClass* crusher);

    int             unknown_24;                  // +0x24
    int             unknown_28;                  // +0x28
    int             FallRate;                    // +0x2C
    void*           NextObject;                  // +0x30  ObjectClass* (cell/transport list)
    void*           AttachedTag;                 // +0x34  TagClass*
    void*           AttachedBomb;                // +0x38  BombClass*
    AudioController AmbientSoundController;       // +0x3C  (0x14)
    AudioController CustomSoundController;        // +0x50  (0x14)
    int             CustomSound;                 // +0x64  (ctor = -1)
    unsigned char   BombVisible;                 // +0x68  (bool)
    unsigned char   align_69[3];                 // +0x69
    int             Health;                      // +0x6C
    int             EstimatedHealth;             // +0x70
    unsigned char   IsOnMap;                     // +0x74  (bool)
    unsigned char   align_75[3];                 // +0x75
    int             unknown_78;                  // +0x78  (ctor = 1)
    int             unknown_7C;                  // +0x7C
    unsigned char   NeedsRedraw;                 // +0x80  (bool)
    unsigned char   InLimbo;                     // +0x81  (bool, ctor = 1)
    unsigned char   InOpenToppedTransport;       // +0x82  (bool)
    unsigned char   IsSelected;                  // +0x83  (bool)
    unsigned char   HasParachute;                // +0x84  (bool)
    unsigned char   align_85[3];                 // +0x85
    void*           Parachute;                   // +0x88  AnimClass*
    unsigned char   OnBridge;                    // +0x8C  (bool)
    unsigned char   IsFallingDown;               // +0x8D  (bool)
    unsigned char   WasFallingDown;              // +0x8E  (bool)
    unsigned char   IsABomb;                     // +0x8F  (bool)
    unsigned char   IsAlive;                     // +0x90  (bool, ctor = 1)
    unsigned char   align_91[3];                 // +0x91
    int             LastLayer;                   // +0x94  (Layer enum, ctor = -1)
    unsigned char   IsInLogic;                   // +0x98  (bool)
    unsigned char   IsVisible;                   // +0x99  (bool, ctor = 1)
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
GG_STATIC_ASSERT(offsetof(ObjectClass, EstimatedHealth)        == 0x70);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsOnMap)                == 0x74);
GG_STATIC_ASSERT(offsetof(ObjectClass, unknown_78)             == 0x78);
GG_STATIC_ASSERT(offsetof(ObjectClass, NeedsRedraw)            == 0x80);
GG_STATIC_ASSERT(offsetof(ObjectClass, InLimbo)               == 0x81);
GG_STATIC_ASSERT(offsetof(ObjectClass, Parachute)              == 0x88);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsAlive)                == 0x90);
GG_STATIC_ASSERT(offsetof(ObjectClass, LastLayer)              == 0x94);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsVisible)              == 0x99);
GG_STATIC_ASSERT(offsetof(ObjectClass, Location)               == 0x9C);
GG_STATIC_ASSERT(offsetof(ObjectClass, LineTrailer)            == 0xA8);
GG_STATIC_ASSERT(sizeof(ObjectClass)                           == 0xAC);

#endif  // GG_MATCH_LAYOUT_OBJECT_CLASS_H
