// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//
// SidebarClass::StripClass::SelectClass and SidebarClass::SBGadgetClass slots
// (layout and evidence: sidebar_select_class.h).

#include "sidebar_select_class.h"

// ---------------------------------------------------------------------------
// SelectClass::Action (0x6AAD00): left / right click on a build entry
// ---------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x48DCD0 (decl; reloc) -- TechnoTypeClass::GetByTypeAndIndex.
SelectTechnoType* __fastcall SelectGetByTypeAndIndex(int type, int index);
// FUNCTION: GAMEMD 0x752700 (decl; reloc) -- VoxClass::Play(name, a, b).
void __fastcall SelectVoxPlay(const char* name, int a, int b);
// FUNCTION: GAMEMD 0x750920 (decl; reloc) -- VocClass::PlayGlobal(index, flags, volume, controller).
void* __fastcall SelectPlayGlobal(int voc, unsigned int flags, float volume, void* controller);
// FUNCTION: GAMEMD 0x40DD70 (decl; reloc) -- WhatAmIHolder check on the placement object.
void* __fastcall SelectCheckPlacement(void* object);
// FUNCTION: GAMEMD 0x48DC90 (decl; reloc) -- MapClass::UnselectAll.
void __fastcall SelectUnselectAll();
// FUNCTION: GAMEMD 0x7C5F00 is the compiler's float-to-int helper (_ftol).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern SidebarHouse* SelectPlayer_00A83D4C;
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern SidebarRules* SelectRules_008871E0;
// GLOBAL: GAMEMD 0x88098C / 0x880990 / 0x880994 / 0x8809A0 / 0x88099A..0x88099C -- placement state.
extern void* PlacementObject_0088098C;
extern int PlacementAux_00880990;
extern int PlacementIndex_00880994;
extern int PendingSuper_008809A0;
extern unsigned char PlacementFlagA_0088099A;
extern unsigned char PlacementFlagB_0088099B;
extern unsigned char PlacementFlagC_0088099C;
// GLOBAL: GAMEMD 0xB07DD8 -- cell handed to a placement event.
extern int PlacementCell_00B07DD8;
// GLOBAL: GAMEMD 0xA8B550 -- build speed percentage.
extern int BuildSpeed_00A8B550;
// GLOBAL: GAMEMD 0xA8ED84 -- Unsorted::CurrentFrame.
extern int CurrentFrame_00A8ED84;
// GLOBAL: GAMEMD 0x880D68 -- per-strip "needs redraw" byte of the map's strips (stride 0xF94).
extern unsigned char StripRedraw_00880D68[];

// The outgoing event queue (0xA802C8 count, 0xA802D0 tail, 0xA802D4 list, 0xA83A54 timestamps).
extern int EventCount_00A802C8;
extern int EventTail_00A802D0;
extern SelectEvent EventList_00A802D4[128];
extern unsigned long EventTime_00A83A54[128];

inline void SelectEvent::Queue()
{
    if (EventCount_00A802C8 < 0x80) {
        EventList_00A802D4[EventTail_00A802D0] = *this;
        EventTime_00A83A54[EventTail_00A802D0] = timeGetTime();
        EventTail_00A802D0 = (EventTail_00A802D0 + 1) & 0x7F;
        EventCount_00A802C8 = EventCount_00A802C8 + 1;
    }
}

// Slot 31: click handling on a build entry: queues the production / hold / cancel /
// place events, plays the EVA lines and keeps the build timer of the entry current;
// super weapon entries (type 0x1F) arm or fire the weapon.
//
// CAPPED at 2.5% positional (22/879; LCS 483/879 = 54.9%, up from 251 = 28.6%). Retail frame
// is 0x9C, ours 0x90; that one-line difference shifts every later offset, so the positional
// score is low even though the structure now follows retail (879 vs 861 instructions).
// Multiset delta: retail-only mov 8, lea 6, or 3, test 1, push 1, jne 1, jmp 1, jle 1;
// ours-only add, cmp, jge, je. Attempts (five, caps are final):
//  1. first pass with `strip`, `entry`, `player` locals: 5.7%, LCS 28.6%.
//  2. regular arm first: worse, reverted, then re-applied with 4.
//  3. the event-queue append as an inline member `SelectEvent::Queue()` (the form the
//     coordinator suggested): byte-identical output to the free function.
//  4. drop the `strip`/`entry`/`player` locals (retail reloads Owner, the entry offset and
//     the house global each time), `type != 0x1F` regular arm first, `factory != 0` arm
//     first: 4.7%, LCS 55.1%.
//  5. pass the tech type's byte flag At_CCE unconverted (callee parameters are
//     `unsigned char`, matching retail's zero-extended byte push): removes the five `setne`
//     and four `test` (multiset delta now 22 instructions), 2.5% positional, LCS 54.9%.
// Also tried and dropped: one function-scope SelectEvent (frame 0x100, worse) and a named
// constant for the repeated -1 (no change; retail keeps -1 in ECX across the compare and the
// store through `or ecx,-1`). The previous layout (shared locals) scored higher positionally
// (5.7%) only by alignment luck. Open: retail lays the hold arm of the `factory != 0` branch
// after the super-weapon arm, which source order does not reproduce.
// FUNCTION: GAMEMD 0x6AAD00
int SidebarSelectClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (Owner == 0) {
        return 1;
    }
    int index = unknown_30 + Owner->TopRowIndex * 2;
    int item = Owner->Entries[index].Item;
    int type = Owner->Entries[index].Type;
    int category = Owner->Entries[index].Category;
    SelectFactory* factory = Owner->Entries[index].Factory;
    Map_0087F7E8.vf_19(0, 0);
    bool shift = (modifier & 1) != 0;
    if (index < Owner->CameoCount) {
        if (type != 0x1F) {
            SelectTechnoType* technoType = SelectGetByTypeAndIndex(type, item);
            if (technoType != 0) {
                if (flags & 8) {
                    flags &= ~8;
                }
                if (flags & 0x10) {
                    if (factory != 0) {
                        if (PlacementObject_0088098C != 0 && SelectCheckPlacement(PlacementObject_0088098C) != 0) {
                            PlacementObject_0088098C = 0;
                            PlacementAux_00880990 = 0;
                            PlacementIndex_00880994 = -1;
                            Map_0087F7E8.SetActiveFoundation_004A8BF0(0);
                        }
                        if (factory->Object == 0 || factory->At_70 != 0) {
                            SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                            SelectVoxPlay("EVA_Canceled", -1, -1);
                            SelectEvent event;
                            if (shift) {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x2E, type, item, technoType->At_CCE)->Queue();
                            } else {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x10, type, item, technoType->At_CCE)->Queue();
                            }
                        } else {
                            SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                            SelectVoxPlay("EVA_OnHold", -1, -1);
                            SelectEvent event;
                            event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xF, type, item, technoType->At_CCE)->Queue();
                            StripRedraw_00880D68[Owner->RowBase * 0xF94] = 1;
                        }
                    } else {
                        if (Owner->Entries[index].State == 1) {
                            Owner->Entries[index].State = 2;
                            Owner->At_3C = 1;
                            Map_0087F7E8.FlagToRedraw(0);
                            SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                            SelectVoxPlay("EVA_OnHold", -1, -1);
                            SelectEvent event;
                            event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xF, type, item, technoType->At_CCE)->Queue();
                        }
                        SelectFactory* primary = SelectPlayer_00A83D4C->GetPrimaryFactory(type, technoType->At_CCE, category);
                        if (primary != 0 && primary->IsQueued(technoType)) {
                            SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                            SelectEvent event;
                            if (shift) {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x2E, type, item, technoType->At_CCE)->Queue();
                            } else {
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0x10, type, item, technoType->At_CCE)->Queue();
                            }
                        }
                    }
                }
                if (flags & 1) {
                    if (factory != 0 && (factory->Object == 0 || factory->At_70 != 0)) {
                        if (factory->IsDone()) {
                            SelectTechno* object = factory->FUN_004CA160();
                            if (object == 0) {
                                if (factory->GetOriginalBalance() != -1) {
                                    PendingSuper_008809A0 = 1;
                                }
                            } else {
                                SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                                SelectTechno* target = (object->*object->Vtbl->At_190)(0, 0);
                                if (target == 0) {
                                    SelectEvent event;
                                    event.Construct((object->*object->Vtbl->At_38)(), 0x10, type, item, technoType->At_CCE)->Queue();
                                    SelectVoxPlay("EVA_UnableToComply", -1, -1);
                                } else if ((object->*object->Vtbl->At_2C)() == 6) {
                                    SelectPlayer_00A83D4C->FUN_004FB840(target, object);
                                } else {
                                    SelectEvent event;
                                    event.ConstructAt((object->*object->Vtbl->At_38)(), 0xB, type, -1, technoType->At_CCE, &PlacementCell_00B07DD8)->Queue();
                                }
                            }
                        } else {
                            SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                            SelectVoxPlay(type == 0x10 ? "EVA_Training" : "EVA_Building", -1, -1);
                            SelectTechnoType* current = SelectGetByTypeAndIndex(Owner->Entries[index].Type, Owner->Entries[index].Item);
                            bool currentFlag = current != 0 && current->At_CCE != 0;
                            SelectPlayer_00A83D4C->FUN_005005B0(type, technoType->At_CCE, category);
                            SelectEvent event;
                            event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xE, Owner->Entries[index].Type, Owner->Entries[index].Item, currentFlag)->Queue();
                            Owner->Entries[index].State = 1;
                            int progress = 0;
                            if (Owner->Entries[index].Factory != 0) {
                                progress = Owner->Entries[index].Factory->GetProgress();
                            }
                            if (Owner->Entries[index].State == 1 && Owner->Entries[index].Progress > progress) {
                                progress = (progress + Owner->Entries[index].Progress) / 2;
                            }
                            Owner->Entries[index].Progress = progress;
                            int frames = factory->GetBuildTimeFrames() + 1;
                            Owner->Entries[index].TimerStart = CurrentFrame_00A8ED84;
                            Owner->Entries[index].TimerDelay = frames;
                            Owner->Entries[index].Frames = frames;
                            Owner->At_3C = 1;
                            Map_0087F7E8.FlagToRedraw(0);
                            SidebarNeedsRedraw_00884B8F = 1;
                        }
                    } else {
                        SelectFactory* primary = SelectPlayer_00A83D4C->GetPrimaryFactory(type, technoType->At_CCE, category);
                        SelectTechnoType* current = SelectGetByTypeAndIndex(Owner->Entries[index].Type, Owner->Entries[index].Item);
                        bool currentFlag = current != 0 && current->At_CCE != 0;
                        bool canBuild = SelectPlayer_00A83D4C->FUN_0050B370(current);
                        bool progressing = false;
                        bool queued = false;
                        if (primary != 0) {
                            progressing = (primary->Object != 0 && primary->At_70 == 0) == false || primary->At_58 != 0 || primary->At_50 > 0;
                        }
                        if (!progressing && type != 7 && !canBuild) {
                            SelectVoxPlay(type == 0x10 ? "EVA_Training" : "EVA_Building", -1, -1);
                        }
                        if (progressing && type == 7) {
                            SelectVoxPlay("EVA_UnableToComply", -1, -1);
                        } else {
                            bool ready = SelectPlayer_00A83D4C->FUN_00500700(type, technoType->At_CCE, category);
                            if (!canBuild) {
                                SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                                if (primary == 0 && !ready) {
                                    SelectPlayer_00A83D4C->FUN_005005B0(type, technoType->At_CCE, category);
                                    queued = true;
                                }
                                SelectEvent event;
                                event.Construct(SelectPlayer_00A83D4C->ArrayIndex, 0xE, Owner->Entries[index].Type, Owner->Entries[index].Item, currentFlag)->Queue();
                            }
                            if ((queued || !ready) && !progressing && !canBuild) {
                                Owner->Entries[index].State = 1;
                                Owner->At_3C = 1;
                                Map_0087F7E8.FlagToRedraw(0);
                                SelectTechnoType* target = SelectGetByTypeAndIndex(type, Owner->Entries[index].Item);
                                if (target != 0) {
                                    int cost = (target->*target->Vtbl->At_84)(SelectPlayer_00A83D4C);
                                    int scaled = cost * BuildSpeed_00A8B550 / 54;
                                    if ((SelectPlayer_00A83D4C->Sub24.*SelectPlayer_00A83D4C->Sub24.Vtbl->At_18)() >= scaled) {
                                        if ((target->*target->Vtbl->At_94)(1, 0, 0, SelectPlayer_00A83D4C)) {
                                            int time = (target->*target->Vtbl->At_88)();
                                            if ((target->*target->Vtbl->At_2C)() == 7 && target->At_1571) {
                                                time = (int)(time * SelectRules_008871E0->At_758);
                                            }
                                            int frames = time;
                                            if (frames < 0xF) {
                                                frames = 0xF;
                                            }
                                            int steps = frames / 54;
                                            if (steps * 54 < 0xF) {
                                                ++steps;
                                            }
                                            if (steps < 1) {
                                                steps = 1;
                                            } else if (steps > 0xFF) {
                                                steps = 0xFF;
                                            }
                                            Owner->Entries[index].Progress = 0;
                                            Owner->Entries[index].Frames = steps;
                                            Owner->Entries[index].TimerStart = CurrentFrame_00A8ED84;
                                            Owner->Entries[index].TimerDelay = steps;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (item != -1) {
                if (flags & 8) {
                    flags &= ~8;
                }
                if (flags & 0x10) {
                    PendingSuper_008809A0 = -1;
                }
                if ((flags & 1) && (unsigned int)item < SelectPlayer_00A83D4C->SuperCount) {
                    SelectPlayGlobal(SelectRules_008871E0->Sound18C, 0x2000, 1.0f, 0);
                    SelectSuper* super = SelectPlayer_00A83D4C->Supers[item];
                    if (super->CanFire()) {
                        if (super->Type->At_BC == 0) {
                            SelectEvent event;
                            struct { short x; short y; } cell = { 0, 0 };
                            event.ConstructSpecial(SelectPlayer_00A83D4C->ArrayIndex, 0x12, super->Type->At_98, &cell)->Queue();
                        } else {
                            PlacementObject_0088098C = 0;
                            PlacementAux_00880990 = 0;
                            PlacementIndex_00880994 = -1;
                            Map_0087F7E8.SetActiveFoundation_004A8BF0(0);
                            Map_0087F7E8.SetRepairMode_004AC8C0(0);
                            Map_0087F7E8.SetSellMode_004AC660(0);
                            PlacementFlagA_0088099A = 0;
                            PlacementFlagB_0088099B = 0;
                            PlacementFlagC_0088099C = 0;
                            PendingSuper_008809A0 = item;
                            SelectUnselectAll();
                            SelectVoxPlay("EVA_SelectTarget", -1, -1);
                        }
                    } else {
                        super->FUN_006CC070();
                    }
                }
            }
        }
    } else {
        flags = 0;
    }
    ControlClass::Action(flags, key, 0);
    return 1;
}

// FUNCTION: GAMEMD 0x6AB990
void SidebarSelectClass::v70()
{
    ToolTipManager_Instance->SaveTimerDelay();
    ToolTipManager_Instance->SetTimerDelay(0);
    Hover = 1;
    Owner->At_3C = 1;
    Map_0087F7E8.FlagToRedraw(0);
    SidebarNeedsRedraw_00884B8F = 1;
    SelectHoverChanged_00B0B518 = 1;
}

// FUNCTION: GAMEMD 0x6AB9E0
void SidebarSelectClass::v74()
{
    ToolTipManager_Instance->RestoreTimeDelay();
    Hover = 0;
    Owner->At_3C = 1;
    Map_0087F7E8.FlagToRedraw(0);
    SidebarNeedsRedraw_00884B8F = 1;
    SelectHoverChanged_00B0B518 = 1;
}

// FUNCTION: GAMEMD 0x6ABA40
int SidebarSBGadgetClass::Action(unsigned flags, unsigned* key, int modifier)
{
    Map_0087F7E8.vf_19(0, 0);
    return 1;
}
