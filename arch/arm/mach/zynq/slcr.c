#include <bitthunder.h>
#include "slcr.h"

BT_u32 BT_ZYNQ_GetArmPLLFrequency() {

	BT_ERROR Error;
	volatile ZYNQ_SLCR_REGS *pRegs = bt_ioremap((void *)ZYNQ_SLCR, BT_SIZE_4K, &Error);

	BT_u32 ctl = pRegs->ARM_PLL_CTRL;
	BT_BOOL	bBypassed = BT_FALSE;


	if(!(ctl & ZYNQ_SLCR_PLL_CTRL_BYPASS_FORCE)) {
		if(ctl & ZYNQ_SLCR_PLL_CTRL_BYPASS_QUAL) {
			if(pRegs->BOOT_MODE & ZYNQ_SLCR_BOOT_MODE_ARM_PLL_BYPASS) {
				bBypassed = BT_TRUE;
			}
		}
	} else {
		bBypassed = BT_TRUE;
	}

	if(bBypassed) {
		return BT_CONFIG_MACH_ZYNQ_SYSCLOCK_FREQ;
	}

	BT_u64 fdiv = ZYNQ_SLCR_PLL_CTRL_FDIV_VAL(ctl);
	BT_u64 val = (BT_u64) BT_CONFIG_MACH_ZYNQ_SYSCLOCK_FREQ;
	val *= fdiv;

	//BT_u64 clk_div = ZYNQ_SLCR_CLK_CTRL_DIVISOR_VAL(pRegs->ARM_CLK_CTRL);

	return val;// / clk_div;
}

BT_u32 BT_ZYNQ_GetIOPLLFrequency() {

	BT_ERROR Error;
	volatile ZYNQ_SLCR_REGS *pRegs = bt_ioremap((void *)ZYNQ_SLCR, BT_SIZE_4K, &Error);

	BT_u32 ctl = pRegs->IO_PLL_CTRL;
	BT_BOOL bBypassed = BT_FALSE;

	if(!(ctl & ZYNQ_SLCR_PLL_CTRL_BYPASS_FORCE)) {
		if(ctl & ZYNQ_SLCR_PLL_CTRL_BYPASS_QUAL) {
			if(pRegs->BOOT_MODE & ZYNQ_SLCR_BOOT_MODE_IO_PLL_BYPASS) {
				bBypassed = BT_TRUE;
			}
		}
	} else {
		bBypassed = BT_TRUE;
	}

	if(bBypassed) {
		return BT_CONFIG_MACH_ZYNQ_SYSCLOCK_FREQ;
	}

	BT_u64 fdiv = ZYNQ_SLCR_PLL_CTRL_FDIV_VAL(ctl);
	BT_u64 val = (BT_u64) BT_CONFIG_MACH_ZYNQ_SYSCLOCK_FREQ;
	val *= fdiv;

	//BT_u64 clk_div = ZYNQ_SLCR_CLK_CTRL_DIVISOR_VAL(pRegs->IO_CLK_CTRL);

	return val;
}

BT_u32 BT_ZYNQ_GetDDRPLLFrequency() {

	BT_ERROR Error;
	volatile ZYNQ_SLCR_REGS *pRegs = bt_ioremap((void *)ZYNQ_SLCR, BT_SIZE_4K, &Error);

	BT_u32 ctl = pRegs->DDR_PLL_CTRL;
	BT_BOOL bBypassed = BT_FALSE;

	if(!(ctl & ZYNQ_SLCR_PLL_CTRL_BYPASS_FORCE)) {
		if(ctl & ZYNQ_SLCR_PLL_CTRL_BYPASS_QUAL) {
			if(pRegs->BOOT_MODE & ZYNQ_SLCR_BOOT_MODE_IO_PLL_BYPASS) {
				bBypassed = BT_TRUE;
			}
		}
	} else {
		bBypassed = BT_TRUE;
	}

	if(bBypassed) {
		return BT_CONFIG_MACH_ZYNQ_SYSCLOCK_FREQ;
	}

	BT_u64 fdiv = ZYNQ_SLCR_PLL_CTRL_FDIV_VAL(ctl);
	BT_u64 val = (BT_u64) BT_CONFIG_MACH_ZYNQ_SYSCLOCK_FREQ;
	val *= fdiv;

	//BT_u64 clk_div = ZYNQ_SLCR_CLK_CTRL_DIVISOR_VAL(pRegs->IO_CLK_CTRL);

	return val;
}

BT_u32 BT_ZYNQ_GetCpuFrequency() {
	BT_ERROR Error;
	volatile ZYNQ_SLCR_REGS *pRegs = bt_ioremap((void *)ZYNQ_SLCR, BT_SIZE_4K, &Error);

	BT_u32 	ctl 		= pRegs->ARM_CLK_CTRL;
	BT_u32 	srcsel 		= ZYNQ_SLCR_CLK_CTRL_SRCSEL_VAL(ctl);

	BT_u32	InputClk;

	switch(srcsel) {
	case ZYNQ_SLCR_CLK_CTRL_SRCSEL_ARMPLL:
		InputClk = BT_ZYNQ_GetIOPLLFrequency();		// This looks wrong! But the meaning of srcsel...
		break;

	case ZYNQ_SLCR_CLK_CTRL_SRCSEL_IOPLL:
		InputClk = BT_ZYNQ_GetArmPLLFrequency();	// ... is switched for ARM_CLK_CTRL!! :S typical Xilinx!
		break;

	case ZYNQ_SLCR_CLK_CTRL_SRCSEL_DDRPLL:
		InputClk = BT_ZYNQ_GetDDRPLLFrequency();
		break;

	default:
		return 0;
	}

	InputClk /= ZYNQ_SLCR_CLK_CTRL_DIVISOR_VAL(pRegs->ARM_CLK_CTRL);

	return InputClk;
}

BT_u32 BT_ZYNQ_GetCpu1xFrequency() {
	BT_ERROR Error;
	volatile ZYNQ_SLCR_REGS *pRegs = bt_ioremap((void *)ZYNQ_SLCR, BT_SIZE_4K, &Error);

	BT_u32 ulCPUClk = BT_ZYNQ_GetCpuFrequency();
	if(pRegs->CLK_621_TRUE) {
		return ulCPUClk / 6;
	}

	return ulCPUClk / 4;
}
