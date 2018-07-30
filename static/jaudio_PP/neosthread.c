uint8_t neosproc_mq[0x20];
uint8_t task_buf[0x6400];
uint32_t tasks[2];
uint32_t* tmp_buf, msgbuf;
int cur, init, neos_ready, neosproc_mq_init;

int Neos_Update(uint16_t* idk) {
	if (neosproc_mq_init == 0)
		return 0; //error
	return !OSSendMessage(neosproc_mq, idk, 0);
}

void ImageLoaded(uint32_t idk) {
	OSSendMessage(neosproc_mq, 0x12345678, 1); //signal we're done, block
}

int Neos_CheckBoot(void) {
	return neos_ready;
}

void neosproc(void* idk) {
	void* msg = 0;
	if (init == 0)
		cur = 0; init = 1;
	neos_ready = 0;
	OSInitMessageQueue(neosproc_mq, msgbuf, 1);
	neosproc_mq_init = 1;
	DVDT_LoadtoARAM(0, "/audiorom.img", GetNeosRom_PreLoaded() - GetNeosRomTop(), GetNeos_FileTop(), 0, 0, ImageLoaded);
	do {OSReceiveMessage(neosproc_mq, msg, 1);} while (msg != 0x12345678); //wait for image to load ^^^
	tmp_buf = OSAlloc2(DAC_SIZE << 1);
	Nas_InitAudio(OSAlloc2(AGC + 4), AGC + 4);
	NeosSync();
	neos_ready = 1;
	Jac_RegisterMixcallback(MixCpu, 3);
	while (1) { //???
		OSReceiveMessage(neosproc_mq, msg, 1);
		Probe_Start(8, "NEOS THREAD");
		tasks[cur] = CreateAudioTask(task_buf + (curr * 0x3200), tmp_buf, JAC_FRAMESAMPLES, 0);
		cur = (cur + 1) & 1; //technically done after NeosSync vvv but
		if (tasks[cur] != 0) {
			RspStart2(task_buf + (cur * 0x3200), tasks[cur], 0);
			tasks[cur] = 0;
			Jac_bcopy(tmp_buf, msg, DAC_SIZE << 1);
		} else
			Jac_bzero(msg, DAC_SIZE << 1);
		Probe_Finish(8);
		NeosSync();
	}
}