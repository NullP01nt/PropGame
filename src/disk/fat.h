#ifndef SEG_FAT_H
	#define SEG_FAT_H

	// Boot Record defines
	#define SECTOR_SIZE 512 // Sector size in bytes
	#define SECTOR_OFFSET(x) ((x)*SECTOR_SIZE)
	#define MBR_SECTOR 0 // Stating the obvious, I know, but it makes things easier at some point
	#define PTABLE_OFFSET 0x1be
	#define MAX_PARTITIONS 4

	struct MBRinfo_t {
		unsigned char	nothing[446];
		unsigned char	partitionData[64];
		unsigned short	signature;
	};

	struct partitionInfo_t {
		unsigned char	status;                 //0x80 - 		active partition
		unsigned char	headStart;              //starting head
		unsigned short	cylSectStart;           //starting cylinder and sector
		unsigned char	type;                   //partition type
		unsigned char	headEnd;                //ending head of the partition
		unsigned short	cylSectEnd;             //ending cylinder and sector
		unsigned int	firstSector;            //total sectors between MBR & the first sector of the partition
		unsigned int	sectorsTotal;           //size of this partition in sectors
	};

	struct eboot_param_block_F16_t {
		unsigned char	jumpBoot[3];		//default: 0x009000EB
				 char	OEMName[8];
		unsigned short	bytesPerSector;		//default: 512
		unsigned char	sectorPerCluster;
		unsigned short	reservedSectorCount;
		unsigned char	numberofFATs;
		unsigned short	rootEntryCount;
		unsigned short	totalSectors_F16;	//must be 0 for FAT32
		unsigned char	mediaType;
		unsigned short	FATsize_F16;		//must be 0 for FAT32
				 short	sectorsPerTrack;
		unsigned short	numberofHeads;
		unsigned int	hiddenSectors;
		unsigned int	totalSectors_F32;
		unsigned char	driveNumber;
		unsigned char	reserved;			// Reserved
		unsigned char	bootSignature;
		unsigned int	volumeID;
				 char	volumeLabel[11];	//"NO NAME "
				 char	fileSystemType[8];	//"FAT32"
		unsigned char	bootData[448];
		unsigned short	bootEndSignature;	//0xaa55
	}__attribute__((packed));

	struct eboot_param_block_F32_t {
		unsigned char	jumpBoot[3];		//default: 0x009000EB
				 char	OEMName[8];
		unsigned short	bytesPerSector;		//default: 512
		unsigned char	sectorPerCluster;
		unsigned short	reservedSectorCount;
		unsigned char	numberofFATs;
		unsigned short	rootEntryCount;
		unsigned short	totalSectors_F16;	//must be 0 for FAT32
		unsigned char	mediaType;
		unsigned short	FATsize_F16;		//must be 0 for FAT32
				 short	sectorsPerTrack;
		unsigned short	numberofHeads;
		unsigned int	hiddenSectors;
		unsigned int	totalSectors_F32;
		unsigned int	FATsize_F32;		//count of sectors occupied by one FAT
		unsigned short	extFlags;
		unsigned short	FSversion;		//0x0000 (defines version 0.0)
		unsigned int	rootCluster;		//first cluster of root directory (=2)
		unsigned short	FSinfo;			//sector number of FSinfo structure (=1)
		unsigned short	BackupBootSector;
		unsigned char	reserved[12];
		unsigned char	driveNumber;
		unsigned char	reserved1;
		unsigned char	bootSignature;
		unsigned int	volumeID;
				 char	volumeLabel[11];	//"NO NAME "
				 char	fileSystemType[8];	//"FAT32"
		unsigned char	bootData[420];
		unsigned short	bootEndSignature;	//0xaa55
	}__attribute__((packed));

	// Filesystem defines
	#define ATTR_READ_ONLY     0x01
	#define ATTR_HIDDEN        0x02
	#define ATTR_SYSTEM        0x04
	#define ATTR_VOLUME_ID     0x08
	#define ATTR_DIRECTORY     0x10
	#define ATTR_ARCHIVE       0x20
	#define ATTR_LONG_NAME     0x0f

	struct directory_entry_t {
				 char	name[11];
		unsigned char	attrib;			//file attributes
		unsigned char	NTreserved;		//always 0
		unsigned char	timeTenth;		//tenths of seconds, set to 0 here
		unsigned short	createTime;		//time file was created
		unsigned short	createDate;		//date file was created
		unsigned short	lastAccessDate;
		unsigned short	firstClusterHI;		//higher word of the first cluster number
		unsigned short	writeTime;		//time of last write
		unsigned short	writeDate;		//date of last write
		unsigned short	firstClusterLO;		//lower word of the first cluster number
		unsigned int	fileSize;		//size of file in bytes
	}__attribute__((packed));

	#define DIR_ENTRY_SIZE	0x32
	#define EMPTY		0x00
	#define DELETED		0xe5
	#define GET		0x00
	#define SET		0x01
	#define READ		0x00
	#define VERIFY		0x01
	#define ADD		0x00
	#define REMOVE		0x01
	#define TOTAL_FREE	0x01
	#define NEXT_FREE	0x02
	#define GET_LIST	0x00
	#define GET_FILE	0x01
	#define DELETE		0x02
	//#define EOF		0x0fffffff

	//************* external variables *************
	extern volatile unsigned char buffer[512];
	extern volatile unsigned long startBlock;
	extern volatile unsigned long firstDataSector, rootCluster, totalClusters;
	extern volatile unsigned int  bytesPerSector, sectorPerCluster, reservedSectorCount;

	//global flag to keep track of free cluster count updating in FSinfo sector
	unsigned char freeClusterCountUpdated;
	unsigned long unusedSectors;

	//************* functions *************
	unsigned char getBootSectorData (void);
	unsigned long getFirstSector(unsigned long clusterNumber);
	unsigned long getSetFreeCluster(unsigned char totOrNext, unsigned char get_set, unsigned long FSEntry);
	struct directory_entry_t* findFiles (unsigned char flag, unsigned char *fileName);
	unsigned long getSetNextCluster (unsigned long clusterNumber,unsigned char get_set,unsigned long clusterEntry);
	unsigned char readFile (unsigned char flag, unsigned char *fileName);
	unsigned char convertFileName (unsigned char *fileName);
//	void createFile (unsigned char *fileName);
	unsigned long searchNextFreeCluster (unsigned long startCluster);
	void memoryStatistics (void);
	void displayMemory (unsigned long memory);
//	void deleteFile (unsigned char *fileName);
	void freeMemoryUpdate (unsigned char flag, unsigned long size);

	void print_partition(struct partitionInfo_t* table);
	void dump_eboot_F16(struct eboot_param_block_F16_t* block);
	void dump_eboot_F32(struct eboot_param_block_F32_t* block);
#endif
