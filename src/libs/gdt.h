#include "printf.h"
#include <stdint.h>

struct GdtSegment {
    uint32_t limit;
    uint32_t base;
    uint8_t access;
    uint8_t flags;
};

void writeGdt(uint8_t *target, struct GdtSegment segments[6]);
