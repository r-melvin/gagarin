// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only) | behaviour-confirmed-name
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI .?AVTerrainClass@@
//   (terrain_common_views.h), the two constructors 0x71BB90 / 0x71BDF0 (every member store below), the loader
//   0x71CDA0 (which inlines the no-init constructor), the CRC body 0x71CF50, and the allocation sites
//   0x71CB55, 0x71DDD3, 0x71DE13 and 0x6BF3BC (`PUSH 0xE0; CALL 0x7C8E17`, four sites, all agreeing).
//
// TerrainClass: one tree / rock / terrain feature placed on the map. Derives the ObjectClass-shaped
// partial view of terrain_common_views.h and, second, StageClass (RTTI member displacement 0xAC).
//
//   +0x00..+0xAB  MapObjClassView (terrain_common_views.h)
//   +0xAC..+0xC7  StageClass (TerrainStageView below): Value, HasChanged, Timer, Rate, Step
//   +0xC8  Type          (TerrainTypeClass*)  ctor argument 1; swizzled by Load
//   +0xCC  IsBurning     (bool)               ctor 0
//   +0xCD  TimeToDie     (bool)               ctor 0
//   +0xD0  unknown_D0 / +0xD4 unknown_D4      ctor 0; both feed the CRC
//   +0xD8  ScreenPos (two dwords)             ctor 0; the projected position, set by Unlimbo
//   sizeof 0xE0 (allocation)
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "terrain_shared.h"
#include "terrain_type_class.h"

// StageClass (RTTI base at +0xAC): a staged frame counter, 0x1C bytes. Its inline constructor and the
// timer restart are expanded in the bodies below; the no-init constructor leaves it alone.
struct TerrainTimerView
{
    int StartTime;   // +0x00  (the frame counter when started; -1 = stopped)
    int unknown_04;  // +0x04
    int DelayTime;   // +0x08

    // The no-init construction leaves the timer untouched.
    TerrainTimerView() {}
    // The restart of the timer with a delay (inline).
    TerrainTimerView(int delay) : StartTime(TerrainFrame), DelayTime(delay) {}
    // FUNCTION: GAMEMD 0x426630 (decl; reloc) - the frames left (0 when expired or stopped).
    int TimeLeft();
};
GG_STATIC_ASSERT(sizeof(TerrainTimerView) == 0xC);

struct TerrainStageView
{
    int              Value;        // +0x00
    bool             HasChanged;   // +0x04
    TerrainTimerView Timer;        // +0x08
    int              Rate;         // +0x14
    int              Step;         // +0x18

    TerrainStageView() : Value(0), HasChanged(false), Timer(0), Rate(0), Step(1) {}
    TerrainStageView(const MapObjNoInit&) {}
    // StageClass::SetRate, inline: the rate and a timer restarted with it.
    void SetRate(int rate)
    {
        Timer = TerrainTimerView(rate);
        Rate = rate;
    }
};
GG_STATIC_ASSERT(offsetof(TerrainStageView, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(TerrainStageView, Rate) == 0x14);
GG_STATIC_ASSERT(offsetof(TerrainStageView, Step) == 0x18);
GG_STATIC_ASSERT(sizeof(TerrainStageView) == 0x1C);

// VTABLE: GAMEMD 0x7F522C (IPersistStream side) and GAMEMD 0x7F5200 / 0x7F5224 / 0x7F521C
class TerrainClass : public MapObjClassView, public TerrainStageView
{
public:
    // FUNCTION: GAMEMD 0x71BB90 - the placing constructor (type, map cell).
    TerrainClass(TerrainTypeClass* type, const MapObjCell* cell);
    // FUNCTION: GAMEMD 0x71BDF0 - the default constructor (the allocation at 0x6BF3BC).
    TerrainClass();
    // No-init constructor: Load re-runs it through placement new to restore
    // the vptrs without touching members.
    TerrainClass(const MapObjNoInit& noInit) : MapObjClassView(noInit), TerrainStageView(noInit) {}

    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x71D310
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x71CDA0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x71CF30
    // Slot 8: the scalar deleting destructor 0x71D350 (compiler output; migrated from
    // match/core/deleting_dtor_sweep.cpp). The destructor body at 0x71B7B0 is out of this partition and
    // is bound, not defined.
    // FUNCTION: GAMEMD 0x71B7B0 (destructor body, outside this partition; bound, never defined here)
    virtual ~TerrainClass();
    virtual void PointerExpired(void* ptr, bool removed);                   // 10  0x71CFD0
    virtual int WhatAmI();                                                  // 11  0x71D300
    virtual int Size();                                                     // 12  0x71D2F0
    virtual void ComputeCRC(MapObjCrcView& crc);                           // 13  0x71CF50
    virtual void Update();                                                  // 23  0x71C730
    virtual MapObjTypeClassView* GetType();                               // 34  0x71D150
    virtual bool vf_53();                                                   // 53  0x71C930
    virtual bool Unlimbo(const MapObjCoord* where, int facing);                  // 54  0x71D000
    virtual void vf_60(MapObjCoord* where);                                // 60  0x71C110
    virtual void vf_61(MapObjCoord* where);                                // 61  0x71C070
    virtual bool vf_65(MapObjRect* rect, bool force, int unused);          // 65  0x71CC50
    virtual void vf_69(MapObjPoint* where, MapObjRect* clip);             // 69  0x71C1B0
    virtual void vf_70(MapObjPoint* where, MapObjRect* clip);             // 70  0x71C360
    virtual bool Mark(int arg);                                            // 73  0x71BFB0
    virtual MapObjRect vf_75();                           // 75  0x71D160
    virtual int vf_91(int* damage, int distance, MapObjWarheadView* warhead, void* source, bool a5, bool a6, void* house);   // 91  0x71B920
    virtual bool vf_94();                                                   // 94  0x71C5B0
    virtual void vf_95();                                                   // 95  0x71C6B0
    virtual int vf_107(MapObjOccupierView* who, int a2, int a3, int a4, int a5);       // 107 0x71C4D0

    // ---- members (complete-object offsets) ---------------------------------------------------
    TerrainTypeClass* Type;          // +0xC8
    bool              IsBurning;     // +0xCC
    bool              TimeToDie;     // +0xCD
    int               unknown_D0;    // +0xD0
    int               unknown_D4;    // +0xD4
    MapObjPoint      ScreenPos;     // +0xD8
};

GG_STATIC_ASSERT(offsetof(TerrainClass, Type) == 0xC8);
GG_STATIC_ASSERT(offsetof(TerrainClass, IsBurning) == 0xCC);
GG_STATIC_ASSERT(offsetof(TerrainClass, TimeToDie) == 0xCD);
GG_STATIC_ASSERT(offsetof(TerrainClass, unknown_D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(TerrainClass, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(TerrainClass, ScreenPos) == 0xD8);
// sizeof is from the allocation: `PUSH 0xE0; CALL 0x7C8E17` at 0x71CB55, 0x71DDD3, 0x71DE13, 0x6BF3BC.
GG_STATIC_ASSERT(sizeof(TerrainClass) == 0xE0);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_CLASS_H
