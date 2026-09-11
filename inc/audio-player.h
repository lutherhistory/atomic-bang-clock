#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <gst/gst.h>

typedef struct
{
    gchar *uri;

    GstElement  *player;
    GstBus      *bus;
    GstMessage  *msg;
} AudioManager;

AudioManager *audio_player_new(const char* file_name);

void audio_player_start_playing(AudioManager *manager);

void audio_player_unref(AudioManager **manager);

#endif
