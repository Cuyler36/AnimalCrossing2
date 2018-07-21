#include "boot.h"

/*
800056A0 .text
800056A0 search_partial_address
80005760 convert_partial_address
800057C0 LoadStringTable
8000580C UnLink
800058B8 LoadLink
80005AA4 LoadLink_compare
80005B44 Get_free_buff_p_for_moduleI_or_moduleO
80005B74 set_info_ReloadLink_module_IorO
80005BD0 reset_info_ReloadLink_module_IorO
80005BE8 ReloadLink_module_IorO
80005D78 audioFatalCallback
80005DA8 sound_initial
80005DF0 sound_initial2
80005E38 HotResetIplMenu
80005E88 fault_callback_keyCheck
80005F20 fault_callback_OK
80005F58 fault_callback_Setumei
80005F84 fault_callback_first
8000608C fault_callback_vimode
800060B8 fault_callback_scroll
800062FC adjustOSArena
800063F0 version_check*/

int main(int argc, const char *argv[]) {
	//TODO: standardize case, add some stuff, audited p well
	uint32_t saveStart, saveEnd;
	uint64_t InitialStartTime;
	uint16_t tbl[3]; //easiest way ig
	DVDFileInfo fileInfo;
	
	version_check();
	ReconfigBATs();
	if (fakemain_check != 0)
		return -1;
	fakemain_check = 1;
	InitialStartTime = osGetTime();
	OSInit();
	OSInitAlarm();
	bzero(osAppNMIBuffer, 0x40);
	
	if (!OSGetResetCode()) //s32, can be negative
		OSReport("System Power On\n");
	else if (OSGetResetCode() < 0) {
		OSReport("Restart\n");
		OSGetSaveRegion(saveStart, saveEnd);
		OSReport("OSGetSaveRegion %08x %08x\n", saveStart, saveEnd);
		bcopy(0x811FFFC0, osAppNMIBuffer, 0x40);
	} else {
		OSReport("Hot Reset\n");
		OSReport("OSGetResetCode=0x%08x\n", OSGetResetCode);
		OSReport("Ignore the reset code in release version\n");
	}
	
	__osInitialize_common();
	if (OSGetConsoleType() & 0x10000000) {
		osAppNMIBuffer[15] |= 0x10;
	} else {
		if (osAppNMIBuffer[15] & 0x10) {
			OSReport("Resetting and returning to Development Mode.\n");
			OSChangeBootMode(0);
			OSResetSystem(1, osAppNMIBuffer[15], 0);
		}
	}
	
	if (*(uint8_t*)(DVDGetCurrentDiskID() + 7) == 0x99)
		osAppNMIBuffer[15] |= 0x20;
	if (*(uint8_t*)(DVDGetCurrentDiskID() + 7) >= 0x90)
		osAppNMIBuffer[15] |= 0x40;
	if (*(uint8_t*)(DVDGetCurrentDiskID() + 7) >= 0x90) {
		OSReport("ZURUMODE2 ENABLE\n");
		osAppNMIBuffer[15] |= 8;
	}
	
	OSReport("osAppNMIBuffer[15]=0x%08x\n", osAppNMIBuffer[15]);
	if (osAppNMIBuffer[15] & 4) {
		osAppNMIBuffer[15] &= 0xFFFFFFFB;
		osAppNMIBuffer[15] |= 2;
		OSReport("Set an exception flag that was reset due to abnormal state.\n");
	} else
		osAppNMIBuffer[15] &= 0xFFFFFFFD;
	
	osAppNMIBuffer[15] |= 4;
	
	OSReport("Animal Crossing bootloader entry\n");
	adjustOSArena();

	DVDOpen("audiorom.img", fileInfo); //get fileInfo
	DVDClose(fileInfo);
	JW_soundAramSize = Na_GetAudioARAMSize((fileInfo.size + 0x1F) & 0xFFFFFFE0, 0x66A0);
	
	JW_Init();
	if (osAppNMIBuffer[15] & 0x20) { //debug
		JC_JUTProcBar_setVisible(JC_JUTProcBar_getManager(), (osAppNMIBuffer[15] & 0x40) >> 6);
		JC_JUTProcBar_setVisibleHeapBar(JC_JUTProcBar_getManager(), (osAppNMIBuffer[15] & 0x40) >> 6);
	}
	
	JC_JUTException_setMapFile("/static.map");
	JC_JUTException_enterAllPad(JC_JUTException_getManager());
	
	fault_Init();
	fault_AddClientEx(my_fault_client7, fault_callback_first, 0, 0, 10, 14);
	fault_AddClientEx(my_fault_client5, fault_callback_vimode, 0, 0, 10, 14);
	fault_AddClientEx(my_fault_client1, fault_callback_keyCheck, tbl, (tbl[2] << 16) | tbl[1], 10, 14);
	fault_AddClientEx(my_fault_client2, fault_callback_OK, 0, 0, 10, 14);
	fault_AddClientEx(my_fault_client3, fault_callback_Setumei, 0, 0, 10, 9);
	fault_AddClientEx(my_fault_client6, fault_callback_scroll, 0, 0, 1, 9);
	fault_AddClient(my_fault_client4, DisplayArena, 0, 0);
	
	if (osAppNMIBuffer[15] & 0x40) { //debug
		JC_JUTAssertion_changeDevice(3);
		JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), 1);
	} else {
		JC_JUTAssertion_changeDevice(2);
		JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), 0);
	}
	
	JC_JUTAssertion_changeDisplayTime(0x258);
	//todo: stupid InitialStartTime calc
	sound_initial();
	initial_menu_init();
	dvderr_init();
	sound_initial2();
	if (!(OSGetConsoleType() & 0x10000000)) {
		OSReport("Retail, Disabling OSReport\n");
		OSReportDisable();
	}
	OSReport("Logging COPYDATE\n");
	boot_copyDate = JC__JKRDvdToMainRam_byName("/COPYDATE", 0, 1);
	if (boot_copyDate == 0)
		OSDVDFatalError();
	LoadStringTable("/static.str");
	//todo: stack stuff here part 1
	moduleD = LoadLink("/forestd.rel.szs", 0, 0, 1, 0, 0, 0);
	moduleA = LoadLink("/foresta.rel.szs", 0, 0, 1, 0, 0, 0);
	JW_Load_AGB_archive_special();
	JW_Load_picture_copy_archive();
	JW_Init2();
	initial_menu_cleanup();
	if (!buff_p_for_moduleI_or_moduleO) {
		//todo: stack stuff here part 2
	}
	if (moduleD == 0)
		moduleD = LoadLink("/forestd.rel.szs", 0, 0, 1, 0, 0, 0);
	if (moduleA == 0)
		moduleA = LoadLink("/foresta.rel.szs", 0, 0, 1, 0, 0, 0);
	if (!JW_Get_AgbTarget_Special_archive_p())
		JW_Load_AGB_archive_special();
	if (!JW_Get_picture_copy_archive_p())
		JW_Load_picture_copy_archive();
	JC_JKRExpHeap_changeGroupID(JC_JFWSystem_getSystemHeap(), 5);
	
	while (HotStartEntry != 0) {
		OSReport("Hot Start (%08x)\n");
		HotStartEntry = HotStartEntry();
	}
	JW_Unload_picture_copy_archive();
	JW_Unload_AGB_archive_special();
	
	UnLink(moduleA, 0, 1);
	moduleA = 0;
	UnLink(moduleD, 0, 1);
	moduleD = 0;
	UnLink(moduleI, 0, 1);
	moduleI = 0;
	UnLink(moduleO, 0, 1);
	moduleO = 0;
	
	buff_p_for_moduleI_or_moduleO = 0;
	buff_size_for_moduleI_or_moduleO = 0;
	reset_info_ReloadLink_module_IorO();
	
	if (StringTable) {
		JW_Free(StringTable);
		StringTable = 0;
	}

	OSReport("Animal Crossing bootloader exit\n");
	JW_Cleanup();
	return 0;
}