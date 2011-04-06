#include <stdio.h>
#include <assert.h>

#include "color.h"

int
main(
  int argc,
  char** argv)
{
  {
    color  a;

    a = color_rgb(0,0.5,0.77);

    assert(a.r == 0.0f);
    assert(a.g == 0.5f);
    assert(a.b == 0.77f);
    assert(a.a == 1.0f);
  }

  {
    color  a;

    a = color_rgba(0,0.23,0.71,0.44);

    assert(a.r == 0.0f);
    assert(a.g == 0.23f);
    assert(a.b == 0.71f);
    assert(a.a == 0.44f);
  }

  {
    color  a;

    a = color_rgba(0,0.11,0.73,0.88);

    assert(color_is_valid(&a) == true);

    a.r = 1.01;
    assert(color_is_valid(&a) == false);

    a.r = 0.44;
    assert(color_is_valid(&a) == true);

    a.r = -2.03;
    assert(color_is_valid(&a) == false);

    a.r = 0.22;
    assert(color_is_valid(&a) == true);

    a.g = 1.01;
    assert(color_is_valid(&a) == false);

    a.g = 0.44;
    assert(color_is_valid(&a) == true);

    a.g = -2.03;
    assert(color_is_valid(&a) == false);

    a.g = 0.22;
    assert(color_is_valid(&a) == true);

    a.b = 1.01;
    assert(color_is_valid(&a) == false);

    a.b = 0.44;
    assert(color_is_valid(&a) == true);

    a.b = -2.03;
    assert(color_is_valid(&a) == false);

    a.b = 0.22;
    assert(color_is_valid(&a) == true);

    a.a = 1.01;
    assert(color_is_valid(&a) == false);

    a.a = 0.44;
    assert(color_is_valid(&a) == true);

    a.a = -2.03;
    assert(color_is_valid(&a) == false);

    a.a = 0.22;
    assert(color_is_valid(&a) == true);
  }

  {
    color  a;
    color  b;

    a = color_rgb(1,0,1);
    b = color_rgba(0.1,0.2,0.3,0.4);

    color_copy(&a,&b);

    assert(a.r == 0.1f);
    assert(a.g == 0.2f);
    assert(a.b == 0.3f);
    assert(a.a == 0.4f);

    assert(a.r == b.r);
    assert(a.g == b.g);
    assert(a.b == b.b);
    assert(a.a == b.a);
  }

  {
    color a;
    color b;

    a = color_rgba(1,0,1,0);
    b = color_rgba(0,1,0,1);

    assert(color_distance(&a,&b) == 4);

    color_copy(&a,&b);

    assert(color_distance(&a,&b) == 0);
  }

  return 0;
}
