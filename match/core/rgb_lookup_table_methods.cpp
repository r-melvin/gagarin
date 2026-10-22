// Provenance: own-binary-via-Ghidra
//
// Builds a 32x32x32 15-bit colour lookup table for one of four pixel formats.
//   GLOBAL: GAMEMD 0xB1D14C  DAT_00b1d14c (unsigned short *, 0x1FFFC-byte table)

extern unsigned short *DAT_00b1d14c;

// FUNCTION: GAMEMD 0x748220
bool FUN_00748220(unsigned int mode)
{
	int rshift;
	int gshift;
	int bshift;

	if (DAT_00b1d14c != 0) {
		operator delete(DAT_00b1d14c);
		DAT_00b1d14c = 0;
	}
	DAT_00b1d14c = (unsigned short *)operator new(0x1FFFC);
	if (DAT_00b1d14c == 0) {
		return false;
	}

	switch (mode) {
	case 0:
		rshift = 10;
		gshift = 5;
		bshift = 0;
		break;
	case 3:
		rshift = 11;
		gshift = 5;
		bshift = 0;
		break;
	case 2:
		rshift = 11;
		gshift = 6;
		bshift = 0;
		break;
	case 1:
		rshift = 11;
		gshift = 6;
		bshift = 1;
		break;
	default:
		return false;
	}

	for (int r = 0; r < 32; r++) {
		for (int g = 0; g < 32; g++) {
			for (int b = 0; b < 32; b++) {
				DAT_00b1d14c[(unsigned short)(((r << 5) | g) << 5) | (unsigned short)b] =
					(unsigned short)((b << bshift) | (r << rshift) | (g << gshift));
			}
		}
	}
	return true;
}
