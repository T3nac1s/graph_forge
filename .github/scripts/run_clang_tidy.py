#!/usr/bin/env python3
"""Run clang-tidy on project and test translation units."""

from __future__ import annotations

import json
import subprocess
import sys
from pathlib import Path


def main() -> int:
    root = Path(__file__).resolve().parents[2]
    compile_commands = root / "build" / "compile_commands.json"
    if not compile_commands.exists():
        print("Missing build/compile_commands.json", file=sys.stderr)
        return 1

    database = json.loads(compile_commands.read_text(encoding="utf-8"))
    test_sources = sorted((root / "tests" / "unit_tests").glob("*.cpp"))
    if not test_sources:
        print("No test sources found.", file=sys.stderr)
        return 1

    tidy = "clang-tidy-18"
    failures = 0
    for source in test_sources:
        entry = next(
            (item for item in database if Path(item["file"]) == source),
            None,
        )
        if entry is None:
            print(f"No compile command for {source}", file=sys.stderr)
            failures += 1
            continue

        command = [
            tidy,
            str(source),
            f"-p={root / 'build'}",
        ]
        print("Running:", " ".join(command))
        result = subprocess.run(command, cwd=root, check=False)
        if result.returncode != 0:
            failures += 1

    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
