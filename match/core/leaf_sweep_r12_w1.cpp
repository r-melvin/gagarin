// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Round 12 small unowned leaves between 0x402000 and 0x540000. Ordered ascending by
// retail address.
#include <windows.h>
#include "../_layout/house_class.h"
#include "../_layout/player_ptr_00a83d4c.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x402C40 / 0x4031D0: walk of a queue that hangs off a global holder.
struct QNode_00402C40
{
    char Pad_00[0x18];
    int  Value;
    QNode_00402C40* FUN_004073E0();
};
GG_STATIC_ASSERT(offsetof(QNode_00402C40, Value) == 0x18);

struct Queue_00402C40
{
    int Pad_00[3];
    QNode_00402C40* FUN_004073C0();
};
GG_STATIC_ASSERT(sizeof(Queue_00402C40) == 0xC);

struct QHolder_00402C40
{
    Queue_00402C40 First;   // +0x00
    Queue_00402C40 Second;  // +0x0C
};
extern QHolder_00402C40* DAT_00815E98;

struct QCursor_004031D0
{
    QNode_00402C40* Cur;
    // FUNCTION: GAMEMD 0x4031D0
    void Begin();
};

// FUNCTION: GAMEMD 0x4031D0
// Point the cursor at the head of the second queue.
void QCursor_004031D0::Begin()
{
    Cur = DAT_00815E98->Second.FUN_004073C0();
}

// ---------------------------------------------------------------------------
// 0x417CA0: four-argument forwarder.
struct Fwd_00417CA0
{
    int FUN_006FFBE0(int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x417CA0
    int Forward(int a, int b, int c, int d);
};

// FUNCTION: GAMEMD 0x417CA0
int Fwd_00417CA0::Forward(int a, int b, int c, int d)
{
    return FUN_006FFBE0(a, b, c, d);
}

// ---------------------------------------------------------------------------
// 0x422C70: refuse when a +0x184 pointer is set, otherwise forward to the base routine.
struct Base_00422C70
{
    bool FUN_005F4B10(int a, int b, int c);
};
struct Obj_00422C70 : Base_00422C70
{
    char Pad_01[0x184 - 1];
    void* Blocker;  // +0x184
    // FUNCTION: GAMEMD 0x422C70
    bool Try(int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(Obj_00422C70, Blocker) == 0x184);

// FUNCTION: GAMEMD 0x422C70
bool Obj_00422C70::Try(int a, int b, int c)
{
    if (Blocker)
        return false;
    return FUN_005F4B10(a, b, c);
}

// ---------------------------------------------------------------------------
// 0x43A5D0: fold the object's state and an elapsed-frame delta into a CRC view.
struct Crc_0043A5D0
{
    void FUN_004A1D50(int v);
};
struct CrcOwner_0043A5D0
{
    char Pad_00[0x30];
    int  Stamp;  // +0x30
    void FUN_00410410(Crc_0043A5D0* crc);
    // FUNCTION: GAMEMD 0x43A5D0
    void Crc(Crc_0043A5D0* crc);
};
extern int DAT_00A8ED84;

// FUNCTION: GAMEMD 0x43A5D0
void CrcOwner_0043A5D0::Crc(Crc_0043A5D0* crc)
{
    FUN_00410410(crc);
    crc->FUN_004A1D50(DAT_00A8ED84 - Stamp);
}

// ---------------------------------------------------------------------------
// 0x453370: reset a field when the house flag is set and the global is clear.
struct Owner_00453370
{
    char Pad_00[0x16BE];
    char Flag;  // +0x16BE
};
struct Obj_00453370
{
    char Pad_00[0x520];
    Owner_00453370* Owner;  // +0x520
    char Pad_524[0x618 - 0x524];
    int  Field618;          // +0x618
    // FUNCTION: GAMEMD 0x453370
    void ClearIfOwnerFlag();
};
GG_STATIC_ASSERT(offsetof(Obj_00453370, Field618) == 0x618);
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x453370
void Obj_00453370::ClearIfOwnerFlag()
{
    if (!DAT_00A8E7AC && Owner->Flag)
        Field618 = 0;
}

// ---------------------------------------------------------------------------
// 0x4790B0: store a clamped mode value.
extern char DAT_0089E3A0;
extern int  DAT_0081C1D0;

// FUNCTION: GAMEMD 0x4790B0
void __fastcall FUN_004790B0(int mode)
{
    if (DAT_0089E3A0 == 1)
    {
        DAT_0081C1D0 = -2;
        return;
    }
    if (mode >= 0)
        mode = 2;
    DAT_0081C1D0 = mode;
}

// ---------------------------------------------------------------------------
// 0x47A6B0: open the device named by DAT_0081C5AC delete-on-close.
extern char DAT_0081C5AC[];

// FUNCTION: GAMEMD 0x47A6B0
void __stdcall FUN_0047A6B0(int unused)
{
    CreateFileA(DAT_0081C5AC, 0, 0, 0, 0, FILE_FLAG_DELETE_ON_CLOSE, 0);
}

// ---------------------------------------------------------------------------
// 0x47B130: close the search handle if open.
extern HANDLE DAT_0081C8EC;

// FUNCTION: GAMEMD 0x47B130
void FUN_0047B130()
{
    if (DAT_0081C8EC != INVALID_HANDLE_VALUE)
    {
        FindClose(DAT_0081C8EC);
        DAT_0081C8EC = INVALID_HANDLE_VALUE;
    }
}

// ---------------------------------------------------------------------------
// 0x488480: byte at +4 of the list entry, or 0.
struct Entry_00488480
{
    char Pad_00[4];
    char Flag;  // +4
};
struct ListBase_00488480
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void Changed();     // slot 18, +0x48
    Entry_00488480* FUN_00557AC0(int index);
};
struct List_00488480 : ListBase_00488480
{
    // FUNCTION: GAMEMD 0x488450
    void SetFlag(int index, char value);
    // FUNCTION: GAMEMD 0x488480
    char FlagAt(int index);
};

// FUNCTION: GAMEMD 0x488450
void List_00488480::SetFlag(int index, char value)
{
    Entry_00488480* e = FUN_00557AC0(index);
    if (e && e->Flag != value)
    {
        e->Flag = value;
        Changed();
    }
}

// FUNCTION: GAMEMD 0x488480
char List_00488480::FlagAt(int index)
{
    Entry_00488480* e = FUN_00557AC0(index);
    if (e)
        return e->Flag;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x48C600: elapsed time accumulated across a pause.
struct Timer_0088733C
{
    int FUN_006C8C40();
};
extern int DAT_00887338;
extern Timer_0088733C DAT_0088733C;
extern int DAT_00887340;

// FUNCTION: GAMEMD 0x48C600
int FUN_0048C600()
{
    int total = DAT_00887340;
    if (DAT_00887338 != -1)
        total += DAT_0088733C.FUN_006C8C40() - DAT_00887338;
    return total;
}

// ---------------------------------------------------------------------------
// 0x5278F0: forward two mapped keys to the reader.
struct Reader_005278F0
{
    int FUN_005276D0(int a, int b, int c);
    // FUNCTION: GAMEMD 0x5278F0
    int Read(int a, int b, int c);
};
int __fastcall FUN_007B5440(int v);

// FUNCTION: GAMEMD 0x5278F0
int Reader_005278F0::Read(int a, int b, int c)
{
    return FUN_005276D0(FUN_007B5440(a), FUN_007B5440(b), c);
}

// ---------------------------------------------------------------------------
// 0x53D550: delete and clear every object in a global table.
struct Deletable_0053D550
{
    virtual ~Deletable_0053D550();
};
extern Deletable_0053D550* DAT_00A9FFC8[80];

// FUNCTION: GAMEMD 0x53D550
void FUN_0053D550()
{
    for (int i = 0; i < 80; ++i)
    {
        delete DAT_00A9FFC8[i];
        DAT_00A9FFC8[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x53EC40 / 0x53EC70: key state table.
extern int   DAT_00AA0444;
extern short DAT_00AA0168[256];

// FUNCTION: GAMEMD 0x53EC40
void __fastcall FUN_0053EC40(int vk, bool pressed)
{
    if (DAT_00AA0444)
        DAT_00AA0168[vk & 0xFF] = (short)(pressed ? 0 : 0x8000);
}

// FUNCTION: GAMEMD 0x53EC70
short __fastcall FUN_0053EC70(int vk)
{
    if (!DAT_00AA0444)
        return GetKeyState(vk);
    return DAT_00AA0168[vk & 0xFF];
}

// ===========================================================================
// 0x4016B0: copy a descriptor's fields into one 0x24-byte table row.
struct Row_004016B0
{
    char Pad_00[0x18];
    int  Value;     // +0x18
    int  Flags;     // +0x1C
    char Pad_20[4];
};
GG_STATIC_ASSERT(sizeof(Row_004016B0) == 0x24);
struct RowTable_004016B0
{
    Row_004016B0* Rows;
};
struct RowSrc_004016B0
{
    char Pad_00[8];
    int  Value;     // +0x08
    int  ModeA;     // +0x0C
    int  ModeB;     // +0x10
};

// FUNCTION: GAMEMD 0x4016B0
// Fill row `index` from the descriptor: the value, then a flag per mode equal to 2.
void __fastcall FUN_004016B0(RowTable_004016B0* table, int index, RowSrc_004016B0* src)
{
    Row_004016B0* row = &table->Rows[index];
    row->Value = src->Value;
    row->Flags = 0;
    if (src->ModeA == 2)
        row->Flags = 1;
    if (src->ModeB == 2)
        row->Flags |= 4;
}

// ---------------------------------------------------------------------------
// 0x41B5E0: a flag that holds for most modes.
struct Obj_0041B5E0
{
    char Pad_00[0xAC];
    int  Mode;      // +0xAC
    char Pad_B0[0x6D2 - 0xB0];
    char Flag6D2;   // +0x6D2
    char Pad_6D3;
    char Flag6D4;   // +0x6D4
    // FUNCTION: GAMEMD 0x41B5E0
    bool Test();
};
GG_STATIC_ASSERT(offsetof(Obj_0041B5E0, Flag6D4) == 0x6D4);

// FUNCTION: GAMEMD 0x41B5E0
bool Obj_0041B5E0::Test()
{
    if (Mode == 6 || Mode == 0x15)
        return false;
    if (Flag6D2 && Mode != 0x1E)
        return false;
    bool r = Flag6D4 != 0;
    return r;
}

// ---------------------------------------------------------------------------
// 0x41B610 / 0x41B660: CRC contribution and reference detach.
struct CrcSink_0041B610
{
    void FUN_004A1CA0(bool v);
    void FUN_004A1D50(int v);
};
struct CrcBase_0041B610
{
    void FUN_004DBAD0(CrcSink_0041B610* crc);
    void FUN_004D9960(void* target, bool all);
};
struct Obj_0041B610 : CrcBase_0041B610
{
    char  Pad_01[0x6C4 - 1];
    void* Ref6C4;           // +0x6C4
    char  Pad_6C8;
    bool  Flag6C9;          // +0x6C9
    char  Pad_6CA[2];
    void* Ref6CC;           // +0x6CC
    bool  Flag6D0;          // +0x6D0
    bool  Flag6D1;          // +0x6D1
    char  Pad_6D2;
    signed char Val6D3;     // +0x6D3
    // FUNCTION: GAMEMD 0x41B610
    void Crc(CrcSink_0041B610* crc);
    // FUNCTION: GAMEMD 0x41B660
    void Detach(void* target, bool all);
};
GG_STATIC_ASSERT(offsetof(Obj_0041B610, Ref6C4) == 0x6C4);
GG_STATIC_ASSERT(offsetof(Obj_0041B610, Ref6CC) == 0x6CC);
GG_STATIC_ASSERT(offsetof(Obj_0041B610, Val6D3) == 0x6D3);

// FUNCTION: GAMEMD 0x41B610
void Obj_0041B610::Crc(CrcSink_0041B610* crc)
{
    FUN_004DBAD0(crc);
    crc->FUN_004A1CA0(Flag6C9);
    crc->FUN_004A1CA0(Flag6D0);
    crc->FUN_004A1CA0(Flag6D1);
    crc->FUN_004A1D50(Val6D3);
}

// FUNCTION: GAMEMD 0x41B660
void Obj_0041B610::Detach(void* target, bool all)
{
    FUN_004D9960(target, all);
    if (Ref6CC == target)
        Ref6CC = 0;
    if (Ref6C4 == target)
        Ref6C4 = 0;
}

// ---------------------------------------------------------------------------
// 0x42E0B0 / 0x42E110: a seven-value record with a double-valued rate limiter.
struct Limiter_0042E0B0
{
    int    F0, F4, F8, FC, F10, F14, F18;
    int    Pad_1C;
    double Last;        // +0x20
    double Prev;        // +0x28
    bool   Armed;       // +0x30
    char   Pad_31[3];
    void FUN_0042E1C0();
    // FUNCTION: GAMEMD 0x42E110
    bool Update(double now);
};
GG_STATIC_ASSERT(offsetof(Limiter_0042E0B0, Prev) == 0x28);
GG_STATIC_ASSERT(offsetof(Limiter_0042E0B0, Armed) == 0x30);

// FUNCTION: GAMEMD 0x42E110
bool Limiter_0042E0B0::Update(double now)
{
    Last = now;
    if (Armed && now - Prev < 0.1)
        return false;
    FUN_0042E1C0();
    return true;
}

// ---------------------------------------------------------------------------
// 0x43C2A0: release each of eight owned objects through their release slot.
struct Owned_0043C2A0
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void Release();     // slot 62, +0xF8
};
struct Holder_0043C2A0
{
    char Pad_00[0x5C8];
    Owned_0043C2A0* Items[8];   // +0x5C8
    // FUNCTION: GAMEMD 0x43C2A0
    void ReleaseAll();
};
GG_STATIC_ASSERT(offsetof(Holder_0043C2A0, Items) == 0x5C8);

// FUNCTION: GAMEMD 0x43C2A0
void Holder_0043C2A0::ReleaseAll()
{
    for (int i = 0; i < 8; ++i)
    {
        if (Items[i])
        {
            Items[i]->Release();
            Items[i] = 0;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x45E8B0: store three values in the indexed 12-byte slot.
struct Slot_0045E8B0
{
    int A;
    int B;
    int C;
};
struct Slots_0045E8B0
{
    char Pad_00[0xF04];
    Slot_0045E8B0 Items[1];   // +0xF04
    // FUNCTION: GAMEMD 0x45E8B0
    void Set(int index, int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(Slots_0045E8B0, Items) == 0xF04);

// FUNCTION: GAMEMD 0x45E8B0
void Slots_0045E8B0::Set(int index, int a, int b, int c)
{
    Items[index].A = a;
    Items[index].B = b;
    Items[index].C = c;
}

// ---------------------------------------------------------------------------
// 0x46D430: clear the flag byte of every slot whose object reports true.
struct Probe_0046D430
{
    bool FUN_005E93F0();
};
extern Probe_0046D430* DAT_00A8DA90[8];
extern char DAT_0089E000[8];

// FUNCTION: GAMEMD 0x46D430
void FUN_0046D430()
{
    for (int i = 0; i < 8; ++i)
    {
        if (DAT_00A8DA90[i]->FUN_005E93F0())
            DAT_0089E000[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x474870: scale by 100/256 and forward.
struct Fwd_00474870
{
    int FUN_005275C0(int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x474870
    int Percent(int a, int b, int c);
};

// FUNCTION: GAMEMD 0x474870
int Fwd_00474870::Percent(int a, int b, int c)
{
    return FUN_005275C0(a, b, c * 100 / 256, 0);
}

// ---------------------------------------------------------------------------
// 0x476F70: forward with the text of a looked-up entry, or an empty default.
extern char DAT_00817474[];
struct Text_00476F70
{
    char Pad_00[0x24];
    char Text[1];   // +0x24
};
struct Lookup_00476F70
{
    Text_00476F70* FUN_006E7330();
};
struct Sink_00476F70
{
    void FUN_00528660(int a, int b, const char* text);
    // FUNCTION: GAMEMD 0x476F70
    void Forward(int a, int b, Lookup_00476F70* l);
};

// FUNCTION: GAMEMD 0x476F70
void Sink_00476F70::Forward(int a, int b, Lookup_00476F70* l)
{
    Text_00476F70* t = l->FUN_006E7330();
    if (t)
        FUN_00528660(a, b, t->Text);
    else
        FUN_00528660(a, b, DAT_00817474);
}

// ---------------------------------------------------------------------------
// 0x48DF30: index of a name in the global name table, or -1.
extern char** DAT_00ABF394;
extern int    DAT_00ABF3A0;
int __cdecl FUN_007C8D20(const char* a, const char* b);

// FUNCTION: GAMEMD 0x48DF30
int __fastcall FUN_0048DF30(const char* name)
{
    if (name && FUN_007C8D20(DAT_00817474, name))
    {
        for (int i = 0; i < DAT_00ABF3A0; ++i)
        {
            if (!FUN_007C8D20(name, DAT_00ABF394[i]))
                return i;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x49B720: delete every owned item, then the array itself.
struct Pool_0049B720
{
    char Pad_00[0x3C];
    char** Items;   // +0x3C
    int    Count;   // +0x40
    // FUNCTION: GAMEMD 0x49B720
    void FreeAll();
};
GG_STATIC_ASSERT(offsetof(Pool_0049B720, Count) == 0x40);

// FUNCTION: GAMEMD 0x49B720
void Pool_0049B720::FreeAll()
{
    if (Items)
    {
        for (int i = 0; i < Count; ++i)
        {
            if (Items[i])
                delete Items[i];
        }
        delete Items;
    }
}

// ---------------------------------------------------------------------------
// 0x44EF80: resolve an id through the object's slot 34, then ask the result.
struct Resolved_0044EF80
{
    int FUN_0045EE70();
};
struct Target_0044EF80
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual Resolved_0044EF80* Resolve(int a, int b);   // slot 34, +0x88
};
struct Owner_0044EF80
{
    char Pad_00[0x21C];
    int  Context;   // +0x21C
    // FUNCTION: GAMEMD 0x44EF80
    int Lookup(Target_0044EF80* t, int a);
};
GG_STATIC_ASSERT(offsetof(Owner_0044EF80, Context) == 0x21C);

// FUNCTION: GAMEMD 0x44EF80
// PARTIAL: 80% -- the argument loads before the slot call are scheduled differently from retail.
int Owner_0044EF80::Lookup(Target_0044EF80* t, int a)
{
    if (t)
    {
        int ctx = Context;
        Resolved_0044EF80* r = t->Resolve(a, ctx);
        return r->FUN_0045EE70();
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x454D70: poke every linked node whose type is one of three values.
struct Node_00454D70
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual int Type();         // slot 11, +0x2C
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159();
    virtual void v160();
    virtual void v161();
    virtual void v162();
    virtual void v163();
    virtual void v164();
    virtual void v165();
    virtual void v166();
    virtual void v167();
    virtual void v168();
    virtual void v169();
    virtual void v170();
    virtual void v171();
    virtual void v172();
    virtual void v173();
    virtual void v174();
    virtual void v175();
    virtual void v176();
    virtual void v177();
    virtual void v178();
    virtual void v179();
    virtual void v180();
    virtual void v181();
    virtual void v182();
    virtual void v183();
    virtual void v184();
    virtual void v185();
    virtual void v186();
    virtual void v187();
    virtual void v188();
    virtual void v189();
    virtual void v190();
    virtual void v191();
    virtual void v192();
    virtual void v193();
    virtual void v194();
    virtual void v195();
    virtual void v196();
    virtual void v197();
    virtual void v198();
    virtual void v199();
    virtual void v200();
    virtual void v201();
    virtual void v202();
    virtual void v203();
    virtual void v204();
    virtual void v205();
    virtual void v206();
    virtual void v207();
    virtual void v208();
    virtual void v209();
    virtual void v210();
    virtual void v211();
    virtual void v212();
    virtual void v213();
    virtual void v214();
    virtual void v215();
    virtual void v216();
    virtual void v217();
    virtual void v218();
    virtual void v219();
    virtual void v220();
    virtual void v221();
    virtual void v222();
    virtual void v223();
    virtual void v224();
    virtual void v225();
    virtual void v226();
    virtual void v227();
    virtual void v228();
    virtual void v229();
    virtual void v230();
    virtual void v231();
    virtual void v232();
    virtual void v233();
    virtual void v234();
    virtual void v235();
    virtual void v236();
    virtual void v237();
    virtual void v238();
    virtual void v239();
    virtual void v240();
    virtual void v241();
    virtual void v242();
    virtual void v243();
    virtual void v244();
    virtual void v245();
    virtual void v246();
    virtual void v247();
    virtual void v248();
    virtual void v249();
    virtual void v250();
    virtual void v251();
    virtual void v252();
    virtual void v253();
    virtual void v254();
    virtual void v255();
    virtual void v256();
    virtual void v257();
    virtual void v258();
    virtual void v259();
    virtual void v260();
    virtual void v261();
    virtual void v262();
    virtual void v263();
    virtual void Poke();        // slot 264, +0x420
    char Pad_04[0x30 - 4];
    Node_00454D70* Next;        // +0x30
};
GG_STATIC_ASSERT(offsetof(Node_00454D70, Next) == 0x30);
struct Chain_00454D70
{
    char Pad_00[0xE4];
    Node_00454D70* Head;        // +0xE4
    // FUNCTION: GAMEMD 0x454D70
    void PokeAll();
};
GG_STATIC_ASSERT(offsetof(Chain_00454D70, Head) == 0xE4);

// FUNCTION: GAMEMD 0x454D70
void Chain_00454D70::PokeAll()
{
    for (Node_00454D70* n = Head; n; n = n->Next)
    {
        int t = n->Type();
        if (t == 1 || t == 0xF || t == 2)
            n->Poke();
    }
}

// ---------------------------------------------------------------------------
// 0x486800: bit-mask test.
struct Mask_00486800
{
    char  Pad_00[0x78];
    int   Mask;         // +0x78
    short Counts[1];    // +0x7C
    // FUNCTION: GAMEMD 0x486800
    bool Allowed(int bit);
};
GG_STATIC_ASSERT(offsetof(Mask_00486800, Counts) == 0x7C);

// FUNCTION: GAMEMD 0x486800
bool Mask_00486800::Allowed(int bit)
{
    if (DAT_00A83D4C && (Mask & (1 << bit)))
    {
        int cur = DAT_00A83D4C->ArrayIndex;
        if (bit == cur)
            return true;
        if (Counts[cur] <= 0)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x49D070: a slot table's checked fetch.
struct Table_0049B610
{
    char  Used;         // +0x00
    char  Pad_01[0x13];
    int   F14;
    int   F18;
    char  F1C;
    char  Pad_1D[0x13];
    int   F30;
    int   F34;
    int   F38;
    void** Items;       // +0x3C
    int   Count;        // +0x40
    int   F44;
    int   F48, F4C, F50, F54, F58, F5C, F60, F64, F68;
    char  Enabled;      // +0x6C
    // FUNCTION: GAMEMD 0x49D070
    bool Fetch(void** out, int index);
};
GG_STATIC_ASSERT(offsetof(Table_0049B610, Count) == 0x40);
GG_STATIC_ASSERT(offsetof(Table_0049B610, Enabled) == 0x6C);

// FUNCTION: GAMEMD 0x49D070
bool Table_0049B610::Fetch(void** out, int index)
{
    bool ok = false;
    *out = 0;
    if (index == -1)
        index = F38;
    if (index < 0 || index >= Count)
        index = -1;
    if (Enabled)
    {
        if (index != -1)
            *out = Items[index];
        if (*out)
            ok = true;
    }
    return ok;
}

// ---------------------------------------------------------------------------
// 0x41A570 / 0x41C1E0: copy out the value held by the +0x3A0 sub-object.
struct Val_0041A570
{
    int V;
};
struct Slot_0041A570
{
    Val_0041A570* FUN_004C93D0(Val_0041A570* out);
};
struct Obj_0041A570
{
    char Pad_00[0x3A0];
    Slot_0041A570 Slot;     // +0x3A0
    // FUNCTION: GAMEMD 0x41A570
    Val_0041A570 Get_0041A570();
};
GG_STATIC_ASSERT(offsetof(Obj_0041A570, Slot) == 0x3A0);

// FUNCTION: GAMEMD 0x41A570
Val_0041A570 Obj_0041A570::Get_0041A570()
{
    Val_0041A570 tmp;
    return *Slot.FUN_004C93D0(&tmp);
}

struct Val_0041C1E0
{
    int V;
};
struct Slot_0041C1E0
{
    Val_0041C1E0* FUN_004C93D0(Val_0041C1E0* out);
};
struct Obj_0041C1E0
{
    char Pad_00[0x3A0];
    Slot_0041C1E0 Slot;     // +0x3A0
    // FUNCTION: GAMEMD 0x41C1E0
    Val_0041C1E0 Get_0041C1E0();
};
GG_STATIC_ASSERT(offsetof(Obj_0041C1E0, Slot) == 0x3A0);

// FUNCTION: GAMEMD 0x41C1E0
Val_0041C1E0 Obj_0041C1E0::Get_0041C1E0()
{
    Val_0041C1E0 tmp;
    return *Slot.FUN_004C93D0(&tmp);
}

// ---------------------------------------------------------------------------
// 0x430620: clear the 256-byte name at +0x0E and copy in up to 127 characters.
char* __cdecl FUN_007CA422(char* dst, const char* src, int n);
struct Named_00430620
{
    char Pad_00[0x0E];
    char Name[0x100];   // +0x0E
    // FUNCTION: GAMEMD 0x430620
    void SetName(const char* s);
};
GG_STATIC_ASSERT(offsetof(Named_00430620, Name) == 0x0E);

// FUNCTION: GAMEMD 0x430620
void Named_00430620::SetName(const char* s)
{
    for (int i = 0; i < 0x40; ++i)
        ((int*)Name)[i] = 0;
    if (s)
        FUN_007CA422(Name, s, 0x7F);
}

// ---------------------------------------------------------------------------
// 0x487C10: per-index flag, unless a type-6 node is linked while the global is set.
struct Row_00487C10
{
    char Flag;      // +0x00
    char Pad_01[0x23];
};
GG_STATIC_ASSERT(sizeof(Row_00487C10) == 0x24);
extern char DAT_00A8E9A0;
extern Row_00487C10 DAT_0089EA60[];
struct Owner_00487C10
{
    char Pad_00[0xE4];
    Node_00454D70* Head;    // +0xE4
    char Pad_E8[4];
    int  Index;             // +0xEC
    char Pad_F0[0x11C - 0xF0];
    char Blocked;           // +0x11C
    // FUNCTION: GAMEMD 0x487C10
    char RowFlag();
};
GG_STATIC_ASSERT(offsetof(Owner_00487C10, Blocked) == 0x11C);

// FUNCTION: GAMEMD 0x487C10
char Owner_00487C10::RowFlag()
{
    if (Blocked)
        return 0;
    if (DAT_00A8E9A0)
    {
        Node_00454D70* n;
        for (n = Head; n; n = n->Next)
        {
            if (n->Type() == 6)
                break;
        }
        if (n)
            return 0;
    }
    return DAT_0089EA60[Index].Flag;
}

// ---------------------------------------------------------------------------
// 0x42CEB0: does list `index` already hold the ordered pair (low, high)?
struct PairList_0042CEB0
{
    int  Pad_00;
    unsigned* Items;    // +0x04
    int  Pad_08[2];
    int  Count;         // +0x10
    int  Pad_14;
};
GG_STATIC_ASSERT(sizeof(PairList_0042CEB0) == 0x18);
struct Pairs_0042CEB0
{
    char Pad_00[0x74];
    PairList_0042CEB0 Lists[1];     // +0x74
    // FUNCTION: GAMEMD 0x42CEB0
    bool Has(unsigned short a, unsigned short b, int index);
};
GG_STATIC_ASSERT(offsetof(Pairs_0042CEB0, Lists) == 0x74);

// FUNCTION: GAMEMD 0x42CEB0
bool Pairs_0042CEB0::Has(unsigned short a, unsigned short b, int index)
{
    if (b < a)
    {
        unsigned short t = a;
        a = b;
        b = t;
    }
    unsigned key = (a << 16) | b;
    PairList_0042CEB0* l = &Lists[index];
    for (int i = l->Count - 1; i >= 0; --i)
    {
        if (l->Items[i] == key)
            return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x88733C
Timer_0088733C DAT_0088733C;
// GLOBAL: GAMEMD 0x887340
int DAT_00887340;
// GLOBAL: GAMEMD 0x89E000
char DAT_0089E000[8];
// GLOBAL: GAMEMD 0x89E3A0
char DAT_0089E3A0;
// GLOBAL: GAMEMD 0xA8DA90
Probe_0046D430* DAT_00A8DA90[8];
// GLOBAL: GAMEMD 0xA9FFC8
Deletable_0053D550* DAT_00A9FFC8[80];
// GLOBAL: GAMEMD 0xAA0168
short DAT_00AA0168[256];
// GLOBAL: GAMEMD 0xAA0444
int DAT_00AA0444;
// GLOBAL: GAMEMD 0xABF3A0
int DAT_00ABF3A0;
// END defined globals
