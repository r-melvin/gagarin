// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: MissionClass ctor FUN_0x005B2DA0 (chains ObjectClass ctor
//   FUN_0x005F3900 at offset 0). Field offsets read from its init writes:
//   CurrentMission @0xAC (param[0x2B]=-1), SuspendedMission @0xB0,
//   QueuedMission @0xB4, unknown_bool_B8 @0xB8, MissionStatus @0xBC,
//   CurrentMissionStartTime @0xC0, MissionAccumulateTime @0xC4,
//   UpdateTimer.StartTime @0xC8 (param[0x32]) / .TimeLeft @0xD0 (param[0x34]).
//   Last member UpdateTimer ends at 0xD4 -> sizeof(MissionClass)==0xD4.
//   Cross-checked vs YRpp.
//
// MissionClass — base of every game object that runs an AI mission state
// machine. Derives ObjectClass at offset 0 and adds the mission/sub-mission
// bookkeeping from 0xAC.
#ifndef GG_MATCH_LAYOUT_MISSION_CLASS_H
#define GG_MATCH_LAYOUT_MISSION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_class.h"

// CDTimerClass — count-down frame timer (sizeof = 0xC). StartTime @0x00,
// CurrentTime/accumulator @0x04 (FrameTimer clock, not stored by the ctor),
// TimeLeft @0x08. Self-guarded for reuse by downstream layers.
#include "frame_timer.h"
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass)             == 0xC);

struct MissionControlClass;

// MissionClass  (0xAC..0xD3, sizeof = 0xD4)
// Retail RTTI 0x817B18 establishes the class key; public access preserves this ABI view.
// VTABLE: GAMEMD 0x7EDCC0 (IPersistStream side)
// VTABLE: GAMEMD 0x7EDCA4 (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7EDC9C (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7EDC94 (INoticeSource side, +0x0C)
class MissionClass : public ObjectClass
{
public:
    // Empty destructor; it only exists inline in the scalar deleting
    // destructor 0x5B3A60, which then calls ~ObjectClass 0x5F3B80.
    virtual ~MissionClass();
    // Overrides of base slots (primary table 0x7EDCC0, 157 slots).
    // FUNCTION: GAMEMD 0x5B3970 (declaration; slot 13)
    virtual void vf_13(Obj_004A1D30* crc);
    // FUNCTION: GAMEMD 0x5B3060 (declaration; slot 23)
    virtual void vf_23();
    // FUNCTION: GAMEMD 0x5B3040 (declaration; slot 97)
    virtual int vf_97();
    // Slots 122-156, introduced by MissionClass. Names are placeholders;
    // argument counts come from RET n. Slots 129-156 all return 450.
    virtual void vf_122(int mission, bool a2);                 // 122 0x5B35E0: queues a mission
    virtual bool vf_123();                                     // 123 0x5B3570: starts the queued mission
    virtual void vf_124(int mission);                          // 124 0x5B2FD0: sets the mission now
    virtual void vf_125(int mission, int a2, int a3);          // 125 0x5B3650: suspends the current mission
    virtual bool vf_126();                                     // 126 0x5B36B0: resumes the suspended mission
    virtual bool vf_127();                                     // 127 0x5B3A10: a mission is suspended
    virtual bool vf_128();                                     // 128 0x4E0140: returns true
    virtual int vf_129();                                      // 129 0x5B2E10: returns 450
    virtual int vf_130();                                      // 130 0x5B2E20: returns 450
    virtual int vf_131();                                      // 131 0x5B2E30: returns 450
    virtual int vf_132();                                      // 132 0x5B2E40: returns 450
    virtual int vf_133();                                      // 133 0x5B2E50: returns 450
    virtual int vf_134();                                      // 134 0x5B2E60: returns 450
    virtual int vf_135();                                      // 135 0x5B2E70: returns 450
    virtual int vf_136();                                      // 136 0x5B2E80: returns 450
    virtual int vf_137();                                      // 137 0x5B2E90: returns 450
    virtual int vf_138();                                      // 138 0x5B2EA0: returns 450
    virtual int vf_139();                                      // 139 0x5B2EB0: returns 450
    virtual int vf_140();                                      // 140 0x5B2EC0: returns 450
    virtual int vf_141();                                      // 141 0x5B2ED0: returns 450
    virtual int vf_142();                                      // 142 0x5B2EE0: returns 450
    virtual int vf_143();                                      // 143 0x5B2EF0: returns 450
    virtual int vf_144();                                      // 144 0x5B2F00: returns 450
    virtual int vf_145();                                      // 145 0x5B2F10: returns 450
    virtual int vf_146();                                      // 146 0x5B2F20: returns 450
    virtual int vf_147();                                      // 147 0x5B2F30: returns 450
    virtual int vf_148();                                      // 148 0x5B2F40: returns 450
    virtual int vf_149();                                      // 149 0x5B2F50: returns 450
    virtual int vf_150();                                      // 150 0x5B2F60: returns 450
    virtual int vf_151();                                      // 151 0x5B2F70: returns 450
    virtual int vf_152();                                      // 152 0x5B2F80: returns 450
    virtual int vf_153();                                      // 153 0x5B2F90: returns 450
    virtual int vf_154();                                      // 154 0x5B2FA0: returns 450
    virtual int vf_155();                                      // 155 0x5B2FB0: returns 450
    virtual int vf_156();                                      // 156 0x5B2FC0: returns 450
    // FUNCTION: GAMEMD 0x5B3A00 (decl; reloc)
    MissionControlClass* FUN_005B3A00();

    int           CurrentMission;            // +0xAC  (Mission enum, ctor = -1)
    int           SuspendedMission;          // +0xB0  (Mission enum, ctor = -1)
    int           QueuedMission;             // +0xB4  (Mission enum, ctor = -1)
    unsigned char unknown_bool_B8;           // +0xB8  (bool)
    unsigned char align_B9[3];               // +0xB9
    int           MissionStatus;             // +0xBC
    int           CurrentMissionStartTime;   // +0xC0  (frames)
    int           MissionAccumulateTime;     // +0xC4
    CDTimerClass  UpdateTimer;               // +0xC8  (0xC)
};

GG_STATIC_ASSERT(offsetof(MissionClass, CurrentMission)          == 0xAC);
GG_STATIC_ASSERT(offsetof(MissionClass, SuspendedMission)        == 0xB0);
GG_STATIC_ASSERT(offsetof(MissionClass, QueuedMission)           == 0xB4);
GG_STATIC_ASSERT(offsetof(MissionClass, unknown_bool_B8)         == 0xB8);
GG_STATIC_ASSERT(offsetof(MissionClass, MissionStatus)           == 0xBC);
GG_STATIC_ASSERT(offsetof(MissionClass, CurrentMissionStartTime) == 0xC0);
GG_STATIC_ASSERT(offsetof(MissionClass, MissionAccumulateTime)   == 0xC4);
GG_STATIC_ASSERT(offsetof(MissionClass, UpdateTimer)             == 0xC8);
GG_STATIC_ASSERT(sizeof(MissionClass)                            == 0xD4);

#endif  // GG_MATCH_LAYOUT_MISSION_CLASS_H
