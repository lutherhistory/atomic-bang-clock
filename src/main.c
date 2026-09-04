#include <gtk/gtk.h>

typedef struct AppConfig {

    const char* title;
    const char* app_id;
    int width;
    int height;

} AppConfig;

static void load_css(GtkApplication* app, gpointer src) {
    (void) app;

    GFile *style_src = src;

    GtkCssProvider  *provider = gtk_css_provider_new();
    GdkDisplay      *display = gdk_display_get_default();

    gtk_css_provider_load_from_file(
        provider, 
        style_src
    );
    gtk_style_context_add_provider_for_display(
        display, 
        GTK_STYLE_PROVIDER(provider), 
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}

static void on_activate(GtkApplication *app, gpointer user_data) {
    AppConfig* config = user_data;

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), config->title);    
    gtk_window_set_default_size(GTK_WINDOW(window), config->width, config->height);
    
    GtkWidget *title  = gtk_label_new("00:00:00");
    gtk_window_set_child(GTK_WINDOW(window), title);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char** argv) {
    GtkApplication *app;
    AppConfig config = {
        .title  = "Atomic Bang Clock",
        .app_id = "io.github.lutherhistory.atom-clock",
        .width  = 800,
        .height = 500
    };
    GFile *style_src = g_file_new_for_path("./http/style.css");
    int status;

    app = gtk_application_new(
        config.app_id, 
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(
        app, 
        "startup", 
        G_CALLBACK(load_css), 
        style_src
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

    g_object_unref(style_src);
    g_object_unref(app);

    return status;
}