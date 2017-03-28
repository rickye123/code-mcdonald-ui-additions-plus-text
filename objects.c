/*

Objects Module

Driver << Display << Game(State) << Characters << Objects

*/

#include "objects.h"

Object CreateObject(char *name, char *image, unsigned int x, unsigned int y, \
                                               unsigned int bit_x, unsigned int bit_y){

    Object o;

    o.name = name;
 
    o.surface = SDL_LoadBMP(image);

    if(o.surface == NULL){
        OBJECT_ERROR(OBJECT_IMAGE_ERR, "Loading of object image bitmap file failed")
    }

    o.texture = NULL;

    /*position within the bitmap*/
    o.source_rect.x = bit_x;
    o.source_rect.y = bit_y;
    o.source_rect.w = TILE_SIZE;
    o.source_rect.h = TILE_SIZE;


    /*snap to tile; necessary?*/
    while(x % TILE_SIZE != 0){
        while(y % TILE_SIZE != 0){
            y++;
        }
        x++;
    }

    o.dest_rect.x = x;
    o.dest_rect.y = y;
    o.dest_rect.w = TILE_SIZE;
    o.dest_rect.h = TILE_SIZE;

    return o;

}

/*Multiple Objects*/

Object *CreateObjectArray(unsigned int size){

    Object *o = NULL;

    if(size <= 0){
        OBJECT_ERROR(OBJ_ALLOC_ERROR, "Object array size cannot be less than or equal to zero");
    }

    o = (Object *)calloc(size, sizeof(Object));

    if(o == NULL){
        OBJECT_ERROR(OBJ_ALLOC_ERROR, "Problem in allocating space for object");
    }

    return o;

}

Object *ResizeObjectArray(Object *o, unsigned int *size){

    Object *temp = NULL;

    temp = CreateObjectArray(*size);

    CopyObjectArray(temp, o, *size);

    FreeObjectArray(o);

    o = CreateObjectArray(++*size);

    CopyObjectArray(o, temp, *size-1);

    FreeObjectArray(temp);

    return o;

}

void CopyObjectArray(Object *dest, Object *src, unsigned int size){

    unsigned int i;

    for(i = 0; i < size; i++){
        dest[i] = src[i];
    }

    return;

}

void FreeObjectArray(Object *o){

    free(o);

    o = NULL;

    return;

}

/*tile size being passed as a parameter so we can use different style buttons*/
Button CreateButton(char *name, char *image, unsigned int x, unsigned int y, \
                                               unsigned int bit_x, unsigned int bit_y, unsigned int tile_size){

    Button b;

    b.name = name;

    b.surface = SDL_LoadBMP(image);

    if(b.surface == NULL){
        OBJECT_ERROR(OBJECT_IMAGE_ERR, "Loading of object image bitmap file failed")
    }

    b.texture = NULL;

    /*position within the bitmap*/
    b.source_rect.x = bit_x;
    b.source_rect.y = bit_y;
    b.source_rect.w = tile_size;
    b.source_rect.h = tile_size;


    /*snap to tile; necessary?
    while(x % tile_size != 0){
        while(y % tile_size != 0){
            y++;
        }
        x++;
    }*/

    b.dest_rect.x = x;
    b.dest_rect.y = y;
    b.dest_rect.w = tile_size;
    b.dest_rect.h = tile_size;

    b.dragging = false;

    return b;

}

/*if user has clicked within button coordinates then allow them to 
  move the button relative to the mouse x and y coords*/
void DragButton(Button *b, SDL_Event *e){

    int mouse_pos_x = 0, mouse_pos_y = 0;

    SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);

    if (mouse_pos_x > b->dest_rect.x && mouse_pos_x < b->dest_rect.x + b->dest_rect.w &&
        mouse_pos_y > b->dest_rect.y && mouse_pos_y < b->dest_rect.y + b->dest_rect.h
        && e->type == SDL_MOUSEBUTTONDOWN ){
        b->dragging = true;
    }

    else if(e->type == SDL_MOUSEBUTTONUP){
        b->dragging = false;
    }

    if(b->dragging == true && SDL_MOUSEMOTION &&
       e->motion.x > 330 && e->motion.x < 640
       && e->motion.y > 0 && e->motion.y < 480){

        /*subtracting TILE_SIZE/2 so
          the button appears to be picked up from its centre*/
        b->dest_rect.x = e->motion.x - (TILE_SIZE/2);
        /*b->dest_rect.y = e->motion.y - (TILE_SIZE/2);*/
    }

    return;

}



/*Hate copying stuff I'm sure we can clean combine these*/
void DragUIButton(Button *b, SDL_Event *e, int relative, int viewport_x){

    int mouse_pos_x = 0, mouse_pos_y = 0;

    SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);

    if (mouse_pos_x > relative && mouse_pos_x < relative + b->dest_rect.w &&
        mouse_pos_y > b->dest_rect.y && mouse_pos_y < b->dest_rect.y + b->dest_rect.h
        && e->type == SDL_MOUSEBUTTONDOWN ){
        b->dragging = true;
    }

    else if(e->type == SDL_MOUSEBUTTONUP){
        b->dragging = false;
    }

    if(b->dragging == true && SDL_MOUSEMOTION &&
       e->motion.x > 640 && e->motion.x < 960
       && e->motion.y > 0 && e->motion.y < 480){

        b->dest_rect.x = e->motion.x - viewport_x - (TILE_SIZE/2);
        b->dest_rect.y = e->motion.y - (TILE_SIZE/2);
    }

    return;

}

/*Multiple Buttons*/

Button *CreateButtonArray(unsigned int size){

    Button *b = NULL;

    if(size == 0){
        UI_ERROR(BUTTON_ALLOC_ERROR, "Object array size cannot be zero");
    }

    b = (Button *)calloc(size, sizeof(Button));

    if(b == NULL){
        UI_ERROR(BUTTON_ALLOC_ERROR, "Problem in allocating space for object");
    }

    return b;

}

Button *ResizeButtonArray(Button *b, unsigned int *size){

    Button *temp = NULL;

    temp = CreateButtonArray(*size);

    CopyButtonArray(temp, b, *size);

    FreeButtonArray(b);

    b = CreateButtonArray(++*size);

    CopyButtonArray(b, temp, *size-1);

    FreeButtonArray(temp);

    return b;

}

void CopyButtonArray(Button *dest, Button *src, unsigned int size){

    unsigned int i;

    for(i = 0; i < size; i++){
        dest[i] = src[i];
    }

    return;

}

void FreeButtonArray(Button *b){

    free(b);

    b = NULL;

    return;
}

