#include "flanterm/flanterm.h"
#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 0
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 0
#define NANOPRINTF_IMPLEMENTATION
#include "nanoprintf.h"
static void kputc(int c, void *ctx) {
    flanterm_write(ctx,(const char*)c,sizeof(c));
}

void kprintf(struct flanterm_context *ctx,char toprint[]) {
    /* kernel printf function pass flanterm ctx here */
    npf_pprintf(&kputc,ctx,toprint);
}
