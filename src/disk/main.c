#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define USE_FAT32
#include "disk.h"
#include "fat.h"

int main(int argc, char** argv) {
	char* filename = "usb_2GB.img";
	if(argc>=2) {
		filename=argv[1];
	}
	printf("filename: %s\n",filename);
	int ddes=-1, pos=-1, ret=0, nr=0,i=0;
	if((ddes=open(filename, O_RDONLY | O_SYNC))==-1) {
		perror("Open");
		exit(1);
	}
	int ptable_size = sizeof(struct ptable_entry_t);
	unsigned char buf[ptable_size];
	struct ptable_entry_t* partition;
	pos = lseek(ddes,PTABLE_OFFSET,SEEK_CUR);
	if((nr = read(ddes,buf,sizeof(buf)))==-1) {
		perror("Read");
		exit(1);
	}

	printf("--- Partition Table ---\n");
	for(i=0;i<sizeof(buf);i++) {
		if(i%16==0 && i!=0) printf("\n");
		printf("%02X ",buf[i]);
	}
	printf("\n\n");
	partition = (struct ptable_entry_t*)buf;
	print_ptable(partition);
	pos=lseek(ddes,SECTOR_OFFSET(partition->rel_sector),SEEK_SET);
	unsigned char fat_header_buf[sizeof(struct ebpb_t)];
	if((nr = read(ddes,fat_header_buf,sizeof(buf)))==-1) {
		perror("Read");
		exit(1);
	}
	printf("--- FAT ---\n");
	struct ebpb_t* ebpb = (struct ebpb_t*)fat_header_buf;
	dump_ebpb(ebpb);
	ret=close(ddes);
	if(ret==-1) {
		perror("Close");
		exit(1);
	}
	return EXIT_SUCCESS;
}
