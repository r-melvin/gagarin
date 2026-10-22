//   No /GX: the stack list has a destructor and retail carries no unwind frame.
// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 at 0x595CE0 (no arguments, plain RET):
//   a dynamic vector of 0x140-byte find-data records on the stack (base
//   constructor 0x5AD9F0, vtables 0x7ED94C dynamic / 0x7ED92C base, growth
//   10, slot 2 resize); the "rmcache\*.mmp" pattern at 0x82BB0C walked with
//   the imports at 0x7E1208/0x7E120C/0x7E1300; the 70-entry cap; the oldest
//   record chosen by the import at 0x7E1100 over the times at +0x0C, +0x04
//   and +0x14 (tested by their high dwords), its name at +0x2C deleted by the
//   import at 0x7E10E0.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct FileTime_00595CE0
{
    unsigned long Low;    // +0x00
    unsigned long High;   // +0x04
};

// The 0x140-byte find-data record (allocation size pushed at 0x595D04).
struct FindData_00595CE0
{
    unsigned long     Attributes;     // +0x00
    FileTime_00595CE0 CreationTime;   // +0x04
    FileTime_00595CE0 AccessTime;     // +0x0C
    FileTime_00595CE0 WriteTime;      // +0x14
    unsigned long     SizeHigh;       // +0x1C
    unsigned long     SizeLow;        // +0x20
    unsigned long     Reserved0;      // +0x24
    unsigned long     Reserved1;      // +0x28
    char              Name[260];      // +0x2C
    char              AltName[14];    // +0x130
    char              _pad13E[2];     // +0x13E
};
GG_STATIC_ASSERT(offsetof(FindData_00595CE0, AccessTime) == 0x0C);
GG_STATIC_ASSERT(offsetof(FindData_00595CE0, WriteTime) == 0x14);
GG_STATIC_ASSERT(offsetof(FindData_00595CE0, Name) == 0x2C);
// Size proven by the `PUSH 0x140` allocations.
GG_STATIC_ASSERT(sizeof(FindData_00595CE0) == 0x140);

extern "C" __declspec(dllimport) void* __stdcall FindFirstFileA(const char* pattern, FindData_00595CE0* data);
extern "C" __declspec(dllimport) int __stdcall FindNextFileA(void* handle, FindData_00595CE0* data);
extern "C" __declspec(dllimport) int __stdcall FindClose(void* handle);
extern "C" __declspec(dllimport) long __stdcall CompareFileTime(const FileTime_00595CE0* a, const FileTime_00595CE0* b);
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char* name);

// STRING: GAMEMD 0x82BB0C  "rmcache\*.mmp"
extern const char STR_0082BB0C[];
// VTABLE: GAMEMD 0x7ED92C -- the vector base.
extern void* DAT_007ED92C[];
// VTABLE: GAMEMD 0x7ED94C -- the dynamic vector.
extern void* DAT_007ED94C[];

struct FindDataList_00595CE0;

// Out-of-line vector pieces reached with the list in ECX.
struct FindDataVectorShim
{
    // FUNCTION: GAMEMD 0x5AD9F0 (decl; reloc) -- VectorClass(capacity, pMem).
    void Construct(int capacity, FindData_00595CE0** pMem);

    virtual ~FindDataVectorShim();
    virtual bool Equals(const FindDataVectorShim* other);
    virtual bool SetCapacity(int capacity, FindData_00595CE0** pMem);
};

struct FindDataList_00595CE0
{
    void*               _vtable;            // +0x00
    FindData_00595CE0** Items;              // +0x04
    int                 Capacity;           // +0x08
    bool                IsInitialized;      // +0x0C
    bool                IsAllocated;        // +0x0D
    int                 Count;              // +0x10
    int                 CapacityIncrement;  // +0x14

    FindDataList_00595CE0() throw()
    {
        ((FindDataVectorShim*)this)->Construct(0, 0);
        _vtable = DAT_007ED94C;
        CapacityIncrement = 10;
        Count = 0;
    }

    ~FindDataList_00595CE0() throw()
    {
        _vtable = DAT_007ED92C;
        if (Items != 0 && IsAllocated) {
            delete Items;
        }
    }

    bool AddItem(FindData_00595CE0* item) throw()
    {
        if (Count >= Capacity) {
            if (!IsAllocated && Capacity != 0) {
                return false;
            }
            if (CapacityIncrement <= 0) {
                return false;
            }
            if (!((FindDataVectorShim*)this)->SetCapacity(Capacity + CapacityIncrement, 0)) {
                return false;
            }
        }
        int index = Count++;
        Items[index] = item;
        return true;
    }

    bool Delete(int index) throw()
    {
        if (index < Count) {
            Count--;
            for (int i = index; i < Count; i++) {
                Items[i] = Items[i + 1];
            }
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(FindDataList_00595CE0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(FindDataList_00595CE0, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(FindDataList_00595CE0) == 0x18);

// FUNCTION: GAMEMD 0x595CE0
// Keep at most 70 cached map files: list them, then repeatedly delete the
// one with the oldest access (else creation, else write) time.
void __cdecl FUN_00595CE0(void)
{
    FindDataList_00595CE0 list;

    FindData_00595CE0* data = new FindData_00595CE0;
    void* handle = FindFirstFileA(STR_0082BB0C, data);
    if (handle != (void*)-1) {
        list.AddItem(data);
        data = new FindData_00595CE0;
        while (FindNextFileA(handle, data)) {
            list.AddItem(data);
            data = new FindData_00595CE0;
        }
        FindClose(handle);
    }
    delete data;

    while (list.Count > 70) {
        int oldest = -1;
        FileTime_00595CE0 best;
        best.Low = 0xFFFFFFFF;
        best.High = 0x7FFFFFFF;
        for (int i = 0; i < list.Count; i++) {
            if (list.Items[i]->AccessTime.High != 0) {
                if (CompareFileTime(&list.Items[i]->AccessTime, &best) == -1) {
                    oldest = i;
                    best.Low = list.Items[i]->AccessTime.Low;
                    best.High = list.Items[i]->AccessTime.High;
                }
            } else if (list.Items[i]->CreationTime.High != 0) {
                if (CompareFileTime(&list.Items[i]->CreationTime, &best) == -1) {
                    oldest = i;
                    best.Low = list.Items[i]->CreationTime.Low;
                    best.High = list.Items[i]->CreationTime.High;
                }
            } else if (list.Items[i]->WriteTime.High != 0) {
                if (CompareFileTime(&list.Items[i]->WriteTime, &best) == -1) {
                    oldest = i;
                    best.Low = list.Items[i]->WriteTime.Low;
                    best.High = list.Items[i]->WriteTime.High;
                }
            }
        }
        if (oldest == -1) {
            break;
        }
        if (!DeleteFileA(list.Items[oldest]->Name)) {
            break;
        }
        delete list.Items[oldest];
        list.Delete(oldest);
    }

    while (list.Count != 0) {
        delete list.Items[0];
        list.Delete(0);
    }
}
