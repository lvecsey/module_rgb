
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <pthread.h>
#include <time.h>

#define _GNU_SOURCE
#define __USE_GNU
#include <math.h>

#include "rgbfunc.h"

#define sigmoid(x) (1.0 / (1.0 + exp(-x)))

int rgbfunc(u_int16_t *rgb, long int xres, long int yres) {

  long int n;
  long int xpos, ypos;
  double x, y;
  double radians;
  double radius;

  double value;
  u_int16_t mono;

  long int span = xres>>8;

  for (n = 0; n < xres*yres; n++) {

    ypos = n / yres;
    xpos = n - (ypos*xres);

    mono = (n%span) ? 65535 : 0;

    rgb[ypos*xres*3 + xpos*3+0] = mono;
    rgb[ypos*xres*3 + xpos*3+1] = mono;
    rgb[ypos*xres*3 + xpos*3+2] = mono;

  }

  return 0;

}


