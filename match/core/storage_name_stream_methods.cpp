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
_COM_SMARTPTR_TYPEDEF(IPropertyStorage, __uuidof(IPropertyStorage));

// GLOBAL: GAMEMD 0x7F7D10 -- the property set format id the readers open.
extern const FMTID DAT_007F7D10;

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

// FUNCTION: GAMEMD 0x682150
// The reader that pairs with the writer below: open the named stream, read wide characters
// two bytes at a time up to the terminator, then narrow the text into the caller's buffer.
// __stdcall; the storage, the key and the output buffer (127 characters at most).
HRESULT __stdcall FUN_00682150(IStorage* storage, int key, char* out)
{
    wchar_t wide[128];
    IStreamPtr stream;
    *out = 0;
    HRESULT hr = storage->OpenStream(StreamNameForKey(key), 0, STGM_SHARE_EXCLUSIVE, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    wchar_t* p = wide;
    for (;;) {
        hr = stream->Read(p, 2, NULL);
        if (FAILED(hr)) {
            return hr;
        }
        if (*p == 0) {
            break;
        }
        p++;
    }
    WideCharToMultiByte(CP_ACP, 0, wide, -1, out, 127, NULL, NULL);
    return hr;
}

// FUNCTION: GAMEMD 0x682240
// The wide form of the reader above: the characters land straight in the caller's buffer.
HRESULT __stdcall FUN_00682240(IStorage* storage, int key, wchar_t* out)
{
    IStreamPtr stream;
    *out = 0;
    HRESULT hr = storage->OpenStream(StreamNameForKey(key), 0, STGM_SHARE_EXCLUSIVE, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    for (;;) {
        hr = stream->Read(out, 2, NULL);
        if (FAILED(hr)) {
            return hr;
        }
        if (*out == 0) {
            break;
        }
        out++;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x6822F0
// Open the property set and read one string property by id, narrowing it into the caller's
// buffer when it is a wide string. __stdcall; the property sets, the property id and the
// output buffer (128 bytes).
HRESULT __stdcall FUN_006822F0(IPropertySetStorage* sets, int propid, char* out)
{
    IPropertyStoragePtr props;
    *out = 0;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        return hr;
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    hr = props->ReadMultiple(1, &spec, &value);
    if (FAILED(hr)) {
        return hr;
    }
    if (value.vt == VT_LPWSTR) {
        WideCharToMultiByte(CP_ACP, 0, value.pwszVal, -1, out, 128, NULL, NULL);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x6823D0
// As the reader above, but a wide string property is copied as wide characters.
HRESULT __stdcall FUN_006823D0(IPropertySetStorage* sets, int propid, wchar_t* out)
{
    IPropertyStoragePtr props;
    *out = 0;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        return hr;
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    hr = props->ReadMultiple(1, &spec, &value);
    if (FAILED(hr)) {
        return hr;
    }
    if (value.vt == VT_LPWSTR) {
        wcsncpy(out, value.pwszVal, 128);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x6824B0
// Read the four-byte value stored in the named stream.
HRESULT __stdcall FUN_006824B0(IStorage* storage, int key, int* out)
{
    IStreamPtr stream;
    *out = 0;
    HRESULT hr = storage->OpenStream(StreamNameForKey(key), 0, STGM_SHARE_EXCLUSIVE, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Read(out, 4, NULL);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682570
// Read an integer property by id.
HRESULT __stdcall FUN_00682570(IPropertySetStorage* sets, int propid, int* out)
{
    IPropertyStoragePtr props;
    *out = 0;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        return hr;
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    hr = props->ReadMultiple(1, &spec, &value);
    if (FAILED(hr)) {
        return hr;
    }
    if (value.vt == VT_I4) {
        *out = value.lVal;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682780
// Write a wide string, terminator included, into a named stream and commit it.
// PARTIAL: 98.1% -- after the Write call retail reloads the stream pointer before popping EDI/EBX;
// here the reload follows the pops (two instructions swapped). Tried: byte count in a local,
// 2 * length + 2, (length + 1) * 2.
HRESULT __stdcall FUN_00682780(IStorage* storage, int key, const wchar_t* text)
{
    IStreamPtr stream;
    HRESULT hr = storage->CreateStream(StreamNameForKey(key), STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Write(text, (wcslen(text) + 1) * sizeof(wchar_t), NULL);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Commit(STGC_DEFAULT);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682A90
// Write a four-byte value into a named stream and commit it.
HRESULT __stdcall FUN_00682A90(IStorage* storage, int key, int value)
{
    IStreamPtr stream;
    HRESULT hr = storage->CreateStream(StreamNameForKey(key), STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Write(&value, 4, NULL);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Commit(STGC_DEFAULT);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682880
// Store a string property by id, widening the text first. The property set is opened, or
// created when it cannot be opened. __stdcall; the property sets, the property id and the text.
// PARTIAL: 92.6% -- the same instructions, but retail loads the property sets pointer into ESI and
// delays the smart pointer's zeroing until after the first pushes; cl emits the zeroing first.
// Tried: separate hr declaration, smart pointer declared before the buffer, local copy of sets.
HRESULT __stdcall FUN_00682880(IPropertySetStorage* sets, int propid, const char* text)
{
    wchar_t wide[128];
    MultiByteToWideChar(CP_ACP, 0, text, -1, wide, 128);

    IPropertyStoragePtr props;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        hr = sets->Create(DAT_007F7D10, NULL, 0, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
        if (FAILED(hr)) {
            return hr;
        }
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    value.vt = VT_LPWSTR;
    value.pwszVal = wide;
    hr = props->WriteMultiple(1, &spec, &value, 2);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x6829A0
// As the writer above, for text that is already wide.
HRESULT __stdcall FUN_006829A0(IPropertySetStorage* sets, int propid, wchar_t* text)
{
    IPropertyStoragePtr props;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        hr = sets->Create(DAT_007F7D10, NULL, 0, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
        if (FAILED(hr)) {
            return hr;
        }
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    value.vt = VT_LPWSTR;
    value.pwszVal = text;
    hr = props->WriteMultiple(1, &spec, &value, 2);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682B80
// Store an integer property by id (opening the property set, or creating it).
HRESULT __stdcall FUN_00682B80(IPropertySetStorage* sets, int propid, int number)
{
    IPropertyStoragePtr props;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        hr = sets->Create(DAT_007F7D10, NULL, 0, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
        if (FAILED(hr)) {
            return hr;
        }
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    value.vt = VT_I4;
    value.lVal = number;
    hr = props->WriteMultiple(1, &spec, &value, 2);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682C70
// Read the eight-byte time stored in the named stream.
HRESULT __stdcall FUN_00682C70(IStorage* storage, int key, FILETIME* out)
{
    IStreamPtr stream;
    out->dwLowDateTime = 0;
    out->dwHighDateTime = 0;
    HRESULT hr = storage->OpenStream(StreamNameForKey(key), 0, STGM_SHARE_EXCLUSIVE, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Read(out, 8, NULL);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682D30
// Read a time property by id; the output stays zero unless the property is a file time.
HRESULT __stdcall FUN_00682D30(IPropertySetStorage* sets, int propid, FILETIME* out)
{
    IPropertyStoragePtr props;
    out->dwLowDateTime = 0;
    out->dwHighDateTime = 0;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        return hr;
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    hr = props->ReadMultiple(1, &spec, &value);
    if (FAILED(hr)) {
        return hr;
    }
    if (value.vt == VT_FILETIME) {
        *out = value.filetime;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682E10
// Write an eight-byte time into a named stream and commit it.
HRESULT __stdcall FUN_00682E10(IStorage* storage, int key, const FILETIME* time)
{
    IStreamPtr stream;
    HRESULT hr = storage->CreateStream(StreamNameForKey(key), STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &stream);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Write(time, 8, NULL);
    if (FAILED(hr)) {
        return hr;
    }
    hr = stream->Commit(STGC_DEFAULT);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x682F00
// Store a time property by id (opening the property set, or creating it).
HRESULT __stdcall FUN_00682F00(IPropertySetStorage* sets, int propid, const FILETIME* time)
{
    IPropertyStoragePtr props;
    HRESULT hr = sets->Open(DAT_007F7D10, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
    if (FAILED(hr)) {
        hr = sets->Create(DAT_007F7D10, NULL, 0, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &props);
        if (FAILED(hr)) {
            return hr;
        }
    }
    PROPSPEC spec;
    spec.ulKind = PRSPEC_PROPID;
    spec.propid = propid;
    PROPVARIANT value;
    value.vt = VT_FILETIME;
    value.filetime = *time;
    hr = props->WriteMultiple(1, &spec, &value, 2);
    if (FAILED(hr)) {
        return hr;
    }
    return hr;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F7D10
extern const FMTID DAT_007F7D10 = {0xF29F85E0, 0x4FF9, 0x1068, {0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9}};
// END defined globals
