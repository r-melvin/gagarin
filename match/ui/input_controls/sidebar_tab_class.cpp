// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// TabClass entries (layout and evidence: sidebar_class_layout.h). TabClass is
// the command bar (the "tab" strip across the top of the screen) that sits
// on top of the sidebar.

#include "sidebar_class_layout.h"
#include "../tooltip_manager_shared.h"
#include "mouse_ww_mouse_class.h"

// GLOBAL: GAMEMD 0xB0C148 -- the 25 command-bar button shapes.
extern SidebarShapeFile* CommandShapes_00B0C148[25];
// GLOBAL: GAMEMD 0xB0CBDC -- "owns the memory" flag of each command-bar shape.
extern bool CommandShapeOwned_00B0CBDC[25];

// FUNCTION: GAMEMD 0x6D0270
void TabClass::vf_50()
{
    SidebarClass::vf_50();
    for (int i = 0; i < 25; ++i) {
        if (CommandShapeOwned_00B0CBDC[i]) {
            delete CommandShapes_00B0C148[i];
            CommandShapeOwned_00B0CBDC[i] = false;
        }
        CommandShapes_00B0C148[i] = 0;
    }
}

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// Command-bar layout state written by the setup at 0x6D02B0.
// GLOBAL: GAMEMD 0xB0CD38 / 0xB0CB50 -- width and height of the first shape.
extern int ShapeWidth_00B0CD38;
extern int ShapeHeight_00B0CB50;
// GLOBAL: GAMEMD 0xB0FC68 -- pointer to the bar rectangle.
extern SidebarTabRect* BarRect_00B0FC68;
// GLOBAL: GAMEMD 0xB0FC6C -- pointer to the bar origin.
extern int* BarOrigin_00B0FC6C;
// GLOBAL: GAMEMD 0xB0CB54 -- button count.
extern int ButtonCount_00B0CB54;
// GLOBAL: GAMEMD 0xB0CC2C -- computed bar origin.
extern int BarX_00B0CC2C;
// GLOBAL: GAMEMD 0xB0CD10 / 0xB0CC38 -- inner and outer bar widths.
extern int InnerWidth_00B0CD10;
extern int OuterWidth_00B0CC38;
// GLOBAL: GAMEMD 0xB0FC58 -- pointer to a record whose field +4 is copied.
struct SidebarTabRecord
{
    int X;
    int Y;
};
extern SidebarTabRecord* BarRecord_00B0FC58;
// GLOBAL: GAMEMD 0xB0CC24 -- copy of BarRecord->At_04.
extern int BarRecordValue_00B0CC24;

// Slot 53: loads the 25 command-bar button shapes and computes the bar geometry.
//
// PARTIAL (63.3%, 38/60). Retail keeps a store of `Scenario->+0x34B8` into an unused
// 4-byte local between the `owned` byte and the rect copy (frame 0x118, ours 0x114), which
// moves every stack offset; cl removes unused locals (also tried: an inline function
// with an unused parameter, a struct member, a reread; all eliminated). Everything
// else matches, including the per-field rect copy that omits the width store.
// FUNCTION: GAMEMD 0x6D02B0
void TabClass::vf_53()
{
    SidebarClass::vf_53();
    char name[0x100];
    bool owned = false;
    for (int i = 0; i < 25; ++i) {
        sprintf(name, "Button%02d.SHP", i);
        CommandShapes_00B0C148[i] = SidebarLoadWholeFileEx(name, &owned);
        CommandShapeOwned_00B0CBDC[i] = owned;
    }
    SidebarShapeFile* shape = CommandShapes_00B0C148[0];
    int width = shape->Width;
    ShapeWidth_00B0CD38 = width;
    ShapeHeight_00B0CB50 = shape->Height;
    SidebarTabRect rect = *BarRect_00B0FC68;
    BarX_00B0CC2C = *BarOrigin_00B0FC6C - ButtonCount_00B0CB54 * rect.Width;
    int flag = DAT_00A8B230->unknown_34B8;
    InnerWidth_00B0CD10 = rect.Width - width;
    BarRecordValue_00B0CC24 = BarRecord_00B0FC58->Y;
    OuterWidth_00B0CC38 = rect.Width - width + width;
    At_5520 = 0;
}

// GLOBAL: GAMEMD 0xB0CCB0 / 0xB0CC40 -- the two extra command-bar buttons.
extern SidebarButton CommandButtonA_00B0CCB0;
extern SidebarButton CommandButtonB_00B0CC40;
// GLOBAL: GAMEMD 0xB0FA90 -- the shape both buttons display.
extern SidebarShapeFile* CommandButtonShape_00B0FA90;
// GLOBAL: GAMEMD 0xB0FC60 / 0xB0FC64 -- pointers to the two button rectangles.
extern SidebarTabRect* ButtonRectA_00B0FC60;
extern SidebarTabRect* ButtonRectB_00B0FC64;
// FUNCTION: GAMEMD 0x72F430 (decl; reloc) -- returns non-zero when the tab bar is enabled.
char SidebarTabBarEnabled();

// FUNCTION: GAMEMD 0x6D03A0
void TabClass::vf_08()
{
    SidebarClass::vf_08();
    if (DAT_00A8ED6B == 0) {
        if (SidebarTabBarEnabled()) {
            FUN_006D0FD0();
            SidebarShapeFile* shape = CommandButtonShape_00B0FA90;
            CommandButtonA_00B0CCB0.ID = 0xF0;
            CommandButtonA_00B0CCB0.At_50 = ConvertA_0087F6CC;
            CommandButtonA_00B0CCB0.IsOn = 0;
            CommandButtonA_00B0CCB0.At_30 = 0;
            CommandButtonA_00B0CCB0.At_20 = 5;
            SidebarTabRect rectA = *ButtonRectA_00B0FC60;
            CommandButtonA_00B0CCB0.SetPosition(rectA.X, rectA.Y);
            CommandButtonA_00B0CCB0.FUN_0069DE00(shape, 0, 0);
            CommandButtonB_00B0CC40.ID = 0xF1;
            CommandButtonB_00B0CC40.At_50 = ConvertA_0087F6CC;
            CommandButtonB_00B0CC40.IsOn = 0;
            CommandButtonB_00B0CC40.At_30 = 0;
            CommandButtonB_00B0CC40.At_20 = 5;
            SidebarTabRect rectB = *ButtonRectB_00B0FC64;
            CommandButtonB_00B0CC40.SetPosition(rectB.X, rectB.Y);
            CommandButtonB_00B0CC40.FUN_0069DE00(shape, 0, 0);
        }
    }
}

// GLOBAL: GAMEMD 0xB0C1C0 -- the 25 command-bar buttons (0x60 bytes each).
extern SidebarButton CommandButtons_00B0C1C0[25];
// GLOBAL: GAMEMD 0xB0CC1C -- index into the command slot table of the active command.
extern int ActiveCommandIndex_00B0CC1C;
// GLOBAL: GAMEMD 0xB0CB78 -- command slot per command index.
extern int CommandSlotTable_00B0CB78[25];

// What ShapeButtonClass::SetToolTip (0x6D09C0) does, expanded inline.
inline void SetButtonToolTip(SidebarButton* button, const char* text)
{
    if (button) {
        ToolTip tooltip;
        tooltip.Bounds.X = button->X;
        tooltip.field_18 = false;
        tooltip.GadgetID = button->ID;
        tooltip.Text = text;
        tooltip.Bounds.Y = button->Y;
        tooltip.Bounds.Width = button->Width;
        tooltip.Bounds.Height = button->Height;
        ToolTipManager_Instance->Remove(tooltip.GadgetID);
        ToolTipManager_Instance->Add(tooltip);
    }
}

// ShapeButtonClass::GetButton (0x6CFD40) expanded inline over the command bar.
inline SidebarButton* GetCommandButton(int index)
{
    int slot = CommandSlotTable_00B0CB78[index];
    if (slot >= 0 && slot < 0x19) {
        return &CommandButtons_00B0C1C0[slot];
    }
    return 0;
}

// True when a command button asks to be redrawn.
inline bool AnyCommandButtonDirty()
{
    for (int index = 0; index < 25; ++index) {
        SidebarButton* button = GetCommandButton(index);
        if (button != 0 && button->At_54) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6D04F0
bool TabClass::vf_54(int control)
{
    bool changed = SidebarClass::vf_54(control);
    if (changed) {
        if (At_53A5) {
            if (At_5544) {
                FUN_006D1200();
            } else {
                AddButton(&CommandButtonB_00B0CC40);
                SetButtonToolTip(&CommandButtonB_00B0CC40, "Tip:ThumbClosed");
            }
        } else {
            if (At_5544) {
                for (int i = 0; i < 25; ++i) {
                    vf_13(&CommandButtons_00B0C1C0[i]);
                }
                vf_13(&CommandButtonA_00B0CCB0);
                for (int j = 0; j < 25; ++j) {
                    SidebarButton* button = GetCommandButton(j);
                    if (button != 0) {
                        ToolTipManager_Instance->Remove(button->ID);
                    }
                }
                ToolTipManager_Instance->Remove(0xF0);
            } else {
                vf_13(&CommandButtonB_00B0CC40);
                ToolTipManager_Instance->Remove(0xF1);
            }
        }
        FlagToRedraw(2);
    }
    return changed;
}

// ---------------------------------------------------------------------------
// Input handling (0x6D0680)
// ---------------------------------------------------------------------------

// GLOBAL: GAMEMD 0xA8ED84 -- Unsorted::CurrentFrame.
extern int CurrentFrame_00A8ED84;
// GLOBAL: GAMEMD 0xB0FC58 -- pointer to the bar origin record {X, Y}.
// (BarRecord_00B0FC58 above.)
// GLOBAL: GAMEMD 0x7F5BFC -- height term of the tooltip area.
extern int TipHeight_007F5BFC;
// GLOBAL: GAMEMD 0xA8B538 -- non-zero while input is locked.
extern int InputLocked_00A8B538;
// Command indices of the named commands handled by the hotkey chain.
// GLOBAL: GAMEMD 0xB0CD24, 0xB0CB3C, 0xB0C1B8, 0xB0CB20, 0xB0CB68, 0xB0CB6C, 0xB0CB38
extern int CommandIndexA_00B0CD24;
extern int CommandIndexB_00B0CB3C;
extern int CommandIndexC_00B0C1B8;
extern int CommandIndexD_00B0CB20;
extern int CommandIndexE_00B0CB68;
extern int CommandIndexF_00B0CB6C;
extern int CommandIndexG_00B0CB38;
// GLOBAL: GAMEMD 0xB0CC20 / 0xB0CD28 -- first and last command of the numbered range.
extern int CommandRangeFirst_00B0CC20;
extern int CommandRangeLast_00B0CD28;
// FUNCTION: GAMEMD 0x731AF0 (decl; reloc)
// Command handlers; signatures are reconciled in their original TU.
void FUN_00731AF0();
void FUN_00731A30();
void FUN_00730F30();
void FUN_00730AF0();
void FUN_00730D60();
void FUN_00730EA0();
void FUN_00732950();
// FUNCTION: GAMEMD 0x731A50 / 0x731A70 (decl; reloc) -- toggle handlers, flag in CL.
void FUN_00731A50(bool flag);
void FUN_00731A70(bool flag);
// FUNCTION: GAMEMD 0x730A10 (decl; reloc)
// Numbered command handlers, index in ECX.
int FUN_00730A10(int index);
bool FUN_00730990(int index);
void FUN_00731060(int index);
void FUN_007313A0(int index);
void FUN_007311C0(int index);
void FUN_007310D0(int index);
// FUNCTION: GAMEMD 0x6CFD40 (decl; reloc) -- ShapeButtonClass::GetButton.
SidebarButton* SidebarGetButton(int index);
// FUNCTION: GAMEMD 0x6D09C0 (decl; reloc) -- ShapeButtonClass::SetToolTip.
void SidebarSetToolTip(SidebarButton* button, const char* text);

// Frames left on a countdown that started at `start` (-1: not started yet) and
// lasts `delay` frames; zero once it has run out.
inline int TimeLeft(int start, int delay)
{
    if (start == -1) {
        return delay;
    }
    int elapsed = CurrentFrame_00A8ED84 - start;
    if (elapsed < delay) {
        return delay - elapsed;
    }
    return 0;
}

// Slot 10: tab-bar input: opens and closes the bar from its hotkeys and dispatches the
// numbered command hotkeys, then runs the base-class input handling.
//
// PARTIAL (95.2%, 218/229). Same instruction multiset as retail. Differences: retail
// loads the tactical width (EDI) before the mouse compare, cl loads it at its use;
// `LEA EDX,[EDX+ECX-2]` operand roles; and `MOV EDX,0x2000` sits between the two
// PlayGlobal pushes in retail. Variants tried: width as a local before / after the
// record copy, four forms of the vertical limit expression.
// FUNCTION: GAMEMD 0x6D0680
void TabClass::vf_10(int* key, Point2D* mouse)
{
    if (TimeLeft(At_5538, At_5540) == 1) {
        At_5545 = true;
        FlagToRedraw(0);
    }
    {
        SidebarTabRecord origin = *BarRecord_00B0FC58;
        if (mouse->X >= origin.X && mouse->X < origin.X + TacticalRect_00886FA0.Width) {
            if (mouse->Y >= origin.Y && mouse->Y < TipHeight_007F5BFC + origin.Y - 2) {
                Map_0087F7E8.vf_19(0, 0);
            }
        }
    }
    int code = *key;
    if (code >= 0x80D6 && code < 0x80EF) {
        int command = (code & ~0x8000) - 0xD6;
        if (command == CommandIndexA_00B0CD24) {
            FUN_00731AF0();
        } else if (command == CommandIndexB_00B0CB3C) {
            FUN_00731A30();
        } else if (command == CommandIndexC_00B0C1B8) {
            FUN_00730F30();
        } else if (command == CommandIndexD_00B0CB20) {
            FUN_00730AF0();
        } else if (command == CommandIndexE_00B0CB68) {
            FUN_00730D60();
        } else if (command == ActiveCommandIndex_00B0CC1C) {
            SidebarButton* button = GetCommandButton(ActiveCommandIndex_00B0CC1C);
            if (button->IsOn) {
                FUN_00731A50(true);
            } else {
                FUN_00731A70(true);
            }
        } else if (command == CommandIndexF_00B0CB6C) {
            FUN_00730EA0();
        } else if (command >= CommandRangeFirst_00B0CC20 && command <= CommandRangeLast_00B0CD28) {
            int number = command - CommandRangeFirst_00B0CC20 + 1;
            if (FUN_00730A10(number) == 0) {
                FUN_00731060(number);
            } else if (FUN_00730990(number)) {
                FUN_007313A0(number);
            } else {
                FUN_007311C0(number);
            }
        } else if (command == CommandIndexG_00B0CB38) {
            FUN_00732950();
        }
    } else if (code == 0x80F0) {
        VocClass::PlayGlobal(DAT_008871E0->GUICloseSound, 1.0f, 0x2000, 0);
        if (At_5544) {
            FUN_006D04D0();
            vf_13(&CommandButtonA_00B0CCB0);
            for (int i = 0; i < 25; ++i) {
                SidebarButton* button = SidebarGetButton(i);
                if (button != 0) {
                    ToolTipManager_Instance->Remove(button->ID);
                }
            }
            ToolTipManager_Instance->Remove(0xF0);
            At_5544 = false;
            AddButton(&CommandButtonB_00B0CC40);
            SidebarSetToolTip(&CommandButtonB_00B0CC40, "Tip:ThumbClosed");
            At_5545 = true;
            FlagToRedraw(0);
        }
    } else if (code == 0x80F1) {
        if (InputLocked_00A8B538 == 0) {
            VocClass::PlayGlobal(DAT_008871E0->GUIOpenSound, 1.0f, 0x2000, 0);
            if (!At_5544) {
                vf_13(&CommandButtonB_00B0CC40);
                ToolTipManager_Instance->Remove(0xF1);
                At_5544 = true;
                FUN_006D1200();
                At_5545 = true;
                FlagToRedraw(0);
            }
        }
    } else if (code >= 0xC0D6 && code < 0xC0EF) {
        int command = (code & ~0xC000) - 0xD6;
        if (command >= CommandRangeFirst_00B0CC20 && command <= CommandRangeLast_00B0CD28) {
            FUN_007310D0(command - CommandRangeFirst_00B0CC20 + 1);
        }
    }
    unknown_551C.FUN_004A2600(0);
    SidebarClass::vf_10(key, mouse);
}


// ---------------------------------------------------------------------------
// Draw (0x6D0A20)
// ---------------------------------------------------------------------------

// The mouse is WWMouseClassInstance (GLOBAL 0x887640, mouse_ww_mouse_class.h); slot 13 fills and returns the
// cursor position.

// The command-bar rectangle record: {X, Y, Width, Height}.
struct SidebarBarArea
{
    int X;
    int Y;
    int Width;
    int Height;
};
// GLOBAL: GAMEMD 0xB0FC58 / 0xB0FC60 / 0xB0FC64 / 0xB0FC68 / 0xB0FC6C -- pointers to the bar
// rectangle and to the positions of the individual pieces.
extern SidebarBarArea* BarArea_00B0FC58;
extern Point2D* ButtonPointA_00B0FC60;
extern Point2D* ButtonPointB_00B0FC64;
extern SidebarBarArea* SlotArea_00B0FC68;
extern int* EndX_00B0FC6C;
// GLOBAL: GAMEMD 0xB0FB08 / 0xB0FA3C / 0xB0FA90 / 0xB0FAA8 / 0xB0FABC -- shapes drawn by the bar.
extern SidebarShapeFile* BarShapeBackdrop_00B0FB08;
extern SidebarShapeFile* BarShapeTop_00B0FA3C;
extern SidebarShapeFile* BarShapeThumb_00B0FA90;
extern SidebarShapeFile* BarShapeSlot_00B0FAA8;
extern SidebarShapeFile* BarShapeEnd_00B0FABC;
// GLOBAL: GAMEMD 0xB0F9E4 -- number of slot pieces drawn.
extern int SlotCount_00B0F9E4;
// GLOBAL: GAMEMD 0xB0CD40 / 0xB0CD44 / 0xB0CC00 -- hover flag, history count, surface history.
extern bool BarHover_00B0CD40;
extern int BarHistoryCount_00B0CD44;
extern SidebarSurfaceView* BarHistory_00B0CC00[4];
// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- draw a shape (see sidebar_class_draw.cpp).
void SidebarDrawShape(SidebarSurfaceView* surface, SidebarConvert* convert,
                      SidebarShapeFile* shape, int frame, Point2D* position,
                      SidebarAreaRect* bounds, int flags, int a6, int a7, int a8,
                      int zAdjust, int a10, int a11, int a12, Point2D offset);

// The last mouse position seen by the bar draw (a function-local static in retail).
struct SidebarLastMouse
{
    int X;
    int Y;
    SidebarLastMouse() : X(0), Y(0) {}
    ~SidebarLastMouse() {}
};

// Slot 16: tab-bar draw: decides from the mouse position and a short surface history
// whether the bar needs redrawing and draws its pieces and buttons.
//
// PARTIAL 17.8%. The shape drawer's last two arguments are one point passed by value.
// Retail keeps the redraw flag in BL with EBP as the zero register and spills `this` to
// the stack, so ESI and EDI hold the mouse coordinates; ours holds `this` in EBP and keeps
// the flag in memory. Attempts: (1) bool flag (as kept); (2) int flag (2.0%); (3) the
// four shape draws through an inline helper: byte-identical. The function-local static
// (guard bit at 0xB0CB58, empty destructor stub at 0x6D0E50) is reproduced by a static
// with a user destructor.
// FUNCTION: GAMEMD 0x6D0A20
void TabClass::vf_16(bool forced)
{
    static SidebarLastMouse lastMouse;
    bool redraw = false;
    if (forced || At_5545 || AnyCommandButtonDirty()) {
        redraw = true;
        BarHistoryCount_00B0CD44 = 0;
    } else {
        Point2D cursor;
        Point2D* mouse = WWMouseClassInstance->vf_13(&cursor);
        int x = mouse->X;
        int y = mouse->Y;
        SidebarBarArea* area = BarArea_00B0FC58;
        if (x >= area->X && x < area->Width + area->X && y >= area->Y && y < area->Height + area->Y) {
            BarHover_00B0CD40 = true;
            if (x != lastMouse.X || y != lastMouse.Y) {
                redraw = true;
            }
        } else {
            if (BarHover_00B0CD40) {
                redraw = true;
            }
            BarHover_00B0CD40 = false;
        }
        lastMouse.X = x;
        lastMouse.Y = y;
        if (redraw) {
            BarHistoryCount_00B0CD44 = 0;
        } else {
            bool seen = false;
            for (int i = 0; i < BarHistoryCount_00B0CD44; ++i) {
                if (BarHistory_00B0CC00[i] == CurrentSurface_00887314) {
                    seen = true;
                    break;
                }
            }
            if (!seen) {
                redraw = true;
            }
        }
    }
    if (!DAT_00A8ED6B) {
        Point2D origin;
        origin.X = 0;
        origin.Y = 0;
        SidebarAreaRect scratch;
        Point2D offset(0, 0);
        SidebarDrawShape(SidebarSurface_00887300, ConvertA_0087F6CC, BarShapeBackdrop_00B0FB08, 0,
                         &origin, (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_78)(&scratch),
                         0, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
        SidebarTouched_00B0B518 = 1;
        unknown_551C.FUN_004A2370(true);
        if (redraw) {
            SidebarAreaRect clip = *(CurrentSurface_00887314->*CurrentSurface_00887314->Vtbl->At_78)(&scratch);
            Point2D position;
            position.X = 0;
            position.Y = 0;
            position.X = BarArea_00B0FC58->X;
            position.Y = BarArea_00B0FC58->Y;
            SidebarAreaRect bounds = clip;
            bounds.Width = BarArea_00B0FC58->Width;
            Point2D offset(0, 0);
            SidebarDrawShape(CurrentSurface_00887314, ConvertA_0087F6CC, BarShapeTop_00B0FA3C, 0,
                             &position, &bounds, 0, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
            if (At_5544) {
                position = *ButtonPointA_00B0FC60;
            } else {
                position = *ButtonPointB_00B0FC64;
            }
            SidebarDrawShape(CurrentSurface_00887314, ConvertA_0087F6CC, BarShapeThumb_00B0FA90, 0,
                             &position, &bounds, 0, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
            if (At_5544) {
                position.X = SlotArea_00B0FC68->X;
                position.Y = BarArea_00B0FC58->Y;
                for (int slot = 0; slot < SlotCount_00B0F9E4; ++slot) {
                    Point2D offset(0, 0);
                    SidebarDrawShape(CurrentSurface_00887314, ConvertA_0087F6CC, BarShapeSlot_00B0FAA8, 0,
                                     &position, &bounds, 0, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
                    position.X = position.X + SlotArea_00B0FC68->Width;
                }
                for (int index = 0; index < 25; ++index) {
                    SidebarButton* button = GetCommandButton(index);
                    if (button != 0 && button->ShapeData != 0) {
                        button->Draw(1);
                        button->At_54 = false;
                    }
                }
            }
            position.X = *EndX_00B0FC6C;
            SidebarDrawShape(CurrentSurface_00887314, ConvertA_0087F6CC, BarShapeEnd_00B0FABC, 0,
                             &position, &bounds, 0, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
            if (At_5544) {
                CommandButtonA_00B0CCB0.Draw(1);
            } else {
                CommandButtonB_00B0CC40.Draw(1);
            }
            At_5546 = true;
            At_5545 = false;
            if (BarHistoryCount_00B0CD44 < 4) {
                BarHistoryCount_00B0CD44 = BarHistoryCount_00B0CD44 + 1;
            }
            for (int i = BarHistoryCount_00B0CD44 - 2; i >= 0; --i) {
                BarHistory_00B0CC00[i + 1] = BarHistory_00B0CC00[i];
            }
            BarHistory_00B0CC00[0] = CurrentSurface_00887314;
        } else {
            At_5546 = false;
        }
    }
    SidebarClass::vf_16(forced);
}

// INoticeSink slot 0 of TabClass (table 0x7EDFAC at +0x5518; RET 8). The body does not use `this`.
// FUNCTION: GAMEMD 0x6D1770
bool TabClass::Notice(int id, int arg)
{
    if (id == 0x11C7) {
        SidebarButton* button = GetCommandButton(ActiveCommandIndex_00B0CC1C);
        if (button != 0 && !button->IsOn) {
            button->TurnOn();
        }
        return true;
    }
    if (id == 0x11C8) {
        SidebarButton* button = GetCommandButton(ActiveCommandIndex_00B0CC1C);
        if (button != 0 && button->IsOn) {
            button->TurnOff();
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6D1800
const wchar_t* TabClass::vf_33(int id)
{
    return SidebarClass::vf_33(id);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0CB78
int CommandSlotTable_00B0CB78[25];
// END defined globals
