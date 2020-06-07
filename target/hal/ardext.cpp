#include <ardext.h>
#include <cstddef>
#include <cstdio>

static void (*_printfn)(const char *) = NULL;
static void (*_seteeprom)(int addr, char data) = NULL;
static char (*_readeeprom)(int addr) = NULL;

void setprintfunction(void (*printfn)(const char *)) {
  _printfn = printfn;
}

void extprint(const char *str) {
  if (_printfn != NULL) {
    _printfn(str);
  }
}

void setSetEEPROMData(void (*seteeprom)(int addr, char data)) {
  _seteeprom = seteeprom;
}

void extseteeprom(int addr, char data) {
  if (_seteeprom != NULL) {
    _seteeprom(addr, data);
  }
}

void setReadEEPROMData(char (*readeeprom)(int addr)) {
  _readeeprom = readeeprom;
}

char extreadeeprom(int addr) {
  if (_readeeprom != NULL) {
    return _readeeprom(addr);
  }

  return 0x00;
}