/*

Objects Header File

Driver << Display << Game(State) << Characters << Objects

*/

#include "map.h"

struct object{

    char *name;
    SDL_Surface *surface;
    SDL_Rect source_rect, dest_rect;
    SDL_Texture *texture;
};
typedef struct object Object;

struct text{

    char *name;
    TTF_Font *font; 
    SDL_Surface *surface;
    SDL_Rect source_rect, dest_rect;
    SDL_Texture *texture;
};
typedef struct text Text;

struct button{

    char *name;
    Bool dragging;
    SDL_Surface *surface;
    SDL_Rect source_rect, dest_rect;
    SDL_Texture *texture;

};
typedef struct button Button;

/*object error enum type*/
enum objecterrs {
          OBJECT_IMAGE_ERR = 1,
          OBJ_ALLOC_ERROR
};

/*enumerated type for interface errors*/
enum uierrs {
          BUTTON_IMAGE_ERR = 1,
          BUTTON_ALLOC_ERROR
};

Object CreateObject(char *name, char *image, unsigned int x, unsigned int y, \
                                             unsigned int bit_x, unsigned int bit_y);
void FreeObjectArray(Object *o);
void CopyObjectArray(Object *dest, Object *src, unsigned int size);
Object *ResizeObjectArray(Object *o, unsigned int *size);
Object *CreateObjectArray(unsigned int size);

Button CreateButton(char *name, char *image, unsigned int x, unsigned int y, \
                                               unsigned int bit_x, unsigned int bit_y, unsigned int tile_size);

void FreeButtonArray(Button *b);
void CopyButtonArray(Button *dest, Button *src, unsigned int size);
Button *ResizeButtonArray(Button *b, unsigned int *size);
Button *CreateButtonArray(unsigned int size);

void DragButton(Button *b, SDL_Event *e);
void DragUIButton(Button *b, SDL_Event *e, int relative, int viewport_x);


