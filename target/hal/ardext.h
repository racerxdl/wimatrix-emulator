#ifndef ARDEXT_H
#define ARDEXT_H

#include <cstdint>

#define FN_PRINT             0
#define FN_SET_EEPROM        1
#define FN_GET_EEPROM        2
#define FN_CONN_CLOSE        3
#define FN_CONN_OPEN         4
#define FN_CONN_WRITE        5
#define FN_CONN_READ         6
#define FN_CONN_PEEK         7
#define FN_CONN_AVAILABLE    8
#define FN_PUT_PIXEL         9
#define FN_END_PANEL_UPDATE 10
#define FN_CONN_SETTIMEOUT  11
#define FN_CONN_OPENUDP     12
#define FN_CONN_READPACKET  13
#define FN_CONN_WRITETO     14

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

void setFunction(int functionId, void *func);

#ifdef __cplusplus
}
#endif

int               extconnclose      (int fd);
int               extconnopen       (const char *host, int port) ;
int               extconnwrite      (int fd, const char *buf, int count);
int               extconnread       (int fd, char *buf, int count);
int               extconnpeek       (int fd);
int               extconnavailable  (int fd);
int               extconnsettimeout (int fd, unsigned long millis);
int               extconnopenudp    (const char *host, int port) ;
int               extconnreadpacket (int fd, char *buf, int buflen, char *rhost, int rhostlen, int *rport);
int               extconnwriteto    (int fd, char *buf, int count, const char *host, int port);

void              extprint          (const char *);
void              extseteeprom      (int addr, char data);
char              extreadeeprom     (int addr);
void              extputpixel       (uint32_t pix);
void              extendpanelupdate ();

#endif
