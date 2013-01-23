#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cog.h>
#include <ctype.h>
#include <propeller.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sd.h>

#undef CALL_MOUNT
#undef SPINNERET_CARD
#undef PROP_BOE
#undef C3_CARD
#undef PARALLEL_SPI

#include "fileio.h"

extern _Driver _SimpleSerialDriver;
extern _Driver _FileDriver;

_Driver *_driverlist[] = {
	&_SimpleSerialDriver,
	&_FileDriver,
	NULL
};

int main(int argc, char** argv) {
	printf("BINARY LOADED, ATTEMPTING TO LIST FILES!\n");
	listFiles(NULL);
	return 0;	
}
