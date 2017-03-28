/*Tests for the creation and rendering of
multiple characters, objects and buttons*/

#include "../game.h"

int main(){

    Game game;
    Character c, x;
    Object o, a;
    Button b, m;

    game.characters = NULL;
    game.objects = NULL;
    game.char_num = 0;
    game.obj_num = 0;
    game.button_num = 0;

    c = CreateCharacter("Ronald", SPRITE_IMAGE, 200, 100, 128, 0);
    x = CreateCharacter("MacDonald", SPRITE_IMAGE, 100, 100, 128, 0);
    InsertNewCharacter(&game, c);
    InsertNewCharacter(&game, x);

    o = CreateObject("logs", OBJECT_IMAGE, 200, 200, 128, 320);
    a = CreateObject("morelogs", OBJECT_IMAGE, 220, 250, 128, 320);
    InsertNewObject(&game, o);
    InsertNewObject(&game, a);

    b = CreateButton("button", BUTTON_IMAGE, 600, 200, 0, 0, 32);
    m = CreateButton("anotherbutton", BUTTON_IMAGE, 600, 100, 0, 0, 32);
    InsertNewButton(&game, b);
    InsertNewButton(&game, m);

    TESTS_EQUAL_INT(2, game.char_num)
    TESTS_EQUAL_INT(2, game.obj_num)
    TESTS_EQUAL_INT(2, game.button_num)

    TESTS_EQUAL_STRING("Ronald", game.characters[0].name)
    TESTS_NOT_NULL(game.characters[0].surface)
    TESTS_IS_NULL(game.characters[0].texture)
    TESTS_EQUAL_INT(128, game.characters[0].source_rect.x)
    TESTS_EQUAL_INT(0, game.characters[0].source_rect.y)
    TESTS_EQUAL_INT(32, game.characters[0].source_rect.w)
    TESTS_EQUAL_INT(32, game.characters[0].source_rect.h)
    /*values here are different because we are 'snapping' to a grid position*/
    TESTS_EQUAL_INT(224, game.characters[0].dest_rect.x)
    TESTS_EQUAL_INT(128, game.characters[0].dest_rect.y)
    TESTS_EQUAL_INT(32, game.characters[0].dest_rect.w)
    TESTS_EQUAL_INT(32, game.characters[0].dest_rect.h)

    TESTS_EQUAL_STRING("MacDonald", game.characters[1].name)
    TESTS_NOT_NULL(game.characters[1].surface)
    TESTS_IS_NULL(game.characters[1].texture)
    TESTS_EQUAL_INT(128, game.characters[1].source_rect.x)
    TESTS_EQUAL_INT(0, game.characters[1].source_rect.y)
    TESTS_EQUAL_INT(32, game.characters[1].source_rect.w)
    TESTS_EQUAL_INT(32, game.characters[1].source_rect.h)
    /*values here are different because we are 'snapping' to a grid position*/
    TESTS_EQUAL_INT(128, game.characters[1].dest_rect.x)
    TESTS_EQUAL_INT(128, game.characters[1].dest_rect.y)
    TESTS_EQUAL_INT(32, game.characters[1].dest_rect.w)
    TESTS_EQUAL_INT(32, game.characters[1].dest_rect.h)

    /*at this point it can probably be assumed that the others for objects and buttons
      work as well because they are the same code essentially, will add test in later*/


    return 0;

}
