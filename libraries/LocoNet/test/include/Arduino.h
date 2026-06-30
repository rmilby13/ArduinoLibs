#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

using uint = unsigned int;
using byte = uint8_t;

// Minimal Arduino-like helpers used by the library
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitRead(value, bit) (((value) >> (bit)) & 1)

namespace arduino {
    using String = std::string;
}

// Minimal Serial stub (not used unless DEBUG enabled)
struct _Serial {
    template<typename... Args>
    void printf(const char*, Args...) {}
    template<typename T>
    void print(T) {}
    template<typename T>
    void println(T) {}
};

static _Serial Serial;

// Provide macros used in code
#define HIGH 0x1
#define LOW  0x0

