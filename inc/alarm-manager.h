#ifndef ALARM_MAANGER_H
#define ALARM_MAANGER_H

#include "ClockType.h"
#include "audio-player.h"

typedef struct
{
    AudioManager    *audioManager;
    ClockType       *clockType;
    gboolean        start;
} AlarmManager;

#endif
