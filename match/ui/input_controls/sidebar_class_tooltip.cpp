// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass slot 33 (tooltip text for a sidebar gadget id); layout and
// evidence: sidebar_class_layout.h. References the source path string
// D:\ra2mdpost\Sidebar.CPP at 0x83FAC4.

#include "sidebar_class_layout.h"

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- StringTable::LoadString.
wchar_t* __fastcall SidebarLoadString(const char* label, int* out, const char* file, int line);
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);

// GLOBAL: GAMEMD 0xB079B0 -- shared tooltip formatting buffer.
extern wchar_t TipBuffer_00B079B0[];

// Slot 33: tooltip text for a sidebar gadget id.
//
// PARTIAL (30.4%, 45/148; LCS 85/130 = 65.4%). Multiset delta: retail has one `sete`
// that cl lacks (retail materialises `!IsEnabled()` with `TEST; SETE; TEST; JE`) and ours
// has the per-case copies of the disabled-text block (retail shares one block, laid
// out directly after the first case, with the later cases jumping back to it). Variants:
// one shared check after the chain (9.2%), per-case inline `DisabledTip` (kept), a
// labelled shared check (14.6%, registers match retail but the shared block is still
// laid out last).
// A tooltip for a disabled button reads "<tip>\n(<disabled>)".
inline const wchar_t* DisabledTip(const SidebarButton* button, const wchar_t* text)
{
    if (!button->IsEnabled()) {
        wchar_t* disabled = SidebarLoadString("Tip:Disabled", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13F4);
        swprintf(TipBuffer_00B079B0, L"%s\n(%s)", text, disabled);
        return TipBuffer_00B079B0;
    }
    return text;
}

// FUNCTION: GAMEMD 0x6AC210
const wchar_t* SidebarClass::vf_33(int id)
{
    const wchar_t* text = PowerClass::vf_33(id);
    if (text != 0) {
        return text;
    }
    if (id == 0xC8) {
        text = SidebarLoadString("Tip:ScrollUp", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13CD);
        return DisabledTip(&ScrollUpButton_00B0B408, text);
    }
    if (id == 0xC9) {
        text = SidebarLoadString("Tip:ScrollDown", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13D3);
        return DisabledTip(&ScrollDownButton_00B0B328, text);
    }
    if (id >= 0xCB && id < 0xCF) {
        int tab = id - 0xCB;
        if (tab == 0) {
            text = SidebarLoadString("Tip:Tab1", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13DB);
        } else if (tab == 1) {
            text = SidebarLoadString("Tip:Tab2", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13DD);
        } else if (tab == 2) {
            text = SidebarLoadString("Tip:Tab3", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13DF);
        } else if (tab == 3) {
            text = SidebarLoadString("Tip:Tab4", 0, "D:\\ra2mdpost\\Sidebar.CPP", 0x13E1);
        }
        return DisabledTip(&TabButtons_00B07C48[tab], text);
    }
    int margin = 0x1A;
    if (Scenario_00A8B230->At_34B8) {
        margin = 0x12;
    }
    if (id >= 1000) {
        int rows = (DAT_00886F9C - StripY_00B0B4F8 - margin + DAT_00886F94 - 7) / 50;
        if (id < 1000 + rows * 2) {
            return Strips[ActiveTab].FUN_006A92E0(id - 1000);
        }
    }
    return text;
}
