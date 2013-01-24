#ifndef __GBL_SEGLOADER_H
#define __GBL_SEGLOADER_H

#include <stdint.h>
#define HUB_SIZE	(32 * 1024)		// 32KB

#define SD_LOAD_RAM		(1 << 0)	// load ram for addresses above 0x30000000

/* sd loader info */
typedef struct {
	uint32_t	cache_size;
	uint32_t	cache_param1;
	uint32_t	cache_param2;
	uint32_t	cache_param3;
	uint32_t	cache_param4;
	uint32_t	flags;
} SdLoaderInfo;

#endif
