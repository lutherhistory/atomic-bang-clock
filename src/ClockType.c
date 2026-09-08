#include "ClockType.h"
#include "glib.h"
#include "gtk/gtk.h"

static void update_clock_text_format(ClockType *clock);
static void update_clock_time_format(ClockType *clock);

void update_clock_text_format(ClockType *clock)
{
    if (!clock || !GTK_IS_LABEL(clock->display)) {
        return;
    }
    update_clock_time_format(clock);
    gchar *text = g_strdup_printf(
        "%02d:%02d:%02d",
        clock->hr,
        clock->min,
        clock->sec
    );
    gtk_label_set_label(GTK_LABEL(clock->display), text);

    g_free(text);
}

void update_clock_time_format(ClockType *clock)
{
    if (!clock) {
        return;
    }

    if (clock->sec > 59)
    {
        clock->sec = 0;
        clock->min++;
    }
    else if (clock->sec < 0)
    {
        clock->sec = 0;
        clock->min--;
    }

    if (clock->min > 59)
    {
        clock->min = 0;
        clock->hr++;
    }
    else if (clock->min < 0)
    {
        clock->min = 0;
        clock->hr--;
    }

    if (clock->hr < 0 || clock->hr > 23)
    {
        clock->hr = 0;
        clock->min = 0;
        clock->sec = 0;
    }
}

ClockType *clock_type_new(gint h, gint m, gint s)
{
    ClockType *clock = g_new(ClockType, 1);

    clock->hr  = h;
    clock->min = m;
    clock->sec = s;
    clock->rate = 0;

    clock->display = NULL;

    return clock;
}

void clock_type_free(ClockType **_clock_)
{
    if (_clock_ && *_clock_) {
        g_free(*_clock_);
        *_clock_ = NULL;
    }
}

GtkWidget *clock_type_get_display(ClockType *clock)
{
    clock->display = gtk_label_new("");
    gtk_widget_add_css_class(clock->display, "ClockType-label");

    update_clock_text_format(clock);

    return clock->display;
}

void clock_type_start(GtkButton *play_button, gpointer _p_clock_)
{
    ClockType *clock = _p_clock_;

    if (clock && play_button) {
        clock->rate = !clock->rate;

        if (clock->rate)
        {
            gtk_button_set_label(play_button, "Pause");
            gtk_widget_add_css_class(
                GTK_WIDGET(play_button),
                "paused"
            );
        }

        else
        {
            gtk_button_set_label(play_button, "Play");
            gtk_widget_remove_css_class(
                GTK_WIDGET(play_button),
                "paused"
            );
        }
    }
}

gboolean update_time(gpointer _p_clock_)
{
    ClockType *clock = _p_clock_;

    if (clock) {
        clock->sec += clock->rate;
        update_clock_text_format(clock);

        return G_SOURCE_CONTINUE;
    }

    return G_SOURCE_REMOVE;
}
