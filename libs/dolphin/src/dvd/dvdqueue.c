#include "dolphin/DVDPriv.h"

#define MAX_QUEUES 4
typedef struct {
	DVDCommandBlock* next;
	DVDCommandBlock* prev;
} DVDQueue;

static DVDQueue WaitingQueue[MAX_QUEUES];

void __DVDClearWaitingQueue(void) {
	u32 i;

	for (i = 0; i < MAX_QUEUES; i++) {
		DVDCommandBlock* q;

		q = (DVDCommandBlock*)&(WaitingQueue[i]);
		q->next = q;
		q->prev = q;
	}
}

BOOL __DVDPushWaitingQueue(s32 prio, DVDCommandBlock* block) {
	BOOL enabled;
	DVDCommandBlock* q;

	enabled = OSDisableInterrupts();

	q = (DVDCommandBlock*)&(WaitingQueue[prio]);

	q->prev->next = block;
	block->prev = q->prev;
	block->next = q;
	q->prev = block;

	OSRestoreInterrupts(enabled);

	return TRUE;
}

static DVDCommandBlock* PopWaitingQueuePrio(s32 prio) {
	DVDCommandBlock* tmp;
	BOOL enabled;
	DVDCommandBlock* q;

	enabled = OSDisableInterrupts();

	q = (DVDCommandBlock*)&(WaitingQueue[prio]);

	tmp = q->next;
	q->next = tmp->next;
	tmp->next->prev = q;

	OSRestoreInterrupts(enabled);

	tmp->next = (DVDCommandBlock*)NULL;
	tmp->prev = (DVDCommandBlock*)NULL;

	return tmp;
}

DVDCommandBlock* __DVDPopWaitingQueue(void) {
	u32 i;
	BOOL enabled;
	DVDCommandBlock* q;

	enabled = OSDisableInterrupts();

	for (i = 0; i < MAX_QUEUES; i++) {
		q = (DVDCommandBlock*)&(WaitingQueue[i]);
		if (q->next != q) {
			OSRestoreInterrupts(enabled);
			return PopWaitingQueuePrio((s32)i);
		}
	}

	OSRestoreInterrupts(enabled);

	return (DVDCommandBlock*)NULL;
}

BOOL __DVDCheckWaitingQueue(void) {
	u32 i;
	BOOL enabled;
	DVDCommandBlock* q;

	enabled = OSDisableInterrupts();

	for (i = 0; i < MAX_QUEUES; i++) {
		q = (DVDCommandBlock*)&(WaitingQueue[i]);
		if (q->next != q) {
			OSRestoreInterrupts(enabled);
			return TRUE;
		}
	}

	OSRestoreInterrupts(enabled);

	return FALSE;
}

BOOL __DVDDequeueWaitingQueue(DVDCommandBlock* block) {
	BOOL enabled;
	DVDCommandBlock* prev;
	DVDCommandBlock* next;

	enabled = OSDisableInterrupts();

	prev = block->prev;
	next = block->next;

	if ((prev == (DVDCommandBlock*)NULL) || (next == (DVDCommandBlock*)NULL)) {
		OSRestoreInterrupts(enabled);
		return FALSE;
	}

	prev->next = next;
	next->prev = prev;

	OSRestoreInterrupts(enabled);

	return TRUE;
}

BOOL __DVDIsBlockInWaitingQueue(DVDCommandBlock* block) {
	u32 i;
	DVDCommandBlock* start;
	DVDCommandBlock* q;

	for (i = 0; i < MAX_QUEUES; i++) {
		start = (DVDCommandBlock*)&(WaitingQueue[i]);

		if (start->next != start) {
			for (q = start->next; q != start; q = q->next) {
				if (q == block)
					return TRUE;
			}
		}
	}

	return FALSE;
}