#include "flanterm/flanterm.h"
void kprintf(struct flanterm_context *ctx, char const *fmt,...);
/* just a wrapper over nanoprintf for quality of life */
void kerror(char error[]);
void kdebug(char debug[]);
