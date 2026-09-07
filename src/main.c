#include <glib.h>
#include <gtk/gtk.h>

#define STYLE_PATH THIS_PATH "/styles"

typedef struct {
    const char *title;
    int width;
    int height;
} Config;

static void load_css(GtkApplication *app, gpointer user_data) {
    (void) app, (void) user_data;

    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(provider, STYLE_PATH "/main.css");
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}

static void on_activate(GtkApplication *app, gpointer _config_) {
    Config *config = _config_;

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), config->width, config->height);
    gtk_window_set_title(GTK_WINDOW(window), config->title);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget *label = gtk_label_new("00:00:00");
    gtk_widget_add_css_class(label, "clock-dial");

    GTimer *timer = g_timer_new();

    gdouble elapsed = g_timer_elapsed(timer, NULL);
    g_print("Elasped: %f secounds", elapsed);

    g_timer_destroy(timer);

    gtk_box_append(GTK_BOX(box), label);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    Config config = {
        .title  = "Atomic Bang Clock",
        .width  = 800,
        .height = 500
    };

    app = gtk_application_new(
        "io.github.lutherhistory.atomic-bang-clock",
        G_APPLICATION_DEFAULT_FLAGS
    );

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
