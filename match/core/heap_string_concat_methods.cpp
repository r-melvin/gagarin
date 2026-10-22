// Provenance: own-binary-via-Ghidra
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x7B4DA0 and 0x7B4ED0: __thiscall, `RET 8` (hidden return slot plus
//   one operand), operator new 0x7C8E17 / operator delete 0x7C8B3D, and the
//   shared empty string 0x889F64 substituted for a null right-hand text.
//
// A one-pointer heap string: copy-constructed by strlen+1/new/strcpy, grown
// by allocating old+new+1 and strcat, released with operator delete.
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64 -- the shared empty string.
extern const char STR_00889F64[];

class HeapString
{
public:
    HeapString(const HeapString& other)
    {
        Text = 0;
        if (other.Text) {
            Text = new char[strlen(other.Text) + 1];
            strcpy(Text, other.Text);
        }
    }
    ~HeapString()
    {
        if (Text) {
            delete Text;
        }
    }
    const char* CStr() const
    {
        return Text == 0 ? STR_00889F64 : Text;
    }
    HeapString& operator+=(const char* text)
    {
        if (text) {
            char* old = Text;
            int length = strlen(text) + 1;
            if (old) {
                length += strlen(old);
            }
            Text = new char[length];
            if (old) {
                strcpy(Text, old);
            } else {
                Text[0] = '\0';
            }
            strcat(Text, text);
            if (old) {
                delete old;
            }
        }
        return *this;
    }

    HeapString operator+(const char* text) const;
    HeapString operator+(const HeapString& other) const;

    char* Text;   // +0x00
};
GG_STATIC_ASSERT(offsetof(HeapString, Text) == 0x00);

// FUNCTION: GAMEMD 0x7B4DA0
HeapString HeapString::operator+(const char* text) const
{
    HeapString result(*this);
    result += text;
    return result;
}

// FUNCTION: GAMEMD 0x7B4ED0
HeapString HeapString::operator+(const HeapString& other) const
{
    HeapString result(*this);
    result += other.CStr();
    return result;
}
