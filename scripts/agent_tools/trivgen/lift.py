#!/usr/bin/env python3
# Provenance: original. Straight-line lifter for tiny retail functions (trivgen).
"""Symbolic lift of a short straight-line x86 function into a Spec.

A Spec is a language-neutral description (statements over symbolic values) that
emit.py turns into VC6-compilable C++.  Everything is derived from the
instructions of the retail function itself; nothing is read from outside
sources.  Functions the lifter cannot represent raise Unsupported(reason).

Symbolic values (tuples):
  ('imm', v)                    32-bit constant
  ('p0',) ('p1',)               entry ECX / EDX
  ('stk', k)                    k-th 4-byte stack argument ([esp+4+4k] at entry)
  ('ld', base, disp, size, sg)  memory load; base None = absolute address `disp`
  ('lea', base, disp)           address of member / global
  ('call', i)                   result of call i
  ('bin', op, a, b) ('un', op, a)
  ('zx', v, size)               zero-extension of a narrow value to 32 bits
  ('cmp', cc, a, b)             comparison result (0/1)
  ('fl', ...)                   x87 values: ('fld', mem) ('fbin', op, a, b)
"""
import re
from dataclasses import dataclass, field

import calleesig
import x86

IMG_LO, IMG_HI = 0x400000, 0x1000000


class Unsupported(Exception):
    pass


def imm(v):
    return ("imm", v & 0xFFFFFFFF)


@dataclass
class Store:
    base: object          # value (pointer) or None for absolute
    disp: int
    size: int
    value: object
    fp: bool = False      # x87 store; value is an fl value


@dataclass
class Decl:
    """A local snapshot of a load: 'alias' (a later store would change it) or 'branch' (kept live across a test)."""
    idx: int
    value: object
    kind: str = "alias"


def contains(v, target):
    if v == target:
        return True
    if isinstance(v, tuple):
        return any(contains(x, target) for x in v[1:] if isinstance(x, tuple))
    return False


def subst(v, old, new):
    if v == old:
        return new
    if isinstance(v, tuple) and v:
        return (v[0],) + tuple(subst(x, old, new) if isinstance(x, tuple) else x for x in v[1:])
    return v


def loads_in(v):
    out = []
    if isinstance(v, tuple) and v:
        if v[0] == "ld" and v[4] != "fp":
            out.append(v)
        for x in v[1:]:
            if isinstance(x, tuple):
                out += loads_in(x)
    return out


@dataclass
class Call:
    idx: int
    target: object        # int address, or ('vt', base, disp) for call [base+disp], or ('mem', ...)
    ecx: object           # value passed in ecx, or None
    edx: object           # value passed in edx, or None
    stack: list           # stack args in call order (left to right)
    cleanup: int          # bytes the caller popped after the call (cdecl) or 0
    tail: bool = False    # emitted as jmp
    ecx_set: bool = False  # ecx written explicitly since entry / the previous call
    edx_set: bool = False
    ecx_w: int = 4         # meaningful width of the ECX / EDX value (1 after an 8-bit write)
    edx_w: int = 4


@dataclass
class Node:
    """One straight-line block; either a leaf (returns) or ends in a conditional branch."""
    stmts: list
    cond: object = None           # value tuple: branch is taken when true
    taken: object = None
    fall: object = None
    ret: object = None
    ret_width: int = 4
    ret_fp: bool = False
    retn: int = 0
    tail: bool = False


@dataclass
class Spec:
    addr: int
    size: int
    insns: list
    stmts: list = field(default_factory=list)       # Store | Call (ordered)
    ret: object = None                              # returned value or None
    ret_width: int = 4                              # 1/2/4 meaningful width of eax at ret
    ret_fp: bool = False
    retn: int = 0                                   # bytes popped by ret n
    uses_ecx: bool = False
    uses_edx: bool = False
    nstack: int = 0
    pattern: str = ""
    calls: list = field(default_factory=list)
    flags: dict = field(default_factory=dict)
    tree: object = None                             # Node when the function branches


REG32 = x86.REG32
SUB8 = {"al": "eax", "cl": "ecx", "dl": "edx", "bl": "ebx"}
SUB16 = {"ax": "eax", "cx": "ecx", "dx": "edx", "bx": "ebx"}
CC = {"e": "==", "z": "==", "ne": "!=", "nz": "!=", "l": "<", "ge": ">=", "le": "<=", "g": ">",
      "b": "u<", "ae": "u>=", "be": "u<=", "a": "u>"}


class Lifter:
    def __init__(self, addr, size, insns):
        self.sp = Spec(addr, size, insns)
        self.reg = {"ecx": (("p0",), 4), "edx": (("p1",), 4), "eax": (None, 4), "ebx": (None, 4),
                    "esi": (None, 4), "edi": (None, 4)}
        self.written = set()       # regs written since entry / last call
        self.pushes = []           # pending pushed stack args (push order)
        self.espoff = 0            # bytes pushed (net) at the moment
        self.flags = None          # last cmp/test: ('cmp', a, b) or ('test', a, b)
        self.fstack = []
        self.stmts = []
        self.counter = [0]
        self.leaf = None
        self.tc = [0]
        self.retn = 0
        self.saved = []            # callee-saved registers pushed in the prologue
        self.last_call = None

    # ------------------------------------------------------------ operands
    def addr_of(self, op):
        """Return (base_value|None, disp) for a memory operand."""
        if op.index is not None:
            raise Unsupported("indexed-operand")
        if op.base is None:
            return None, op.disp & 0xFFFFFFFF
        if op.base == "esp":
            k = op.disp - self.espoff - 4
            if k < 0 or k % 4:
                raise Unsupported("stack-local")
            return ("stkslot", k // 4), 0
        v, w = self.reg.get(op.base, (None, 4))
        if v is None:
            raise Unsupported("undef-base-reg")
        disp = op.disp
        while True:      # fold `ecx = this + N; [ecx+M]` into a single member access
            if v[0] == "bin" and v[1] == "+" and v[3][0] == "imm":
                disp += v[3][1] - (1 << 32) if v[3][1] >= 0x80000000 else v[3][1]
                v = v[2]
            elif v[0] == "lea":
                disp += v[2]
                v = v[1]
            else:
                break
        return v, disp

    def read_op(self, op, size=None):
        if op.kind == "imm":
            return imm(op.val)
        if op.kind == "reg":
            return self.read_reg(op.reg)
        base, disp = self.addr_of(op)
        sz = size or op.size or 4
        if isinstance(base, tuple) and base[0] == "stkslot":
            self.sp.nstack = max(self.sp.nstack, base[1] + 1)
            if sz == 1:
                return ("lo", ("stk", base[1]), 1)
            if sz != 4:
                raise Unsupported("stack-narrow")
            return ("stk", base[1])
        return ("ld", base, disp, sz, False)

    def read_reg(self, name):
        if name in REG32:
            v, w = self.reg[name] if name in self.reg else (None, 4)
            if v is None:
                raise Unsupported("undef-reg-read:" + name)
            if w == 1:
                raise Unsupported("narrow-reg-read32")
            return v
        if name in SUB8:
            v, w = self.reg[SUB8[name]]
            if v is None:
                raise Unsupported("undef-reg-read:" + name)
            return ("lo", v, 1) if w == 4 and not (v[0] == "zx") else v
        if name in SUB16:
            v, w = self.reg[SUB16[name]]
            if v is None:
                raise Unsupported("undef-reg-read:" + name)
            return ("lo", v, 2) if w == 4 and not (v[0] == "zx") else v
        raise Unsupported("reg:" + name)

    def write_reg(self, name, value, width=4):
        if name in REG32:
            self.reg[name] = (value, width)
            self.written.add(name)
            return
        if name in SUB8:
            full = SUB8[name]
            cur, w = self.reg[full]
            self.written.add(full)
            if cur == imm(0) and w == 4:
                self.reg[full] = (("zx", value, 1), 4)
            elif cur is None or w == 1:
                self.reg[full] = (value, 1)
            else:
                # the upper bits keep their old, unrelated contents: only the low byte is meaningful
                self.reg[full] = (value, 1)
            return
        if name in SUB16:
            full = SUB16[name]
            cur, w = self.reg[full]
            self.written.add(full)
            if cur == imm(0) and w == 4:
                self.reg[full] = (("zx", value, 2), 4)
            else:
                self.reg[full] = (value, 2)
            return
        raise Unsupported("reg-write:" + name)

    def after_store(self, st):
        """A store changes memory: registers that cached the stored value now read it back,
        registers that hold an older load of the same cell get a local snapshot."""
        sp = self.sp
        new = ("ld", st.base, st.disp, st.size, False)
        snaps = []
        for name, (v, w) in list(self.reg.items()):
            if v is None:
                continue
            if not st.fp and v == st.value and st.size == 4 and new in loads_in(st.value):
                self.reg[name] = (new, w)       # read-modify-write: the register is the new cell value
                continue
            for l in loads_in(v):
                if l[1] == st.base and l[2] == st.disp:
                    snaps.append(l)
        for l in dict.fromkeys(snaps):
            self.tc[0] += 1
            tid = self.tc[0]
            d = Decl(tid, l)
            # the snapshot belongs before the store that was just appended
            self.stmts.insert(len(self.stmts) - 1, d)
            for name, (v, w) in list(self.reg.items()):
                if v is not None:
                    self.reg[name] = (subst(v, l, ("tmp", tid, l[3])), w)
            self.pushes = [subst(p, l, ("tmp", tid, l[3])) for p in self.pushes]

    def mark_use(self, v):
        """Record entry-register uses reachable from value v."""
        if not isinstance(v, tuple):
            return
        if v[0] == "p0":
            self.sp.uses_ecx = True
        elif v[0] == "p1":
            self.sp.uses_edx = True
        for x in v[1:]:
            if isinstance(x, tuple):
                self.mark_use(x)

    def step(self, i, nxt):
        sp = self.sp
        mn, ops = i.mn, i.ops
        if mn == "nop":
            return False
        if mn == "ret":
            self.retn = ops[0].val if ops else 0
            return self.finish_ret()
        if mn == "mov":
            d, s = ops
            if d.kind == "reg":
                if s.kind == "mem" and s.size is None and d.regsize:
                    s.size = d.regsize
                v = self.read_op(s, d.regsize)
                self.mark_use(v)
                if d.regsize == 4:
                    if s.kind == "mem" and v[0] == "ld":
                        v = ("ld", v[1], v[2], 4, False)
                    self.write_reg(d.reg, v, 4)
                elif d.regsize == 1:
                    if s.kind == "mem" and v[0] == "ld":
                        v = ("ld", v[1], v[2], 1, False)
                    self.write_reg(d.reg, v)
                else:
                    if s.kind == "mem" and v[0] == "ld":
                        v = ("ld", v[1], v[2], 2, False)
                    self.write_reg(d.reg, v)
                return False
            # store
            sz = d.size or (s.regsize if s.kind == "reg" else None)
            if sz is None:
                raise Unsupported("store-size")
            v = self.read_op(s, sz)
            self.mark_use(v)
            base, disp = self.addr_of(d)
            if isinstance(base, tuple) and base[0] == "stkslot":
                raise Unsupported("stack-store")
            self.mark_use(base)
            self.stmts.append(Store(base, disp, sz, v))
            self.after_store(self.stmts[-1])
            return False
        if mn == "xor" and ops[0].kind == "reg" and ops[1].kind == "reg" and ops[0].reg == ops[1].reg:
            r = ops[0].reg
            if r in REG32:
                self.reg[r] = (imm(0), 4)
                self.written.add(r)
            elif r in SUB8:
                # xor al,al : value 0, width 1 (upper bits stay as they were: treat as 8-bit result)
                self.reg[SUB8[r]] = (imm(0), 1)
                self.written.add(SUB8[r])
            else:
                raise Unsupported("xor-reg")
            self.flags = None
            return False
        if mn == "lea":
            d, s = ops
            base, disp = self.addr_of(s) if s.index is None else (None, None)
            if s.index is not None:
                raise Unsupported("lea-indexed")
            if base is None:
                self.write_reg(d.reg, imm(disp))
            else:
                self.mark_use(base)
                self.write_reg(d.reg, ("lea", base, disp))
            return False
        if mn in ("movzx", "movsx"):
            d, s = ops
            sz = s.size if s.kind == "mem" else s.regsize
            v = self.read_op(s, sz)
            self.mark_use(v)
            if mn == "movzx":
                self.write_reg(d.reg, ("zx", v, sz))
            else:
                self.write_reg(d.reg, ("sx", v, sz))
            return False
        if mn in ("add", "sub") and ops[0].kind == "reg" and ops[0].reg == "esp":
            lc = self.last_call
            if mn == "add" and ops[1].kind == "imm" and lc is not None and not lc.cleanup \
                    and ops[1].val == 4 * len(lc.stack) and not self.pushes:
                lc.cleanup = ops[1].val
                self.espoff -= ops[1].val
                return False
            raise Unsupported("stack-local" if mn == "sub" else "add-esp")
        if mn in ("inc", "dec") or (mn in ("add", "sub", "or", "and", "xor") and len(ops) == 2):
            return self.alu(i)
        if mn in ("not", "neg") and ops[0].kind == "reg":
            v = self.read_reg(ops[0].reg)
            self.mark_use(v)
            self.write_reg(ops[0].reg, ("un", mn, v))
            return False
        if mn in ("shl", "shr", "sar") and ops[0].kind == "reg" and ops[1].kind == "imm":
            v = self.read_reg(ops[0].reg)
            self.mark_use(v)
            self.write_reg(ops[0].reg, ("bin", mn, v, imm(ops[1].val)))
            return False
        if mn == "cmp":
            a = self.read_op(ops[0])
            b = self.read_op(ops[1])
            self.mark_use(a)
            self.mark_use(b)
            self.flags = ("cmp", a, b)
            return False
        if mn == "test":
            a = self.read_op(ops[0])
            b = self.read_op(ops[1])
            self.mark_use(a)
            self.mark_use(b)
            self.flags = ("test", a, b)
            return False
        if mn.startswith("set"):
            cc = mn[3:]
            if self.flags is None or cc not in CC:
                raise Unsupported("setcc-noflags")
            kind, a, b = self.flags
            if kind == "test":
                if a != b:
                    raise Unsupported("test-two-operands")
                cmpv = ("cmp", CC[cc] if cc in ("e", "z", "ne", "nz") else cc, a, imm(0))
                if cc in ("l", "ge", "le", "g"):
                    cmpv = ("cmp", CC[cc], a, imm(0))
            else:
                cmpv = ("cmp", CC[cc], a, b)
            d = ops[0]
            self.write_reg(d.reg, cmpv) if False else None
            full = SUB8.get(d.reg)
            if not full:
                raise Unsupported("setcc-dest")
            cur, w = self.reg[full]
            self.written.add(full)
            if cur == imm(0) and w == 4:
                self.reg[full] = (("zx", cmpv, 1), 4)
            else:
                self.reg[full] = (cmpv, 1)
            return False
        if mn == "push":
            if ops[0].kind == "reg" and ops[0].reg in ("esi", "edi", "ebx", "ebp") \
                    and self.reg.get(ops[0].reg, (None, 4))[0] is None and not self.pushes:
                self.saved.append(ops[0].reg)
                self.espoff += 4
                return False
            v = self.read_op(ops[0], 4)
            self.mark_use(v)
            self.pushes.append(v)
            self.espoff += 4
            return False
        if mn == "pop":
            r = ops[0].reg
            if self.saved and self.saved[-1] == r and not self.pushes:
                self.saved.pop()
                self.espoff -= 4
                self.reg[r] = (None, 4)
                return False
            lc = self.last_call
            if r == "ecx" and lc is not None and not lc.cleanup and len(lc.stack) == 1 and not self.pushes:
                lc.cleanup = 4
                self.espoff -= 4
                self.reg["ecx"] = (None, 4)
                self.written.discard("ecx")
                return False
            raise Unsupported("pop")
        if mn == "call":
            return self.do_call(i, nxt, tail=False)
        if mn == "jmp":
            return self.do_call(i, nxt, tail=True)
        if mn.startswith("j"):
            raise Unsupported("branch")
        if mn in ("fld", "fstp", "fdiv", "fmul", "fadd", "fsub", "fild", "fistp", "fld1", "fldz", "fchs",
                  "fdivr", "fsubr"):
            return self.x87(i)
        raise Unsupported("insn:" + mn)

    # ------------------------------------------------------------ ALU
    def alu(self, i):
        mn, ops = i.mn, i.ops
        d = ops[0]
        s = ops[1] if len(ops) > 1 else None
        op = {"inc": "+", "dec": "-", "add": "+", "sub": "-", "or": "|", "and": "&", "xor": "^"}[mn]
        sv = imm(1) if s is None else self.read_op(s, d.size or (d.regsize if d.kind == "reg" else None))
        self.mark_use(sv)
        if d.kind == "reg":
            if d.regsize != 4:
                raise Unsupported("alu-narrow-reg")
            cur = self.read_reg(d.reg)
            self.mark_use(cur)
            if (op == "|" and sv == imm(0xFFFFFFFF)) or (op == "&" and sv == imm(0)):
                self.write_reg(d.reg, sv)       # x | -1 and x & 0 are constants
                self.flags = None
                return False
            self.write_reg(d.reg, ("bin", op, cur, sv))
            self.flags = ("res", self.read_reg(d.reg), self.read_reg(d.reg)) if mn in ("inc", "dec", "and", "or", "xor", "add", "sub") else None
            return False
        base, disp = self.addr_of(d)
        if isinstance(base, tuple) and base[0] == "stkslot":
            raise Unsupported("stack-rmw")
        self.mark_use(base)
        sz = d.size or 4
        cur = ("ld", base, disp, sz, False)
        self.stmts.append(Store(base, disp, sz, ("bin", op, cur, sv)))
        self.after_store(self.stmts[-1])
        self.flags = None
        return False

    # ------------------------------------------------------------ x87
    def fmem(self, op):
        base, disp = self.addr_of(op)
        if isinstance(base, tuple) and base[0] == "stkslot":
            raise Unsupported("fp-stack")
        self.mark_use(base)
        if op.size not in (4, 8):
            raise Unsupported("fp-size")
        return ("ld", base, disp, op.size, "fp")

    def x87(self, i):
        mn, ops = i.mn, i.ops
        if mn == "fld":
            if ops[0].kind != "mem":
                raise Unsupported("fld-reg")
            self.fstack.append(("fl", self.fmem(ops[0])))
            return False
        if mn == "fld1":
            self.fstack.append(("fl", ("imm", "1.0")))
            return False
        if mn == "fldz":
            self.fstack.append(("fl", ("imm", "0.0")))
            return False
        if mn in ("fdiv", "fmul", "fadd", "fsub", "fdivr", "fsubr") and len(ops) == 1 and ops[0].kind == "mem":
            if not self.fstack:
                raise Unsupported("fp-empty")
            a = self.fstack.pop()
            b = ("fl", self.fmem(ops[0]))
            op = {"fdiv": "/", "fmul": "*", "fadd": "+", "fsub": "-"}.get(mn)
            if op:
                self.fstack.append(("fl", ("bin", op, a, b)))
            else:
                op = {"fdivr": "/", "fsubr": "-"}[mn]
                self.fstack.append(("fl", ("bin", op, b, a)))
            return False
        if mn == "fstp" and ops[0].kind == "mem":
            if not self.fstack:
                raise Unsupported("fp-empty")
            v = self.fstack.pop()
            base, disp = self.addr_of(ops[0])
            if isinstance(base, tuple) and base[0] == "stkslot":
                raise Unsupported("fp-stack")
            self.mark_use(base)
            if ops[0].size not in (4, 8):
                raise Unsupported("fp-size")
            self.stmts.append(Store(base, disp, ops[0].size, v, fp=True))
            return False
        raise Unsupported("x87:" + mn)

    # ------------------------------------------------------------ calls
    def do_call(self, i, nxt, tail):
        sp = self.sp
        op = i.ops[0]
        if op.kind == "imm":
            target = op.val
        elif op.kind == "mem" and op.index is None and op.base is None:
            target = ("imp", op.disp & 0xFFFFFFFF)
        elif op.kind == "mem" and op.index is None:
            base, disp = self.addr_of(op)
            self.mark_use(base)
            target = ("vt", base, disp)
        else:
            raise Unsupported("call-operand")
        ecx = self.reg["ecx"][0]
        edx = self.reg["edx"][0]
        stack = list(reversed(self.pushes))
        idx = self.counter[0]
        c = Call(idx, target, ecx, edx, stack, 0, tail, "ecx" in self.written, "edx" in self.written,
                 self.reg["ecx"][1], self.reg["edx"][1])
        if tail:
            if self.pushes or self.saved:
                raise Unsupported("tail-with-pushes")
            self.counter[0] += 1
            sp.calls.append(c)
            self.stmts.append(c)
            self.leaf = dict(ret=("call", c.idx), ret_width=4, ret_fp=False, retn=0, tail=True)
            return True
        self.counter[0] += 1
        sp.calls.append(c)
        self.stmts.append(c)
        self.last_call = c
        nxt_cleanup = nxt is not None and ((nxt.mn == "add" and nxt.ops and nxt.ops[0].kind == "reg"
                                           and nxt.ops[0].reg == "esp") or
                                          (nxt.mn == "pop" and nxt.ops and nxt.ops[0].reg == "ecx"
                                           and len(stack) == 1))
        if not nxt_cleanup:
            self.espoff -= 4 * len(stack)
        self.pushes = []
        # clobbers: caller-saved registers hold the call result / garbage
        self.reg["eax"] = (("call", c.idx), 4)
        self.written.add("eax")
        self.reg["ecx"] = (None, 4)
        self.reg["edx"] = (None, 4)
        self.written.discard("ecx")
        self.written.discard("edx")
        self.flags = None
        self.fstack = []
        return False

    def finish_ret(self):
        if self.pushes or self.saved:
            raise Unsupported("push-unbalanced")
        if self.fstack:
            if len(self.fstack) != 1:
                raise Unsupported("fp-stack-left")
            self.leaf = dict(ret=self.fstack[0], ret_width=4, ret_fp=True, retn=self.retn, tail=False)
            return True
        v, w = self.reg["eax"]
        self.leaf = dict(ret=v, ret_width=w, ret_fp=False, retn=self.retn, tail=False)
        return True

    # ------------------------------------------------------------ branches
    def clone(self):
        import copy
        memo = {id(self.sp): self.sp, id(self.counter): self.counter, id(self.tc): self.tc, id(self.sp.insns): self.sp.insns}
        return copy.deepcopy(self, memo)

    def cond_expr(self, i):
        """Value tuple that is true when the conditional jump `i` is taken."""
        cc = i.mn[1:]
        if self.flags is None:
            raise Unsupported("jcc-no-flags")
        kind, a, b = self.flags
        if kind == "cmp":
            lhs, rhs = a, b
        elif kind == "test" and a == b or kind == "res":
            lhs, rhs = a, imm(0)
            if cc in ("ae", "b", "be", "a"):
                raise Unsupported("jcc-unsigned-after-test")
        else:
            lhs, rhs = ("bin", "&", a, b), imm(0)
            if cc in ("l", "ge", "le", "g", "s", "ns", "ae", "b", "be", "a"):
                raise Unsupported("jcc-test-two-operands")
        if kind == "res" and cc in ("l", "ge", "le", "g"):
            raise Unsupported("jcc-signed-after-alu")
        if cc in ("s", "ns"):
            return ("cmp", "<" if cc == "s" else ">=", lhs, imm(0)) if kind != "cmp" else \
                ("cmp", "<" if cc == "s" else ">=", ("bin", "-", lhs, rhs), imm(0))
        table = {"e": "==", "z": "==", "ne": "!=", "nz": "!=", "l": "<", "ge": ">=", "le": "<=", "g": ">",
                 "b": "u<", "ae": "u>=", "be": "u<=", "a": "u>"}
        if cc not in table:
            raise Unsupported("jcc:" + cc)
        return ("cmp", table[cc], lhs, rhs)

    def snapshot_cond(self, cond, by_addr, fall_addr, tgt_addr):
        """A loaded value that the branch tests and that stays live in a register becomes a local."""
        for name, (v, w) in list(self.reg.items()):
            if v is None:
                continue
            inner = v[1] if v[0] in ("sx", "zx") else v
            if inner[0] != "ld" or inner[4] == "fp" or not contains(cond, v):
                continue
            if w != 4 and inner[3] == 4:
                continue
            if not (calleesig.live_after(by_addr, fall_addr, name) or calleesig.live_after(by_addr, tgt_addr, name)):
                continue
            self.tc[0] += 1
            tid = self.tc[0]
            d = Decl(tid, v, "branch")
            self.stmts.append(d)
            t = ("tmp", tid, 4 if v[0] in ("sx", "zx") else v[3])
            cond = subst(cond, v, t)
            for n2, (v2, w2) in list(self.reg.items()):
                if v2 is not None:
                    self.reg[n2] = (subst(v2, v, t), w2)
            self.pushes = [subst(p, v, t) for p in self.pushes]
            self.flags = None
        return cond

    def explore(self, idx, depth=0):
        ins = self.sp.insns
        index = {i.addr: k for k, i in enumerate(ins)}
        by_addr = {i.addr: i for i in ins}
        if depth > 6:
            raise Unsupported("branch-depth")
        while idx < len(ins):
            i = ins[idx]
            if i.ops is None:
                raise Unsupported("operand-parse:" + i.text)
            m = re.match(r"^(j[a-z]+) (?:0x)?([0-9a-f]+)$", i.text)
            if m and i.mn != "jmp":
                tgt = int(m.group(2), 16)
                if tgt not in index or index[tgt] <= idx:
                    raise Unsupported("branch-target")
                cond = self.cond_expr(i)
                cond = self.snapshot_cond(cond, by_addr, i.addr + i.size, tgt)
                node = Node(self.stmts, cond=cond)
                a = self.clone()
                b = self.clone()
                a.stmts = []
                b.stmts = []
                node.taken = a.explore(index[tgt], depth + 1)
                node.fall = b.explore(idx + 1, depth + 1)
                return node
            if i.mn == "jmp" and m:
                tgt = int(m.group(2), 16)
                if tgt in index:
                    if index[tgt] <= idx:
                        raise Unsupported("backward-jump")
                    idx = index[tgt]
                    continue
            nxt = ins[idx + 1] if idx + 1 < len(ins) else None
            if self.step(i, nxt):
                lf = self.leaf
                return Node(self.stmts, ret=lf["ret"], ret_width=lf["ret_width"], ret_fp=lf["ret_fp"],
                            retn=lf["retn"], tail=lf["tail"])
            idx += 1
        raise Unsupported("fell-off-end")


def leaves(node):
    if node.cond is None:
        yield node
    else:
        yield from leaves(node.taken)
        yield from leaves(node.fall)


def lift(addr):
    size, insns = x86.extent(addr)
    if size == 0:
        raise Unsupported("no-code")
    L = Lifter(addr, size, insns)
    root = L.explore(0)
    sp = L.sp
    lv = list(leaves(root))
    sp.nstack = max([sp.nstack] + [l.retn // 4 for l in lv])
    if root.cond is None:
        sp.stmts = root.stmts
        sp.ret, sp.ret_width, sp.ret_fp, sp.retn = root.ret, root.ret_width, root.ret_fp, root.retn
    else:
        sp.tree = root
        sp.retn = max(l.retn for l in lv)
        if len({l.retn for l in lv}) > 1:
            raise Unsupported("mixed-retn")
    if not (insns[-1].mn.startswith("ret") or insns[-1].mn == "jmp"):
        raise Unsupported("no-terminator")
    return sp
