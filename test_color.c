#include <stdio.h>
#include <assert.h>

#include "color.h"

int
main(
  int argc,
  char** argv)
{
  {
    color  c;

    c = color_make_rgb(0,0.5,0.77);

    assert(c.r == 0.0f);
    assert(c.g == 0.5f);
    assert(c.b == 0.77f);
    assert(c.a == 1.0f);

    color_free(&c);

    assert(c.r == -1.0f);
    assert(c.g == -1.0f);
    assert(c.b == -1.0f);
    assert(c.a == -1.0f);
  }

  {
    color  c;

    c = color_make_rgba(0,0.23,0.71,0.44);

    assert(c.r == 0.0f);
    assert(c.g == 0.23f);
    assert(c.b == 0.71f);
    assert(c.a == 0.44f);

    color_free(&c);
  }

  {
    color  c;

    c = color_make_rgba(0,0.11,0.73,0.88);

    assert(color_is_valid(&c) == true);

    c.r = 1.01;
    assert(color_is_valid(&c) == false);

    c.r = 0.44;
    assert(color_is_valid(&c) == true);

    c.r = -2.03;
    assert(color_is_valid(&c) == false);

    c.r = 0.22;
    assert(color_is_valid(&c) == true);

    c.g = 1.01;
    assert(color_is_valid(&c) == false);

    c.g = 0.44;
    assert(color_is_valid(&c) == true);

    c.g = -2.03;
    assert(color_is_valid(&c) == false);

    c.g = 0.22;
    assert(color_is_valid(&c) == true);

    c.b = 1.01;
    assert(color_is_valid(&c) == false);

    c.b = 0.44;
    assert(color_is_valid(&c) == true);

    c.b = -2.03;
    assert(color_is_valid(&c) == false);

    c.b = 0.22;
    assert(color_is_valid(&c) == true);

    c.a = 1.01;
    assert(color_is_valid(&c) == false);

    c.a = 0.44;
    assert(color_is_valid(&c) == true);

    c.a = -2.03;
    assert(color_is_valid(&c) == false);

    c.a = 0.22;
    assert(color_is_valid(&c) == true);

    color_free(&c);
  }

  {
    color  a;
    color  b;

    a = color_make_rgb(1,0,1);
    b = color_make_rgba(0.1,0.2,0.3,0.4);

    color_copy(&a,&b);

    assert(a.r == 0.1f);
    assert(a.g == 0.2f);
    assert(a.b == 0.3f);
    assert(a.a == 0.4f);

    assert(a.r == b.r);
    assert(a.g == b.g);
    assert(a.b == b.b);
    assert(a.a == b.a);

    color_free(&a);
    color_free(&b);
  }

  {
    color a;
    color b;

    a = color_make_rgba(1,0,1,0);
    b = color_make_rgba(0,1,0,1);

    assert(color_distance(&a,&b) == 4);

    color_copy(&a,&b);

    assert(color_distance(&a,&b) == 0);

    color_free(&a);
    color_free(&b);
  }

  return 0;
}
