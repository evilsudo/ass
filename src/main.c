#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "libs/limine.h"
#include "libs/printf.h"
#include "libs/shared.h"
#include "libs/gdt.h"
#define NANOPRINTF_IMPLEMENTATION

extern void setGdt(uint16_t limit, uint32_t base);
extern void updateSegs();
static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

uint64_t segments[] = {
    0x0000000000000000, /* null */
    0x00009a000000ffff, /* 16-bit code and data */
    0x000093000000ffff,
    0x00cf9a000000ffff, /* 32-bit code and data */
    0x00cf93000000ffff,
    0x00af9b000000ffff, /* 64-bit code and data */
    0x00af93000000ffff,
    0x00affb000000ffff, /* usermode code and data */
    0x00aff3000000ffff,
};

// Set the base revision to 6, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.
__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);
// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.
/* just the first framebuffer, temporary for now */


// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// Implement them as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!
// They CAN be moved to a different .c file.

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
    uint8_t *restrict pdest = dest;
    const uint8_t *restrict psrc = src;

    for (size_t i = 0; i < n; i++) {
        pdest[i] = psrc[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *p = s;

    for (size_t i = 0; i < n; i++) {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pdest = dest;
    const uint8_t *psrc = src;

    if ((uintptr_t)src > (uintptr_t)dest) {
        for (size_t i = 0; i < n; i++) {
            pdest[i] = psrc[i];
        }
    } else if ((uintptr_t)src < (uintptr_t)dest) {
        for (size_t i = n; i > 0; i--) {
            pdest[i-1] = psrc[i-1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = s1;
    const uint8_t *p2 = s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

// Halt and catch fire function.i

// The following will be our kernel's entry point.
// If renaming kmain() to something else, make sure to change the
// linker script accordingly.
void kmain(void) {
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
        hcf();
    }
    kprintf(&ctx, "%s","Hello world from (variadic) kprintf!!");
    uint8_t addr_raw = 0xF0;
    uint8_t *addr = &addr_raw;
    writeGdt(addr,segments);
    setGdt(0xF0, 0x138);
    updateSegs();
    hcf();
}
