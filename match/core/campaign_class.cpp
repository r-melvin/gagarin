// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @0x46CC90 / @0x46CE10 (Ghidra
//   disasm). INI method addresses cross-checked against YRpp
//   (consult-only, no LICENSE; reconfirmed below). Each offset confirmed
//   numerically from the member-access disassembly.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x46CC90   CampaignClass::FindIndex          (__fastcall)
//   FUNCTION: GAMEMD 0x46CE10   CampaignClass::CreateFromINIList  (__fastcall)
//   GLOBAL:   GAMEMD 0xA83CF8   CampaignClass::Array  (DynamicVectorClass<CampaignClass*>)
//   LIBRARY:  GAMEMD 0x7C8D20   _strcmpi  (CRT; excluded from match target)

#include "campaign_class.h"

// --- referenced retail callees (declared, no body => reloc-normalised CALLs) ---
extern "C" int __cdecl _strcmpi(const char*, const char*);

// CCINIClass — only the three methods CreateFromINIList uses, bound to their
// retail addresses (YRpp, reconfirmed). Modelled as __thiscall
// members so cl emits ECX=this + the reloc CALL.
class CCINIClass
{
public:
    int         GetKeyCount(const char* pSection);                 // 0x526960
    const char* GetKeyName(const char* pSection, int nKeyIndex);   // 0x526CC0
    int ReadString(const char* pSection, const char* pKey,
                   const char* pDefault, char* pBuffer, size_t szBufferSize); // 0x528A10
};

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x46CC90  (__fastcall — name in ECX)
//
// Linear case-insensitive lookup of `name` in CampaignClass::Array by each
// entry's ID (+0x24); returns the index, or -1 if absent. Count and Items are
// reloaded from the global each iteration.
// ---------------------------------------------------------------------------
int __fastcall CampaignClass::FindIndex(const char* name)
{
    for (int i = 0; i < CampaignArray.Count; ++i)
    {
        CampaignClass* entry = CampaignArray.Items[i];
        if (_strcmpi(entry->ID, name) == 0)
            return i;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x410800 (decl; reloc) — AbstractTypeClass base constructor.
// FUNCTION: GAMEMD 0x7CA489 (decl; reloc) — wcscpy (CRT).
// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new (CRT).
// ---------------------------------------------------------------------------
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dest, const wchar_t* src);

// The FindIndex search again, `__forceinline` so retail's inlined copy inside
// CreateFromINIList is reproduced (cl 8804 will not inline the out-of-line
// __fastcall static on its own). Naming the entry in a local
// (`CampaignClass* entry = ...`) rather than subscripting inside the call
// argument is what puts the Items load in ECX and the buffer LEA in EDX, as
// retail has them; it is worth six instructions here and also took the
// out-of-line 0x46CC90 copy from 89.3% to 100%.
static __forceinline int FindIndexInline(const char* name)
{
    for (int i = 0; i < CampaignArray.Count; ++i)
    {
        CampaignClass* entry = CampaignArray.Items[i];
        if (_strcmpi(entry->ID, name) == 0)
            return i;
    }
    return -1;
}

// The constructor body, expanded by hand. Retail inlines the whole thing into
// CreateFromINIList, so it is written as a Construct member rather than a real
// constructor: under /GX `new CampaignClass(name)` wraps the allocation in an
// exception frame with an unwind funclet that frees the block, which retail
// does not have.
//
// The four vtable-pointer stores are the COM multiple-inheritance base's, read
// straight out of the disassembly (0x46CEC6..0x46CEE0).
__forceinline CampaignClass* CampaignClass::Construct(const char* name)
{
    this->BaseConstruct(name);

    this->idxCD = -1;
    this->FinalMovie = -1;

    this->Vptr  = (CampaignVtbl*)0x7E4A28;
    this->Vptr2 = (void*)0x7E4A0C;
    this->Vptr3 = (void*)0x7E4A04;
    this->Vptr4 = (void*)0x7E49FC;

    CampaignArray.AddItem(this);

    this->Scenario[0] = 0;
    wcscpy(this->Description, L"");

    return this;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x46CE10  (__fastcall — pINI in ECX)
//
// For every key in [Battles], read its value into a 32-char buffer, find or
// create the matching CampaignClass, and let it parse its own INI section.
//
// The retail body inlines three things: the FindIndex search, the whole
// CampaignClass constructor (four vptr stores, idxCD/FinalMovie = -1, the
// Array.AddItem, the Scenario/Description resets), and
// DynamicVectorClass<CampaignClass*>::AddItem with its SetCapacity growth arm.
// All three are spelled out above / below rather than called.
//
// MATCHED 100% (112/112), up from 2.7%. Four levers, in order of value:
//   1. The constructor written as `p = (CampaignClass*)::operator new(0x3A0);
//      p = p ? p->Construct(name) : 0;` with a `__forceinline` Construct.
//      `new CampaignClass(name)` with a declared constructor keeps the ctor out
//      of line and adds the /GX exception frame retail does not have; without
//      __forceinline cl 8804 refuses to expand Construct at all (2.7% -> 31.2%).
//   2. The allocate arm written FIRST (`if (idx == -1) { new } else
//      { existing }`). Retail lays the allocation inline and the
//      `Array.Items[idx]` lookup as the far block at 0x46CF58; the reverse
//      spelling swaps them and inverts every branch with it.
//   3. `int index = this->Count++; this->Items[index] = item;` in the inlined
//      AddItem. `Items[Count++] = item;` stores first and increments after,
//      where retail bumps the count before the element store
//      (`MOV ECX,[Count]; MOV EAX,ECX; INC ECX; MOV [Count],ECX`).
//      (2 + 3 together: 31.2% -> 92.0%.)
//   4. The searched entry bound to a local before the `_strcmpi` call
//      (92.0% -> 98.2%), and the grown capacity accumulated in place
//      (`grow += this->Capacity;` rather than `grow + this->Capacity` in the
//      argument) so the sum lands in the freshly loaded CapacityIncrement
//      register as retail's `ADD ECX,EAX` does (98.2% -> 100%).
// ---------------------------------------------------------------------------
void __fastcall CampaignClass::CreateFromINIList(CCINIClass* pINI)
{
    int count = pINI->GetKeyCount("Battles");
    for (int i = 0; i < count; ++i)
    {
        char buffer[32];
        pINI->ReadString("Battles",
                         pINI->GetKeyName("Battles", i),
                         "", buffer, sizeof(buffer));

        int idx = FindIndexInline(buffer);

        CampaignClass* pCampaign;
        if (idx == -1)
        {
            pCampaign = (CampaignClass*)::operator new(sizeof(CampaignClass));
            pCampaign = pCampaign ? pCampaign->Construct(buffer) : 0;
        }
        else
        {
            pCampaign = CampaignArray.Items[idx];
        }

        (pCampaign->*pCampaign->Vptr->At_64)(pINI);
    }
}
