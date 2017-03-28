/*

Display Header File

Driver << Display >> Game(State) >> Characters >> Objects

*/

#include "game.h"
#include <SDL2/SDL_ttf.h>

#define MILLISECOND_DELAY 20
#define CODE_LIMIT 9
#define ARRAY_LINE_START 2
#define ARRAY_LINE_END 7
#define Y_ARRAY_START 4
#define ARE_EQUAL(EXPECTED, PRODUCED) strcmp(EXPECTED, PRODUCED) == 0



void RenderText(Game *g);
unsigned int EventLoop(Game *g);
void Events(Game *g);
TTF_Font* SetupTTF(char *fontName, int fontSize);
void SetTextTexture(Game *g);

void DetermineBitImage(Window *win, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH], int i, int j);
void SetWinBitmapPos(Window *window, unsigned int bit_x, unsigned int bit_y);


void SetTextures(Game *g, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH], unsigned int ui_tiles[MAP_HEIGHT][MAP_WIDTH]);
void SetGameTexture(Game *g, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH]);
void SetUITexture(Game *g, unsigned int ui_tiles[MAP_HEIGHT][MAP_WIDTH]);
void SetGamePieceTextures(Game *g);


void RenderAll(Game *game);
void RenderGameViewport(Game *g);
void RenderCharacters(Game *g);
void RenderObjects(Game *g);
void RenderButtons(Game *g);
void RenderUIViewport(Game *g);


void DetermineUIBitImage(UI *u, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH], unsigned int i, unsigned int j);
void SetUIBitmapPos(UI *u, unsigned int bit_x, unsigned int bit_y);
void ClickUIButton(Game *g, Button *b, SDL_Event *e, int button_num, int viewport_x);

void IndicateNewEntry(Game *g, Button *b);
void InsertInstruction(Game *g, char *instruction_name);

void ViewportDragging(Game *g, SDL_Event *event);
void CheckForButtonClick(Game *g, SDL_Event *event);

void Reposition(unsigned int *position_x, unsigned int *position_y);
void RemoveUIButton(Game *g);
