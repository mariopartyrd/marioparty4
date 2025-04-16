#include "dolphin.h"
#include "game/flag.h"
#include "game/dvd.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/thpmain.h"
#include "game/gamework_data.h"

#include "version.h"

#define SR_DVD_LOADING 0
#define SR_DVD_COVER_OPEN 1
#define SR_DVD_NO_DISK 2
#define SR_DVD_WRONG_DISK 3
#define SR_DVD_RETRY_ERROR 4
#define SR_DVD_FATAL_ERROR 5

#define PAD_BTN_SRESET (PAD_BUTTON_START|PAD_BUTTON_X|PAD_BUTTON_B)
#define PAD_BTN_SRESET_SHORT (PAD_BUTTON_X|PAD_BUTTON_B)

extern s32 HuDvdErrWait;

static s32 SR_PreRstChk[4] = {0, 0, 0, 0};

#if VERSION_JP
static s32 padding[4] = {0, 0, 0, 0};
#endif

#if VERSION_ENG

#include "coveropen_en.inc"
#include "fatalerror_en.inc"
#include "loading_en.inc"
#include "nodisc_en.inc"
#include "retryerror_en.inc"
#include "wrongdisc_en.inc"

#elif VERSION_PAL

#include "coveropen_en.inc"
#include "fatalerror_en.inc"
#include "loading_en.inc"
#include "nodisc_en.inc"
#include "retryerror_en.inc"
#include "wrongdisc_en.inc"

#include "coveropen_fr.inc"
#include "fatalerror_fr.inc"
#include "loading_fr.inc"
#include "nodisc_fr.inc"
#include "retryerror_fr.inc"
#include "wrongdisc_fr.inc"

#include "coveropen_ge.inc"
#include "fatalerror_ge.inc"
#include "loading_ge.inc"
#include "nodisc_ge.inc"
#include "retryerror_ge.inc"
#include "wrongdisc_ge.inc"

#include "coveropen_it.inc"
#include "fatalerror_it.inc"
#include "loading_it.inc"
#include "nodisc_it.inc"
#include "retryerror_it.inc"
#include "wrongdisc_it.inc"

#include "coveropen_sp.inc"
#include "fatalerror_sp.inc"
#include "loading_sp.inc"
#include "nodisc_sp.inc"
#include "retryerror_sp.inc"
#include "wrongdisc_sp.inc"

#else

#include "coveropen_jp.inc"
#include "fatalerror_jp.inc"
#include "loading_jp.inc"
#include "nodisc_jp.inc"
#include "retryerror_jp.inc"
#include "wrongdisc_jp.inc"

#endif

static s16 SR_PushTime[4] = {};
static s8 SR_ResetPad = -1;

static s16 XfbW;
static s16 XfbH;
static s32 XfbProg;
static void *Xfb[2] = {};
static BOOL trychkBusyWait;
s32 SR_ExecReset;
static s32 SR_RestartChk;
static BOOL H_ResetReady;

void HuRestartSystem(void);

s32 HuSoftResetCheck(void);
s32 HuSoftResetCountCheck(void);
static void HuSoftResetPostProc(void);

s32 HuSoftResetButtonCheck(void)
{
	if(SR_ExecReset) {
		HuRestartSystem();
	}
	return (SR_ExecReset) ? 1 : 0;
}

static OSMessageQueue ToeMessageQueue;

void HuDvdErrDispIntFunc(u32 retraceCount)
{
	OSWakeupThread(&ToeMessageQueue.queueSend);
}

static void HuPreRstChk(void)
{
	static PADStatus padStat[4];
	int i;
	PADRead(padStat);
	for(i=0; i<4; i++) {
		PADStatus *status = &padStat[i];
		if(status->err != 0) { 
			continue;
		}
		if((status->button & PAD_BTN_SRESET) == PAD_BTN_SRESET) {
			SR_PreRstChk[i] = 1;
		} else {
			SR_PreRstChk[i] = 0;
		}
	}
}

static OSMessage ToeMessageArray[16];
static OSThread ToeThread;
static u8 ToeThreadStack[4096];

static void *ToeThreadFunc(void *param);
static void ToeDispCheck(void);

void HuDvdErrDispInit(GXRenderModeObj *rmode, void *xfb1, void *xfb2)
{
	BOOL intrOld;
	_ClearFlag(0x30000);
	SR_ResetPad = -1;
	SR_ExecReset = H_ResetReady = 0;
	SR_RestartChk = 0;
	SR_PushTime[0] = SR_PushTime[1] = SR_PushTime[2] = SR_PushTime[3] = 0;
	VIWaitForRetrace();
	VIWaitForRetrace();
	VIWaitForRetrace();
	HuPreRstChk();
	HuDvdErrWait = 0;
	Xfb[0] = xfb1;
	Xfb[1] = xfb2;
	if(rmode) {
		XfbW = (u16)(((u16)rmode->fbWidth+15) & ~0xF);
		XfbH = rmode->xfbHeight;
	} else {
		#if VERSION_NTSC
		XfbW = 640;
		XfbH = 480;
		#else
		XfbW = 640;
		XfbH = 528;
		#endif
	}
	#if VERSION_PAL
	(void)(VIGetTvFormat() == VI_PAL);
	#endif
	if((u16)rmode->xFBmode == VI_XFBMODE_SF) {
		XfbProg = 0;
	} else {
		XfbProg = 1;
	}
	trychkBusyWait = FALSE;
	OSInitMessageQueue(&ToeMessageQueue, ToeMessageArray, 16);
	OSCreateThread(&ToeThread, ToeThreadFunc, NULL, &ToeThreadStack[4096], 4096, 8, OS_THREAD_ATTR_DETACH);
	OSResumeThread(&ToeThread);
	intrOld = OSDisableInterrupts();
	VISetPreRetraceCallback(HuDvdErrDispIntFunc);
	OSRestoreInterrupts(intrOld);
}

static void *ToeThreadFunc(void *param)
{
	while(1) {
		BOOL hide_disp;
		OSSleepThread(&ToeMessageQueue.queueSend);
		if(!_CheckFlag(FLAG_ID_MAKE(3, 0))) {
			BOOL reset;
			if(!HuSoftResetCheck()) {
				if(SR_ExecReset) {
					reset = TRUE;
				} else {
					if(H_ResetReady == TRUE && OSGetResetButtonState() != TRUE) {
						reset = TRUE;
					} else {
						if(H_ResetReady != TRUE && OSGetResetButtonState() == TRUE) {
							H_ResetReady = TRUE;
						}
						reset = FALSE;
					}
				}
				if(reset) {
					proc_reset:
					HuSoftResetPostProc();
				}
			}  else {
				goto proc_reset;
			}
		}
		if(SR_ExecReset) {
			HuRestartSystem();
		}
		if(SR_ExecReset) {
			hide_disp = TRUE;
		} else {
			hide_disp = FALSE;
		}
		if(!hide_disp) {
			ToeDispCheck();
		}
	}
}

static void _HuDvdErrDispXFB(s32 error);

static void ToeDispCheck(void)
{
	s32 status;
	if(SR_ResetPad != -1 || SR_ExecReset != FALSE || SR_RestartChk != 0) {
		return;
	}
	status = DVDGetDriveStatus();
	switch(status) {
		case DVD_STATE_FATAL_ERROR:
			status = SR_DVD_FATAL_ERROR;
			trychkBusyWait = TRUE;
			break;
			
		case DVD_STATE_END:
			HuDvdErrWait = 0;
			trychkBusyWait = FALSE;
			return;
			
		case DVD_STATE_COVER_OPEN:
			status = SR_DVD_COVER_OPEN;
			trychkBusyWait = TRUE;
			break;
			
		case DVD_STATE_BUSY:
		case DVD_STATE_COVER_CLOSED:
			if(!trychkBusyWait) {
				return;
			}
			status = SR_DVD_LOADING;
			break;
			
		case DVD_STATE_NO_DISK:
			status = SR_DVD_NO_DISK;
			trychkBusyWait = TRUE;
			break;
			
		case DVD_STATE_WRONG_DISK:
			status = SR_DVD_WRONG_DISK;
			trychkBusyWait = TRUE;
			break;
			
		case DVD_STATE_RETRY:
			status = SR_DVD_RETRY_ERROR;
			trychkBusyWait = TRUE;
			break;
			
		default:
			return;
	}
	HuDvdErrWait = 1;
	HuPadRumbleAllStop();
	VISetBlack(FALSE);
	VIFlush();
	if(msmSysCheckInit()) {
		HuAudSStreamAllStop();
	}
	_HuDvdErrDispXFB(status);
}

#if VERSION_NTSC

#define XFB_SIZE 0x96000

#else

#define XFB_SIZE (XfbW*XfbH*2)

#endif

static void _HuDvdErrDispXFB(s32 error)
{
	#if VERSION_ENG
	static void *bmpMes[][6] = {
		 loading_en, coveropen_en, nodisc_en, wrongdisc_en, retryerror_en, fatalerror_en
	};
	#elif VERSION_PAL
	static void *bmpMes[][6] = {
		loading_en, coveropen_en, nodisc_en, wrongdisc_en, retryerror_en, fatalerror_en,
		loading_fr, coveropen_fr, nodisc_fr, wrongdisc_fr, retryerror_fr, fatalerror_fr,
		loading_ge, coveropen_ge, nodisc_ge, wrongdisc_ge, retryerror_ge, fatalerror_ge,
		loading_it, coveropen_it, nodisc_it, wrongdisc_it, retryerror_it, fatalerror_it,
		loading_sp, coveropen_sp, nodisc_sp, wrongdisc_sp, retryerror_sp, fatalerror_sp
	};
	#else
	static void *bmpMes[][6] = {
		 loading_jp, coveropen_jp, nodisc_jp, wrongdisc_jp, retryerror_jp, fatalerror_jp
	};
	#endif
	
	s16 *bmpData;
	u8 *xfb1_ptr;
	u8 *xfb2_ptr;
	u32 i;
	u32 data;
	u32 row;
	s8 language;
	u32 *xfb1;
	u32 *xfb2;
	u32 j;
	u8 y1;
	u8 y2;
	s32 reset;
	u32 *data_ptr;
	u32 row_offset;
	u32 row_pitch;
	void *tempfb1;
	void *tempfb2;
	s32 status;
	u8 color[2];
	
	
	#if VERSION_PAL
	switch(GWGameStat.language) {
		case 2:
			language = 2;
			break;
		
		case 3:
			language = 1;
			break;
		
		case 4:
			language = 3;
			break;
		
		case 5:
			language = 4;
			break;
			
		default:
			language = 0;
			break;
	}
	#else
	language = 0;
	#endif
	xfb1 = Xfb[0];
	xfb2 = Xfb[1];
	for(i=0; i<XFB_SIZE/4; i++, xfb1++, xfb2++) {
		#if VERSION_NTSC
		*xfb1 = *xfb2 = 0x800080;
		#else
		*xfb1 = *xfb2 = 0x10801080;
		#endif
	}
	DCStoreRangeNoSync(Xfb[0], XFB_SIZE);
	DCStoreRangeNoSync(Xfb[1], XFB_SIZE);
	bmpData = bmpMes[language][error];
	data_ptr = (u32 *)(bmpData+2);
	row_offset = ((XfbW/2)-(bmpData[0]/2))*2;
	row_pitch = XfbW*2;
	color[1] = color[0] = 128;
	for(row=0; row<bmpData[1]; row++) {
		
		xfb1_ptr = ((u8 *)(Xfb[0])+((row+200)*row_pitch)+row_offset);
		tempfb1 = xfb1_ptr;
		xfb2_ptr = ((u8 *)(Xfb[1])+((row+200)*row_pitch)+row_offset);
		tempfb2 = xfb2_ptr;
		for(i=0; i<bmpData[0]; i += 32) {
			data = *data_ptr++;
			for(j=0; j<32; j += 2, data >>= 2, xfb1_ptr += 4, xfb2_ptr += 4) {
				if(data & 0x3){
					if(data & 0x1) {
						y1 = 0xEB;
					} else {
						y1 = 0x10;
					}
					if(data & 0x2) {
						y2 = 0xEB;
					} else {
						y2 = 0x10;
					}
					xfb1_ptr[0] = y1;
					xfb1_ptr[1] = color[1];
					xfb1_ptr[2] = y2;
					xfb1_ptr[3] = color[0];
					xfb2_ptr[0] = y1;
					xfb2_ptr[1] = color[1];
					xfb2_ptr[2] = y2;
					xfb2_ptr[3] = color[0];
				}
			}
		}
		DCStoreRangeNoSync(tempfb1, bmpData[0]*2);
		DCStoreRangeNoSync(tempfb2, bmpData[0]*2);
	}
	status = DVDGetDriveStatus();
	while(status) {
		if(status != DVDGetDriveStatus()) {
			break;
		}
		if(SR_ExecReset) {
			reset = TRUE;
		} else {
			if(H_ResetReady == TRUE && OSGetResetButtonState() != TRUE) {
				reset = TRUE;
			} else {
				if(H_ResetReady != TRUE && OSGetResetButtonState() == TRUE) {
					H_ResetReady = TRUE;
				}
				reset = FALSE;
			}
		}
		if(reset) {
			if(msmSysCheckInit()) {
				msmStreamSetMasterVolume(0);
				msmSeSetMasterVolume(0);
				msmMusSetMasterVolume(0);
			}
			HuRestartSystem();
		}
		
		OSYieldThread();
	}
}

void HuRestartSystem(void)
{
	u32 retrace[2];
	BOOL prevInt;
	if(SR_RestartChk) {
		return;
	}
	SR_RestartChk = TRUE;
	PADRecalibrate(PAD_CHAN0_BIT|PAD_CHAN1_BIT|PAD_CHAN2_BIT|PAD_CHAN3_BIT);
	msmSysCheckInit();
	VISetBlack(TRUE);
	VIFlush();
	prevInt = OSDisableInterrupts();
	if(!prevInt) {
		OSReport("PrevInt=DISABLE!!\n");
	}
	OSEnableInterrupts();
	retrace[1] = VIGetRetraceCount();
	retrace[0] = 0;
	while(retrace[1] == VIGetRetraceCount()) {
		if(retrace[0]++ >= 1349800) {
			break;
		}
	}
	OSReport("Timeout Count=%d\n", retrace[0]);
	__GXAbortWaitPECopyDone();
	OSResetSystem(0, 0, 0);
}

s32 HuSoftResetCheck(void)
{
	int i;
	if(VCounter == 0) {
		return 0;
	}
	if(SR_ExecReset) {
		return 1;
	}
	if(SR_ResetPad != -1) {
		if(!(_PadBtn[SR_ResetPad] & PAD_BTN_SRESET)) {
			return 1;
		}
	} else {
		for(i=0; i<4; i++) {
			if(SR_PreRstChk[i] && (_PadBtn[i] & PAD_BTN_SRESET) != PAD_BTN_SRESET) {
				SR_PreRstChk[i] = 0;
			}
		}
	}
	
	if(HuSoftResetCountCheck()) {
		return 1;
	} else {
		return 0;
	}
}

s32 HuSoftResetCountCheck(void)
{
	int i;
	for(i=0; i<4; i++) {
		if((_PadBtn[i] & PAD_BTN_SRESET_SHORT) != PAD_BTN_SRESET_SHORT) {
			SR_PushTime[i] = 0;
		} else {
			if(!SR_PreRstChk[i]) {
				if(_PadBtn[i] & PAD_BUTTON_START) {
					if(SR_PushTime[i]++ >= 30) {
						SR_ResetPad = i;
						return 1;
					}
				} else {
					SR_PushTime[i] = 0;
				}
			}
		}
	}
	return 0;
}

static void HuSoftResetPostProc(void)
{
	if(!SR_ExecReset) {
		VISetBlack(TRUE);
		VIFlush();
		if(THPProc) {
			HuTHPStop();
			HuTHPClose();
		}
		if(msmSysCheckInit()) {
			msmStreamSetMasterVolume(0);
			msmSeSetMasterVolume(0);
			msmMusSetMasterVolume(0);
		}
		HuPadRumbleAllStop();
		SR_ExecReset = TRUE;
	}
}
