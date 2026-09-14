#ifndef WIDNOW_MANAGER_H
#define WIDNOW_MANAGER_H

#include <gtk/gtk.h>

GtkWindow *atomic_window_new(GtkApplication *app, gpointer _config_);

#endif
