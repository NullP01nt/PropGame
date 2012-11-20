#include <stdio.h>
#include <stdlib.h>
#include "fat.h"

void dump_ebpb(struct ebpb_t* block) {
	int i =0;
	printf("Assembly: ");
	for(i=0; i<sizeof(block->bpb.assembly);i++) {
		printf("%02X ",block->bpb.assembly[i]);
	}
	printf("\n");
	printf("OEM ID: %s\n",block->bpb.OEM_identifier);
	printf("Bytes per sector: %d\n",block->bpb.bytes_per_sector);
	printf("Sectors per cluster: %d\n",block->bpb.sectors_per_cluster);
	printf("Reserved sectors: %d\n",block->bpb.reserved_sectors);
	printf("#FAT tables: %d\n",block->bpb.FAT_count);
	printf("#Directory entries: %d\n",block->bpb.dir_entry_count);
	printf("Total sectors: %d\n",block->bpb.total_sectors);
	printf("Media Descriptor: %02x\n",block->bpb.media_descriptor);
	printf("Sectors per FAT: %d\n",block->bpb.sectors_per_FAT);
	printf("Sectors per track: %d\n",block->bpb.sectors_per_track);
	printf("Head count: %d\n",block->bpb.head_count);
	printf("Hidden sectors: %d\n", block->bpb.hidden_sectors);
	printf("Large sectors: %d\n", block->bpb.large_sectors);
}
