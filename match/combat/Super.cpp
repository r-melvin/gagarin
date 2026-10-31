// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Super.CPP. The name is the source-file string at 0x842510
//   in retail gamemd.exe v1.001, passed by the assert at 0x6cc2de inside this object's
//   code range (0x6cac10-0x6ce37f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// SuperClass recharge-state accessors. Functions ordered ascending by retail
// address. Offsets confirmed numerically against the retail disassembly.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.

#include "../FUNCTION.H"
#include "super_class_methods.h"
#include "super_class_readiness_methods.h"
#include "super_class_more_methods.h"
#include "../core/mathtbl_init_shapes.h"

#include "trivial_tu225_methods.h"

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/empty_function_family_methods.h"

#include "../core/vector_remove_item_family_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "super_class_lose_methods.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F3FA8
extern const double DAT_007F3FA8;
// GLOBAL: GAMEMD 0xB0C008
extern double DAT_00B0C008;

// SYNTHETIC: GAMEMD 0x006CAC40
// GLOBAL: GAMEMD 0x00B0C080
double DAT_00B0C080 = DAT_00B0C008 / DAT_007F3FA8;

// SYNTHETIC: GAMEMD 0x006CAC60
// GLOBAL: GAMEMD 0x00B0C068
double DAT_00B0C068 = DAT_007E1718 / DAT_00B0C080;

// SYNTHETIC: GAMEMD 0x006CADE0
// GLOBAL: GAMEMD 0x00B0C070
MathTblCoord DAT_00B0C070;

// FUNCTION: GAMEMD 0x6CB7B0  SuperClass::Lose (__thiscall)
// Take a superweapon away from its house: clear both state flags and pull it
// off the sidebar timer list. Losing one the house never had is a no-op.
// The list removal is the inline DynamicVectorClass::RemoveItem. Its
// FindItemIndex call goes through `this` inside the inlined member, so cl
// keeps retail's indirect dispatch (`MOV EDX,[0xA83D50]; CALL [EDX+0x10]`).
bool SuperClass::Lose()
{
    if (IsPresent)
    {
        IsReady = false;
        IsPresent = false;

        ShowTimers.RemoveItem(this);

        return true;
    }

    return false;
}

// GLOBAL: GAMEMD 0xA83CB8 -- the super weapon array (defined in core/static_vector_init_stubs.cpp).
extern DynamicVectorClass<SuperClass*> DAT_00A83CB8;
// GLOBAL: GAMEMD 0xB0C000 -- the "no cell" sentinel.
extern CellStruct DAT_00B0C000;

// FUNCTION: GAMEMD 0x6CAEC0
// Default constructor: an unowned, untyped super weapon with no charge, then
// registered in the global array.
SuperClass::SuperClass()
    : CustomChargeTime(-1), Type(0), Owner(0), RechargeTimer(0), BlinkState(0), BlinkTimer_Low(0),
      BlinkTimer_High(0), SpecialSoundDuration(-1), CanHold(true), ChronoMapCoords(DAT_00B0C000),
      Animation(0), AnimationGotInvalid(false), IsPresent(false), IsOneTime(false), IsReady(false),
      IsSuspended(false), ChargeDrainState(-1)
{
    DAT_00A83CB8.AddItem(this);
}

// SYNTHETIC: GAMEMD 0x6CE220 -- SuperClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

// FUNCTION: GAMEMD 0x6CB820  SuperClass::SetReadiness (__thiscall)
//   mov al,[esp+4]; mov [ecx+0x6f],al; ret 4
void SuperClass::SetReadiness(bool ready)
{
    this->IsReady = ready;
}

// FUNCTION: GAMEMD 0x006CC070
void FUN_006CC070()
{
}

// FUNCTION: GAMEMD 0x6CC260  SuperClass::GetRechargeTime (__thiscall)
//   mov eax,[ecx+0x24]; cmp eax,-1; jnz ret; mov eax,[ecx+0x28]; mov eax,[eax+0xb0]; ret
int SuperClass::GetRechargeTime() const
{
    if (this->CustomChargeTime != -1)
        return this->CustomChargeTime;
    return this->Type->RechargeTime;
}

// FUNCTION: GAMEMD 0x6CC280  SuperClass::SetRechargeTime (__thiscall)
//   mov eax,[esp+4]; mov [ecx+0x24],eax; ret 4
void SuperClass::SetRechargeTime(int time)
{
    this->CustomChargeTime = time;
}

// FUNCTION: GAMEMD 0x6CC290  SuperClass::ResetRechargeTime (__thiscall)
//   mov dword [ecx+0x24],0xffffffff; ret
void SuperClass::ResetRechargeTime()
{
    this->CustomChargeTime = -1;
}

// FUNCTION: GAMEMD 0x6CC2A0
// Member getter (byte).
unsigned char Obj_006CC2A0::FUN_006CC2A0() const
{
    return unknown_28->unknown_E6;
}

// FUNCTION: GAMEMD 0x6CC2B0
//
// The sidebar caption for a superweapon's state. A suspended weapon reads
// "on hold" whatever else is true. A charge-drain weapon (Yuri's Psychic
// Dominator style) names its drain state - charging, ready, or firing - and has
// no caption for any other state. A plain weapon reads "ready" once charged and
// nothing before.
//
// The drain state is a real `switch`: retail lowers the three dense cases to
// `SUB ECX,0 / DEC ECX / DEC ECX` and places the case bodies 2, 1, 0 after
// the fall-through default. Two shape points matter: the "on hold" caption is
// the trailing block (the IsSuspended test jumps forward over everything, so
// the body sits under `if (!IsSuspended)`), and the switch carries its own
// `default: return 0;` - without it VC6 sinks the shared `XOR EAX,EAX; RET`
// to the end and turns the last case test into a `JNE default` (34.7%).
gg_wchar* SuperClass::NameReadiness() const
{
    if (!this->IsSuspended) {
        if (this->Type->UseChargeDrain) {
            switch (this->ChargeDrainState) {
            case 0:
                return FUN_00734E60(DAT_008424EC, 0, DAT_00842510, 0x397);
            case 1:
                return FUN_00734E60(DAT_0081B454, 0, DAT_00842510, 0x39A);
            case 2:
                return FUN_00734E60(DAT_008424FC, 0, DAT_00842510, 0x39D);
            default:
                return 0;
            }
        } else if (this->IsReady) {
            return FUN_00734E60(DAT_0081B454, 0, DAT_00842510, 0x3B0);
        }
        return 0;
    }

    return FUN_00734E60(DAT_0083FB2C, 0, DAT_00842510, 0x3B6);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CC360  SuperClass::CanFire (__thiscall)
// A suspended superweapon can never fire. For charge-drain weapons readiness is
// the drain state machine rather than the plain ready flag.
bool SuperClass::CanFire() const
{
    if (!IsSuspended) {
        if (Type->UseChargeDrain) {
            // The temporary is load-bearing: `return ChargeDrainState != 0;`
            // makes VC6 build an int 0/1 (XOR EAX,EAX + SETNE), whereas retail
            // materialises the bool in AL alone (MOV EAX,[+0x7C]; TEST EAX,EAX;
            // SETNZ AL). Binding it to a bool local first reproduces that.
            bool draining = ChargeDrainState != 0;
            return draining;
        }
        return IsReady;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CDE80
// Empty function that pops its stack arguments.
void __stdcall FUN_006CDE80(int a1, int a2)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CDE90  SuperClass::ShouldDrawProgress (__thiscall)
// Charge-drain weapons always show their sidebar progress overlay; everything
// else shows it only while still charging.
bool SuperClass::ShouldDrawProgress() const
{
    if (Type->UseChargeDrain)
        return true;

    return !IsReady;
}

// GLOBAL: GAMEMD 0xB0F5B8 -- the registry of super weapons that carry an animation.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F5B8;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// Registry append, expanded in place: the growth increment is tested before the sum.
static inline bool SuperRegistryAdd(DynamicVectorClass<AbstractClass*>* vector, AbstractClass* item)
{
    if (vector->Count >= vector->Capacity) {
        if (!vector->IsAllocated && vector->Capacity != 0)
            return false;
        if (vector->CapacityIncrement <= 0)
            return false;
        if (!vector->SetCapacity(vector->Capacity + vector->CapacityIncrement, 0))
            return false;
    }
    int index = vector->Count++;
    vector->Items[index] = item;
    return true;
}

// FUNCTION: GAMEMD 0x6CDEF0
HRESULT __stdcall SuperClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) SuperClass(LoadTag());
    if (Animation) {
        SuperRegistryAdd(&DAT_00B0F5B8, this);
    }
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Animation);
    BlinkTimer_Low = 0;
    BlinkTimer_High = 0;
    return 0;
}

// FUNCTION: GAMEMD 0x6CDFF0
// Forget a pointer that is going away: the type's owner or type slot, or the animation.
void SuperClass::vf_10(void* target, bool removed)
{
    if (target == Owner) {
        Owner = 0;
    }
    if (target == Type) {
        Type = 0;
    }
    if (target == Animation) {
        Animation = 0;
        AnimationGotInvalid = 1;
    }
}

// FUNCTION: GAMEMD 0x6CE1A0  SuperClass::ShouldFlashTab (__thiscall)
//   mov al,[ecx+0x70]; test al,al; jnz false        ; IsSuspended -> false
//   mov eax,[ecx+0x28]; mov dl,[eax+0xe5]; test dl,dl; jz noDrain
//     mov edx,[ecx+0x7c]; test edx,edx; jz false; jmp frames  ; ChargeDrainState
//   noDrain: mov dl,[ecx+0x6f]; test dl,dl; jz false           ; IsReady
//   frames: mov eax,[eax+0xe8]; cmp eax,-1; jnz chk; mov al,1; ret
//   chk: test eax,eax; jz false; mov ecx,[ecx+0x74]; add ecx,eax
//        mov eax,[0xa8ed84]; cmp ecx,eax; jle false; mov al,1; ret
//   false: xor al,al; ret
bool SuperClass::ShouldFlashTab() const
{
    if (!this->IsSuspended) {
        if (this->Type->UseChargeDrain) {
            if (this->ChargeDrainState == 0)
                goto fail;
        } else if (!this->IsReady) {
            goto fail;
        }

        int frames = this->Type->FlashSidebarTabFrames;
        if (frames == -1)
            return true;
        if (frames != 0 && this->ReadyFrame + frames > CurrentFrame)
            return true;
    }
fail:
    return false;
}

// FUNCTION: GAMEMD 0x6CE1F0
// The RTTI id of a super weapon.
int __stdcall SuperClass::vf_rtti_3()
{
    return 0x39;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CE200
// Returns a constant. Vtable slot 11 of SuperClass (RTTI).
int Obj_006CE200::FUN_006CE200() const
{
    return 0x39;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CE210
// Returns a constant. Vtable slot 12 of SuperClass (RTTI).
int Obj_006CE210::FUN_006CE210() const
{
    return 0x80;
}

// Take a reference on the held interface, if there is one.
struct Obj_006CE270 {
    IUnknown* unknown_00;
    void FUN_006CE270();
};
GG_STATIC_ASSERT(offsetof(Obj_006CE270, unknown_00) == 0x00);
// FUNCTION: GAMEMD 0x006CE270
void Obj_006CE270::FUN_006CE270()
{
    if (unknown_00 != 0) {
        unknown_00->AddRef();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006CE2D0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool ItemVector_0063DFD0::FUN_00006CE2D0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F3FA8
extern const double DAT_007F3FA8 = 60.0;
// GLOBAL: GAMEMD 0x81B454
extern const char DAT_0081B454[] = "TXT_READY";
// GLOBAL: GAMEMD 0x83FB2C
extern const char DAT_0083FB2C[] = "TXT_HOLD";
// GLOBAL: GAMEMD 0x8424EC
extern const char DAT_008424EC[] = "TXT_CHARGING";
// GLOBAL: GAMEMD 0x8424FC
extern const char DAT_008424FC[] = "TXT_FIRESTORM_ON";
// GLOBAL: GAMEMD 0x842510
extern const char DAT_00842510[] = "D:\\ra2mdpost\\Super.CPP";
// END defined globals
