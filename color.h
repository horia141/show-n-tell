#ifndef _COLOR_H
#define _COLOR_H

#include <stdbool.h>

typedef struct _color  color;

struct _color
{
  float  r;
  float  g;
  float  b;
  float  a;
};

color   color_rgb(float r, float g, float b);
color   color_rgba(float r, float g, float b, float a);

bool    color_is_valid(const color* c);

color*  color_copy(color* dst, const color* src);
float   color_distance(const color* a, const color* b);

#endif
