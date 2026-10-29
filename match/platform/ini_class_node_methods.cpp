// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI.
//
// The INI node cluster, bodies ascending by retail address.

// Ob2 inlines native GenericList construction into List<INIEntry*>.
#include "ini_class_node_methods.h"

// FUNCTION: GAMEMD 0x40E320
GenericNode::GenericNode()
    : NextNode(0), PrevNode(0)
{
}

// Insert `node` after this node, first taking it out of whatever list holds it.
//
// FUNCTION: GAMEMD 0x40E340
void GenericNode::Link(GenericNode* node)
{
    node->Unlink();
    node->NextNode = NextNode;
    node->PrevNode = this;
    if (NextNode != 0) {
        NextNode->PrevNode = node;
    }
    NextNode = node;
}

// GenericList::GenericList - link the head sentinel to the tail sentinel.
//
// FUNCTION: GAMEMD 0x52ACE0
GenericList::GenericList()
{
    FirstNode.Link(&LastNode);
}

// Cut an INI line short at its first comment character and trim what is left.
// A missing semicolon leaves the line untouched, which is why the trim is
// inside the second guard rather than after it.
//
// FUNCTION: GAMEMD 0x52AA90
void INIClass::FUN_0052AA90(char* buffer)
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
bool INIClass::FUN_0052AAC0(char* buffer)
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
// comment chain and the trailing comment text; the base unlinks the node. The
// comment chain's text was allocated by the CRT while the chain cells came off
// the game heap, so the two walk to different deallocators.
//
// FUNCTION: GAMEMD 0x52AAF0
INIClass::INIEntry::~INIEntry()
{
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
}

// INIClass::INISection::~INISection - release the section name, delete every
// entry through its own virtual destructor, empty the entry index, drain the
// section's comment chain, and then let the members go: the index again, the
// list and its two sentinels, and finally the node itself.
//
// FUNCTION: GAMEMD 0x52AB80
INIClass::INISection::~INISection()
{
    FUN_007C93E8(Section);
    Section = 0;

    while (FirstEntry()->IsValid()) {
        INIEntry* ptr = FirstEntry();
        delete ptr;
    }

    EntryIndex.Clear();

    while (Comments != 0) {
        FUN_007C93E8(Comments->Comment);
        INIComment* next = Comments->Next;
        FUN_007C8B3D(Comments);
        Comments = next;
    }

    EntryIndex.Clear();
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
    : Entry(entry), Value(value), Comments(comments), CommentString(commentstring),
      PreIndentCursor(preindentcursor), PostIndentCursor(postindentcursor),
      CommentCursor(commentcursor)
{
}

// The classes' constructors, vtables and scalar deleting destructors are
// compiler-generated; the list and node instantiations INISection keeps its
// entries and its owner list on are requested explicitly.
// SYNTHETIC: GAMEMD 0x40E390 -- GenericNode scalar deleting destructor (vtable 0x7E1B0C).
// SYNTHETIC: GAMEMD 0x40E3E0 -- GenericList scalar deleting destructor (vtable 0x7E1B04).
// SYNTHETIC: GAMEMD 0x52AD50 -- INIEntry scalar deleting destructor (vtable 0x7EB734).
// SYNTHETIC: GAMEMD 0x52AE00 -- INISection scalar deleting destructor (vtable 0x7EB73C).
// SYNTHETIC: GAMEMD 0x52AE20 -- Node<INISection*> scalar deleting destructor (vtable 0x7EB74C).
// SYNTHETIC: GAMEMD 0x52AF50 -- List<INIEntry*> constructor.
// SYNTHETIC: GAMEMD 0x52AFC0 -- List<INIEntry*> scalar deleting destructor (vtable 0x7EB744).
template class List<INIClass::INIEntry*>;
template class Node<INIClass::INISection*>;
