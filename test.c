#include "lv2/core/lv2.h"

#include <stdio.h>
#include <dlfcn.h>
#include <julia.h>

int main() {
  void *lib;
  int (*myfunc)(int);
  jl_function_t *jmyfunc;

  int x1, y1;
  int x2, y2;
  jl_value_t *jx, *jy;

  dlopen("libjulia.so", RTLD_NOW | RTLD_GLOBAL);
  jl_init();

  jmyfunc = (jl_function_t*)jl_eval_string(
      "include(\"./myscript.jl\"); myfunc"
  );

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

  printf("\nCalling myfunc with jl_call1 succeeds\n");
  x1 = 13;
  jx = jl_box_int32(x1);
  jy = jl_call1(jmyfunc, jx);
  y1 = jl_unbox_int32(jy);
  printf("jmyfunc(%d) = %d\n\n", x1, y1);


  printf("But calling myfunc directly segfaults\n");
  x2 = 3;
  y2 = myfunc(x2);
  printf("myfunc(%d) = %d\n\n", x2, y2);

  jl_atexit_hook(0);
  dlclose(lib);
}
