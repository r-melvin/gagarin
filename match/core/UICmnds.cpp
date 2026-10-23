// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit UICmnds.cpp. The name is the source-file string at 0x845598
//   in retail gamemd.exe v1.001, passed by the assert at 0x731b01 inside this object's
//   code range (0x730780-0x73442f). Functions are in ascending retail address order.
//
//   cross-checked against YRpp. Each function is
//
// reccmp annotations:

#include "../_layout/techno_class.h"
#include "../_layout/house_class.h"
#include "../_layout/techno_type_class.h"
#include "vector_class_operations.h"
#include <stdlib.h>
#include <string.h>
#include "../ui/input_controls/ui_display_chain.h"

// Sidebar "tab object" globals @ 0x00B0FE5C / 0x00B0FE60. Declared-only so cl
// emits reloc-normalised absolute stores/compares.
extern TechnoClass* SidebarTabObjectA;   // 0x00B0FE5C
extern TechnoClass* SidebarTabObjectB;   // 0x00B0FE60

#include "trivial_tu256_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F5C08
extern const double DAT_007F5C08;
// GLOBAL: GAMEMD 0xB0FDF8
extern double DAT_00B0FDF8;
// GLOBAL: GAMEMD 0xB0FE30
extern double DAT_00B0FE30;
// GLOBAL: GAMEMD 0xB0FE38
extern int DAT_00B0FE38;
// GLOBAL: GAMEMD 0xB0FE3C
extern int DAT_00B0FE3C;
// GLOBAL: GAMEMD 0xB0FE40
extern int DAT_00B0FE40;
// GLOBAL: GAMEMD 0xB0FE48
extern double DAT_00B0FE48;


// STRING: GAMEMD 0x00845598
extern const char DAT_00845598[] = "D:\\ra2mdpost\\UICmnds.cpp";
// STRING: GAMEMD 0x00845584
extern const char DAT_00845584[] = "MSG:NothingSelected";
// STRING: GAMEMD 0x008455C8
extern const char DAT_008455C8[] = "MSG:SelAcrossMap";
// STRING: GAMEMD 0x008455B4
extern const char DAT_008455B4[] = "MSG:SelAcrossScreen";
// STRING: GAMEMD 0x00845638
extern const char DAT_00845638[] = "MSG:Critical";
// STRING: GAMEMD 0x00845624
extern const char DAT_00845624[] = "MSG:HeavilyDamaged";
// STRING: GAMEMD 0x00845618
extern const char DAT_00845618[] = "MSG:Healthy";
// STRING: GAMEMD 0x00887734
extern const wchar_t DAT_00887734[] = L"";

// FUNCTION: GAMEMD 0x7307B0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007307B0()
{
    DAT_00B0FE48 = DAT_00B0FDF8 / DAT_007F5C08;
}

// FUNCTION: GAMEMD 0x7307D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007307D0()
{
    DAT_00B0FE30 = DAT_007E1718 / DAT_00B0FE48;
}

// FUNCTION: GAMEMD 0x730950
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00730950()
{
    DAT_00B0FE40 = 0;
    DAT_00B0FE38 = 0x80;
    DAT_00B0FE3C = 0x80;
}

// FUNCTION: GAMEMD 0x730970
void __cdecl FUN_00730970()
{
    if (DAT_00B0FE6C) {
        delete DAT_00B0FE6C;
        DAT_00B0FE6C = 0;
    }
}

// FUNCTION: GAMEMD 0x730990
bool FUN_00730990(int group)
{
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && !object->IsSelected && object->Group == group - 1)
                return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x730A10
int FUN_00730A10(int group)
{
    int result = 0;
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && object->Group == group - 1)
                ++result;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x730AD0
// Returns a constant.
int __cdecl FUN_00730AD0()
{
    return 0x4046;
}

// FUNCTION: GAMEMD 0x730AE0
// Returns a constant.
int __cdecl FUN_00730AE0()
{
    return 0xF0;
}

// FUNCTION: GAMEMD 0x731060
void FUN_00731060(int group)
{
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled) {
                if (object->Group == group - 1) object->Group = -1;
                if (object->IsSelected) object->Group = group - 1;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7310D0
void FUN_007310D0(int group)
{
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && object->Group == group - 1)
                object->Group = -1;
        }
    }
}

// FUNCTION: GAMEMD 0x731130
bool FUN_00731130(int group)
{
    for (int i = DAT_00A8EC78.Count - 1; i >= 0; --i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled) {
                if (object->Group == group - 1 && !object->IsSelected) return false;
                if (object->Group != group - 1 && object->IsSelected) return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x731A30
// Branching.
void FUN_00731A30(int a1, int a2)
{
    if (DAT_00A8B538 == 0)
    {
        FUN_004AC960(DAT_0087F7E8, a2, -1);
    }
}

// FUNCTION: GAMEMD 0x731A50
void FUN_00731A50(bool value)
{
    if (DAT_00A8B538 == 0) {
        FUN_006379C0();
        FUN_0063A120(value, true);
    }
}

// FUNCTION: GAMEMD 0x731A70
void FUN_00731A70(bool value)
{
    FUN_00637A10();
    if (DAT_00A8B538 == 0)
        FUN_0063A120(value, false);
}

// FUNCTION: GAMEMD 0x731A90
// Tail-forwards to another function.
void __cdecl FUN_00731A90()
{
    FUN_00637AA0();
}

// FUNCTION: GAMEMD 0x731AA0
bool __cdecl FUN_00731AA0()
{
    int count = DAT_00A8ECB8.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno && !object->CanAttackOnTheMove())
            return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x731BE0
// Stores to a global.
void __cdecl FUN_00731BE0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x731CF0
// Stores to a global.
void __cdecl FUN_00731CF0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x731D10
void FUN_00731D10(wchar_t* text)
{
    if (DAT_00A8ECB8.Count == 0) {
        wcscpy(text, FUN_00734E60(DAT_00845584, 0, DAT_00845598, 0x3F1));
    } else if (DAT_00B0FE64) {
        wcscpy(text, FUN_00734E60(DAT_008455C8, 0, DAT_00845598, 0x3F3));
    } else {
        wcscpy(text, FUN_00734E60(DAT_008455B4, 0, DAT_00845598, 0x3F5));
    }
}

// FUNCTION: GAMEMD 0x731EB0
UICmndsVector* FUN_00731EB0(bool (__fastcall *predicate)(TechnoClass*, void*), void* context)
{
    UICmndsVector* result = new UICmndsVector;
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (predicate(object, context)) result->AddItem(object);
    }
    return result;
}

// FUNCTION: GAMEMD 0x732050
UICmndsVector* __cdecl FUN_00732050()
{
    UICmndsVector* result = new UICmndsVector;
    int count = DAT_00A8ECB8.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno) result->AddItem(object);
    }
    return result;
}

// FUNCTION: GAMEMD 0x732110
void FUN_00732110(UICmndsVector* list, void (__fastcall *callback)(TechnoClass*, void*), void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        callback(list->Items[i], context);
}

// FUNCTION: GAMEMD 0x732140
void FUN_00732140(UICmndsVector* list, bool (__fastcall *predicate)(TechnoClass*, void*),
                 void (__fastcall *callback)(TechnoClass*, void*), void* condition, void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = list->Items[i];
        if (predicate(object, condition)) callback(object, context);
    }
}

// FUNCTION: GAMEMD 0x732190
bool FUN_00732190(UICmndsVector* list, bool (__fastcall *callback)(TechnoClass*, void*), void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        if (!callback(list->Items[i], context)) return false;
    return true;
}

// FUNCTION: GAMEMD 0x7321D0
bool FUN_007321D0(UICmndsVector* list, bool (__fastcall *callback)(TechnoClass*, void*), void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        if (callback(list->Items[i], context)) return true;
    return false;
}

// FUNCTION: GAMEMD 0x732210
int FUN_00732210(DynamicVectorClass<const char*>* list, const char* text)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        if (strcmp(text, list->Items[i]) == 0) return i;
    return -1;
}

// FUNCTION: GAMEMD 0x732580
int FUN_00732580(TechnoClass* object)
{
    if (object && object->IsAlive) {
        bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
        if (controlled) return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7325C0
int FUN_007325C0(TechnoClass* object)
{
    if (object->vf_11() != 6 && object->vf_33()->IsSelectableCombatant && object->vf_79())
        return 1;
    return 0;
}

// FUNCTION: GAMEMD 0x732CA0
// Branching.
void __cdecl FUN_00732CA0()
{
    if (DAT_00B0FE65 == 0)
    {
        unsigned char t1 = DAT_00B0FE65;
        DAT_00B0FE65 = 1;
        int c0 = timeGetTime();
        DAT_00B0FE68 = c0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x732CC0
void __cdecl FUN_00732CC0()
{
    if (DAT_00B0FE65) {
        DAT_00B0FE65 = 0;
        if (abs(int(timeGetTime() - DAT_00B0FE68)) <= 500) {
            FUN_00732950();
            Map_0087F7E8.GScreenClass::FlagToRedraw(1);
        }
    }
}

// FUNCTION: GAMEMD 0x733160
void FUN_00733160(TechnoClass* object)
{
    if (DAT_00B0FE6C) {
        for (int i = DAT_00B0FE6C->Count - 1; i >= 0; --i) {
            if (DAT_00B0FE6C->Items[i] == object) {
                DAT_00B0FE6C->Delete(i);
                return;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7335F0
int FUN_007335F0(TechnoClass* object)
{
    if (object && object->IsAlive) {
        bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
        if (controlled && object->vf_11() != 6) return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x733640
const wchar_t* FUN_00733640(int value)
{
    if (value == 0) return FUN_00734E60(DAT_00845638, 0, DAT_00845598, 0x644);
    if (value == 1) return FUN_00734E60(DAT_00845624, 0, DAT_00845598, 0x646);
    if (value == 2) return FUN_00734E60(DAT_00845618, 0, DAT_00845598, 0x648);
    return DAT_00887734;
}
// FUNCTION: GAMEMD 0x7336A0
int FUN_007336A0(int value)
{
    if (value == -1) return 0;
    if (value == 0) return 1;
    return value == 1 ? 2 : 0;
}

// FUNCTION: GAMEMD 0x733990
int FUN_00733990(int value)
{
    if (value == -1) return 0;
    if (value == 0) return 1;
    return value == 1 ? 2 : 0;
}

// FUNCTION: GAMEMD 0x733C60
int FUN_00733C60(TechnoClass* object, const char* text)
{
    const char* id = object->vf_34()->ID;
    if (text && strcmp(id, text) == 0 && object->vf_79()) return 1;
    return 0;
}
// FUNCTION: GAMEMD 0x734210
void __cdecl FUN_00734210()
{
    DAT_00845550 = timeGetTime() - 1601;
    DAT_00845554 = -1;
    DAT_00845558 = timeGetTime() - 1601;
    DAT_0084555C = -100;
}

// FUNCTION: GAMEMD 0x734270
// Removes this object from the two sidebar tab-object slots. A null this clears
// both slots; otherwise only the slot(s) that point at this object are cleared.
void TechnoClass::ClearSidebarTabObject()
{
    if (this == NULL) {
        SidebarTabObjectA = NULL;
        SidebarTabObjectB = NULL;
        return;
    }
    if (this == SidebarTabObjectA) {
        SidebarTabObjectA = NULL;
        return;
    }
    if (this == SidebarTabObjectB) {
        SidebarTabObjectB = NULL;
        return;
    }
}

// FUNCTION: GAMEMD 0x7342C0
bool FUN_007342C0(AbstractClass* object)
{
    if (!object) return false;
    return object->Flags.IsTechno;
}


