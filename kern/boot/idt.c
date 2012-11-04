#include <kern/types.h>
#include <kern/functions.h>
#include <kern/boot/idt.h>

/**
 * Helper function which makes an IDT destriptor
 */

IDT_DESCRIPTOR kidt[256];
IDT_TABLE kidtr;

void InitIDTDescriptor (BYTE index,
                        DWORD dwBase,
                        WORD wSelector,
                        BYTE bFlags)
{
    
    kidt[index].BaseLower = (dwBase & 0xFFFF);
    kidt[index].BaseHigher = (dwBase >> 16) & 0xFFFF;
    kidt[index].Selector = wSelector;
    kidt[index].Flags = bFlags;
    kidt[index].Reserved = 0; // set it to 0
}

/**
 * Loads the new IDT which will handle interrupts
 */
void LoadIDT (void)
{
    int i;
    for(i=0; i<32; i++) {
      InitIDTDescriptor(i, (DWORD)default_isr, 0x08, 0x8E);
    }
    InitIDTDescriptor( 8, (DWORD)isr8 , 0x08, 0x8E);
    InitIDTDescriptor( 10, (DWORD)isr10 , 0x08, 0x8E);
    InitIDTDescriptor( 11, (DWORD)isr11 , 0x08, 0x8E);
    InitIDTDescriptor( 12, (DWORD)isr12 , 0x08, 0x8E);
    InitIDTDescriptor( 13, (DWORD)isr13 , 0x08, 0x8E);
    InitIDTDescriptor( 14, (DWORD)isr14 , 0x08, 0x8E);
    
    kidtr.Limit = sizeof(IDT_DESCRIPTOR) * 256 -1;
    kidtr.Base  = (DWORD)kidt;
    asm ("lidt (kidtr)");
	InitIDTDescriptor( 32, (DWORD)isr32 , 0x08, 0x8E);
    InitIDTDescriptor( 0x80, (DWORD)isr0x80 , 0x08, 0x8E);
	asm ("int $0x80");
	/** User defined interruptions **/
    /*       */
}

void UserInterrupt (REGISTERS *pRegisters) {
  printk("Interrupt %d called \n", pRegisters->IntNum);
}

void ISRDispatcher (REGISTERS Registers)
{
  if(Registers.IntNum > 31) {
    UserInterrupt (&Registers);
  }
  else {
    ISRExceptHandler(&Registers);
  }
}

void ISRExceptHandler (REGISTERS *pRegisters)
{
    printk("Error %d got \n", pRegisters->IntNum);
    if (pRegisters->IntNum == 13) {
      // Interrupt doesn't exist
      printk ("Unhandled interrupt \n");
    }
}

void ClockTick(void) {
  printk (".");
}

void KeyboardHandler (void) {
	printk ("Keyboard \n");
}
