#include <dlfcn.h>
#include <string.h>

typedef int (*unlink_type)(const char *);

int unlink(const char *pathname) {
  if (strstr(pathname, "PROTECT") != NULL) {
    return 0;
  }
  int res = ((unlink_type)(dlsym(RTLD_NEXT, "unlink")))(pathname);
  return res;
}
