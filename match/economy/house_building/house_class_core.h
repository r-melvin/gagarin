// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   HouseClusterView: the house-cluster-scoped ABI view of HouseClass (retail RTTI
//   .?AVHouseClass@@, TD 0x824500; tables and bases in house_views.h). It is NOT the canonical
//   HouseClass: root integrates the canonical base later. Layout read from the retail gamemd.exe
//   v1.001: the constructor 0x4F54A0 (every member store, the seven vptr stores at
//   0x4F5DCC..0x4F5DFB), the allocation sites 0x500A13 / 0x500AFC / 0x59A17B / 0x687F9B
//   (`PUSH 0x160B8; CALL 0x7C8E17`, all agreeing), Size 0x504730 (`MOV EAX, 0x160B8`) and the bodies
//   of this cluster. Member names are YRpp-cross-checked and kept only where a ctor store
//   or a body in this cluster touches the offset; the rest are positional.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_CLASS_CORE_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_CLASS_CORE_H

class WaypointPathClass;
class WaypointClass;
#include <string.h>
#include "house_views.h"
#include "../../_layout/cell.h"
#include "house_building_views.h"
#include "house_techno_view.h"

// ---- helper views (read-only dependencies bound by address) ------------------------------------

// The CRC accumulator the CRC slot (0x502D60) feeds. Each entry takes one value.
class HouseCrcView
{
public:
    // FUNCTION: GAMEMD 0x4A1CA0 (read-only here)
    void AddBool(bool value);
    // FUNCTION: GAMEMD 0x4A1D50 (read-only here)
    void AddInt(int value);
    // FUNCTION: GAMEMD 0x4A1D90 (read-only here) - a double, passed as its two halves
    void AddDouble(double value);
};

// GLOBAL: GAMEMD 0xA8ED84 - the current frame counter.
extern int HouseFrame;

// CDTimerClass-shaped (0xC): StartTime (-1 when stopped), a clock slot, Delay.
// Not merged: cluster timers differ in constructors and inline bodies (see house_building_views.h).
struct HouseTimer
{
    int StartTime;   // +0x00
    int unknown_04;  // +0x04
    int Delay;       // +0x08

    // Started now with no delay (a stopped timer is StartTime == -1).
    HouseTimer() : StartTime(HouseFrame), Delay(0) {}
    HouseTimer(int delay) : StartTime(HouseFrame), Delay(delay) {}
    // The inline remaining-time computation used by the CRC slot.
    int GetTimeLeft() const
    {
        int start = StartTime;
        int left = Delay;
        if (start != -1) {
            int elapsed = HouseFrame - start;
            if (elapsed < left)
                left -= elapsed;
            else
                left = 0;
        }
        return left;
    }
};
GG_STATIC_ASSERT(sizeof(HouseTimer) == 0xC);

// Three-byte colour (no padding).
struct HouseRgb
{
    unsigned char R, G, B;

    HouseRgb(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b) {}
};
GG_STATIC_ASSERT(sizeof(HouseRgb) == 3);

// StorageClass-shaped (0x10): the tiberium stores. Entries read-only here.
struct HouseStorage
{
    // FUNCTION: GAMEMD 0x6C95E0 (read-only here)
    HouseStorage();
    // FUNCTION: GAMEMD 0x6C9600 (read-only here)
    int GetTotalValue() const;
    // FUNCTION: GAMEMD 0x6C9650 (read-only here)
    float GetTotalAmount() const;
    unsigned char unknown_00[0x10];
};
GG_STATIC_ASSERT(sizeof(HouseStorage) == 0x10);

// UnitTrackerClass-shaped (0x808). Ten of them run 0x328..0x5378 (ctor LEA sites).
struct HouseUnitTracker
{
    // FUNCTION: GAMEMD 0x748FD0 (read-only here)
    HouseUnitTracker();
    // FUNCTION: GAMEMD 0x749060 (read-only here) - sizes the tracker for a type count
    void Init(int typeCount);
    unsigned char unknown_00[0x808];
};
GG_STATIC_ASSERT(sizeof(HouseUnitTracker) == 0x808);

// CounterClass-shaped (0x14). Twelve of them run 0x5500..0x55F0.
struct HouseCounter
{
    // FUNCTION: GAMEMD 0x49F9B0 (read-only here)
    HouseCounter();
    // FUNCTION: GAMEMD 0x49FAE0 (read-only here) - the count held for a type index
    int GetCount(int typeIndex);
    // FUNCTION: GAMEMD 0x49FB60 (read-only here) - the sum over all types
    int GetTotal();
    // FUNCTION: GAMEMD 0x49FB70 (read-only here) - writes the counter to a stream
    void Save(IStream* stream);
    // FUNCTION: GAMEMD 0x49FBE0 (read-only here) - reads the counter from a stream
    void Load(IStream* stream);
    unsigned char unknown_00[0x14];
};
GG_STATIC_ASSERT(sizeof(HouseCounter) == 0x14);

// DropshipStruct-shaped (0x2C). Three of them run 0x5670..0x56F4.
struct HouseDropship
{
    // FUNCTION: GAMEMD 0x4B69B0 (read-only here)
    HouseDropship();
    // FUNCTION: GAMEMD 0x4B6BB0 (read-only here) - registers the dropship's pointer fields after a load
    void Swizzle();
    unsigned char unknown_00[0x2C];
};
GG_STATIC_ASSERT(sizeof(HouseDropship) == 0x2C);

// BaseClass-shaped (0x78), with a vptr: slot 0 loads from a stream, slot 1 saves to one (0x503040 /
// 0x504080 call [vptr] / [vptr+4] with `this` and the stream on the stack); slot 2 (thiscall) feeds the CRC.
struct HouseBase
{
    // FUNCTION: GAMEMD 0x42E6F0 (read-only here)
    HouseBase();
    virtual void __stdcall LoadFromStream(IStream* stream);    // 0
    virtual void __stdcall SaveToStream(IStream* stream);      // 1
    virtual void ComputeCrc(HouseCrcView* crc);     // 2 (+0x8: used by the CRC slot)
    unsigned char unknown_04[0x74];
};
GG_STATIC_ASSERT(sizeof(HouseBase) == 0x78);


// CellClass-shaped (read-only here): only slot 18 is called.
class HouseCellView
{
public:
    virtual void vf_0(); virtual void vf_1(); virtual void vf_2(); virtual void vf_3();
    virtual void vf_4(); virtual void vf_5(); virtual void vf_6(); virtual void vf_7();
    virtual void vf_8(); virtual void vf_9(); virtual void vf_10(); virtual void vf_11();
    virtual void vf_12(); virtual void vf_13(); virtual void vf_14(); virtual void vf_15();
    virtual void vf_16(); virtual void vf_17();
    virtual HBCoord* GetCoords(HBCoord* result);   // 18  +0x48 (hidden-return coordinate)

    // FUNCTION: GAMEMD 0x47C3D0 (read-only here) - the techno nearest to a point in the cell
    struct HouseTechnoView* FindTechnoNearestTo(HBCoord* point, bool flag, struct HouseTechnoView* exclude);
};

// MapClass-shaped (read-only here): cell lookup by map cell.
class HouseMapView
{
public:
    // FUNCTION: GAMEMD 0x5657A0 (read-only here)
    HouseCellView* GetCellAt(const CellStruct& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 - the map.
extern HouseMapView HouseMap;
// GLOBAL: GAMEMD 0xA8EF98 - the "no cell" value (-1, -1)... read as two shorts.
extern HBCell HouseEmptyCell;
// GLOBAL: GAMEMD 0xA8EFF8 - the coordinate used when a base cell is unset.
extern HBCoord HouseEmptyCoord;

// The coordinate of a cell: the default coordinate while the cell is unset, else the map's lookup.
// Retail expands it inline per use.
inline HBCoord HouseCellCoord(CellStruct cell)
{
    if (cell.X == HouseEmptyCell.X && cell.Y == HouseEmptyCell.Y)
        return HouseEmptyCoord;
    HBCoord coord;
    return *HouseMap.GetCellAt(cell)->GetCoords(&coord);
}

// RulesClass-shaped: only the members the house entries read. Each name below is the rules INI key the
// member is read from (the reader 0x66D530 / 0x672AE0 / 0x674240 pushes the key string, then stores to the
// offset); members without an attested key keep positional names.
struct HouseRulesView
{
    unsigned char unknown_00[0x8B0];
    struct HouseTypeIndexView** BuildConst;      // +0x8B0 Items of the type list at +0x8AC (key 0x83D4A0, 0x672B23)
    unsigned char unknown_8B4[0x8E8 - 0x8B4];
    struct HouseTypeIndexView** BuildRefinery;   // +0x8E8 Items of the type list at +0x8E4 (key 0x83D484, 0x672CFA)
    unsigned char unknown_8EC[0xB24 - 0x8EC];
    struct HouseTypeIndexView** BaseUnit;        // +0xB24 Items of the type list at +0xB20 (key 0x83C764, 0x66F7DA)
    unsigned char unknown_B28[0xB3C - 0xB28];
    struct                                      // +0xB3C type list (DynamicVectorClass shape), key 0x83C754 (0x66F8DD)
    {
        void*                  _vtable;
        struct HouseTypeIndexView** Items;       // +0xB40
        int                    Capacity;
        int                    unknown_0C;
        int                    Count;            // +0xB4C
        int                    CapacityIncrement;
    } HarvesterUnit;
    unsigned char unknown_B54[0xFA8 - 0xB54];
    void*         unknown_FA8;   // +0xFA8 the warhead passed by 0x501496
    unsigned char unknown_FAC[0x10A8 - 0xFAC];
    double        AttackDelay;   // +0x10A8 key 0x83D350 (FSTP at 0x673998); scales the attack timer delay (ctor 0x4F6368)
    unsigned char unknown_10B0[0x115C - 0x10B0];
    int*          TeamDelays;    // +0x115C Items of the list at +0x1158 (key 0x83C5C8, 0x66FD8B)
    unsigned char unknown_1160[0x143C - 0x1160];
    int           unknown_143C;  // +0x143C
    unsigned char unknown_1440[0x14C0 - 0x1440];
    double        unknown_14C0;  // +0x14C0
    unsigned char unknown_14C8[0x16A8 - 0x14C8];
    double        unknown_16A8;  // +0x16A8
    double        DamageDelay;   // +0x16B0 key 0x83BE20 (FSTP at 0x670D4F); scaled by 900.0 for DamageDelayTimer (ctor 0x4F5C9F)
};
GG_STATIC_ASSERT(offsetof(HouseRulesView, BuildConst) == 0x8B0);
GG_STATIC_ASSERT(offsetof(HouseRulesView, BuildRefinery) == 0x8E8);
GG_STATIC_ASSERT(offsetof(HouseRulesView, BaseUnit) == 0xB24);
GG_STATIC_ASSERT(offsetof(HouseRulesView, HarvesterUnit) == 0xB3C);
GG_STATIC_ASSERT(offsetof(HouseRulesView, unknown_FA8) == 0xFA8);
GG_STATIC_ASSERT(offsetof(HouseRulesView, AttackDelay) == 0x10A8);
GG_STATIC_ASSERT(offsetof(HouseRulesView, TeamDelays) == 0x115C);
GG_STATIC_ASSERT(offsetof(HouseRulesView, unknown_143C) == 0x143C);
GG_STATIC_ASSERT(offsetof(HouseRulesView, unknown_14C0) == 0x14C0);
GG_STATIC_ASSERT(offsetof(HouseRulesView, unknown_16A8) == 0x16A8);
GG_STATIC_ASSERT(offsetof(HouseRulesView, DamageDelay) == 0x16B0);
// GLOBAL: GAMEMD 0x8871E0 - the rules object pointer.
extern HouseRulesView* HouseRules;

// IEnumConnectionPoints implementation object (0x24 bytes, allocated at 0x502504). Constructor read-only.
class HouseConnPtEnum : public IEnumConnectionPoints
{
public:
    // FUNCTION: GAMEMD 0x4A0C20 (read-only here)
    HouseConnPtEnum(void* connectionPoints);
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
    virtual HRESULT __stdcall Next(ULONG cConnections, IConnectionPoint** ppCP, ULONG* pcFetched);
    virtual HRESULT __stdcall Skip(ULONG cConnections);
    virtual HRESULT __stdcall Reset();
    virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum);
    unsigned char unknown_04[0x20];
};
GG_STATIC_ASSERT(sizeof(HouseConnPtEnum) == 0x24);

// AbstractClass-shaped object handed to PointerExpired: only WhatAmI (slot 11) is called.
class HouseAbstractPtrView
{
public:
    virtual void vf_0(); virtual void vf_1(); virtual void vf_2(); virtual void vf_3();
    virtual void vf_4(); virtual void vf_5(); virtual void vf_6(); virtual void vf_7();
    virtual void vf_8(); virtual void vf_9(); virtual void vf_10();
    virtual int WhatAmI();   // 11  +0x2C (6 == BuildingClass)
};

// The CRT's RTTI cast helper (VC6 __RTDynamicCast), declared by hand with the type descriptors spelled out.
// LIBRARY: GAMEMD 0x7CAAE4 (LIBRARY)
extern "C" void* __cdecl HouseRtDynamicCast(void* object, long vfDelta, void* srcType, void* dstType, int isReference);
// GLOBAL: GAMEMD 0x8177C8   .?AVAbstractClass@@
extern char HouseTypeDesc_AbstractClass[];
// GLOBAL: GAMEMD 0x8249E8   .?AVTagClass@@
extern char HouseTypeDesc_TagClass[];





// ---- views used by the house slots ---------------------------------------------------------------


// The type objects held in the rules type lists (index stored at +0xDF8).
struct HouseTypeIndexView
{
    unsigned char unknown_00[0x6CC];
    int           unknown_6CC;   // +0x6CC bit mask tested against the house type index (0x4F9129)
    unsigned char unknown_6D0[0xDF8 - 0x6D0];
    int           TypeIndex;   // +0xDF8
};
GG_STATIC_ASSERT(offsetof(HouseTypeIndexView, unknown_6CC) == 0x6CC);
GG_STATIC_ASSERT(offsetof(HouseTypeIndexView, TypeIndex) == 0xDF8);

// The COM interface held in AIGeneral; only its IUnknown slots are called here.
struct HouseAIGeneralView : public IUnknown
{
};

// Element types of the house vectors. Each distinct element type gets its own vptr in retail (the
// 0x7EA5A4 / 0x7E9E24 / 0x7EA944 / 0x7EA4E4 / 0x7EA924 / 0x7EA904 / 0x7E5D48 tables), so every element
// is its own opaque type here.
struct HouseTagRef
{
    // FUNCTION: GAMEMD 0x6E53A0 (read-only here) - fires a tag event
    void SpringEvent(int event, int a, HBCell cell, int b, int c);
};
struct HouseBuildingRef;
struct HouseStartingUnit { int Type; short X; short Y; };
// The super weapon type object (opaque here).
struct HouseSuperTypeView;
struct HouseSuperRef
{
    // Slots 0-7 are the COM IPersistStream block; the destructor is slot 8 of the retail table (scalar
    // deleting destructor, flag in the argument).
    virtual long __stdcall vf_0();
    virtual unsigned long __stdcall vf_1();
    virtual unsigned long __stdcall vf_2();
    virtual long __stdcall vf_3();
    virtual long __stdcall vf_4();
    virtual long __stdcall vf_5();
    virtual long __stdcall vf_6();
    virtual long __stdcall vf_7();
    virtual ~HouseSuperRef();

    unsigned char       unknown_04[0x24];
    HouseSuperTypeView* Type;   // +0x28
};
GG_STATIC_ASSERT(offsetof(HouseSuperRef, Type) == 0x28);
struct HouseAngerNode
{
    void* House;
    int   Value;
    HouseAngerNode() {}
    HouseAngerNode(void* house, int value) : House(house), Value(value) {}
};
struct HouseScoutNode
{
    void* Cell;
    bool  Flag;
    HouseScoutNode() {}
    HouseScoutNode(void* cell, bool flag) : Cell(cell), Flag(flag) {}
};

// Fixed-size character buffer with the inlined bounded assignment retail expands for PlainName and
// UINameString: the source is copied through a stack buffer (strncpy then a forced terminator) and the
// buffer is then copied over the member.
template <int N> struct HouseFixedString
{
    HouseFixedString() { Buffer[0] = 0; }

    void Assign(const char* source)
    {
        char temp[N];
        if (source == 0)
            temp[0] = 0;
        else {
            strncpy(temp, source, N - 1);
            temp[N - 1] = 0;
        }
        if (temp != Buffer)
            memcpy(Buffer, temp, N);
    }

    char Buffer[N];
};

// RandomClass-shaped (read-only here): the ranged draw used for the attack delay.
class HouseRandomView
{
public:
    // FUNCTION: GAMEMD 0x65C7E0 (read-only here)
    int RandomRanged(int minimum, int maximum);
};

// ScenarioClass-shaped (read-only here): the AI difficulty and the random generator.
struct HouseScenarioView
{
    unsigned char   unknown_00[0x218];
    HouseRandomView Random;   // +0x218
    unsigned char   unknown_219[0x610 - 0x219];
    int             Difficulty;   // +0x610 copied to AIDifficulty (ctor 0x4F54E2)
};
GG_STATIC_ASSERT(offsetof(HouseScenarioView, Difficulty) == 0x610);
// GLOBAL: GAMEMD 0xA8B230 - the scenario instance.
extern HouseScenarioView* HouseScenario;

// SuperClass-shaped (0x80 bytes, allocated at 0x4F6221; constructor read-only here).
struct HouseSuperObject : public HouseSuperRef
{
    // FUNCTION: GAMEMD 0x6CAF90 (read-only here)
    HouseSuperObject(void* superType, HouseClusterView* owner);
    unsigned char unknown_2C[0x54];
};
GG_STATIC_ASSERT(sizeof(HouseSuperObject) == 0x80);

// GLOBAL: GAMEMD 0xA8E334 / 0xA8E340 - the super-weapon type array (Items / Count).
extern void** HouseSuperTypeItems;
extern int HouseSuperTypeCount;

// The connection-point source object the constructor allocates (0x34 bytes, allocated at 0x4F64AB;
// constructor read-only here). Only the IUnknown slots are called.
class HouseConnPtSource : public IUnknown
{
public:
    // FUNCTION: GAMEMD 0x4A0870 (read-only here)
    HouseConnPtSource(const IID* iid, IUnknown* outer);
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
    virtual ULONG __stdcall AddRef();
    virtual ULONG __stdcall Release();
    unsigned char unknown_04[0x30];
};
GG_STATIC_ASSERT(sizeof(HouseConnPtSource) == 0x34);

// VectorClass<T> shape (0x10): vptr, Items, Capacity, IsInitialized/IsAllocated bytes.
template <class T> class HouseVector
{
public:
    // FUNCTION: GAMEMD various (read-only here): the (capacity, storage) constructor.
    HouseVector(int capacity, T* storage);
    virtual ~HouseVector();
    virtual bool operator==(const HouseVector<T>& other) const;     // 1
    virtual bool SetCapacity(int capacity, T* storage);              // 2
    virtual void Clear();                                            // 3
    virtual int FindItemIndex(const T& item) const;                  // 4
    T& operator[](int index) { return Items[index]; }

    T*            Items;           // +0x04
    int           Capacity;        // +0x08
    bool          IsInitialized;   // +0x0C
    bool          IsAllocated;     // +0x0D
    unsigned char unknown_0E[2];   // +0x0E
};

// DynamicVectorClass<T> shape (0x18).
template <class T> class HouseDynVector : public HouseVector<T>
{
public:
    HouseDynVector(int capacity, T* storage) : HouseVector<T>(capacity, storage)
    {
        CapacityIncrement = 10;
        Count = 0;
    }

    // DynamicVectorClass::AddItem, inlined by the original (the shape of the overlay module's expansion).
    bool AddItem(const T& item)
    {
        int cap = this->Capacity;
        if (Count < cap
            || ((this->IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && this->SetCapacity(CapacityIncrement + cap, 0))) {
            (*this)[Count++] = item;
            return true;
        }
        return false;
    }

    // The same operation as the expansion retail has at the first three building-vector loads (0x5036xx
    // ConYards / Buildings / UnitRepairStations): the grown capacity is `cap + increment`, not
    // `increment + cap`.
    bool AddItemCapFirst(const T& item)
    {
        int cap = this->Capacity;
        if (Count < cap
            || ((this->IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && this->SetCapacity(cap + CapacityIncrement, 0))) {
            (*this)[Count++] = item;
            return true;
        }
        return false;
    }

    // RemoveItem(index), expanded inline.
    bool RemoveItemAt(int index)
    {
        if (index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index) {
                this->Items[index] = this->Items[index + 1];
            }
            return true;
        }
        return false;
    }

    // The out-of-line RemoveItem(index) of the building vectors (0x45AE10 for HouseBuildingRef*).
    bool RemoveAt(int index);

    // DynamicVectorClass::RemoveItem, expanded inline where the original inlined it.
    bool RemoveItem(const T& item)
    {
        int index = this->FindItemIndex(item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index) {
                this->Items[index] = this->Items[index + 1];
            }
            return true;
        }
        return false;
    }
    int Count;               // +0x10
    int CapacityIncrement;   // +0x14
};

// HouseTypeClass-shaped: only the members the house entries read.
struct HouseTypeView
{
    unsigned char  unknown_00[0x24];
    char           Name[0x3C];        // +0x24 the plain name copied into PlainName (ctor 0x4F62C0)
    unsigned short* UIName;           // +0x60 the wide interface name copied into UIName (ctor 0x4F6307)
    char           NameBuffer[0x34];  // +0x64 source of the name returned by GetName (0x4F6961)
    char           Name2[0x20];       // +0x98 read by 0x4F90FF
    int            ArrayIndex2;       // +0xB8 the second array index (0x5113F0 ctor), folded into the CRC (0x502D7F)
    int            Side;              // +0xBC 0 / 1 / 2 selects SideIndex (ctor 0x4F6460)
    int            ColorScheme;       // +0xC0 copied to ColorSchemeIndex (ctor 0x4F5E57)
    unsigned char  unknown_C4[0x148 - 0xC4];
    float          ValueMultiplier;   // +0x148 scales the stored tiberium value (0x4F6999)
    unsigned char  unknown_14C[0x1A6 - 0x14C];
    bool           unknown_1A6;       // +0x1A6 read at 0x4F8A5B
};
GG_STATIC_ASSERT(offsetof(HouseTypeView, Name) == 0x24);
GG_STATIC_ASSERT(offsetof(HouseTypeView, UIName) == 0x60);
GG_STATIC_ASSERT(offsetof(HouseTypeView, NameBuffer) == 0x64);
GG_STATIC_ASSERT(offsetof(HouseTypeView, Name2) == 0x98);
GG_STATIC_ASSERT(offsetof(HouseTypeView, ArrayIndex2) == 0xB8);
GG_STATIC_ASSERT(offsetof(HouseTypeView, Side) == 0xBC);
GG_STATIC_ASSERT(offsetof(HouseTypeView, ColorScheme) == 0xC0);
GG_STATIC_ASSERT(offsetof(HouseTypeView, ValueMultiplier) == 0x148);
GG_STATIC_ASSERT(offsetof(HouseTypeView, unknown_1A6) == 0x1A6);

// ---- the primary-side base: AbstractClass-shaped, 0x24 bytes ---------------------------------------
// The 4 COM tables then UniqueID / flags / RefCount / dirty. Slots 0-7 are IPersistStream, 8.. game slots.
class HouseAbstractView : public IPersistStream, public HBRttiBase,
                          public HBNoticeSinkBase, public HBNoticeSourceBase
{
public:
    // FUNCTION: GAMEMD 0x410170 (AbstractClass constructor; read-only here)
    HouseAbstractView();

    virtual HRESULT __stdcall IsDirty();                                 // 4   0x410450
    // FUNCTION: GAMEMD 0x410380 (read-only here) - the AbstractClass load
    virtual HRESULT __stdcall Load(IStream* pStm);                       // 5
    // FUNCTION: GAMEMD 0x410320 (read-only here) - the AbstractClass save
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);     // 6
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize);       // 7   0x4103E0
    virtual ~HouseAbstractView();                                // 8   0x4F7140 body (house)
    virtual void vf_9();                                         // 9   0x410470
    virtual void PointerExpired(HouseAbstractPtrView* pointer, bool removed);    // 10  0x4FB9B0
    virtual int WhatAmI();                                       // 11  0x50E360
    virtual int Size();                                          // 12  0x504730
    virtual void ComputeCrc(HouseCrcView* crc);                  // 13  0x502D60
    virtual void vf_14();                                        // 14  0x410490
    virtual void vf_15();                                        // 15  0x4104A0
    virtual int vf_16();                                         // 16  0x50E370
    virtual void vf_17();                                        // 17  0x410440
    virtual void vf_18();                                        // 18  0x4104C0
    virtual void vf_19();                                        // 19  0x4104F0
    virtual void vf_20();                                        // 20  0x410520
    virtual void vf_21();                                        // 21  0x410530
    virtual void vf_22();                                        // 22  0x410540
    virtual void Update();                                       // 23  0x4F8440

    int           UniqueID;        // +0x10
    int           AbstractFlags;   // +0x14
    int           unknown_18;      // +0x18
    long          RefCount;        // +0x1C
    unsigned char Dirty;           // +0x20
    unsigned char unknown_21[3];   // +0x21
};
GG_STATIC_ASSERT(sizeof(HouseAbstractView) == 0x24);

// VTABLE: GAMEMD 0x7EA8A0 (primary), 0x7EA884 (+0x04), 0x7EA87C (+0x08), 0x7EA874 (+0x0C),
//         0x7EA834 (+0x24), 0x7EA80C (+0x28), 0x7EA7F4 (+0x2C)
class HouseClusterView : public HouseAbstractView, public HouseIHouseBase, public HousePublicHouseBase,
                         public IConnectionPointContainer
{
public:
    // FUNCTION: GAMEMD 0x4F54A0
    HouseClusterView(HouseTypeView* type);
    // FUNCTION: GAMEMD 0x4F5190 (read-only here) - the no-init constructor Load re-runs through placement new
    HouseClusterView(const HBNoInit& noInit);
    virtual ~HouseClusterView();

    // ---- primary table (IPersistStream side) overrides ----------------------------------------
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);   // 0   0x4F6830
    virtual ULONG __stdcall AddRef();                                    // 1   0x50E340
    virtual ULONG __stdcall Release();                                   // 2   0x50E350
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);               // 3   0x5046F0
    virtual HRESULT __stdcall Load(IStream* pStm);                       // 5   0x503040
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);     // 6   0x504080
    virtual void PointerExpired(HouseAbstractPtrView* pointer, bool removed);            // 10  0x4FB9B0
    virtual int WhatAmI();                                               // 11  0x50E360
    virtual int Size();                                                  // 12  0x504730
    virtual void ComputeCrc(HouseCrcView* crc);                          // 13  0x502D60
    virtual int vf_16();                                                 // 16  0x50E370
    virtual void Update();                                               // 23  0x4F8440

    // ---- IHouse / IPublicHouse overrides (this is the IHouse / IPublicHouse subobject) ---------
    virtual int __stdcall GetIndex();                                    // 0x4F6E60 (IHouse 3, IPublicHouse 3)
    virtual BSTR __stdcall GetName();                                    // 0x4F6950 (IHouse 4, IPublicHouse 4)
    virtual IUnknown* __stdcall GetMainInterface();                      // 0x4F6930
    virtual int __stdcall GetCredits();                                  // 0x4F6990
    virtual int __stdcall GetTiberiumStored();                           // 0x4F69D0
    virtual int __stdcall GetPowerOutput();                              // 0x4F6A00
    virtual int __stdcall GetPowerDrain();                               // 0x4F6A10
    virtual int __stdcall CountOwnedOfCategory(int category);            // 0x4F6A20
    virtual int __stdcall SumScoreOfCategory(int category);              // 0x4F6AE0
    virtual void* __stdcall GetBaseCenter(void* cell);                   // 0x4F6BC0
    virtual int __stdcall SellAllBuildings();                            // 0x5013A0
    virtual int __stdcall DestroyAllTechnos();                           // 0x501400
    virtual int __stdcall PublicCountOwnedOfCategory(int category);      // 0x4F6A80
    virtual int __stdcall PublicSumScoreOfCategory(int category);        // 0x4F6B50
    virtual void* __stdcall PublicGetBaseCenter(void* cell);             // 0x4F6D10
    virtual bool __stdcall HasEnoughPower();                             // 0x4F6910

    // ---- IConnectionPointContainer (+0x2C) -------------------------------------------------------
    virtual HRESULT __stdcall EnumConnectionPoints(IEnumConnectionPoints** ppEnum);          // 0x5024F0
    virtual HRESULT __stdcall FindConnectionPoint(REFIID riid, IConnectionPoint** ppCP);     // 0x502550

    // FUNCTION: GAMEMD 0x50BF60 (read-only here; matched elsewhere)
    void CalculateCostMultipliers();

    // ---- members (complete-object offsets) ---------------------------------------------------------
    int    ArrayIndex;                     // +0x30 ctor MOV [EBP+0x30],-1 @0x004F54B8
    HouseTypeView* Type;                         // +0x34 HouseTypeClass*; ctor MOV [EBP+0x34],EAX(=arg) @0x004F54C2
    HouseDynVector<HouseTagRef*> RelatedTags;                 // +0x38  ctor LEA ESI @0x004F54B4 (vptr 0x7EA5A4)
    HouseDynVector<HouseBuildingRef*> ConYards;                    // +0x50  ctor LEA ESI @0x004F54DB
    HouseDynVector<HouseBuildingRef*> Buildings;                   // +0x68  ctor LEA ESI @0x004F54F3
    HouseDynVector<HouseBuildingRef*> UnitRepairStations;          // +0x80  ctor LEA ESI @0x004F550B
    HouseDynVector<HouseBuildingRef*> Grinders;                    // +0x98  ctor LEA ESI @0x004F5526
    HouseDynVector<HouseBuildingRef*> Absorbers;                   // +0xB0  ctor LEA ESI @0x004F5541
    HouseDynVector<HouseBuildingRef*> Bunkers;                     // +0xC8  ctor LEA ESI @0x004F555C
    HouseDynVector<HouseBuildingRef*> Occupiables;                 // +0xE0  ctor LEA ESI @0x004F5577
    HouseDynVector<HouseBuildingRef*> CloningVats;                 // +0xF8  ctor LEA ESI @0x004F5592
    HouseDynVector<HouseBuildingRef*> SecretLabs;                  // +0x110 ctor LEA ESI @0x004F55AD
    HouseDynVector<HouseBuildingRef*> PsychicDetectionBuildings;   // +0x128 ctor LEA ESI @0x004F55C8
    HouseDynVector<HouseBuildingRef*> FactoryPlants;               // +0x140 ctor LEA ESI @0x004F55E3
    int    CountResourceGatherers;         // +0x158 ctor @0x004F55FE
    int    CountResourceDestinations;      // +0x15C ctor @0x004F5604
    int    CountWarfactories;              // +0x160 ctor @0x004F5610
    int    InfantrySelfHeal;               // +0x164 ctor @0x004F5617
    int    UnitsSelfHeal;                  // +0x168 ctor @0x004F5620
    HouseDynVector<HouseStartingUnit*> StartingUnits;      // +0x16C ctor LEA ESI @0x004F560A
    int    AIDifficulty;                   // +0x184 ctor @0x004F5648 (0 == Hard)
    double FirepowerMultiplier;            // +0x188 ctor halves @0x004F564E/0x004F5654
    double GroundspeedMultiplier;          // +0x190 ctor @0x004F565A/0x004F5660
    double AirspeedMultiplier;             // +0x198 ctor @0x004F5666/0x004F566C
    double ArmorMultiplier;                // +0x1A0 ctor @0x004F5672/0x004F5678
    double ROFMultiplier;                  // +0x1A8 ctor @0x004F567E/0x004F5684
    double CostMultiplier;                 // +0x1B0 ctor @0x004F568A/0x004F5690
    double BuildTimeMultiplier;            // +0x1B8 ctor @0x004F5696/0x004F569C
    double RepairDelay;                    // +0x1C0 ctor @0x004F56A2/0x004F56A8
    double BuildDelay;                     // +0x1C8 ctor @0x004F56AE/0x004F56B7
    int    IQLevel;                        // +0x1D0 ctor @0x004F56BD
    int    TechLevel;                      // +0x1D4 ctor MOV [EBP+0x1D4],1 @0x004F56C3
    unsigned int AltAllies;                // +0x1D8 IndexBitfield; ctor @0x004F56CD
    int    StartingCredits;                // +0x1DC ctor @0x004F56D3
    int    StartingEdge;                   // +0x1E0 ctor @0x004F56D9
    unsigned int AIState_1E4;              // +0x1E4 ctor @0x004F56DF (name anchor confirmed)
    int    SideIndex;                      // +0x1E8 ctor MOV [EBP+0x1E8],-1 @0x004F6455
    bool          IsHumanPlayer;           // +0x1EC ctor @0x004F56E5
    bool          IsInPlayerControl;       // +0x1ED ctor @0x004F56EB
    bool          Production;              // +0x1EE ctor @0x004F56F1
    bool          AutocreateAllowed;       // +0x1EF ctor @0x004F56F7
    bool          NodeLogic_1F0;           // +0x1F0 ctor MOV byte,1 @0x004F56FD (name anchor confirmed)
    bool          ShipYardConst_1F1;       // +0x1F1 ctor @0x004F5704 (name anchor confirmed)
    bool          AITriggersActive;        // +0x1F2 ctor @0x004F570A
    bool          AutoBaseBuilding;        // +0x1F3 ctor @0x004F5710
    bool          DiscoveredByPlayer;      // +0x1F4 ctor @0x004F5716
    bool          Defeated;                // +0x1F5 ctor @0x004F571C
    bool          IsGameOver;              // +0x1F6 ctor @0x004F5722
    bool          IsWinner;                // +0x1F7 ctor @0x004F5728
    bool          IsLoser;                 // +0x1F8 ctor @0x004F572E
    bool          CiviliansEvacuated;      // +0x1F9 ctor @0x004F5734
    bool          FirestormActive;         // +0x1FA ctor @0x004F573A
    bool          HasThreatNode;           // +0x1FB ctor @0x004F5740
    bool          RecheckTechTree;         // +0x1FC ctor MOV byte,1 @0x004F5746
    unsigned char align_1FD[3];            // +0x1FD
    int    IPAddress;                      // +0x200 ctor @0x004F574D
    int    TournamentTeamID;               // +0x204 ctor @0x004F5753
    bool          LostConnection;          // +0x208 ctor @0x004F5759
    unsigned char align_209[3];            // +0x209
    int    SelectedPathIndex;              // +0x20C ctor @0x004F575F
    WaypointPathClass* PlanningPaths[12];              // +0x210 .. 0x23F ctor LEA EDI @0x004F643B (12 dwords = 0x30)
    signed char   Visionary;               // +0x240 ctor @0x004F5765
    bool          MapIsClear;              // +0x241 ctor @0x004F576B
    bool          IsTiberiumShort;         // +0x242 ctor @0x004F5771
    bool          HasBeenSpied;            // +0x243 ctor @0x004F5777
    bool          HasBeenThieved;          // +0x244 ctor @0x004F577D
    bool          Repairing;               // +0x245 ctor @0x004F5783
    bool          IsBuiltSomething;        // +0x246 ctor @0x004F5789
    bool          IsResigner;              // +0x247 ctor @0x004F578F
    bool          IsGiverUpper;            // +0x248 ctor @0x004F5795
    bool          AllToHunt;               // +0x249 ctor @0x004F579B
    bool          IsParanoid;              // +0x24A ctor @0x004F57A1
    bool          IsToLook;                // +0x24B ctor MOV byte,1 @0x004F57A7
    int    IQLevel2;                       // +0x24C ctor @0x004F57BB
    int    AIMode;                         // +0x250 ctor @0x004F57C4
    HouseDynVector<HouseSuperRef*> Supers;             // +0x254 ctor LEA ESI @0x004F57B4
    int    LastBuiltBuildingType;          // +0x26C ctor @0x004F57DE
    int    LastBuiltInfantryType;          // +0x270 ctor @0x004F57E4
    int    LastBuiltAircraftType;          // +0x274 ctor @0x004F57EA
    int    LastBuiltVehicleType;           // +0x278 ctor @0x004F57F0
    int    AllowWinBlocks;                 // +0x27C ctor @0x004F57F6
    HouseTimer RepairTimer;              // +0x280 ctor @0x004F5802/0x004F5808
    HouseTimer AlertTimer;               // +0x28C ctor @0x004F581A/0x004F5814
    HouseTimer BorrowedTime;             // +0x298 ctor @0x004F5825/0x004F582B
    HouseTimer PowerBlackoutTimer;       // +0x2A4 ctor @0x004F583D/0x004F5837
    HouseTimer RadarBlackoutTimer;       // +0x2B0 ctor @0x004F5849/0x004F584F
    bool          Side2TechInfiltrated;    // +0x2BC ctor @0x004F5855
    bool          Side1TechInfiltrated;    // +0x2BD ctor @0x004F585B
    bool          Side0TechInfiltrated;    // +0x2BE ctor @0x004F5861
    bool          BarracksInfiltrated;     // +0x2BF ctor @0x004F5867
    bool          WarFactoryInfiltrated;   // +0x2C0 ctor @0x004F586D
    unsigned char align_2C1[3];            // +0x2C1
    unsigned int InfantryAltOwner;         // +0x2C4 ctor @0x004F5879
    unsigned int UnitAltOwner;             // +0x2C8 ctor @0x004F587F
    unsigned int AircraftAltOwner;         // +0x2CC ctor @0x004F5885
    unsigned int BuildingAltOwner;         // +0x2D0 ctor @0x004F588B
    int    AirportDocks;                   // +0x2D4 ctor @0x004F5891
    int    PoweredUnitCenters;             // +0x2D8 ctor @0x004F5897
    int    CreditsSpent;                   // +0x2DC ctor @0x004F589D
    int    HarvestedCredits;               // +0x2E0 ctor @0x004F58A3
    int    StolenBuildingsCredits;         // +0x2E4 ctor @0x004F58A9
    int    OwnedUnits;                     // +0x2E8 ctor @0x004F58AF
    int    OwnedNavy;                      // +0x2EC ctor @0x004F58B5
    int    OwnedBuildings;                 // +0x2F0 ctor @0x004F58BB
    int    OwnedInfantry;                  // +0x2F4 ctor @0x004F58C1
    int    OwnedAircraft;                  // +0x2F8 ctor @0x004F58C7
    HouseStorage OwnedTiberium;            // +0x2FC ctor LEA ECX @0x004F5873
    int    Balance;                        // +0x30C ctor @0x004F58D8
    int    TotalStorage;                   // +0x310 ctor @0x004F58DE
    HouseStorage OwnedWeed;                // +0x314 ctor LEA ECX @0x004F58D2
    unsigned int unknown_324;              // +0x324 (name anchor confirmed; ctor leaves it, bounded
                                           //        by OwnedWeed end and BuiltAircraftTypes start)
    HouseUnitTracker BuiltAircraftTypes;   // +0x328   ctor LEA ECX @0x004F58E9
    HouseUnitTracker BuiltInfantryTypes;   // +0xB30   ctor LEA ECX @0x004F58F4
    HouseUnitTracker BuiltUnitTypes;       // +0x1338  ctor LEA ECX @0x004F58FF
    HouseUnitTracker BuiltBuildingTypes;   // +0x1B40  ctor LEA ECX @0x004F590A
    HouseUnitTracker KilledAircraftTypes;  // +0x2348  ctor LEA ECX @0x004F5915
    HouseUnitTracker KilledInfantryTypes;  // +0x2B50  ctor LEA ECX @0x004F5920
    HouseUnitTracker KilledUnitTypes;      // +0x3358  ctor LEA ECX @0x004F592B
    HouseUnitTracker KilledBuildingTypes;  // +0x3B60  ctor LEA ECX @0x004F5936
    HouseUnitTracker CapturedBuildings;    // +0x4368  ctor LEA ECX @0x004F5941
    HouseUnitTracker CollectedCrates;      // +0x4B70  ctor LEA ECX @0x004F594C
    int    NumAirpads;                     // +0x5378 ctor @0x004F595C
    int    NumBarracks;                    // +0x537C ctor @0x004F5962
    int    NumWarFactories;                // +0x5380 ctor @0x004F5968
    int    NumConYards;                    // +0x5384 ctor @0x004F596E
    int    NumShipyards;                   // +0x5388 ctor @0x004F5974
    int    NumOrePurifiers;                // +0x538C ctor @0x004F597A
    float  CostInfantryMult;               // +0x5390 ctor @0x004F5980
    float  CostUnitsMult;                  // +0x5394 ctor @0x004F5986
    float  CostAircraftMult;               // +0x5398 ctor @0x004F598C
    float  CostBuildingsMult;              // +0x539C ctor @0x004F5992
    float  CostDefensesMult;               // +0x53A0 ctor @0x004F5998
    int    PowerOutput;                    // +0x53A4 ctor @0x004F599E
    int    PowerDrain;                     // +0x53A8 ctor @0x004F59A4
    void*  Primary_ForAircraft;            // +0x53AC ctor @0x004F59AA
    void*  Primary_ForInfantry;            // +0x53B0 ctor @0x004F59B0
    void*  Primary_ForVehicles;            // +0x53B4 ctor @0x004F59B6
    void*  Primary_ForShips;               // +0x53B8 ctor @0x004F59BC
    void*  Primary_ForBuildings;           // +0x53BC ctor @0x004F59C2
    void*  Primary_Unused1;                // +0x53C0 ctor @0x004F59C8
    void*  Primary_Unused2;                // +0x53C4 ctor @0x004F59CE
    void*  Primary_Unused3;                // +0x53C8 ctor @0x004F59D4
    void*  Primary_ForDefenses;            // +0x53CC ctor @0x004F59DA
    unsigned char AircraftType_53D0;       // +0x53D0 ctor @0x004F59E0 (name anchor confirmed)
    unsigned char InfantryType_53D1;       // +0x53D1 ctor @0x004F59E6
    unsigned char VehicleType_53D2;        // +0x53D2 ctor @0x004F59EC
    unsigned char ShipType_53D3;           // +0x53D3 ctor @0x004F59F2
    unsigned char BuildingType_53D4;       // +0x53D4 ctor @0x004F59F8
    unsigned char unknown_53D5;            // +0x53D5 ctor @0x004F59FE
    unsigned char unknown_53D6;            // +0x53D6 ctor @0x004F5A04
    unsigned char unknown_53D7;            // +0x53D7 ctor @0x004F5A0A
    unsigned char DefenseType_53D8;        // +0x53D8 ctor @0x004F5A10
    unsigned char unknown_53D9[3];         // +0x53D9 never written by the ctor
    HouseTechnoView* OurFlagCarrier;       // +0x53DC UnitClass*; ctor @0x004F5A16
    HBCell OurFlagCoords;              // +0x53E0 ctor word stores @0x004F5A1C/0x004F5A23
    int    KilledUnitsOfHouses[20];        // +0x53E4 .. 0x5433 ctor LEA EDI @0x004F62A1
    int    TotalKilledUnits;               // +0x5434 ctor @0x004F5A2A
    int    KilledBuildingsOfHouses[20];    // +0x5438 .. 0x5487 ctor LEA EDI @0x004F62AE
    int    TotalKilledBuildings;           // +0x5488 ctor @0x004F5A30
    int    WhoLastHurtMe;                  // +0x548C ctor @0x004F5A36
    HBCell BaseSpawnCell;              // +0x5490 ctor @0x004F5A41
    HBCell BaseCenter;                 // +0x5494 ctor @0x004F5A4D
    int    Radius;                         // +0x5498 ctor @0x004F5A53
    unsigned char ZoneInfos[0x3C];           // +0x549C .. 0x54D7 bounded, not written — see note
    int    LATime;                         // +0x54D8 ctor @0x004F5A59
    int    LAEnemy;                        // +0x54DC ctor @0x004F5A5F
    HouseAbstractPtrView* ToCapture;                 // +0x54E0 ctor @0x004F5A65
    unsigned int RadarVisibleTo;           // +0x54E4 IndexBitfield; ctor @0x004F5A6B
    int    PointTotal;                     // +0x54E8 ctor @0x004F5A71
    int    PreferredTargetType;            // +0x54EC ctor MOV [EBP+0x54EC],1 @0x004F5A77
    HBCell PreferredTargetCell;        // +0x54F0 ctor @0x004F5A81/0x004F5A88
    HBCell PreferredDefensiveCell;     // +0x54F4 ctor @0x004F5A8F/0x004F5A96
    HBCell PreferredDefensiveCell2;    // +0x54F8 ctor @0x004F5A9D/0x004F5AA4
    int    PreferredDefensiveCellStartTime;// +0x54FC ctor MOV [EBP+0x54FC],-100 @0x004F5AB1
    HouseCounter OwnedBuildingTypes;            // +0x5500 ctor LEA ECX @0x004F5AAB
    HouseCounter OwnedUnitTypes;                // +0x5514 ctor LEA ECX @0x004F5AC0
    HouseCounter OwnedInfantryTypes;            // +0x5528 ctor LEA ECX @0x004F5ACB
    HouseCounter OwnedAircraftTypes;            // +0x553C ctor LEA ECX @0x004F5AD6
    HouseCounter ActiveBuildingTypes;           // +0x5550 ctor LEA ECX @0x004F5AE1
    HouseCounter ActiveUnitTypes;               // +0x5564 ctor LEA ECX @0x004F5AEC
    HouseCounter ActiveInfantryTypes;           // +0x5578 ctor LEA ECX @0x004F5AF7
    HouseCounter ActiveAircraftTypes;           // +0x558C ctor LEA ECX @0x004F5B02
    HouseCounter FactoryProducedBuildingTypes;  // +0x55A0 ctor LEA ECX @0x004F5B0D
    HouseCounter FactoryProducedUnitTypes;      // +0x55B4 ctor LEA ECX @0x004F5B18
    HouseCounter FactoryProducedInfantryTypes;  // +0x55C8 ctor LEA ECX @0x004F5B23
    HouseCounter FactoryProducedAircraftTypes;  // +0x55DC ctor LEA ECX @0x004F5B2E
    HouseTimer AttackTimer;              // +0x55F0 ctor @0x004F5B40/0x004F637D
    int    InitialAttackDelay;             // +0x55FC ctor @0x004F5B4C
    int    EnemyHouseIndex;                // +0x5600 ctor @0x004F5B59
    HouseDynVector<HouseAngerNode> AngerNodes;         // +0x5604 ctor LEA ECX @0x004F5B52
    HouseDynVector<HouseScoutNode> ScoutNodes;         // +0x561C ctor LEA ECX @0x004F5B65
    HouseTimer AITimer;                  // +0x5634 ctor @0x004F5BA2/0x004F5BA8
    HouseTimer Unknown_Timer_5640;       // +0x5640 ctor @0x004F5BBA/0x004F5BB4 (name anchor confirmed)
    int    ProducingBuildingTypeIndex;     // +0x564C ctor @0x004F5BC0
    int    ProducingUnitTypeIndex;         // +0x5650 ctor @0x004F5BC6
    int    ProducingInfantryTypeIndex;     // +0x5654 ctor @0x004F5BCC
    int    ProducingAircraftTypeIndex;     // +0x5658 ctor @0x004F5BD2
    int    RatioAITriggerTeam;             // +0x565C ctor MOV [EBP+0x565C],0x64 @0x004F5BDD
    int    RatioTeamAircraft;              // +0x5660 ctor @0x004F5BE7
    int    RatioTeamInfantry;              // +0x5664 ctor @0x004F5BED
    int    RatioTeamBuildings;             // +0x5668 ctor @0x004F5BF3
    int    BaseDefenseTeamCount;           // +0x566C ctor @0x004F5BF9
    HouseDropship DropshipData[3];        // +0x5670 .. 0x56F3 ctor LEA ESI @0x004F5BFF
    int    CurrentDropshipIndex;           // +0x56F4 ctor @0x004F5C22
    bool          HasCloakingRanges;       // +0x56F8 ctor @0x004F5C28
    HouseRgb Color;                     // +0x56F9 ctor @0x004F5C30/0x004F5C36/0x004F5C3C
    HouseRgb LaserColor;                // +0x56FC ctor @0x004F5C48/0x004F5C4E/0x004F5C54
    unsigned char align_56FF;              // +0x56FF
    HouseBase Base;                        // +0x5700 .. 0x5777 ctor LEA ECX @0x004F5C42
    bool          RecheckPower;            // +0x5778 ctor MOV byte,1 @0x004F5C5F
    bool          RecheckRadar;            // +0x5779 ctor MOV byte,1 @0x004F5C66
    bool          SpySatActive;            // +0x577A ctor @0x004F5C6D
    bool          IsBeingDrained;          // +0x577B ctor @0x004F5C73
    int    Edge;                           // +0x577C ctor @0x004F5C79
    HBCell EMPTarget;                  // +0x5780 ctor @0x004F5C7F/0x004F5C86
    HBCell NukeTarget;                 // +0x5784 ctor @0x004F5C8D/0x004F5C94
    unsigned int Allies;                   // +0x5788 IndexBitfield; ctor @0x004F5C9B
    HouseTimer DamageDelayTimer;         // +0x578C ctor @0x004F5CC4/0x004F5CBE
    HouseTimer TeamDelayTimer;           // +0x5798 ctor @0x004F5CD5/0x004F5CDB
    HouseTimer TriggerDelayTimer;        // +0x57A4 ctor @0x004F5CE7/0x004F5CED
    HouseTimer SpeakAttackDelayTimer;    // +0x57B0 ctor @0x004F5CFF/0x004F5CF9
    HouseTimer SpeakPowerDelayTimer;     // +0x57BC ctor @0x004F5D0B/0x004F5D11
    HouseTimer SpeakMoneyDelayTimer;     // +0x57C8 ctor @0x004F5D23/0x004F5D1D
    HouseTimer SpeakMaxedDelayTimer;     // +0x57D4 ctor @0x004F5D2F/0x004F5D35
    HouseAIGeneralView* AIGeneral;         // +0x57E0 IAIHouse*; ctor @0x004F5D3B
    unsigned int ThreatPosedEstimates[130][130]; // +0x57E4 .. 0x15FF3 ctor LEA EDI @0x004F61F6;
                                           //   0x10810 bytes, closing exactly on PlainName
    HouseFixedString<21> PlainName;        // +0x15FF4 ctor MOV byte [EBP+0x15FF4],BL @0x004F5D41
    HouseFixedString<32> UINameString;     // +0x16009 ctor MOV byte [EBP+0x16009],BL @0x004F5D4D
    unsigned char unknown_16029;           // +0x16029
    unsigned short UIName[21];             // +0x1602A wchar_t[21]; ctor MOV word [EBP+0x1602A],BX @0x004F5E46
    int    ColorSchemeIndex;               // +0x16054 ctor @0x004F5D54
    int    StartingPoint;                  // +0x16058 NOT written by the ctor (union with a HBCell)
    unsigned int StartingAllies;           // +0x1605C NOT written by the ctor
    unsigned int unknown_16060;            // +0x16060 ctor @0x004F5D5D
    HouseDynVector<IConnectionPoint*> ConnectionPoints;       // +0x16064 ctor LEA ESI @0x004F5D47
    unsigned int unknown_1607C;            // +0x1607C ctor @0x004F5D74
    unsigned int unknown_16080;            // +0x16080 ctor @0x004F5D7A
    unsigned int unknown_16084;            // +0x16084 NOT written by the ctor
    double unused_16088;                   // +0x16088 ctor @0x004F5D85/0x004F5D8B
    double unused_16090;                   // +0x16090 ctor @0x004F5D91/0x004F5D97
    unsigned int padding_16098;            // +0x16098 NOT written by the ctor
    float  PredictionEnemyArmor;           // +0x1609C ctor @0x004F5DA2
    float  PredictionEnemyAir;             // +0x160A0 ctor @0x004F5DA8
    float  PredictionEnemyInfantry;        // +0x160A4 ctor @0x004F5DAE
    int    TotalOwnedInfantryCost;         // +0x160A8 ctor @0x004F5DB4
    int    TotalOwnedVehicleCost;          // +0x160AC ctor @0x004F5DBA
    int    TotalOwnedAircraftCost;         // +0x160B0 ctor @0x004F5DC0
    int    PowerSurplus;                   // +0x160B4 ctor @0x004F5DC6; closes the object at 0x160B8
};

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_CLASS_CORE_H
