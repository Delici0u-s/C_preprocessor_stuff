import pyperclip

def safe_preview(fallback): return eval("preview_amount") if "preview_amount" in globals() else fallback

# === Configuration ===
# preview_amount = 10
start = 0
end = safe_preview(1002)
name = "_LF_"

# === Helpers ===
def get_arg_list(start: int, end: int, prefix: str = "a"):
    return [f"{prefix}{j}" for j in range(start, end)]

def generate_macro(i: int) -> str:
  arglist = get_arg_list(0, i)
  return f"#define {name}{i}(s, f, {", ".join(arglist)}) {" s() ".join([f"f({j})" for j in arglist])}"

# === Macro Generation ===
lines = []
for i in range(start, end):
    lines.append(generate_macro(i))

output = '\n'.join(lines)


# === Output ===
try:
  preview_amount
  print(output)
except:
  pyperclip.copy(output)
