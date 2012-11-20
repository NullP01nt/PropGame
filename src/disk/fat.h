#ifndef SEG_FAT_H
	#define SEG_FAT_H

	struct bpb_t {
		unsigned char	assembly[3];
		unsigned char	OEM_identifier[8];
		unsigned short	bytes_per_sector;
		unsigned char	sectors_per_cluster;
		unsigned short	reserved_sectors;
		unsigned char	FAT_count;
		unsigned short	dir_entry_count;
		unsigned short	total_sectors;
		unsigned char	media_descriptor;
		unsigned short	sectors_per_FAT;
		unsigned short	sectors_per_track;
		unsigned short	head_count;
		unsigned int	hidden_sectors;
		unsigned int	large_sectors;
	}__attribute__((packed));

	struct ebpb_t {
		struct bpb_t bpb;
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
		unsigned char	volume_label[11];
		unsigned char	system_identifier[8];
		#ifdef USE_FAT32
		unsigned char	boot_code[420];
		#else
		unsigned char	boot_code[448];
		#endif
		unsigned char	boot_signature[2];
	}__attribute__((packed));

void dump_ebpb(struct ebpb_t* block);
#endif
