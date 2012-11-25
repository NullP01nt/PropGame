#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "fat.h"

void read_from_file(int fdes, unsigned char *buffer, unsigned int bytes_to_read, unsigned int start) {
	int nr=0;
	if(fdes!=-1) {
		lseek(fdes,start,SEEK_SET);
		if((nr = read(fdes,buffer,bytes_to_read))==-1) {
			perror("READ");
			exit(1);
		}
	}
}

int main(int argc, char** argv) {
	char* filename = "usb_2GB.img";
	unsigned char buffer[SECTOR_SIZE];
	if(argc>=2) {
		filename=argv[1];
	}
	printf("filename: %s\n",filename);
	int ddes=-1, pos=-1, ret=0;//, nr=0,i=0;
	if((ddes=open(filename, O_RDONLY | O_SYNC))==-1) {
		perror("Open");
		exit(1);
	}
	read_from_file(ddes,buffer,sizeof(struct partitionInfo_t),PTABLE_OFFSET);
	struct partitionInfo_t* partition = (struct partitionInfo_t*)buffer;
	print_partition(partition);
	int relative_sector = SECTOR_OFFSET(partition->firstSector);
	read_from_file(ddes,buffer,sizeof(struct eboot_param_block_F32_t),relative_sector);
	printf("--- FAT ---\n");
	struct eboot_param_block_F32_t* ebpb = (struct eboot_param_block_F32_t*)buffer;
	dump_eboot_F32(ebpb);
	ret=close(ddes);
	if(ret==-1) {
		perror("Close");
		exit(1);
	}
	return EXIT_SUCCESS;
}
