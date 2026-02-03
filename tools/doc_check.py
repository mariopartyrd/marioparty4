# Scan for undocumented functions in C files
import re
import glob
import argparse

from pathlib import Path

# List of C keywords to exclude
C_KEYWORDS = {
    "if",
    "else",
    "while",
    "for",
    "do",
    "switch",
    "case",
    "default",
    "break",
    "continue",
    "return",
    "goto",
    "sizeof",
    "typedef",
    "struct",
    "union",
    "enum",
    "static",
    "extern",
    "const",
    "volatile",
    "inline",
    "register",
    "restrict",
    "auto",
    "void",
    "int",
    "char",
    "float",
    "double",
    "long",
    "short",
    "signed",
    "unsigned",
    "bool",
    "_Bool",
    "_Complex",
    "_Imaginary",
    "alignas",
    "alignof",
    "atomic",
    "thread_local",
    "noexcept",
    "static_assert",
    "constexpr",
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
    r"^\s+(/\*.*\*/\s*)?(?!return)[a-zA-Z0-9]+\s+\*?\*?((var_|temp_|sp|unk|lbl_\d+_\S+_\d+)\S?\d*(_field\d*\s*:\s*)?\S?\[?\d*\]?)(\s*=\s*\S*)?;",
    re.MULTILINE,
)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Scan for undocumented functions in C files")
    parser.add_argument(
        "directory",
        nargs="?",
        default="src/game",
        help="Directory or file to scan for C files (default: src/game)"
    )
    parser.add_argument(
        "-l", "--list",
        action="store_true",
        help="List all undocumented functions and unlabelled variables"
    )
    parser.add_argument(
        "--list-functions",
        action="store_true",
        help="List only undocumented functions"
    )
    parser.add_argument(
        "--list-variables",
        action="store_true",
        help="List only unlabelled variables"
    )
    args = parser.parse_args()
    
    # Check if the path is a file or directory
    path = Path(args.directory)
    if path.is_file():
        files = [str(path)]
    elif path.is_dir():
        files = glob.glob(f"{args.directory}/**/*.c", recursive=True)
    else:
        print(f"Error: {args.directory} is not a valid file or directory")
        exit(1)

    total_funcs = 0
    total_documented = 0
    total_unlabelled = 0
    
    # Determine what to list
    list_funcs = args.list or args.list_functions
    list_vars = args.list or args.list_variables

    if not (list_funcs or list_vars):
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
            documented_funcs = set(
                match.group(1) for match in DOXYGEN_COMMENT.finditer(content)
            )
            # Filter out C keywords
            all_funcs = {func for func in all_funcs if func not in C_KEYWORDS}
            # Find all unlabeled variables
            all_vars = UNLABELLED_VARIABLE.findall(content)
            # Undocumented = all - documented
            undocumented = all_funcs - documented_funcs
            percent = (len(documented_funcs) / len(all_funcs)) * 100 if all_funcs else 0
            percent_str = f"{percent:05.2f}" if percent < 10 else f"{percent:05.2f}"
            total_count = f"({len(documented_funcs)}/{len(all_funcs)})".ljust(7)
            
            if not (list_funcs or list_vars):
                print(f"{file:<30}: {percent_str}% {total_count} : {len(all_vars)}")
            else:
                # Print file header with stats
                print(f"\n{file}: {percent_str}% {total_count} : {len(all_vars)}")
                
                # List undocumented functions if requested
                if list_funcs and undocumented:
                    print(f"  Undocumented functions ({len(undocumented)}):")
                    for func in sorted(undocumented):
                        print(f"    - {func}")
                
                # List unlabelled variables if requested
                if list_vars and all_vars:
                    print(f"  Unlabelled variables ({len(all_vars)}):")
                    for var in all_vars:
                        # var is a tuple from findall, extract the variable name (index 1)
                        var_name = var[1]
                        print(f"    - {var_name}")
            
            total_funcs += len(all_funcs)
            total_documented += len(documented_funcs)
            total_unlabelled += len(all_vars)

    if total_funcs:
        total_percent = (total_documented / total_funcs) * 100
    else:
        total_percent = 0

    print(
        f"\nTotal: {total_documented}/{total_funcs} functions documented ({total_percent:.2f}%)"
    )
    print(f"Total unlabelled variables: {total_unlabelled}")
