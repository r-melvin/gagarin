// Provenance: own-binary-via-Ghidra
//
// Recursively walks a wildcard path, counting sub-directories, files and bytes.
//   STRING: GAMEMD 0x826598  "."
//   STRING: GAMEMD 0x846610  ".."
//   STRING: GAMEMD 0x84660c  "\\*"

#include <string.h>

struct FindDataA
{
	unsigned long dwFileAttributes;
	unsigned long ftCreationTime[2];
	unsigned long ftLastAccessTime[2];
	unsigned long ftLastWriteTime[2];
	unsigned long nFileSizeHigh;
	unsigned long nFileSizeLow;
	unsigned long dwReserved0;
	unsigned long dwReserved1;
	char cFileName[260];
	char cAlternateFileName[14];
};

extern "C" __declspec(dllimport) void *__stdcall FindFirstFileA(const char *name, FindDataA *data);
extern "C" __declspec(dllimport) int __stdcall FindNextFileA(void *find, FindDataA *data);
extern "C" __declspec(dllimport) int __stdcall FindClose(void *find);

// FUNCTION: GAMEMD 0x751ea0
void __fastcall FUN_00751ea0(const char *path, int *dirs, int *files, int *bytes)
{
	char sub[260];
	FindDataA data;

	void *find = FindFirstFileA(path, &data);
	if (find == (void *)-1) {
		return;
	}
	do {
		if (data.dwFileAttributes & 0x10) {
			if (_stricmp(data.cFileName, ".") != 0 && _stricmp(data.cFileName, "..") != 0) {
				(*dirs)++;
				strcpy(sub, path);
				sub[strlen(sub) - 1] = '\0';
				strcat(sub, data.cFileName);
				strcat(sub, "\\*");
				FUN_00751ea0(sub, dirs, files, bytes);
			}
		} else {
			(*files)++;
			*bytes += data.nFileSizeLow;
		}
	} while (FindNextFileA(find, &data));
	FindClose(find);
}
