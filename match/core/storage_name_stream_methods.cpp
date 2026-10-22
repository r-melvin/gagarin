// Provenance: own-binary-via-Ghidra
// Writes a wide copy of a narrow string into a named stream of an IStorage
// and commits it. __stdcall, three stack arguments (`ret 0xC`): the storage,
// a key looked up in a 13-entry {key, wide name} table at 0x83D658 (bounds
// 0x83D658..0x83D6C0), and the narrow text. The stream is held in a
// comip.h smart pointer: the E_POINTER issue call (0x7DC720) and the
// Release on every exit come from _com_ptr_t.
#include <comdef.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct StreamNameEntry
{
    int Key;                 // +0x00
    const wchar_t* Name;     // +0x04
};
GG_STATIC_ASSERT(offsetof(StreamNameEntry, Key) == 0);
GG_STATIC_ASSERT(offsetof(StreamNameEntry, Name) == 4);
GG_STATIC_ASSERT(sizeof(StreamNameEntry) == 8);

// GLOBAL: GAMEMD 0x83D658
extern StreamNameEntry DAT_0083d658[13];

_COM_SMARTPTR_TYPEDEF(IStream, __uuidof(IStream));

inline const wchar_t* StreamNameForKey(int key)
{
    for (int i = 0; i < 13; i++) {
        if (DAT_0083d658[i].Key == key) {
            return DAT_0083d658[i].Name;
        }
    }
    return NULL;
}

// FUNCTION: GAMEMD 0x682640
HRESULT __stdcall FUN_00682640(IStorage* storage, int key, const char* text)
{
    wchar_t wide[128];
    MultiByteToWideChar(CP_ACP, 0, text, -1, wide, 128);

    IStreamPtr stream;
    HRESULT hr = storage->CreateStream(StreamNameForKey(key), STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Write(wide, (wcslen(wide) + 1) * sizeof(wchar_t), NULL);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Commit(STGC_DEFAULT);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}
