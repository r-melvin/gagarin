// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The ToolTipManager bodies that retail builds with automatic inlining: the
// destructor (which expands FUN_00724BE0 and the vector destructor), the
// window-message hook (which expands FUN_00724A30 twice), and those two
// helpers themselves. The rest of the class is in tooltip_manager.cpp, whose
// bodies (Remove in particular) only match without /Ob2. Bodies ascending by
// retail address.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
#include "tooltip_manager_shared.h"

// USER32 KillTimer, reached through the IAT slot at 0x7e148c (reloc-normalised).
extern "C" __declspec(dllimport) int __stdcall KillTimer(void* hWnd,
                                                         unsigned int uIDEvent);
// USER32 SetTimer, GetCursorPos and ScreenToClient through the IAT slots at
// 0x7e1494, 0x7e13c0 and 0x7e1458 (reloc-normalised).
extern "C" __declspec(dllimport) unsigned int __stdcall SetTimer(void* hWnd,
    unsigned int nIDEvent, unsigned int uElapse, void* lpTimerFunc);
extern "C" __declspec(dllimport) int __stdcall GetCursorPos(Point2D* lpPoint);
extern "C" __declspec(dllimport) int __stdcall ScreenToClient(void* hWnd, Point2D* lpPoint);

// The Win32 message record the hook at 0x724200 receives.
struct tagMSG
{
    void* hwnd;            // +0x00
    unsigned int message;  // +0x04
    unsigned int wParam;   // +0x08
    long lParam;           // +0x0C
    unsigned long time;    // +0x10
    Point2D pt;            // +0x14
};
GG_STATIC_ASSERT(offsetof(tagMSG, message) == 0x04);
GG_STATIC_ASSERT(offsetof(tagMSG, wParam) == 0x08);
GG_STATIC_ASSERT(sizeof(tagMSG) == 0x1C);

// GLOBAL: GAMEMD 0xA8F7D8 -- coordinate debug display on.
extern bool DisplayScFlag_00A8F7D8;

// FUNCTION: GAMEMD 0x7240B0
// Stops the 'PITT' timer, redraws the area of a showing tip, then frees the
// table and every registered tip record.
ToolTipManager::~ToolTipManager()
{
    KillTimer(this->hWnd, 0x54544950);  // 'PITT'
    FUN_00724BE0();
    Table.Clear();
    for (int i = 0; i < ToolTips.Count; ++i) {
        if (ToolTips.Items[i])
            delete (ToolTip*)ToolTips.Items[i];
    }
    ToolTips.Clear();
}

// FUNCTION: GAMEMD 0x724200
// The message hook while active. Mouse movement restarts the show delay (or,
// with no delay, picks the tip under the cursor at once); a button message
// stops the timer; the 'PITT' timer itself picks the tip under the cursor.
// A picked tip that Process accepts arms the hide timer.
void ToolTipManager::FUN_00724200(const tagMSG* msg)
{
    if (IsActive != true)
        return;
    switch (msg->message) {
    case 0x201:
    case 0x202:
    case 0x204:
    case 0x205:
    case 0x207:
    case 0x208:
        KillTimer(hWnd, 0x54544950);
        FUN_00724BE0();
        break;
    case 0x200:
        if (ToolTipDelay != 0 && !DisplayScFlag_00A8F7D8) {
            KillTimer(hWnd, 0x54544950);
            SetTimer(hWnd, 0x54544950, ToolTipDelay, 0);
            FUN_00724BE0();
        } else {
            GetCursorPos(&CurrentMousePosition);
            ScreenToClient(hWnd, &CurrentMousePosition);
            CurrentToolTip = const_cast<ToolTip*>(FUN_00724A30(CurrentMousePosition));
            if (Process())
                SetTimer(hWnd, 0x54544950, unknown_230, 0);
        }
        break;
    case 0x113:
        if (msg->wParam == 0x54544950) {
            KillTimer(hWnd, 0x54544950);
            if (CurrentToolTip) {
                FUN_00724BE0();
            } else {
                GetCursorPos(&CurrentMousePosition);
                ScreenToClient(hWnd, &CurrentMousePosition);
                CurrentToolTip = const_cast<ToolTip*>(FUN_00724A30(CurrentMousePosition));
                if (Process())
                    SetTimer(hWnd, 0x54544950, unknown_230, 0);
            }
        }
        break;
    }
}

// FUNCTION: GAMEMD 0x724A30
const ToolTip* ToolTipManager::FUN_00724A30(const Point2D& point) const
{
    for (int i = 0; i < ToolTips.Count; ++i) {
        if (ToolTips.Items[i]->Bounds.Contains(point))
            return ToolTips.Items[i];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x724BE0
void ToolTipManager::FUN_00724BE0()
{
    if (CurrentToolTip != 0) {
        MarkToRedraw(CurrentToolTipData);
    }
}
