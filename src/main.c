#include <gtk/gtk.h>

#include "ClockType.h"
#include "glib-object.h"
#include "glib.h"

#define STYLE_PATH THIS_PATH "/styles"

typedef struct Config Config;
typedef struct ClockType ClockType;


typedef struct Config
{
    gint width;
    gint height;
    const gchar *title;

    ClockType *myClock;
} Config;

/// Widget allocations
static GtkWindow *create_window(GtkWidget *window, Config *config)
{
    gtk_window_set_default_size(
        GTK_WINDOW(window),
        config->width,
        config->height
    );
    gtk_window_set_title(GTK_WINDOW(window), config->title);

    return GTK_WINDOW(window);
}

static GtkBox *create_container(GtkWindow *window, GtkBox *layout1, GtkBox *layout2)
{
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(container, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(container, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(container), GTK_WIDGET(layout1));
    gtk_box_append(GTK_BOX(container), GTK_WIDGET(layout2));

    gtk_window_set_child(window, GTK_WIDGET(container));

    return GTK_BOX(container);
}

static GtkBox *create_dialLayout(ClockType **clock)
{
    GtkWidget *layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(layout, GTK_ALIGN_CENTER);

    GtkWidget *label = clock_type_get_display(*clock);
    gtk_widget_add_css_class(layout, "ClockType-label");

    GtkEventController *scroll = gtk_event_controller_scroll_new(
        GTK_EVENT_CONTROLLER_SCROLL_VERTICAL
    );
    g_signal_connect(
        scroll,
        "scroll",
        G_CALLBACK(modify_time),
        *clock
    );

    GtkEventController *motion = gtk_event_controller_motion_new();
    g_signal_connect(
        motion,
        "motion",
        G_CALLBACK(on_display),
        *clock
    );

    gtk_widget_add_controller(label, scroll);
    gtk_widget_add_controller(label, motion);
    gtk_box_append(GTK_BOX(layout), label);

    return GTK_BOX(layout);
}

static GtkBox *create_btnsLayout(ClockType **clock)
{
    GtkWidget *layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(layout, GTK_ALIGN_CENTER);

    GtkWidget *play_btn = gtk_button_new_with_label("Play");
    gtk_widget_add_css_class(play_btn, "ClockType-play");
    gtk_box_append(GTK_BOX(layout), play_btn);

    g_signal_connect(
        play_btn,
        "clicked",
        G_CALLBACK(clock_type_start),
        *clock
    );

    return GTK_BOX(layout);
}

/// Application Callback
static void load_css(GtkApplication *app, gpointer _config_)
{
    (void) app, (void) _config_;

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(
        provider,
        STYLE_PATH "/main.css"
    );
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}

static void on_activate(GtkApplication *app, gpointer _config_)
{
    Config      *config = _config_;
    GtkWindow   *window     = create_window(gtk_application_window_new(app), _config_);
    GtkBox      *dialLayout = create_dialLayout(&config->myClock);
    GtkBox      *btnsLayout = create_btnsLayout(&config->myClock);

    create_container(window, dialLayout, btnsLayout);

    g_timeout_add(
        1000,
        update_time,
        config->myClock
    );

    gtk_window_present(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new(
        "io.github.lutherhistory.atomic-bang-clock",
        G_APPLICATION_DEFAULT_FLAGS
    );
    Config config = {
        .width  = 800,
        .height = 500,
        .title  = "Atomic Bang Clock",

        .myClock = clock_type_new(0, 0, 0)
    };

    g_signal_connect(
        app,
        "startup",
        G_CALLBACK(load_css),
        NULL
    );

    g_signal_connect(
        app,
        "activate",
        G_CALLBACK(on_activate),
        &config
    );

    int status = g_application_run(
        G_APPLICATION(app),
        argc,
        argv
    );

    clock_type_free(&config.myClock);
    g_object_unref(app);
    return status;
}
