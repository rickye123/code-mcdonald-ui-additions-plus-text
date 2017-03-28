CC = gcc
CFLAGS = `pkg-config sdl2 --cflags` -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm -g
OBS = ob_test
CHARS = char_test
DISPLAY = display_test
COB = c_o_b_test
INCLUDES = ../objects.h ../characters.h ../display.h ../game.h ../testassertions.h
SOURCES = ../objects.c ../characters.c ../display.c ../game.c
LIBS =  `pkg-config sdl2 --libs`

.PHONY: $(OBS) $(CHARS)	$(DISPLAY) $(COB)

all: $(OBS) $(CHARS) $(DISPLAY) $(COB)

$(OBS):	$(SOURCES) $(INCLUDES)
	$(CC) $(SOURCES) $(OBS).c -o $(OBS) $(CFLAGS) $(LIBS)

$(CHARS):	$(SOURCES) $(INCLUDES)
	$(CC) $(SOURCES) $(CHARS).c -o $(CHARS) $(CFLAGS) $(LIBS)

$(DISPLAY):	$(SOURCES) $(INCLUDES)
	$(CC) $(SOURCES) $(DISPLAY).c -o $(DISPLAY) $(CFLAGS) $(LIBS)

$(COB):	$(SOURCES) $(INCLUDES)
	$(CC) $(SOURCES) $(COB).c -o $(COB) $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBS) $(CHARS) $(DISPLAY)

run: all
	./$(OBS)
	./$(CHARS)
	./$(DISPLAY)
	./$(COB)

