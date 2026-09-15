#include "core/main_window.h"
#include "gtk/gtk.h"

MainWindow * main_window_new(GtkApplication *app)
{
    MainWindow *window = g_new(MainWindow, 1);

    window->m_window = gtk_application_window_new(app);
    window->m_title  = "Atomic Bang Clock";
    window->m_width  = 800;
    window->m_height = 500;

    return window;
}

void main_window_free(MainWindow ** window)
{
    if (*window) {
        g_free(*window);
        *window = NULL;
    }
}

void main_window_show(MainWindow *window)
{
    gtk_window_set_default_size(GTK_WINDOW(window->m_window), window->m_width, window->m_height);
    gtk_window_set_title(GTK_WINDOW(window->m_window), window->m_title);

    gtk_window_present(GTK_WINDOW(window->m_window));
}
