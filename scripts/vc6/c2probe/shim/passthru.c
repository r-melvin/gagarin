/* c2probe shim - DIAGNOSTIC-ONLY drop-in for the back end C2.DLL (12.00.8447,
 * sha256 a0cc45f8...).  Derived from sushi-shi/homm3-decomp scripts/homm3/vc6/
 * shim/passthru.c (CC0 1.0); modified for gagarin.
 *
 * The CL driver LoadLibraryA's "c2" from its own directory and resolves
 * "_InvokeCompilerPass@12" / "_AbortCompilerPass@4".  This DLL exports those two
 * names, forwards to the real back end (renamed C2_real.dll in the same
 * directory) and, only when C2PROBE_FILTER is set, installs the decision hooks
 * in force.c.  With no rule set the hooks replay the stolen instructions and
 * change nothing; c2probe.py's `gate` proves that byte-for-byte.
 *
 * Fail-closed: the shim refuses (returns 4, compiling nothing) unless the
 * explicit driver variable C2PROBE_DRIVER=1 is set, so a stray build that picks
 * up the probe toolchain cannot silently produce objects.
 *
 * Built by the pinned VC6 itself: C89, /NOENTRY, kernel32 only, no CRT.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef int (__stdcall *invokeCompilerPassFunction)(int, char **, int);
typedef int (__stdcall *abortCompilerPassFunction)(int);

static HMODULE    g_real;
static invokeCompilerPassFunction g_invoke;
static abortCompilerPassFunction  g_abort;
static LONG       g_calls;

static HANDLE logOpen(void)
{
    static char path[520];
    HANDLE h;
    if (!GetEnvironmentVariableA("C2PROBE_LOG", path, sizeof path))
        lstrcpyA(path, "c2probe.log");
    h = CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
                    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (h != INVALID_HANDLE_VALUE)
        SetFilePointer(h, 0, 0, FILE_END);
    return h;
}

static void writeString(HANDLE h, const char *s)
{
    DWORD n;
    if (h == INVALID_HANDLE_VALUE)
        return;
    if (s == 0)
        s = "(null)";
    WriteFile(h, s, (DWORD)lstrlenA(s), &n, 0);
}

static void writeDecimal(HANDLE h, unsigned long v)
{
    char buf[16];
    int i = 16;
    DWORD n;
    if (h == INVALID_HANDLE_VALUE)
        return;
    do {
        buf[--i] = (char)('0' + (int)(v % 10));
        v /= 10;
    } while (v != 0 && i > 0);
    WriteFile(h, buf + i, (DWORD)(16 - i), &n, 0);
}

static void writeSignedDecimal(HANDLE h, long v)
{
    if (v < 0) {
        writeString(h, "-");
        writeDecimal(h, (unsigned long)(-v));
    } else {
        writeDecimal(h, (unsigned long)v);
    }
}

static int resolveReal(void)
{
    static char path[MAX_PATH + 16];
    DWORD n;
    int i, cut;
    HMODULE self;

    if (g_invoke != 0 && g_abort != 0)
        return 1;
    self = GetModuleHandleA("C2.DLL");
    n = (self != 0) ? GetModuleFileNameA(self, path, MAX_PATH) : 0;
    cut = -1;
    for (i = 0; i < (int)n; ++i)
        if (path[i] == '\\' || path[i] == '/' || path[i] == ':')
            cut = i;
    if (cut >= 0) {
        lstrcpyA(path + cut + 1, "C2_real.dll");
        g_real = LoadLibraryA(path);
    }
    if (g_real == 0)
        g_real = LoadLibraryA("C2_real.dll");
    if (g_real == 0)
        return 0;
    g_invoke = (invokeCompilerPassFunction)GetProcAddress(g_real, "_InvokeCompilerPass@12");
    g_abort  = (abortCompilerPassFunction)GetProcAddress(g_real, "_AbortCompilerPass@4");
    return (g_invoke != 0 && g_abort != 0);
}

#include "force.c"

static int driverAllowed(void)
{
    char v[8];
    return GetEnvironmentVariableA("C2PROBE_DRIVER", v, sizeof v) && v[0] == '1';
}

int __stdcall InvokeCompilerPass(int argc, char **argv, int fLastTU)
{
    HANDLE h;
    LONG call;
    int i, ret;

    if (!driverAllowed())
        return 4;
    call = InterlockedIncrement(&g_calls);
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "# c2probe call=");
        writeDecimal(h, (unsigned long)call);
        writeString(h, " fLastTU=");
        writeSignedDecimal(h, fLastTU);
        writeString(h, " argc=");
        writeSignedDecimal(h, argc);
        writeString(h, "\n");
        for (i = 0; i < argc; ++i) {
            if (i)
                writeString(h, " ");
            writeString(h, argv[i]);
        }
        writeString(h, "\n");
        CloseHandle(h);
    }
    if (!resolveReal())
        return 2;
    if (!installForce()) {
        h = logOpen();
        if (h != INVALID_HANDLE_VALUE) {
            writeString(h, "# c2probe hook instruction guard failed\n");
            CloseHandle(h);
        }
        return 3;
    }
    ret = g_invoke(argc, argv, fLastTU);
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "# c2probe call=");
        writeDecimal(h, (unsigned long)call);
        writeString(h, " ret=");
        writeSignedDecimal(h, ret);
        writeString(h, "\n");
        CloseHandle(h);
    }
    return ret;
}

int __stdcall AbortCompilerPass(int code)
{
    if (!driverAllowed() || !resolveReal())
        return 0;
    return g_abort(code);
}
