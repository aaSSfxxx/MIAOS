#ifndef __idt_h
#define __idt_h

/* IDT Descriptor */
struct idtdescr {
   WORD BaseLower; // offset bits 0..15
   WORD Selector; // a code segment selector in GDT or LDT
   BYTE Reserved;      // unused, set to 0
   BYTE Flags; // type and attributes, see below
   WORD BaseHigher; // offset bits 16..31
} PACKED;

typedef struct idtdescr IDT_DESCRIPTOR, *PIDT_DESCRIPTOR;

struct idttable {
    WORD Limit;
    DWORD Base; 
} PACKED;

typedef struct idttable IDT_TABLE, *PIDT_TABLE;

void LoadIDT (void);

/** Exception handler + reserved interruptions **/
extern void isr8 (void);
extern void isr10 (void);
extern void isr11 (void);
extern void isr12 (void);
extern void isr13 (void);
extern void isr14 (void);

extern void default_isr (void);

/** User-defined interruptions **/
extern void isr32 (void);
extern void isr33 (void);
extern void isr0x80 (void);

typedef struct registers
{
   DWORD DS;                  // Data segment selector
   DWORD EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX; // Pushed by pusha.
   DWORD IntNum, ErrCode;    // Interrupt number and error code (if applicable)
   DWORD EIP, CS, EFLAGS, UserESP, SS; // Pushed by the processor automatically.
} REGISTERS, *PREGISTERS; 
#endif
