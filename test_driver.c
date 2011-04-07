#include <stdio.h>
#include <assert.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "driver.h"

static struct {
  int  a;
  int  b;
} _test1_data;

void
test1_init_cb()
{
  _test1_data.a = 10;
}

void
test1_display_cb()
{
  _test1_data.b = 20;
}

int
test1_frame_cb()
{
  return 0;
}


static struct {
  int  a;
  int  b;
  int  c;
} _test2_data;

void
test2_init_cb()
{
  _test2_data.a = 10;
}

void
test2_display_cb()
{
  _test2_data.b = 20;
  glBegin(GL_QUADS);
  glColor3f(_test2_data.c / 10.0,0,0);
  glVertex2f(-1,-1);
  glVertex2f(-1,1);
  glVertex2f(1,1);
  glVertex2f(1,-1);
  glEnd();
}

int
test2_frame_cb()
{
  if (_test2_data.c < 10) {
    _test2_data.c += 1;
    return 1;
  } else {
    return 0;
  }
}


int
main(
   int argc,
   char** argv)
{
  {
    driver*  drv;

    drv = driver_make(test1_init_cb,test1_display_cb,test1_frame_cb,100);

    driver_start(drv,argc,argv);
    driver_free(drv);

    assert(_test1_data.a == 10);
    assert(_test1_data.b == 20);
  }

  {
    driver* drv;

    drv = driver_make(test2_init_cb,test2_display_cb,test2_frame_cb,250);

    driver_start(drv,argc,argv);
    driver_free(drv);

    assert(_test2_data.a == 10);
    assert(_test2_data.b == 20);
    assert(_test2_data.c == 10);
  }

  return 0;
}