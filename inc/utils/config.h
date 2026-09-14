#ifndef CONFIG_H
#define CONFIG_H

#include "ClockType.h"

typedef struct
{
    const char *id;

    AtomicClock_type *clockType;
}

AtomicApp_conf;



#endif
