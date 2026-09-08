#include "ClockType.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"
#include <glib.h>

void update_clock(ClockType *thisClock)
{
    thisClock->text = g_strdup_printf(
        "%02d:%02d:%02d",
        thisClock->h,
        thisClock->m,
        thisClock->s
    );

    gtk_label_set_label(GTK_LABEL(thisClock->label), thisClock->text);
    g_free(thisClock->text);
}

ClockType *clock_type_new(int h, int m, int s)
{
    ClockType *thisClock = g_new(ClockType, 1);

    thisClock->h = h;
    thisClock->m = m;
    thisClock->s = s;

    thisClock->label = gtk_label_new("");
    update_clock(thisClock);

    return thisClock;
}

GtkWidget *clock_type_new_dial(gchar *text)
{
    GtkWidget *dial = gtk_label_new(text);

    gtk_widget_add_css_class(dial, "ClockType-label");
    gtk_widget_set_halign(dial, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(dial, GTK_ALIGN_CENTER);

    return dial;
}

GtkWidget *clock_type_new_play_button(void)
{
    GtkWidget *btn = gtk_button_new_with_label("Play");

    gtk_widget_add_css_class(btn, "ClockType-play");
    gtk_widget_set_halign(btn, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(btn, GTK_ALIGN_END);

    return btn;
}

void clock_type_free(ClockType *thisClock)
{
    if (thisClock) {
        g_free(thisClock);
    }
}

gboolean update_time(gpointer _clockData_)
{
    ClockType *clockData = _clockData_;

    if (clockData) {
        clockData->s += 1;

        update_clock(_clockData_);
        return G_SOURCE_CONTINUE;
    }

    return G_SOURCE_REMOVE;
}

gboolean on_close_request(ClockType **clock)
{
    clock_type_free(*clock);
    *clock = NULL;
    g_message("ClockType has cleaned up");

    return FALSE;
}
