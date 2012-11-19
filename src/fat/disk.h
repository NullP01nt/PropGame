#ifndef SEG_DISK_H
#define SEG_DISK_H

#define SECTOR_SIZE 512 // Sector size in bytes
#define MBR_SECTOR 0 // Stating the obvious, I know, but it makes things easier at some point
#define PTABLE_OFFSET 0x1be
struct ptable_entry_t {
	unsigned char bootflag;
	unsigned char hd_start;
	unsigned short cs_start;
	unsigned char system_id;
	unsigned char hd_end;
	unsigned short cs_end;
	unsigned int rel_sector;
	unsigned int sector_count;
};

void print_ptable(struct ptable_entry_t* table);
#endif
