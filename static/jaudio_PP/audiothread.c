#include "audiothread.h"

/*
8001CBA0 .text
8001CBA0 DspSyncCountClear
8001CBC0 DspSyncCountCheck
8001CBE0 DspSync__Fv
8001CC40 AudioSync__Fv
8001CCC0 NeosSync__Fv
8001CD00 __DspSync__FsP9OSContext
8001CD80 __DspReg__Fv
8001CDE0 audioproc__FPv*/
void StartAudioThread(void* r3, uint32_t r4, uint32_t r5, uint32_t r6) {
	if (priority_set) {
		pri = OSGetThreadPriority(OSGetCurrentThread()) - 3;
		pri3 = pri + 1;
		pri2 = pri + 2;
	}
	Jac_HeapSetup(r3, r4);
	Jac_SetAudioARAMSize(r5);
	Jac_InitARAM(r6 & 4);
	if (r6 & 2) {
		OSCreateThread(jac_audioThread, audioproc, 0, neosStack, 0x2000, pri, 0);
		OSResumeThread(jac_audioThread);
	}

	if (r6 & 1) {
		jac_dvdproc_init();
		OSCreateThread(jac_dvdThread, jac_dvdproc, 0, audioproc_mq, 0x2000, pri3, 0);
		OSResumeThread(jac_dvdThread);
	}

	if (r6 & 4) {
		OSCreateThread(jac_neosThread, neosproc, 0, dvdStack, 0x2000, pri2, 0);
		OSResumeThread(jac_neosThread);
	}
}

/*8001D080 .text_00
8001D080 OSInitFastCast
*/