#include "main.h"

void mainproc(int param) {
	ScreenWidth = 320;
	ScreenHeight = 240;
	JW_BeginFrame();
	JW_EndFrame();
	mCD_init_card();
	osCreateMesgQueue(l_serialMsgQ, serialMsgBuf, 1);
	CreateIRQManager(padmgrStack, 0x1800, 0x12, 1);
	memset(padmgrStack, 0xEB, 0x1800);
	padmgr_Create(l_serialMsgQ, 7, 15, graphStack, 0x1800);
	osCreateThread2(graphThread, 4, graph_proc, param, zuruKeyCheck, 0x2400, 8);
	JW_BeginFrame();
	JW_EndFrame();
	osStartThread(graphThread);
	osSetThreadPri(0, 5);
	JW_Init3();
	JW_Init4();
	mMsg_aram_init2();
	mLd_StartFlagOn();
	famicom_mount_archive();
	JC_JKRAramHeap_dump(JC_JKRAram_getAramHeap());
	osSetThreadPri(0, 0);
	while (1)
		osYieldThread(); //we've set up, yield
}

int entry(void) {
	padmgr_Init(0);
	new_Debug_mode();
	*(uint16_t*)(debug_mode + 0xD4) = 0;
	mainproc(0);
	return 0; //should never happen
}

void main(void) { //called from _prolog
	OSReport("Animal Crossing main start\n");
	HotStartEntry = entry;
}