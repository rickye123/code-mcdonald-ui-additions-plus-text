/*UI Module*/

struct ui {

    unsigned int x, y;
    SDL_Texture *texture;
    SDL_Surface *source, *surface;
    SDL_Rect source_rect, dest_rect;
};
typedef struct ui UI;


