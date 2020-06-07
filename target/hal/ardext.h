#ifndef ARDEXT_H
#define ARDEXT_H


#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

void setprintfunction(void (*printfn)(const char *));

#ifdef __cplusplus
}
#endif


void extprint(const char *);

#endif