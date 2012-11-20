#include <stdio.h>
#include <stdlib.h>

#include "disk.h"

int main(int argc, char** argv) {
	char* filename="usb_2GB.img";
	if(argc>=2) {
		filename=argv[1];
	}
	int fd = 0;
   	if((fd=open(filename, O_RDONLY))==-1) {
		perror("Open");
		exit(1);
	}
	printf("Filename: %s\n",filename);
	return EXIT_SUCCESS;
}
