import pyperclip

# === Configuration ===
start = 0
end = 100
name = "_REM1_"
output_to_clipboard = True   # comment out to print

# === Helpers ===
def get_arg_list(start: int, end: int, joiner: str = ", ", prefix: str = "a"):
    return joiner.join([f"{prefix}{j}" for j in range(start, end)])

def generate_macro(i: int) -> str:
  return f"#define {name}{i} {i-1}"

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
