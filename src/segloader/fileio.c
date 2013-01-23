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

#include "fileio.h"

FILE *stdinfile;
FILE *stdoutfile;

void listFiles(char* loadpath) {
	int i;
	char *ptr;
	char fname[13];
	char *path = "./";
	DIR *dirp;
	struct dirent *entry;

	if(loadpath != NULL) {
		strcpy(path, loadpath);
	}

	path = "./";
	dirp = opendir(path);

	if(!dirp) {
		perror(path);
	}

	while((entry = readdir(dirp))) {
		if((entry->attr & ATTR_SYSTEM) || (entry->attr & ATTR_VOLUME_ID) || (entry->attr & ATTR_DIRECTORY)) continue;
		if(entry->name[0] == '.') continue;
		ptr = fname;
		for(i=0; i < 8; i++) {
			if(entry->name[i] == ' ') break;
			*ptr++ = tolower(entry->name[i]);
		}
		if(entry->name[8] != ' ') {
			*ptr++ = '.';
			for(i=8; i<11; i++) {
				if(entry->name[i] == ' ') break;
				*ptr++ = tolower(entry->name[i]);
			}
		}
		*ptr = 0;
		printf("%s\n",fname);
	}
	closedir(dirp);
}
