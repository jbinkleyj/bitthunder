/**
 *	Timer API
 *
 **/

#include <bitthunder.h>

struct _BT_OPAQUE_HANDLE {
	BT_HANDLE_HEADER h;
};

typedef struct _BT_TIMER_CONTROLLER {
	BT_HANDLE 	hTimers;
	BT_u32		ulBaseTimer;
	BT_u32		ulTotalTimers;
} BT_TIMER_CONTROLLER;

static BT_HANDLE g_hTimer = NULL;
static const BT_DEV_IF_SYSTIMER *g_Ops = NULL;

BT_ERROR BT_SetSystemTimerHandle(BT_HANDLE hTimer) {
	if(!g_hTimer) {
		g_hTimer = hTimer;
		g_Ops = BT_IF_SYSTIMER_OPS(hTimer);
	}

	return BT_ERR_NONE;
}

BT_ERROR BT_StopSystemTimer() {
	return g_Ops->pfnStop(g_hTimer);
}

BT_u32 BT_GetSystemTimerOffset() {
	BT_ERROR Error;

	if(g_hTimer) {
		BT_u32 rate = g_Ops->pfnGetClockRate(g_hTimer, &Error);
		return g_Ops->pfnGetOffset(g_hTimer, &Error) / (rate / 1000000);
	}
	return 0;
}


BT_u32 BT_GetKernelTime() {
	BT_u32 us = 0;
	us += (1000 * BT_kTickCount());

	return us + BT_GetSystemTimerOffset();
}

BT_u32 BT_GetKernelTick() {
	return BT_kTickCount();
}
