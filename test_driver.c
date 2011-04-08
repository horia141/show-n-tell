#include <stdio.h>
#include <assert.h>

#include "driver.h"

static int
test1_frame_cb()
{
  return 0;
}

static struct {
  int  curr_iteration
} _test2_data = {
  .curr_iteration = 0
};

static int
test2_frame_cb()
{
  if (_test2_data.curr_iteration < 10) {
    _test2_data.curr_iteration += 1;
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

    drv = driver_make(test1_frame_cb,10);

    assert(driver_is_valid(drv));

    driver_start(drv);
    driver_free(drv);
  }

  {
    driver*  drv;
    image*   texture;
    tquad*   tq1;
    tquad*   tq2;

    drv = driver_make(test2_frame_cb,250);

    assert(driver_is_valid(drv));

    texture = image_from_ppm_t("test_driver.ppm");
    tq1 = driver_tquad_make_color(drv,&(rectangle){0.22,0.44,0.11,0.11},4,4,&(color){1,0,0,1});
    tq2 = driver_tquad_make_image(drv,&(rectangle){0.54,0.82,0.11,0.10},texture);

    assert(tquad_is_valid(tq1));
    assert(tquad_is_valid(tq2));

    image_free(texture);
    driver_start(drv);
    driver_free(drv);
  }

  return 0;
}
