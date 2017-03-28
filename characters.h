/*

Characters Header File

Driver << Display << Game(State) << Characters >> Objects

*/

#include "objects.h"
#include "string.h"

#define MOVE_AMOUNT 4
#define X_START 150
#define Y_START 150
#define SPRITE_IMAGE "sprite.bmp"
#define CHAR_ERROR(ERR_NUM, MESSAGE) \
        fprintf(stderr, "Error number %d --> %s.\n",\
                         ERR_NUM, MESSAGE); exit(ERR_NUM);

struct character{

    char *name; /*added a name so we can find them inside the game struct later on*/
    unsigned int x_coord, y_coord, x_prev, y_prev;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect source_rect, dest_rect;

};
typedef struct character Character;


enum charerrs {
          CHAR_IMAGE_ERR = 1,
          ALLOCATION_ERROR
};

void InitChar(Character *c);
Character CreateCharacter(char *name, char *image, unsigned int x, unsigned int y, \
                                                   unsigned int bit_x, unsigned int bit_y);
void CharacterEvents(Character *c);
void MoveAndAnimateRight(Character *c);
void MoveAndAnimateDown(Character *c);
void MoveAndAnimateUp(Character *c);
void MoveAndAnimateLeft(Character *c);


void FreeCharacterArray(Character *c);

void CopyCharacterArray(Character *dest, Character *src, unsigned int size);
Character *ResizeCharacterArray(Character *c, unsigned int *size);
Character *CreateCharacterArray(unsigned int size);

