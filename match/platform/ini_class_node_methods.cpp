// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | TS++-cross-check
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI. RA1's CODE/INI.CPP and
//   the TS++ headers supplied member and function NAMES only.
//
// The INI node cluster, bodies ascending by retail address.

// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
// Ob2 inlines native GenericList construction into List<INIEntry*>.
#include "ini_class_node_methods.h"
#include "../_layout/straw.h"
#include "../_layout/memory_buffer.h"

// FUNCTION: GAMEMD 0x40E320
GenericNode::GenericNode()
{
    NextNode = 0;
    PrevNode = 0;
    Vtable = &GG_VTABLE_GENERIC_NODE_SLOTS;
}

// Cut an INI line short at its first comment character and trim what is left.
// A missing semicolon leaves the line untouched, which is why the trim is
// inside the second guard rather than after it.
//
// FUNCTION: GAMEMD 0x52AA90
void __fastcall INIClass::Strip_Comments(char* buffer)
{
    if (buffer != 0) {
        char* comment = FUN_007CAF30(buffer, ';');
        if (comment != 0) {
            *comment = '\0';
            FUN_00727CF0(buffer);
        }
    }
}

// True when a line is a section header: skip any leading whitespace, then
// require an opening bracket and a closing bracket somewhere after it. The
// whitespace test is an unsigned byte compare against a space, not an
// `isspace` table lookup.
//
// FUNCTION: GAMEMD 0x52AAC0
bool __fastcall INIClass::Line_Contains_Section(char* buffer)
{
    if (buffer != 0) {
        while (*buffer != '\0' && (unsigned char)*buffer <= ' ') {
            buffer++;
        }

        if (*buffer == '[' && FUN_007CAF30(buffer, ']') != 0) {
            return true;
        }
    }

    return false;
}

// INIClass::INIEntry::~INIEntry - release the key, the value, the retained
// comment chain and the trailing comment text, then unlink the node. The
// comment chain's text was allocated by the CRT while the chain cells came off
// the game heap, so the two walk to different deallocators.
//
// FUNCTION: GAMEMD 0x52AAF0
void INIClass::INIEntry::DestroyEntry()
{
    Vtable = &GG_VTABLE_INIENTRY;

    FUN_007C93E8(Entry);
    Entry = 0;
    FUN_007C93E8(Value);
    Value = 0;

    while (Comments != 0) {
        FUN_007C93E8(Comments->Comment);
        INIComment* next = Comments->Next;
        FUN_007C8B3D(Comments);
        Comments = next;
    }

    FUN_007C93E8(CommentString);
    CommentString = 0;

    DestroyNode();
}

// INIClass::INISection::~INISection - release the section name, delete every
// entry through its own virtual destructor, empty the entry index, drain the
// section's comment chain, and then let the members go: the index again, the
// list and its two sentinels, and finally the node itself.
//
// FUNCTION: GAMEMD 0x52AB80
void INIClass::INISection::DestroySection()
{
    Vtable = &GG_VTABLE_INISECTION;

    FUN_007C93E8(Section);
    Section = 0;

    while (FirstEntry()->IsValid()) {
        INIEntry* ptr = FirstEntry();
        if (ptr != 0) {
            ((GG_Deletable*)ptr)->DeletingDestructor(1);
        }
    }

    EntryIndex.Clear();

    while (Comments != 0) {
        FUN_007C93E8(Comments->Comment);
        INIComment* next = Comments->Next;
        FUN_007C8B3D(Comments);
        Comments = next;
    }

    EntryIndex.Clear();
    EntryList.DestroyList();
    DestroyNode();
}

// GenericList::GenericList.
//
// FUNCTION: GAMEMD 0x52ACE0
GenericList::GenericList()
{
    // FirstNode and LastNode have already run their GenericNode constructors.
    Vtable = &GG_VTABLE_GENERIC_LIST_SLOTS;
    FirstNode.Link(&LastNode);
}

// Slot zero of INIEntry's vtable. Retail carries the whole destructor expanded
// here rather than calling the out-of-line copy at 0x52AAF0, so it is spelled
// out again.
//
// FUNCTION: GAMEMD 0x52AD50
void* INIClass::INIEntry::DeletingDestructor(unsigned int flags)
{
    Vtable = &GG_VTABLE_INIENTRY;

    FUN_007C93E8(Entry);
    Entry = 0;
    FUN_007C93E8(Value);
    Value = 0;

    while (Comments != 0) {
        FUN_007C93E8(Comments->Comment);
        INIComment* next = Comments->Next;
        FUN_007C8B3D(Comments);
        Comments = next;
    }

    FUN_007C93E8(CommentString);
    CommentString = 0;

    DestroyNode();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// Slot zero of Node<INISection*>'s vtable. The node adds nothing to
// GenericNode, so the whole destructor is the base unlink.
//
// FUNCTION: GAMEMD 0x52AE20
template<> void* Node<INIClass::INISection*>::DeletingDestructor(unsigned int flags)
{
    DestroyNode();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// Slot zero of CacheStraw's vtable: clear the observed sub-object at +0x0C,
// call the Straw base routine, then free on request. This sequence does not
// establish original C++ member ownership or destructor structure.
//
// FUNCTION: GAMEMD 0x52AE70
void* CacheStraw::DeletingDestructor(unsigned int flags)
{
    Buffer.Clear();
    ((Straw*)this)->Straw::~Straw();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// CRCEngine::CRCEngine - seed the running value and clear the staging word.
//
// FUNCTION: GAMEMD 0x52AEC0
CRCEngine::CRCEngine(long initial)
{
    CRC = initial;
    Index = 0;
    StagingBuffer = 0;
}

// INIClass::INIEntry::INIEntry - the node links are cleared by the base, then
// the seven members are taken from the seven arguments. The cursor arguments
// arrive in a different order from the members they land in, which is what the
// out-of-order stores at the tail of retail's body record.
//
// FUNCTION: GAMEMD 0x52AF00
INIClass::INIEntry::INIEntry(char* entry, char* value, INIComment* comments,
                   char* commentstring, int commentcursor, int preindentcursor,
                   int postindentcursor)
{
    NextNode = 0;
    PrevNode = 0;

    Entry = entry;
    Value = value;
    Comments = comments;
    CommentString = commentstring;
    PreIndentCursor = preindentcursor;
    PostIndentCursor = postindentcursor;
    CommentCursor = commentcursor;

    Vtable = &GG_VTABLE_INIENTRY;
}

// List<INIEntry*>::List - the base list constructor with the derived seat
// written over it. cl schedules that last store into the epilogue.
//
// FUNCTION: GAMEMD 0x52AF50
template<> List<INIClass::INIEntry*>::List()
{
    Vtable = &GG_VTABLE_LISTOFINIENTRY;
}

// Slot zero of List<INIEntry*>'s vtable. The list adds no members, so the
// destructor is the base drain plus the conditional free.
//
// FUNCTION: GAMEMD 0x52AFC0
template<> void* List<INIClass::INIEntry*>::DeletingDestructor(unsigned int flags)
{
    DestroyList();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// The explicit-vptr model uses a one-slot member-function-pointer cell. VC6's
// single-inheritance representation is one relocated function address, checked
// slot-for-slot against retail; no call adapter is involved.
// VTABLE: GAMEMD 0x7EB744 -- List<INIClass::INIEntry*>.
INIEntryListDeletingSlot GG_VTABLE_LISTOFINIENTRY =
    &List<INIClass::INIEntry*>::DeletingDestructor;
GG_STATIC_ASSERT(sizeof(INIEntryListDeletingSlot) == 4);
