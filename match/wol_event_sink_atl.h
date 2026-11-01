// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The three COM event-sink objects of the online-service layer, read off retail gamemd.exe v1.001.
// Each is an ATL 3.0 CComObject<> over a CComObjectRootEx<CComMultiThreadModel> class whose single
// interface is mapped with COM_INTERFACE_ENTRY_IID; the RTTI vtables are 0x7F76B4 (CChatEventSink, 45
// slots after IUnknown), 0x7F766C (CNetUtilEventSink, 7) and 0x7F78E4 (CDownloadEventSink, 5). The
// slot bodies are placeholders (their implementations are not modelled here); the interface
// identifiers are data defined elsewhere (retail 0x84A900, 0x84A920, 0x84A910).
#ifndef GG_WOL_EVENT_SINK_ATL_H
#define GG_WOL_EVENT_SINK_ATL_H

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlimpl.cpp>

extern const IID DAT_0084A900;

struct IChatEventSink_DAT_0084A900 : public IUnknown
{
    virtual long __stdcall vf_3() { return 0; }
    virtual long __stdcall vf_4() { return 0; }
    virtual long __stdcall vf_5() { return 0; }
    virtual long __stdcall vf_6() { return 0; }
    virtual long __stdcall vf_7() { return 0; }
    virtual long __stdcall vf_8() { return 0; }
    virtual long __stdcall vf_9() { return 0; }
    virtual long __stdcall vf_10() { return 0; }
    virtual long __stdcall vf_11() { return 0; }
    virtual long __stdcall vf_12() { return 0; }
    virtual long __stdcall vf_13() { return 0; }
    virtual long __stdcall vf_14() { return 0; }
    virtual long __stdcall vf_15() { return 0; }
    virtual long __stdcall vf_16() { return 0; }
    virtual long __stdcall vf_17() { return 0; }
    virtual long __stdcall vf_18() { return 0; }
    virtual long __stdcall vf_19() { return 0; }
    virtual long __stdcall vf_20() { return 0; }
    virtual long __stdcall vf_21() { return 0; }
    virtual long __stdcall vf_22() { return 0; }
    virtual long __stdcall vf_23() { return 0; }
    virtual long __stdcall vf_24() { return 0; }
    virtual long __stdcall vf_25() { return 0; }
    virtual long __stdcall vf_26() { return 0; }
    virtual long __stdcall vf_27() { return 0; }
    virtual long __stdcall vf_28() { return 0; }
    virtual long __stdcall vf_29() { return 0; }
    virtual long __stdcall vf_30() { return 0; }
    virtual long __stdcall vf_31() { return 0; }
    virtual long __stdcall vf_32() { return 0; }
    virtual long __stdcall vf_33() { return 0; }
    virtual long __stdcall vf_34() { return 0; }
    virtual long __stdcall vf_35() { return 0; }
    virtual long __stdcall vf_36() { return 0; }
    virtual long __stdcall vf_37() { return 0; }
    virtual long __stdcall vf_38() { return 0; }
    virtual long __stdcall vf_39() { return 0; }
    virtual long __stdcall vf_40() { return 0; }
    virtual long __stdcall vf_41() { return 0; }
    virtual long __stdcall vf_42() { return 0; }
    virtual long __stdcall vf_43() { return 0; }
    virtual long __stdcall vf_44() { return 0; }
    virtual long __stdcall vf_45() { return 0; }
    virtual long __stdcall vf_46() { return 0; }
    virtual long __stdcall vf_47() { return 0; }
};

class CChatEventSink : public CComObjectRootEx<CComMultiThreadModel>, public IChatEventSink_DAT_0084A900
{
public:
    BEGIN_COM_MAP(CChatEventSink)
        COM_INTERFACE_ENTRY_IID(DAT_0084A900, IChatEventSink_DAT_0084A900)
    END_COM_MAP()
};

extern const IID DAT_0084A920;

struct INetUtilEventSink_DAT_0084A920 : public IUnknown
{
    virtual long __stdcall vf_3() { return 0; }
    virtual long __stdcall vf_4() { return 0; }
    virtual long __stdcall vf_5() { return 0; }
    virtual long __stdcall vf_6() { return 0; }
    virtual long __stdcall vf_7() { return 0; }
    virtual long __stdcall vf_8() { return 0; }
    virtual long __stdcall vf_9() { return 0; }
};

class CNetUtilEventSink : public CComObjectRootEx<CComMultiThreadModel>, public INetUtilEventSink_DAT_0084A920
{
public:
    BEGIN_COM_MAP(CNetUtilEventSink)
        COM_INTERFACE_ENTRY_IID(DAT_0084A920, INetUtilEventSink_DAT_0084A920)
    END_COM_MAP()
};

extern const IID DAT_0084A910;

struct IDownloadEventSink_DAT_0084A910 : public IUnknown
{
    virtual long __stdcall vf_3() { return 0; }
    virtual long __stdcall vf_4() { return 0; }
    virtual long __stdcall vf_5() { return 0; }
    virtual long __stdcall vf_6() { return 0; }
    virtual long __stdcall vf_7() { return 0; }
};

class CDownloadEventSink : public CComObjectRootEx<CComMultiThreadModel>, public IDownloadEventSink_DAT_0084A910
{
public:
    BEGIN_COM_MAP(CDownloadEventSink)
        COM_INTERFACE_ENTRY_IID(DAT_0084A910, IDownloadEventSink_DAT_0084A910)
    END_COM_MAP()
};

#endif
