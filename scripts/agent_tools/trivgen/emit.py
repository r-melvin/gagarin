#!/usr/bin/env python3
# Provenance: original. C++ emission for trivgen Specs (VC6, /Gr default, no steering).
"""Turn a lift.Spec into C++ pieces (placeholders only).

Names: Obj_<addr> receiver view of the function at <addr>, FUN_<addr>
functions, DAT_<addr> globals, Gbl_<addr> view of a global object, unknown_<off>
members.  A variant is a dict of knobs (narrow-integer spelling, return type
spelling) cycled by the verify loop when an attempt does not match.
"""
import dataclasses
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
import common  # noqa: E402
import lift  # noqa: E402
import calleesig  # noqa: E402
import pe_imports  # noqa: E402
from lift import Call, Decl, Store, Unsupported, imm  # noqa: E402


def hx(v, w=8):
    return f"{v:0{w}X}"


def section(va):
    return common.pe().section_of(va)


def is_data_addr(v):
    return section(v) in (".data", ".rdata", ".bss")


@dataclass
class Field:
    off: int
    size: int
    kind: str = "int"          # int | ptr | fp
    ptr: str = None            # pointee view name when kind == ptr
    sg: str = "u"
    uns: bool = False

    def ctype(self, v1):
        if self.kind == "ptr":
            return self.ptr + "*"
        if self.kind == "fp":
            return "double" if self.size == 8 else "float"
        if self.size == 4:
            return "unsigned int" if self.uns else "int"
        if self.size == 2:
            return "short" if self.sg == "s" else "unsigned short"
        return "char" if self.sg == "s" else v1


@dataclass
class View:
    name: str
    fields: dict = field(default_factory=dict)
    methods: dict = field(default_factory=dict)   # addr -> declaration text
    vslots: dict = field(default_factory=dict)    # slot -> declaration text
    global_obj: int = None


@dataclass
class Glob:
    addr: int
    ctype: str
    const: bool = False
    array: bool = False


@dataclass
class Out:
    spec: object
    var: dict
    views: dict
    globals: dict
    protos: dict            # addr -> (key, decl)
    body: str               # .cpp definition text (without annotation)
    decl: str               # header declaration for free functions ('' for members)
    member_of: str = None
    mdecl: str = ""         # member declaration line
    kind: str = ""
    pattern: str = ""
    mname: str = None       # manifest name override (canonical members)
    sym_hint: str = None    # decorated-name fragment that locates the symbol when it has no FUN_<addr>
    canon: dict = None      # canonical class declaration used


class Emitter:
    def __init__(self, spec, var):
        self.sp = spec
        self.var = var
        self.A = spec.addr
        self.fname = f"FUN_{hx(self.A)}"
        self.views = {}
        self.globals = {}
        self.protos = {}
        self.argtype = {}
        self.this_used = False
        self.p0_scalar = False
        self.p1_used = False
        self.kind = None
        self.callv = {}
        self.uns = set()
        self.call_ct = {}
        self.tmptype = {}
        self.lea_target = None

    # ------------------------------------------------------------ views / paths
    def vname(self, path):
        a = hx(self.A)
        k = path[0]
        if k == "this":
            n, rest = f"Obj_{a}", path[1:]
        elif k == "stk":
            n, rest = f"Arg{path[1] + 1}_{a}", path[2:]
        elif k == "g":
            if len(path) == 2:
                return self._mk(f"Gbl_{hx(path[1])}")
            n, rest = f"Gbl_{hx(path[1])}", path[2:]
            return self._mk(n + "".join(f"_{o:X}" for o in rest))
        elif k == "gp":
            n, rest = f"Gptr_{hx(path[1])}", path[2:]
        elif k == "tmp":
            return self.vname(self.path_of(self.tmpsrc[path[1]]) + tuple(path[2:]))
        else:
            raise Unsupported("view-root")
        if rest:
            n += "".join(f"_{o:X}" for o in rest)
        return self._mk(n)

    def _mk(self, name):
        if name not in self.views:
            self.views[name] = View(name)
        return self.views[name]

    def path_of(self, v):
        t = v[0]
        if t == "p0":
            return ("this",)
        if t == "stk":
            return ("stk", v[1])
        if t == "ld":
            _, base, disp, size, sg = v
            if size != 4 or sg == "fp":
                raise Unsupported("narrow-pointer")
            if base is None:
                return ("gp", disp)
            return self.path_of(base) + (disp,)
        if t == "imm" and is_data_addr(v[1]):
            return ("g", v[1])
        if t == "tmp":
            src = self.tmpsrc.get(v[1])
            if src is None:
                raise Unsupported("pointer-from-tmp")
            self.mark_chain(self.path_of(src))
            return ("tmp", v[1])
        raise Unsupported("pointer-from-" + t)

    def depth0(self, path):
        return 1 if path[0] == "this" else 2

    def mark_chain(self, path):
        """Each hop through memory is a pointer field typed as a pointer to the next view."""
        if len(path) <= self.depth0(path):
            return
        parent = path[:-1]
        self.mark_chain(parent)
        pv = self.vname(parent)
        f = pv.fields.get(path[-1])
        child = self.vname(path).name
        if f is None:
            pv.fields[path[-1]] = Field(path[-1], 4, "ptr", child)
        elif f.size != 4 or f.kind not in ("int", "ptr"):
            raise Unsupported("field-kind-conflict")
        else:
            f.kind, f.ptr = "ptr", child

    def root_text(self, path):
        """Expression for the pointer/object at the root of `path`, '' for implicit this."""
        k = path[0]
        if k == "this":
            self.this_used = True
            return "a1->" if self.kind == "fastcall" else ""
        if k == "stk":
            n = self.vname(path[:2]).name
            self.argtype[path[1]] = n + "*"
            return f"a{self.argpos(path[1])}->"
        if k == "tmp":
            return f"t{path[1]}->"
        if k == "gp":
            self.globals[path[1]] = Glob(path[1], self.vname(path[:2]).name + "*")
            return f"DAT_{hx(path[1])}->"
        if k == "g":
            self.globals[path[1]] = Glob(path[1], self.vname(path[:2]).name)
            self.vname(path[:2]).global_obj = path[1]
            return f"DAT_{hx(path[1])}."
        raise Unsupported("root")

    def argpos(self, k):
        """1-based position of stack arg k in the parameter list."""
        extra = 0
        if self.kind == "fastcall":
            extra = 2
        return k + 1 + extra

    def member_text(self, path, disp):
        self.mark_chain(path)
        txt = self.root_text(path[:self.depth0(path)])
        sep = txt[-1] if txt else None
        hops = path[self.depth0(path):]
        pre = txt
        for h in hops:
            pre += f"unknown_{hx(h, 2)}->"
        if path[0] == "gp" and not hops:
            self.globals[path[1]] = Glob(path[1], self.vname(path).name + "*")
        elif path[0] == "gp":
            self.globals[path[1]] = Glob(path[1], self.vname(path[:2]).name + "*")
        return pre + f"unknown_{hx(disp, 2)}"

    def field_decl(self, base, disp, size, kind, sg):
        path = self.path_of(base)
        self.mark_chain(path)
        v = self.vname(path)
        f = v.fields.get(disp)
        if f is None:
            f = v.fields[disp] = Field(disp, size, kind, sg=sg)
        else:
            if f.size != size:
                raise Unsupported("field-size-conflict")
            if kind == "fp" and f.kind != "fp":
                raise Unsupported("field-kind-conflict")
            if sg == "s":
                f.sg = "s"
        if (base, disp) in self.uns:
            f.uns = True
        return path

    def global_scalar(self, addr, size, fp, sg):
        sec = section(addr)
        if sec not in (".data", ".rdata", ".bss"):
            raise Unsupported(f"abs-address-in-{sec}")
        if fp:
            ct = "double" if size == 8 else "float"
        elif size == 4:
            ct = "unsigned int" if (None, addr) in self.uns else "int"
        elif size == 2:
            ct = "short" if sg == "s" else "unsigned short"
        else:
            ct = "char" if sg == "s" else self.var.get("v1", "unsigned char")
        g = self.globals.get(addr)
        if g is not None and (g.ctype != ct or g.array):
            raise Unsupported("global-type-conflict")
        self.globals[addr] = Glob(addr, ct, const=(sec == ".rdata"))
        return f"DAT_{hx(addr)}"

    def global_array(self, addr):
        g = self.globals.get(addr)
        if g is not None and not g.array:
            raise Unsupported("global-type-conflict")
        self.globals[addr] = Glob(addr, "char", array=True)
        return f"DAT_{hx(addr)}"

    # ------------------------------------------------------------ expressions
    def mem(self, base, disp, size, fp=False, sg="u"):
        if base is None:
            return self.global_scalar(disp, size, fp, sg)
        if disp < 0 or disp >= 0x80000000:
            raise Unsupported("negative-offset")
        if base[0] == "lea":
            raise Unsupported("mem-of-lea")
        path = self.field_decl(base, disp, size, "fp" if fp else "int", sg)
        return self.member_text(path, disp)

    def ex(self, v):
        t = v[0]
        if t == "imm":
            val = v[1]
            if val >= 0xFFFFFF00:
                return str(val - 0x100000000)
            return str(val) if val < 10 else f"0x{val:X}"
        if t == "p0":
            self.p0_scalar = True
            return "a1"
        if t == "p1":
            self.p1_used = True
            return "a2"
        if t == "stk":
            self.argtype.setdefault(v[1], "unsigned int" if ("stk", v[1]) in self.uns else "int")
            return f"a{self.argpos(v[1])}"
        if t == "tmp":
            return f"t{v[1]}"
        if t == "call":
            if self.inline.get(v[1]):
                return self.inline[v[1]]
            return f"c{v[1]}"
        if t == "ld":
            _, base, disp, size, sg = v
            return self.mem(base, disp, size, sg == "fp", "u")
        if t == "lea":
            _, base, disp = v
            path = self.path_of(base)
            self.field_decl(base, disp, 4, "int", "u")
            return "&" + self.member_text(path, disp)
        if t == "zx":
            return self.ex(v[1])
        if t == "sx":
            inner = v[1]
            if inner[0] != "ld":
                raise Unsupported("sx-non-load")
            _, base, disp, size, sg = inner
            return self.mem(base, disp, size, False, "s")
        if t == "lo":
            if v[1][0] == "stk" and self.var.get("narrowp"):
                self.argtype[v[1][1]] = self.var.get("v1", "unsigned char")
                return f"a{self.argpos(v[1][1])}"
            if v[1][0] == "call":
                self.call_ct[v[1][1]] = self.var.get("v1", "unsigned char")
                return self.ex(v[1])
            return f"({'unsigned short' if v[2] == 2 else 'unsigned char'}){self.ex(v[1])}"
        if t == "bin":
            _, op, a, b = v
            if op == "+" and a in getattr(self, "proots", ()) and b[0] == "imm":
                return self.ex(("lea", a, b[1]))
            o = {"shl": "<<", "shr": ">>", "sar": ">>"}.get(op, op)
            if op == "shr":
                self.mark_uns(a)
            return f"({self.ex(a)} {o} {self.ex(b)})"
        if t == "un":
            return f"({'~' if v[1] == 'not' else '-'}{self.ex(v[2])})"
        if t == "cmp":
            _, cc, a, b = v
            if cc.startswith("u"):
                self.mark_uns(a)
                self.mark_uns(b)
                cc = cc[1:]
            return f"({self.ex(a)} {cc} {self.ex(b)})"
        if t == "fl":
            return self.exf(v[1])
        raise Unsupported("ex:" + t)

    def mark_uns(self, v):
        if v[0] == "ld":
            self.uns.add((v[1], v[2]))
        elif v[0] == "stk":
            self.uns.add(("stk", v[1]))
        elif v[0] == "tmp":
            self.tmptype[v[1]] = "unsigned int"
        elif v[0] in ("bin", "un"):
            for x in v[2:]:
                if isinstance(x, tuple):
                    self.mark_uns(x)

    def exf(self, v):
        if v[0] == "ld":
            return self.ex(v)
        if v[0] == "imm":
            return v[1]
        if v[0] == "bin":
            _, op, a, b = v
            f = lambda x: self.exf(x[1]) if x[0] == "fl" else self.exf(x)
            return f"({f(a)} {op} {f(b)})"
        raise Unsupported("exf")

    # ------------------------------------------------------------ driver
    def pick_kind(self):
        sp = self.sp
        if sp.uses_edx:
            return "fastcall"
        if sp.uses_ecx or sp.flags.get("member"):
            return "member"
        if sp.retn:
            return "stdcall"
        return "cdecl"

    def build_canon(self):
        """Out-of-line definition of a member that the canonical class header already declares."""
        sp = self.sp
        c = sp.flags.get("canon")
        if not c:
            raise Unsupported("no-canonical-declaration")
        if sp.tree is not None or sp.stmts or sp.calls:
            raise Unsupported("canonical-needs-fields")
        params = c["params"]
        n = 0 if params in ("", "void") else params.count(",") + 1
        if sp.retn != 4 * n:
            raise Unsupported("canonical-signature-mismatch")
        rt = c["rt"]
        lines = []
        if sp.ret is None:
            if rt != "void":
                raise Unsupported("canonical-return-mismatch")
        elif sp.ret[0] == "imm" and rt != "void":
            val = sp.ret[1]
            base = rt.replace("const", "").strip()
            if base == "bool" and val in (0, 1):
                lines.append(f"return {'true' if val else 'false'};")
            elif base.endswith("*") and val == 0:
                lines.append("return 0;")
            elif base in ("int", "long", "unsigned int", "unsigned long", "short", "unsigned short", "char",
                          "unsigned char"):
                lines.append(f"return {self.ex(sp.ret)};")
            else:
                raise Unsupported("canonical-return-type")
        else:
            raise Unsupported("canonical-return-mismatch")
        head = f"{rt} {c['cls']}::{c['name']}({params}){' const' if c['const'] else ''}"
        body = head + "\n{\n" + "".join(f"    {t}\n" for t in lines) + "}\n"
        return Out(sp, self.var, {}, {}, {}, body, "", c["cls"], "", "canon", "", f"{c['cls']}::{c['name']}",
                   f"?{c['name']}@{c['cls']}@@", c)

    def build(self):
        sp = self.sp
        if self.var.get("canon"):
            return self.build_canon()
        root = sp.tree if sp.tree is not None else lift.Node(
            sp.stmts, ret=sp.ret, ret_width=sp.ret_width, ret_fp=sp.ret_fp, retn=sp.retn,
            tail=bool(sp.calls and sp.calls[-1].tail))
        if self.var.get("inline_tmps"):
            root = self.inline_tmps_tree(root)
        self.root = root
        self.nodes = list(walk_nodes(root))
        self.calls = sorted({st.idx: st for nd in self.nodes for st in nd.stmts if isinstance(st, Call)}.values(),
                            key=lambda c: c.idx)
        self.tmpsrc = {st.idx: st.value for nd in self.nodes for st in nd.stmts if isinstance(st, Decl)}
        self.kind = getattr(self, "kind_force", None)
        self.prescan_calls()
        self.proots = self.ptr_roots()
        if self.kind is None:
            self.kind = self.pick_kind()
        # which call values are consumed beyond a direct return, over the whole tree
        used = set()
        for nd in self.nodes:
            vals = []
            for st in nd.stmts:
                if isinstance(st, (Store, Decl)):
                    vals.append(st.value)
                elif isinstance(st, Call):
                    vals += list(st.stack) + [x for x in (st.ecx, st.edx) if x is not None]
            if nd.cond is not None:
                vals.append(nd.cond)
            for v in vals:
                for n in _walk(v):
                    if n[0] == "call":
                        used.add(n[1])
        self.inline = {}
        for lf in self.nodes:
            if lf.cond is not None or lf.ret is None or lf.ret[0] == "call":
                continue
            calls_here = [st for st in lf.stmts if isinstance(st, Call)]
            for n in _walk(lf.ret):
                if n[0] == "call":
                    if n[1] not in used and calls_here and lf.stmts[-1] is calls_here[-1] and calls_here[-1].idx == n[1]:
                        self.inline[n[1]] = None
                    else:
                        used.add(n[1])
        self.used_elsewhere = used
        self.pending = []
        self.leaf_types = []
        self.ret_call = None
        self.ret_text = None
        self.decl_ld = {}
        if self.var.get("brstyle") in ("ifA", "ifB"):
            tv = self.two_valued(root) if root.cond is not None else None
            if tv is None:
                raise Unsupported("not-two-valued-tree")
            tgt = tv[0] if self.var["brstyle"] == "ifA" else tv[1]
            other = tv[1] if self.var["brstyle"] == "ifA" else tv[0]
            decls = [st for nd in walk_nodes(root) for st in nd.stmts if isinstance(st, Decl)]
            lines = self.finish_items(self.render_items(decls))
            text = self.bx_text(self.boolexpr(root, lambda nd: (nd.ret, nd.ret_width) == tgt))
            la = lift.Node([], ret=tgt[0], ret_width=tgt[1])
            lb = lift.Node([], ret=other[0], ret_width=other[1])
            ta, ra = self.ret_parts(la)
            tb, rb = self.ret_parts(lb)
            self.leaf_types += [ta, tb]
            lines += [f"if ({self.strip(text)})", "{", f"    return {ra};", "}", f"return {rb};"]
        elif self.var.get("brstyle") == "bool":
            if root.cond is None or not self.bool_leaves(root):
                raise Unsupported("not-boolean-tree")
            lines = []
            for nd in walk_nodes(root):
                if nd.cond is not None or nd.stmts:
                    pass
            decls = [st for nd in walk_nodes(root) for st in nd.stmts if isinstance(st, Decl)]
            lines += self.finish_items(self.render_items(decls))
            text = self.bx_text(self.boolexpr(root))
            for lf in self.nodes:
                if lf.cond is None:
                    self.leaf_types.append(self.ret_parts(lf)[0])
            lines.append(f"return {self.strip(text)};")
        else:
            lines = self.render_node(root, 0)
        rtype = self.unify_ret()
        self.finish_protos()
        resolved = []
        for ln in lines:
            def sub(m):
                kind, idx = m.group(1), int(m.group(2))
                if kind == "T":
                    dv = self.decl_ld[idx]
                    ct = self.tmptype.get(idx) or ("int" if dv[0] in ("sx", "zx") else self.ld_ctype(dv))
                    self.tmptype[idx] = ct
                    return ct
                return self.call_ct.get(idx, "int")
            resolved.append(re.sub(r"@([TC])(\d+)@", sub, ln))
        lines = resolved
        if self.kind == "member" and self.p0_scalar and not self.this_used and not getattr(self, "kind_force", None):
            e = Emitter(self.sp, self.var)
            e.kind_force = "fastcall"
            return e.build()
        return self.assemble(lines, rtype)

    def inline_tmps_tree(self, root):
        """Replace branch-snapshot locals by the loads they copy (no aliasing store can intervene)."""
        mapping = {}
        for nd in walk_nodes(root):
            for st in nd.stmts:
                if isinstance(st, Decl) and st.kind == "branch":
                    mapping[st.idx] = st.value

        def sub(v):
            if not isinstance(v, tuple) or not v:
                return v
            if v[0] == "tmp" and v[1] in mapping:
                return sub(mapping[v[1]])
            return (v[0],) + tuple(sub(x) if isinstance(x, tuple) else x for x in v[1:])

        def rw(nd):
            out = []
            for st in nd.stmts:
                if isinstance(st, Decl) and st.idx in mapping:
                    continue
                if isinstance(st, Store):
                    out.append(dataclasses.replace(st, base=sub(st.base), value=sub(st.value)))
                elif isinstance(st, Decl):
                    out.append(dataclasses.replace(st, value=sub(st.value)))
                elif isinstance(st, Call):
                    out.append(dataclasses.replace(st, ecx=sub(st.ecx), edx=sub(st.edx),
                                                   stack=[sub(x) for x in st.stack],
                                                   target=(sub(st.target) if isinstance(st.target, tuple) else st.target)))
                else:
                    out.append(st)
            n = dataclasses.replace(nd, stmts=out, cond=sub(nd.cond), ret=sub(nd.ret))
            if nd.cond is not None:
                n.taken = rw(nd.taken)
                n.fall = rw(nd.fall)
            return n
        return rw(root) if mapping else root

    def bool_leaves(self, root):
        for nd in walk_nodes(root):
            if nd.cond is None:
                if nd.ret is None or nd.ret[0] != "imm" or nd.ret[1] not in (0, 1) or nd.ret_fp or nd.tail:
                    return False
                if any(not isinstance(st, Decl) for st in nd.stmts):
                    return False
            elif any(not isinstance(st, Decl) for st in nd.stmts):
                return False
        return True

    def two_valued(self, root):
        """(valueA, valueB) leaf values if every leaf is a statement-free constant of one of two values."""
        vals = []
        for nd in walk_nodes(root):
            if nd.cond is None:
                if nd.ret is None or nd.ret[0] != "imm" or nd.ret_fp or nd.tail or nd.stmts:
                    return None
                key = (nd.ret, nd.ret_width)
                if key not in vals:
                    vals.append(key)
            elif any(not isinstance(st, Decl) for st in nd.stmts):
                return None
        return tuple(vals) if len(vals) == 2 else None

    def boolexpr(self, node, pred=None):
        K = lambda b: ("K", b)
        pred = pred or (lambda nd: nd.ret[1] == 1)
        if node.cond is None:
            return K(bool(pred(node)))
        t, f = self.boolexpr(node.taken, pred), self.boolexpr(node.fall, pred)
        C = ("C", node.cond)
        NC = ("C", negate(node.cond))
        if t == K(False):
            return NC if f == K(True) else ("and", NC, f)
        if t == K(True):
            return C if f == K(False) else ("or", C, f)
        if f == K(False):
            return C if t == K(True) else ("and", C, t)
        if f == K(True):
            return NC if t == K(False) else ("or", NC, t)
        return ("tern", C, t, f)

    def bx_text(self, e, parent=None):
        k = e[0]
        if k == "K":
            return "true" if e[1] else "false"
        if k == "C":
            return self.cond_text(e[1])
        if k in ("and", "or"):
            parts = []
            for x in e[1:]:
                parts.append(x)
            # flatten same-operator chains
            flat = []
            def fl(x):
                if x[0] == k:
                    for y in x[1:]:
                        fl(y)
                else:
                    flat.append(x)
            fl(e)
            txt = (" && " if k == "and" else " || ").join(self.bx_text(x, k) for x in flat)
            return f"({txt})" if parent and parent != k else txt
        if k == "tern":
            return f"({self.cond_text(e[1][1])} ? {self.bx_text(e[2])} : {self.bx_text(e[3])})"
        raise Unsupported("boolexpr")

    def render_items(self, stmts):
        """Statement texts for a block's stores, snapshots and calls (ret-mode calls recorded)."""
        items = []
        for st in stmts:
            if isinstance(st, Decl):
                items.append(("decl", st.idx, self.ex(st.value), st.value))
            elif isinstance(st, Store):
                lv = self.mem(st.base, st.disp, st.size, st.fp, "u")
                self.type_pointer_store(st)
                items.append(("txt", self.store_text(lv, st)))
            else:
                items.append(self.render_call(st))
        return items

    def type_pointer_store(self, st):
        """Storing the (pointer) receiver or a pointer argument types the destination as that pointer."""
        v = st.value
        if st.fp or st.size != 4 or v not in getattr(self, "proots", ()):
            return
        path = self.path_of(v)
        ptr = self.vname(path).name + "*"
        if st.base is None:
            g = self.globals.get(st.disp)
            if g is None or g.array:
                raise Unsupported("global-type-conflict")
            g.ctype = ptr
        else:
            bp = self.path_of(st.base)
            f = self.vname(bp).fields.get(st.disp)
            f.kind, f.ptr = "ptr", self.vname(path).name

    def finish_items(self, items):
        out = []
        for it in items:
            if it[0] == "txt":
                out.append(it[1])
            elif it[0] == "decl":
                _, idx, text, ld = it
                self.decl_ld[idx] = ld
                out.append(f"@T{idx}@ t{idx} = {text};")
            elif it[0] == "call":
                _, idx, text, mode = it
                if mode == "stmt":
                    out.append(text + ";")
                elif mode == "local":
                    out.append(f"@C{idx}@ c{idx} = {text};")
        return out

    def render_node(self, node, depth):
        """Lines (indented by `depth` extra levels) for a node and everything below it."""
        pad = "    " * depth
        # per-leaf return-call context
        self.ret_call = None
        if node.cond is None:
            self.ret_call = node.ret[1] if (node.ret is not None and node.ret[0] == "call") else None
            self.ret_text = None
        items = self.render_items(node.stmts)
        lines = [pad + t for t in self.finish_items(items)]
        if node.cond is None:
            rtype, rexpr = self.ret_parts(node)
            self.leaf_types.append(rtype)
            if rexpr is not None:
                lines.append(f"{pad}return {rexpr};")
            return lines
        joined = self.try_join(node, depth, lines)
        if joined is not None:
            return joined
        style = self.var.get("brstyle", "fall")
        if style == "fall":
            cond = self.cond_text(negate(node.cond))
            first, rest = node.fall, node.taken
        else:
            cond = self.cond_text(node.cond)
            first, rest = node.taken, node.fall
        then_lines = self.render_node(first, depth + 1)
        rest_lines = self.render_node(rest, depth)
        return lines + [f"{pad}if ({cond})", f"{pad}{{"] + then_lines + [f"{pad}}}"] + rest_lines

    def try_join(self, node, depth, lines):
        """if (c) { stmts } <shared leaf>: both arms are leaves with the same return."""
        a, b = node.taken, node.fall
        if a.cond is not None or b.cond is not None:
            return None
        if (a.ret, a.ret_width, a.ret_fp, a.retn, a.tail) != (b.ret, b.ret_width, b.ret_fp, b.retn, b.tail):
            return None
        if a.tail or any(isinstance(x, Call) for x in a.stmts + b.stmts):
            return None
        # strip a common suffix of statements
        sa, sb = list(a.stmts), list(b.stmts)
        common = []
        while sa and sb and sa[-1] == sb[-1]:
            common.insert(0, sa.pop())
            sb.pop()
        if sa and sb:
            return None
        pad = "    " * depth
        # the arm with statements is the conditional one
        if sb:                      # fall arm has the statements: it runs when the branch is not taken
            cond = self.cond_text(negate(node.cond))
            body = sb
        elif sa:
            cond = self.cond_text(node.cond)
            body = sa
        else:
            body = []
            cond = None
        out = list(lines)
        if body:
            blk = self.finish_items(self.render_items(body))
            out += [f"{pad}if ({cond})", f"{pad}{{"] + [f"{pad}    {t}" for t in blk] + [f"{pad}}}"]
        tail = lift.Node(common, ret=a.ret, ret_width=a.ret_width, ret_fp=a.ret_fp, retn=a.retn, tail=a.tail)
        return out + self.render_node(tail, depth)

    def cond_text(self, cond):
        _, cc, a, b = cond
        if cc.startswith("u"):
            self.mark_uns(a)
            self.mark_uns(b)
            cc = cc[1:]
        if b == imm(0) and cc in ("==", "!="):
            t = self.strip(self.ex(a))
            if self.var.get("zerotest") == "bang":
                return t if cc == "!=" else f"!{t}" if t.replace('_', '').isalnum() else f"!({t})"
        return f"{self.strip(self.ex(a))} {cc} {self.strip(self.ex(b))}"

    def unify_ret(self):
        ts = [t for t in self.leaf_types]
        vals = [t for t in ts if t != "void"]
        if not vals:
            return "void"
        if len(vals) != len(ts):
            raise Unsupported("mixed-void-leaves")
        if len(set(vals)) == 1:
            return vals[0]
        small = {"bool", "unsigned char", "char"}
        if all(t in small for t in vals):
            return self.var.get("v1", "unsigned char")
        if all(t in small | {"int"} for t in vals):
            return "int"
        raise Unsupported("mixed-leaf-types")

    # ------------------------------------------------------------ calls
    def prescan_calls(self):
        """Resolve which entry registers are passed through to callees (using the callee's own bytes)."""
        sp = self.sp
        self.cres = {}
        for c in self.calls:
            T = c.target
            if isinstance(T, tuple) and T[0] == "imp":
                self.prescan_import(c)
                continue
            if isinstance(T, tuple) and T[0] == "vt":
                self.prescan_virtual(c)
                continue
            if not isinstance(T, int):
                raise Unsupported("indirect-call")
            sig = calleesig.sig(T)
            if sig is None:
                raise Unsupported("callee-sig")
            n = len(c.stack)
            ecx = c.ecx if (c.ecx is not None and (sig.reads_ecx or (c.ecx_set and c.ecx not in c.stack))) else None
            edx = c.edx if (c.edx is not None and (sig.reads_edx or (c.edx_set and c.edx not in c.stack))) else None
            if c.cleanup:
                ecx = edx = None
            elif c.ecx is None and sig.reads_ecx:
                raise Unsupported("undefined-ecx-argument")
            elif c.edx is None and sig.reads_edx:
                pass        # an undefined EDX read is most likely a scratch save/restore in the callee
            if c.tail and n:
                raise Unsupported("tail-with-stack")
            if c.cleanup:
                conv = "cdecl"
                expect = 0
            elif edx is not None:
                conv = "fastcall"
                expect = 4 * n
            elif ecx is not None:
                conv = "thiscall"
                expect = 4 * n
            elif n:
                conv = "stdcall"
                expect = 4 * n
            else:
                conv = "cdecl"
                expect = 0
            if conv == "thiscall" and ecx[0] == "imm" and not is_data_addr(ecx[1]):
                if n:
                    raise Unsupported("thiscall-int-receiver")
                conv = "fastcall"
            if sig.pops is not None and sig.pops != expect:
                if not (sig.pops == 0 and not n and conv in ("cdecl", "fastcall", "thiscall")):
                    raise Unsupported("callee-pops-mismatch")
            self.cres[c.idx] = dict(conv=conv, ecx=ecx, edx=edx, sig=sig)
            if ecx is not None and ecx[0] == "p0":
                sp.uses_ecx = True
            if edx is not None and edx[0] == "p1":
                sp.uses_edx = True

    def ptr_roots(self):
        """Entry values used as pointers anywhere in the function (p0 / stack args)."""
        roots = set()
        sp = self.sp

        def see(v):
            for n in _walk(v):
                if n[0] == "ld" and n[1] is not None and n[1][0] in ("p0", "stk"):
                    roots.add(n[1])
                if n[0] == "lea" and n[1][0] in ("p0", "stk"):
                    roots.add(n[1])
        for nd in self.nodes:
            for st in nd.stmts:
                if isinstance(st, Store):
                    if st.base is not None and st.base[0] in ("p0", "stk"):
                        roots.add(st.base)
                    see(st.value)
                elif isinstance(st, Decl):
                    see(st.value)
                elif isinstance(st, Call):
                    for v in list(st.stack) + [x for x in (st.ecx, st.edx) if x is not None]:
                        see(v)
            if nd.cond is not None:
                see(nd.cond)
            if nd.ret is not None:
                see(nd.ret)
        for c in self.calls:
            if isinstance(c.target, tuple) and c.target[0] == "vt" and c.target[1][0] == "ld":
                r = c.target[1][1]
                if r is not None and r[0] in ("p0", "stk"):
                    roots.add(r)
            if c.ecx is not None and c.ecx[0] in ("p0", "stk") and c.cleanup == 0 and isinstance(c.target, int):
                sig = calleesig.sig(c.target) if isinstance(c.target, int) else None
                if sig is not None and sig.reads_ecx:
                    roots.add(c.ecx)
        return roots

    def prescan_import(self, c):
        T = c.target
        ent = pe_imports.iat().get(T[1])
        if ent is None:
            raise Unsupported("call-through-non-import")
        dll, name = ent
        n = len(c.stack)
        if name.startswith("#"):
            raise Unsupported("import-by-ordinal")
        conv = "cdecl" if (c.cleanup or dll.lower().startswith("msvcrt")) else "stdcall"
        if conv == "stdcall" and not n and False:
            pass
        self.cres[c.idx] = dict(conv="import", imp=(dll, name, conv, T[1]), ecx=None, edx=None)

    def prescan_virtual(self, c):
        T = c.target
        _, base, disp = T
        if base[0] != "ld" or base[2] != 0 or base[3] != 4 or base[1] is None:
            raise Unsupported("indirect-call")
        if disp < 0 or disp % 4:
            raise Unsupported("virtual-offset")
        if c.ecx is None or c.ecx != base[1]:
            raise Unsupported("virtual-receiver-mismatch")
        if c.cleanup:
            raise Unsupported("virtual-cdecl")
        self.cres[c.idx] = dict(conv="virtual", ecx=base[1], edx=None, slot=disp // 4)
        if base[1][0] == "p0":
            self.sp.uses_ecx = True

    def argv(self, v):
        """Argument text for a value passed to a callee."""
        if v[0] == "n1":                      # a byte-sized register argument (8-bit write before the call)
            w = v[1]
            if w[0] == "imm":
                if self.var.get("v1") == "bool" and w[1] in (0, 1):
                    return "true" if w[1] else "false"
                return str(w[1])
            return self.strip(self.ex(w))
        if v[0] == "imm" and is_data_addr(v[1]):
            return self.global_array(v[1])
        if v[0] == "p0":
            self.this_used = True
            return "this" if self.kind == "member" else "a1"
        if v[0] == "call":
            return f"c{v[1]}"
        return self.strip(self.ex(v))

    def ptype_of(self, v):
        if v[0] == "n1":
            return self.var.get("v1", "unsigned char")
        if v[0] == "imm":
            return "void*" if is_data_addr(v[1]) else "int"
        if v[0] == "p0":
            return self.vname(("this",)).name + "*"
        if v[0] == "ld" and v[3] == 4 and v[4] != "fp":
            return self.ld_ctype(v)
        if v[0] == "stk":
            return self.argtype.get(v[1], "int")
        if v[0] == "tmp":
            return self.tmptype.get(v[1], "int")
        if v[0] == "lea":
            return "void*"
        if v[0] == "bin" and v[1] == "+" and v[2] in getattr(self, "proots", ()) and v[3][0] == "imm":
            return "void*"
        return "int"

    def recv_prefix(self, rv):
        """Text 'obj->' / 'obj.' / '' for the receiver value rv; also returns the view."""
        if rv[0] == "lea":
            raise Unsupported("thiscall-on-member-address")
        path = self.path_of(rv)
        self.mark_chain(path)
        if path == ("this",):
            self.this_used = True
            return ("a1->" if self.kind == "fastcall" else ""), self.vname(path)
        txt = self.root_text(path[:self.depth0(path)])
        for h in path[self.depth0(path):]:
            txt += f"unknown_{hx(h, 2)}->"
        return txt, self.vname(path)

    def call_rtype(self, c):
        if self.var.get("retvoid") and self.sp.tree is not None and c.idx not in self.used_elsewhere \
                and c.idx not in self.inline:
            return "void"
        if c.idx in self.inline:
            return "int"
        if c.idx in self.used_elsewhere:
            return "int"
        if c.tail or c.idx == self.ret_call:
            return self.var.get("callret", "void")
        return "void"

    def render_call(self, c):
        res = self.cres[c.idx]
        conv = res["conv"]
        T = c.target
        rt = self.call_rtype(c)
        args = [self.argv(v) for v in c.stack]
        if conv == "import":
            dll, name, cc, va = res["imp"]
            text = f"{name}({', '.join(args)})"
            self.pending.append(("import", va, rt, list(c.stack), (dll, name, cc), c.idx))
            return self.finish_call_item(c, text, rt)
        if conv == "virtual":
            prefix, view = self.recv_prefix(res["ecx"])
            fname = f"vf_{res['slot']}"
            text = f"{prefix}{fname}({', '.join(args)})"
            self.pending.append(("virtual", res["slot"], rt, view, list(c.stack), c.idx))
            return self.finish_call_item(c, text, rt)
        fname = f"FUN_{hx(T)}"
        if conv == "thiscall":
            prefix, view = self.recv_prefix(res["ecx"])
            text = f"{prefix}{fname}({', '.join(args)})"
            self.pending.append(("member", T, rt, view, list(c.stack), c.idx))
        elif conv == "fastcall":
            ecx = res["ecx"]
            if ecx is None and c.ecx is not None and not c.ecx_set and c.ecx[0] == "p0":
                ecx = c.ecx                      # untouched incoming ECX rides along unchanged
            if ecx is not None and c.ecx_w == 1 and c.ecx_set:
                ecx = ("n1", ecx)
            if res["edx"] is not None and c.edx_w == 1 and c.edx_set:
                res = dict(res, edx=("n1", res["edx"]))
            a0 = self.argv(ecx) if ecx is not None else "0"
            if res["edx"] is None:
                text = f"{fname}({', '.join([a0] + args)})"
                self.pending.append(("fast", T, rt, [ecx] + list(c.stack), c.idx))
            else:
                a1 = self.argv(res["edx"])
                text = f"{fname}({', '.join([a0, a1] + args)})"
                self.pending.append(("fast", T, rt, [ecx if ecx is not None else imm(0), res["edx"]] + list(c.stack), c.idx))
        elif conv == "stdcall":
            text = f"{fname}({', '.join(args)})"
            self.pending.append(("std", T, rt, list(c.stack), c.idx))
        else:
            text = f"{fname}({', '.join(args)})"
            self.pending.append(("cdecl", T, rt, list(c.stack), c.idx))
        return self.finish_call_item(c, text, rt)

    def finish_call_item(self, c, text, rt):
        if c.idx in self.inline:
            self.inline[c.idx] = text
            return ("call", c.idx, text, "inline")
        if c.idx in self.used_elsewhere:
            return ("call", c.idx, text, "local")
        if c.tail or c.idx == self.ret_call:
            if rt == "void":
                return ("call", c.idx, text, "stmt")
            self.ret_text = text
            return ("call", c.idx, text, "ret")
        return ("call", c.idx, text, "stmt")

    def finish_protos(self):
        for p in self.pending:
            kind, T, rt = p[0], p[1], p[2]
            rt = self.call_ct.get(p[-1], rt)
            fname = f"FUN_{hx(T)}"
            if kind == "import":
                dll, name, cc = p[4]
                pts = ", ".join(self.ptype_of(v) for v in p[3])
                ccs = "__cdecl" if cc == "cdecl" else "__stdcall"
                decl = f'extern "C" __declspec(dllimport) {rt} {ccs} {name}({pts});'
                self.protos[T] = (f"imp:{rt}:{pts}", decl, None, f"Import {name} from {dll} (IAT slot 0x{T:X})")
                continue
            if kind == "virtual":
                view, vals = p[3], p[4]
                pts = ", ".join(self.ptype_of(v) for v in vals)
                view.vslots[T] = f"    virtual {rt} vf_{T}({pts});"
                continue
            if kind == "member":
                view, vals = p[3], p[4]
                pts = ", ".join(self.ptype_of(v) for v in vals)
                view.methods[T] = f"{rt} {fname}({pts});"
            else:
                vals = p[3]
                pts = ", ".join(self.ptype_of(v) for v in vals)
                if kind == "fast":
                    decl, key = f"{rt} {fname}({pts});", f"fast:{rt}:{pts}"
                elif kind == "std":
                    decl, key = f"{rt} __stdcall {fname}({pts});", f"std:{rt}:{pts}"
                else:
                    decl, key = f"{rt} __cdecl {fname}({pts});", f"cdecl:{rt}:{pts}"
                self.protos[T] = (key, decl, T)

    def ld_ctype(self, v):
        _, base, disp, size, sg = v
        if base is None:
            return self.globals[disp].ctype
        path = self.path_of(base)
        return self.vname(path).fields[disp].ctype(self.var.get("v1", "unsigned char"))

    def store_text(self, lv, s):
        val = s.value
        if val[0] == "bin" and val[2][0] == "ld" and val[2][1:3] == (s.base, s.disp):
            op, rhs = val[1], val[3]
            if op in ("+", "-") and rhs == imm(1):
                return f"{lv}{op}{op};"
            return f"{lv} {op}= {self.ex(rhs)};"
        if s.size == 1 and val[0] == "imm" and self.var.get("v1") == "bool" and val[1] in (0, 1):
            return f"{lv} = {'true' if val[1] else 'false'};"
        if val in getattr(self, "proots", ()) and val[0] in ("p0", "stk"):
            return f"{lv} = {self.argv(val) if val[0] == 'p0' else self.ex(val)};"
        return f"{lv} = {self.strip(self.ex_trunc(val, s.size))};"

    def ex_trunc(self, v, size):
        """A value stored through a narrower lvalue: the truncation is the store's own conversion."""
        if v[0] == "lo" and size == v[2] and v[1][0] != "call":
            if v[1][0] == "stk" and self.var.get("narrowp"):
                return self.ex(v)
            return self.ex(v[1])
        return self.ex(v)

    @staticmethod
    def strip(t):
        """Drop one pair of redundant outer parentheses."""
        if t.startswith("(") and t.endswith(")"):
            depth = 0
            for k, ch in enumerate(t):
                depth += ch == "("
                depth -= ch == ")"
                if depth == 0 and k < len(t) - 1:
                    return t
            return t[1:-1]
        return t

    def ret_parts(self, leaf):
        sp = self.sp
        v = leaf.ret
        var = self.var
        v1 = var.get("v1", "unsigned char")
        if leaf.ret_fp:
            f = v[1]
            return ("double" if f[3] == 8 else "float") if f[0] == "ld" else "double", self.strip(self.ex(v))
        if v is None or (var.get("retvoid") and (sp.tree is not None or (leaf.stmts and not self.calls))):
            return "void", None
        if v[0] == "call" and v[1] == self.ret_call:
            if v[1] in self.used_elsewhere:
                return "int", f"c{v[1]}"
            rt = var.get("callret", "void")
            if rt == "void":
                return "void", None
            return rt, self.ret_text
        w = leaf.ret_width
        if v[0] == "imm":
            val = v[1]
            if w == 1:
                if v1 == "bool" and val in (0, 1):
                    return "bool", "true" if val else "false"
                return v1, self.ex(v)
            if is_data_addr(val):
                return "void*", self.global_array(val)
            return "int", self.ex(v)
        if v[0] == "p0":
            self.this_used = True
            return "@THIS@", "this" if self.kind == "member" else "a1"
        if w == 2 and v[0] != "zx":
            ex = self.ex(v)
            return var.get("v2", "unsigned short"), ex
        inner = v[1] if v[0] == "zx" and v[1][0] == "cmp" else (v if v[0] == "cmp" else None)
        if inner is not None:
            mode = var.get("retcmp", "expr")
            ex = self.ex(inner)
            if mode == "tern":
                return "bool", f"{ex} ? true : false"
            if mode == "int" or w == 4 and v[0] == "zx" and var.get("retcmp") == "int":
                return "int", self.strip(ex)
            return ("bool" if v1 == "bool" or w == 4 else v1), self.strip(ex)
        if w == 1:
            ex = self.ex(v)
            if v[0] == "ld":
                return self.ld_ctype(v) if False else v1, ex
            return v1, ex
        if v[0] == "ld":
            ex = self.ex(v)
            return self.ld_ctype(v), ex
        if v[0] == "stk":
            ex = self.ex(v)
            return self.argtype[v[1]], ex
        if v[0] == "tmp":
            return self.tmptype.get(v[1], "int"), self.ex(v)
        if v[0] == "lea":
            _, base, disp = v
            ex = self.ex(v)
            path = self.path_of(base)
            return self.vname(path).fields[disp].ctype(v1) + "*", ex
        return var.get("retint", "int"), self.strip(self.ex(v))

    # ------------------------------------------------------------ assemble
    def assemble(self, stmts, rtype):
        sp = self.sp
        kind = self.kind
        n = max(sp.nstack, sp.retn // 4)
        if kind == "member":
            # `this` is the receiver view of this function
            vw = self.vname(("this",))
            if rtype == "@THIS@":
                rtype = vw.name + "*"
            params = [self.argtype.get(k, "int") + f" a{k + 1}" for k in range(n)]
            const = not any(isinstance(s, Store) for s in sp.stmts) and sp.ret is not None and sp.ret[0] != "p0" \
                and sp.ret[0] != "lea" and not sp.calls and not self.var.get("nonconst")
            sig = f"{rtype} {self.fname}({', '.join(params)})" + (" const" if const else "")
            vw.methods[self.A] = sig + ";"
            body = f"{rtype} {vw.name}::{self.fname}({', '.join(params)})" + (" const" if const else "")
            return self.out(body, stmts, "", vw.name, sig + ";")
        params = []
        if kind == "fastcall":
            # a1 = ecx, a2 = edx, then stack
            if self.this_used and not self.p0_scalar:
                vw = self.vname(("this",))
                params.append(f"{vw.name}* a1")
                if rtype == "@THIS@":
                    rtype = vw.name + "*"
            elif self.this_used and self.p0_scalar:
                raise Unsupported("ecx-mixed-use")
            else:
                params.append("int a1")
            if sp.uses_edx or n:
                params.append("int a2")
            params += [self.argtype.get(k, "int") + f" a{k + 3}" for k in range(n)]
            cc = ""
        elif kind == "stdcall":
            params = [self.argtype.get(k, "int") + f" a{k + 1}" for k in range(n)]
            cc = "__stdcall "
        else:
            params = [self.argtype.get(k, "int") + f" a{k + 1}" for k in range(n)]
            cc = "__cdecl "
        if rtype == "@THIS@":
            raise Unsupported("returns-this-free")
        sig = f"{rtype} {cc}{self.fname}({', '.join(params)})"
        return self.out(sig, stmts, sig + ";", None, "")

    def out(self, head, stmts, decl, member_of, mdecl):
        body = head + "\n{\n" + "".join(f"    {s}\n" for s in stmts) + "}\n"
        return Out(self.sp, self.var, self.views, self.globals, self.protos, body, decl, member_of, mdecl,
                   self.kind)


def walk_nodes(n):
    yield n
    if n.cond is not None:
        yield from walk_nodes(n.taken)
        yield from walk_nodes(n.fall)


INV = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", "<=": ">", ">": "<=",
       "u<": "u>=", "u>=": "u<", "u<=": "u>", "u>": "u<="}


def negate(cond):
    _, cc, a, b = cond
    return ("cmp", INV[cc], a, b)


def _walk(v):
    if isinstance(v, tuple) and v:
        yield v
        for x in v[1:]:
            if isinstance(x, tuple):
                yield from _walk(x)


def features(sp):
    nodes_t = list(walk_nodes(sp.tree)) if sp.tree is not None else [
        lift.Node(sp.stmts, ret=sp.ret, ret_width=sp.ret_width, ret_fp=sp.ret_fp)]
    vals = []
    stores = []
    for nd in nodes_t:
        for st in nd.stmts:
            if isinstance(st, Store):
                vals.append(st.value)
                stores.append(st)
            elif isinstance(st, Decl):
                vals.append(st.value)
        if nd.cond is not None:
            vals.append(nd.cond)
        elif nd.ret is not None:
            vals.append(nd.ret)
    nodes = [n for v in vals for n in _walk(v)]
    rets = [nd for nd in nodes_t if nd.cond is None]
    word = any(nd.ret_width == 2 and nd.ret is not None for nd in rets) or any(st.size == 2 for st in stores)
    byte = (any(nd.ret_width == 1 and nd.ret is not None for nd in rets) or any(st.size == 1 for st in stores)
            or any((n[0] == "ld" and n[3] == 1) or n[0] == "lo" or (n[0] == "zx" and n[2] == 1) for n in nodes))
    cmpret = any(nd.ret is not None and any(n[0] == "cmp" for n in _walk(nd.ret)) for nd in rets)
    lostk = any(n[0] == "lo" and n[1][0] == "stk" for n in nodes)
    ret0 = sp.ret
    voidable = bool(stores) and ret0 is not None and not sp.calls and sp.tree is None
    helper = voidable and any(contains_v(st.value, ret0) for st in stores)
    tree = sp.tree is not None
    boolean = False
    if tree:
        boolean = all(nd.ret is not None and nd.ret[0] == "imm" and nd.ret[1] in (0, 1) and not nd.stmts
                      for nd in rets) and all(not any(not isinstance(st, Decl) for st in nd.stmts)
                                              for nd in nodes_t if nd.cond is not None)
    twovalued = False
    if tree:
        vv = []
        for nd in rets:
            if nd.ret is None or nd.ret[0] != "imm" or nd.stmts:
                vv = None
                break
            if (nd.ret, nd.ret_width) not in vv:
                vv.append((nd.ret, nd.ret_width))
        twovalued = vv is not None and len(vv) == 2
    has_branch_decl = any(isinstance(st, Decl) and st.kind == "branch" for nd in nodes_t for st in nd.stmts)
    garbage = tree and any(nd.ret is not None and nd.ret[0] == "call" for nd in rets)
    return dict(word=word, byte=byte, cmpret=cmpret, voidable=voidable, helper=helper, lostk=lostk, tree=tree,
                boolean=boolean, twovalued=twovalued, branch_decl=has_branch_decl, garbage=garbage)


def contains_v(v, target):
    return v == target or (isinstance(v, tuple) and any(contains_v(x, target) for x in v[1:] if isinstance(x, tuple)))


def variants(sp):
    """Ordered knob dictionaries to try for one function (duplicates are removed by body)."""
    f = features(sp)
    r = sp.ret
    boolish = sp.ret_width == 1 and r is not None and (r[0] == "cmp" or (r[0] == "imm" and r[1] in (0, 1)))
    if f["tree"]:
        boolish = f["boolean"]
    v1s = ["bool", "unsigned char", "char"] if boolish else ["unsigned char", "bool", "char"]
    if not f["byte"]:
        v1s = ["unsigned char"]
    if f["word"]:
        v1s = ["unsigned char", "char"]
    rcs = ["expr", "tern", "int"] if f["cmpret"] else ["expr"]
    rvs = ([True, False] if f["helper"] else [False, True]) if f["voidable"] else [False]
    if f["tree"]:
        rvs = [True, False] if f["garbage"] else [False, True]
    cr = ["void", "int", "bool"] if (sp.ret is not None and sp.ret[0] == "call") else [None]
    if f["tree"]:
        cr = ["void", "int", "bool"] if f["garbage"] else [None]
    nps = [True, False] if f["lostk"] else [False]
    brs = [None]
    inls = [False]
    if f["tree"]:
        brs = (["bool", "ifA", "ifB", "fall", "taken"] if f["boolean"]
               else ["ifA", "ifB", "fall", "taken"] if f["twovalued"] else ["fall", "taken"])
        inls = [True, False] if f["branch_decl"] else [False]
    out = []
    if sp.flags.get("canon") and not sp.stmts and not sp.calls and sp.tree is None:
        out.append({"canon": True})
    for rv in rvs:
     for br in brs:
      for inl in inls:
       for c in cr:
        for np_ in nps:
         for rc in rcs:
          for v1 in v1s:
            d = {"v1": v1}
            if f["word"]:
                d["v2"] = "unsigned short" if v1 == "unsigned char" else "short"
            if br:
                d["brstyle"] = br
            if inl:
                d["inline_tmps"] = True
            if c:
                d["callret"] = c
            if np_:
                d["narrowp"] = True
            if rc != "expr":
                d["retcmp"] = rc
            if rv:
                d["retvoid"] = True
            out.append(d)
    return out


def emit(spec, var):
    return Emitter(spec, var).build()
