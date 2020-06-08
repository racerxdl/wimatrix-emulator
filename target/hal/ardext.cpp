#include <ardext.h>
#include <cstddef>
#include <cstdio>

static void             (*_printfn      )(const char *) = NULL;
static void             (*_seteeprom    )(int addr, char data) = NULL;
static char             (*_readeeprom   )(int addr) = NULL;

static int              (*_connclose    )(int fd) = NULL;
static int              (*_connopen     )(const char *host, int port) = NULL;
static int              (*_connwrite    )(int fd, const char *buf, int count) = NULL;
static int              (*_connread     )(int fd, char *buf, int count) = NULL;
static int              (*_connpeek     )(int fd) = NULL;
static int              (*_connavailable)(int fd) = NULL;

void setFunction(int functionId, void *func) {
  switch (functionId) {
    case FN_PRINT:
      _printfn = (void (*)(const char *))func;
      break;
    case FN_SET_EEPROM:
      _seteeprom = (void (*)(int, char))func;
      break;
    case FN_GET_EEPROM:
      _readeeprom = (char (*)(int))func;
      break;
    case FN_CONN_CLOSE:
      _connclose = (int (*)(int))func;
      break;
    case FN_CONN_OPEN:
      _connopen = (int (*)(const char *, int) )func;
      break;
    case FN_CONN_WRITE:
      _connwrite = (int (*)(int, const char *, int))func;
      break;
    case FN_CONN_READ:
      _connread = (int (*)(int, char *, int))func;
      break;
    case FN_CONN_PEEK:
      _connpeek = (int (*)(int))func;
      break;
    case FN_CONN_AVAILABLE:
      _connavailable = (int (*)(int))func;
      break;
  }
}

void extprint(const char *str) {
  if (_printfn != NULL) {
    _printfn(str);
  }
}

void extseteeprom(int addr, char data) {
  if (_seteeprom != NULL) {
    _seteeprom(addr, data);
  }
}

char extreadeeprom(int addr) {
  if (_readeeprom != NULL) {
    return _readeeprom(addr);
  }

  return 0x00;
}

int extconnclose(int fd)  {
  if (_connclose != NULL) {
    return _connclose(fd) ;
  }

  return -1;
}

int extconnopen(const char *host, int port)  {
  if (_connopen != NULL) {
    return _connopen(host, port);
  }

  return -1;
}

int extconnwrite(int fd, const char *buf, int count)  {
  if (_connwrite != NULL) {
    return _connwrite(fd, buf, count);
  }

  return -1;
}

int extconnread(int fd, char *buf, int count)  {
  if (_connread != NULL) {
    return _connread(fd, buf, count) ;
  }

  return -1;
}

int extconnpeek(int fd)  {
  if (_connpeek != NULL) {
    _connpeek(fd) ;
  }

  return -1;
}

int extconnavailable(int fd)  {
  if (_connavailable != NULL) {
    return _connavailable(fd) ;
  }

  return -1;
}
