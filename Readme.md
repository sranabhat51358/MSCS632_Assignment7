
# Statistics Calculator in C, OCaml, and Python

This project calculates the mean, median, and mode of user-provided integers using three programming paradigms:

- **C:** Procedural programming
- **OCaml:** Functional programming
- **Python:** Object-oriented programming

## Project Structure

```text
MSCS632-Statistics/
├── README.md
├── c/
│   └── statistics.c
├── ocaml/
│   └── statistics.ml
└── python/
    └── statistics_calculator.py
```

## How to Compile and Run

### 1. C

```bash
cd c
clang -std=c11 -Wall -Wextra -pedantic statistics.c -o statistics
./statistics
```

### 2. OCaml

```bash
cd ocaml
ocamlc -w +a-70 -o statistics statistics.ml
./statistics
```

### 3. Python

```bash
cd python
python3 statistics_calculator.py
```

Python does not require a separate compilation step.

## Example Output

For input values `4, 2, 7, 2, 9, 4`:

```text
Mean: 4.67
Median: 4.00
Mode: 2, 4
```

## Notes

- Enter the number of integers, followed by each integer when prompted.
- All three programs calculate the same statistics using their respective programming paradigms.
- Ensure the required compiler or Python interpreter is installed before running the programs.

