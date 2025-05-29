# Scan for undocumented functions in C files
import re
import glob

from pathlib import Path

# List of C keywords to exclude
C_KEYWORDS = {
    "if", "else", "while", "for", "do", "switch", "case", "default", "break", "continue",
    "return", "goto", "sizeof", "typedef", "struct", "union", "enum", "static", "extern",
    "const", "volatile", "inline", "register", "restrict", "auto", "void", "int", "char",
    "float", "double", "long", "short", "signed", "unsigned", "bool", "_Bool", "_Complex",
    "_Imaginary", "alignas", "alignof", "atomic", "thread_local", "noexcept", "static_assert",
    "constexpr"
}

SKIP_FILES = [
    Path("src/game/kerent.c"),
    Path("src/game/font.c"),
    Path("src/game/ovllist.c"),
]

# Regex to match function definitions (simple heuristic, may need further tuning)
FUNC_DEF = re.compile(
    r"^[ \t]*(?:[a-zA-Z_][\w\s\*\(\),]*\*?\s+)?\*?\s*([a-zA-Z_]\w*)\s*\([^;{]*\)\s*\{",
    re.MULTILINE,
)

# Regex to match Doxygen-style comment immediately before function definition
DOXYGEN_COMMENT = re.compile(
    r"/\*\*.*?\*/\s*(?:[a-zA-Z_][\w\s\*\(\),]*\*?\s+)?\*?([a-zA-Z_]\w*)\s*\([^;{]*\)\s*\{",
    re.DOTALL,
)
# Unlabelled variables
UNLABELLED_VARIABLE = re.compile(
    r"^\s+(?!return)[a-zA-Z0-9]+\s+\*?((var_|temp_|sp|unk)\S?\d*\S?);",
    re.MULTILINE,
)

if __name__ == "__main__":
    files = glob.glob("src/game/**/*.c", recursive=True)

    total_funcs = 0
    total_documented = 0
    total_unlabelled = 0

    print("File".ljust(31), "Doc %", "Total".ljust(10), "Unlabelled Vars")
    print("-" * 64)

    for file in files:
        file_path = Path(file)
        if file_path in SKIP_FILES:
            continue
        with open(file_path, "r", encoding="utf-8") as f:
            content = f.read()
            # Find all function definitions
            all_funcs = set(match.group(1) for match in FUNC_DEF.finditer(content))
            # Find all documented functions
            documented_funcs = set(match.group(1) for match in DOXYGEN_COMMENT.finditer(content))
            # Filter out C keywords
            all_funcs = {func for func in all_funcs if func not in C_KEYWORDS}
            # Find all unlabeled variables
            all_vars = UNLABELLED_VARIABLE.findall(content)
            # Undocumented = all - documented
            undocumented = all_funcs - documented_funcs
            percent = (len(documented_funcs) / len(all_funcs)) * 100 if all_funcs else 0
            percent_str = f"{percent:05.2f}" if percent < 10 else f"{percent:05.2f}"
            total_count = f"({len(documented_funcs)}/{len(all_funcs)})".ljust(7)
            print(f"{file:<30}: {percent_str}% {total_count} : {len(all_vars)}")
            total_funcs += len(all_funcs)
            total_documented += len(documented_funcs)
            total_unlabelled += len(all_vars)

    if total_funcs:
        total_percent = (total_documented / total_funcs) * 100
    else:
        total_percent = 0

    print(f"\nTotal: {total_documented}/{total_funcs} functions documented ({total_percent:.2f}%)")
    print(f"Total unlabelled variables: {total_unlabelled}")
