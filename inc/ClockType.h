#ifndef CLOCKTYPE_H
#define CLOCKTYPE_H

#include "glib.h"
#include <gtk/gtk.h>

typedef struct ClockType
{
    gint hr;
    gint min;
    gint sec;

    gint rate;
    gboolean on_sec;
    gboolean on_min;
    gboolean on_hr;

    GtkWidget *display;
} ClockType;

ClockType *clock_type_new(gint h, gint m, gint s);

void clock_type_free(ClockType **_p_clock_);

GtkWidget *clock_type_get_display(ClockType *clock);

void clock_type_start(GtkButton *play_button, gpointer _p_clock_);

void on_display(GtkEventController *controller, double x, double y, gpointer _p_clock_);

void modify_time(GtkEventController *controller, double dx, double dy, gpointer _p_clock_);

gboolean update_time(gpointer _p_clock_);

#endif
