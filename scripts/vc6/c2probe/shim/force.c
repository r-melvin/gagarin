/* c2probe decision hooks for the pinned C2.DLL 12.00.8447 (sha256 a0cc45f8...).
 * Included by passthru.c.  DIAGNOSTIC ONLY: the output of a forced compile is a
 * question put to the compiler ("what if this one decision went the other way"),
 * never a candidate for the tree.
 *
 * Hook points and the recovered roles are those documented by sushi-shi/
 * homm3-decomp vc6 notes on the shim, decision forcing, register allocation and inliner (CC0 1.0);
 * the stolen-instruction guards below re-verify every site against this DLL
 * before patching, and c2probe.py's inertness gate re-proves byte identity.
 *
 *   0x1995c  per-function entry of the inliner: ESI -> body, body[0] -> symbol
 *            (name at symbol+0x18).  Selects the root (C2PROBE_FILTER).
 *   0x19f8c  inline budget test: EDI -> callee symbol, ESP+0x48 budget,
 *            +0x34 depth, +0x30 sites left, +0x1c owner body, callee cb at
 *            symbol+0x6d.  Rule action E -> 0x19faf (admit), K -> 0x19a94.
 *   0x24748  end of the global register choice: EDI = chosen register
 *            (1=EAX..8=EDI), EBX = live-range group (candidates at group+0x20).
 *   0x36afa / 0x3e3e0  tail-merge match-count tests (veto -> count 0).
 *   0x3356e  register binder (passive): ESI = register id, EDX = pseudo; logged as "bind".
 *   0x33273  local scratch-register selector (fastcall: ECX context, EDX pseudo).  The
 *            rotation cursor is the pointer stored at 0x9d710 into the preference table
 *            at 0xadff4 (ids 1=EAX 2=ECX 3=EDX ...).  Forcing request k sets the cursor
 *            to start at EAX/ECX/EDX; the preferred-register path (pseudo+0x2c) and
 *            occupancy tests still apply, so the compiler's own legality decides.
 *
 * Environment (all read once per process):
 *   C2PROBE_FILTER       substring of the root's compiler name; "*" = every root;
 *                        unset = pure pass-through (no hook is installed).
 *   C2PROBE_INLINE_FORCE rule file, lines  owner<TAB>callee<TAB>occurrence<TAB>E|K
 *                        ("*" = any; occurrence 1-based within the root, 0 = all)
 *   C2PROBE_REG_FORCE    "k:reg,..." k-th colour decision of the root -> register
 *   C2PROBE_MERGE_VETO   "k,..." k-th first-seen tail-merge decision -> declined
 *   C2PROBE_SCRATCH_FORCE "k:reg,..." k-th scratch request of the root starts its rotation
 *                        at reg (1=EAX 2=ECX 3=EDX)
 */

static char g_filter[256];
static int g_hooked;
static int g_selected;
static unsigned long g_root;

static void writeHex(HANDLE h, unsigned long value)
{
    char text[8];
    unsigned i;
    DWORD n;
    for (i = 0; i < 8; ++i)
        text[7-i] = "0123456789abcdef"[(value >> (4*i)) & 15];
    WriteFile(h, text, 8, &n, 0);
}

static int contains(const char *text, const char *part)
{
    const char *start, *a, *b;
    if (!*part) return 1;
    if (!text) return 0;
    for (start = text; *start; ++start) {
        for (a = start, b = part; *a && *b && *a == *b; ++a, ++b) {}
        if (!*b) return 1;
    }
    return 0;
}

static int patchHook(unsigned long rva, void *hook,
    const unsigned char *expected, unsigned count)
{
    unsigned char *code = (unsigned char *)g_real + rva;
    DWORD old, ignored;
    unsigned i;
    for (i = 0; i < count; ++i) if (code[i] != expected[i]) return 0;
    if (!VirtualProtect(code, count, PAGE_EXECUTE_READWRITE, &old)) return 0;
    code[0] = 0xe9;
    *(long *)(code+1) = (char *)hook - (char *)(code+5);
    for (i = 5; i < count; ++i) code[i] = 0x90;
    VirtualProtect(code, count, old, &ignored);
    FlushInstructionCache(GetCurrentProcess(), code, count);
    return 1;
}

/* ---- inline rules ------------------------------------------------------- */
#define FORCE_RULES 256
static struct {
    char owner[96];
    char callee[160];
    unsigned long occurrence;
    unsigned long seen;
    char action;
} g_rules[FORCE_RULES];
static unsigned g_ruleCount;
static unsigned long g_decision;
static void *g_siteReturn, *g_expandTarget, *g_keepTarget, *g_mainReturn;

static unsigned copyField(char *dst, unsigned size, const char *src, unsigned n)
{
    unsigned i;
    for (i = 0; i < n && src[i] != '\t' && src[i] != '\n' && src[i] != '\r'; ++i)
        if (i + 1 < size) dst[i] = src[i];
    dst[i < size ? i : size - 1] = 0;
    return i;
}

static void loadForceRules(void)
{
    static char path[520];
    static char text[65536];
    HANDLE h;
    DWORD n = 0;
    unsigned at = 0;
    if (!GetEnvironmentVariableA("C2PROBE_INLINE_FORCE", path, sizeof path)) return;
    h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL, 0);
    if (h == INVALID_HANDLE_VALUE) return;
    ReadFile(h, text, sizeof text - 1, &n, 0);
    CloseHandle(h);
    text[n] = 0;
    while (at < n && g_ruleCount < FORCE_RULES) {
        unsigned k;
        unsigned long occurrence = 0;
        char action;
        if (text[at] == '#' || text[at] == '\n' || text[at] == '\r') {
            while (at < n && text[at] != '\n') ++at;
            ++at; continue;
        }
        at += copyField(g_rules[g_ruleCount].owner, sizeof g_rules[0].owner, text+at, n-at);
        if (text[at] != '\t') break;
        ++at;
        at += copyField(g_rules[g_ruleCount].callee, sizeof g_rules[0].callee, text+at, n-at);
        if (text[at] != '\t') break;
        ++at;
        for (k = at; k < n && text[k] >= '0' && text[k] <= '9'; ++k)
            occurrence = occurrence * 10 + (unsigned long)(text[k] - '0');
        at = k;
        if (text[at] != '\t') break;
        action = text[at+1];
        if (action != 'E' && action != 'K') break;
        g_rules[g_ruleCount].occurrence = occurrence;
        g_rules[g_ruleCount].action = action;
        if (g_rules[g_ruleCount].owner[0] == '*' && !g_rules[g_ruleCount].owner[1])
            g_rules[g_ruleCount].owner[0] = 0;
        if (g_rules[g_ruleCount].callee[0] == '*' && !g_rules[g_ruleCount].callee[1])
            g_rules[g_ruleCount].callee[0] = 0;
        ++g_ruleCount;
        while (at < n && text[at] != '\n') ++at;
        ++at;
    }
}

static char forceDecision(const char *owner, const char *callee)
{
    unsigned i;
    char result = 0;
    for (i = 0; i < g_ruleCount; ++i) {
        if (!contains(owner, g_rules[i].owner) || !contains(callee, g_rules[i].callee))
            continue;
        ++g_rules[i].seen;
        if (!result && (g_rules[i].occurrence == 0
                        || g_rules[i].seen == g_rules[i].occurrence))
            result = g_rules[i].action;
    }
    return result;
}

/* ---- register / merge tables ------------------------------------------- */
typedef int (__fastcall *setHasFunction)(void *set, unsigned long member);
static setHasFunction g_setHas;
static void *g_colorReturn, *g_mergeReturnA, *g_mergeReturnB;
static unsigned long g_colorIndex, g_mergeIndex;
static struct { unsigned long a, b; } g_vetoPairs[1024];
static unsigned g_vetoPairCount;
static unsigned char g_regForce[1024];
static int g_regForceActive;
static unsigned char g_mergeVeto[1024];
static unsigned char g_scratchForce[1024];
static int g_scratchForceActive;
static unsigned long g_scratchIndex;
static void *g_scratchReturn;

static void loadRegisterForce(void)
{
    static char text[8192];
    DWORD n = GetEnvironmentVariableA("C2PROBE_REG_FORCE", text, sizeof text);
    unsigned long k = 0, reg = 0, i;
    int seenColon = 0;
    if (!n || n >= sizeof text) return;
    for (i = 0; i <= n; ++i) {
        char c = i < n ? text[i] : ',';
        if (c >= '0' && c <= '9') {
            if (seenColon) reg = reg * 10 + (unsigned long)(c - '0');
            else k = k * 10 + (unsigned long)(c - '0');
        } else if (c == ':') {
            seenColon = 1;
        } else if (c == ',' || c == ' ') {
            if (seenColon && k && k < sizeof g_regForce && reg && reg < 9 && reg != 5) {
                g_regForce[k] = (unsigned char)reg;
                g_regForceActive = 1;
            }
            k = reg = 0; seenColon = 0;
        }
    }
}

static void loadScratchForce(void)
{
    static char text[8192];
    DWORD n = GetEnvironmentVariableA("C2PROBE_SCRATCH_FORCE", text, sizeof text);
    unsigned long k = 0, reg = 0, i;
    int seenColon = 0;
    if (!n || n >= sizeof text) return;
    for (i = 0; i <= n; ++i) {
        char c = i < n ? text[i] : ',';
        if (c >= '0' && c <= '9') {
            if (seenColon) reg = reg * 10 + (unsigned long)(c - '0');
            else k = k * 10 + (unsigned long)(c - '0');
        } else if (c == ':') {
            seenColon = 1;
        } else {
            if (seenColon && k && k < sizeof g_scratchForce && reg >= 1 && reg <= 3) {
                g_scratchForce[k] = (unsigned char)reg;
                g_scratchForceActive = 1;
            }
            k = reg = 0; seenColon = 0;
        }
    }
}

static void loadMergeVeto(void)
{
    static char text[8192];
    DWORD n = GetEnvironmentVariableA("C2PROBE_MERGE_VETO", text, sizeof text);
    unsigned long k = 0, i;
    if (!n || n >= sizeof text) return;
    for (i = 0; i <= n; ++i) {
        char c = i < n ? text[i] : ',';
        if (c >= '0' && c <= '9') k = k * 10 + (unsigned long)(c - '0');
        else { if (k && k < sizeof g_mergeVeto) g_mergeVeto[k] = 1; k = 0; }
    }
}

/* ---- hook bodies ------------------------------------------------------- */
static void __cdecl traceMain(unsigned long *body)
{
    HANDLE h;
    DWORD lastError;
    unsigned char *sym = (unsigned char *)body[0];
    unsigned i;
    g_root = (unsigned long)sym;
    g_selected = contains(*(const char **)(sym+0x18), g_filter);
    g_colorIndex = 0;
    g_mergeIndex = 0;
    g_scratchIndex = 0;
    g_vetoPairCount = 0;
    for (i = 0; i < g_ruleCount; ++i) g_rules[i].seen = 0;
    if (!g_selected) return;
    lastError = GetLastError();
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "main "); writeString(h, *(const char **)(sym+0x18));
        writeString(h, " cb="); writeSignedDecimal(h, *(short *)(sym+0x6d));
        writeString(h, "\n"); CloseHandle(h);
    }
    SetLastError(lastError);
}

static unsigned long __cdecl traceSite(unsigned long *regs)
{
    HANDLE h;
    DWORD lastError;
    unsigned char *sym = (unsigned char *)regs[0];   /* saved EDI */
    unsigned char *sp = (unsigned char *)(regs[3]+4); /* before pushfd */
    unsigned long *body = *(unsigned long **)(sp+0x1c);
    const char *owner, *callee;
    char action;
    if (!g_selected) return 0;
    lastError = GetLastError();
    owner = *(const char **)((unsigned char *)body[0]+0x18);
    callee = *(const char **)(sym+0x18);
    action = g_ruleCount ? forceDecision(owner, callee) : 0;
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "site owner="); writeString(h, owner);
        writeString(h, " callee="); writeString(h, callee);
        writeString(h, " cb="); writeSignedDecimal(h, *(short *)(sym+0x6d));
        writeString(h, " budget="); writeSignedDecimal(h, *(long *)(sp+0x48));
        writeString(h, " depth="); writeDecimal(h, *(unsigned long *)(sp+0x34));
        writeString(h, " remain="); writeDecimal(h, *(unsigned long *)(sp+0x30));
        writeString(h, " args="); writeDecimal(h, regs[6]);
        if (action) { writeString(h, " force="); writeString(h, action == 'E' ? "E" : "K"); }
        writeString(h, "\n"); CloseHandle(h);
    }
    SetLastError(lastError);
    return action == 'E' ? 1 : action == 'K' ? 2 : 0;
}

static void __cdecl colorDecision(unsigned long *regs)
{
    /* pushad layout: EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX */
    unsigned char *group = (unsigned char *)regs[4];
    void *set;
    unsigned long chosen = regs[0], eligible = 0, r, forced = 0;
    HANDLE h;
    DWORD lastError;
    if (!g_selected) return;
    lastError = GetLastError();
    ++g_colorIndex;
    set = *(void **)(group + 0x20);
    for (r = 1; r <= 8; ++r)
        if (r != 5 && set && g_setHas(set, r)) eligible |= 1ul << r;
    if (chosen && g_regForceActive && g_colorIndex < sizeof g_regForce
            && g_regForce[g_colorIndex]
            && (eligible & (1ul << g_regForce[g_colorIndex]))) {
        forced = g_regForce[g_colorIndex];
        regs[0] = forced;
    }
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "color k="); writeDecimal(h, g_colorIndex);
        writeString(h, " chosen="); writeDecimal(h, chosen);
        writeString(h, " eligible="); writeHex(h, eligible);
        writeString(h, " priority="); writeSignedDecimal(h, *(long *)(group + 0x0c));
        if (forced) { writeString(h, " forced="); writeDecimal(h, forced); }
        writeString(h, "\n"); CloseHandle(h);
    }
    SetLastError(lastError);
}

static unsigned long __cdecl mergeDecision(unsigned long kind, unsigned long *regs)
{
    HANDLE h;
    DWORD lastError;
    unsigned long count = regs[7], a = regs[2], b = regs[4];
    unsigned i;
    int veto;
    if (!count || !g_selected) return count;
    for (i = 0; i < g_vetoPairCount; ++i)
        if (g_vetoPairs[i].a == a && g_vetoPairs[i].b == b) return 0;
    lastError = GetLastError();
    ++g_mergeIndex;
    veto = g_mergeIndex < sizeof g_mergeVeto && g_mergeVeto[g_mergeIndex];
    if (veto && g_vetoPairCount < 1024) {
        g_vetoPairs[g_vetoPairCount].a = a;
        g_vetoPairs[g_vetoPairCount].b = b;
        ++g_vetoPairCount;
    }
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "merge k="); writeDecimal(h, g_mergeIndex);
        writeString(h, " kind="); writeDecimal(h, kind);
        writeString(h, " count="); writeDecimal(h, count);
        if (veto) writeString(h, " veto=1");
        writeString(h, "\n"); CloseHandle(h);
    }
    SetLastError(lastError);
    return veto ? 0 : count;
}

/* regs: pushad layout; EDX = pseudo, ECX = context. */
static void __cdecl scratchDecision(unsigned long *regs)
{
    unsigned long *cursor = (unsigned long *)((char *)g_real + 0x9d710);
    unsigned char *pseudo = (unsigned char *)regs[5];
    unsigned long forced = 0, before = *cursor;
    HANDLE h;
    DWORD lastError;
    if (!g_selected) return;
    lastError = GetLastError();
    ++g_scratchIndex;
    if (g_scratchForceActive && g_scratchIndex < sizeof g_scratchForce
            && g_scratchForce[g_scratchIndex]) {
        forced = g_scratchForce[g_scratchIndex];
        *cursor = (unsigned long)((char *)g_real + 0xadff4) + (forced - 1) * 4;
    }
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "scratch k="); writeDecimal(h, g_scratchIndex);
        writeString(h, " cursor="); writeDecimal(h, (before - (unsigned long)((char *)g_real + 0xadff4)) / 4);
        writeString(h, " pseudo="); writeHex(h, *(unsigned long *)(pseudo + 0x1c));
        writeString(h, " preferred="); writeDecimal(h, *(unsigned long *)(pseudo + 0x2c) ? 1 : 0);
        if (forced) { writeString(h, " forced="); writeDecimal(h, forced); }
        writeString(h, "\n"); CloseHandle(h);
    }
    SetLastError(lastError);
}

static void __declspec(naked) scratchHook(void)
{
    __asm {
        pushfd
        pushad
        mov eax, esp
        push eax
        call scratchDecision
        add esp, 4
        popad
        popfd
        sub esp, 14h
        push ebx
        push ebp
        jmp dword ptr [g_scratchReturn]
    }
}

static void *g_bindReturn;
static void *g_bindingsAddress;

static void __cdecl bindTrace(unsigned long *regs)
{
    unsigned char *pseudo = (unsigned char *)regs[5];     /* EDX */
    HANDLE h;
    DWORD lastError;
    if (!g_selected || IsBadReadPtr(pseudo, 0x20)) return;
    lastError = GetLastError();
    h = logOpen();
    if (h != INVALID_HANDLE_VALUE) {
        writeString(h, "bind scratchk="); writeDecimal(h, g_scratchIndex);
        writeString(h, " reg="); writeDecimal(h, regs[1]);   /* ESI */
        writeString(h, " pseudo="); writeHex(h, *(unsigned long *)(pseudo + 0x1c));
        writeString(h, " kind="); writeDecimal(h, pseudo[4]);
        writeString(h, "\n"); CloseHandle(h);
    }
    SetLastError(lastError);
}

static void __declspec(naked) bindHook(void)
{
    __asm {
        pushfd
        pushad
        mov eax, esp
        push eax
        call bindTrace
        add esp, 4
        popad
        popfd
        push ecx
        mov ecx, g_bindingsAddress
        mov [ecx + esi*4], edx
        pop ecx
        jmp dword ptr [g_bindReturn]
    }
}

static void __declspec(naked) mainHook(void)
{
    __asm {
        pushfd
        pushad
        push esi
        call traceMain
        add esp, 4
        popad
        popfd
        mov eax, [esi]
        movsx eax, word ptr [eax+06dh]
        jmp dword ptr [g_mainReturn]
    }
}

static void __declspec(naked) siteHook(void)
{
    __asm {
        pushfd
        pushad
        mov eax, esp
        push eax
        call traceSite
        add esp, 4
        mov dword ptr [g_decision], eax
        popad
        popfd
        mov ax, word ptr [edi+06dh]
        mov esi, [esp+048h]
        cmp dword ptr [g_decision], 1
        je forceExpand
        cmp dword ptr [g_decision], 2
        je forceKeep
        jmp dword ptr [g_siteReturn]
    forceExpand:
        jmp dword ptr [g_expandTarget]
    forceKeep:
        jmp dword ptr [g_keepTarget]
    }
}

static void __declspec(naked) colorHook(void)
{
    __asm {
        pushfd
        pushad
        mov eax, esp
        push eax
        call colorDecision
        add esp, 4
        popad
        popfd
        lea eax, [edi*8]
        sub eax, edi
        jmp dword ptr [g_colorReturn]
    }
}

static void __declspec(naked) mergeHookA(void)
{
    __asm {
        mov eax, [esp+10h]
        pushad
        mov ecx, esp
        push ecx
        push 1
        call mergeDecision
        add esp, 8
        mov [esp+1Ch], eax
        popad
        test eax, eax
        jmp dword ptr [g_mergeReturnA]
    }
}

static void __declspec(naked) mergeHookB(void)
{
    __asm {
        mov eax, [esp+18h]
        pushad
        mov ecx, esp
        push ecx
        push 2
        call mergeDecision
        add esp, 8
        mov [esp+1Ch], eax
        popad
        test eax, eax
        jmp dword ptr [g_mergeReturnB]
    }
}

static int installForce(void)
{
    static const unsigned char mainBytes[] = {0x8b,0x06,0x0f,0xbf,0x40,0x6d};
    static const unsigned char siteBytes[] = {0x66,0x8b,0x47,0x6d,0x8b,0x74,0x24,0x48};
    static const unsigned char colorBytes[] = {0x8d,0x04,0xfd,0,0,0,0,0x2b,0xc7};
    static const unsigned char bindBytes[] = {0x89,0x14,0xb5,0xec,0xd6,0x79,0x10};
    static const unsigned char scratchBytes[] = {0x83,0xec,0x14,0x53,0x55};
    static const unsigned char mergeBytesA[] = {0x8b,0x44,0x24,0x10,0x85,0xc0,0x77,0x47};
    static const unsigned char mergeBytesB[] = {0x8b,0x44,0x24,0x18,0x85,0xc0,0xc7,0x02};
    if (g_hooked) return 1;
    if (!GetEnvironmentVariableA("C2PROBE_FILTER", g_filter, sizeof g_filter))
        return 1;                       /* pure pass-through */
    if (g_filter[0] == '*' && !g_filter[1]) g_filter[0] = 0;
    g_mainReturn = (char *)g_real + 0x19962;
    g_siteReturn = (char *)g_real + 0x19f94;
    g_expandTarget = (char *)g_real + 0x19faf;
    g_keepTarget = (char *)g_real + 0x19a94;
    g_colorReturn = (char *)g_real + 0x24751;
    g_mergeReturnA = (char *)g_real + 0x36b00;
    g_mergeReturnB = (char *)g_real + 0x3e3e6;
    g_scratchReturn = (char *)g_real + 0x33278;
    g_bindReturn = (char *)g_real + 0x33575;
    g_bindingsAddress = (char *)g_real + 0x9d6ec;
    g_setHas = (setHasFunction)((char *)g_real + 0x19b5);
    loadForceRules();
    loadRegisterForce();
    loadMergeVeto();
    loadScratchForce();
    if (!patchHook(0x1995c, mainHook, mainBytes, sizeof mainBytes)) return 0;
    if (!patchHook(0x19f8c, siteHook, siteBytes, sizeof siteBytes)) return 0;
    /* colorBytes carries the 32-bit scale-table displacement of 'lea eax,[edi*8]';
     * only the opcode and the trailing sub are guarded. */
    {
        unsigned char *c = (unsigned char *)g_real + 0x24748;
        if (c[0] != colorBytes[0] || c[1] != colorBytes[1] || c[2] != colorBytes[2]
            || c[7] != colorBytes[7] || c[8] != colorBytes[8]) return 0;
        if (!patchHook(0x24748, colorHook, c, sizeof colorBytes)) return 0;
    }
    if (!patchHook(0x3356e, bindHook, bindBytes, sizeof bindBytes)) return 0;
    if (!patchHook(0x33273, scratchHook, scratchBytes, sizeof scratchBytes)) return 0;
    if (!patchHook(0x36afa, mergeHookA, mergeBytesA, 6)) return 0;
    if (!patchHook(0x3e3e0, mergeHookB, mergeBytesB, 6)) return 0;
    g_hooked = 1;
    return 1;
}
