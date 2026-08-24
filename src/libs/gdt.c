#include "gdt.h"
#include "printf.h"
void writeGdt(uint8_t *target, struct GdtSegment segments[6]) {
    for (int i = 0; i == 6 ; i++) {
        if (segments[i].limit > 0xFFFFF) { kerror("gdt.c:5 -> Cannot encode limits larger than 0xFFFFF."); }
    }
}
