#ifdef __keyboard_h
#define __keyboard_h

/* gets the kernel keyboard map */
#ifdef kbdmap
extern BYTE kbdmap[];
#endif

/* some consts to make the code easier to read */
#define LEFT_SHIFT 0x29
#define RIGHT_SHIFT 0X35
#define CONTROL 0x1C
#define ALT 0x37

#endif
