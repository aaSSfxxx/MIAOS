#ifndef __gdt_h
#define __gdt_h

#define GDTBASE    0x0		/* GDT home */
#define GDTSIZE    0xFF

/* Definitions for access flags */
#define ACCESS_BASE (1 << 7) | (1 << 4) | 1 /* 5th bit seems always 1 */
#define EXECUTABLE (1 << 3)
#define GROW_DOWN (1 << 2)
#define ACCESS_FROM_LOWER GROW_DOWN
#define ALLOW_RW 2
#define RING3 (3 << 5)

/* Some usual definitions */
#define RING0_CODE ACCESS_BASE | EXECUTABLE | ALLOW_RW
#define RING0_DATA ACCESS_BASE | ALLOW_RW
#define RING3_CODE RING0_CODE | RING3
#define RING3_DATA RING0_DATA | RING3

/* Segment Descriptor */
struct gdtdesc {
    WORD LimitLow;    
    WORD BaseLow;
    BYTE BaseMiddle;
    BYTE Access;
    BYTE LimitHigh : 4;
    BYTE Other : 4;
    BYTE BaseHigh;
} PACKED;
typedef struct gdtdesc GDT_DESCRIPTOR, *PGDT_DESCRIPTOR;

/* GDTR */
struct gdtr {
    WORD Limit ;
    DWORD Base ;
} PACKED;
typedef struct gdtr GDTR, *PGDTR;

#endif

