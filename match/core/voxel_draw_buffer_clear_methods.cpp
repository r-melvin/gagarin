// Provenance: own-binary-via-Ghidra
//
// Clears the two 256x256 voxel draw buffers (whole, or the dirty rectangle)
// and resets the screen-space bounds accumulators.
//   GLOBAL: GAMEMD 0x8467E0  DAT_008467e0 (int, full clear pending)
//   GLOBAL: GAMEMD 0xB1D5E0  DAT_00b1d5e0 (unsigned char[256][256])
//   GLOBAL: GAMEMD 0xB2D5E0  DAT_00b2d5e0 (3 floats, bounds minimum)
//   GLOBAL: GAMEMD 0xB2D820  DAT_00b2d820 (int)
//   GLOBAL: GAMEMD 0xB2D948  DAT_00b2d948 (3 floats, bounds maximum)
//   GLOBAL: GAMEMD 0xB2FB60  DAT_00b2fb60 (dirty rectangle x, y, w, h)
//   GLOBAL: GAMEMD 0xB2FB70  DAT_00b2fb70 (int)
//   GLOBAL: GAMEMD 0xB2FF78  DAT_00b2ff78 (unsigned char[256][256])
//   GLOBAL: GAMEMD 0xB43180  DAT_00b43180 (int, second buffer in use)

#include <string.h>

struct DirtyRect
{
	int X;
	int Y;
	int W;
	int H;
};

struct Float3
{
	Float3() {}
	Float3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

extern int DAT_008467e0;
extern unsigned char DAT_00b1d5e0[256][256];
extern Float3 DAT_00b2d5e0;
extern int DAT_00b2d820;
extern Float3 DAT_00b2d948;
extern DirtyRect DAT_00b2fb60;
extern int DAT_00b2fb70;
extern unsigned char DAT_00b2ff78[256][256];
extern int DAT_00b43180;

// FUNCTION: GAMEMD 0x753e00
void FUN_00753e00()
{
	DAT_00b2d820 = 0;
	DAT_00b2fb70 = 0;
	if (DAT_008467e0 != 0) {
		DAT_008467e0 = 0;
		memset(DAT_00b2ff78, 0, sizeof(DAT_00b2ff78));
		memset(DAT_00b1d5e0, 0, sizeof(DAT_00b1d5e0));
	} else {
		if (DAT_00b2fb60.X < 0 || DAT_00b2fb60.Y < 0
			|| DAT_00b2fb60.X + DAT_00b2fb60.W > 255 || DAT_00b2fb60.Y + DAT_00b2fb60.H > 255) {
			memset(DAT_00b2ff78, 0, sizeof(DAT_00b2ff78));
		} else {
			for (int row = DAT_00b2fb60.Y; row <= DAT_00b2fb60.Y + DAT_00b2fb60.H; row++) {
				memset(&DAT_00b2ff78[row][DAT_00b2fb60.X], 0, DAT_00b2fb60.W + 1);
			}
		}
		if (DAT_00b43180 != 0) {
			for (int row = DAT_00b2fb60.Y; row <= DAT_00b2fb60.Y + DAT_00b2fb60.H; row++) {
				memset(&DAT_00b1d5e0[row][DAT_00b2fb60.X], 0, DAT_00b2fb60.W + 1);
			}
		}
	}
	DAT_00b2d5e0 = Float3(10000.0f, 10000.0f, 10000.0f);
	DAT_00b2d948 = Float3(-10000.0f, -10000.0f, -10000.0f);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB2FB60
DirtyRect DAT_00b2fb60;
// GLOBAL: GAMEMD 0xB2FB70
int DAT_00b2fb70;
// GLOBAL: GAMEMD 0xB43180
int DAT_00b43180;
// GLOBAL: GAMEMD 0x8467E0
int DAT_008467e0 = 1;
// END defined globals
