#ifndef SEG_DISK_H
#define SEG_DISK_H

#define SECTOR_SIZE 512 // Sector size in bytes
#define MBR_SECTOR 0 // Stating the obvious, I know, but it makes things easier at some point
#define PTABLE_OFFSET 0x1be
struct ptable_entry_t {
	unsigned char bootflag;
	unsigned char start_head;
	unsigned short start_hw_addr; // 6 bits for sector, remaining 10 bits for cylinder
	unsigned char system_id;
	unsigned char end_head;
	unsigned short end_hw_addr; // see start_hw_addr comment
	unsigned int rel_sector;
	unsigned int sector_count;
};

void print_ptable(struct ptable_entry_t* table);
#endif
