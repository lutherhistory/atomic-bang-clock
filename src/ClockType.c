#include "ClockType.h"
#include "glib.h"
#include "gtk/gtk.h"

static void update_clock_text_format(ClockType *clock);
static void update_clock_time_format(ClockType *clock);

void update_clock_text_format(ClockType *clock)
{
    if (!clock || !GTK_IS_LABEL(clock->display))
        return;

    if (clock->rate)
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
        clock->sec = 59;
        clock->min--;
    }

    if (clock->min > 59)
    {
        clock->min = 0;
        clock->hr++;
    }
    else if (clock->min < 0)
    {
        clock->min = 59;
        clock->hr--;
    }

    if (clock->hr < 0 || clock->hr > 24)
    {
        clock->hr  = 0;
        clock->min = 0;
        clock->sec = 0;
    }
}

gboolean has_finished(ClockType* clock)
{
    return !(clock->sec || clock->min || clock->hr) && clock->rate;
}

ClockType *clock_type_new(gint h, gint m, gint s)
{
    ClockType *clock = g_new(ClockType, 1);

    clock->hr  = h;
    clock->min = m;
    clock->sec = s;

    clock->rate = 0;
    clock->on_hr  = FALSE;
    clock->on_min = FALSE;
    clock->on_sec = FALSE;

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
        if (!clock->rate)
            clock->rate = -1;
        else
            clock->rate = 0;

        if (clock->rate)
        {
            gtk_button_set_icon_name(play_button, "media-playback-pause-symbolic");
            gtk_widget_add_css_class(
                GTK_WIDGET(play_button),
                "paused"
            );
        }

        else
        {
            gtk_button_set_icon_name(play_button, "media-playback-start-symbolic");
            gtk_widget_remove_css_class(
                GTK_WIDGET(play_button),
                "paused"
            );
        }
    }
}

void on_display(GtkEventController *controller, double x, double y, gpointer _p_clock_)
{
    (void) controller, (void) y;

    ClockType *clock = _p_clock_;

    if (x > 0 && x < 100)
    {
        clock->on_hr  = TRUE;
        clock->on_min = FALSE;
        clock->on_sec = FALSE;
    }

    else if (x > 100 && x < 200)
    {
        clock->on_hr  = FALSE;
        clock->on_min = TRUE;
        clock->on_sec = FALSE;
    }

    else if (x > 200 && x < 300)
    {
        clock->on_hr  = FALSE;
        clock->on_min = FALSE;
        clock->on_sec = TRUE;
    }
}

void modify_time(GtkEventController *controller, double dx, double dy, gpointer _p_clock_)
{
    (void) controller, (void) dx;

    ClockType *clock = _p_clock_;

    if (!clock || clock->rate != 0)
        return;

    if (clock->on_sec) {
        if (clock->sec > 0 && dy > 0) {
            clock->sec -= dy;
        } else if (clock->sec < 59 && dy < 0) {
            clock->sec -= dy;
        }
    }

    else if (clock->on_min) {
        if (clock->min > 0 && dy > 0) {
            clock->min -= dy;
        } else if (clock->min < 59 && dy < 0) {
            clock->min -= dy;
        }
    }

    else if (clock->on_hr) {
        if (clock->hr > 0 && dy > 0) {
            clock->hr -= dy;
        } else if (clock->hr < 24 && dy < 0) {
            clock->hr -= dy;
        }
    }

    update_clock_text_format(clock);
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
