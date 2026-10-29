// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below (three COM objects share
//   one QueryInterface shape: a static interface table of {iid, offset, handler} entries).
//
// Address index: 0x7AC700 0x7AC870 0x7AD690

#include <windows.h>

// An interface id as four words.
struct GuidWords
{
    unsigned long Word0;
    unsigned long Word1;
    unsigned long Word2;
    unsigned long Word3;
};

typedef long (__stdcall *InterfaceHandler)(void* object, const GuidWords* iid, void** out, unsigned long offset);

// One interface table entry: id (null matches anything), offset of the interface inside the object and
// a handler (the value 1 marks a plain offset entry; a null handler ends the table).
struct InterfaceEntry
{
    const GuidWords* Iid;
    unsigned long Offset;
    InterfaceHandler Handler;
};

// GLOBAL: GAMEMD 0x7F7698 / 0x7F7650 / 0x7F7638 -- the interface tables.
extern const InterfaceEntry DAT_007F7698[];
extern const InterfaceEntry DAT_007F7650[];
extern const InterfaceEntry DAT_007F7638[];

// The shared walk: IUnknown is answered from the first entry's offset, otherwise the table is searched
// for the id and the matching entry's offset or handler produces the interface.
inline long InterfaceQuery(void* object, const InterfaceEntry* entries, const GuidWords* iid, void** out)
{
    if (out == 0) {
        return 0x80004003;
    }
    *out = 0;
    if (iid->Word0 == 0 && iid->Word1 == 0 && iid->Word2 == 0xC0 && iid->Word3 == 0x46000000) {
        IUnknown* unknown = (IUnknown*)((char*)object + entries->Offset);
        unknown->AddRef();
        *out = unknown;
        return 0;
    }
    while (entries->Handler != 0) {
        BOOL blind = entries->Iid == 0;
        if (blind || (entries->Iid->Word0 == iid->Word0 && entries->Iid->Word1 == iid->Word1
                      && entries->Iid->Word2 == iid->Word2 && entries->Iid->Word3 == iid->Word3)) {
            if (entries->Handler == (InterfaceHandler)1) {
                IUnknown* unknown = (IUnknown*)((char*)object + entries->Offset);
                unknown->AddRef();
                *out = unknown;
                return 0;
            }
            long result = entries->Handler(object, iid, out, entries->Offset);
            if (result == 0 || (!blind && result < 0)) {
                return result;
            }
        }
        entries++;
    }
    return 0x80004002;
}

// FUNCTION: GAMEMD 0x7AC700
// QueryInterface over the interface table at 0x7F7698.
long __stdcall FUN_007AC700(void* object, const GuidWords* iid, void** out)
{
    return InterfaceQuery(object, DAT_007F7698, iid, out);
}

// FUNCTION: GAMEMD 0x7AC870
// QueryInterface over the interface table at 0x7F7650.
long __stdcall FUN_007AC870(void* object, const GuidWords* iid, void** out)
{
    return InterfaceQuery(object, DAT_007F7650, iid, out);
}

// FUNCTION: GAMEMD 0x7AD690
// QueryInterface over the interface table at 0x7F7638.
long __stdcall FUN_007AD690(void* object, const GuidWords* iid, void** out)
{
    return InterfaceQuery(object, DAT_007F7638, iid, out);
}
