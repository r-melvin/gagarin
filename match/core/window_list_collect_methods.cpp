// Provenance: own-binary-via-Ghidra
// Window-enumeration callback (__stdcall, `ret 8`): its address is pushed
// at 0x61210B and 0x61275F together with a zeroed 12-byte local list and
// passed to the imported enumerator at [0x7E14E4]. It appends the handle to
// the list {count +0x00, capacity +0x04, data +0x08}. The append inlines
// the same grow step twice (once for the append, once inside the insert):
// capacity doubles with a floor of 10, the new block is cleared, the old
// elements copied, and the old block freed (operator new 0x7C8E17,
// operator delete 0x7C8B3D); the insert shifts the tail with memmove and
// constructs the element in place behind a null check.
#include <windows.h>
#include <new.h>
#include <string.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct WindowEntry_00622470
{
    HWND Window;   // +0x00

    WindowEntry_00622470(HWND window) : Window(window) {}
};
GG_STATIC_ASSERT(sizeof(WindowEntry_00622470) == 4);

class WindowList_00622470
{
public:
    int Count;      // +0x00
    int Capacity;   // +0x04
    WindowEntry_00622470* Data;        // +0x08

    void Grow()
    {
        if (Count >= Capacity) {
            int size = Count * 2;
            if (size < 10) size = 10;
            WindowEntry_00622470* data = (WindowEntry_00622470*)operator new(size * sizeof(WindowEntry_00622470));
            memset(data, 0, size * sizeof(WindowEntry_00622470));
            if (Data != NULL) {
                memcpy(data, Data, Count * sizeof(WindowEntry_00622470));
            }
            operator delete(Data);
            Data = data;
            Capacity = size;
        }
    }

    void Insert(int index, const WindowEntry_00622470& value)
    {
        Grow();
        if (index < Count) {
            memmove(&Data[index + 1], &Data[index], (Count - index) * sizeof(WindowEntry_00622470));
        }
        new (&Data[index]) WindowEntry_00622470(value);
        Count++;
    }

    void Add(const WindowEntry_00622470& value)
    {
        int index = Count;
        Grow();
        Insert(index, value);
    }
};
GG_STATIC_ASSERT(offsetof(WindowList_00622470, Count) == 0x00);
GG_STATIC_ASSERT(offsetof(WindowList_00622470, Capacity) == 0x04);
GG_STATIC_ASSERT(offsetof(WindowList_00622470, Data) == 0x08);

// FUNCTION: GAMEMD 0x622470
BOOL CALLBACK FUN_00622470(HWND window, LPARAM param)
{
    WindowList_00622470* list = (WindowList_00622470*)param;
    if (list != NULL) {
        list->Add(window);
    }
    return TRUE;
}
