#include <stdlib.h>

#include "color.h"
#include "utils.h"

color
color_rgb(
  float r,
  float g,
  float b)
{
  assert(r >= 0 && r <= 1);
  assert(g >= 0 && g <= 1);
  assert(b >= 0 && b <= 1);

  color  new_color;

  new_color.r = r;
  new_color.g = g;
  new_color.b = b;
  new_color.a = 1;

  return new_color;
}

color
color_rgba(
  float r,
  float g,
  float b,
  float a)
{
  assert(r >= 0 && r <= 1);
  assert(g >= 0 && g <= 1);
  assert(b >= 0 && b <= 1);
  assert(a >= 0 && a <= 1);

  color  new_color;

  new_color.r = r;
  new_color.g = g;
  new_color.b = b;
  new_color.a = a;

  return new_color;
}


bool
color_is_valid(
  const color* c)
{
  if (c == NULL) {
    return true;
  }

  if (c->r < 0 || c->r > 1) {
    return false;
  }

  if (c->g < 0 || c->g > 1) {
    return false;
  }

  if (c->b < 0 || c->b > 1) {
    return false;
  }

  if (c->a < 0 || c->a > 1) {
    return false;
  }

  return true;
}


color*
color_copy(
  color* dst,
  const color* src)
{
  assert(color_is_valid(dst));
  assert(color_is_valid(src));

  dst->r = src->r;
  dst->g = src->g;
  dst->b = src->b;
  dst->a = src->a;

  return dst;
}

float
color_distance(
  const color* a,
  const color* b)
{
  assert(color_is_valid(a));
  assert(color_is_valid(b));

  float  dst_r;
  float  dst_g;
  float  dst_b;
  float  dst_a;

  dst_r = a->r - b->r;
  dst_g = a->g - b->g;
  dst_b = a->b - b->b;
  dst_a = a->a - b->a;

  return dst_r*dst_r + dst_g*dst_g + dst_b*dst_b + dst_a*dst_a;
}
