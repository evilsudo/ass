#include "printf.h"
#include <stdint.h>

void writeGdt(uint8_t *target, uint64_t segbits[]);
uint64_t encodeseg(uint32_t limit,uint32_t base,uint8_t access,uint8_t flags);
