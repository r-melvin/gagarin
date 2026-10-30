// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Entry-point disassembly of retail gamemd.exe v1.001 at 0x5BDF70 and 0x5BE6D0 (MouseClass primary vtable 0x7E1964
//   slots 30 and 31)
//   (layout, slot and global evidence: mouse_mouse_class.h). IStream::Write is reached through vtable +0x10 and
//   OleSaveToStream through the import at 0x7E15F4.

#include "../../FUNCTION.H"
#include "../../core/pair_vector_ctor_family_methods.h"
#include "mouse_mouse_class.h"

// The stream stores a 0x10-byte value record. Its in-memory vector element is
// ZoneConnectionClass; this temporary represents only the serialized fields.
struct MapSaveItem
{
    CellStruct a;
    CellStruct b;
    unsigned char c;
    int d;
};
GG_STATIC_ASSERT(offsetof(MapSaveItem, c) == 0x08);
GG_STATIC_ASSERT(offsetof(MapSaveItem, d) == 0x0C);
GG_STATIC_ASSERT(sizeof(MapSaveItem) == 0x10);

// SYNTHETIC: GAMEMD 0x40D290
// MouseClass scalar deleting destructor, emitted from the inline destructor (partial; see mouse_mouse_class.h).

// FUNCTION: GAMEMD 0x5BDF70
// CAPPED at 84.8% (positional): identical instruction multiset except one `XOR`/`MOV` and a
// `JE`/`JNE` pair; the rest of the delta is the induction-variable shape of the bucket loop (retail keeps its counter
// in EAX and spills two stepped pointers; the indexed loop spills the counter) and the stack slots of the loop-carried
// values ([ESP+0x18..0x28]). Variants tried: for(1..3) / for(0..2) / do-while with index and with stepped pointers (the
// pointer form reaches 93.8% but is a steering alias and is not adopted); separate counters per list; block-scoped
// counters (they spill to the stream parameter's home slot like retail).
long MouseClass::vf_30(IStream* stream)
{
    int i;
    CellTags.Clear();
    ListA.Clear();

    HRESULT hr = ScrollClass::vf_30(stream);
    if (hr < 0)
        return hr;

    MouseSceneTarget* readTarget;
    hr = stream->Read(&readTarget, 4, 0);
    if (hr < 0)
        return hr;

    MouseLastTarget = MOUSE_NO_TARGET;
    vf_23();

    delete Records;
    Records = 0;
    delete[] Words;
    MapBucketTable<MapBucketA>* bucketsA = BucketsA;
    Words = 0;
    if (bucketsA) {
        if (bucketsA->Items)
            delete[] bucketsA->Items;
        delete bucketsA;
    }
    BucketsA = 0;

    for (i = 0; i < 3; i++)
        Rings[i].Clear();
    for (i = 0; i < 13; i++) {
        delete Buffers[i];
        Buffers[i] = 0;
    }
    for (i = 0; i < 3; i++) {
        MapBucketTable<MapBucketB>* buckets = BucketsB[i];
        if (buckets) {
            if (buckets->Items)
                delete[] buckets->Items;
            delete buckets;
            BucketsB[i] = 0;
        }
    }
    Owned.Clear();

    hr = stream->Read(this, 0x556C, 0);
    if (hr < 0)
        return hr;

    if (this) {
        Obj_005BDF70 noInit;
        new (this) MouseClass(noInit);
    }

    for (i = 0; i < 4; i++) {
        for (int j = 0; j < 75; j++)
            DAT_00B0C110.SwizzleManagerClass::vf_4(&Strips[i].Cameos[j].Pointer);
    }
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Pending);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_11A8);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_11A0);

    vf_22();
    vf_24();
    Records = 0;
    Words = 0;
    vf_28(&MapRect, 1, 0, 0);

    if (Records) {
        delete Records;
        Records = 0;
    }
    if (Words) {
        delete[] Words;
        Words = 0;
    }
    Records = new char[WordCount * 10];
    Words = new MapWordEntry[WordCount];
    BucketsA = new MapBucketTable<MapBucketA>;
    for (i = 1; i < 4; i++) {
        int scale = 1 << i;
        Rings[i - 1].Clear();
        Rings[i - 1].CapacityIncrement = (MapRect.Width * MapRect.Height * 4) / (scale * scale);
        BucketsB[i - 1] = new MapBucketTable<MapBucketB>;
    }

    hr = stream->Read(Words, WordCount << 2, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < 13; i++) {
        Buffers[i] = new char[BufferShorts << 1];
        hr = stream->Read(Buffers[i], BufferShorts << 1, 0);
        if (hr < 0)
            return hr;
    }

    int itemCount = 0;
    hr = stream->Read(&itemCount, 4, 0);
    if (hr < 0)
        return hr;
    SaveItems.Clear();
    {
        int n;
        for (n = 0; n < itemCount; n++) {
            ZoneConnectionClass item;
            hr = stream->Read(&item, 0x10, 0);
            if (hr < 0)
                return hr;
            SaveItems.AddItem(item);
        }
    }

    for (i = 0; i < Owned.Capacity; i++) {
        if (Owned.Items[i]) {
            delete Owned.Items[i];
            Owned.Items[i] = 0;
        }
    }

    int count;
    hr = stream->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    {
        int n;
        for (n = 0; n < count; n++) {
            void* object;
            OleLoadFromStream(stream, MouseObjectIid, &object);
        }
    }

    hr = stream->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    {
        int n;
        for (n = 0; n < count; n++) {
            Cell cell;
            hr = stream->Read(&cell, 4, 0);
            if (hr < 0)
                return hr;
            CellTags.AddItem(cell);
        }
    }

    hr = stream->Read(&count, 4, 0);
    if (hr < 0)
        return hr;
    {
        int n;
        for (n = 0; n < count; n++) {
            Cell value;
            hr = stream->Read(&value, 4, 0);
            if (hr < 0)
                return hr;
            ListA.AddItem(value);
        }
    }

    MouseScenarioInstance->Target->Method_71DCA0();
    if (MouseScenarioInstance->Target != MouseLastTarget)
        MouseSceneTarget::Method_545150(MouseScenarioInstance->Target, true);
    else
        MouseScenarioInstance->Target->Method_547110();
    MouseSceneTarget::Method_546DA0(false, false);
    MouseScenarioInstance->Target->Method_5FE620();
    MouseScenarioInstance->Target->Method_45E970();
    MouseScenarioInstance->Target->Method_427940();
    MouseScenarioInstance->Target->Method_6B5490();
    WaypointCoord = 0;
    MouseLastTarget = MouseScenarioInstance->Target;
    return 0;
}

// FUNCTION: GAMEMD 0x5BE6D0
long MouseClass::vf_31(IStream* stream)
{
    HRESULT hr = ScrollClass::vf_31(stream);
    if (hr < 0)
        return hr;

    MouseSceneTarget* scenarioValue = MouseScenarioInstance->Target;
    hr = stream->Write(&scenarioValue, 4, 0);
    if (hr < 0)
        return hr;

    hr = stream->Write(this, 0x556C, 0);
    if (hr < 0)
        return hr;

    hr = stream->Write(Words, WordCount << 2, 0);
    if (hr < 0)
        return hr;

    int i;
    for (i = 0; i < 13; i++) {
        hr = stream->Write(Buffers[i], BufferShorts << 1, 0);
        if (hr < 0)
            return hr;
    }

    int itemCount = SaveItems.Count;
    hr = stream->Write(&itemCount, 4, 0);
    if (hr < 0)
        return hr;

    for (i = 0; i < itemCount; i++) {
        const ZoneConnectionClass& source = SaveItems.Items[i];
        MapSaveItem item;
        memcpy(&item.a, &source.unknown_00, 4);
        memcpy(&item.b, &source.unknown_04, 4);
        item.c = source.unknown_08;
        item.d = source.unknown_0C;
        hr = stream->Write(&item, 0x10, 0);
        if (hr < 0)
            return hr;
    }

    int count = 0;
    MapSavedObject* object;
    FUN_00578350();
    for (object = NextSavedObject_00578290(); object; object = NextSavedObject_00578290()) {
        if (FUN_005657E0(object->GetCell()))
            count++;
    }

    hr = stream->Write(&count, 4, 0);
    if (hr < 0)
        return hr;

    FUN_00578350();
    for (object = NextSavedObject_00578290(); object; object = NextSavedObject_00578290()) {
        if (FUN_005657E0(object->GetCell())) {
            OleSaveToStream(object, stream);
            count--;
        }
    }
    if (count != 0)
        return hr;

    count = CellTags.Count;
    hr = stream->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = stream->Write(&CellTags.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }

    count = ListA.Count;
    hr = stream->Write(&count, 4, 0);
    if (hr < 0)
        return hr;
    for (i = 0; i < count; i++) {
        hr = stream->Write(&ListA.Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    return 0;
}
