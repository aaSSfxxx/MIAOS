#include <kern/types.h>
#include <kern/boot/gdt.h>

GDT_DESCRIPTOR kgdt[GDTSIZE];	/* GDT */
GDTR kgdtr;		/* GDTR */

/*
 * Helper function which allows us to easily make a GDT descriptor
 */
void InitGDTDescriptor (DWORD dwBase, 
                    DWORD dwLimit,
                    BYTE  bAccess,
                    BYTE bOther,
                    PGDT_DESCRIPTOR desc)
{
        desc->LimitLow = (dwLimit & 0xffff);
        desc->BaseLow = (dwBase & 0xffff);
        desc->BaseMiddle = (dwBase & 0xff0000) >> 16;
        desc->BaseHigh = (dwBase & 0xff000000) >> 24;
        desc->Access = bAccess;
        desc->LimitHigh = (dwLimit & 0xf0000) >> 16;
        desc->Other = (bOther & 0xf);
        return;
}

/*
 * Init a new GDT for the kernel :>
 * Here, we init ring0 & ring3 descriptors
 */
void InitGDT (void)
{

        /* initialisation des descripteurs de segment */
        InitGDTDescriptor(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
        InitGDTDescriptor(0x0, 0xFFFFF, RING0_CODE, 0x0D, &kgdt[1]);
        InitGDTDescriptor(0x0, 0xFFFFF, RING0_DATA, 0x0D, &kgdt[2]);
		InitGDTDescriptor(0x0, 0x0, 0x97, 0x0D, &kgdt[3]); /* RINGO stack */
        InitGDTDescriptor(0x0, 0xFFFFF, RING3_CODE, 0x0D, &kgdt[4]);
        InitGDTDescriptor(0x0, 0xFFFFF, RING3_DATA, 0x0D, &kgdt[5]);
		InitGDTDescriptor(0x0, 0x0, 0x97 | RING3, 0x0D, &kgdt[6]); /* Ring3 stack */
        /* initialisation de la structure pour GDTR */
        kgdtr.Limit = GDTSIZE * 8;
        kgdtr.Base = GDTBASE;

        /* recopie de la GDT a son adresse */
        memcpy((char *) kgdtr.Base, (char *) kgdt, kgdtr.Limit);

        /* chargement du registre GDTR */
        asm("lgdtl (kgdtr)");

        /* initialisation des segments */
        asm("   movw $0x10, %ax \n \
            movw %ax, %ds       \n \
            movw %ax, %es       \n \
            movw %ax, %fs       \n \
            movw %ax, %gs       \n \
            ljmp $0x08, $next   \n \
            next:               \n");
}


