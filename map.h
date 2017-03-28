/*

Map Header File

Driver << Display << Game(State) << Characters << Objects << Map

*/

#include<stdio.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "testassertions.h"

#define TILE_SIZE 32
#define MAP_HEIGHT 15
#define MAP_WIDTH 20
#define OBJECT_IMAGE "PathAndObjects.bmp"
#define BUTTON_IMAGE "scrollsandblocks.bmp"

#define OBJECT_ERROR(ERR_NUM, MESSAGE) \
        fprintf(stderr, "Error number %d --> %s.\n",\
                         ERR_NUM, MESSAGE); exit(ERR_NUM);

#define UI_ERROR(ERR_NUM, MESSAGE) \
        fprintf(stderr, "Error number %d --> %s.\n",\
                         ERR_NUM, MESSAGE); exit(ERR_NUM);

#define DISPLAY_ERROR(ERR_NUM, MESSAGE) \
        fprintf(stderr, "Error number %d --> %s.\n",\
                         ERR_NUM, MESSAGE); exit(ERR_NUM);

#define FILE_ERROR(ERR_NUM, MESSAGE) \
        fprintf(stderr, "Error number %d --> %s.\n",\
                         ERR_NUM, MESSAGE); exit(ERR_NUM);

#define FILE_OPEN_ERROR 99
#define FILE_NOT_CLOSED 200
#define FILE_READ_ERROR 9

enum bool {false, true};
typedef enum bool Bool;

/*A tile struct maybe so we can have collisions and have 'reactive' tiles
  for sounds and events
  Unsure of where to put this at the moment; maybe at the top as everything
  seems to have some dependency on whether a tile is occupied or not
*/

struct tile{

    /*unsigned int x, y;*/
    unsigned int value;
    /*Bool occupied;*/

};
typedef struct tile Tile;

/*an enumerated type to define our errors specific to the SDL related stuff*/
enum displayerrs {
          SDL_NOT_INITIALISED = 1,
          WINDOW_NOT_INITIALISED,
          NULL_WINDOW,
          NULL_ARG_TO_RENDER,
          SURFACE_NOT_INITIALISED,
          RENDERER_NOT_INITIALISED,
          COLOUR_NOT_SET
};

FILE *OpenFile(char *filename);
unsigned int CloseFile(FILE *f_ptr);

void MakeMapFromFile(FILE *f, unsigned int map[15][20]);


