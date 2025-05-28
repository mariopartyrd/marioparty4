# Scan for undocumented functions in C files
import re
import glob

# List of C keywords to exclude
c_keywords = {
    "if", "else", "while", "for", "do", "switch", "case", "default", "break", "continue",
    "return", "goto", "sizeof", "typedef", "struct", "union", "enum", "static", "extern",
    "const", "volatile", "inline", "register", "restrict", "auto", "void", "int", "char",
    "float", "double", "long", "short", "signed", "unsigned", "bool", "_Bool", "_Complex",
    "_Imaginary", "alignas", "alignof", "atomic", "thread_local", "noexcept", "static_assert",
    "constexpr"
}

# Regex to match function definitions (simple heuristic, may need further tuning)
func_def = re.compile(
    r"^[ \t]*(?:[a-zA-Z_][\w\s\*\(\),]*\*?\s+)?([a-zA-Z_]\w*)\s*\([^;{]*\)\s*\{",
    re.MULTILINE,
)

# Regex to match Doxygen-style comment immediately before function
doxygen_comment = re.compile(
    r"/\*\*.*?\*/\s*(?:[a-zA-Z_][\w\s\*\(\),]*\*?\s+)?([a-zA-Z_]\w*)\s*\([^;{]*\)\s*\{",
    re.DOTALL,
)

files = glob.glob("src/game/**/*.c", recursive=True)

for file in files:
    with open(file, "r", encoding="utf-8") as f:
        content = f.read()
        # Find all function definitions
        all_funcs = set(match.group(1) for match in func_def.finditer(content))
        # Find all documented functions
        documented_funcs = set(match.group(1) for match in doxygen_comment.finditer(content))
        # Filter out C keywords
        all_funcs = {func for func in all_funcs if func not in c_keywords}
        # Undocumented = all - documented
        undocumented = all_funcs - documented_funcs
        try:
            percent = (len(documented_funcs) / len(all_funcs)) * 100
            print(f"{file}: {percent:.2f}%")
        except ZeroDivisionError:
            print(f"{file}: 100%")
