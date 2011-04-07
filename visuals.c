#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "visuals.h"

static struct _visuals
{
  int                 w_id;
  visuals_init_cb     init_cb;
  visuals_display_cb  display_cb;
  visuals_frame_cb    frame_cb;
  int                 ms_per_frame;
  bool                running;
} _visuals_s = {
  .w_id         = -1,
  .init_cb      = NULL,
  .display_cb   = NULL,
  .frame_cb     = NULL,
  .ms_per_frame = 20,
  .running      = false
};

void
_visuals_display_cb()
{
  assert(visuals_is_valid(&_visuals_s));

  glClear(GL_COLOR_BUFFER_BIT);

  if (_visuals_s.display_cb != NULL) {
    _visuals_s.display_cb();
  }

  glutSwapBuffers();
}

void
_visuals_frame_cb()
{
  assert(visuals_is_valid(&_visuals_s));

  int  next;

  if (_visuals_s.frame_cb != NULL) {
    next = _visuals_s.frame_cb();

    glutPostRedisplay();

    if (next != 0) {
      glutTimerFunc(_visuals_s.ms_per_frame,_visuals_frame_cb,0);
    } else {
      glutDestroyWindow(_visuals_s.w_id);
    }
  }
}


visuals*
visuals_make(
  int argc,
  char** argv,
  visuals_init_cb init_cb,
  visuals_display_cb display_cb,
  visuals_frame_cb frame_cb,
  int ms_per_frame)
{
  assert(_visuals_s.running == false);
  assert(argc > 0);
  assert(argv != NULL);
  assert(argv[0] != NULL);
  assert(argv[0][0] != '\0');
  assert(ms_per_frame > 0);

  _visuals_s.w_id = -1;
  _visuals_s.init_cb = init_cb;
  _visuals_s.display_cb = display_cb;
  _visuals_s.frame_cb = frame_cb;
  _visuals_s.ms_per_frame = ms_per_frame;
  _visuals_s.running = true;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  _visuals_s.w_id = glutCreateWindow("Visuals");
  glutDisplayFunc(_visuals_display_cb);

  glClearColor(0,0,0,0);
  glLoadIdentity();
  glOrtho(-1,1,-1,1,-1,1);
  glScalef(2,2,1);
  glTranslatef(-0.5,0.5,0);
  glRotatef(180,1,0,0);
  
  glEnable(GL_TEXTURE_2D);

  if (_visuals_s.init_cb != NULL) {
    _visuals_s.init_cb();
  }

  glutTimerFunc(_visuals_s.ms_per_frame,_visuals_frame_cb,0);
  glutMainLoop();

  return &_visuals_s;
}

void
visuals_free(
  visuals* v)
{
  assert(visuals_is_valid(v));

  _visuals_s.w_id = -1;
  _visuals_s.init_cb = NULL;
  _visuals_s.frame_cb = NULL;
  _visuals_s.ms_per_frame = -1;
  _visuals_s.running = false;
}


bool
visuals_is_valid(
  const visuals* v)
{
  if (v != &_visuals_s) {
    return false;
  }

  if (_visuals_s.w_id <= 0) {
    return false;
  }

  if (_visuals_s.ms_per_frame <= 0) {
    return false;
  }

  if (_visuals_s.running == false) {
    return false;
  }

  return true;
}
