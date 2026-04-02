#ifndef _DOLPHIN_THP
#define _DOLPHIN_THP

#include "dolphin/types.h"
#include "dolphin/thp/THPAudio.h"
#include "dolphin/thp/THPVideoDecode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 THPSample;
typedef s16 THPCoeff;
typedef f32 THPQuantTab[64];

typedef struct _THPHuffmanTab {
  u8 quick[32];
  u8 increment[32];
  u8* Vij;
  s32 maxCode[18];
  s32 valPtr[18];
  u8 Vij1;
  u8 pad[11];
} THPHuffmanTab;

typedef struct _THPComponent {
  u8 quantizationTableSelector;
  u8 DCTableSelector;
  u8 ACTableSelector;
  THPCoeff predDC;
} THPComponent;

typedef struct _THPFileInfo {
  THPQuantTab quantTabs[3];
  THPHuffmanTab huffmanTabs[4];
  THPComponent components[3];
  u16 xPixelSize;
  u16 yPixelSize;
  u16 MCUsPerRow;
  u16 decompressedY;
  u8* c;
  u32 currByte;
  u32 cnt;
  u8 validHuffmanTabs;
  u8 RST;
  u16 nMCU;
  u16 currMCU;
  u8* dLC[3];
} THPFileInfo;

s32 __THPAudioGetNewSample(THPAudioDecodeInfo*);
void __THPAudioInitialize(THPAudioDecodeInfo*, u8*);

static void __THPSetupBuffers(void);
static u8 __THPReadFrameHeader(void);
static u8 __THPReadScaneHeader(void);
static u8 __THPReadQuantizationTable(void);
static u8 __THPReadHuffmanTableSpecification(void);
static void __THPHuffGenerateSizeTable(void);
static void __THPHuffGenerateCodeTable(void);
static void __THPHuffGenerateDecoderTables(u8 tabIndex);
static void __THPRestartDefinition(void);
static void __THPPrepBitStream(void);
static void __THPDecompressYUV(void*, void*, void*);
static void __THPGQRRestore(void);
static void __THPDecompressiMCURow512x448(void);
static void __THPDecompressiMCURow640x480(void);
static void __THPDecompressiMCURowNxN(void);
static void __THPInverseDCTNoYPos(THPCoeff*, u32);
static void __THPHuffDecodeDCTCompY(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompU(THPFileInfo*, THPCoeff*);
static void __THPHuffDecodeDCTCompV(THPFileInfo*, THPCoeff*);

static const u8 __THPJpegNaturalOrder[80] = {
    0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,  12, 19, 26, 33,
    40, 48, 41, 34, 27, 20, 13, 6,  7,  14, 21, 28, 35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51, 58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54,
    47, 55, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63};

static const f64 __THPAANScaleFactor[8] = {
    1.0f, 1.387039845f, 1.306562965f, 1.175875602f, 1.0f, 0.785694958f, 0.541196100f, 0.275899379f,
};

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_THP
