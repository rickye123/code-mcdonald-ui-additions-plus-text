/*Test Driver Module to Run the Game*/

#include "display.h"



#define WATER_IMAGE "water-sheet.bmp"

Text CreateText(Game *g, char *name, char *text, unsigned int x, unsigned int y) ;

void InsertNewText(Game *g, Text new_t);
Text* CreateTextArray(unsigned int size) ;
Text *ResizableTextArray(Text *t, unsigned int *size) ;

void CopyTextArray(Text *dest, Text *src, unsigned int size);
void FreeTextArray(Text *t);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface *destination);

int main(void){

    Game game;
    Character c, x;
    Object o, a, e;
    Text t; 
    Button b, forward, back, right, left, dig, plant, run, clear;
    unsigned int map[15][20];
    unsigned int overlay[15][20];
    unsigned int ui_layout[15][20];
    FILE *f = OpenFile("map.txt");
    FILE *over = OpenFile("maptwo.txt");

    CreateWindow(&game.window);
    game.characters = NULL;
    game.objects = NULL;
    game.char_num = 0;
    game.obj_num = 0;
    game.button_num = 0;
    game.text_num = 0; 

    MakeMapFromFile(f, map);
    MakeMapFromFile(over, overlay);
    MakeUILayout(ui_layout);

    game.ui = CreateUI(BUTTON_IMAGE, 0, 0, 0, 128);

    c = CreateCharacter("Ronald", SPRITE_IMAGE, 224, 128, 128, 0);
    x = CreateCharacter("McDonald", SPRITE_IMAGE, 100, 100, 128, 0);
    InsertNewCharacter(&game, c);
    InsertNewCharacter(&game, x);

    o = CreateObject("logs", OBJECT_IMAGE, 200, 200, 128, 320);
    a = CreateObject("morelogs", OBJECT_IMAGE, 320, 350, 128, 320);
    e = CreateObject("morelogs2", OBJECT_IMAGE, 570, 350, 128, 320);   

    InsertNewObject(&game, o);
    InsertNewObject(&game, a);
    InsertNewObject(&game, e);

    b = CreateButton("button", BUTTON_IMAGE, 624, 200, 0, 0, 32);
    InsertNewButton(&game, b);

    t = CreateText(&game, "test", "hello", 32, 0);
    InsertNewText(&game, t); 

    forward = CreateButton("FD", "UIButtons.bmp", 32, 384, 0, 0, 32);
    back = CreateButton("RT", "UIButtons.bmp", 64, 384, 32, 0, 32);
    right = CreateButton("BK", "UIButtons.bmp", 96, 384, 64, 0, 32);
    left = CreateButton("LT", "UIButtons.bmp", 128, 384, 96, 0, 32);
    dig = CreateButton("DIG", "UIButtons.bmp", 160, 384, 128, 0, 32);
    plant = CreateButton("PLANT", "UIButtons.bmp", 192, 384, 160, 0, 32);

    run = CreateButton("RUN", "UIButtons.bmp", 224, 384, 192, 0, 32);
    clear = CreateButton("CLEAR", "UIButtons.bmp", 256, 384, 224, 0, 32);

    InsertNewUIButton(&game, forward);
    InsertNewUIButton(&game, back);
    InsertNewUIButton(&game, right);
    InsertNewUIButton(&game, left);
    InsertNewUIButton(&game, dig);
    InsertNewUIButton(&game, plant);
    InsertNewUIButton(&game, run);
    InsertNewUIButton(&game, clear);

   /* SetObjectTexture(&game, overlay); */
    SetTextures(&game, map, ui_layout);

    EventLoop(&game);

    SDL_FreeSurface(b.surface);
    SDL_DestroyTexture(b.texture);
    FreeGame(&game);

    return 0;

}


Text CreateText(Game *g, char *name, char *text, unsigned int x, unsigned int y) 
{

    Text t; 
    SDL_Color textColor = {0, 0, 0, 1};

    t.name = name; 
    t.font = SetupTTF("xerox.ttf", 24); 

    t.surface = TTF_RenderText_Solid(t.font, text, textColor);

    if(t.surface == NULL) {
        puts("ERROR!!!!");
        exit(1);
    }

    t.texture = NULL; 

    t.dest_rect.x = x;
    t.dest_rect.y = y;
    t.dest_rect.w = TILE_SIZE;
    t.dest_rect.h = TILE_SIZE;

    SDL_BlitSurface(t.surface, NULL, g->window.screen, &t.dest_rect);

    return t; 

}

void SetTextTexture(Game *g)
{

    CreateText(g, "testText", "message", 64, 32);

    g->window.texture = SDL_CreateTextureFromSurface(g->window.renderer, g->window.screen);

    return;

}


TTF_Font* SetupTTF(char *fontName, int fontSize)
{

    TTF_Font *font_ptr; 
    /* SDL2_TTF needs to be initialized just like SDL2 */
    if ( TTF_Init() == -1 ) {
        printf("Failed to initialize TTF : %s", SDL_GetError());
        exit(1); 
    }

    /* Load our fonts, with a huge size */
    font_ptr = TTF_OpenFont(fontName, fontSize);
    
    /* Error check */
    if ( font_ptr == NULL ) {
        printf("Failed to load font : %s",SDL_GetError());
        exit(1); 
    }
    puts("\nsuccessful");
    return font_ptr; 
}


void InsertNewText(Game *g, Text new_t) {

    if(g->text_num == 0) {
        g->text = CreateTextArray(++g->text_num); 
        g->text[g->text_num - 1] = new_t; 

        return; 
    }

    g->text = ResizableTextArray(g->text, &g->text_num);
    g->text[g->text_num - 1] = new_t; 

    return; 

}

Text* CreateTextArray(unsigned int size) 
{
    Text *t = NULL; 

    if(size <= 0) {
        puts("Size less than 0");
        exit(1); 
    }

    t = (Text *)calloc(size, sizeof(Text)); 

    if(t == NULL) {
        puts("T is null");
        exit(1);
    }

    return t; 
}

Text *ResizableTextArray(Text *t, unsigned int *size) 
{
    Text *temp = NULL; 

    temp = CreateTextArray(*size); 

    CopyTextArray(temp, t, *size); 

    FreeTextArray(t); 

    t = CreateTextArray(++*size); 

    CopyTextArray(t, temp, *size - 1);

    FreeTextArray(temp);

    return t; 
}

void CopyTextArray(Text *dest, Text *src, unsigned int size)
{

    unsigned int i;

    for(i = 0; i < size; i++){
        dest[i] = src[i];
    }

    return;

}

void FreeTextArray(Text *t)
{

    free(t);

    t = NULL;

    return;

}