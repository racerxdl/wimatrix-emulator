#include <ardext.h>
#include <cstddef>
#include <cstdio>

static void (*_printfn)(const char *) = NULL;

void setprintfunction(void (*printfn)(const char *)) {
  _printfn = printfn;
}

void extprint(const char *str) {
  if (_printfn != NULL) {
    _printfn(str);
  }
}