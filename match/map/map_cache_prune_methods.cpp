// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail entry 0x595CE0 creates the stack vector, searches rmcache map files,
// and deletes the oldest records above its 70-file limit. Native allocation
// size 0x140 and the FindFirstFileA/FindNextFileA imports identify the SDK
// WIN32_FIND_DATAA ABI. RTTI tables 0x7ED92C/0x7ED94C identify the canonical
// VectorClass/DynamicVectorClass pointer specialization.
#include <windows.h>
#include "../core/vector_find_data.h"
#include "../core/vector_class_dynamic_ctor.h"
#include "../core/vector_class_mutation.h"

template class VectorClass<WIN32_FIND_DATAA*>;
template class DynamicVectorClass<WIN32_FIND_DATAA*>;
typedef VectorClass<WIN32_FIND_DATAA*> FindDataVector;
GG_STATIC_ASSERT(sizeof(FindDataVector) == 0x10);
typedef DynamicVectorClass<WIN32_FIND_DATAA*> FindDataList;
GG_STATIC_ASSERT(sizeof(WIN32_FIND_DATAA) == 0x140);
GG_STATIC_ASSERT(offsetof(WIN32_FIND_DATAA, ftCreationTime) == 0x04);
GG_STATIC_ASSERT(offsetof(WIN32_FIND_DATAA, ftLastAccessTime) == 0x0C);
GG_STATIC_ASSERT(offsetof(WIN32_FIND_DATAA, ftLastWriteTime) == 0x14);
GG_STATIC_ASSERT(offsetof(WIN32_FIND_DATAA, cFileName) == 0x2C);
GG_STATIC_ASSERT(offsetof(FILETIME, dwLowDateTime) == 0);
GG_STATIC_ASSERT(offsetof(FILETIME, dwHighDateTime) == 4);
GG_STATIC_ASSERT(sizeof(FILETIME) == 8);
GG_STATIC_ASSERT(offsetof(FindDataList, Items) == 4);
GG_STATIC_ASSERT(offsetof(FindDataList, Capacity) == 8);
GG_STATIC_ASSERT(offsetof(FindDataList, IsInitialized) == 0xC);
GG_STATIC_ASSERT(offsetof(FindDataList, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(FindDataList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(FindDataList, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(FindDataList) == 0x18);
// VTABLE: GAMEMD 0x7ED92C -- VectorClass<WIN32_FIND_DATAA*>.
// VTABLE: GAMEMD 0x7ED94C -- DynamicVectorClass<WIN32_FIND_DATAA*>.
// STRING: GAMEMD 0x82BB0C
extern const char STR_0082BB0C[];

// FUNCTION: GAMEMD 0x595CE0
// Keep at most 70 cached map files: list them, then repeatedly delete the
// one with the oldest access (else creation, else write) time.
void __cdecl FUN_00595CE0(void)
{
    FindDataList list;

    WIN32_FIND_DATAA* data = new WIN32_FIND_DATAA;
    HANDLE handle = FindFirstFileA(STR_0082BB0C, data);
    if (handle != INVALID_HANDLE_VALUE) {
        list.AddItem(data);
        data = new WIN32_FIND_DATAA;
        while (FindNextFileA(handle, data)) {
            list.AddItem(data);
            data = new WIN32_FIND_DATAA;
        }
        FindClose(handle);
    }
    delete data;

    while (list.Count > 70) {
        int oldest = -1;
        FILETIME best;
        best.dwLowDateTime = 0xFFFFFFFF;
        best.dwHighDateTime = 0x7FFFFFFF;
        for (int i = 0; i < list.Count; i++) {
            if (list.Items[i]->ftLastAccessTime.dwHighDateTime != 0) {
                if (CompareFileTime(&list.Items[i]->ftLastAccessTime, &best) == -1) {
                    oldest = i;
                    best.dwLowDateTime = list.Items[i]->ftLastAccessTime.dwLowDateTime;
                    best.dwHighDateTime = list.Items[i]->ftLastAccessTime.dwHighDateTime;
                }
            } else if (list.Items[i]->ftCreationTime.dwHighDateTime != 0) {
                if (CompareFileTime(&list.Items[i]->ftCreationTime, &best) == -1) {
                    oldest = i;
                    best.dwLowDateTime = list.Items[i]->ftCreationTime.dwLowDateTime;
                    best.dwHighDateTime = list.Items[i]->ftCreationTime.dwHighDateTime;
                }
            } else if (list.Items[i]->ftLastWriteTime.dwHighDateTime != 0) {
                if (CompareFileTime(&list.Items[i]->ftLastWriteTime, &best) == -1) {
                    oldest = i;
                    best.dwLowDateTime = list.Items[i]->ftLastWriteTime.dwLowDateTime;
                    best.dwHighDateTime = list.Items[i]->ftLastWriteTime.dwHighDateTime;
                }
            }
        }
        if (oldest == -1) {
            break;
        }
        if (!DeleteFileA(list.Items[oldest]->cFileName)) {
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
