// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   The gadget class family of the UI input/controls module as one hierarchy:
//
//     LinkClass > GadgetClass > ControlClass > ToggleClass > ShapeButtonClass, TextButtonClass
//                                            > GaugeClass  > TriColorGaugeClass, SliderClass
//                                            > ListClass   > CheckListClass, ColorListClass
//                                            > EditClass   > DropListClass
//                             > StaticButtonClass, TextLabelClass
//
//   Bases are the RTTI chains read from retail gamemd.exe v1.001. Virtual slot order comes from the retail
//   vtables (0x7E92BC Gadget, 0x7E528C Control, 0x7E8118 Toggle, 0x7E8088 ShapeButton, 0x7F55DC TextButton,
//   0x7E9384 Gauge, 0x7E9430 TriColorGauge, 0x7ED21C Slider, 0x7ED10C List, 0x7E4F84 CheckList,
//   0x7E5054 ColorList, 0x7E81A4 Edit, 0x7E7FCC DropList, 0x7F3EA0 StaticButton, 0x7F5B44 TextLabel); the
//   Gadget, List, ColorList, DropList and StaticButton tables are checked slot for slot by the vtable rows.
//   Members are pinned by the constructor stores (0x4E12F0 Gadget, 0x48E520 Control, 0x723E60 Toggle,
//   0x69DD30 ShapeButton, 0x4E2500 Gauge, 0x4E2A50 TriColorGauge, 0x6B1B20 Slider, 0x557230 List,
//   0x488760 ColorList, 0x4C2FC0 Edit, 0x4B4E10 DropList, 0x6C6540 StaticButton) and by the method bodies in
//   the lists_* and controls_* sources.
//
//   This header supersedes the per-cluster copies of these classes; it is not to be included together with
//   control_class.h, toggle_class_methods.h, shape_button_class.h or the
//   list headers there, which retain separate derived-class declarations. GadgetClass is shared below.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_UI_GADGET_H
#define GG_MATCH_UI_INPUT_CONTROLS_UI_GADGET_H

#include "ui_common.h"
#include "../../core/link_class_methods.h"
#include "../../_layout/memory_buffer.h"
#include "../../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8B3D operator delete
void __cdecl operator delete(void* block);

class GadgetClass;
// GLOBAL: GAMEMD 0x8B3E88 -- the gadget that captured the mouse.
extern GadgetClass* GadgetClass_StuckOn;
// GLOBAL: GAMEMD 0x8B3E8C -- the list head the last Input call ran for.
extern GadgetClass* GadgetClass_LastList;
// GLOBAL: GAMEMD 0x8B3E90 -- the gadget holding the keyboard focus.
extern GadgetClass* GadgetClass_Focused;
// GLOBAL: GAMEMD 0x8B3E94 -- the gadget under the pointer.
extern GadgetClass* GadgetClass_Hovered;

// GadgetClass uses the shared canonical declaration.
#include "../gadget_class_methods.h"

// VTABLE: GAMEMD 0x007E528C
class ControlClass : public GadgetClass
{
public:
    ControlClass(int id, int x, int y, int w, int h, unsigned flags, char sticky);   // 0x48E520

    virtual unsigned GetID();                                                // 0x44  0x48E610
    virtual int  Draw(int forced);                                           // 0x6C  0x48E620
    virtual int  Action(unsigned flags, unsigned* key, int modifier);        // 0x7C  0x48E5A0
    virtual void SetPeer(GadgetClass* peer);                                 // 0x84  0x48E600 (new slot 33)

    unsigned     ID;      // +0x24
    GadgetClass* Peer;    // +0x28  stored by 0x48E600; Draw (0x48E620) redraws it through slot +0x6C
};
GG_STATIC_ASSERT(offsetof(ControlClass, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(ControlClass, Peer) == 0x28);
GG_STATIC_ASSERT(sizeof(ControlClass) == 0x2C);   // the Toggle/Gauge/List/Edit members start at +0x2C

// VTABLE: GAMEMD 0x007E8118
class ToggleClass : public ControlClass
{
public:
    ToggleClass(int id, int x, int y, int width, int height);   // 0x723E60: Control(id, x, y, w, h, 5, 1)

    virtual int Action(unsigned flags, unsigned* key, int modifier);   // 0x7C  0x723EC0

    void TurnOn();    // 0x723EA0
    void TurnOff();   // 0x723EB0

    unsigned char unknown_2C;   // +0x2C  set on press, cleared on release (Action 0x723EC0)
    unsigned char IsOn;        // +0x2D  TurnOn/TurnOff
    unsigned char unknown_2E[2];
    int           unknown_30;  // +0x30  1: a release flips IsOn, 2: a release latches it on
};
GG_STATIC_ASSERT(offsetof(ToggleClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(ToggleClass, IsOn) == 0x2D);
GG_STATIC_ASSERT(offsetof(ToggleClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(sizeof(ToggleClass) == 0x34);   // ShapeButton/TextButton members start at +0x34

// The ShapeButton declaration is shared with the standalone method owner.
#include "../shape_button_class.h"

// VTABLE: GAMEMD 0x007F55DC
class TextButtonClass : public ToggleClass
{
public:
    virtual int  Draw(int forced);                            // 0x6C  0x71FFE0
    virtual void SetText(const wchar_t* text, bool resize);   // 0x88  0x720020 (new slot 34)
    virtual void SetPrintFlags(int flags);                    // 0x8C  0x720200
    virtual void vf_36();                            // 0x90  0x720070
    virtual void DrawText(const wchar_t* text);               // 0x94  0x720140

    unsigned char  HasOutline;     // +0x34  vf_36 draws an outline when set
    unsigned char  unknown_35;   // +0x35  vf_36 draws nothing when set
    unsigned char  unknown_36[2];
    const wchar_t* Text;           // +0x38
    int            unknown_3C;     // +0x3C

    TextButtonClass();   // 0x71FFB0: ToggleClass(0, 0, 0, 0, 0), then text cleared and mode 2
};
GG_STATIC_ASSERT(offsetof(TextButtonClass, HasOutline) == 0x34);
GG_STATIC_ASSERT(offsetof(TextButtonClass, unknown_35) == 0x35);
GG_STATIC_ASSERT(offsetof(TextButtonClass, Text) == 0x38);
GG_STATIC_ASSERT(offsetof(TextButtonClass, unknown_3C) == 0x3C);

// VTABLE: GAMEMD 0x007E9384
class GaugeClass : public ControlClass
{
public:
    GaugeClass(int id, int x, int y, int w, int h);   // 0x4E2500: Control(id, x, y, w, h, 7, 1)

    virtual int  Draw(int forced);                                      // 0x6C  0x4E2690
    virtual int  Action(unsigned flags, unsigned* key, int modifier);   // 0x7C  0x4E2830
    virtual int  vf_34(int maximum);     // 0x88  0x4E2580 (new slot 34)
    virtual int  SetValue(int value);         // 0x8C  0x4E25A0
    virtual int  GetValue();                  // 0x90  0x4E30A0
    virtual void vf_37(int use);           // 0x94  0x4E30B0
    virtual int  vf_38();               // 0x98  0x4E30C0
    virtual void vf_39();                 // 0x9C  0x4E29A0
    virtual int  vf_40(int pixel);     // 0xA0  0x4E25D0
    virtual int  vf_41(int value);     // 0xA4  0x4E2650

    unsigned char unknown_2C;       // +0x2C  Draw gates the bar on it
    unsigned char unknown_2D;       // +0x2D  vf_37 / Draw / Action
    unsigned char unknown_2E;   // +0x2E  selects the X or Y axis
    unsigned char unknown_2F;
    int           Maximum;        // +0x30
    int           Value;          // +0x34
    int           unknown_38;     // +0x38  Action

    // The pointer position along the gauge's axis (Action reads it four times).
    int MouseAlongAxis() const
    {
        return unknown_2E ? DAT_00887640->GetX() : DAT_00887640->GetY();
    }
};
GG_STATIC_ASSERT(offsetof(GaugeClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(GaugeClass, unknown_2D) == 0x2D);
GG_STATIC_ASSERT(offsetof(GaugeClass, unknown_2E) == 0x2E);
GG_STATIC_ASSERT(offsetof(GaugeClass, Maximum) == 0x30);
GG_STATIC_ASSERT(offsetof(GaugeClass, Value) == 0x34);
GG_STATIC_ASSERT(offsetof(GaugeClass, unknown_38) == 0x38);

// VTABLE: GAMEMD 0x007E9430
class TriColorGaugeClass : public GaugeClass
{
public:
    virtual int Draw(int forced);             // 0x6C  0x4E2B50
    virtual int vf_42(int limit);       // 0xA8  0x4E2AF0 (new slot 42)
    virtual int vf_43(int limit);    // 0xAC  0x4E2B20

    int unknown_3C;       // +0x3C
    int unknown_40;    // +0x40
};
GG_STATIC_ASSERT(offsetof(TriColorGaugeClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(TriColorGaugeClass, unknown_40) == 0x40);

// VTABLE: GAMEMD 0x007ED21C
class SliderClass : public GaugeClass
{
public:
    // 0x6B1B20: Gauge(id, x, y, w, h); +0x44 = (last argument != 0); when it is clear the plus and minus
    // ShapeButtons are allocated (0x60 bytes each) into +0x3C/+0x40 and peered to the slider.
    SliderClass(int id, int x, int y, int w, int h, int belt);
    virtual ~SliderClass();                                             // 0x00  0x6B1D00 body
    virtual void PeerToPeer(unsigned flags, unsigned* key, GadgetClass* source);  // 0x4C  0x6B2160
    virtual int  Draw(int forced);                                      // 0x6C  0x6B20F0
    virtual int  Action(unsigned flags, unsigned* key, int modifier);   // 0x7C  0x6B1F50
    virtual int  vf_34(int maximum);                               // 0x88  0x6B1D40
    virtual int  SetValue(int value);                                   // 0x8C  0x6B1E50
    virtual int  vf_38();                                         // 0x98  0x558120
    virtual void vf_39();                                           // 0x9C  0x6B2070
    virtual void vf_42(int size);   // 0xA8  0x6B1DC0 (new slot 42)
    virtual int  Bump(int up);             // 0xAC  0x6B2000
    virtual int  Step(int up);             // 0xB0  0x6B2040

    // The thumb length and start in pixels from the current range, value and thumb size.
    void SyncThumb()
    {
        int length = unknown_2E ? Width : Height;
        int raw = (int)((double)unknown_48 / Maximum * length);
        int pixels = raw > 4 ? raw : 4;
        unknown_4C = pixels;
        int start = (int)((double)Value / Maximum * length);
        unknown_50 = start < length - pixels ? start : length - pixels;
    }


    GadgetClass*  unknown_3C;    // +0x3C  deleted by the destructor 0x6B1D00
    GadgetClass*  unknown_40;   // +0x40
    unsigned char unknown_44;    // +0x44  constructor flag; gates the box-and-thumb path in Draw
    unsigned char unknown_45[3];
    int           unknown_48;     // +0x48  in value units
    int           unknown_4C;   // +0x4C  in pixels (vf_38 returns it)
    int           unknown_50;    // +0x50  in pixels
};
GG_STATIC_ASSERT(offsetof(SliderClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(SliderClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(SliderClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(SliderClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(SliderClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(SliderClass, unknown_50) == 0x50);
GG_STATIC_ASSERT(sizeof(SliderClass) == 0x54);   // ListClass::Scroller +0x118, SelectedIndex +0x16C

// The list's entry vector: the canonical DynamicVectorClass<wchar_t const*> (its destructor reseats 0x7ED1FC, which
// RTTI names VectorClass<unsigned short const*>; VC6's wchar_t is unsigned short).
typedef DynamicVectorClass<wchar_t const*> TextDynVector;
GG_STATIC_ASSERT(sizeof(TextDynVector) == 0x18);   // List +0x34, LineHeight +0x4C

// VTABLE: GAMEMD 0x007ED10C
class ListClass : public ControlClass
{
public:
    ListClass(int id, int x, int y, int w, int h, unsigned textFlags, void const* upShape,
              void const* downShape);                           // 0x557230
    // 0x558060 is the compiler's scalar deleting destructor with this body expanded in it (the out-of-line copy
    // is 0x557600, which the derived destructors call).
    virtual ~ListClass();                                       // 0x00  0x558060 (ordinary destructor defined in lists_list.cpp)
    virtual LinkClass* Add(LinkClass& object);                  // 0x0C  0x557E10
    virtual LinkClass* AddTail(LinkClass& object);              // 0x10  0x557EB0
    virtual LinkClass* AddHead(LinkClass& object);              // 0x14  0x557E60
    virtual LinkClass* Remove();                                // 0x24  0x557F00
    virtual void       MarkRedraw();                            // 0x48  0x557FD0
    virtual void       PeerToPeer(unsigned flags, unsigned* key, GadgetClass* source);  // 0x4C  0x557B10
    virtual void       SetPosition(int x, int y);               // 0x64  0x557570
    virtual int        Draw(int forced);                        // 0x6C  0x557920
    virtual int        Action(unsigned flags, unsigned* key, int modifier);  // 0x7C  0x557830
    virtual int        AddItem(wchar_t const* text);            // 0x88  0x5576A0 (new slot 34)
    virtual int        EnableScrollBar();                       // 0x8C  0x557BE0
    virtual void       Bump(int minus);                         // 0x90  0x557A20
    virtual int        GetCount();                              // 0x94  0x4886B0
    virtual int        GetSelectedIndex();                      // 0x98  0x557B00
    virtual wchar_t const* GetCurrentItem();                    // 0x9C  0x557AE0
    virtual wchar_t const* GetItem(int index);                  // 0xA0  0x557AC0
    virtual int        StepSelectedIndex(int delta);            // 0xA4  0x557FB0
    // VC6 lays overloaded virtuals out in reverse declaration order: the text overload is declared first so that
    // RemoveItem(int) takes slot 0xA8 and RemoveItem(text) slot 0xAC.
    virtual void       RemoveItem(wchar_t const* text);         // 0xAC  0x557800
    virtual void       RemoveItem(int index);                   // 0xA8  0x557730
    virtual int        DisableScrollBar()                       // 0xB0  0x557CB0 (inline in the retail TU)
    {
        if (IsScrollActive) {
            Width += Scroller.Width;
            IsScrollActive = false;
            Scroller.Remove();
            UpButton.Remove();
            DownButton.Remove();
            MarkRedraw();
            return 1;
        }
        return 0;
    }
    virtual void       SetSelectedText(wchar_t const* text);    // 0xB4  0x558010
    virtual void       vf_46(int index);             // 0xB8  0x557F40
    virtual void       vf_47(int tabStops);                       // 0xBC  0x557D10
    virtual int        SetViewIndex(int index);                 // 0xC0  0x557B70
    virtual void       Step(int minus);                         // 0xC4  0x557A70
    virtual void       DrawItem(int index, int x, int y, int width, int selected);  // 0xC8  0x557D20

    unsigned         TextFlags;        // +0x2C  TextPrintType
    int              Tabs;             // +0x30
    TextDynVector    List;             // +0x34
    int              LineHeight;       // +0x4C
    int              LineCount;        // +0x50
    bool             IsScrollActive;   // +0x54
    ShapeButtonClass UpButton;         // +0x58
    ShapeButtonClass DownButton;       // +0xB8
    SliderClass      Scroller;         // +0x118
    int              SelectedIndex;    // +0x16C
    int              CurrentTopIndex;  // +0x170
};
GG_STATIC_ASSERT(offsetof(ListClass, TextFlags) == 0x2C);
GG_STATIC_ASSERT(offsetof(ListClass, Tabs) == 0x30);
GG_STATIC_ASSERT(offsetof(ListClass, List) == 0x34);
GG_STATIC_ASSERT(offsetof(ListClass, LineHeight) == 0x4C);
GG_STATIC_ASSERT(offsetof(ListClass, LineCount) == 0x50);
GG_STATIC_ASSERT(offsetof(ListClass, IsScrollActive) == 0x54);
GG_STATIC_ASSERT(offsetof(ListClass, UpButton) == 0x58);
GG_STATIC_ASSERT(offsetof(ListClass, DownButton) == 0xB8);
GG_STATIC_ASSERT(offsetof(ListClass, Scroller) == 0x118);
GG_STATIC_ASSERT(offsetof(ListClass, SelectedIndex) == 0x16C);
GG_STATIC_ASSERT(offsetof(ListClass, CurrentTopIndex) == 0x170);
GG_STATIC_ASSERT(sizeof(ListClass) == 0x174);   // CheckListClass::IsReadOnly / ColorListClass::Colors at +0x174

// One entry of a CheckListClass: the string and its check state (the entry's pointer lives in the text vector).
struct CheckItemClass
{
    wchar_t const* Text;       // +0x00
    bool           IsChecked;  // +0x04
};
GG_STATIC_ASSERT(offsetof(CheckItemClass, IsChecked) == 0x04);

// VTABLE: GAMEMD 0x007E4F84 (declared for the call views; not emitted by this module)
class CheckListClass : public ListClass
{
public:
    virtual ~CheckListClass();                                            // 0x00  0x4886E0
    virtual int        Action(unsigned flags, unsigned* key, int modifier);  // 0x7C  0x4884A0
    virtual int        AddItem(wchar_t const* text);                      // 0x88  0x488310
    virtual wchar_t const* GetCurrentItem();                              // 0x9C  0x488350
    virtual wchar_t const* GetItem(int index);                            // 0xA0  0x488360
    virtual void       RemoveItem(wchar_t const* text);                   // 0xAC  0x488380
    virtual void       RemoveItem(int index);                             // 0xA8  0x4886C0
    virtual void       SetSelectedText(wchar_t const* text);              // 0xB4  0x4883F0
    virtual void       vf_46(int index);                       // 0xB8  0x4886D0
    virtual void       DrawItem(int index, int x, int y, int width, int selected);  // 0xC8  0x488520

    bool IsReadOnly;   // +0x174
};
GG_STATIC_ASSERT(offsetof(CheckListClass, IsReadOnly) == 0x174);

// Vector of colour-scheme indices (DynamicVectorClass<int> over VectorClass<int>).
struct Obj_007E4DB8
{
    Obj_007E4DB8() { Vector = 0; VectorMax = 0; IsValid = true; IsAllocated = false; }
    virtual ~Obj_007E4DB8() { Obj_007E4DB8::Clear(); }
    virtual bool operator==(Obj_007E4DB8 const& other) const;
    virtual bool Resize(int capacity, int const* array);
    virtual void Clear()
    {
        if (Vector && IsAllocated) {
            delete Vector;
            Vector = 0;
        }
        IsAllocated = false;
        VectorMax = 0;
    }
    virtual int  ID(int const& object) const;

    int*  Vector;       // +0x04
    int   VectorMax;    // +0x08
    bool  IsValid;      // +0x0C
    bool  IsAllocated;  // +0x0D
};

struct ColorDynVector : public Obj_007E4DB8
{
    ColorDynVector() { unknown_14 = 10; ActiveCount = 0; }

    int ActiveCount;  // +0x10
    int unknown_14;   // +0x14

    int& operator[](int index) { return Vector[index]; }

    // Expanded by ColorListClass 0x488850 and 0x4888B0/0x488910.
    bool Add(const int& object)
    {
        if (ActiveCount >= VectorMax) {
            if ((IsAllocated || !VectorMax) && unknown_14 > 0) {
                if (!Resize(VectorMax + unknown_14, 0))
                    return false;
            } else {
                return false;
            }
        }
        int index = ActiveCount;
        ActiveCount = index + 1;
        Vector[index] = object;
        return true;
    }
    bool Delete(int index)
    {
        if (index < ActiveCount) {
            ActiveCount--;
            for (int i = index; i < ActiveCount; ++i)
                Vector[i] = Vector[i + 1];
        }
        return true;
    }
};
GG_STATIC_ASSERT(offsetof(ColorDynVector, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_007E4DB8, Vector) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_007E4DB8, VectorMax) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_007E4DB8, IsValid) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_007E4DB8, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(Obj_007E4DB8) == 0x10);
GG_STATIC_ASSERT(offsetof(ColorDynVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(sizeof(ColorDynVector) == 0x18);   // Style +0x18C after Colors +0x174

// VTABLE: GAMEMD 0x007E5054
class ColorListClass : public ListClass
{
public:
    ColorListClass(int id, int x, int y, int w, int h, unsigned textFlags, void const* upShape,
                   void const* downShape);                                // 0x488760
    // CALLEE: GAMEMD 0x4887F0 -- ordinary destructor; deleting entry 0x488F00 is emitted by its owning TU.
    virtual ~ColorListClass(); // ordinary 0x4887F0; deleting slot 0x488F00
    virtual int        AddItem(wchar_t const* text);                      // 0x88  0x488EE0
    virtual void       RemoveItem(wchar_t const* text);                   // 0xAC  0x4888B0
    virtual void       RemoveItem(int index);                             // 0xA8  0x488910
    virtual void       DrawItem(int index, int x, int y, int width, int selected);  // 0xC8  0x488980
    virtual int        AddItem(wchar_t const* text, int color);           // 0xCC  0x488850 (new slot 51)
    virtual void       SetStyle(int style, int selectColor);              // 0xD0  0x488960

    ColorDynVector Colors;       // +0x174
    int            Style;        // +0x18C
    int            SelectColor;  // +0x190
};
GG_STATIC_ASSERT(offsetof(ColorListClass, Colors) == 0x174);
GG_STATIC_ASSERT(offsetof(ColorListClass, Style) == 0x18C);
GG_STATIC_ASSERT(offsetof(ColorListClass, SelectColor) == 0x190);

// VTABLE: GAMEMD 0x007E81A4 (declared for the call views; not emitted by this module)
class EditClass : public ControlClass
{
public:
    // 0x4C2FC0: Control(id, x, y, w, h, 1, 0), +0x2C = textFlags without bit 8, +0x30 flags, +0x34 text,
    // +0x38 size - 1, +0x3C wcslen(text), +0x40 GetColorScheme().
    EditClass(int id, wchar_t* text, int size, unsigned textFlags, int x, int y, int w, int h,
              unsigned flags);
    virtual ~EditClass();                                                   // 0x00  0x4B57D0 (body 0x4C30B0)
    virtual void       SetFocus();                                          // 0x50  0x4C3570
    virtual int        Draw(int forced);                                    // 0x6C  0x4C3110
    virtual int        Action(unsigned flags, unsigned* key, int modifier);  // 0x7C  0x4C3190
    virtual void       SetText(wchar_t* text, int size);                    // 0x88  0x4C30E0 (new slot 34)
    virtual void       Slot35();                                            // 0x8C  0x4B55A0
    virtual void       vf_36();                                    // 0x90  0x4C32A0
    virtual void       DrawText(wchar_t const* text);                       // 0x94  0x4C32E0
    virtual bool       vf_38(int ch);                                   // 0x98  0x4C3420

    unsigned       TextFlags;   // +0x2C  TextPrintType
    unsigned       unknown_30;   // +0x30  1 letters, 2 digits, 4 symbols only, 8 upper-case
    wchar_t*       Text;        // +0x34
    unsigned       MaxLength;   // +0x38
    unsigned       Length;      // +0x3C
    int            SchemeIndex; // +0x40
    int            IsReadOnly;  // +0x44
};
GG_STATIC_ASSERT(offsetof(EditClass, TextFlags) == 0x2C);
GG_STATIC_ASSERT(offsetof(EditClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(EditClass, Text) == 0x34);
GG_STATIC_ASSERT(offsetof(EditClass, MaxLength) == 0x38);
GG_STATIC_ASSERT(offsetof(EditClass, Length) == 0x3C);
GG_STATIC_ASSERT(offsetof(EditClass, SchemeIndex) == 0x40);
GG_STATIC_ASSERT(offsetof(EditClass, IsReadOnly) == 0x44);

// VTABLE: GAMEMD 0x007E7FCC
class DropListClass : public EditClass
{
public:
    DropListClass(int id, wchar_t* text, int size, unsigned textFlags, int x, int y, int w, int listHeight,
                  void const* upShape, ShapeHeader const* dropShape);       // 0x4B4E10
    // FUNCTION: GAMEMD 0x4B55F0 (compiler-emitted scalar deleting destructor; destroys unknown_B0, unknown_50, EditClass)
    virtual ~DropListClass() {}                                             // 0x00  0x4B55F0
    virtual LinkClass* Add(LinkClass& object);                              // 0x0C  0x4B4F20
    virtual LinkClass* AddTail(LinkClass& object);                          // 0x10  0x4B4F40
    virtual LinkClass* AddHead(LinkClass& object);                          // 0x14  0x4B4F60
    virtual void       Zap();                                               // 0x20  0x4B4EE0
    virtual LinkClass* Remove();                                            // 0x24  0x4B4F80
    virtual void       PeerToPeer(unsigned flags, unsigned* key, GadgetClass* source);  // 0x4C  0x4B50C0
    virtual void       KillFocus();                                         // 0x54  0x4B50A0
    virtual void       SetPosition(int x, int y);                           // 0x64  0x4B54E0
    virtual void       Slot39();                                            // 0x9C  0x4B4FB0 (new slot 39)
    virtual void       Slot40();                                            // 0xA0  0x4B4FF0
    virtual void       Slot41();                                            // 0xA4  0x4B5010
    virtual void       SelectItem(wchar_t const* text);                     // 0xA8  0x4B5530
    virtual void       vf_43(int index);                         // 0xAC  0x4B5030
    virtual int        GetCount();                                          // 0xB0  0x4B55B0
    virtual void       Slot45();                                            // 0xB4  0x4B55D0

    bool             unknown_48;   // +0x48
    char             unknown_49[3];
    int              unknown_4C;  // +0x4C  stored by the constructor only
    ShapeButtonClass unknown_50;  // +0x50
    ListClass        unknown_B0;    // +0xB0
};
GG_STATIC_ASSERT(offsetof(DropListClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(DropListClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(DropListClass, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(DropListClass, unknown_B0) == 0xB0);

// StaticButton member/temporary cleanup at 0x6C689C and 0x6C6724 uses
// the shared MemoryBuffer destructor entry at 0x43AE50.

// VTABLE: GAMEMD 0x7F3EA0
class StaticButtonClass : public GadgetClass
{
public:
    // Not claimed: the constructor is only declared here because defining it makes the compiler emit the vtable
    // and the scalar deleting destructor (slot 0, 0x6C6880), which inlines the destructor below. Retail
    // 0x6C6540 (Gadget(x, y, w, h, 0, 0), +0x24 MemoryBuffer(0, 0), +0x30 = 0, +0x34 = flags, then SetText) /
    // 0x6C6610; expansion candidates.
    StaticButtonClass(int unused, const wchar_t* text, int flags, int x, int y, int width, int height);
    virtual ~StaticButtonClass()
    {
        if (Text)
            delete Text;
    }
    virtual int  Draw(int forced);                             // 0x6C  0x6C6640
    virtual void SetText(const wchar_t* text, bool resize);    // 0x84  0x6C6680 (new slot 33)
    virtual void vf_34();                             // 0x88  0x6C6740
    virtual void DrawText(const wchar_t* text);                // 0x8C  0x6C67F0

    MemoryBuffer Background;  // +0x24  the screen region saved behind the text
    wchar_t*       Text;        // +0x30
    int            unknown_34;  // +0x34
};
GG_STATIC_ASSERT(offsetof(StaticButtonClass, Background) == 0x24);
GG_STATIC_ASSERT(offsetof(StaticButtonClass, Text) == 0x30);
GG_STATIC_ASSERT(offsetof(StaticButtonClass, unknown_34) == 0x34);

// VTABLE: GAMEMD 0x7F5B44
class TextLabelClass : public GadgetClass
{
public:
    // FUNCTION: GAMEMD 0x72A440 -- defining it emits the vtable at 0x7F5B44.
    TextLabelClass(const wchar_t* text, int x, int y, int scheme, int unused);
    virtual int  Draw(int forced);                      // 0x6C  0x72A4A0
    virtual void SetText(const wchar_t* text);          // 0x84  0x72A660 (new slot 33)

    int            unknown_24;  // +0x24 (not read by the entries here)
    int            unknown_28;  // +0x28
    int            unknown_2C;  // +0x2C
    const wchar_t* Text;        // +0x30
    int            SchemeIndex; // +0x34
    int            MaxWidth;    // +0x38  negative: the surface width
    int            unknown_3C;  // +0x3C  passed by address to the text draw
    unsigned char  IsHidden;    // +0x40
    unsigned char  IsTyping;    // +0x41
    unsigned char  unknown_42[2];
    int            CharsShown;  // +0x44
    unsigned long  unknown_48;    // +0x48
};
GG_STATIC_ASSERT(offsetof(TextLabelClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(TextLabelClass, Text) == 0x30);
GG_STATIC_ASSERT(offsetof(TextLabelClass, SchemeIndex) == 0x34);
GG_STATIC_ASSERT(offsetof(TextLabelClass, MaxWidth) == 0x38);
GG_STATIC_ASSERT(offsetof(TextLabelClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(TextLabelClass, IsHidden) == 0x40);
GG_STATIC_ASSERT(offsetof(TextLabelClass, IsTyping) == 0x41);
GG_STATIC_ASSERT(offsetof(TextLabelClass, CharsShown) == 0x44);
GG_STATIC_ASSERT(offsetof(TextLabelClass, unknown_48) == 0x48);
// operator new is called with 0x4C at both constructor call sites (0x5D3D2B and 0x5D42D9).
GG_STATIC_ASSERT(sizeof(TextLabelClass) == 0x4C);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_UI_GADGET_H
