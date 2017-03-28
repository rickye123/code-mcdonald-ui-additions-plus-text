/*

Game Module - for the stored game state and building levels,
              characters, objects and buttons etc

Driver << Display << Game(State) >> Characters >> Objects

*/

#include "game.h"

UI CreateUI(char *image, unsigned int x, unsigned int y, \
                                                   unsigned int bit_x, unsigned int bit_y){
    UI u;

    u.source = SDL_LoadBMP(image);
    if(u.source == NULL){
        CHAR_ERROR(CHAR_IMAGE_ERR, "Loading of character bitmap file failed");
    }
    u.surface = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0);
    u.texture = NULL;
    u.buttons = NULL;
    u.button_num = 0;

    /*position within the bitmap*/
    u.source_rect.x = bit_x;
    u.source_rect.y = bit_y;
    u.source_rect.w = TILE_SIZE;
    u.source_rect.h = TILE_SIZE;

    u.dest_rect.x = x;
    u.dest_rect.y = y;
    u.dest_rect.w = TILE_SIZE;
    u.dest_rect.h = TILE_SIZE;


    u.instruction_num = 0;

    return u;

}

void MakeUILayout(unsigned int map[15][20]){

    unsigned int i;
    unsigned int temp[15][20] = {

{122,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,126,127},
{139,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,143,144},
{156,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,161},
{156,165,166,166,166,166,166,167,157,157,157,157,157,157,157,157,157,157,157,161},
{156,182,157,157,157,157,157,184,157,157,157,157,157,157,157,157,157,157,157,161},
{156,182,183,183,183,183,183,184,157,157,157,157,157,157,157,157,157,157,157,161},
{156,182,157,157,157,157,157,184,157,157,157,157,157,157,157,157,157,157,157,161},
{156,182,183,183,183,183,183,184,157,157,157,157,157,157,157,157,157,157,157,161},
{156,182,157,157,157,157,157,184,157,157,157,157,157,157,157,157,157,157,157,161},
{156,199,200,200,200,200,200,201,157,157,157,157,157,157,157,157,157,157,157,161},
{156,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,161},
{156,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,161},
{156,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,161},
{190,191,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,193,194,195},
{207,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,211,212}

             /*{0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5},
             {6, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11},
             {12, 13, 14, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17},
             {18, 165,166,166,166,166,166,167, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 182,187,183,187,183,187,184, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 182, 20, 21, 22, 22, 22, 184, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 182,187,183,187,183,187,184, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 182, 20, 21, 22, 22, 22, 184, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 182,187,183,187,183,187,184, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 182, 20, 21, 22, 22, 22, 184, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 199,200,200,200,200,200,201, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 19, 20, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {18, 19, 20, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23},
             {24, 25, 26, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29},
             {122, 31, 169, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35}*/

         };

    /*can't initialise a 2D array like this after declaration so copying it over*/
    for(i = 0; i < MAP_HEIGHT; i++){
        memcpy(&map[i], &temp[i], sizeof(temp[0]));
    }

    return;

}




void CreateWindow(Window *window){

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Unable to initialize SDL: ");
        SDL_Quit();
        DISPLAY_ERROR(SDL_NOT_INITIALISED, SDL_GetError())
    }

    window->win = SDL_CreateWindow(
                          "SDL Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          WIN_WIDTH, WIN_HEIGHT,
                          0
                          );

    if(window->win == NULL){
        fprintf(stderr, "Unable to initialize SDL Window: ");
        SDL_Quit();
        DISPLAY_ERROR(WINDOW_NOT_INITIALISED, SDL_GetError());
    }

    window->screen = SDL_CreateRGBSurface(0, WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0);

    if(window->screen == NULL){
        fprintf(stderr, "Unable to initialize SDL Surface: ");
        SDL_Quit();
        DISPLAY_ERROR(SURFACE_NOT_INITIALISED, SDL_GetError());
    }

    /*load the bitmap file from which we want to create our background*/
    window->background = SDL_LoadBMP(BACKGROUND_IMAGE);

    if(window->background == NULL){
        fprintf(stderr, "Unable to initialize SDL Surface: background");
        SDL_Quit();
        DISPLAY_ERROR(SURFACE_NOT_INITIALISED, SDL_GetError());
    }

    window->renderer = SDL_CreateRenderer(window->win, -1, 0 || SDL_RENDERER_ACCELERATED);

    if(window->renderer == NULL){
        fprintf(stderr, "Unable to initialize SDL Renderer: ");
        SDL_Quit();
        DISPLAY_ERROR(RENDERER_NOT_INITIALISED, SDL_GetError());
    }

    /*if(SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0){
        fprintf(stderr, "Unable to initialize SDL Draw Colour");
        SDL_Quit();
        DISPLAY_ERROR(COLOUR_NOT_SET, SDL_GetError());
    }


   if(SDL_RenderClear(window->renderer) != 0){
        fprintf(stderr, "Issue in clearing SDL Renderer");
        SDL_Quit();
        DISPLAY_ERROR(COLOUR_NOT_SET, SDL_GetError());
    }
*/



    window->finished = false;

    /*two viewports to break up the window and display the game and UI in the same window*/
    window->game_viewport.x = 0;
    window->game_viewport.y = 0;
    window->game_viewport.w = 960;
    window->game_viewport.h = 480;

    window->ui_viewport.x = 640;
    window->ui_viewport.y = 0;
    window->ui_viewport.w = 960;
    window->ui_viewport.h = 480;

    return;

}

void FreeGame(Game *g){

    unsigned int i;

    for(i = 0; i < g->char_num; i++){
        SDL_FreeSurface(g->characters[i].surface);
        SDL_DestroyTexture(g->characters[i].texture);
    }

    for(i = 0; i < g->obj_num; i++){
        SDL_FreeSurface(g->objects[i].surface);
        SDL_DestroyTexture(g->objects[i].texture);
    }

    DestroyAndQuit(&g->window);
    FreeCharacterArray(g->characters);
    FreeObjectArray(g->objects);

    return;

}

void DestroyAndQuit(Window *win){

    if(win->win == NULL){
        DISPLAY_ERROR(NULL_WINDOW, "Null window struct passed as parameter, cannot be destroyed");
    }

    SDL_DestroyWindow(win->win);
    SDL_Quit();

    return;

}

/*this will automatically create a new character array if there
is not already one present*/
void InsertNewCharacter(Game *g, Character new_c){

    if(g->char_num == 0){

        g->characters = CreateCharacterArray(++g->char_num);
        g->characters[g->char_num-1] = new_c;

        return;
    }

    if(CharacterPresent(g, new_c)){
        return;
    }

    /*otherwise we will resize the array and insert the new variable*/
    g->characters = ResizeCharacterArray(g->characters, &g->char_num);
    g->characters[g->char_num-1] = new_c;

    return;

}

/*simply don't insert the character if it already exists*/
unsigned int CharacterPresent(Game *g, Character new_c){

    unsigned int i;

    for(i = 0; i < g->char_num; i++){

        if(strcmp(new_c.name, g->characters[i].name) == 0){
            printf("Character with name %s already exists, won't be added to game", new_c.name);
            return 1;
        }
    }

    return 0;

}

void InsertNewObject(Game *g, Object new_o){

    if(g->obj_num == 0){

        g->objects = CreateObjectArray(++g->obj_num);
        g->objects[g->obj_num-1] = new_o;

        return;
    }

    /*if(ObjectPresent(g, new_o)){
        return;
    }*/

    g->objects = ResizeObjectArray(g->objects, &g->obj_num);
    g->objects[g->obj_num-1] = new_o;

    return;

}

unsigned int ObjectPresent(Game *g, Object new_o){

    unsigned int i;

    for(i = 0; i < g->obj_num; i++){

        if(strcmp(new_o.name, g->objects[i].name) == 0){
            printf("Object with name %s already exists, won't be added to game", new_o.name);
            return 1;
        }
    }

    return 0;

}

void InsertNewButton(Game *g, Button new_b){

    if(g->button_num == 0){

        g->buttons = CreateButtonArray(++g->button_num);
        g->buttons[g->button_num-1] = new_b;

        return;
    }

    /*if(ObjectPresent(g, new_b)){ we might want multiple buttons with the same name
        return;
    }*/

    g->buttons = ResizeButtonArray(g->buttons, &g->button_num);
    g->buttons[g->button_num-1] = new_b;

    return;

}

void InsertNewUIButton(Game *g, Button new_b){

    if(g->ui.button_num == 0){

        g->ui.buttons = CreateButtonArray(++g->ui.button_num);
        g->ui.buttons[g->ui.button_num-1] = new_b;

        return;
    }

    g->ui.buttons = ResizeButtonArray(g->ui.buttons, &g->ui.button_num);
    g->ui.buttons[g->ui.button_num-1] = new_b;

    return;

}

void CollisionDetection(Game *g){
  unsigned int i, xc, yc, hc, wc, xo, yo, ho, wo;

  /* current character position */
  xc = g->characters[0].dest_rect.x;
  yc = g->characters[0].dest_rect.y;
  /* character height and width */
  hc = g->characters[0].dest_rect.h;
  wc = g->characters[0].dest_rect.w;

  for(i = 0; i < g->obj_num; i++){
    /* the ith object position */ 
    xo = g->objects[i].dest_rect.x;
    yo = g->objects[i].dest_rect.y;
    /* the ith  object height and width */
    ho = g->objects[i].dest_rect.h;
    wo = g->objects[i].dest_rect.w;
  
    if((xc < (xo + wo  - 8)) && ((xc + wc - 8) > xo) && (yc < (yo + ho - 15)) && ((hc + yc - 1) > yo)){
      g->characters[0].dest_rect.x = g->characters[0].x_prev;
      g->characters[0].dest_rect.y = g->characters[0].y_prev;
    }
  }
}




