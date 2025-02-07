#ifndef METROTRK_PORTABLE_MSGBUF_H
#define METROTRK_PORTABLE_MSGBUF_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

DSError TRKInitializeMessageBuffers(void);

DSError TRKSetBufferPosition(TRKBuffer* msg, u32 pos);
void* TRKGetBuffer(int);
void TRKResetBuffer(TRKBuffer* msg, u8 keepData);
void* TRKGetBuffer(int idx);
void TRKReleaseBuffer(int idx);
DSError TRKGetFreeBuffer(int* msgID, TRKBuffer** outMsg);

DSError TRKAppendBuffer(TRKBuffer* msg, const void* data, size_t length);
DSError TRKAppendBuffer1_ui8(TRKBuffer* buffer, const u8 data);
inline DSError TRKAppendBuffer1_ui8(TRKBuffer* buffer, const u8 data)
{
	if (buffer->position >= TRKMSGBUF_SIZE) {
		return DS_MessageBufferOverflow;
	}

	buffer->data[buffer->position++] = data;
	buffer->length++;
	return DS_NoError;
}
DSError TRKAppendBuffer1_ui16(TRKBuffer* buffer, const u16 data);
DSError TRKAppendBuffer1_ui32(TRKBuffer* buffer, const u32 data);
DSError TRKAppendBuffer1_ui64(TRKBuffer* buffer, const u64 data);
DSError TRKAppendBuffer_ui8(TRKBuffer* buffer, const u8* data, int count);
DSError TRKAppendBuffer_ui32(TRKBuffer* buffer, const u32* data, int count);

DSError TRKReadBuffer1_ui8(TRKBuffer* buffer, u8* data);
DSError TRKReadBuffer1_ui16(TRKBuffer* buffer, u16* data);
DSError TRKReadBuffer1_ui32(TRKBuffer* buffer, u32* data);
DSError TRKReadBuffer1_ui64(TRKBuffer* buffer, u64* data);
DSError TRKReadBuffer_ui8(TRKBuffer* buffer, u8* data, int count);
DSError TRKReadBuffer_ui32(TRKBuffer* buffer, u32* data, int count);
DSError TRKReadBuffer(TRKBuffer* msg, void* data, size_t length);

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_MSGBUF_H */
