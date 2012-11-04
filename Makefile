OBJ=kernel 
BASEDIR=$(CURDIR)
export BASEDIR

CSOURCES= kern/boot/gdt.c \
          kern/boot/kernel.c \
          kern/boot/idt.c \
          kern/klibc/screen.c \
          kern/klibc/printk.c \
          kern/klibc/functions.c

ASMSOURCES= kern/boot/boot.obj \
            kern/boot/idtmgr.obj

COBJECTS=$(CSOURCES:.c=.o)
ASMOBJECTS=$(ASMSOURCES:.asm=.obj) 

all: $(OBJ) 

%.obj: %.asm
	nasm -f elf -o $@ $^

%.o: %.c
	$(CC) -o $@ -nostdlib -c -I$(BASEDIR)/include $^

kernel: $(COBJECTS) $(ASMOBJECTS)
	ld -Ttext=100000 --entry=_start $(ASMOBJECTS) $(COBJECTS) -o $(BASEDIR)/out/$@

clean:
	rm -f $(COBJECTS) $(ASMOBJECTS) bochs.log
