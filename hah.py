import pyperclip

# === Configuration ===
start = 1
end = 101
name = "_AP_ARG_"
output_to_clipboard = True   # comment out to print

# === Helpers ===
def get_arg_list(start: int, end: int, joiner: str = ", ", prefix: str = "a"):
    return joiner.join([f"{prefix}{j}" for j in range(start, end)])

def generate_macro(i: int) -> str:
  args = get_arg_list(0, i)
  body = ', '.join(f'(a0, a{j})' for j in range(1, i))
  return f"#define {name}{i-1}({args}) {body}"
# def generate_macro(i: int) -> str:
#   return f"#define {name}{i}({get_arg_list(0, i)}) {get_arg_list(1, i)}"

# === Macro Generation ===
lines = []
for i in range(start, end):
    lines.append(generate_macro(i))

output = '\n'.join(lines)


# === Output ===
try:
  output_to_clipboard
  pyperclip.copy(output)
except:
  print(output)
