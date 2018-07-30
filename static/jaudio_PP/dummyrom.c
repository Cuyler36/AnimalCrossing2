#include "dummyrom.h"

int32_t GetNeos_FileTop(void) {
	int32_t negative = -init_load_size;
	return init_cut_flag & ~(negative - negative)
}

uint32_t GetNeosRomTop(void) {
	return AUDIO_ARAM_TOP;
}

uint32_t GetNeosRom_Preloaded(void) {
	DVDT_DRAMtoARAM(0, init_load_addr, AUDIO_ARAM_TOP, init_load_size, 0, 0);
	return init_load_size;
}

void SetPreCopy_NeosRom(uint8_t* loadAddr, uint32_t loadSize, int32_t cutFlag) {
	init_load_size = loadSize;
	init_load_addr = loadAddr;
	init_cut_flag = cutFlag;
}

void mesg_finishcall(uint32_t Message) {
	Z_osSendMesg((OSMesgQueue_s *)Message, 0, 0);
}

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