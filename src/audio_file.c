#include <debug.h>
#include <wave_format.h>

static inline pa_sample_format_t bits_per_sample_to_pa_sample_format(int bits) {
    switch(bits){
        case 8: return PA_SAMPLE_U8;    // unsigned 8bit PCM
        case 16: return PA_SAMPLE_S16LE;    // signed 16bit little endian PCM
        case 32: return PA_SAMPLE_S32LE;    // signed 32bit little endian PCM
        default: return PA_SAMPLE_INVALID;  // invalid value
    }
}

struct audio_data *audio_file_manip(const char *filename){
    struct stat statbuff = {0,};
    struct wave_header *header = NULL;
    struct audio_data *au_data = NULL;
    int fd = -1;
    int ret = -1;
    pa_sample_format_t fmt = 0;
    uint32_t rate = 0;
    uint32_t chnls = 0;

    au_data = calloc(1, sizeof(struct audio_data));
    check(au_data != NULL, "failed to allocate memory for audio data");

    fd = open(filename, O_RDONLY);
    check(fd > 0, "failed to open the file %s", filename);

    ret = fstat(fd, &statbuff);
    check(ret == 0, "failed to get stats about file %s", filename);

    header = mmap(NULL, statbuff.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    check(header != MAP_FAILED, "failed to map %s to memory", filename);

    check(strncmp(header->id, "RIFF", 4) == 0, "%s is not a wave file", 
                    filename);

    check(header->audio_fmt == 1, "%s has audio compression within it", 
                            filename);

    chnls = header->n_channels;
    rate = header->sample_rate;
    fmt = bits_per_sample_to_pa_sample_format(header->bits_per_sample);

    au_data->h = header;
    au_data->size = statbuff.st_size;
    au_data->buff = (char *)(header + 1);
    au_data->audio_size = header->data_size;
    au_data->s = (pa_sample_spec){.format = fmt, .rate = rate, .channels = chnls};

    return au_data;

error:
    if (au_data != NULL)
        free(au_data);
    if (fd > 0)
        close(fd);
    if (header != MAP_FAILED)
        munmap(header, statbuff.st_size);

    return NULL;
}