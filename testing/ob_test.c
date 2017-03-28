/*Object Module Testing*/

#include "../objects.h"

int main(void){

    Object o;
    Button b;
    o = CreateObject("logs", OBJECT_IMAGE, 200, 200, 128, 320);
    b = CreateButton("button", BUTTON_IMAGE, 0, 0, 600, 200, 32);

    TESTS_EQUAL_STRING("logs", o.name)
    TESTS_NOT_NULL(o.surface)
    TESTS_IS_NULL(o.texture)
    TESTS_EQUAL_INT(128, o.source_rect.x)
    TESTS_EQUAL_INT(320, o.source_rect.y)
    TESTS_EQUAL_INT(32, o.source_rect.w)
    TESTS_EQUAL_INT(32, o.source_rect.h)
    TESTS_EQUAL_INT(224, o.dest_rect.x)
    TESTS_EQUAL_INT(224, o.dest_rect.y)
    TESTS_EQUAL_INT(32, o.dest_rect.w)
    TESTS_EQUAL_INT(32, o.dest_rect.h)

    TESTS_EQUAL_STRING("button", b.name)
    TESTS_NOT_NULL(b.surface)
    TESTS_IS_NULL(b.texture)
    TESTS_EQUAL_INT(600, b.source_rect.x)
    TESTS_EQUAL_INT(200, b.source_rect.y)
    TESTS_EQUAL_INT(32, b.source_rect.w)
    TESTS_EQUAL_INT(32, b.source_rect.h)
    TESTS_EQUAL_INT(0, b.dest_rect.x)
    TESTS_EQUAL_INT(0, b.dest_rect.y)
    TESTS_EQUAL_INT(32, b.dest_rect.w)
    TESTS_EQUAL_INT(32, b.dest_rect.h)
    TESTS_EQUAL_BOOLEAN(false, b.dragging)

    return 0;

}

