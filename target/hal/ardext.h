#ifndef ARDEXT_H
#define ARDEXT_H


#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

void setprintfunction(void (*printfn)(const char *));
void setSetEEPROMData(void (*seteeprom)(int addr, char data));
void setReadEEPROMData(char (*readeeprom)(int addr));

#ifdef __cplusplus
}
#endif


void extprint(const char *);
void extseteeprom(int addr, char data);
char extreadeeprom(int addr);

#endif