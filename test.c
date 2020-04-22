#include "lv2/core/lv2.h"

#include <stdio.h>
#include <dlfcn.h>
#include <julia.h>

int main() {
  void *lib;
  int (*myfunc)(int);

  int x, y;

  dlopen("libjulia.so", RTLD_NOW | RTLD_GLOBAL);
  jl_init();
  lib = dlopen("./myscript.so", RTLD_NOW);
  if (lib == NULL) {
    printf("Failed to open lib: %s\n", dlerror());
    return 1;
  }

  myfunc = dlsym(lib, "myfunc");
  if (myfunc == NULL) {
    printf("Failed to open myfunc: %s\n", dlerror());
    return 1;
  }

  printf("Run myfunc\n");
  x = 3;
  y = myfunc(x);
  printf("myfunc(%d) = %d\n", x, y);

  jl_atexit_hook(0);
  dlclose(lib);
}
