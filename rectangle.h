#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "utils.h"

typedef struct _rectangle  rectangle;

struct _rectangle
{
  float  x;
  float  y;
  float  w;
  float  h;
};

rectangle  rectangle_xywh(float x, float y, float w, float h);
rectangle  rectangle_tlbr(float tl_x, float tl_y, float br_x, float br_y);

bool       rectangle_is_valid(const rectangle* r);

rectangle* rectangle_copy(rectangle* dst, const rectangle* src);

#endif
