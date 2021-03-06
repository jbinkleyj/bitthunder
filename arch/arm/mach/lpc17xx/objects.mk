#
#	LPC17xx Platform objects
#
MACH_LPC17xx_OBJECTS  += $(BUILD_DIR)arch/arm/mach/lpc17xx/lpc17xx.o			# Provides machine description.
MACH_LPC17xx_OBJECTS += $(BUILD_DIR)arch/arm/mach/lpc17xx/ioconfig.o
MACH_LPC17xx_OBJECTS  += $(BUILD_DIR)arch/arm/mach/lpc17xx/rcc.o
MACH_LPC17xx_OBJECTS  += $(BUILD_DIR)arch/arm/mach/lpc17xx/gpio.o
MACH_LPC17xx_OBJECTS-$(BT_CONFIG_MACH_LPC17xx_TIMER)    += $(BUILD_DIR)arch/arm/mach/lpc17xx/timer.o
MACH_LPC17xx_OBJECTS-$(BT_CONFIG_MACH_LPC17xx_UART)     += $(BUILD_DIR)arch/arm/mach/lpc17xx/uart.o
MACH_LPC17xx_OBJECTS-$(BT_CONFIG_MACH_LPC17xx_CAN)      += $(BUILD_DIR)arch/arm/mach/lpc17xx/can.o
MACH_LPC17xx_OBJECTS-$(BT_CONFIG_MACH_LPC17xx_SPI)      += $(BUILD_DIR)arch/arm/mach/lpc17xx/spi.o
MACH_LPC17xx_OBJECTS-$(BT_CONFIG_MACH_LPC17xx_I2C)      += $(BUILD_DIR)arch/arm/mach/lpc17xx/i2c.o
MACH_LPC17xx_OBJECTS-$(BT_CONFIG_MACH_LPC17xx_ADC)      += $(BUILD_DIR)arch/arm/mach/lpc17xx/adc.o
MACH_LPC17xx_OBJECTS-$(BT_CONFIG_MACH_LPC17xx_PWM)      += $(BUILD_DIR)arch/arm/mach/lpc17xx/pwm.o

MACH_LPC17xx_OBJECTS += $(MACH_LPC17xx_OBJECTS-y)

$(MACH_LPC17xx_OBJECTS): MODULE_NAME="HAL"
$(MACH_LPC17xx_OBJECTS): CFLAGS += -D BT_CONFIG_MACH_LPC17xx_SYSCLOCK_FREQ=$(BT_CONFIG_MACH_LPC17xx_SYSCLOCK_FREQ)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -D BT_CONFIG_MACH_LPC17xx_SYSCLOCK_IRC_FREQ=$(BT_CONFIG_MACH_LPC17xx_SYSCLOCK_IRC_FREQ)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_ARCH_ARM_NVIC_BASE=$(BT_CONFIG_ARCH_ARM_NVIC_BASE)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_ARCH_ARM_NVIC_TOTAL_IRQS=$(BT_CONFIG_ARCH_ARM_NVIC_TOTAL_IRQS)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_TOTAL_GPIOS=$(BT_CONFIG_MACH_LPC17xx_TOTAL_GPIOS)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_GPIO_BASE=$(BT_CONFIG_MACH_LPC17xx_GPIO_BASE)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_CAN0_BASE=$(BT_CONFIG_MACH_LPC17xx_CAN0_BASE)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_UART0_BASE=$(BT_CONFIG_MACH_LPC17xx_UART0_BASE)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_TIMER0_BASE=$(BT_CONFIG_MACH_LPC17xx_TIMER0_BASE)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_TIMER1_BASE=$(BT_CONFIG_MACH_LPC17xx_TIMER1_BASE)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_TIMER2_BASE=$(BT_CONFIG_MACH_LPC17xx_TIMER2_BASE)
$(MACH_LPC17xx_OBJECTS): CFLAGS += -DBT_CONFIG_MACH_LPC17xx_TIMER3_BASE=$(BT_CONFIG_MACH_LPC17xx_TIMER3_BASE)



OBJECTS += $(MACH_LPC17xx_OBJECTS)
