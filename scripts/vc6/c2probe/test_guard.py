#!/usr/bin/env python3
"""Negative controls for guard.py: each kind of shim-driver leakage must be caught."""
import os, sys, tempfile, unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import guard as G


class GuardTest(unittest.TestCase):
    def test_clean_packet_passes(self):
        with tempfile.TemporaryDirectory() as d:
            Path(d, "README.md").write_text("Evidence: REA ev-123\n")
            Path(d, "manifest_delta.json").write_text('[{"addr": "0x401000"}]')
            self.assertEqual(G.scan_dir(d), [])

    def test_marker_in_report_or_log(self):
        with tempfile.TemporaryDirectory() as d:
            Path(d, "notes.md").write_text("# " + G.MARKER + " report\n")
            self.assertEqual(len(G.scan_dir(d)), 1)

    def test_path_into_probe_dirs(self):
        with tempfile.TemporaryDirectory() as d:
            Path(d, "build.log").write_text("cl -Fo build/c2probe/probe/x.obj\n")
            self.assertEqual(len(G.scan_dir(d)), 1)

    def test_manifest_row_with_marker(self):
        with tempfile.TemporaryDirectory() as d:
            Path(d, "manifest_delta.json").write_text('[{"addr":"0x1","note":"%s"}]' % G.MARKER)
            self.assertEqual(len(G.scan_dir(d)), 1)

    def test_ledger_object(self):
        import hashlib
        data = b"\x4c\x01fake-object"
        ledger = {hashlib.sha256(data).hexdigest()}
        self.assertEqual(len(G.scan_bytes("a.obj", data, ledger)), 1)
        self.assertEqual(G.scan_bytes("b.obj", data + b"x", ledger), [])

    def test_env(self):
        old = os.environ.pop("C2PROBE_DRIVER", None)
        try:
            self.assertEqual(G.env_findings(), [])
            os.environ["C2PROBE_DRIVER"] = "1"
            self.assertEqual(len(G.env_findings()), 1)
        finally:
            os.environ.pop("C2PROBE_DRIVER", None)
            if old is not None:
                os.environ["C2PROBE_DRIVER"] = old


if __name__ == "__main__":
    unittest.main()
