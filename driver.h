#ifndef _DRIVER_H
#define _DRIVER_H

#include "utils.h"

typedef void          (*driver_init)(void);
typedef void          (*driver_display)(void);
typedef int           (*driver_frame)(void);
typedef struct _driver  driver;

driver*  driver_make(driver_init init, driver_display display, driver_frame frame, int ms_per_frame);
void     driver_free(driver* drv);

bool     driver_is_valid(const driver* drv);

driver*  driver_start(driver* drv, int argc, char** argv);

#endif
