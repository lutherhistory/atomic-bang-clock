#ifndef APP_H
#define APP_H

#include <gtk/gtk.h>

typedef struct {
    const char *title;
    const char *id;
    int width;
    int hegiht;
} Config;

typedef struct {
    GtkApplication *app;
    Config config;
    int status;
} Application;



#endif
