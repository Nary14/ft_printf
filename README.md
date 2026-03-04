*This project has been created as part of the 42 curriculum by ***traomeli***.*
<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined:opsz,wght,FILL,GRAD@24,400,0,0&icon_names=swords" />

<span class="material-symbols-outlined">
swords 
</span>

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
make bonus  # Build with bonus features
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

## Resources

* [`man 3 printf`](https://man7.org/linux/man-pages/man3/printf.3.html) — Official printf documentation
* [`man 3 stdarg`](https://man7.org/linux/man-pages/man3/stdarg.3.html) — Variadic functions in C
* GNU C Library Documentation

### Use of AI

AI tools were used for concept clarification (variadic functions, format string parsing), debugging assistance, and README documentation.
 All implementation decisions and final code were written by the student.
