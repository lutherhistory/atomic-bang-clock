#ifndef CLOCKTYPE_H
#define CLOCKTYPE_H

#include "glib.h"
#include <gtk/gtk.h>

typedef struct
{
    gint h;
    gint m;
    gint s;
    gchar *text;

    GtkWidget *label;
} ClockType;

ClockType *clock_type_new(int h, int m, int s);

GtkWidget *clock_type_new_dial(gchar *text);

GtkWidget *clock_type_new_play_button(void);

void clock_type_free(ClockType *thisClock);

gboolean update_time(gpointer _clockData_);

gboolean on_close_request(ClockType **clock);

#endif
