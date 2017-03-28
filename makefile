CC = gcc
CFLAGS = `pkg-config sdl2 --cflags` -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm -lSDL2_ttf -g
TARGET = driver
INCLUDES = game.h characters.h display.h game.h objects.h map.h
SOURCES = characters.c display.c game.c objects.c map.c $(TARGET).c
LIBS =  `pkg-config sdl2 --libs`

all:	$(TARGET)
	
$(TARGET):	$(SOURCES) $(INCLUDES)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)

