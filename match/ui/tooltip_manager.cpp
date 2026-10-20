// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Flag bisection: /GX adds exception-unwind code absent from constructor
// 0x724000. This flag set reproduces its complete 0xA7-byte body; all other
// methods in this TU are verified under the same flags.
// Retail gamemd.exe v1.001 instructions and RTTI establish these methods,
// fields and virtual slots. Names were cross-checked with consult-only YRpp.
// Process references the retail source-path string D:\ra2mdpost\ToolTip.cpp.
#include "tooltip_manager_shared.h"


// USER32 KillTimer, reached through the IAT slot at 0x7e148c (reloc-normalised).
extern "C" __declspec(dllimport) int __stdcall KillTimer(void* hWnd,
                                                         unsigned int uIDEvent);

// Stripped debug logger at 0x4068E0 (cdecl, variadic; retail body is a bare RET).
extern "C" void __cdecl ToolTipManager_DebugPrint(const char* format, ...);


// FUNCTION: GAMEMD 0x724000
ToolTipManager::ToolTipManager(void* window)
 : CurrentToolTip(0), hWnd(window), IsActive(false), ToolTipDelay(1000), unknown_230(10000)
{
    ToolTips.Clear();
    gg_free(Table.Items);
    Table.Items = 0;
    Table.Count = 0;
    Table.unknown_08 = 0;
    Table.IsSorted = 0;
    Table.Cached = 0;
}

// FUNCTION: GAMEMD 0x7241A0  (__thiscall)
void ToolTipManager::SetState(bool bState)
{
    if (this->IsActive == bState)
        return;

    this->IsActive = bState;
    if (!bState)
    {
        KillTimer(this->hWnd, 0x54544950);  // 'PITT'
        if (this->CurrentToolTip)
            this->MarkToRedraw(this->CurrentToolTipData);
    }

    ToolTipManager_DebugPrint("Tooltips are %s.\n",
                              this->IsActive == 1 ? "on" : "off");
}

// FUNCTION: GAMEMD 0x724520  (__thiscall)
// MOV EAX,[ESP+4]; MOV [ECX+0x228],EAX; RET 4
void ToolTipManager::SetTimerDelay(int value)
{
    this->ToolTipDelay = value;
}

// FUNCTION: GAMEMD 0x724530  (__thiscall)
// MOV EAX,[ECX+0x228]; MOV [ECX+0x22c],EAX; RET
void ToolTipManager::SaveTimerDelay()
{
    this->LastToolTipDelay = this->ToolTipDelay;
}

// FUNCTION: GAMEMD 0x724540  (__thiscall)
// MOV EAX,[ECX+0x22c]; MOV [ECX+0x228],EAX; RET
void ToolTipManager::RestoreTimeDelay()
{
    this->ToolTipDelay = this->LastToolTipDelay;
}

// FUNCTION: GAMEMD 0x724730 ToolTipManager::Remove (__thiscall, RET 4)
void ToolTipManager::Remove(unsigned int key)
{
    ToolTipTable* table = &this->Table;
    if (this->Table.Count == 0)
        return;
    if (!table->Ensure(key))
        return;

    const ToolTip* data = table->GetTip(key);
    if (this->CurrentToolTip == data && this->CurrentToolTip != 0)
        this->MarkToRedraw(this->CurrentToolTipData);

    table->RemoveEntry(data);
    this->ToolTips.RemoveItem(data);

    if (data != 0)
        gg_free(const_cast<ToolTip*>(data));
}

// FUNCTION: GAMEMD 0x724AA0
bool ToolTipManager::Update(ToolTipManagerData& from)
{
    return true;
}

// FUNCTION: GAMEMD 0x724AB0
void ToolTipManager::MarkToRedraw(ToolTipManagerData& from)
{
    ClearDimension(CurrentToolTipData);
    CurrentToolTip = 0;
}

// FUNCTION: GAMEMD 0x724AD0
//
// Resolve the current tooltip's text and position it. The text comes from the
// string table when the tip carries a label, otherwise from the virtual by
// gadget id. Empty text drops the tip; otherwise the text is copied into the
// help block, the block is anchored at the mouse and handed to Update, whose
// refusal also drops the tip. Reports whether a tip is still current.
//
// Both drop paths fall through to the single trailing return: VC6 duplicates
// that tail into the Update-refused block with the just-stored zero forwarded
// (`MOV ECX,EBX .. CMP ECX,EBX; SETNZ AL`), which an explicit `return` in that
// block folds away to a bare register return instead.
bool ToolTipManager::Process()
{
    ToolTip* tip = this->CurrentToolTip;
    if (tip != 0) {
        wchar_t* text;
        if (tip->Text == 0)
            text = this->GetToolTipText(tip->GadgetID);
        else
            // STRING: GAMEMD 0x8449CC
            text = StringTable_LoadString(tip->Text, 0, "D:\\ra2mdpost\\ToolTip.cpp", 0x233);

        if (text != 0 && wcslen(text) > 0) {
            wcsncpy(this->CurrentToolTipData.HelpText, text, 0x100);
            this->CurrentToolTipData.X = this->CurrentMousePosition.X;
            this->CurrentToolTipData.Y = this->CurrentMousePosition.Y;
            if (!this->Update(this->CurrentToolTipData)) {
                ClearDimension(this->CurrentToolTipData);
                this->CurrentToolTip = 0;
            }
        } else {
            ClearDimension(this->CurrentToolTipData);
            this->CurrentToolTip = 0;
        }
    }
    return this->CurrentToolTip != 0;
}

// FUNCTION: GAMEMD 0x724B80
void ToolTipManager::Draw(bool onSidebar)
{
    if (onSidebar == true) {
        Process();
    }
    if (CurrentToolTip != 0) {
        DrawText(CurrentToolTipData);
    }
}

// FUNCTION: GAMEMD 0x724BB0
void ToolTipManager::DrawText(ToolTipManagerData& from)
{
    // STRING: GAMEMD 0x8449E8
    ToolTipManager_DebugPrint("ToolTip: %s\n", from.HelpText);
}

// FUNCTION: GAMEMD 0x724BD0
wchar_t* ToolTipManager::GetToolTipText(unsigned int id)
{
    return 0;
}

// FUNCTION: GAMEMD 0x724BE0
void ToolTipManager::FUN_00724BE0()
{
    if (CurrentToolTip != 0) {
        MarkToRedraw(CurrentToolTipData);
    }
}

// FUNCTION: GAMEMD 0x724C00  ToolTipManager::IsToolTipShowing (__thiscall)
// A tip is on screen exactly while the current-tip pointer is set.
bool ToolTipManager::IsToolTipShowing() const
{
    return CurrentToolTip != 0;
}

// FUNCTION: GAMEMD 0x724FA0
// The Add caller supplies ECX=&Table and one stack key pointer; RET 4.
bool ToolTipTable::HasCachedKey(const unsigned int* key)
{
    if (Cached != 0 && Cached->Key == *key) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x724FC0
ToolTipTableEntry* ToolTipTable::Search(unsigned int* key)
{
    if (Count == 0)
        return 0;
    if (!IsSorted) {
        FUN_007C8B48(Items, Count, sizeof(ToolTipTableEntry), CompareToolTipTableEntries);
        Cached = 0;
        IsSorted = 1;
    }
    return SearchSorted(key);
}

// FUNCTION: GAMEMD 0x725040
// qsort callback shared by ToolTipManager's table operations. SETGE in the
// retail entry compares signed DWORD keys, even though lookup uses unsigned
// keys. The original callback name and declaring scope are unconfirmed.
extern "C" int __cdecl CompareToolTipTableEntries(const void* a, const void* b)
{
    int left = (int)((const ToolTipTableEntry*)a)->Key;
    int right = (int)((const ToolTipTableEntry*)b)->Key;
    if (left == right)
        return 0;
    if (left < right)
        return -1;
    return 1;
}
