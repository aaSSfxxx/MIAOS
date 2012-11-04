#ifndef __grubstruct_h
#define __grubstruct_h

struct mb_partial_info {
	unsigned long flags;
	unsigned long low_mem;
	unsigned long high_mem;
	unsigned long boot_device;
	unsigned long cmdline;
};

#endif
