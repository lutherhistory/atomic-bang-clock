#include "core/style_context.h"
#include "managers/style_manager.h"
#include "utils/resources.h"

#include <gdk/gdk.h>
#include <gtk/gtk.h>

void style_context_load_main(StyleContext *style)
{
    GtkCssProvider  *provider = gtk_css_provider_new();
    GdkDisplay      *display  = gdk_display_get_default();

    gtk_css_provider_load_from_resource(
        provider,
        RES("/styles/main.css")
    );
    gtk_style_context_add_provider_for_display(
        display,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(provider);
}
