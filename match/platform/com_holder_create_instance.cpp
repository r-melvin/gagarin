// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Derived from the retail gamemd.exe v1.001 disassembly at 0x41C250.
//   Imports: CoCreateInstance (IAT 0x7E15FC), OleRun (IAT 0x7E1600).

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ComUnknown_0041C250;

struct ComUnknownVtbl_0041C250
{
    long (__stdcall* QueryInterface)(ComUnknown_0041C250*, const void* riid, void** ppv);
    long (__stdcall* AddRef)(ComUnknown_0041C250*);
    long (__stdcall* Release)(ComUnknown_0041C250*);
};
GG_STATIC_ASSERT(offsetof(ComUnknownVtbl_0041C250, QueryInterface) == 0x0);
GG_STATIC_ASSERT(offsetof(ComUnknownVtbl_0041C250, Release) == 0x8);

struct ComUnknown_0041C250 { ComUnknownVtbl_0041C250* Vtbl; };

extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(
    const void* rclsid, ComUnknown_0041C250* outer, unsigned long context,
    const void* riid, void** ppv);
extern "C" __declspec(dllimport) long __stdcall OleRun(ComUnknown_0041C250* object);

// GLOBAL: GAMEMD 0x817BB0 - IID of the held interface.
extern const char riid_00817BB0[16];
// GLOBAL: GAMEMD 0x817BC0 - IID_IUnknown.
extern const char riid_00817BC0[16];

// A smart-pointer style holder: one interface pointer.
struct ComPtr_0041C250
{
    ComUnknown_0041C250* Interface;   // +0x0000

    long CreateInstance(const void* rclsid, ComUnknown_0041C250* outer,
                        unsigned long context);
};
GG_STATIC_ASSERT(offsetof(ComPtr_0041C250, Interface) == 0);

// FUNCTION: GAMEMD 0x41C250
// Releases the held interface, then creates a new object. Out-of-process
// contexts (0x14) create as IUnknown, OleRun it, then query the held IID.
long ComPtr_0041C250::CreateInstance(const void* rclsid, ComUnknown_0041C250* outer,
                                     unsigned long context)
{
    long hr;
    if (Interface != 0) {
        Interface->Vtbl->Release(Interface);
    }
    if (context & 0x14) {
        ComUnknown_0041C250* unknown;
        hr = CoCreateInstance(rclsid, outer, context, riid_00817BC0, (void**)&unknown);
        if (hr < 0) {
            return hr;
        }
        hr = OleRun(unknown);
        if (hr >= 0) {
            hr = unknown->Vtbl->QueryInterface(unknown, riid_00817BB0, (void**)&Interface);
        }
        unknown->Vtbl->Release(unknown);
    } else {
        hr = CoCreateInstance(rclsid, outer, context, riid_00817BB0, (void**)&Interface);
    }
    return hr;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x817BB0
extern const char riid_00817BB0[16] = {-112, 50, 15, 7, 65, -104, -47, 17, -73, 9, 0, -96, 36, -35, -81, -47};
// GLOBAL: GAMEMD 0x817BC0
extern const char riid_00817BC0[16] = {0, 0, 0, 0, 0, 0, 0, 0, -64, 0, 0, 0, 0, 0, 0, 70};
// END defined globals
