#ifndef _DOLPHIN_OSALARM
#define _DOLPHIN_OSALARM

#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm {
  OSAlarmHandler handler;
  u32 tag;
  OSTime fire;
  OSAlarm* prev;
  OSAlarm* next;
  OSTime period;
  OSTime start;
};

void OSInitAlarm(void);
void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler);
void OSSetAlarmTag(OSAlarm* alarm, u32 tag);
void OSSetAbsAlarm(OSAlarm* alarm, OSTime time, OSAlarmHandler handler);
void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler);
void OSCreateAlarm(OSAlarm* alarm);
void OSCancelAlarm(OSAlarm* alarm);
void OSCancelAlarms(u32 tag);

BOOL OSCheckAlarmQueue(void);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSALARM
