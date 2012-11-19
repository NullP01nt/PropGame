#include "disk.h"
#include <stdio.h>
#include <stdlib.h>

void print_ptable(struct ptable_entry_t* table) {
	printf("Bootflag: %s\n",table->bootflag==0x80?"True":"False");
	printf("Starting Head: %d\n",table->hd_start);
	int start_sect = ((table->cs_start)>>10)&0x3F;
	printf("%d\n",((table->cs_start)>>10)&0xFF);
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
