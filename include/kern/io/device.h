#ifndef __device_h
#define __device_h

typedef struct __device_ops {
	(STATUS)(*DeviceInit)();
	(STATUS)(*DeviceRead)(char *buffer, int size);
	(STATUS)(*DeviceWrite)(char *buffer, int size);
	(STATUS)(*DeviceControl)(int ioControl, char* buffer, int size);
	(STATUS)(*DeviceShutdown)();
}

#endif
