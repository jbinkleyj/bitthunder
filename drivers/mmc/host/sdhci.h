#ifndef _SDHCI_H_
#define _SDHCI_H_

#include <bitthunder.h>

#define SDHCI_FLAGS_ALWAYS_PRESENT				0x00000001		///< Flag to forcibly assume card presence. (E.g. when card detection line is not connected).


typedef struct _SDHCI_REGS {
	BT_u32	SDMA_Address;
	BT_u16	BLOCK_SIZE;
	BT_u16	BLOCK_COUNT;
	BT_u32	ARGUMENT;
	BT_u16	TRANSFERMODE;
	BT_u16	COMMAND;
	#define COMMAND_RESPONSE_SELECT				0x0003
    #define COMMAND_RESPONSE_SELECT_GET(x)		((x & COMMAND_RESPONSE_SELECT) >> 0)
    #define COMMAND_RESPONSE_SELECT_SET(x, val)	(x = (x & ~COMMAND_RESPONSE_SELECT) | ((val & 0x3) << 0))
	#define COMMAND_RESPONSE_SELECT_48
	#define COMMAND_CRC_ENABLE 					0x0008
	#define COMMAND_DATA_PRESENT 				0x0020
	BT_u16	RESPONSE[8];
	BT_u32	BUFFER_DATA_PORT;
	BT_u32	PRESENT_STATE;
    #define STATE_COMMAND_INHIBIT_CMD			0x00000001
	#define STATE_COMMAND_INHIBIT_DAT			0x00000002
	#define STATE_DAT_LINE_ACTIVE 				0x00000004
	#define STATE_WRITE_TRANSFER_ACTIVE 		0x00000100
	#define STATE_READ_TRANSFER_ACTIVE 			0x00000200
	#define STATE_BUFFER_WRITE_ENABLE 			0x00000400
	#define STATE_BUFFER_READ_ENABLE 			0x00000800
	#define STATE_CARD_INSERTED 				0x00010000
	#define STATE_CARD_STATE_STABLE				0x00020000
	#define STATE_CARD_DETECT_PIN_LEVEL 		0x00040000
	#define STATE_CARD_WRITE_PROTECT_PIN_LEVEL	0x00080000
	#define STATE_DAT_LINE_SIGNAL_LEVELS		0x00F00000
	#define STATE_CMD_LINE_SIGNAL_LEVEL 		0x01000000

	BT_u8	HOST_CONTROL;
	#define HOST_LED_CONTROL					0x01
	#define HOST_TRANSFER_WIDTH					0x02
	#define HOST_HIGH_SPEED_ENABLE				0x04
	#define HOST_DMA_SELECT						0x18
	#define HOST_CD_TEST						0x40
	#define HOST_CD_SIGNAL						0x80

	BT_u8	POWER_CONTROL;
    #define POWER_ENABLE						0x01
    #define POWER_ENABLE_GET(x)					((x & POWER_ENABLE) >> 0)
    #define POWER_ENABLE_SET(x, val)			(x |= ((val & 0x1) << 0))
	#define POWER_SELECT						0x0E
    #define POWER_SELECT_GET(x)					((x & POWER_SELECT) >> 1)
    #define POWER_SELECT_SET(x, val)		    (x = (x & ~POWER_SELECT) | ((val & 0x07) << 1))
	#define POWER_SELECT_1_8V					0x5
	#define POWER_SELECT_3_0V					0x6
	#define POWER_SELECT_3_3V 					0x7



	BT_u8	BLOCK_GAP_CONTROL;
	BT_u8	WAKEUP_CONTROL;

	BT_u16	CLOCK_CONTROL;
    #define CLOCK_INTERNAL_ENABLE				0x0001
	#define CLOCK_INTERNAL_STABLE				0x0002
	#define CLOCK_SD_ENABLE						0x0004
	#define CLOCK_SD_SELECT						0xFF00

	BT_u8	TIMEOUT_CONTROL;
	BT_u8	SOFTWARE_RESET;
	#define RESET_ALL							0x01
	#define RESET_CMD							0x02
	#define RESET_DATA							0x04

	BT_u16 NORMAL_INT_STATUS;
	#define NORMAL_INT_COMMAND_COMPLETE			0x0001
	#define NORMAL_INT_TRANSFER_COMPLETE		0x0002
	#define NORMAL_INT_BLOCK_GAP_EVENT			0x0004
	#define NORMAL_INT_DMA						0x0008
	#define NORMAL_INT_BUF_WRITE_READY			0x0010
	#define NORMAL_INT_BUF_READ_READY			0x0020
	#define NORMAL_INT_CARD_INSERTED			0x0040
	#define NORMAL_INT_CARD_REMOVED				0x0080
	#define NORMAL_INT_CARD						0x0100
	#define NORMAL_INT_ERROR					0x8000

	BT_u16 ERROR_INT_STATUS;

	BT_u16	NORMAL_INT_ENABLE;
	BT_u16	ERROR_INT_ENABLE;

	BT_u16	NORMAL_INT_SIGNAL_ENABLE;
	BT_u16	ERROR_INT_SIGNAL_ENABLE;

	BT_u16	AUTO_CMD12_ERROR;
	BT_u16 	reserved_0;

	BT_u32	CAPABILITIES;
	#define CAPS_1_8V							0x08000000
	#define CAPS_3_0V 							0x04000000
	#define CAPS_3_3V 							0x02000000

	BT_u32	reserved_caps_0;

	BT_u32	MAX_CURRENT_CAPS;
	BT_u32	reserved_max_current_caps;

	BT_u32	FORCE_EVENT_AUTO_CMD12;

	BT_u8	ADMA_ERROR_STATUS;
	BT_u8	reserved_1;

	BT_u32	ADMA_SYS_ADDRESS[2];

	/*BT_u32	reserved_2;
	BT_u32	BOOT_TIMEOUT;
	BT_u32	DEBUG_SELECTION;

	BT_STRUCT_RESERVED_u32(3, 0x64, 0xF0);
	BT_u32	SPI_INTERRUPT_SUPPORT;
	BT_STRUCT_RESERVED_u32(4, 0xF0, 0xFC);*/

	BT_STRUCT_RESERVED_u32(3, 0x5C, 0xFC);

	BT_u32	SLOT_INT_STAT_HCVERSION;
	#define HCVERSION_VENDOR 					0xFF000000
	#define HCVERSION_VENDOR_GET(x)				((x & HCVERSION_VENDOR) >> 24)
	#define HCVERSION_SPECV						0x00FF0000
	#define HCVERSION_SPECV_GET(x)				((x & HCVERSION_SPECV) >> 16)
} SDHCI_REGS;



















#endif
