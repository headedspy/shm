#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "buf.h"

int main(){
	int shm = shm_open("SHMemory", O_RDONLY, 0);
	if(shm < 0){
		perror("Open");
		return -1;
	}

	struct cyclicBuff* mem = mmap(NULL, sizeof(struct cyclicBuff), PROT_READ, MAP_SHARED, shm, 0);
	if(mem == NULL){
		perror("Mmap");
		return -1;
	}

	uint64_t curPos = (mem->curPos + 2048)%4096;

	for(;;){
		if(mem->curPos == curPos){
			sleep(1);
			continue;
		}
		printf("%d\n", mem->data[curPos]);
		curPos++;
		curPos %= 4096;
	}
	return 0;
}
