/*

Display Module

Driver << Display >> Game(State) >> Characters >> Objects

*/

#include "display.h"

unsigned int EventLoop(Game *g){

    while(!g->window.finished){

        Events(g);

        RenderAll(g);

        SDL_Delay(MILLISECOND_DELAY - SDL_GetTicks() % MILLISECOND_DELAY);

    }

    return 0;

}

void Events(Game *g){

    SDL_Event event;

    if(g->window.win == NULL){
        DISPLAY_ERROR(NULL_WINDOW, "Null window struct passed as parameter");
    }

    /*if an event such as quit or 'q' is pending then exit game.
      Changed 'switch' to if and else because switch quite confusing*/
    while(SDL_PollEvent(&event)) {

        if(event.type == SDL_QUIT){
            g->window.finished = true;
        }
        else if (event.type == SDL_KEYDOWN &&
                  event.key.keysym.sym == SDLK_q){
            g->window.finished = true;
     
        }

        else if (SDL_MOUSEMOTION){

            ViewportDragging(g, &event);

            CheckForButtonClick(g, &event);
        }
        
    }
    /* checks for any collisions between character and objects */
    CollisionDetection(g);

    /*for these events we are only passing our main character Ronald*/
    CharacterEvents(&g->characters[0]);
  
    return;

}

void ViewportDragging(Game *g, SDL_Event *event){

    /*int relative_pos = 0;*/

    DragButton(&g->buttons[0], event);

    if(g->buttons[0].dragging == true && g->buttons[0].dest_rect.x > UI_WIDTH){
        g->window.ui_viewport.x = g->buttons[0].dest_rect.x+17; /*drag our menu out*/
    }

    /*this is some sorcery to make sure that we can drag and drop 
      buttons that are within the UI when it is pulled out*/
    /*relative_pos = (GAME_WIDTH + g->ui.buttons[0].dest_rect.x) - 
                   (GAME_WIDTH - g->window.ui_viewport.x);*/

    return;

}

void CheckForButtonClick(Game *g, SDL_Event *event){

    unsigned int i;

    for(i = 0; i < g->ui.button_num; i++){
        ClickUIButton(g, &g->ui.buttons[i], event, i+1, g->window.ui_viewport.x);
    }

    return;

}

void ClickUIButton(Game *g, Button *b, SDL_Event *e, int button_num, int viewport_x){

    int mouse_pos_x = 0, mouse_pos_y = 0;

    SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);

    if (e->type == SDL_MOUSEBUTTONDOWN &&
        mouse_pos_x > viewport_x + (TILE_SIZE*button_num) && mouse_pos_x < viewport_x + (TILE_SIZE * button_num) + b->dest_rect.w &&
        mouse_pos_y > b->dest_rect.y && mouse_pos_y < b->dest_rect.y + b->dest_rect.h){
        printf("%s, %d\n", b->name, button_num);

        IndicateNewEntry(g, b); /*change the image in the structure*/
        /*InsertNewInstruction();*/

    }

    return;

}

void IndicateNewEntry(Game *g, Button *b){

    static unsigned int position_x = ARRAY_LINE_START, position_y = Y_ARRAY_START;
    unsigned int i;
    Button instruction;    

    if(position_x == ARRAY_LINE_END && !ARE_EQUAL(b->name, "CLEAR")){
        position_x = ARRAY_LINE_START;
        position_y = position_y + 2; /*just jumping down to the next clear row*/

    }

    if(ARE_EQUAL(b->name, "CLEAR") && g->ui.instruction_num != 0){

        Reposition(&position_x, &position_y);
        RemoveUIButton(g);

    }

    else if(ARE_EQUAL(b->name, "RUN") && g->ui.instruction_num != 0){
        for(i = 0; i < g->ui.instruction_num; i++){
            printf("%s\n", g->ui.instructions[i]);
        }
    }


    if(position_y > CODE_LIMIT){
        printf("Code limit reached\n");
        return;
    }

    if(ARE_EQUAL(b->name, "FD") || ARE_EQUAL(b->name, "BK") ||
       ARE_EQUAL(b->name, "RT") || ARE_EQUAL(b->name, "LT") ||
       ARE_EQUAL(b->name, "DIG") || ARE_EQUAL(b->name, "PLANT")){

        instruction = CreateButton(b->name, "UIButtons.bmp", (position_x * TILE_SIZE), (position_y * TILE_SIZE), b->source_rect.x, b->source_rect.y, TILE_SIZE);
        InsertNewUIButton(g, instruction);
        position_x++;

        InsertInstruction(g, instruction.name);
        g->ui.instruction_num++;
        printf("Added instruction\n");
    }


    SetGamePieceTextures(g);

    return;

}

void Reposition(unsigned int *position_x, unsigned int *position_y){

    if(*position_x == ARRAY_LINE_START && *position_y > Y_ARRAY_START){
        *position_x = ARRAY_LINE_END-1;
        *position_y = *position_y - 2;
    }

    else if (*position_x > ARRAY_LINE_START){
        *position_x = *position_x - 1;
    }

    return;

}

void RemoveUIButton(Game *g){

    g->ui.instruction_num--;
    g->ui.button_num--;

    return;

}

void InsertInstruction(Game *g, char *instruction_name){

    strcpy(g->ui.instructions[g->ui.instruction_num], instruction_name);

    return;

}

/*############Display Stuff################*/

/*this creates our background map by creating textures 
  from surfaces so we use only the renderer.
  Limiting the rendering to our map size only so we can
  extend the overall window for the UI stuff

  Lookup optimised surface loading and soft stretching

*/
void SetTextures(Game *g, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH], unsigned int ui_tiles[MAP_HEIGHT][MAP_WIDTH]){

    SetGameTexture(g, tiles);

    SetUITexture(g, ui_tiles);

    if(g->window.texture == NULL){
        DISPLAY_ERROR(NULL_ARG_TO_RENDER, "Error in setting window texture");
    }

    SetTextTexture(g);

    SetGamePieceTextures(g);

    return;

}

void SetGameTexture(Game *g, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH]){

    unsigned int i, j;

    for(i = 0; i < MAP_HEIGHT; i++){
        for(j = 0; j < MAP_WIDTH; j++){

             g->window.dest_rect.y = i * TILE_SIZE;
             g->window.dest_rect.x = j * TILE_SIZE;

             DetermineBitImage(&g->window, tiles, i, j);

             SDL_BlitSurface(g->window.background, &g->window.source_rect, \
                                        g->window.screen, &g->window.dest_rect);

        }
    }

    g->window.texture = SDL_CreateTextureFromSurface(g->window.renderer, g->window.screen);

    return;

}

void SetObjectTexture(Game *g, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH]){

    unsigned int i, j;

    for(i = 0; i < MAP_HEIGHT; i++){
        for(j = 0; j < MAP_WIDTH; j++){

             if(tiles[i][j] != 0){

             g->window.dest_rect.y = i * TILE_SIZE;
             g->window.dest_rect.x = j * TILE_SIZE;

             DetermineBitImage(&g->window, tiles, i, j);

             InsertNewObject(g, 
                 CreateObject("logs", OBJECT_IMAGE, g->window.dest_rect.x, g->window.dest_rect.y, 128, 128));

             SDL_BlitSurface(g->window.background, &g->window.source_rect, \
                                        g->window.screen, &g->window.dest_rect);
             }
        }
    }

    g->window.texture = SDL_CreateTextureFromSurface(g->window.renderer, g->window.screen);

    return;

}

void SetUITexture(Game *g, unsigned int ui_tiles[MAP_HEIGHT][MAP_WIDTH]){

    unsigned int i, j;

    for(i = 0; i < MAP_HEIGHT; i++){
        for(j = 0; j < MAP_WIDTH; j++){

             g->ui.dest_rect.y = i * TILE_SIZE;
             g->ui.dest_rect.x = j * TILE_SIZE;

             DetermineUIBitImage(&g->ui, ui_tiles, i, j);

             SDL_BlitSurface(g->ui.source, &g->ui.source_rect, \
                                        g->ui.surface, &g->ui.dest_rect);

        }
    }

    g->ui.texture = SDL_CreateTextureFromSurface(g->window.renderer, g->ui.surface);

    return;

}

void SetGamePieceTextures(Game *g){

    unsigned int i;

    for(i = 0; i < g->char_num; i++){

        g->characters[i].texture = SDL_CreateTextureFromSurface(g->window.renderer, g->characters[i].surface);
    }

    for(i = 0; i < g->obj_num; i++){

        g->objects[i].texture = SDL_CreateTextureFromSurface(g->window.renderer, g->objects[i].surface);
    }

    for(i = 0; i < g->button_num; i++){

        g->buttons[i].texture = SDL_CreateTextureFromSurface(g->window.renderer, g->buttons[i].surface);
    }

    for(i = 0; i < g->ui.button_num; i++){

        g->ui.buttons[i].texture = SDL_CreateTextureFromSurface(g->window.renderer, g->ui.buttons[i].surface);
    }

    for (i = 0; i < g->text_num; i++) {
        g->text[i].texture = SDL_CreateTextureFromSurface(g->window.renderer, g->text[i].surface);
    }

    return;

}

void RenderAll(Game *game){

    if(game->characters == NULL || game->objects == NULL || game->buttons == NULL || game->text == NULL){
        DISPLAY_ERROR(NULL_ARG_TO_RENDER, "Null variable cannot be rendered");
    }

    SDL_RenderClear(game->window.renderer);

    RenderGameViewport(game);

    RenderUIViewport(game);

    SDL_RenderPresent(game->window.renderer);

    return;

}

void RenderUIViewport(Game *g){

    unsigned int i;

    SDL_RenderSetViewport(g->window.renderer, &g->window.ui_viewport);
    SDL_RenderCopy(g->window.renderer, g->ui.texture, NULL, NULL);


    for(i = 0; i < g->ui.button_num; i++){
        if(g->ui.buttons[i].texture == NULL){
            DISPLAY_ERROR(NULL_ARG_TO_RENDER, "Null UI Button variable cannot be rendered" );
        }
        SDL_RenderCopy(g->window.renderer, g->ui.buttons[i].texture, &g->ui.buttons[i].source_rect, &g->ui.buttons[i].dest_rect);

    }

    return;

}

void RenderGameViewport(Game *g){

    SDL_RenderSetViewport(g->window.renderer, &g->window.game_viewport);
    SDL_RenderCopy(g->window.renderer, g->window.texture, NULL, NULL);
    
    RenderObjects(g);
    RenderCharacters(g);
    RenderButtons(g);
    RenderText(g); 

    return;

}

void RenderText(Game *g) {

    unsigned int i;

    for(i = 0; i < g->text_num; i++){
        if(g->text[i].texture == NULL){
            DISPLAY_ERROR(NULL_ARG_TO_RENDER, "Null variable cannot be rendered" );
        }
        SDL_RenderCopy(g->window.renderer, g->text[i].texture, &g->text[i].source_rect, &g->text[i].dest_rect);

    }

    return;
}

void RenderCharacters(Game *g){

    unsigned int i;

    for(i = 0; i < g->char_num; i++){
        if(g->characters[i].texture == NULL){
            DISPLAY_ERROR(NULL_ARG_TO_RENDER, "Null variable cannot be rendered" );
        }
        SDL_RenderCopy(g->window.renderer, g->characters[i].texture, &g->characters[i].source_rect, &g->characters[i].dest_rect);

    }

    return;

}

void RenderObjects(Game *g){

    unsigned int i;

    for(i = 0; i < g->obj_num; i++){
        if(g->objects[i].texture == NULL){
            DISPLAY_ERROR(NULL_ARG_TO_RENDER, "Null variable cannot be rendered" );
        }
        SDL_RenderCopy(g->window.renderer, g->objects[i].texture, &g->objects[i].source_rect, &g->objects[i].dest_rect);
    }

    return;

}

void RenderButtons(Game *g){

    unsigned int i;

    for(i = 0; i < g->button_num; i++){
        if(g->buttons[i].texture == NULL){
            DISPLAY_ERROR(NULL_ARG_TO_RENDER, "Null variable cannot be rendered" );
        }
        SDL_RenderCopy(g->window.renderer, g->buttons[i].texture, &g->buttons[i].source_rect, &g->buttons[i].dest_rect);
    }

    return;

}



/*determine which part of the bitmap will be used for
  the corresponding number on our map array*/
void DetermineBitImage(Window *win, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH], \
                                                                int i, int j){

    int x = 0, y = 0;
    unsigned int bmp_columns = 16;

    x = ((tiles[i][j] - 1) % bmp_columns) * TILE_SIZE;
    y = ((tiles[i][j] - 1) / bmp_columns) * TILE_SIZE;
/*
    if(tiles[i][j] == 0){ x = 32; y = 352;} simple grass
    else if(tiles[i][j] == 1){ x = 0; y = 0 ;} paths and cobbles
    else if(tiles[i][j] == 2){ x = 32, y = 0;}
    else if(tiles[i][j] == 3){ x = 64, y = 0;}
    else if(tiles[i][j] == 4){ x = 0, y = 32;}
    else if(tiles[i][j] == 5){ x = 32, y = 32;}
    else if(tiles[i][j] == 6){ x = 64, y = 32;}
    else if(tiles[i][j] == 7){ x = 0, y = 64;}
    else if(tiles[i][j] == 8){ x = 32, y = 64;}
    else if(tiles[i][j] == 9){ x = 64, y = 64;}

    else if(tiles[i][j] == 10){ x = 96, y = 320;} water and edges
    else if(tiles[i][j] == 11){ x = 0, y = 352 ;}
    else if(tiles[i][j] == 12){ x = 0, y = 384 ;}
    else if(tiles[i][j] == 13){ x = 0, y = 416;}
    else if(tiles[i][j] == 14){ x = 32, y = 384;}
    else if(tiles[i][j] == 15){ x = 64, y = 384;}
    else if(tiles[i][j] == 16){ x = 32, y = 416;}
    else if(tiles[i][j] == 17){ x = 64, y = 416;}*/

    SetWinBitmapPos(win, x, y);

    return;

}

void SetWinBitmapPos(Window *window, unsigned int bit_x, unsigned int bit_y){

    window->source_rect.x = bit_x;
    window->source_rect.y = bit_y;
    window->source_rect.w = TILE_SIZE;
    window->source_rect.h = TILE_SIZE;

    return;

}

void DetermineUIBitImage(UI *u, unsigned int tiles[MAP_HEIGHT][MAP_WIDTH], unsigned int i, unsigned int j){

    unsigned int x = 0, y = 0;
    unsigned int bmp_columns = 17;

    x = ((tiles[i][j]- 43) % bmp_columns) * TILE_SIZE;
    y = ((tiles[i][j] - 43) / bmp_columns) * TILE_SIZE;

    /*if(tiles[i][j] == 0){ x = 352; y = 128; }
    else if(tiles[i][j] == 1){ x = 384; y = 128; }
    else if(tiles[i][j] == 2){ x = 416; y = 128; }
    else if(tiles[i][j] == 3){ x = 448; y = 128; }
    else if(tiles[i][j] == 4){ x = 480; y = 128; }
    else if(tiles[i][j] == 5){ x = 512; y = 128; }
    else if(tiles[i][j] == 6){ x = 352; y = 150; }
    else if(tiles[i][j] == 7){ x = 384; y = 150; }
    else if(tiles[i][j] == 8){ x = 416; y = 150; }
    else if(tiles[i][j] == 9){ x = 448; y = 150; }
    else if(tiles[i][j] == 10){ x = 480; y = 150; }
    else if(tiles[i][j] == 11){ x = 512; y = 150; }
    else if(tiles[i][j] == 12){ x = 352; y = 182; }
    else if(tiles[i][j] == 13){ x = 384; y = 182; }
    else if(tiles[i][j] == 14){ x = 416; y = 182; }
    else if(tiles[i][j] == 15){ x = 448; y = 182; }
    else if(tiles[i][j] == 16){ x = 480; y = 182; }
    else if(tiles[i][j] == 17){ x = 512; y = 182; }
    else if(tiles[i][j] == 18){ x = 352; y = 214; }
    else if(tiles[i][j] == 19){ x = 384; y = 214; }
    else if(tiles[i][j] == 20){ x = 416; y = 214; }
    else if(tiles[i][j] == 21){ x = 448; y = 214; }
    else if(tiles[i][j] == 22){ x = 480; y = 214; }
    else if(tiles[i][j] == 23){ x = 512; y = 214; }
    else if(tiles[i][j] == 24){ x = 352; y = 246; }
    else if(tiles[i][j] == 25){ x = 384; y = 246; }
    else if(tiles[i][j] == 26){ x = 416; y = 246; }
    else if(tiles[i][j] == 27){ x = 448; y = 246; }
    else if(tiles[i][j] == 28){ x = 480; y = 246; }
    else if(tiles[i][j] == 29){ x = 512; y = 246; }
    else if(tiles[i][j] == 30){ x = 352; y = 278; }
    else if(tiles[i][j] == 31){ x = 384; y = 278; }
    else if(tiles[i][j] == 32){ x = 416; y = 278; }
    else if(tiles[i][j] == 33){ x = 448; y = 278; }
    else if(tiles[i][j] == 34){ x = 480; y = 278; }
    else if(tiles[i][j] == 35){ x = 512; y = 278; }*/

/*544/320
17/10
169: x =  512, 278 
544/32 = 17*/

    /*else if(tiles[i][j] == 169){ x = ((169%17)) * 32; y = (169/17) * 32; printf("%d, %d\n", x, y);}
    else if(tiles[i][j] == 122){ x = ((122%17)) * 32; y = (122/17) * 32; printf("%d, %d\n", x, y);}
    else if(tiles[i][j] == 165){ x = 320; y = 278; }
    else if(tiles[i][j] == 166){ x = 320; y = 278; }
    else if(tiles[i][j] == 167){ x = 320; y = 278; }
    else if(tiles[i][j] == 182){ x = 320; y = 278; }
    else if(tiles[i][j] == 187){ x = 352; y = 278; }
    else if(tiles[i][j] == 183){ x = 352; y = 278; }
    else if(tiles[i][j] == 183){ x = 352; y = 278; }
    else if(tiles[i][j] == 182){ x = 352; y = 278; }
    else if(tiles[i][j] == 199){ x = 352; y = 278; }
    else if(tiles[i][j] == 200){ x = 352; y = 278; }
    else if(tiles[i][j] == 201){ x = 352; y = 278; }*/


    SetUIBitmapPos(u, x, y);

    return;

}

void SetUIBitmapPos(UI *u, unsigned int bit_x, unsigned int bit_y){

    u->source_rect.x = bit_x;
    u->source_rect.y = bit_y;
    u->source_rect.w = TILE_SIZE;
    u->source_rect.h = TILE_SIZE;

    return;

}

