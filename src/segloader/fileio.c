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
#include "vga_text.h"

FILE *stdinfile;
FILE *stdoutfile;

#define EXEC_EXTENSION "pex"

void listFilesByExt(char* loadpath, char* ext) {
	int i;
	char *ptr;
	char fname[13];
	char *path = "./";
	char fext[4];
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
		if((entry->attr & ATTR_VOLUME_ID) || (entry->attr & ATTR_DIRECTORY) || (entry->name[0] == '.')) continue;
		ptr = fname;
		for(i=0; i < 8; i++) {
			if(entry->name[i] == ' ') break;
			*ptr++ = tolower(entry->name[i]);
		}
		if(entry->name[8] != ' ') {
			*ptr++ = '.';
			for(i=8; i<11; i++) {
				if(entry->name[i] == ' ') break;
				fext[i-8] = tolower(entry->name[i]);
				*ptr++ = tolower(entry->name[i]);
			}
		}
		*ptr = 0;
		fext[3] = 0x00;
		if(ext != NULL) {
			if(strcmp(fext, ext) != 0) continue;
		} 
		printf("%s\t%s\n",fname,fext);
	}
	closedir(dirp);
}

void listExecutables() {
	listFilesByExt(NULL, EXEC_EXTENSION);
}

void listFiles(char* loadpath) {
	listFilesByExt(loadpath,NULL);
}
