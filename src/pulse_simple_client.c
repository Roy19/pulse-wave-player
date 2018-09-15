#include <debug.h>
#include <wave_format.h>

void free_audio_data(struct audio_data *au_data) {
    check(au_data != NULL, "invalid audio data.");

    // unmap the header from memory
    if (au_data->h)
        munmap(au_data->h, au_data->size);
    // unmap the buffer if available 
    if (au_data->buff)
        munmap(au_data->buff, au_data->audio_size);

    // free the data
    free(au_data);

error:
    return;
}

int main(int argc, char*argv[]) {
    pa_simple *s = NULL;
    int ret = 1;
    int error;

    if (argc <= 1){
        fprintf(stderr, "USAGE: %s <wave_file>", argv[0]);
        exit(1);
    }
    /* Get the audiofile data*/
    struct audio_data *au = audio_file_manip(argv[1]);
    check(au != NULL, "failed to parse wave file data");

    /* Create a new playback stream */
    if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &(au->s), NULL, NULL, &error))) {
        log_err("pa_simple_new() failed: %s", pa_strerror(error));
        goto error;
    }
    log_info("connection of pulseaudio server established");
#if 0
        pa_usec_t latency;
        if ((latency = pa_simple_get_latency(s, &error)) == (pa_usec_t) -1) {
            fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        fprintf(stderr, "%0.0f usec    \r", (float)latency);
#endif
        /* play it */
    log_info("playing wave file %s", argv[1]);
    if (pa_simple_write(s, au->buff, (size_t) au->audio_size, &error) < 0) {
        log_err("pa_simple_write() failed: %s\n", pa_strerror(error));
        goto error;
    }
    /* Make sure that every single sample was played */
    log_info("draining playback stream");
    if (pa_simple_drain(s, &error) < 0) {
        log_err("pa_simple_drain() failed: %s\n", pa_strerror(error));
        goto error;
    }
    log_info("playback stream fully drained");
    
    ret = 0;

error:  // fall through
    if (s)
        pa_simple_free(s);
    free_audio_data(au);

    return ret;
}
