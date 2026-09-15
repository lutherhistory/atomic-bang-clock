#ifndef STYLE_MANAGER_H
#define STYLE_MANAGER_H

#include <gdk/gdk.h>

typedef struct
{
    GResource *res;
}

StyleContext;

void style_context_load_main(StyleContext *style);

#endif
