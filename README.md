# BoredOS libc

This repository houses a lightweight, custom subset of standard C library routines and basic POSIX syscall wrappers specifically written for the BoredOS userspace environment. 

It provides the minimal standard library interfaces (such as basic stdio, string manipulation, memory allocation, and socket structures) and startup assembler objects (`crt0.o`, `crti.o`, etc.) necessary to compile and boot the BoredOS shell, core utilities, and desktop environment.

It is simple, highly tailored to the BoredOS kernel syscall interface, and limited in comparison to full standard libraries like `glibc` or `musl`.

## Building & Installation

### Integrated Build (Inside BoredOS)
When building from the main BoredOS repository, the root coordinator automatically compiles and installs this library into `build/sdk/` by running:
```bash
make SDK_DIR=../../build/sdk install
```

### Standalone SDK Build
To compile and generate the BoredOS C SDK in isolation:
```bash
make SDK_DIR=/path/to/custom/sdk install
```
This will compile `libc.a` and the startup stubs, copying them alongside standard headers to your target SDK directory.
