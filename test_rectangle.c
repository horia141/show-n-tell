#include <stdio.h>
#include <assert.h>

#include "rectangle.h"

int
main(
  int argc,
  char** argv)
{
  {
    rectangle  r;

    r = rectangle_make_xywh(1,2,3,4);

    assert(r.x == 1.0f);
    assert(r.y == 2.0f);
    assert(r.w == 3.0f);
    assert(r.h == 4.0f);

    rectangle_free(&r);

    assert(r.x == 0.0f);
    assert(r.y == 0.0f);
    assert(r.w == -1.0f);
    assert(r.h == -1.0f);
  }

  {
    rectangle  r;

    r = rectangle_make_tlbr(1,2,3,4);

    assert(r.x == 1.0f);
    assert(r.y == 2.0f);
    assert(r.w == 2.0f);
    assert(r.h == 2.0f);

    rectangle_free(&r);
  }

  {
    rectangle  r;

    r = rectangle_make_xywh(1,3,2,0.2);

    assert(rectangle_is_valid(&r) == true);

    r.w = -1.3;
    assert(rectangle_is_valid(&r) == false);

    r.w = 0.55;
    assert(rectangle_is_valid(&r) == true);

    r.h = -1.3;
    assert(rectangle_is_valid(&r) == false);

    r.h = 0.55;
    assert(rectangle_is_valid(&r) == true);

    rectangle_free(&r);
  }

  {
    rectangle  a;
    rectangle  b;

    a = rectangle_make_xywh(4,4,3,2);
    b = rectangle_make_tlbr(3,4,7,5);

    rectangle_copy(&a,&b);

    assert(a.x == 3);
    assert(a.y == 4);
    assert(a.w == 4);
    assert(a.h == 1);

    assert(a.x == b.x);
    assert(a.y == b.y);
    assert(a.w == b.w);
    assert(a.h == b.h);

    rectangle_free(&a);
    rectangle_free(&b);
  }

  return 0;
}
