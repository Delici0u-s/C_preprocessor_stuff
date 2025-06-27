def generate_header(n):
    with open("generated_macros.h", "w") as f:
        for i in range(n + 1):
            for j in range(n + 1):
                value = 1 if i == j else 0
                f.write(f"#define _EQ_{i}_{j} {value}\n")

generate_header(1000)
