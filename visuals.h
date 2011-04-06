#ifndef _VISUALS_H
#define _VISUALS_H

#include "utils.h"

typedef void            (*visuals_init_cb)(void);
typedef void            (*visuals_display_cb)(void);
typedef int             (*visuals_frame_cb)(void);
typedef struct _visuals   visuals;

visuals*  visuals_make(int argc, char** argv, visuals_init_cb init_cb,
		       visuals_display_cb display_cb, visuals_frame_cb frame_cb,
		       int ms_per_frame);
void      visuals_free(visuals* v);

bool      visuals_is_valid(const visuals* v);

#endif
