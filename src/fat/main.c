//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "disk.h"
#include "fat.h"

int main(int argc, char** argv) {
	char* filename = "usb_2GB.img";
	if(argc>=2) {
		filename = argv[1];
	}
	printf("filename: %s\n",filename);
	int ddes=-1, pos=-1, ret=0, nr=0,i=0;
	if((ddes=open(filename, O_RDONLY | O_SYNC))==-1) {
		perror("Open");
		exit(1);
	}
	int ptable_size = sizeof(struct ptable_entry_t);
	unsigned char buf[MAX_PARTITIONS*ptable_size];
	struct ptable_entry_t* partition[MAX_PARTITIONS];
	pos=lseek(ddes,PTABLE_OFFSET,SEEK_CUR);
	printf("Position of pointer is: %d\n",pos);
	if((nr = read(ddes,buf,sizeof(buf)))==-1) {
		perror("Read");
		exit(1);
	}
	ret=close(ddes);
	if(ret==-1) {
		perror("Close");
		exit(1);
	}

	for(i=0;i<sizeof(buf);i++) {
		if(i%16==0 && i!=0) printf("\n");
		printf("%02X ",buf[i]);
	}
	printf("\n");
	for(i=0;i<MAX_PARTITIONS;i++) {
		partition[i] = (struct ptable_entry_t*)&buf[i*ptable_size];
		printf("--- Partition %d ---\n",i+1);
		print_ptable(partition[i]);
		printf("\n");
	}
	return EXIT_SUCCESS;
}
