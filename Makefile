# Copyright (c) 2026 Christiaan (chris@boreddev.nl)
# Pure Standard C Library & OS SDK Makefile

CC  = x86_64-elf-gcc
AR  = x86_64-elf-ar
AS  = nasm

SDK_DIR ?= ../../build/sdk

CFLAGS  = -Wall -Wextra -std=gnu11 -ffreestanding -O2 -fno-stack-protector \
          -fno-stack-check -fno-lto -fno-pie -m64 -march=x86-64 -mno-red-zone \
          -Iinclude

LIBC_SOURCES = $(wildcard src/*.c)
LIBC_OBJS    = $(patsubst src/%.c, obj/libc_%.o, $(LIBC_SOURCES))

all: obj/libc.a obj/crt0.o obj/crt1.o obj/crti.o obj/crtn.o

obj/libc_%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/crt%.o: src/crt%.asm
	@mkdir -p obj
	$(AS) -f elf64 $< -o $@

obj/libc.a: $(LIBC_OBJS)
	$(AR) rcs $@ $^

install: all
	mkdir -p $(SDK_DIR)/include/sys $(SDK_DIR)/lib
	cp -r include/. $(SDK_DIR)/include/
	cp obj/libc.a $(SDK_DIR)/lib/
	cp obj/crt0.o obj/crt1.o obj/crti.o obj/crtn.o $(SDK_DIR)/lib/

clean:
	rm -rf obj
