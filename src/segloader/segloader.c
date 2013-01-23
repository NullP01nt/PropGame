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
#include "gamepad.h"

uint8_t PAD_ONE;

extern _Driver _SimpleSerialDriver;
extern _Driver _FileDriver;

_Driver *_driverlist[] = {
	&_SimpleSerialDriver,
	&_FileDriver,
	NULL
};

int main(int argc, char** argv) {
	printf("--- PEX files ---\n");
	listFilesByExt(NULL,"pex");
	printf("--- TXT files ---\n");
	listFilesByExt(NULL,"txt");
	printf("--- BIN files ---\n");
	listFilesByExt(NULL,"bin");
	printf("\n--- All Files ---\n");
	listFiles(NULL);
	return 0;
}
