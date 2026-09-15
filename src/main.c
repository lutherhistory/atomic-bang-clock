#include "core/app.h"
#include "core/main_window.h"
#include "core/style_context.h"

#include <glib.h>
#include <gtk/gtk.h>

static void on_startup(GtkApplication *app, gpointer _config_)
{
    AtomicApp *config = _config_;


    style_context_load_main(config->style);

   /// `on_startup()` logs
   g_message("Successful Startup");
}

static void on_activate(GtkApplication *app, gpointer _config_)
{
    AtomicApp *config = _config_;

    config->window = main_window_new(app);
    main_window_show(config->window);

    /// `on_activate()` logs
    g_message("Successful Activated");
}

static void on_shutdown(GtkApplication *app, gpointer _config_)
{
    AtomicApp *config = _config_;

    style_context_free(&config->style);
    main_window_free(&config->window);

    /// `on_shutdown()` logs
    if (config->window == NULL)
        g_message("Successful Quit");

    else {
        g_error("Failed to release!");
    }
}

int main(int argc, char **argv)
{
    AtomicApp config;
    GtkApplication *app = gtk_application_new(
        "io.github.lutherhistory.atomic-bang-clock",
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(
        G_APPLICATION(app),
        "startup",
        G_CALLBACK(on_startup),
        &config
    );

    g_signal_connect(
        G_APPLICATION(app),
        "activate",
        G_CALLBACK(on_activate),
        &config
    );

    g_signal_connect(
        G_APPLICATION(app),
        "shutdown",
        G_CALLBACK(on_shutdown),
        &config
    );

    int status = g_application_run(
        G_APPLICATION(app),
        argc,
        argv
    );

    g_object_unref(app);

    return status;
}
