// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   AddRef of the three COM event-sink objects of the online-service layer, read off retail
//   gamemd.exe v1.001. Each object holds, after its vptr, the reference count at +4. The sinks are
//   RTTI-named ATL CComObject instantiations (vtables 0x7F76B4, 0x7F766C, 0x7F78E4, slot 1); their
//   other slots are not modelled here.
//   Address index: 0x7A5220, 0x7AA6A0 (chat event callbacks), 0x7AC690 (chat), 0x7AC800 (net util),
//   0x7AD620 (download).

#include <windows.h>

#define GG_EVENT_SINK_CLASS(NAME)                                              \
    class NAME                                                                 \
    {                                                                          \
    public:                                                                    \
        virtual long __stdcall QueryInterface(const GUID& iid, void** ppv);    \
        virtual unsigned long __stdcall AddRef();                              \
        long __stdcall OnStatus(int code, int value);                          \
        long __stdcall OnLog(int code, int value);                             \
        LONG m_dwRef;                                                          \
    };

// FUNCTION: GAMEMD 0x785740 (decl; reloc)
void __fastcall FUN_00785740(int value);
// FUNCTION: GAMEMD 0x5E2700 (decl; reloc)
void __cdecl FUN_005E2700(int param, const wchar_t* format, ...);
// GLOBAL: GAMEMD 0xB77DC1
extern bool DAT_00B77DC1;
// GLOBAL: GAMEMD 0x7EEF28
extern int DAT_007EEF28;

GG_EVENT_SINK_CLASS(ChatEventSink_r12)
GG_EVENT_SINK_CLASS(NetUtilEventSink_r12)
GG_EVENT_SINK_CLASS(DownloadEventSink_r12)

// FUNCTION: GAMEMD 0x7A5220
// Forwards the value for a non-negative code.
long __stdcall ChatEventSink_r12::OnStatus(int code, int value)
{
    if (code >= 0) {
        FUN_00785740(value);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AA6A0
// Logs the value for a non-negative code unless logging is switched off.
long __stdcall ChatEventSink_r12::OnLog(int code, int value)
{
    if (!DAT_00B77DC1 && code >= 0) {
        FUN_005E2700(DAT_007EEF28, L">>> %hs", value);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AC690
unsigned long __stdcall ChatEventSink_r12::AddRef()
{
    return InterlockedIncrement(&m_dwRef);
}

// FUNCTION: GAMEMD 0x7AC800
unsigned long __stdcall NetUtilEventSink_r12::AddRef()
{
    return InterlockedIncrement(&m_dwRef);
}

// FUNCTION: GAMEMD 0x7AD620
unsigned long __stdcall DownloadEventSink_r12::AddRef()
{
    return InterlockedIncrement(&m_dwRef);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB77DC1
bool DAT_00B77DC1;
// GLOBAL: GAMEMD 0x7EEF28
int DAT_007EEF28 = -1;
// END defined globals
