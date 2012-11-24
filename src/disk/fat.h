#ifndef SEG_FAT_H
	#define SEG_FAT_H


	#define SECTOR_SIZE 512 // Sector size in bytes
	#define SECTOR_OFFSET(x) ((x)*SECTOR_SIZE)
	#define MBR_SECTOR 0 // Stating the obvious, I know, but it makes things easier at some point
	#define PTABLE_OFFSET 0x1be
	#define MAX_PARTITIONS 4
	struct partition_entry_t {
		unsigned char bootflag;
		unsigned char hd_start;
		unsigned short cs_start;
		unsigned char system_id;
		unsigned char hd_end;
		unsigned short cs_end;
		unsigned int rel_sector;
		unsigned int sector_count;
	};

	struct boot_param_block_t {
		unsigned char	assembly[3];
		char			OEM_identifier[8];
		unsigned short	bytes_per_sector;
		unsigned char	sectors_per_cluster;
		unsigned short	reserved_sectors;
		unsigned char	FAT_count;
		unsigned short	dir_entry_count;
		unsigned short	total_sectors;
		unsigned char	media_descriptor;
		unsigned short	sectors_per_FAT;
		short			sectors_per_track;
		unsigned short	head_count;
		unsigned int	hidden_sectors;
		unsigned int	large_sectors;
	}__attribute__((packed));

	struct eboot_param_block_t {
		struct boot_param_block_t bpb;
		#ifdef USE_FAT32
		unsigned int	sectors_per_fat;
		unsigned short	flags;
		unsigned short	FAT_version;
		unsigned int	root_dir_cluster;
		unsigned short	FSInfo_cluster;
		unsigned short	backup_bsector_cluster;
		unsigned char	reserved[12];
		#endif	
		unsigned char	drive_number;
		unsigned char	winnt_flags;
		unsigned char	signature;
		unsigned int	volume_serial;
		char			volume_label[11];
		char			system_identifier[8];
		#ifdef USE_FAT32
		unsigned char	boot_code[420];
		#else
		unsigned char	boot_code[448];
		#endif
		unsigned short	boot_signature;
	}__attribute__((packed));


	void print_partition(struct partition_entry_t* table);
	void dump_eboot(struct eboot_param_block_t* block);
#endif
