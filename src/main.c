// #include "ClockType.h"
#include "ClockType.h"
#include "glib-object.h"
#include "gtk/gtkshortcut.h"
#include <glib.h>
#include <gtk/gtk.h>

#define STYLE_PATH THIS_PATH "/styles"

typedef struct
{
    const char *title;
    int width;
    int height;

    ClockType *clock;
} Config;

typedef struct
{
    GtkWidget *mainLayout;
    GtkWidget *dialLayout;
    GtkWidget *btnsLayout;
} Container;

/// --- Container Contents ---
// ...

/// --- Widgets Contents ---
GtkWidget *create_window(GtkApplication *app, gpointer _config_, Container *container)
{
    GtkWidget   *window = gtk_application_window_new(app);
    Config      *config = _config_;

    // Child & Styles
    gtk_window_set_default_size(GTK_WINDOW(window), config->width, config->height);
    gtk_window_set_title(GTK_WINDOW(window), config->title);
    gtk_box_append(GTK_BOX(container->mainLayout), container->dialLayout);
    gtk_box_append(GTK_BOX(container->mainLayout), container->btnsLayout);

    // Positioning
    gtk_widget_set_halign(container->mainLayout, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(container->mainLayout, GTK_ALIGN_CENTER);

    gtk_widget_set_halign(container->btnsLayout, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(container->btnsLayout, GTK_ALIGN_END);

    gtk_window_set_child(GTK_WINDOW(window), container->mainLayout);

    return window;
}

/// --- Application Contents ---
static void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(provider, STYLE_PATH "/main.css");
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}

static void on_activate(GtkApplication *app, gpointer _config_)
{
    // Containers
    Container   container = {
        .mainLayout = gtk_box_new(GTK_ORIENTATION_VERTICAL,   0),
        .dialLayout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0),
        .btnsLayout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0)
    };

    // Widgets
    ClockType   *myClock    = clock_type_new(0, 0, 7);
    GtkWidget   *window     = create_window(app, _config_, &container);

    GtkWidget   *label      = myClock->label;
    GtkWidget   *btn        = gtk_button_new_with_label("Play");

    // Imply Widgets
    gtk_widget_add_css_class(label, "ClockType-label");
    gtk_box_append(GTK_BOX(container.dialLayout), label);

    gtk_widget_add_css_class(btn, "ClockType-play");
    gtk_box_append(GTK_BOX(container.btnsLayout), btn);

    gtk_window_present(GTK_WINDOW(window));

    // Tasks
    g_timeout_add(
        1000,
        update_time,
        myClock
    );
}

int main(int argc, char **argv)
{
    GtkApplication *app = gtk_application_new(
        "io.github.lutherhistory.atomic-bang-clock",
        G_APPLICATION_DEFAULT_FLAGS
    );
    Config config = {
        .title  = "Atomic Bang Clock",
        .width  = 800,
        .height = 500,
        .clock  = clock_type_new(0, 0, 7)
    };
    int status;

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

    status = g_application_run(
        G_APPLICATION(app),
        argc,
        argv
    );

    g_object_unref(app);
    return status;
}
