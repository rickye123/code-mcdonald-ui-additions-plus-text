/*

Characters Module

Driver << Display << Game(State) << Characters >> Objects

*/

#include "characters.h"

Character CreateCharacter(char *name, char *image, unsigned int x, unsigned int y, \
                                                   unsigned int bit_x, unsigned int bit_y){

    int colorkey;
    Character c;
    c.name = name;
    
  

    c.surface = SDL_LoadBMP(image);
    if(c.surface == NULL){
        CHAR_ERROR(CHAR_IMAGE_ERR, "Loading of character bitmap file failed");
    }

    c.texture = NULL;

    /*background colour of the bmp needs to be found so it
      can be filtered when drawing sprite*/
    colorkey = SDL_MapRGB(c.surface->format, 255, 0, 255);
    SDL_SetColorKey(c.surface, SDL_RLEACCEL, colorkey);

    /*position within the bitmap*/
    c.source_rect.x = bit_x;
    c.source_rect.y = bit_y;
    c.source_rect.w = TILE_SIZE;
    c.source_rect.h = TILE_SIZE;
    c.x_prev = x;
    c.y_prev = y;
    /*snap to tile; necessary?*/
   
  

    c.dest_rect.x = x;
    c.dest_rect.y = y;
    c.dest_rect.w = TILE_SIZE;
    c.dest_rect.h = TILE_SIZE;

    return c;

}


/*should this go into the 'Events' module?*/
void CharacterEvents(Character *c){

    const uint8_t *keystate;

    /*note: only gives current state after all events
      have been processed so potential for event to be
      missed if pressed and released before processing*/

    /*using GetKeyboardState as we may want to include
     mulitple key presses; to pull up a menu or switch
     views, zoom maybe - also GetKeyState didn't work?*/

    keystate = SDL_GetKeyboardState(NULL);

    if(keystate[SDL_SCANCODE_RIGHT]){

        MoveAndAnimateRight(c);

    }
    else if(keystate[SDL_SCANCODE_LEFT]){

        MoveAndAnimateLeft(c);

    }
    else if(keystate[SDL_SCANCODE_UP]){

        MoveAndAnimateUp(c);
    }
    else if(keystate[SDL_SCANCODE_DOWN]){

        MoveAndAnimateDown(c);
    }

    return;
}


/*numbers correspond to different locations of the sprite bitmap file*/
void MoveAndAnimateRight(Character *c){

    if(c->source_rect.x == 64){
        c->source_rect.x = 96;
    }
    else{
        c->source_rect.x = 64;
    }
    
    /*check that our character isn't going out of view*/
    if(c->dest_rect.x < 600){
        c->x_prev = c->dest_rect.x;
        c->dest_rect.x += MOVE_AMOUNT;
        c->dest_rect.y = c->dest_rect.y;
    }

    return;

}

void MoveAndAnimateLeft(Character *c){

    if(c->source_rect.x == 192){
        c->source_rect.x = 224;
    }
    else{
        c->source_rect.x = 192;
    }

    if(c->dest_rect.x > 0){
        c->x_prev = c->dest_rect.x;
        c->dest_rect.x -= MOVE_AMOUNT;
        c->dest_rect.y = c->dest_rect.y;
    }

    return;

}

void MoveAndAnimateUp(Character *c){

    if(c->source_rect.x == 0){
        c->source_rect.x = 32;
    }
    else{
        c->source_rect.x = 0;
    }

    if(c->dest_rect.y > 0){
        c->y_prev = c->dest_rect.y;
        c->dest_rect.y -= MOVE_AMOUNT;
        c->dest_rect.x = c->dest_rect.x;
    }

    return;

}

void MoveAndAnimateDown(Character *c){

    if(c->source_rect.x == 128){
        c->source_rect.x = 160;
    }
    else{
        c->source_rect.x = 128;
    }

    if(c->dest_rect.y < 440){
        c->y_prev = c->dest_rect.y;
        c->dest_rect.y += MOVE_AMOUNT;
        c->dest_rect.x = c->dest_rect.x;
    }

    return;

}

/*Multiple Characters*/

Character *CreateCharacterArray(unsigned int size){

    Character *c = NULL;

    if(size <= 0){
        CHAR_ERROR(ALLOCATION_ERROR, "Character array size cannot be less than or equal to zero");
    }

    c = (Character *)calloc(size, sizeof(Character));

    if(c == NULL){
        CHAR_ERROR(ALLOCATION_ERROR, "Problem in allocating space for character");
    }

    return c;

}

/*when we are inserting a new character, we automatically resize the
  array which we are using by copying it to a temp array, resizing by
  one element and copying back*/
Character *ResizeCharacterArray(Character *c, unsigned int *size){

    Character *temp = NULL;

    temp = CreateCharacterArray(*size);

    CopyCharacterArray(temp, c, *size);

    FreeCharacterArray(c);

    c = CreateCharacterArray(++*size);

    CopyCharacterArray(c, temp, *size-1);

    FreeCharacterArray(temp);

    return c;

}

void CopyCharacterArray(Character *dest, Character *src, unsigned int size){

    unsigned int i;

    for(i = 0; i < size; i++){
        dest[i] = src[i];
    }

    return;

}

void FreeCharacterArray(Character *c){

    free(c);

    c = NULL;

    return;

}

