#include <bt_config.h>

#ifdef BT_CONFIG_LINKER_INIT_SECTION_FLASH
#define BT_LINKER_INIT_SECTION	FLASH
#define BT_LINKER_KERNEL_ENTRY	BT_CONFIG_LINKER_FLASH_START_ADDRESS
#endif

#ifdef BT_CONFIG_LINKER_INIT_SECTION_SRAM
#define BT_LINKER_INIT_SECTION	SRAM
#define BT_LINKER_KERNEL_ENTRY	BT_CONFIG_LINKER_SRAM_START_ADDRESS
#endif

#ifdef BT_CONFIG_LINKER_INIT_SECTION_RAM
#define BT_LINKER_INIT_SECTION	RAM
#define BT_LINKER_KERNEL_ENTRY	BT_CONFIG_LINKER_RAM_START_ADDRESS
#endif


#ifdef BT_CONFIG_LINKER_TEXT_SECTION_FLASH
#define BT_LINKER_TEXT_SECTION	FLASH
#endif

#ifdef BT_CONFIG_LINKER_TEXT_SECTION_SRAM
#define BT_LINKER_TEXT_SECTION	SRAM
#endif

#ifdef BT_CONFIG_LINKER_TEXT_SECTION_RAM
#define BT_LINKER_TEXT_SECTION	RAM
#endif


#ifdef BT_CONFIG_LINKER_DATA_SECTION_FLASH
#define BT_LINKER_DATA_SECTION	FLASH
#endif

#ifdef BT_CONFIG_LINKER_DATA_SECTION_SRAM
#define BT_LINKER_DATA_SECTION	SRAM
#endif

#ifdef BT_CONFIG_LINKER_DATA_SECTION_RAM
#define BT_LINKER_DATA_SECTION	RAM
#endif


#ifdef BT_CONFIG_LINKER_BSS_SECTION_FLASH
#define BT_LINKER_BSS_SECTION	FLASH
#endif

#ifdef BT_CONFIG_LINKER_BSS_SECTION_SRAM
#define BT_LINKER_BSS_SECTION	SRAM
#endif

#ifdef BT_CONFIG_LINKER_BSS_SECTION_RAM
#define BT_LINKER_BSS_SECTION	RAM
#endif


#ifdef BT_CONFIG_USE_VIRTUAL_ADDRESSING
#define BT_LINKER_RAM_ADDRESS	0xC0000000
#else
#define BT_LINKER_RAM_ADDRESS	BT_CONFIG_LINKER_RAM_START_ADDRESS
#endif
