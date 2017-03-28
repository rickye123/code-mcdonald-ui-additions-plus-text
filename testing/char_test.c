/*Character Module Testing*/

#include "../characters.h"

int main(void){

    Character c;

    c = CreateCharacter("ronald", SPRITE_IMAGE, 150, 150, 128, 0);

    TESTS_EQUAL_STRING("ronald", c.name)
    TESTS_NOT_NULL(c.surface)
    TESTS_IS_NULL(c.texture)
    TESTS_EQUAL_INT(128, c.source_rect.x)
    TESTS_EQUAL_INT(0, c.source_rect.y)
    TESTS_EQUAL_INT(32, c.source_rect.w)
    TESTS_EQUAL_INT(32, c.source_rect.h)
    /*values here are different because we are 'snapping' to a grid position*/
    TESTS_EQUAL_INT(160, c.dest_rect.x)
    TESTS_EQUAL_INT(160, c.dest_rect.y)
    TESTS_EQUAL_INT(32, c.dest_rect.w)
    TESTS_EQUAL_INT(32, c.dest_rect.h)

    c.source_rect.x = 64;
    MoveAndAnimateRight(&c);
    TESTS_EQUAL_INT(96, c.source_rect.x);
    TESTS_EQUAL_INT(162, c.dest_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.y);
    MoveAndAnimateRight(&c);
    TESTS_EQUAL_INT(64, c.source_rect.x);
    TESTS_EQUAL_INT(164, c.dest_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.y);

    c.source_rect.x = 192;
    MoveAndAnimateLeft(&c);
    TESTS_EQUAL_INT(224, c.source_rect.x);
    TESTS_EQUAL_INT(162, c.dest_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.y);
    MoveAndAnimateLeft(&c);
    TESTS_EQUAL_INT(192, c.source_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.y);

    c.source_rect.x = 0;
    MoveAndAnimateUp(&c);
    TESTS_EQUAL_INT(32, c.source_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.x);
    TESTS_EQUAL_INT(158, c.dest_rect.y);
    MoveAndAnimateUp(&c);
    TESTS_EQUAL_INT(0, c.source_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.x);
    TESTS_EQUAL_INT(156, c.dest_rect.y)

    c.source_rect.x = 128;
    MoveAndAnimateDown(&c);
    TESTS_EQUAL_INT(160, c.source_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.x);
    TESTS_EQUAL_INT(158, c.dest_rect.y);
    MoveAndAnimateDown(&c);
    TESTS_EQUAL_INT(128, c.source_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.x);
    TESTS_EQUAL_INT(160, c.dest_rect.y)

    c.dest_rect.x = 600;
    MoveAndAnimateRight(&c);
    TESTS_EQUAL_INT(600, c.dest_rect.x);

    c.dest_rect.x = 0;
    MoveAndAnimateLeft(&c);
    TESTS_EQUAL_INT(0, c.dest_rect.x);

    c.dest_rect.y = 0;
    MoveAndAnimateUp(&c);
    TESTS_EQUAL_INT(0, c.dest_rect.y);

    c.dest_rect.y = 440;
    MoveAndAnimateRight(&c);
    TESTS_EQUAL_INT(440, c.dest_rect.y);

    return 0;

}

