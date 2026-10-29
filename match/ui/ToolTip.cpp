// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT
// Placement lead: this file regresses under the project /Ob2 default, so a
// definition it can see probably lived in another original file.
//   Original translation unit ToolTip.cpp. The name is the source-file string at 0x8449cc
//   in retail gamemd.exe v1.001, passed by the assert at 0x724afa inside this object's
//   code range (0x723a90-0x7250bf). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// A free __fastcall table lookup at 0x723D20: an index below 0x3C selects one
// of twenty result codes through a byte-indexed jump table; any other index
// gives 0. Its callers and the meaning of the codes are not recovered (no
// direct code references). The case blocks are written in retail's block
// order (0x723D38 onwards).
//
//   cross-checked against YRpp.
//
// Flag bisection: /GX adds exception-unwind code absent from constructor
// 0x724000. This flag set reproduces its complete 0xA7-byte body; all other
// methods in this TU are verified under the same flags.
// Retail gamemd.exe v1.001 instructions and RTTI establish these methods,
// fields and virtual slots. Names were cross-checked with YRpp.
// Process references the retail source-path string D:\ra2mdpost\ToolTip.cpp.
//
// Flag bisection: /GX outlines the derived deleting destructor; omitting
// it reproduces the complete retail 0x724F40 body as well as all other slots.
// Raw vtables 0x7F57E8 and 0x7F57C8, RTTI descriptors 0x844938/0x844968,
// and complete entry-origin instruction spans establish these virtual methods.
// Slot names 5/6 remain placeholders. Generic definitions are shared in
// vector_class_operations.h; these instantiations bind the ToolTip entries.
// LIBRARY: GAMEMD 0x7C8E17
// operator new(size_t), emitted as ??2@YAPAXI@Z for these pointer arrays.


#include "toggle_class_methods.h"

#include "tooltip_manager_shared.h"


// USER32 KillTimer, reached through the IAT slot at 0x7e148c (reloc-normalised).
extern "C" __declspec(dllimport) int __stdcall KillTimer(void* hWnd,
                                                         unsigned int uIDEvent);

// Stripped debug logger at 0x4068E0 (cdecl, variadic; retail body is a bare RET).
extern "C" void __cdecl ToolTipManager_DebugPrint(const char* format, ...);

#include "tooltip_manager_shared.h"

template class DynamicVectorClass<const ToolTip*>;

#include "trivial_tu248_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F5798
extern const double DAT_007F5798;
// GLOBAL: GAMEMD 0xB0F538
extern double DAT_00B0F538;
// GLOBAL: GAMEMD 0xB0F570
extern double DAT_00B0F570;
// GLOBAL: GAMEMD 0xB0F578
extern int DAT_00B0F578;
// GLOBAL: GAMEMD 0xB0F57C
extern int DAT_00B0F57C;
// GLOBAL: GAMEMD 0xB0F580
extern int DAT_00B0F580;
// GLOBAL: GAMEMD 0xB0F588
extern double DAT_00B0F588;

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00723AC0()
{
    DAT_00B0F588 = DAT_00B0F538 / DAT_007F5798;
}

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00723AE0()
{
    DAT_00B0F570 = DAT_007E1718 / DAT_00B0F588;
}

// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00723C60()
{
    DAT_00B0F580 = 0;
    DAT_00B0F578 = 0x80;
    DAT_00B0F57C = 0x80;
}

// FUNCTION: GAMEMD 0x723D20
int FUN_00723D20(unsigned int index)
{
    switch (index) {
    case 0x00:
    case 0x39:
        return 0x0F;
    case 0x04:
        return 0x13;
    case 0x22:
        return 0x20;
    case 0x0C:
    case 0x26:
        return 0x16;
    case 0x27:
    case 0x28:
        return 0x1D;
    case 0x05:
    case 0x06:
    case 0x0D:
    case 0x20:
    case 0x2A:
    case 0x32:
        return 0x0A;
    case 0x01:
    case 0x03:
    case 0x0F:
    case 0x10:
    case 0x3B:
        return 0x09;
    case 0x14:
        return 0x0D;
    case 0x0B:
        return 0x12;
    case 0x11:
        return 0x14;
    case 0x12:
        return 0x0C;
    case 0x18:
        return 0x04;
    case 0x19:
        return 0x03;
    case 0x1A:
        return 0x02;
    case 0x1B:
        return 0x01;
    case 0x2E:
    case 0x2F:
    case 0x38:
    case 0x3A:
        return 0x24;
    case 0x08:
        return 0x25;
    case 0x33:
        return 0x29;
    case 0x34:
        return 0x2A;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x723E60
ToggleClass::ToggleClass(int id, int x, int y, int width, int height)
    : ControlClass(id, x, y, width, height, 5, 1),
      unknown_2C(0), IsOn(0), unknown_30(0)
{
}

// FUNCTION: GAMEMD 0x723EA0  (__thiscall)
// Set the toggle ON, then tail-call the redraw virtual:
//   mov eax,[ecx]; mov byte [ecx+2d],1; jmp [eax+0x48]
void ToggleClass::TurnOn()
{
    IsOn = true;
    MarkRedraw();
}

// FUNCTION: GAMEMD 0x723EB0  (__thiscall)
// Set the toggle OFF, then tail-call the redraw virtual:
//   mov eax,[ecx]; mov byte [ecx+2d],0; jmp [eax+0x48]
void ToggleClass::TurnOff()
{
    IsOn = false;
    MarkRedraw();
}

// FUNCTION: GAMEMD 0x724000
ToolTipManager::ToolTipManager(void* window)
 : CurrentToolTip(0), hWnd(window), IsActive(false), ToolTipDelay(1000), unknown_230(10000)
{
    ToolTips.Clear();
    gg_free(Table.Items);
    Table.Items = 0;
    Table.Count = 0;
    Table.Capacity = 0;
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

// FUNCTION: GAMEMD 0x724510
int ToolTipManager::FUN_00724510() const
{
    return ToolTipDelay;
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

// FUNCTION: GAMEMD 0x724550
int ToolTipManager::FUN_00724550() const
{
    return unknown_230;
}

// FUNCTION: GAMEMD 0x724560
void ToolTipManager::FUN_00724560(int value)
{
    unknown_230 = value;
}

// FUNCTION: GAMEMD 0x724570
int ToolTipManager::FUN_00724570() const
{
    return ToolTips.Count;
}

// FUNCTION: GAMEMD 0x724580
// Registers a copy of `tip` unless its gadget id is already in the table.
bool ToolTipManager::Add(ToolTip& tip)
{
    ToolTipTable* table = &Table;
    unsigned int key = tip.GadgetID;
    if (table->Count != 0) {
        if (table->HasCachedKey(&key))
            return false;
        ToolTipTableEntry* found = table->Search(&key);
        if (found != 0) {
            table->Cached = found;
            return false;
        }
    }
    ToolTip* copy = new ToolTip(tip);
    if (copy == 0)
        return false;
    if (!ToolTips.AddItem(copy)) {
        delete copy;
        return false;
    }
    if (table->Count + 1 > table->Capacity) {
        int grow = table->Capacity == 0 ? 10 : table->Capacity;
        if (grow < 0)
            return true;
        ToolTipTableEntry* items = new ToolTipTableEntry[table->Capacity + grow];
        if (items == 0)
            return true;
        for (int i = 0; i < table->Count; ++i)
            items[i] = table->Items[i];
        delete table->Items;
        table->Items = items;
        table->Capacity += grow;
        table->Cached = 0;
    }
    table->Items[table->Count].Key = copy->GadgetID;
    table->Items[table->Count].Data = copy;
    table->IsSorted = 0;
    ++table->Count;
    return true;
}

// FUNCTION: GAMEMD 0x724730 ToolTipManager::Remove (__thiscall, RET 4)
// PARTIAL: 97.2% -- register naming differs in a few instructions; multiset identical.
void ToolTipManager::Remove(unsigned int key)
{
    if (Table.Count == 0)
        return;
    if (!Table.Ensure(key))
        return;

    const ToolTip* data = Table.GetTip(key);
    if (this->CurrentToolTip == data && this->CurrentToolTip != 0)
        this->MarkToRedraw(this->CurrentToolTipData);

    Table.RemoveEntry(data);
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x724BB0
void ToolTipManager::DrawText(ToolTipManagerData& from)
{
    // STRING: GAMEMD 0x8449E8
    ToolTipManager_DebugPrint("ToolTip: %s\n", from.HelpText);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x724BD0
wchar_t* ToolTipManager::GetToolTipText(unsigned int id)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x724C00  ToolTipManager::IsToolTipShowing (__thiscall)
// A tip is on screen exactly while the current-tip pointer is set.
bool ToolTipManager::IsToolTipShowing() const
{
    return CurrentToolTip != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x724C30
// DynamicVectorClass<const ToolTip*>::Clear

// FUNCTION: GAMEMD 0x724C60
// DynamicVectorClass<const ToolTip*>::Slot5

// FUNCTION: GAMEMD 0x724C80
// VectorClass<const ToolTip*>::Slot6

// FUNCTION: GAMEMD 0x724C90
// VectorClass<const ToolTip*>::operator==

// FUNCTION: GAMEMD 0x724CD0
// VectorClass<const ToolTip*>::SetCapacity

// FUNCTION: GAMEMD 0x724D80
// VectorClass<const ToolTip*>::Clear

// FUNCTION: GAMEMD 0x724DB0
// VectorClass<const ToolTip*>::FindItemIndex

// FUNCTION: GAMEMD 0x724DF0
// VectorClass<const ToolTip*>::Slot5

// FUNCTION: GAMEMD 0x724E10
// DynamicVectorClass<const ToolTip*>::SetCapacity

// FUNCTION: GAMEMD 0x724EC0
// DynamicVectorClass<const ToolTip*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x724EF0
// VectorClass<const ToolTip*> scalar deleting destructor

// SYNTHETIC: GAMEMD 0x724F40
// DynamicVectorClass<const ToolTip*> scalar deleting destructor

template class VectorClass<const ToolTip*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x724F90
// Returns its receiver.
Obj_00724F90* Obj_00724F90::FUN_00724F90()
{
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x724FA0
// The Add caller supplies ECX=&Table and one stack key pointer; RET 4.
bool ToolTipTable::HasCachedKey(const unsigned int* key)
{
    if (Cached != 0 && Cached->Key == *key) {
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// SYNTHETIC: GAMEMD 0x4B5810
// ToggleClass scalar deleting destructor, emitted by its existing constructor.
