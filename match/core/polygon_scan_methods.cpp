// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Polygon scan conversion into per-row {left, right} spans. Both entries
// are __fastcall free functions: 0x63F080 takes the polygon {count +0x00,
// points +0x04 (8-byte x/y pairs)} in ECX and the span buffer {height
// +0x00, top row +0x04, spans +0x08} in EDX; 0x63F2E0 walks one edge with
// x1/y1 in ECX/EDX and x2, y2, side (1 = left column), skip-first-row and
// the span cursor on the stack (`ret 0x14`). The span block is allocated on
// demand as height * 8 + 0x640 bytes (operator new 0x7C8E17).
#include <stdlib.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct PolyPoint_0063F080
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(PolyPoint_0063F080) == 8);

struct Polygon_0063F080
{
    int Count;                     // +0x00
    PolyPoint_0063F080* Points;    // +0x04
};
GG_STATIC_ASSERT(offsetof(Polygon_0063F080, Count) == 0x00);
GG_STATIC_ASSERT(offsetof(Polygon_0063F080, Points) == 0x04);

struct ScanSpan_0063F080
{
    int Left;    // +0x00
    int Right;   // +0x04
};
GG_STATIC_ASSERT(sizeof(ScanSpan_0063F080) == 8);

struct ScanBuffer_0063F080
{
    int Height;                    // +0x00
    int Top;                       // +0x04
    ScanSpan_0063F080* Spans;      // +0x08
};
GG_STATIC_ASSERT(offsetof(ScanBuffer_0063F080, Height) == 0x00);
GG_STATIC_ASSERT(offsetof(ScanBuffer_0063F080, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(ScanBuffer_0063F080, Spans) == 0x08);

void __fastcall FUN_0063F2E0(int x1, int y1, int x2, int y2, int side, int skip, ScanSpan_0063F080** cursor);

// FUNCTION: GAMEMD 0x63F080
void __fastcall FUN_0063F080(Polygon_0063F080* polygon, ScanBuffer_0063F080* buffer)
{
    PolyPoint_0063F080* points = polygon->Points;
    int count = polygon->Count;
    if (count == 0) return;

    int top = points[0].Y;
    int bottom = top;
    int top_index = 0;
    int bottom_index = 0;
    for (int index = 1; index < count; index++) {
        int y = points[index].Y;
        if (y < top) {
            top_index = index;
            top = y;
        } else if (y > bottom) {
            bottom_index = index;
            bottom = y;
        }
    }
    if (top == bottom) return;

    int right = top_index;
    while (points[right].Y == top) {
        right = (right + 1) % count;
    }
    right = (count + right - 1) % count;

    int left = top_index;
    while (points[left].Y == top) {
        left = (count + left - 1) % count;
    }
    left = (left + 1) % count;

    int direction = -1;
    int pointed = (points[left].X != points[right].X);
    if (pointed == 1) {
        if (points[left].X > points[right].X) {
            int swap = left;
            left = right;
            right = swap;
            direction = pointed;
        }
    } else {
        int after = (right + 1) % count;
        int before = (count + left - 1) % count;
        if ((points[before].Y - points[left].Y) * (points[after].X - points[left].X)
            - (points[after].Y - points[left].Y) * (points[before].X - points[left].X) < 0) {
            int swap = left;
            left = right;
            right = swap;
            direction = 1;
        }
    }

    buffer->Height = pointed - top - 1 + bottom;
    if (buffer->Height <= 0) return;
    buffer->Top = top - pointed + 1;
    if (buffer->Spans == NULL) {
        buffer->Spans = (ScanSpan_0063F080*)operator new(buffer->Height * sizeof(ScanSpan_0063F080) + 0x640);
    }
    if (buffer->Spans == NULL) {
        buffer->Height = 0;
        return;
    }

    ScanSpan_0063F080* cursor = buffer->Spans;
    int skip = (pointed == 0);
    int first = skip;
    int current = left;
    int next;
    do {
        if (direction > 0) {
            next = (current + 1) % polygon->Count;
        } else {
            next = (current + polygon->Count - 1) % polygon->Count;
        }
        FUN_0063F2E0(points[current].X, points[current].Y, points[next].X, points[next].Y, 1, first, &cursor);
        first = 0;
        current = next;
    } while (next != bottom_index);

    cursor = buffer->Spans;
    first = skip;
    direction = -direction;
    current = right;
    do {
        if (direction > 0) {
            next = (current + 1) % polygon->Count;
        } else {
            next = (current + polygon->Count - 1) % polygon->Count;
        }
        FUN_0063F2E0(points[current].X - 1, points[current].Y, points[next].X - 1, points[next].Y, 0, first, &cursor);
        first = 0;
        current = next;
    } while (next != bottom_index);
}

// FUNCTION: GAMEMD 0x63F2E0
void __fastcall FUN_0063F2E0(int x1, int y1, int x2, int y2, int side, int skip, ScanSpan_0063F080** cursor)
{
    ScanSpan_0063F080* span = *cursor;
    int dx = x2 - x1;
    int step = (dx > 0) ? 1 : -1;
    int dy = y2 - y1;
    if (dy <= 0) return;

    int adx = abs(dx);
    int count;
    if (adx == 0) {
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            span++;
        }
    } else if (dy == adx) {
        if (skip) x1 += step;
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            x1 += step;
            span++;
        }
    } else if (dy > adx) {
        int error = (dx >= 0) ? 0 : 1 - dy;
        if (skip) {
            error += adx;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
        }
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            error += adx;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
            span++;
        }
    } else {
        int whole = (adx / dy) * step;
        int fraction = adx % dy;
        int error = (dx >= 0) ? 0 : 1 - dy;
        if (skip) {
            error += fraction;
            x1 += whole;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
        }
        count = dy - skip;
        while (count-- > 0) {
            if (side == 1) span->Left = x1; else span->Right = x1;
            error += fraction;
            x1 += whole;
            if (error > 0) {
                x1 += step;
                error -= dy;
            }
            span++;
        }
    }
    *cursor = span;
}
