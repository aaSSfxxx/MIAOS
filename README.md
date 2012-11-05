MIAOS
=====

MIAOS Is Another Operating System

----How to read the source----

Let us begin with some black magie

The code of the very begining you'll see while booting MIAOS is contained
in `boot/kernel.c`. Take a look at this first, you'll see how and what
MIAOS initialize the system.

Another piece of code to be seen is `boot/idt.c`, it contains stuff to
set up our interrupts, involved by the initialization.
