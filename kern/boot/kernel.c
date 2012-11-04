#include <kern/types.h>
#include <kern/io.h>
#include <kern/boot/gdt.h>
#include <kern/boot/grub_struct.h>
#include <kern/boot/idt.h>
#include <kern/functions.h>

void OkMsg(void)
{
	printk("OK\n");
}
/** copypasta from http://a.michelizza.free.fr/Pepin/ManageKBD/kern/pic.c **/
void InitPIC(void)
{
	printk ("Initialize PIC\n");
	/* Init ICW1 */
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	//printk ("ICW1 OK\n");
	
	/* Init ICW2 */
	outb(0x21, 0x20);	/* start vector = 32 */
	outb(0xA1, 0x70);	/* start vector = 96 */
	//printk ("ICW2 OK\n");
	
	/* Init ICW3 */
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	//printk ("ICW3 OK\n");
	
	/* Init ICW4 */
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	//printk ("ICW4 OK\n");
	
	/* interruption mask */
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
	//printk ("Interrupts unmasked\n");
	
	printk ("PIC configured (or not :') ) \n");
}


/** Kernel (real) entry point **/
void kmain(struct mb_partial_info *mbi)
{
    printk("RAM detected : %uk (lower), %uk (upper)\n", mbi->low_mem, mbi->high_mem);
    printk("Command line got: %s \n", mbi->cmdline);
	printk ("Initialize GDT ... ");
	InitGDT();
    asm("   movw $0x18, %ax \n \
                movw %ax, %ss \n \
                movl $0x1FFF0, %esp");
	OkMsg();
    
	LoadIDT();
    printk ("IDT loaded  éè\n");
    InitPIC();

	sti;
	while(1) { }
}
