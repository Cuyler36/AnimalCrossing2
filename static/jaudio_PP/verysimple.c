void Jac_Start(void* r3, uint32_t r4, uint32_t r5) {
	StartAudioThread(r3, r4, r5, 7);
	Jac_WaveDirectorySet("/");
	Jac_PlayInit();
	Jac_Portcmd_Init();
}

void Jac_PlayInit(void) {
	Jaq_Reset();
	Jac_ConnectTableInit();
	Jam_InitRegistTrack();
}