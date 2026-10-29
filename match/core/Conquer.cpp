// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Conquer.CPP. The name is the source-file string at 0x81d4f8
//   in retail gamemd.exe v1.001, passed by the assert at 0x48cb8e inside this object's
//   code range (0x48c6b0-0x48e28f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   jump-table @0x48DD10 and discriminator byte-table @0x48DD24 were decoded to
//   recover the (AbstractType -> array) mapping; cross-checked against YRpp
//   (reconfirmed here).
//
//   Names cross-checked against YRpp (each
//   offset/address reconfirmed against the user's binary below).
//
// Translation unit: Theater::FindIndex — linear case-insensitive lookup of a
// theater by ID over the fixed 6-entry Theater::Array.
//
//   GLOBAL:   GAMEMD 0x7E1B78   Theater::Array[6]    (0x70 stride; end 0x7E1E18)
//   LIBRARY:  GAMEMD 0x7C8D20   _stricmp             (CRT; reloc-normalised call)
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names.
//
// Small leaves (64 bytes or less) between 0x470000 and 0x500000 that other
// translation units already declared as callees but nothing defined.
//
//   cross-checked against YRpp.

#include "empty_function_family_methods.h"
#include "../_layout/session_class.h"
#include "mathtbl_init_shapes.h"

#include "techno_type_class_getbytype_methods.h"

#include "theater_methods.h"

// The fixed global array. Its address (0x7E1B78) and the end sentinel
// (&Array[6] == 0x7E1E18) are emitted as relocations and normalised by the
// differ; confirmed numerically from the 0x48DBE0 disassembly.
extern Theater Theater_Array[6];

// CRT case-insensitive compare @0x7C8D20 — declared (no body) so cl emits a
// reloc-normalised call rather than inlining an intrinsic.
extern "C" int __cdecl _stricmp(const char* s1, const char* s2);

#include "trivial_tu055_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" size_t __cdecl strlen(const char* s);
#pragma intrinsic(strlen)

// GLOBAL: GAMEMD 0x00A8ED84
extern "C" int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x00AA0738
extern "C" int DAT_00AA0738;
// GLOBAL: GAMEMD 0x007E1B60 (five string pointers)
extern "C" const char* const DAT_007E1B60[5];
// GLOBAL: GAMEMD 0x007E523C (nineteen string pointers)
extern "C" const char* const DAT_007E523C[19];
// GLOBAL: GAMEMD 0x0081DA28 (twelve string pointers)
extern "C" const char* const DAT_0081DA28[12];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

// 0x4CAC40: x87 helper taking one double and returning one (callee only).
double __cdecl FUN_004CAC40(double value);
// 0x5117D0: name -> index, -1 when absent (callee only).
int FUN_005117D0(const char* name);

// ---------------------------------------------------------------------------

#include "../_layout/obj_00483460.h"

#include "../_layout/obj_00485060.h"

#include "../_layout/obj_004870b0.h"

#include "../_layout/pair_00487f20.h"

#include "../_layout/obj_0048ba80.h"

#include "../_layout/obj_004a1d30.h"

#include "../_layout/obj_004a50f0.h"

#include "../_layout/pair_004c1b50.h"

#include "../_layout/obj_004c91c0.h"

#include "../_layout/obj_004ca160.h"

// GLOBAL: GAMEMD 0x0085D0A4 (4096-entry float table)
extern "C" const float DAT_0085D0A4[4096];

#include "../_layout/obj_004e1100.h"

struct Obj_004D2790;

struct Vtbl_004D2790;

#include "../_layout/obj_004d2790.h"


#include "../_layout/vtbl_004d2790.h"

#include "../_layout/record_004d2790.h"

// 0x7C5F3D and 0x7C5FFF: runtime-library helpers with no binary name; the
// first returns a byte (callees only).
extern "C" char __cdecl FUN_007C5F3D();
extern "C" void __cdecl FUN_007C5FFF();
extern "C" char* __cdecl strncpy(char* dst, const char* src, size_t count);

// GLOBAL: GAMEMD 0x0084E863
extern "C" signed char DAT_0084E863;
// GLOBAL: GAMEMD 0x0084E865
extern "C" const char DAT_0084E865[];

extern "C" char* __cdecl strcpy(char* dst, const char* src);
#pragma intrinsic(strcpy)
extern "C" char* __cdecl _strupr(char* text);

#include "../_layout/text_004f4cb0.h"

#include "../_layout/obj_004f4c20.h"

#include "unsorted_callback_methods.h"

#include "../map/map_class_methods.h"

// ---------------------------------------------------------------------------
// Externs reconfirmed numerically from the disasm at the listed addresses.
// ---------------------------------------------------------------------------

// ObjectClass::CurrentObjects @ 0x00A8ECB8.  Disasm touches Items (+0x04 =>
// 0x00A8ECBC) and Count (+0x10 => 0x00A8ECC8).
#include "../_layout/current_objects.h"
#include "../_layout/object_class.h"

// Case-insensitive string compare (retail __cdecl helper @ 0x007C8D20).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

// Trailing helpers invoked by UnselectAll (not matched here — declared so cl
// emits reloc-normalised calls):
//   0x00731D00  __fastcall(arg in ECX)   — clears a selection-drag latch pair.
//   0x00431060  __fastcall(this in ECX)  — clears the per-cell select flags of
//                                          the global selection grid @ 0x0089C3B0.
void sub_731D00(void* a);
void sub_431060(void* self);
extern int DAT_0089C3B0;  // selection grid base @ 0x0089C3B0

// __thiscall (ECX=this), no explicit args, vtable slot at +0x150 — the per-object

// LandType name table @ 0x0081DA28 .. 0x0081DA58 (12 const char* entries:
// "Clear","Road","Water","Rock","Wall","Tiberium",...). Loop bound is the
// one-past pointer 0x0081DA58.
extern const char* const LandTypeName[12];

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E51E0
extern const double DAT_007E51E0;
// GLOBAL: GAMEMD 0x89E948
extern double DAT_0089E948;

// SYNTHETIC: GAMEMD 0x0048C6E0
// GLOBAL: GAMEMD 0x0089E9A0
double DAT_0089E9A0 = DAT_0089E948 / DAT_007E51E0;

// SYNTHETIC: GAMEMD 0x0048C700
// GLOBAL: GAMEMD 0x0089E988
double DAT_0089E988 = DAT_007E1718 / DAT_0089E9A0;

// SYNTHETIC: GAMEMD 0x0048C880
// GLOBAL: GAMEMD 0x0089E990
MathTblCoord DAT_0089E990;

// FUNCTION: GAMEMD 0x48C8A0
// Empty function.
void __cdecl FUN_0048C8A0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48D080
//
// The per-frame callback: service audio, run the first pump object, do the
// in-game half when a game is running, drain the message queue playing a
// blip for every chat line from somebody else, and once a second poke the
// two devices that keep the screensaver away.
//
// PARTIAL (43.6%, 99 of 101 instructions of the same kinds). Everything
// matches in form, including the mode branch laid out with the equal-to-one
// body out of line, the packed message record whose payload int sits one
// byte into the sender word, the drain loop with its peeled entry test and
// the once-a-second device guard. The residual is retail materialising the
// two sentinel arguments into dead registers (`OR ECX,-1` / `OR EAX,-1`
// then pushing them) where cl 8804 pushes the immediates, which shifts
// every later instruction by two. Tried: the sentinels as immediates and
// through named locals, and both orders for the mode tests. Same
// materialised-push-constant class recorded for the NearByLocation sites.
void __cdecl Unsorted_CallBack()
{
    FUN_00406F70();

    if (DAT_00B45B68 > 0 && *DAT_00B45B5C != 0) {
        Pump_0048D080* pump = *DAT_00B45B5C;
        (pump->*pump->Vptr->At_08)();
    }

    if (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) {
        FUN_0048D1E0();
    }

    if (Session_00A8B238.GameMode != 1) {
        if (Session_00A8B238.GameMode != 2) {
            goto guard;
        }
    } else if (!(DAT_00A8DAB8 & 1)) {
        return;
    }

    DAT_00A8EA70.NullModemClass::Service();
    if (DAT_00A8B230->At_3598) {
        Message_0048D080 message;
        int flag;
        while (DAT_00A8EA70.FUN_005F1C30(&message, &flag) > 0) {
            if (message.Kind == 0x6C && (message.SenderWord & 0xFF) != DAT_00A8DB30) {
                DAT_00AC4F58.FUN_00643C50(1, (double)message.Packed.Payload, -1, -1);
            }
        }
    }

guard:
    if (Session_00A8B238.GameMode == 4 && !DAT_00B77DC2 && gg_time(0) != DAT_0089E9B0) {
        if (DAT_00AC116C != 0 && DAT_00B77DCC == 0) {
            DAT_00AC116C->Vtbl->At_0C(DAT_00AC116C);
        }
        if (DAT_00AC1170 != 0) {
            DAT_00AC1170->Vtbl->At_1C(DAT_00AC1170);
        }
        DAT_0089E9B0 = gg_time(0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48D1D0
// Calls other functions.
bool FUN_0048D1D0(Obj_0048D1D0* a1, int a2)
{
    FUN_0048D080(a1, a2);
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48DB70
// Empty function.
void __cdecl FUN_0048DB70()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0048DB80
// Index of `name` in the five-entry table at 0x7E1B60, or -1.
int FUN_0048DB80(const char* name)
{
    if (name != NULL) {
        for (int i = 0; i < 5; i++) {
            if (_stricmp(DAT_007E1B60[i], name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

extern "C" const char DAT_00817F64[];
// FUNCTION: GAMEMD 0x0048DBC0
const char* FUN_0048DBC0(unsigned int index)
{
    if (index < 5)
        return DAT_007E1B60[index];
    return DAT_00817F64;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x48DBE0   Theater::FindIndex   (__fastcall)
//
// pName arrives in ECX (__fastcall). EBX=pName, EDI=index, ESI walks the array
// at 0x70 stride; on the first _stricmp==0 hit returns the index, else -1.
// ---------------------------------------------------------------------------
int Theater::FindIndex(const char* pName)
{
    for (int i = 0; i < 6; ++i) {
        if (_stricmp(pName, Theater_Array[i].ID) == 0) {
            return i;
        }
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48DC90  (__fastcall)
// Drain CurrentObjects by repeatedly invoking object[0]'s vtable[+0x150] virtual
// (each call de-registers itself, shrinking Count), then reset the drag latch and
// clear the selection grid.
void MapView_5865E0::UnselectAll()
{
    while (CurrentObjects.Count != 0)
    {
        CurrentObjects.Items[0]->vf_84();
    }
    sub_731D00(0);
    sub_431060(&DAT_0089C3B0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48DCD0  (__fastcall)
// Dispatch on AbstractType (in ECX) and index (in EDX). Retail compiles this as
// a dense byte-indexed jump table: LEA EAX,[abs-1]; CMP EAX,0x27; JA default;
// then a 40-entry byte-table selects one of five jump targets.
//   abs 1 / 40       -> UnitTypeClass::Array
//   abs 6 / 7        -> BuildingTypeClass::Array
//   abs 15 / 16      -> InfantryTypeClass::Array
//   abs 2 / 3        -> AircraftTypeClass::Array
// The case blocks are written in retail physical-emit order (Unit, Building,
// Infantry, Aircraft) so the jump table and block addresses line up byte-exact.
TechnoTypeClass* TechnoTypeClass::GetByTypeAndIndex(AbstractType abs, int index)
{
    switch (abs)
    {
    case AbstractType_Unit:
    case AbstractType_UnitType:
        return UnitTypeClass_ArrayItems[index];

    case AbstractType_Building:
    case AbstractType_BuildingType:
        return BuildingTypeClass_ArrayItems[index];

    case AbstractType_Infantry:
    case AbstractType_InfantryType:
        return InfantryTypeClass_ArrayItems[index];

    case AbstractType_Aircraft:
    case AbstractType_AircraftType:
        return AircraftTypeClass_ArrayItems[index];

    default:
        return 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0048DE70
// Index of `name` in the nineteen-entry table at 0x7E523C, or 0.
int FUN_0048DE70(const char* name)
{
    if (name != NULL) {
        for (int i = 0; i < 19; i++) {
            if (_stricmp(name, DAT_007E523C[i]) == 0) {
                return i;
            }
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0048DEB0
// One-bit mask for the index 0x5117D0 finds for `name`, or 0.
int FUN_0048DEB0(const char* name)
{
    int mask = 0;
    int index = FUN_005117D0(name);
    if (index != -1) {
        mask = 1 << index;
    }
    return mask;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0048DED0
void FUN_0048DED0()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x48DF80  (__fastcall)
// Map a land-type name to its index; "<none>" or NULL => -1; unknown => -1.
int MapView_5865E0::GetLandTypeFromName(const char* name)
{
    if (strcmpi("<none>", name) != 0 && name != 0)
    {
        int i = 0;
        const char* const* p = LandTypeName;
        while ((int)p < (int)&LandTypeName[12])
        {
            if (strcmpi(*p, name) == 0)
                return i;
            ++p;
            ++i;
        }
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0048DFD0
// Name for one of twelve values, or the string at 0x817474.
const char* FUN_0048DFD0(unsigned int value)
{
    if (value < 12) {
        return DAT_0081DA28[value];
    }
    return DAT_00817474;
}

// Index of a name in an eight-entry string table at 0x81DA58; NULL or unknown => -1.
extern const char* const DAT_0081DA58[8];
// FUNCTION: GAMEMD 0x0048DFF0
int FUN_0048DFF0(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < 8; ++i) {
            if (strcmpi(DAT_0081DA58[i], name) == 0)
                return i;
        }
    }
    return -1;
}

// Index of a name in a five-entry string table at 0x81DA78; NULL or unknown => -1.
extern const char* const DAT_0081DA78[5];
// FUNCTION: GAMEMD 0x0048E050
int FUN_0048E050(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < 5; ++i) {
            if (strcmpi(DAT_0081DA78[i], name) == 0)
                return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x0048E090
const char* FUN_0048E090(unsigned int index)
{
    if (index < 5)
        return DAT_0081DA78[index];
    return DAT_00817474;
}
