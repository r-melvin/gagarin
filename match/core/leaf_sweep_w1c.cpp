// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Second sweep of small unowned leaves between 0x401000 and 0x540000: predicates,
// copies and short forwarders. Ordered ascending by retail address.
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

struct Sub_00406250
{
};
void __fastcall FUN_00407150(Sub_00406250* self, int value);

struct Obj_00406250
{
    char Pad_00[0x108];
    Sub_00406250 unknown_108;
};
GG_STATIC_ASSERT(offsetof(Obj_00406250, unknown_108) == 0x108);

// FUNCTION: GAMEMD 0x406250
// Clamps the value into 0..0x4000 and hands it to the +0x108 member.
void __fastcall FUN_00406250(Obj_00406250* self, int value)
{
    if ((unsigned)value > 0x4000)
        value = 0x4000;
    else if (value < 0)
        value = 0;
    FUN_00407150(&self->unknown_108, value);
}

struct Obj_0042A690
{
    char Pad_00[0x18];
    int* unknown_18;
    int* unknown_1C;
    char Pad_20[8];
    int  unknown_28;
    // FUNCTION: GAMEMD 0x42A690
    bool IsCurrent(int unused, bool first, int index);
};
GG_STATIC_ASSERT(offsetof(Obj_0042A690, unknown_28) == 0x28);

// FUNCTION: GAMEMD 0x42A690
// True when entry `index` of the selected array equals the +0x28 value.
bool Obj_0042A690::IsCurrent(int unused, bool first, int index)
{
    if (first)
    {
        bool same = unknown_18[index] == unknown_28;
        return same;
    }
    bool same = unknown_1C[index] == unknown_28;
    return same;
}

struct Rec_00465550
{
    char Data[0x78];
};

// GLOBAL: GAMEMD 0x89D368
extern Rec_00465550 DAT_0089D368[];

struct Obj_00465550
{
    char Pad_00[0xEF0];
    int  unknown_EF0;
    // FUNCTION: GAMEMD 0x465550
    Rec_00465550* CurrentRecord();
};
GG_STATIC_ASSERT(offsetof(Obj_00465550, unknown_EF0) == 0xEF0);

// FUNCTION: GAMEMD 0x465550
// Record of the table selected by +0xEF0; value 9 selects record 6.
Rec_00465550* Obj_00465550::CurrentRecord()
{
    int index = unknown_EF0;
    if (index == 9)
        index = 6;
    return &DAT_0089D368[index];
}

// GLOBAL: GAMEMD 0x89E000
extern char DAT_0089E000[8];

// FUNCTION: GAMEMD 0x46D460
// True when all eight bytes of the table are non-zero.
bool FUN_0046D460()
{
    int i;
    for (i = 0; i < 8; i++)
    {
        if (!DAT_0089E000[i])
            break;
    }
    int all = i == 8;
    return all != 0;
}

// GLOBAL: GAMEMD 0x8B4148
extern int DAT_008B4148;

struct Obj_00484AB0
{
    char  Pad_00[0xEC];
    int   unknown_EC;
    char  Pad_F0[0x116 - 0xF0];
    short unknown_116;
    // FUNCTION: GAMEMD 0x484AB0
    int InRange();
};
GG_STATIC_ASSERT(offsetof(Obj_00484AB0, unknown_116) == 0x116);

// FUNCTION: GAMEMD 0x484AB0
// True when the +0x116 index is within 0..DAT_008B4148 and mode +0xEC is 10.
int Obj_00484AB0::InRange()
{
    short index = unknown_116;
    if (index >= 0 && index < DAT_008B4148 && unknown_EC == 10)
        return 1;
    return 0;
}

struct Rec_004A3840
{
    int Words[0x18];
};

struct Obj_004A3840
{
    Rec_004A3840 unknown_00[0x400];
    int          unknown_18000;
    // FUNCTION: GAMEMD 0x4A3840
    int Append(const Rec_004A3840* record);
};
GG_STATIC_ASSERT(offsetof(Obj_004A3840, unknown_18000) == 0x18000);

// FUNCTION: GAMEMD 0x4A3840
// Appends a 96-byte record; returns 1 when the 1024-entry table is full.
int Obj_004A3840::Append(const Rec_004A3840* record)
{
    if (unknown_18000 == 0x400)
        return 1;
    unknown_00[unknown_18000] = *record;
    unknown_18000++;
    return 0;
}

struct Item_0049E3B0
{
    char Data[0x4C];
};

struct Obj_0049E3B0
{
    char          Pad_00[0x58];
    Item_0049E3B0* unknown_58;
    int           unknown_5C;
    char          unknown_60;
    void Build();
    // FUNCTION: GAMEMD 0x49E3B0
    bool GetItem(int index, Item_0049E3B0** out);
    // FUNCTION: GAMEMD 0x49E4F0
    char GetCount(int* out);
};
GG_STATIC_ASSERT(offsetof(Obj_0049E3B0, unknown_60) == 0x60);
GG_STATIC_ASSERT(sizeof(Item_0049E3B0) == 0x4C);

// FUNCTION: GAMEMD 0x49E3B0
// Address of item `index` (built on demand); null and false when out of range.
bool Obj_0049E3B0::GetItem(int index, Item_0049E3B0** out)
{
    if (!unknown_60)
        Build();
    if (index >= 0 && index < unknown_5C)
    {
        *out = &unknown_58[index];
        return true;
    }
    *out = 0;
    return false;
}

// FUNCTION: GAMEMD 0x49E4F0
// Item count (built on demand); returns whether the table is built.
char Obj_0049E3B0::GetCount(int* out)
{
    if (!unknown_60)
        Build();
    *out = unknown_5C;
    return unknown_60;
}

struct Iface_004BAFE0
{
    virtual long __stdcall Slot0();
    virtual long __stdcall Slot1();
    virtual long __stdcall Slot2();
    virtual long __stdcall Slot3();
    virtual long __stdcall Slot4();
    virtual long __stdcall Slot5();
    virtual long __stdcall Slot6();
    virtual long __stdcall Slot7();
    virtual long __stdcall Slot8();
    virtual long __stdcall Slot9();
    virtual long __stdcall Slot10();
    virtual long __stdcall Slot11();
    virtual long __stdcall Slot12();
    virtual long __stdcall Slot13();
    virtual long __stdcall Slot14();
    virtual long __stdcall Slot15();
    virtual long __stdcall Slot16();
    virtual long __stdcall Slot17();
    virtual long __stdcall Slot18();
    virtual long __stdcall Slot19();
    virtual long __stdcall Slot20();
    virtual long __stdcall Slot21();
    virtual long __stdcall Slot22();
    virtual long __stdcall Slot23();
    virtual long __stdcall Slot24();
    virtual long __stdcall Slot25();
    virtual long __stdcall Slot26(int arg);
};

struct Obj_004BAFE0
{
    char            Pad_00[0xC];
    int             unknown_0C;
    char            Pad_10[0xC];
    Iface_004BAFE0* unknown_1C;
    // FUNCTION: GAMEMD 0x4BAFE0
    int IsReady();
    // FUNCTION: GAMEMD 0x4BAD30
    int Release(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_004BAFE0, unknown_1C) == 0x1C);

// FUNCTION: GAMEMD 0x4BAD30
// Passes `arg` to the interface; on success drops the +0x0C count when positive; always returns 1.
int Obj_004BAFE0::Release(int arg)
{
    if (unknown_1C->Slot26(arg) == 0 && unknown_0C > 0)
        unknown_0C--;
    return 1;
}

// FUNCTION: GAMEMD 0x4BAFE0
// True when the interface's slot 24 returns the expected status.
int Obj_004BAFE0::IsReady()
{
    if (unknown_1C && unknown_1C->Slot24() == (long)0x887601C2)
        return 1;
    return 0;
}

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// GLOBAL: GAMEMD 0x8B3F14
extern unsigned int DAT_008B3F14;

// FUNCTION: GAMEMD 0x4E24A0
// Three fiftieths of the time elapsed since the DAT_008B3F14 stamp (wrap-aware).
unsigned int FUN_004E24A0()
{
    unsigned int now = timeGetTime();
    unsigned int start = DAT_008B3F14;
    unsigned int elapsed;
    if (now <= start)
        elapsed = now - start - 1;
    else
        elapsed = now - start;
    return elapsed * 3 / 50;
}

// GLOBAL: GAMEMD 0xAA044C
extern int* DAT_00AA044C;
// GLOBAL: GAMEMD 0xAA0374
extern int DAT_00AA0374;
// GLOBAL: GAMEMD 0xAA0448
extern int DAT_00AA0448;

// FUNCTION: GAMEMD 0x53E4C0
// Entry `index` of the table when the table is live and the index is in range, else 0.
int __fastcall FUN_0053E4C0(int index)
{
    if (DAT_00AA0448 && index >= 0 && index < DAT_00AA0374)
        return DAT_00AA044C[index];
    return 0;
}

struct Iface_0053F5B0
{
    virtual void Slot0(int flag);
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
};

// GLOBAL: GAMEMD 0x887628
extern Iface_0053F5B0* DAT_00887628;
// GLOBAL: GAMEMD 0xAA05AC
extern int DAT_00AA05AC;
// GLOBAL: GAMEMD 0xAA05A8
extern int DAT_00AA05A8;

// FUNCTION: GAMEMD 0x53F5B0
// Calls slot 8 of the global interface when present, clears DAT_00AA05AC, returns 1.
int FUN_0053F5B0()
{
    if (DAT_00887628)
        DAT_00887628->Slot8();
    DAT_00AA05AC = 0;
    return 1;
}

// FUNCTION: GAMEMD 0x53F630
// Calls slot 1 of the global interface and clears DAT_00AA05A8.
void FUN_0053F630()
{
    DAT_00887628->Slot1();
    DAT_00AA05A8 = 0;
}

struct Session_0053AE00
{
    char Pad_00[0x16054];
    int  unknown_16054;
};
GG_STATIC_ASSERT(offsetof(Session_0053AE00, unknown_16054) == 0x16054);

// GLOBAL: GAMEMD 0xA83D4C
extern Session_0053AE00* DAT_00A83D4C;
// GLOBAL: GAMEMD 0x82809C
extern char DAT_0082809C[];
// GLOBAL: GAMEMD 0x828034
extern char DAT_00828034[];
// GLOBAL: GAMEMD 0xA8BC60
extern char DAT_00A8BC60[];

// GAMEMD 0x734E60
wchar_t* __fastcall FUN_00734E60(void* self, int zero, const char* file, int line);

struct Printer_0053AE00
{
    // GAMEMD 0x5D3BA0
    void Print(int a, int b, wchar_t* text, int color, int c, int d, int e);
};

// FUNCTION: GAMEMD 0x53AE00
// Looks up the message string for line 0x463 and prints it.
void FUN_0053AE00()
{
    wchar_t* text = FUN_00734E60(DAT_0082809C, 0, DAT_00828034, 0x463);
    int color = 3;
    if (DAT_00A83D4C)
        color = DAT_00A83D4C->unknown_16054;
    ((Printer_0053AE00*)DAT_00A8BC60)->Print(0, 0, text, color, 0x4046, 0x96, 0);
}

// GLOBAL: GAMEMD 0x8280B8
extern char DAT_008280B8[];

// FUNCTION: GAMEMD 0x53B410
// Looks up the message string for line 0x53B and prints it.
void FUN_0053B410()
{
    wchar_t* text = FUN_00734E60(DAT_008280B8, 0, DAT_00828034, 0x53B);
    int color = 3;
    if (DAT_00A83D4C)
        color = DAT_00A83D4C->unknown_16054;
    ((Printer_0053AE00*)DAT_00A8BC60)->Print(0, 0, text, color, 0x4046, 0x96, 0);
}

struct Factory_00523B10;

struct Product_00523B10
{
    char Pad_00[0x6F0];
    Product_00523B10(Factory_00523B10* owner, int arg);
};
GG_STATIC_ASSERT(sizeof(Product_00523B10) == 0x6F0);

struct Factory_00523B10
{
    // FUNCTION: GAMEMD 0x523B10
    Product_00523B10* Create(int arg);
};

// FUNCTION: GAMEMD 0x523B10
// Allocates and constructs a 0x6F0-byte product owned by this factory.
Product_00523B10* Factory_00523B10::Create(int arg)
{
    return new Product_00523B10(this, arg);
}

struct Product_00549AA0
{
    char Pad_00[0xB0];
    Product_00549AA0(int owner, int arg);
};
GG_STATIC_ASSERT(sizeof(Product_00549AA0) == 0xB0);

struct Factory_00549AA0
{
    char Pad_00[0x294];
    int  unknown_294;
    // FUNCTION: GAMEMD 0x549AA0
    bool Create(int arg, int unused);
};
GG_STATIC_ASSERT(offsetof(Factory_00549AA0, unknown_294) == 0x294);

// FUNCTION: GAMEMD 0x549AA0
// Allocates and constructs a 0xB0-byte product; true when allocation succeeded.
bool Factory_00549AA0::Create(int arg, int unused)
{
    if (new Product_00549AA0(unknown_294, arg))
        return true;
    return false;
}

// GLOBAL: GAMEMD 0x817474
extern char DAT_00817474[];
// GLOBAL: GAMEMD 0x817694
extern char DAT_00817694[];

struct Type_00428F70
{
    char Pad_00[0x24];
    char unknown_24[0x378 - 0x24];
    Type_00428F70(const char* name);
};
GG_STATIC_ASSERT(sizeof(Type_00428F70) == 0x378);

struct List_00428F70
{
    char         Pad_00[4];
    Type_00428F70** unknown_04;
    char         Pad_08[8];
    int          unknown_10;
};
GG_STATIC_ASSERT(offsetof(List_00428F70, unknown_10) == 0x10);

// FUNCTION: GAMEMD 0x00428F70
// Finds the entry whose name (+0x24) matches, creating a new one when none does;
// null for the placeholder names "<none>" and "none".
Type_00428F70* __fastcall FUN_00428F70(const char* name, List_00428F70* list)
{
    if (_stricmp(DAT_00817474, name) && _stricmp(DAT_00817694, name))
    {
        for (int i = 0; i < list->unknown_10; i++)
        {
            if (!_stricmp(list->unknown_04[i]->unknown_24, name))
                return list->unknown_04[i];
        }
        return new Type_00428F70(name);
    }
    return 0;
}

struct Type_00466000
{
    char Pad_00[0x24];
    char unknown_24[0x1798 - 0x24];
    Type_00466000(const char* name);
};
GG_STATIC_ASSERT(sizeof(Type_00466000) == 0x1798);

struct List_00466000
{
    char         Pad_00[4];
    Type_00466000** unknown_04;
    char         Pad_08[8];
    int          unknown_10;
};
GG_STATIC_ASSERT(offsetof(List_00466000, unknown_10) == 0x10);

// FUNCTION: GAMEMD 0x00466000
// Finds the entry whose name (+0x24) matches, creating a new one when none does;
// null for the placeholder names "<none>" and "none".
Type_00466000* __fastcall FUN_00466000(const char* name, List_00466000* list)
{
    if (_stricmp(DAT_00817474, name) && _stricmp(DAT_00817694, name))
    {
        for (int i = 0; i < list->unknown_10; i++)
        {
            if (!_stricmp(list->unknown_04[i]->unknown_24, name))
                return list->unknown_04[i];
        }
        return new Type_00466000(name);
    }
    return 0;
}

#pragma pack(push, 1)
struct Slot_004E4820
{
    char Pad_00[0x6B];
    int  unknown_6B;    // unaligned
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Slot_004E4820, unknown_6B) == 0x6B);

// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xA8DA90
extern Slot_004E4820* DAT_00A8DA90[8];
// GLOBAL: GAMEMD 0xAC11B4
extern Slot_004E4820* DAT_00AC11B4;


void __fastcall FUN_004E45A0(HWND self, int controlId);
void __fastcall FUN_004E4770(HWND self, int controlId);

inline int ControlId_004E4820(int index)
{
    if (index == 0) return 0x6A2;
    if (index == 1) return 0x522;
    if (index == 2) return 0x523;
    if (index == 3) return 0x524;
    if (index == 4) return 0x525;
    if (index == 5) return 0x526;
    if (index == 6) return 0x527;
    return index == 7 ? 0x528 : -1;
}

// FUNCTION: GAMEMD 0x004E4820
// For each of the eight slots, refreshes its control through FUN_004E4770 in game mode 3 or 4 when
// the slot is the current one or has no key, otherwise through FUN_004E45A0.
void __fastcall FUN_004E4820(HWND self)
{
    for (int i = 0; i < 8; i++)
    {
        int id = ControlId_004E4820(i);
        if ((DAT_00A8B238 == 3 || DAT_00A8B238 == 4)
            && (DAT_00A8DA90[i] == DAT_00AC11B4 || DAT_00A8DA90[i]->unknown_6B == -1))
            FUN_004E4770(self, id);
        else
            FUN_004E45A0(self, id);
    }
}

void __fastcall FUN_004E50C0(HWND self, int controlId);
void __fastcall FUN_004E5260(HWND self, int controlId);

inline int ControlId_004E5310(int index)
{
    if (index == 0) return 0x6A3;
    if (index == 1) return 0x6A4;
    if (index == 2) return 0x6A5;
    if (index == 3) return 0x6A6;
    if (index == 4) return 0x6A7;
    if (index == 5) return 0x6A8;
    if (index == 6) return 0x6AA;
    return index == 7 ? 0x6AB : -1;
}

// FUNCTION: GAMEMD 0x004E5310
// For each of the eight slots, refreshes its control through FUN_004E5260 in game mode 3 or 4 when
// the slot is the current one or has no key, otherwise through FUN_004E50C0.
void __fastcall FUN_004E5310(HWND self)
{
    for (int i = 0; i < 8; i++)
    {
        int id = ControlId_004E5310(i);
        if ((DAT_00A8B238 == 3 || DAT_00A8B238 == 4)
            && (DAT_00A8DA90[i] == DAT_00AC11B4 || DAT_00A8DA90[i]->unknown_6B == -1))
            FUN_004E5260(self, id);
        else
            FUN_004E50C0(self, id);
    }
}

void __fastcall FUN_004E5B60(HWND self, int controlId);
void __fastcall FUN_004E5CB0(HWND self, int controlId);

inline int ControlId_004E5D60(int index)
{
    if (index == 0) return 0x76D;
    if (index == 1) return 0x76E;
    if (index == 2) return 0x76F;
    if (index == 3) return 0x770;
    if (index == 4) return 0x771;
    if (index == 5) return 0x772;
    if (index == 6) return 0x773;
    return index == 7 ? 0x774 : -1;
}

// FUNCTION: GAMEMD 0x004E5D60
// For each of the eight slots, refreshes its control through FUN_004E5CB0 in game mode 3 or 4 when
// the slot is the current one or has no key, otherwise through FUN_004E5B60.
void __fastcall FUN_004E5D60(HWND self)
{
    for (int i = 0; i < 8; i++)
    {
        int id = ControlId_004E5D60(i);
        if ((DAT_00A8B238 == 3 || DAT_00A8B238 == 4)
            && (DAT_00A8DA90[i] == DAT_00AC11B4 || DAT_00A8DA90[i]->unknown_6B == -1))
            FUN_004E5CB0(self, id);
        else
            FUN_004E5B60(self, id);
    }
}

// GLOBAL: GAMEMD 0x8229C0
extern char DAT_008229C0[];

// GLOBAL: GAMEMD 0x822B7C
extern char DAT_00822B7C[];

// FUNCTION: GAMEMD 0x004E4770
// Fills the combo box `id` of the dialog with a single entry (message line 0x237),
// selects it, and re-shows the control when it was visible.
void __fastcall FUN_004E4770(HWND dialog, int id)
{
    HWND control = GetDlgItem(dialog, id);
    bool wasHidden = ShowWindow(control, SW_HIDE) == 0;
    SendMessageA(control, 0x14B, 0, 0);
    SendMessageA(control, 0x4DD, 0, 1);
    SendMessageA(control, 0x4DE, 0, 9);
    int index = (int)SendMessageA(control, 0x4C2, 0, (LPARAM)FUN_00734E60(DAT_00822B7C, 0, DAT_008229C0, 0x237));
    SendMessageA(control, 0x151, index, -2);
    SendMessageA(control, 0x498, index, -1);
    SendMessageA(control, 0x14E, 0, 0);
    SendMessageA(control, 0x4F1, 0, 1);
    if (!wasHidden)
        ShowWindow(control, SW_SHOW);
}

// STRING: GAMEMD 0x8229EC -- "GUI:Observer"
extern char DAT_008229EC[];

// FUNCTION: GAMEMD 0x004E3B00
// Fills the combo box `id` of the dialog with a single entry (the "GUI:Observer" label, message line 0x135),
// selects it, and re-shows the control when it was visible.
void __fastcall FUN_004E3B00(HWND dialog, int id)
{
    HWND control = GetDlgItem(dialog, id);
    bool wasHidden = ShowWindow(control, SW_HIDE) == 0;
    SendMessageA(control, 0x14B, 0, 0);
    SendMessageA(control, 0x4DE, 0, 7);
    int index = (int)SendMessageA(control, 0x4C2, 0, (LPARAM)FUN_00734E60(DAT_008229EC, 0, DAT_008229C0, 0x135));
    SendMessageA(control, 0x151, index, -3);
    SendMessageA(control, 0x14E, 0, 0);
    SendMessageA(control, 0x4F1, 0, 1);
    if (!wasHidden)
        ShowWindow(control, SW_SHOW);
}

// GLOBAL: GAMEMD 0x822B7C
extern char DAT_00822B7C[];

// FUNCTION: GAMEMD 0x004E5260
// Fills the combo box `id` of the dialog with a single entry (message line 0x36C),
// selects it, and re-shows the control when it was visible.
void __fastcall FUN_004E5260(HWND dialog, int id)
{
    HWND control = GetDlgItem(dialog, id);
    bool wasHidden = ShowWindow(control, SW_HIDE) == 0;
    SendMessageA(control, 0x14B, 0, 0);
    SendMessageA(control, 0x4DD, 0, 1);
    SendMessageA(control, 0x4DE, 0, 9);
    int index = (int)SendMessageA(control, 0x4C2, 0, (LPARAM)FUN_00734E60(DAT_00822B7C, 0, DAT_008229C0, 0x36C));
    SendMessageA(control, 0x151, index, -2);
    SendMessageA(control, 0x498, index, -1);
    SendMessageA(control, 0x14E, 0, 0);
    SendMessageA(control, 0x4F1, 0, 1);
    if (!wasHidden)
        ShowWindow(control, SW_SHOW);
}

// GLOBAL: GAMEMD 0x822BF8
extern char DAT_00822BF8[];

// FUNCTION: GAMEMD 0x004E5CB0
// Fills the combo box `id` of the dialog with a single entry (message line 0x48D),
// selects it, and re-shows the control when it was visible.
void __fastcall FUN_004E5CB0(HWND dialog, int id)
{
    HWND control = GetDlgItem(dialog, id);
    bool wasHidden = ShowWindow(control, SW_HIDE) == 0;
    SendMessageA(control, 0x14B, 0, 0);
    SendMessageA(control, 0x4DD, 0, 1);
    SendMessageA(control, 0x4DE, 0, 9);
    int index = (int)SendMessageA(control, 0x4C2, 0, (LPARAM)FUN_00734E60(DAT_00822BF8, 0, DAT_008229C0, 0x48D));
    SendMessageA(control, 0x151, index, -2);
    SendMessageA(control, 0x498, index, -1);
    SendMessageA(control, 0x14E, 0, 0);
    SendMessageA(control, 0x4F1, 0, 1);
    if (!wasHidden)
        ShowWindow(control, SW_SHOW);
}

// Vtable images installed by the constructors below.
extern char VTABLE_007E8C68[];
extern char VTABLE_007E8C70[];
extern char VTABLE_007E8C78[];
extern char VTABLE_007E8C94[];
extern char VTABLE_007E91EC[];
extern char VTABLE_007EB5E4[];
extern char VTABLE_007EB5EC[];
extern char VTABLE_007EB5F4[];
extern char VTABLE_007EB610[];
extern char VTABLE_007EB6D4[];
extern char VTABLE_007E4DD8[];

struct Sub_007E91EC
{
    char* Vtbl;
    Sub_007E91EC() { Vtbl = VTABLE_007E91EC; }
};

struct Base_004D3540
{
    char* Vtbl[4];
    // GAMEMD 0x6F4300
    Base_004D3540(int arg);
};

struct Obj_004D3540 : Base_004D3540
{
    char  Pad_10[0x588 - 0x10];
    Sub_007E91EC unknown_588;
    char  Pad_58C[0x5AC - 0x58C];
    Sub_007E91EC unknown_5AC;
    char  Pad_5B0[0x674 - 0x5B0];
    int   unknown_674;
    // FUNCTION: GAMEMD 0x4D3540
    Obj_004D3540(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_004D3540, unknown_674) == 0x674);

// FUNCTION: GAMEMD 0x4D3540
// Runs the base constructor, then seats this class's vtables and member vtable images.
Obj_004D3540::Obj_004D3540(int arg) : Base_004D3540(arg)
{
    unknown_674 = 0;
    Vtbl[0] = VTABLE_007E8C94;
    Vtbl[1] = VTABLE_007E8C78;
    Vtbl[2] = VTABLE_007E8C70;
    Vtbl[3] = VTABLE_007E8C68;
}

struct Sub_007EB6D4
{
    char* Vtbl;
    Sub_007EB6D4() { Vtbl = VTABLE_007EB6D4; }
};

struct Base_00523980
{
    char* Vtbl[4];
    // GAMEMD 0x711840
    Base_00523980(int arg);
};

struct Obj_00523980 : Base_00523980
{
    char  Pad_10[0xE50 - 0x10];
    Sub_007EB6D4 unknown_E50;
    char  Pad_E54[0xE6C - 0xE54];
    Sub_007EB6D4 unknown_E6C;
    char  Pad_E70[0xE88 - 0xE70];
    char* unknown_E88;
    // FUNCTION: GAMEMD 0x523980
    Obj_00523980(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_00523980, unknown_E88) == 0xE88);

// FUNCTION: GAMEMD 0x523980
// Runs the base constructor, then seats this class's vtables and member vtable images.
Obj_00523980::Obj_00523980(int arg) : Base_00523980(arg)
{
    unknown_E88 = VTABLE_007E4DD8;
    Vtbl[0] = VTABLE_007EB610;
    Vtbl[1] = VTABLE_007EB5F4;
    Vtbl[2] = VTABLE_007EB5EC;
    Vtbl[3] = VTABLE_007EB5E4;
}

extern char VTABLE_007E4B14[];
extern char VTABLE_007E4B1C[];
extern char VTABLE_007E4B24[];
extern char VTABLE_007E4B40[];
extern char VTABLE_007E4BA4[];

// Vector member (vtable at +0x00) whose inline constructor installs the items
// pointer, flags and growth step.
struct Vec_00471950
{
    char* Vtbl;
    int*  Items;
    int   Capacity;
    char  IsInitialized;
    char  IsAllocated;
    int   Count;
    int   Increment;
    Vec_00471950()
    {
        IsInitialized = 1;
        Items = 0;
        Capacity = 0;
        IsAllocated = 0;
        Vtbl = VTABLE_007E4BA4;
        Increment = 10;
        Count = 0;
    }
};
GG_STATIC_ASSERT(sizeof(Vec_00471950) == 0x18);

struct Base_00471950
{
    char* Vtbl[4];
    char  Pad_10[0x24 - 0x10];
    // GAMEMD 0x4101C0
    Base_00471950(int arg);
};

struct Obj_00471950 : Base_00471950
{
    Vec_00471950 unknown_24;
    // FUNCTION: GAMEMD 0x471950
    Obj_00471950(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_00471950, unknown_24) == 0x24);

// FUNCTION: GAMEMD 0x471950
// Runs the base constructor, builds the +0x24 vector member, seats this class's vtables.
Obj_00471950::Obj_00471950(int arg) : Base_00471950(arg)
{
    Vtbl[0] = VTABLE_007E4B40;
    Vtbl[1] = VTABLE_007E4B24;
    Vtbl[2] = VTABLE_007E4B1C;
    Vtbl[3] = VTABLE_007E4B14;
}

extern char VTABLE_007ECC1C[];
extern char VTABLE_007ECC24[];
extern char VTABLE_007ECC2C[];
extern char VTABLE_007ECC48[];
extern char VTABLE_007ECCEC[];

struct Vec_00544A00
{
    char* Vtbl;
    int*  Items;
    int   Capacity;
    char  IsInitialized;
    char  IsAllocated;
    int   Count;
    int   Increment;
    Vec_00544A00()
    {
        IsInitialized = 1;
        Items = 0;
        Capacity = 0;
        IsAllocated = 0;
        Vtbl = VTABLE_007ECCEC;
        Increment = 10;
        Count = 0;
    }
};
GG_STATIC_ASSERT(sizeof(Vec_00544A00) == 0x18);

struct Base_00544A00
{
    char* Vtbl[4];
    char  Pad_10[0x2A4 - 0x10];
    // GAMEMD 0x5F7320
    Base_00544A00(int arg);
};

struct Obj_00544A00 : Base_00544A00
{
    Vec_00544A00 unknown_2A4;
    // FUNCTION: GAMEMD 0x544A00
    Obj_00544A00(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_00544A00, unknown_2A4) == 0x2A4);

// FUNCTION: GAMEMD 0x544A00
// Runs the base constructor, builds the +0x2A4 vector member, seats this class's vtables.
Obj_00544A00::Obj_00544A00(int arg) : Base_00544A00(arg)
{
    Vtbl[0] = VTABLE_007ECC48;
    Vtbl[1] = VTABLE_007ECC2C;
    Vtbl[2] = VTABLE_007ECC24;
    Vtbl[3] = VTABLE_007ECC1C;
}

extern "C" void __cdecl FUN_007C8B3D(void* block);   // GAMEMD 0x7C8B3D operator delete

extern char VTABLE_007EA658[];
extern char VTABLE_007EA674[];
extern char VTABLE_007EA690[];

// Owned object with a virtual deleting destructor in slot 0.
struct Owned_004F3070
{
    virtual void Release(unsigned flags);
};

// Member owned through +0x0C and released by FUN_005D0580 followed by operator delete.
struct Inner_004F3A70
{
    // GAMEMD 0x5D0580
    void Teardown();
};

struct Base_004F3A70
{
    char*           Vtbl;
    char            Pad_04[8];
    Inner_004F3A70* unknown_0C;
    // FUNCTION: GAMEMD 0x4F3A70
    void Destroy();
};
GG_STATIC_ASSERT(offsetof(Base_004F3A70, unknown_0C) == 0x0C);

// FUNCTION: GAMEMD 0x4F3A70
// Seats the vtable and tears down the +0x0C member.
void Base_004F3A70::Destroy()
{
    Inner_004F3A70* inner = unknown_0C;
    Vtbl = VTABLE_007EA690;
    if (inner)
    {
        inner->Teardown();
        FUN_007C8B3D(inner);
    }
}

struct DerivedA_004F3070 : Base_004F3A70
{
    char            Pad_10[0x24 - 0x10];
    Owned_004F3070* unknown_24;
    // FUNCTION: GAMEMD 0x4F3070
    void DestroyA();
};
GG_STATIC_ASSERT(offsetof(DerivedA_004F3070, unknown_24) == 0x24);

// FUNCTION: GAMEMD 0x4F3070
// Seats the vtable, releases the +0x24 object, then runs the base destructor.
void DerivedA_004F3070::DestroyA()
{
    Owned_004F3070* owned = unknown_24;
    Vtbl = VTABLE_007EA658;
    if (owned)
        owned->Release(1);
    Base_004F3A70::Destroy();
}

struct Tail_004F3600
{
    // GAMEMD 0x7B46F0
    void Destroy();
};

struct DerivedB_004F3600 : Base_004F3A70
{
    char            Pad_10[0x30 - 0x10];
    Inner_004F3A70* unknown_30;
    Tail_004F3600   unknown_34;
    // FUNCTION: GAMEMD 0x4F3600
    void DestroyB();
};
GG_STATIC_ASSERT(offsetof(DerivedB_004F3600, unknown_34) == 0x34);

// FUNCTION: GAMEMD 0x4F3600
// Seats the vtable, frees the +0x30 member, destroys the +0x34 member, then runs the base destructor.
void DerivedB_004F3600::DestroyB()
{
    Inner_004F3A70* inner = unknown_30;
    Vtbl = VTABLE_007EA674;
    if (inner)
    {
        inner->Teardown();
        FUN_007C8B3D(inner);
    }
    unknown_34.Destroy();
    Base_004F3A70::Destroy();
}

extern char VTABLE_007E37EC[];
extern char VTABLE_007EA6AC[];

// Vector member (vtable at +0x00): its destructor frees an owned array.
struct Vec_004F3E90
{
    char* Vtbl;
    void* Items;
    int   Capacity;
    char  Pad_0C;
    char  IsAllocated;
    ~Vec_004F3E90()
    {
        Vtbl = VTABLE_007E37EC;
        if (Items && IsAllocated)
        {
            FUN_007C8B3D(Items);
            Items = 0;
        }
        IsAllocated = 0;
        Capacity = 0;
    }
};
GG_STATIC_ASSERT(offsetof(Vec_004F3E90, IsAllocated) == 0x0D);

struct DerivedC_004F3E90 : Base_004F3A70
{
    Vec_004F3E90 unknown_10;
    // FUNCTION: GAMEMD 0x4F3E90
    void DestroyC();
};
GG_STATIC_ASSERT(offsetof(DerivedC_004F3E90, unknown_10) == 0x10);

// FUNCTION: GAMEMD 0x4F3E90
// Seats the vtable, destroys the +0x10 vector member (freeing its owned array),
// then runs the base destructor.
void DerivedC_004F3E90::DestroyC()
{
    Vtbl = VTABLE_007EA6AC;
    unknown_10.~Vec_004F3E90();
    Base_004F3A70::Destroy();
}

struct CellView_004ACA90
{
    // GAMEMD 0x481130
    int Query();
};

struct Item_004ACA90
{
    // GAMEMD 0x4810A0
    int Locate(int arg);
};

struct Map_004ACA90
{
    // GAMEMD 0x565730
    CellView_004ACA90* GetCell(Item_004ACA90* item, int where);
};

// GLOBAL: GAMEMD 0x87F7E8
extern Map_004ACA90 DAT_0087F7E8;

// FUNCTION: GAMEMD 0x4ACA90
// Locates the item's cell on the global map and returns that cell's query result.
int __stdcall FUN_004ACA90(Item_004ACA90* item, int arg)
{
    int where = item->Locate(arg);
    return DAT_0087F7E8.GetCell(item, where)->Query();
}

struct CellView_004AA290
{
    // GAMEMD 0x47C5A0
    int Query();
};

struct Map_004AA290
{
    // GAMEMD 0x5657A0
    CellView_004AA290* GetCell(int a, int b, int c);
    // FUNCTION: GAMEMD 0x4AA290
    int QueryCell(int a, int b);
};

// FUNCTION: GAMEMD 0x4AA290
// Query result of the cell addressed by (a, b).
int Map_004AA290::QueryCell(int a, int b)
{
    return GetCell(a, b, 0)->Query();
}
