/*

Game Header File

Driver << Display << Game(State) >> Characters >> Objects

*/

#include "characters.h"

#define GAME_WIDTH 640
#define UI_HEIGHT 480
#define UI_WIDTH 320
#define WIN_HEIGHT UI_HEIGHT
#define WIN_WIDTH GAME_WIDTH + UI_WIDTH

#define BACKGROUND_IMAGE "PathAndObjects.bmp"

/* All info required for game screen - technically this could go at the top of the dependancy list as it all comes from SDL*/
struct window {

    SDL_bool finished;
    SDL_Window *win;
    SDL_Surface *background, *screen;
    SDL_Rect source_rect, dest_rect;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Rect game_viewport;
    SDL_Rect ui_viewport;


};
typedef struct window Window;

struct ui {

    char instructions[20][20]; /*yes this is grim an we can calloc it up later on*/
    unsigned int instruction_num;

    unsigned int x, y, button_num;
    SDL_Texture *texture;
    SDL_Surface *source, *surface;
    Button *buttons; /* --> seperate the game an ui buttons for easier rendering and tracking of events etc*/
    SDL_Rect source_rect, dest_rect;
};
typedef struct ui UI;

/*Is this ok here??? --> perhaps it is best place because display is going to need to know about the game state*/
struct game {

    Window window;
    UI ui;
    Character *characters;
    Object *objects;
    Button *buttons;
    Text *text; 
    unsigned int tiles[15][20];
    unsigned int char_num, obj_num, button_num, text_num;

};
typedef struct game Game;

void CreateWindow(Window *win);
UI CreateUI(char *image, unsigned int x, unsigned int y, \
                                                   unsigned int bit_x, unsigned int bit_y);
void MakeUILayout(unsigned int map[15][20]);

void InsertNewCharacter(Game *g, Character new_c);
void InsertNewObject(Game *g, Object new_o);
void InsertNewButton(Game *g, Button new_b);

void InsertNewUIButton(Game *g, Button new_b);

unsigned int CharacterPresent(Game *g, Character new_c);
unsigned int ObjectPresent(Game *g, Object new_o);

void DestroyAndQuit(Window *win);
void FreeGame(Game *g);
void CollisionDetection(Game *g);



