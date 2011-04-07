#include <setjmp.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "driver.h"

struct _driver
{
  bool            running;
  driver_init     init_cb;
  driver_display  display_cb;
  driver_frame    frame_cb;
  int             ms_per_frame;
  jmp_buf         glut_return_env;
};

static struct {
  int      started;
  driver*  drv;
  int      w_id;
} _glut_state = {
  .started = false,
  .drv = NULL,
  .w_id = -1
};

static void
_glut_display_cb()
{
  assert(_glut_state.started);
  assert(driver_is_valid(_glut_state.drv));
  assert(_glut_state.w_id > 0);

  glClear(GL_COLOR_BUFFER_BIT);

  if (_glut_state.drv->display_cb != NULL) {
    _glut_state.drv->display_cb();
  }

  glutSwapBuffers();
}

static void
_glut_frame_cb()
{
  assert(_glut_state.started);
  assert(driver_is_valid(_glut_state.drv));
  assert(_glut_state.w_id > 0);

  int  next;

  if (_glut_state.drv->frame_cb != NULL) {
    next = _glut_state.drv->frame_cb();
    glutPostRedisplay();

    if (next != 0) {
      glutTimerFunc(_glut_state.drv->ms_per_frame,_glut_frame_cb,0);
    } else {
      glutHideWindow();
      longjmp(_glut_state.drv->glut_return_env,1);
    }
  }
}

driver*
driver_make(
  driver_init init,
  driver_display display,
  driver_frame frame,
  int ms_per_frame)
{
  assert(ms_per_frame > 0);

  driver*  new_drv;

  new_drv = malloc(sizeof(driver));

  new_drv->running = false;
  new_drv->init_cb = init;
  new_drv->display_cb = display;
  new_drv->frame_cb = frame;
  new_drv->ms_per_frame = ms_per_frame;
  
  return new_drv;
}

void
driver_free(
  driver* drv)
{
  assert(driver_is_valid(drv));

  if (drv->running) {
    assert(0);
  }

  drv->running = false;
  drv->init_cb = NULL;
  drv->display_cb = NULL;
  drv->frame_cb = NULL;
  drv->ms_per_frame = -1;

  free(drv);
}


bool
driver_is_valid(const driver* drv)
{
  if (drv == NULL) {
    return false;
  }

  if (drv->ms_per_frame < 1) {
    return false;
  }

  return true;
}


driver*
driver_start(
  driver* drv,
  int argc,
  char** argv)
{
  assert(driver_is_valid(drv));
  assert(argc > 0);
  assert(argv != NULL);
  assert(argv[0] != NULL);
  assert(argv[0][0] != '\0');
  assert(_glut_state.drv == NULL);

  volatile int  jmp_ret;

  if (!_glut_state.started) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);

    _glut_state.started = true;
    _glut_state.drv = drv;
    _glut_state.w_id = glutCreateWindow("ShowNTell");

    glutDisplayFunc(_glut_display_cb);
  } else {
    _glut_state.drv = drv;
  }

  glClearColor(0,0,0,0);
  glLoadIdentity();
  glOrtho(-1,1,-1,1,-1,1);
  glScalef(2,2,1);
  glTranslatef(-0.5,0.5,0);
  glRotatef(180,1,0,0);
  
  glEnable(GL_TEXTURE_2D);

  if (drv->init_cb != NULL) {
    drv->init_cb();
  }

  if (drv->display_cb != NULL) {
    glClear(GL_COLOR_BUFFER_BIT);
    drv->display_cb();
    glutSwapBuffers();
  }

  jmp_ret = setjmp(drv->glut_return_env);

  if (jmp_ret == 0) {
    drv->running = true;
    glutTimerFunc(drv->ms_per_frame,_glut_frame_cb,0);
    glutShowWindow();
    glutFullScreen();
    glutMainLoop();
  } else {
    drv->running = false;
  }

  _glut_state.drv = NULL;

  return drv;
}
