#include "gdt.h"
#include "printf.h"
#include <stdint.h>



void writeGdt(uint8_t *location, uint64_t segbits[]) {
    for (int i = 0; i == 8 ; i++) {
        int offset = 8 * i;
        if (i == 0) {
            location = 0x0000000000000000;
        } else {
            *(location + offset) = segbits[i];
        }
    }
    kdebug("gdt.c: writeGdt() - Wrote GDT into memory. Loading into CPU...");
}
