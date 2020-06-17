#pragma once

#include <cstdint>
#include <compat/astring.h>

class ESPEmu {
public:
  uint64_t getEfuseMac() { return 0; }
};

extern ESPEmu ESP;