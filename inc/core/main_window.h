#ifndef WIDNOW_MANAGER_H
#define WIDNOW_MANAGER_H

#include <gtk/gtk.h>

typedef struct
{
    const char *m_title;
    gint m_width;
    gint m_height;

    GtkWidget *m_window;
}

MainWindow;

MainWindow * main_window_new(GtkApplication *app);

void main_window_free(MainWindow ** window);

void main_window_show(MainWindow *window);

#endif
