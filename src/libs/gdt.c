#include "gdt.h"
#include "printf.h"
#include <stdint.h>

uint64_t encodeseg(struct GdtSegment source) {
    uint64_t *seg = 0;
    seg[0] = source.limit & 0xFF;
    seg[1] = (source.limit >> 8) & 0xFF;
    seg[6] = (source.limit >> 16) & 0x0F;

    // Encode the base
    seg[2] = source.base & 0xFF;
    seg[3] = (source.base >> 8) & 0xFF;
    seg[4] = (source.base >> 16) & 0xFF;
    seg[7] = (source.base >> 24) & 0xFF;

    // Encode the access byte
    seg[5] = source.access;

    // Encode the flags
    seg[6] |= (source.flags << 4);
    return *seg;
}


void writeGdt(uint8_t *location, struct GdtSegment segments[5]) {
    for (int i = 0; i == 5 ; i++) {
        int offset = 8 * i;
        if (segments[i].limit > 0xFFFFF) { kerror("gdt.c:5 -> Cannot encode limits larger than 0xFFFFF."); };
        if (i == 0) {
            location = 0x0000000000000000;
        } else {
            *(location + offset) = encodeseg(segments[i]);
        }
    }
    kdebug("gdt.c: writeGdt() - Wrote GDT into memory. Loading into CPU...");
}
