#include "audio-player.h"

#define AUDIO_PATH THIS_PATH "/audios"

AudioManager *audio_player_new(const char* file_name)
{
    AudioManager *manager = g_new(AudioManager, 1);

    if (!(manager->player = gst_element_factory_make("playbin", "player"))) {
        g_printerr("Failed to create playbin\n");
        g_free(manager);
        return NULL;
    }

    manager->uri = g_strdup_printf("file://%s/%s", AUDIO_PATH, file_name);
    g_object_set(
        manager->player,
        "uri",
        manager->uri,
        NULL
    );

    manager->bus = gst_element_get_bus(manager->player);

    gst_element_set_state(
        manager->player,
        GST_STATE_PAUSED
    );

    return manager;
}

void audio_player_start_playing(AudioManager *manager)
{
    gst_element_set_state(
        manager->player,
        GST_STATE_PLAYING
    );

    manager->msg = gst_bus_timed_pop_filtered(
        manager->bus,
        GST_CLOCK_TIME_NONE,
        GST_MESSAGE_ERROR | GST_MESSAGE_EOS
    );

    if (manager->msg) {
        switch (GST_MESSAGE_TYPE(manager->msg)) {
            case GST_MESSAGE_ERROR: {
                GError *err = NULL;
                gchar *debug = NULL;

                gst_message_parse_error(manager->msg, &err, &debug);

                g_printerr("Error: %s\n", err->message);

                g_clear_error(&err);
                g_free(debug);
                break;
            }

            case GST_MESSAGE_EOS:
                g_print("Playback finished.\n");
                break;

            default:
                break;
            }
        gst_message_unref(manager->msg);
        manager->msg = NULL;
    }

    gst_element_set_state(
        manager->player,
        GST_STATE_PAUSED
    );
}

void audio_player_unref(AudioManager **manager)
{
    if (!manager || !*manager)
        return;

    if ((*manager)->bus)
        gst_object_unref((*manager)->bus);

    if ((*manager)->player)
        gst_object_unref((*manager)->player);

    if ((*manager)->uri)
        g_free((*manager)->uri);

    g_free(*manager);
    *manager = NULL;
}
