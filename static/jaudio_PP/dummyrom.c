#include "dummyrom.h"

/*
8001C900 .text
8001C900 GetNeos_FileTop__Fv
8001C920 GetNeosRomTop__Fv
8001C940 GetNeosRom_PreLoaded__Fv
8001C980 SetPreCopy_NeosRom__FPUcUli
8001C9A0 mesg_finishcall__FUl
8001C9E0 ARAMStartDMAmesg__FUlUlUlUllP13OSMesgQueue_s*/
int ARAMStartDMAmesg(uint32_t ARAMtoDRAM, uint32_t DRAMAddress, uint32_t ARAMAddress, uint32_t DMASize, int32_t Unused, OSMesgQueue_s* Message) {
	ARAMAddress += AUDIO_ARAM_TOP; // Usually 0x4000
	if (ARAMtoDRAM == 1) {
		DVDT_ARAMtoDRAM(Message, DRAMAddress, ARAMAddress, DMASize, 0, &mesg_finishcall);
	}
	else {
		DVDT_DRAMtoARAM(Message, DRAMAddress, ARAMAddress, DMASize, 0, &mesg_finishcall);
	}
	return 0;
}

void Jac_SetAudioARAMSize(uint32_t size) {
	SELECTED_ARAM_SIZE = size;
}

uint32_t ARAllocFull(uint32_t* idk) {
	idk = (get_ptr(aram_hp + 8) - (get_ptr(aram_hp + 4) - get_ptr(aram_hp))) - 32;
	return Nas_HeapAlloc(aram_hp, idk);
}

void Jac_InitARAM(uint32_t idk) {
	uint32_t size;
	AUDIO_ARAM_TOP = ARGetBaseAddress();
	if (idk == 0)
		size = 0;
	else {
		size = Jac_CheckFile("/audiorom.img");
		if (size != 0)
			size = (size + 0x1F) & 0xFFFFFFE0;
	}
	CARD_SECURITY_BUFFER = 64;
	size += AUDIO_ARAM_TOP;
	JAC_ARAM_DMA_BUFFER_TOP = size;
	size += 0xC000;
	if (SELECTED_ARAM_SIZE)
		Nas_HeapInit(aram_hp, size, SELECTED_ARAM_SIZE - size);
	else
		Nas_HeapInit(aram_hp, size, 0x810000 - size);
}