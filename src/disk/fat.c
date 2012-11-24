#include <stdio.h>
#include <stdlib.h>
#include "fat.h"

void print_ptable(struct partition_entry_t* table) {
	if(table->sector_count<=0 || table->system_id==0) {
		printf("This is not an initialized partition\n");
	} else {	
		printf("Bootflag: %s\n",table->bootflag==0x80?"True":"False");
		printf("Starting Head: %d\n",table->hd_start);
		int start_sect = ((table->cs_start)>>10)&0x3F;
		int start_cyl = (table->cs_start)&0x3FF;
		printf("Starting Sector: %d\n",start_sect);
		printf("Starting Cylinder: %d\n",start_cyl);
		printf("System ID: %02x\n",table->system_id);
		printf("Ending Head: %d\n",table->hd_end);
		int end_sect = ((table->cs_end)>>10)&0x3F;
		int end_cyl = (table->cs_end)&0x3FF;
		printf("Ending Sector: %d\n",end_sect);
		printf("Ending Cylinder: %d\n",end_cyl);
		printf("Relative Sector: %d\n",table->rel_sector);
		printf("Total sectors: %d\n",table->sector_count);
	}
}

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
	printf("\n");
	printf("Volume Label: ");
	for(i=0;i<sizeof(block->volume_label);i++) {
		if(block->volume_label[i]==0) break;
		printf("%c",block->volume_label[i]);
	}
	printf("\n");
	printf("Sys ID: ");
	for(i=0;i<sizeof(block->system_identifier);i++) {
		if(block->system_identifier[i]==0) break;
		printf("%c",block->system_identifier[i]);
	}
	printf("\n");
}
