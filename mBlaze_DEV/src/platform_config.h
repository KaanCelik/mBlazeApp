#ifndef __PLATFORM_CONFIG_H_
#define __PLATFORM_CONFIG_H_

#ifdef __PPC__
#define CACHEABLE_REGION_MASK 0x80800000
#endif

#ifdef DEBUG
#define DEBUG_MODE 1
#else
#define DEBUG_MODE 0
#endif

#endif
