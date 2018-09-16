# pulse-wave-player
Reads a wave file and plays it using PulseAudio daemon.
Uses the PulseAudio SimpleAPI.

## Required Dependencies
* [pkg-config] (https://www.freedesktop.org/wiki/Software/pkg-config/)
* [PulseAudio daemon] (https://www.freedesktop.org/wiki/Software/PulseAudio/)
* [PulseAudio SimpleAPI] (https://freedesktop.org/software/pulseaudio/doxygen/)

## TODO features
* [ ] Fix some memory leaks reported by Valgrind.
* [ ] Have protect against 0 sized wave files. 
* [ ] Make the same stuff using PulseAudio AsynchornousAPI.
* [ ] Use Gstreamer do do the same.
