// Provenance: own-binary-via-Ghidra
//
// Reads the executable's ProductVersion resource string once and caches it.
//   GLOBAL: GAMEMD 0x846158  DAT_00846158 (char[], cached version text)
//   GLOBAL: GAMEMD 0x846358  DAT_00846358 (bool, "not yet queried")
//   GLOBAL: GAMEMD 0xB732F0  DAT_00b732f0 (module instance handle)
//   STRING: GAMEMD 0x846374  "\\StringFileInfo\\%04d%04d\\ProductVersion"
//   STRING: GAMEMD 0x84639c  "\\VarFileInfo\\Translation"

#include <string.h>
#include <stdio.h>

extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void *module, char *name, unsigned long size);
extern "C" unsigned long __stdcall GetFileVersionInfoSizeA(char *name, unsigned long *handle);
extern "C" int __stdcall GetFileVersionInfoA(char *name, unsigned long handle, unsigned long len, void *data);
extern "C" int __stdcall VerQueryValueA(const void *block, char *sub, void **buffer, unsigned int *len);

extern void *DAT_00b732f0;
extern bool DAT_00846358;
extern char DAT_00846158[];

// FUNCTION: GAMEMD 0x74fdc0
char *FUN_0074fdc0()
{
	char path[260];
	char query[128];
	unsigned long handle;
	unsigned int len;

	if (DAT_00846358) {
		DAT_00846358 = false;
		if (GetModuleFileNameA(DAT_00b732f0, path, 260) > 0) {
			handle = 1;
			int size = GetFileVersionInfoSizeA(path, &handle);
			if (size > 0) {
				void *data = operator new(size);
				if (GetFileVersionInfoA(path, handle, size, data)) {
					void *value;
					VerQueryValueA(data, "\\VarFileInfo\\Translation", &value, &len);
					if (len > 0) {
						sprintf(query, "\\StringFileInfo\\%04d%04d\\ProductVersion",
							((unsigned short *)value)[0], ((unsigned short *)value)[1]);
						VerQueryValueA(data, query, &value, &len);
						if (len > 0) {
							strcpy(DAT_00846158, (char *)value);
						}
					}
				}
				operator delete(data);
			}
		}
	}
	return DAT_00846158;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x846358
bool DAT_00846358 = true;
// GLOBAL: GAMEMD 0xB732F0
void * DAT_00b732f0;
// END defined globals
