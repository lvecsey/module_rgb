module_rgb takes a shared library file, and outputs a 960x960 (by default) .rgb image.

./module_rgb librgbfunc.so | display -size 960x960 rgb:-

You can create any shared library of your choosing so long as it contains the following function:

  #include <sys/types.h>
  int rgbfunc(u_int16_t *rgb, long int xres, long int yres);

module_rgb will write the contents of the rgb array to standard output, for use with display.

Alternatively,

	USE_MMAP=1 ./module_rgb librgbfunc.so img_960x960.rgb
	display -size 960x960 ./img_960x960.rgb




