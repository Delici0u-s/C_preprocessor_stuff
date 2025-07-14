import sys

# Script: generate_var_count.py
# Generates a C header with VAR_COUNT support from 0 up to N arguments using preprocessor macros.

MAX_ARGS = 1001
HEADER_GUARD = "D_MACROS_VAR_COUNT_H"

# Helper to create macro parameter list for _ARG_N
# E.g., for N=3: "_, _3, _2, _1, X_, ..."
def make_arg_list(n):
    params = ["_"] + [f"_{i}" for i in range(n, 1, -1)] + ["_1", "X_", "..."]
    return ", ".join(params)

# Generate count sequence from start down to end inclusive
# E.g., for N=3, start=3, end=0: "3, 2, 1, 0"
def make_count_list(start, end):
    return ", ".join(str(i) for i in range(start, end - 1, -1))


def main():
    lines = []
    lines.append(f"#ifndef {HEADER_GUARD}")
    lines.append(f"#define {HEADER_GUARD}")
    lines.append("#include <common.h>\n")

    # Define the _ARG_N macro to extract the count
    arg_params = make_arg_list(MAX_ARGS)
    lines.append(f"#define _ARG_{MAX_ARGS}({arg_params}) X_")

    # HAS_COMMA: detects presence of comma in __VA_ARGS__
    comma_flags = ", ".join(["1"] * MAX_ARGS + ["0"])
    lines.append("#define HAS_COMMA(...) \\")
    lines.append(f"  EXPAND(_ARG_{MAX_ARGS}(__VA_ARGS__, {comma_flags}))\n")

    # Helper for empty check
    lines.append("#define _TRIGGER_PARENTHESIS_(...) ,")
    lines.append("#define _PASTE5(_0, _1, _2, _3, _4) _0##_1##_2##_3##_4")
    lines.append("#define _IS_EMPTY_CASE_0001 ,")
    lines.append("#define _IS_EMPTY(_0, _1, _2, _3) \\")
    lines.append("  HAS_COMMA(_PASTE5(_IS_EMPTY_CASE_, _0, _1, _2, _3))\n")
    lines.append("#define IS_EMPTY(...)  \\")
    lines.append("  _IS_EMPTY(HAS_COMMA(__VA_ARGS__), HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__), \\")
    lines.append("            HAS_COMMA(__VA_ARGS__(/*empty*/)), HAS_COMMA(_TRIGGER_PARENTHESIS_ __VA_ARGS__(/*empty*/)))\n")

    # VAR_COUNT definitions
    lines.append("#define _VAR_COUNT_EMPTY_1(...) 0")
    # For non-empty, pass sequence from MAX_ARGS down to 0 (inclusive)
    count_seq = make_count_list(MAX_ARGS, 0)
    lines.append("#define _VAR_COUNT_EMPTY_0(...) \\")
    lines.append(f"  EXPAND(_ARG_{MAX_ARGS}(__VA_ARGS__, {count_seq}))")
    lines.append("#define VAR_COUNT(...) _CONCAT(_VAR_COUNT_EMPTY_, IS_EMPTY(__VA_ARGS__)(__VA_ARGS__))\n")

    lines.append(f"#endif /* {HEADER_GUARD} */")

    # Write to file
    with open("var_count.h", "w") as f:
        f.write("\n".join(lines))

    print(f"Generated var_count.h supporting 0..{MAX_ARGS} args")

if __name__ == '__main__':
    main()
