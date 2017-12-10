#ifndef _BUF_H
#define _BUF_H

#include <stdint.h>

struct cyclicBuff{
	volatile uint64_t curPos;
	volatile int data[4096];
};
#endif

