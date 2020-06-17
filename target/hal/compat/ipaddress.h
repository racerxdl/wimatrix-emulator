#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <cstddef>
#include <cstdint>
#include <compat/astring.h>
#include <compat/stringable.h>

class IPAddress : public Stringable {
private:
    union {
        uint8_t bytes[4];  // IPv4 address
        uint32_t dword;
    } address;
public:
    IPAddress() : IPAddress(0,0,0,0) {}
    IPAddress(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);
    IPAddress(uint32_t address);
    IPAddress(const uint8_t *address);
    IPAddress(const char *address);

    bool fromString(const char *address);
    bool fromString(const String &address) { return fromString(address.c_str()); }

    operator uint32_t() const { return address.dword; }
    bool operator==(const IPAddress& addr) const { return address.dword == addr.address.dword; }
    bool operator==(const uint8_t* addr) const {
      return  address.bytes[0] == addr[0] &&
              address.bytes[1] == addr[1] &&
              address.bytes[2] == addr[2] &&
              address.bytes[3] == addr[3];
    }

    uint8_t operator[](int index) const { return address.bytes[index]; }

    IPAddress& operator=(uint32_t address);

    virtual String toString() const;

    uint8_t* raw_address() {
        return address.bytes;
    }
};

#endif
