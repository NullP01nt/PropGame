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
	printf("Arg count: %d\n",argc);
	char* filename = "usb_2GB.img";
	if(argc>=2) {
		filename = argv[1];
	}
	printf("filename: %s\n",filename);
	int ddes=-1, pos=-1, ret=0, nr=0, i=0;
	if((ddes=open(filename, O_RDONLY | O_SYNC))==-1) {
		perror("Open");
		exit(1);
	}
	printf("ddes is %d\n",ddes);
	unsigned char buf[4*sizeof(struct ptable_entry_t)];
	struct ptable_entry_t *partition[5];
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

	partition[0] = (struct ptable_entry_t*)buf;
	partition[1] = (struct ptable_entry_t*)buf[16];
	partition[2] = (struct ptable_entry_t*)buf[32];
	partition[3] = (struct ptable_entry_t*)buf[48];
	/*for(i=0; i<4;i++) {
		partition[i] = (struct ptable_entry_t*)buf[i*sizeof(struct ptable_entry_t)];
	}
	*/
	print_ptable(partition[0]);
	/*FILE *dp;
	unsigned char buffer[4*sizeof(struct ptable_entry_t)];
	struct ptable_entry_t* p1 = (struct ptable_entry_t*)malloc(sizeof(struct ptable_entry_t));
	struct ptable_entry_t* p2 = (struct ptable_entry_t*)malloc(sizeof(struct ptable_entry_t));
	struct ptable_entry_t* p3 = (struct ptable_entry_t*)malloc(sizeof(struct ptable_entry_t));
	struct ptable_entry_t* p4 = (struct ptable_entry_t*)malloc(sizeof(struct ptable_entry_t));
	if((dp=fopen(filename,"rb"))!=0) {
		fseek(dp,PTABLE_OFFSET,MBR_SECTOR*SECTOR_SIZE);
		fread(buffer,sizeof(char),sizeof(buffer),dp);
		fclose(dp);
	}
	int i=0;
	for(i=0;i<sizeof(buffer);i++) {
		if(i%16==0 && i!=0) printf("\n");
		printf("%02X ",buffer[i]);
	}
	printf("\n");
	p1 = (struct ptable_entry_t*)buffer;
	p2 = (struct ptable_entry_t*)buffer[16];
	p3 = (struct ptable_entry_t*)buffer[32];
	p4 = (struct ptable_entry_t*)buffer[48];
	print_ptable(p1);*/
	return EXIT_SUCCESS;
}
