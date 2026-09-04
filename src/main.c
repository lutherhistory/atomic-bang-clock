#include <gtk/gtk.h>

typedef struct AppConfig AppConfig;

struct AppConfig
{
    const char *title;
    const char *id;
    int width;
    int height;
};

static void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(
        provider,
        "./http/style.css"
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}

static void on_activate(GtkApplication *app, gpointer __config) 
{
    AppConfig *config = __config;


    // Window
    GtkWidget *window = gtk_application_window_new(app);

    // Layout
    GtkWidget *box    = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        10
    );

    gtk_window_set_title(
        GTK_WINDOW(window), 
        config->title
    );
    gtk_window_set_default_size(
        GTK_WINDOW(window), 
        config->width, 
        config->height
    );

    gtk_window_set_child(GTK_WINDOW(window), box);


    // `Clock` Dial
    GtkWidget *dial = gtk_label_new("00:00:00");

    gtk_widget_add_css_class(
        dial,
        "clock-dial"
    );

    gtk_widget_set_halign(
        dial,
        GTK_ALIGN_CENTER
    );

    gtk_widget_set_valign(
        dial,
        GTK_ALIGN_CENTER
    );
    gtk_widget_set_vexpand(dial, TRUE);

    gtk_box_append(GTK_BOX(box), dial);

    // `Button` play button
    GtkWidget *button = gtk_button_new_with_label("▶");

    gtk_widget_add_css_class(
        button,
        "clock-play"
    );

    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);


    gtk_box_append(GTK_BOX(box), button);

    // Window shows up
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) 
{
    GtkApplication *app;
    int status;

    /// Application Setup...
    AppConfig config  = {
        .title  = "Atomi Bang Clock",
        .id     = "io.github.lutherhistory.atomic-bang-clock",
        .width  = 800,
        .height = 500
    };

    app = gtk_application_new(
        config.id,
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(
        app,
        "startup",
        G_CALLBACK(load_css),
        NULL
    );

    g_signal_connect(
        G_APPLICATION(app),
        "activate",
        G_CALLBACK(on_activate),
        &config
    );

    /// Application Loop...
    status = g_application_run(
        G_APPLICATION(app),
        argc,
        argv
    );

    /// Free up Memories...
    g_object_unref(app);
    return status;
}