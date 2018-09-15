#ifndef __wave_fmt_h__
#define __wave_fmt__h__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#include <sys/mman.h>

#include <debug.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <errno.h>

#define BUFSIZE 1024

struct wave_header{
    char id[4]; // contains the charaters "RIFF"
    uint8_t ignored[16]; // ignore the fmt and chunk sizes
    uint16_t audio_fmt; // PCM = 1, others denote some kind of compression
    uint16_t n_channels;    // 1 = Mono, 2 = Stereo
    uint32_t sample_rate; // 8K or 44.1K no of samples
    uint32_t byte_rate; // == sample_rate * n_channels * no of bits / 8
    uint16_t block_align;   // no of bytes for 1 sample (for all channels)
    uint16_t bits_per_sample;   // == 8bits, 16bits etc
    char ignored2[4];   // contains the words "data"
    uint32_t data_size; // the actual data size
}__attribute__((packed, aligned(1)));

struct audio_data{
    struct wave_header *h;  // the appropriate header for the wave file
    size_t size;        // size of the entire file
    
    char *buff;         // pointer to the raw audio data
    uint32_t audio_size;    // size of the data
    pa_sample_spec s;   //  pulse_audio sample specification
};

struct audio_data *audio_file_manip(const char *filename);

#endif