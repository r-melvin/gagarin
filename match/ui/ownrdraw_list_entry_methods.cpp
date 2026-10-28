// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x624460 destroys the two wide strings at +0x08 and +0x04 of a list entry, in that
//   order, through the string destructor 0x7B6760; 0x6247D0 is its copy constructor.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

class WideString_006255F0
{
public:
    unsigned short* Buffer;   // +0x00

    // FUNCTION: GAMEMD 0x7B66C0 (decl; reloc)
    WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B6760 (decl; reloc)
    ~WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B6720 (decl; reloc)
    WideString_006255F0(const WideString_006255F0& other);
};

struct ListEntry_006255F0
{
    int Id;                       // +0x00
    WideString_006255F0 Name;     // +0x04
    WideString_006255F0 Text;     // +0x08
    int unknown_0C;               // +0x0C
    int unknown_10;               // +0x10
    int unknown_14;               // +0x14

    ListEntry_006255F0(const ListEntry_006255F0& other);
    ~ListEntry_006255F0();
};

// FUNCTION: GAMEMD 0x624460
ListEntry_006255F0::~ListEntry_006255F0()
{
}

// FUNCTION: GAMEMD 0x6247D0
ListEntry_006255F0::ListEntry_006255F0(const ListEntry_006255F0& other)
    : Id(other.Id), Name(other.Name), Text(other.Text),
      unknown_0C(other.unknown_0C), unknown_10(other.unknown_10), unknown_14(other.unknown_14)
{
}
