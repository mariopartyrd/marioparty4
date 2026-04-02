#include "types.h"
#include "asm_types.h"

/* clang-format off */

union FpscrUnion
{
    f64 f;
    struct
    {
        u32 fpscr_pad;
        u32 fpscr;
    }   u;
};

#define HID0_SPD 0x00000200  // Speculative cache access enable (0 enable)

void PPCMthid0 ( u32 newHID0 );

/*
 * --INFO--
 * Address:	8036F7D4
 * Size:	000008
 */
asm u32 PPCMfmsr (void)
{
    nofralloc
    mfmsr r3
    blr
}

/*
 * --INFO--
 * Address:	8036F7DC
 * Size:	000008
 */
asm void PPCMtmsr (register u32 newMSR)
{
    nofralloc
    mtmsr newMSR
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	00000C
 */
void PPCOrMsr(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00000C
 */
void PPCAndMsr(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00000C
 */
void PPCAndCMsr(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8036F7E4
 * Size:	000008
 */
asm u32 PPCMfhid0 (void)
{
    nofralloc
    mfspr r3, HID0
    blr
}

/*
 * --INFO--
 * Address:	8036F7EC
 * Size:	000008
 */
asm void PPCMthid0 (register u32 newHID0)
{
    nofralloc
    mtspr HID0, newHID0
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void PPCMfhid1(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8036F7F4
 * Size:	000008
 */
asm u32 PPCMfl2cr (void)
{
    nofralloc
    mfspr r3, L2CR
    blr
}

/*
 * --INFO--
 * Address:	8036F7FC
 * Size:	000008
 */
asm void PPCMtl2cr (register u32 newL2cr)
{
    nofralloc
    mtspr L2CR, newL2cr
    blr
}

/*
 * --INFO--
 * Address:	8036F804
 * Size:	000008
 */
__declspec ( weak ) asm void PPCMtdec ( register u32 newDec )
{
    nofralloc
    mtdec newDec
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void PPCMfdec(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8036F80C
 * Size:	000008
 */
asm void PPCSync (void)
{
    nofralloc
    sc
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
asm void PPCEieio(void) {
    nofralloc
    mfmsr       r5
    rlwinm      r6, r5, 0, 0x11, 0xf
    mtmsr       r6
    mfspr       r3, hid0
    ori         r4, r3, 8
    mtspr       hid0, r4
    isync
    eieio
    isync

    mtspr       hid0, r3
    mtmsr       r5
    isync

    blr
}

/*
 * --INFO--
 * Address:	8036F814
 * Size:	000014
 */
__declspec ( weak ) asm void PPCHalt (void) //spins infinitely
{
    nofralloc

    sync

_spin:
    nop
    li r3, 0
    nop
    b _spin

    // NEVER REACHED
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfmmcr0(void)
{
	nofralloc
	mfspr r3, MMCR0
	blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 * UNUSED
 */
asm void PPCMtmmcr0 (register u32 newMmcr0)
{
    nofralloc
    mtspr       MMCR0, newMmcr0
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfmmcr1(void)
{
    nofralloc
    mfspr       r3, MMCR1
    blr}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 * UNUSED
 */
asm void PPCMtmmcr1 (register u32 newMmcr1)
{
    nofralloc
    mtspr       MMCR1, newMmcr1
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfpmc1(void)
{
    nofralloc
    mfspr       r3, PMC1
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 * UNUSED
 */
asm void PPCMtpmc1 (register u32 newPmc1)
{
    nofralloc
    mtspr       PMC1, newPmc1
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfpmc2(void)
{
    nofralloc
    mfspr       r3, PMC2
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 * UNUSED
 */
asm void PPCMtpmc2 (register u32 newPmc2)
{
    nofralloc
    mtspr       PMC2, newPmc2
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfpmc3(void)
{
    nofralloc
    mfspr       r3, PMC2
    blr}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 * UNUSED
 */
asm void PPCMtpmc3 (register u32 newPmc3)
{
    nofralloc
    mtspr       PMC3, newPmc3
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfpmc4(void)
{
    nofralloc
    mfspr       r3, PMC4
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 * UNUSED
 */
asm void PPCMtpmc4 (register u32 newPmc4)
{
    nofralloc
    mtspr       PMC4, newPmc4
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfsia(void)
{
    nofralloc
    mfspr       r3, SIA
    blr}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMtsia(register u32 newSia)
{
    nofralloc
    mtspr       SIA, newSia
    blr
}

/*
 * --INFO--
 * Address:	8036F828
 * Size:	000020
 */
u32 PPCMffpscr(void)
{
    union FpscrUnion m;


    asm
    {
        mffs fp31
        stfd fp31, m.f;
    }

    return m.u.fpscr;
}

/*
 * --INFO--
 * Address:	8036F848
 * Size:	000028
 */
void PPCMtfpscr(register u32 newFPSCR)
{
    union FpscrUnion m;

    asm
    {
        li    r4, 0
        stw   r4, m.u.fpscr_pad;
        stw   newFPSCR, m.u.fpscr
        lfd   fp31, m.f
        mtfsf 0xff, fp31
    }
}

/*
 * --INFO--
 * Address:	8036F870
 * Size:	000008
 */
asm u32 PPCMfhid2 ( void )
{
    nofralloc
    mfspr r3, HID2
    blr
}

/*
 * --INFO--
 * Address:	8036F878
 * Size:	000008
 */
asm void PPCMthid2 ( register u32 newhid2 )
{
    nofralloc
    mtspr HID2, newhid2
    blr
}

/*
 * --INFO--
 * Address:	8036F880
 * Size:	00000C
 */
asm u32 PPCMfwpar(void)
{
	nofralloc
	sync
	mfspr r3, WPAR
	blr
}

/*
 * --INFO--
 * Address:	8036F88C
 * Size:	000008
 */
asm void PPCMtwpar ( register u32 newwpar )
{
    nofralloc
    mtspr WPAR, newwpar
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfdmaU(void)
{
    nofralloc
    mfspr       r3, DMA_U
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
asm void PPCMfdmaL(void)
{
    nofralloc
    mfspr       r3, DMA_L
    blr
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void PPCMtdmaU(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void PPCMtdmaL(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void PPCMfpvr(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000028
 */
void PPCEnableSpeculation(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8036F894
 * Size:	000028
 */
void PPCDisableSpeculation (void)
{
    PPCMthid0(PPCMfhid0() | HID0_SPD);
}

/*
 * --INFO--
 * Address:	8036F8BC
 * Size:	000008
 */
asm void PPCSetFpIEEEMode(void)
{
    nofralloc
    mtfsb0      4*7+1
    blr
}
/*
 * --INFO--
 * Address:	8036F8C4
 * Size:	000008
 */
asm void PPCSetFpNonIEEEMode (void)
{
    nofralloc
    mtfsb1      4*7+1
    blr
}

/* clang-format on */
