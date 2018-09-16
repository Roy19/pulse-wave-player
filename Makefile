CC = gcc
CFLAGS = -g -O2 -Isrc/ $(shell pkg-config --cflags libpulse)
LDFLAGS = $(shell pkg-config --libs libpulse-simple)

SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)
OBJS = $(patsubst %.c,%.o,$(SOURCES))

PROGRAM = pulse_player

all:$(OBJS) $(PROGRAM)

$(OBJS): CFLAGS += -c

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJS)
	rm -f $(PROGRAM)