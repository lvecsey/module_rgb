
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <time.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) {

  long int debug = getenv("DEBUG") != NULL;

  long int use_mmap = getenv("USE_MAAP") != NULL;

  u_int16_t mono;
  long int xres = 960, yres = 960;
  size_t img_sz = xres*yres*sizeof(u_int16_t)*3;
  u_int16_t *rgb;

  void *handle;
  int (*rgbfunc)(u_int16_t *rgb, long int xres, long int yres);

  struct timespec before, after;

  handle = dlopen(argc>1?argv[1]:NULL, RTLD_NOW);
  rgbfunc = dlsym(handle, "rgbfunc");

  clock_gettime(CLOCK_REALTIME, &before);

  if (!use_mmap) { 
    rgb = malloc(img_sz); 
    rgbfunc(rgb, xres, yres);
    write(1,rgb,img_sz);
  }
  else {
    
    mode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH;
    char *filename = argc>2 ? argv[2] : NULL;
    int fd = open(filename,O_RDWR|O_CREAT,mode);
    int ftruncate_retval = ftruncate(fd,img_sz);
    void *m;
    
    m = mmap(NULL, img_sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (m==MAP_FAILED) {
      perror("mmap");
      return -1;
    }

    rgb = (u_int16_t*) m;
    rgbfunc(rgb, xres, yres);

  }

  clock_gettime(CLOCK_REALTIME, &after);

  fprintf(stderr, "%s: Elapsed time, %g seconds.\n", __FUNCTION__, (after.tv_sec + after.tv_nsec / 1000000000.0) - (before.tv_sec + before.tv_nsec / 1000000000.0));

  return 0;

}

      
