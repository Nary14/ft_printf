*This project has been created as part of the 42 curriculum by ***traomeli***.*

# ft_printf

## Description

**ft_printf** is a custom implementation of the standard C `printf()` function, developed as part of the 42 curriculum. The goal of this project is to recode `printf()` from libc, learning how to handle a variable number of arguments using variadic functions in C.

This project introduces the `<stdarg.h>` macros (`va_start`, `va_arg`, `va_copy`, `va_end`) and emphasizes writing well-structured, extensible code.

## Instructions

### Compilation

This will generate the static library file:

```bash
make
```

### Makefile Rules

```bash
make        # Build libftprintf.a
make clean  # Remove object files
make fclean # Remove object files and library
make re     # Rebuild from scratch
```

### Usage

```c
#include "ft_printf.h"
```

```bash
cc your_file.c libftprintf.a
```

> **Note:** The library must be created using `ar`. The `libtool` command is forbidden.  
> `libftprintf.a` must be created at the root of my repository.

## Supported Conversions

| Specifier | Description |
| --------- | ----------- |
| `%c` | Prints a single character |
| `%s` | Prints a string |
| `%p` | Prints a `void *` pointer in hexadecimal format |
| `%d` | Prints a decimal (base 10) number |
| `%i` | Prints an integer in base 10 |
| `%u` | Prints an unsigned decimal (base 10) number |
| `%x` | Prints a number in hexadecimal (base 16) lowercase |
| `%X` | Prints a number in hexadecimal (base 16) uppercase |
| `%%` | Prints a percent sign |

---

## Algorithm & Data Structure

### Overview

`ft_printf` works in three stages: **parse** the format string character by character, **dispatch** to the appropriate formatting function when a `%` specifier is found, and **accumulate** the total number of bytes written to return at the end.

### 1. Format String Parsing — Linear Scan

**Algorithm:** Single-pass linear scan (O(n) where n = length of format string).

The `ft_printf` function iterates over the format string one character at a time using a `while` loop. When it encounters a regular character, it writes it directly. When it encounters `%`, it advances one position and reads the next character to determine the conversion specifier.

```
format string: "Hello %d, %s!\n"
               ──────►──────────  single left-to-right pass
                      ↑
                      % triggers ft_util()
```

**Justification:** A linear scan is the simplest and most efficient approach for format string parsing. Since format strings are read sequentially with no need to backtrack or look ahead more than one character past `%`, O(n) time and O(1) space is optimal. No intermediate buffer or tokeniser is needed.

---

### 2. Variadic Argument Handling — `va_list`

**Data structure:** `va_list` (a compiler-managed pointer into the variadic argument area).

`va_start(args, format)` initialises `args` to point at the first variadic argument after `format`. Each call to `va_arg(args, type)` advances the pointer by the size of `type` and returns the value. `va_end` cleans up.

```c
va_list args;
va_start(args, format);
// inside ft_util:
va_arg(args, int)           // consumes next int
va_arg(args, char *)        // consumes next pointer
va_end(args);
```

**Justification:** `va_list` is the only portable, standards-compliant way to access a variable-length argument list in C. It maps directly onto the calling convention's argument-passing mechanism (registers or stack depending on ABI), with zero overhead compared to any manual alternative.

---

### 3. Specifier Dispatch — If-Chain

**Algorithm:** Sequential conditional checks (`if` chain inside `ft_util`).

When a `%` is detected, the specifier character is passed to `ft_util`, which tests it against each known specifier in order and calls the matching formatting function.

```
sign == 'd' → ft_putnbr()
sign == 'x' → ft_hexa(..., "0123456789abcdef")
sign == 'X' → ft_hexa(..., "0123456789ABCDEF")
sign == 'c' → ft_putchar()
sign == 's' → ft_putstr()
sign == 'p' → ft_ptr()
sign == 'u' → ft_putnbr_usd()
sign == '%' → ft_putchar('%')
```

**Justification:** With only 8 specifiers, a linear if-chain is perfectly readable and carries negligible performance cost. A jump table or hash map would add implementation complexity for no measurable gain at this scale. The if-chain also makes it straightforward to add new specifiers without restructuring.

---

### 4. Integer & Unsigned Printing — Recursion

**Algorithm:** Recursive decimal decomposition.

Both `ft_putnbr` (signed) and `ft_putnbr_usd` (unsigned) extract digits by dividing by 10 recursively until the quotient is less than 10, then print digits on the way back up the call stack — naturally producing left-to-right output without needing a temporary buffer.

```
ft_putnbr(423):
  ft_putnbr(42)
    ft_putnbr(4)  → prints '4'
  prints '2'      → prints '2'
prints '3'        → prints '3'
output: "423"
```

The INT_MIN edge case (`-2147483648`) is handled explicitly before the sign check because negating it would overflow a signed 32-bit integer — `-(-2147483648)` is undefined behaviour in C.

**Justification:** Recursion eliminates the need for a digit buffer (e.g. a local `char[12]` array) and produces concise, correct code. The maximum recursion depth for a 32-bit integer is 10 frames, so stack usage is negligible and there is no risk of stack overflow.

---

### 5. Hexadecimal Conversion — Recursion with Base String

**Algorithm:** Recursive base-16 decomposition using a character lookup string.

`ft_hexa` takes the number and a base string (`"0123456789abcdef"` or `"0123456789ABCDEF"`). It recurses on `nbr / 16` until the value is less than 16, then indexes into the base string with `nbr % 16` on the way back up.

```c
ft_hexa(255, "0123456789abcdef")
  ft_hexa(15, ...)   → prints base[15] = 'f'
  prints base[15]    → prints 'f'
output: "ff"
```

The same function handles `%x`, `%X`, and `%p` (cast to `unsigned long` to safely cover 64-bit addresses), making it reusable across three specifiers.

**Justification:** Passing the base string as a parameter is a clean, zero-duplication strategy — the only difference between lowercase and uppercase hex is which lookup string is used. Reusing `ft_hexa` for pointer addresses via an `unsigned long` cast avoids writing a separate conversion function.

---

### 6. Pointer Printing — NULL Guard + Prefix

**Algorithm:** Null-pointer guard followed by a `"0x"` prefix prepended to `ft_hexa`.

`ft_ptr` checks whether the pointer is `NULL` first and prints `(nil)` in that case, matching the behaviour of glibc `printf`. Otherwise it writes the literal `"0x"` and passes the pointer cast to `unsigned long` into `ft_hexa`.

**Justification:** Casting to `unsigned long` is the correct portable approach for printing pointer values as integers on both 32-bit and 64-bit systems, where `sizeof(void *)` equals `sizeof(unsigned long)` on all 42-school-targeted Linux and macOS platforms.

---

### 7. Return Value Tracking — Running Counter

**Data structure:** A single `int` accumulator (`i` in `ft_printf`).

Every output helper (`ft_putchar`, `ft_putstr`, `ft_hexa`, etc.) returns the number of bytes it wrote by propagating the return value of `write(2)`. Each return value is added to `i`, which is returned at the end of `ft_printf`.

**Justification:** This mirrors exactly what `write(2)` already provides — the byte count — making the accounting reliable even if a write partially succeeds. Tracking it as a running sum avoids any post-processing or secondary pass over the output.

---

### Summary Table

| Component | Choice | Reason |
|---|---|---|
| Format string parsing | Linear scan | O(n), no backtracking needed |
| Variadic arguments | `va_list` | Only portable C standard mechanism |
| Specifier dispatch | If-chain | 8 cases — simplicity beats a jump table |
| Integer printing | Recursion | No buffer needed, max 10 stack frames |
| Hex conversion | Recursion + base string param | One function covers `%x`, `%X`, and `%p` |
| Pointer printing | NULL guard + `unsigned long` cast | Portable across 32/64-bit, matches glibc |
| Return value | Running `int` counter | Directly propagates `write(2)` byte counts |

---

## Resources

* [`man 3 printf`](https://man7.org/linux/man-pages/man3/printf.3.html) — Official printf documentation
* [`man 3 stdarg`](https://man7.org/linux/man-pages/man3/stdarg.3.html) — Variadic functions in C
* GNU C Library Documentation

### Use of AI

AI tools were used for concept clarification (variadic functions, format string parsing), debugging assistance, and README documentation. All implementation decisions and final code were written by the student.
