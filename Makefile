CC = gcc
CFLAGS = -g -O2 -Isrc/ $(shell pkg-config --cflags libpulse)
LDFLAGS = $(shell pkg-config --libs libpulse-simple libpulse)

SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)

PROGRAM = pulse_player

all:$(PROGRAM)

$(PROGRAM):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)