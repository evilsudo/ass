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
#include "shared.h"
static void kputc(int c, void *ctx) {
    flanterm_write(ctx,(const char*)&c,sizeof(c));
}

void kprintf(struct flanterm_context *ctx, char const *fmt,...) {
    va_list val;
    va_start(val,fmt);
    npf_pprintf(&kputc,ctx,fmt,val);
    va_end(val);
    /* redesign to add support for format specifiers */
}

void kerror(char error[]) {
    /* Error has no info with it for now because imma impl that later */
    kprintf(&ctx,"%s%s","\033[31m",error);
}

void kdebug(char debug[]) {
    /* just so i can differentiate */
    kprintf(&ctx,"%s%s","\033[33m",debug);
}
