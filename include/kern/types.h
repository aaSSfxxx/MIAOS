#ifndef _I386_TYPE_
#define _I386_TYPE_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char uchar;

typedef u8 BYTE;
typedef u16 WORD;
typedef u32 DWORD;


typedef DWORD STATUS;
typedef PVOID (void*) ;
#define PACKED __attribute__ ((packed))

#endif
