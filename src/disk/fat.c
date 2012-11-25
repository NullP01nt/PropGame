#include <stdio.h>
#include <stdlib.h>
#include "fat.h"
void print_hex_bytes(unsigned char* data,int numBytes) {
	int i=0;
	for(i=0; i<numBytes;i++) {
		if(i%16==0) printf("\n\t");
		printf("%02x ",data[i]);
	}
}

void print_char_bytes(unsigned char* data, int numBytes) {
	int i=0;
	for(i=0; i<numBytes;i++) {
		printf("%c",(char)data[i]);
	}
	printf("\n");
}

void print_partition(struct partitionInfo_t* table) {
	if(table->sectorsTotal<=0 || table->type==0) {
		printf("This is not an initialized partition\n");
	} else {	
		printf("Bootflag: %s\n",table->status==0x80?"True":"False");
		printf("Starting Head: %d\n",table->headStart);
		int start_sect = ((table->cylSectStart)>>10)&0x3F;
		int start_cyl = (table->cylSectStart)&0x3FF;
		printf("Starting Sector: %d\n",start_sect);
		printf("Starting Cylinder: %d\n",start_cyl);
		printf("System ID: %02x\n",table->type);
		printf("Ending Head: %d\n",table->headEnd);
		int end_sect = ((table->cylSectEnd)>>10)&0x3F;
		int end_cyl = (table->cylSectEnd)&0x3FF;
		printf("Ending Sector: %d\n",end_sect);
		printf("Ending Cylinder: %d\n",end_cyl);
		printf("Relative Sector: %d\n",table->firstSector);
		printf("Total sectors: %d\n",table->sectorsTotal);
	}
}
void dump_eboot_F16(struct eboot_param_block_F16_t* block) {
	printf("Jump Assembly: ");
	print_hex_bytes(block->jumpBoot,3);
	printf("\n");
	printf("OEM Identifier: %s\n",block->OEMName);
	printf("Bytes per sector: %d\n",block->bytesPerSector);
	printf("Sectors per cluster: %d\n",block->sectorPerCluster);
	printf("Reserved sectors: %d\n",block->reservedSectorCount);
	printf("Number of FAT tables: %d\n",block->numberofFATs);
	printf("Number of Directory entries: %d\n",block->rootEntryCount);
	printf("Total sectors (F16): %d\n",block->totalSectors_F16);
	printf("Media Descriptor: %02x\n",block->mediaType);
	printf("Sectors per FAT (F16): %d\n",block->FATsize_F16);
	printf("Sectors per track: %d\n",block->sectorsPerTrack);
	printf("Head count: %d\n",block->numberofHeads);
	printf("Hidden sectors: %d\n", block->hiddenSectors);
	printf("Total Sectors (F32): %d\n", block->totalSectors_F32);
	printf("Drive Number: %d\n", block->driveNumber);
	printf("Boot Signature: %02X\n",block->bootSignature);
	printf("Volume ID: %d\n",block->volumeID);
	printf("Volume Label: ");
	print_char_bytes(block->volumeLabel,11);
	printf("\n");
	printf("Filesystem Type: ");
	print_char_bytes(block->fileSystemType,8);
	printf("\n");
}

void dump_eboot_F32(struct eboot_param_block_F32_t* block) {
	printf("Jump Assembly: ");
	print_hex_bytes(block->jumpBoot,3);
	printf("\n");
	printf("OEM Identifier: %s\n",block->OEMName);
	printf("Bytes per sector: %d\n",block->bytesPerSector);
	printf("Sectors per cluster: %d\n",block->sectorPerCluster);
	printf("Reserved sectors: %d\n",block->reservedSectorCount);
	printf("Number of FAT tables: %d\n",block->numberofFATs);
	printf("Number of Directory entries: %d\n",block->rootEntryCount);
	printf("Total sectors (F16): %d\n",block->totalSectors_F16);
	printf("Media Descriptor: %02x\n",block->mediaType);
	printf("Sectors per FAT (F16): %d\n",block->FATsize_F16);
	printf("Sectors per track: %d\n",block->sectorsPerTrack);
	printf("Head count: %d\n",block->numberofHeads);
	printf("Hidden sectors: %d\n", block->hiddenSectors);
	printf("Total Sectors (F32): %d\n", block->totalSectors_F32);
	printf("Sectors per FAT (F32): %d\n", block->FATsize_F32);
	printf("Flags: %d\n", block->extFlags);
	printf("FAT Version Number: %d\n", block->FSversion);
	printf("Root directory cluster: %d\n",block->rootCluster);
	printf("FileSystem Info cluster: %d\n",block->FSinfo);
	printf("Backup BootSector cluster: %d\n",block->BackupBootSector);
	printf("Reserved: ");
	print_hex_bytes(block->reserved,12);
	printf("\n");
	printf("Drive Number: %d\n",block->driveNumber);
	printf("Reserved: %d\n", block->reserved1);
	printf("Boot Signature: %02X\n", block->bootSignature);
	printf("Volume ID: %d\n", block->volumeID);
	printf("Volume Label: ");
	print_char_bytes(block->volumeLabel,11);
	printf("Filesystem Type: ");
	print_char_bytes(block->fileSystemType,8);
}

