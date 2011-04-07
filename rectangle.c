#include "rectangle.h"

rectangle
rectangle_xywh(
  float x,
  float y,
  float w,
  float h)
{
  assert(w > 0);
  assert(h > 0);

  rectangle  new_r;

  new_r.x = x;
  new_r.y = y;
  new_r.w = w;
  new_r.h = h;

  return new_r;
}

rectangle
rectangle_tlbr(
  float tl_x,
  float tl_y,
  float br_x,
  float br_y)
{
  assert(tl_x < br_x);
  assert(tl_y < br_y);

  rectangle  new_r;

  new_r.x = tl_x;
  new_r.y = tl_y;
  new_r.w = br_x - tl_x;
  new_r.h = br_y - tl_y;

  return new_r;
}


bool
rectangle_is_valid(
  const rectangle* r)
{
  if (r->w < 0) {
    return false;
  }

  if (r->h < 0) {
    return false;
  }

  return true;
}


rectangle*
rectangle_copy(
  rectangle* dst,
  const rectangle* src)
{
  assert(rectangle_is_valid(dst));
  assert(rectangle_is_valid(src));

  dst->x = src->x;
  dst->y = src->y;
  dst->w = src->w;
  dst->h = src->h;

  return dst;
}
