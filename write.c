#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "buf.h"

int num=0;

int getNum(){
	return ++num;
}

int main(){
	int shm = shm_open("SHMemory", O_CREAT | O_RDWR, S_IRWXO);
	if(shm < 0){
		perror("Open");
		return -1;
	}

	if(ftruncate(shm, sizeof(struct cyclicBuff)) == -1){
		perror("Ftruncate");
		return -1;
	}

	struct cyclicBuff* mem = mmap(NULL, sizeof(struct cyclicBuff), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
	if(mem == NULL){
		perror("Map");
		return -1;
	}

	mem->curPos%=4096;


	for(;;){
		mem->curPos++;
		mem->curPos%=4096; 
		mem->data[mem->curPos] = getNum(); 
		if(mem->curPos%512 == 0)sleep(1);
	}
	return 0;
}
