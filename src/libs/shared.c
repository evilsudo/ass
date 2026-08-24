#include "flanterm/flanterm.h"
#include "flanterm/flanterm_backends/fb.h"
#include "limine.h"
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

struct flanterm_context *ctx;
void GetFramebuffer() {
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
    ctx = flanterm_fb_init(
        NULL,
        NULL,
        framebuffer-> address, framebuffer -> width, framebuffer -> height, framebuffer -> pitch,
        framebuffer -> red_mask_size, framebuffer -> red_mask_shift,
        framebuffer -> green_mask_size, framebuffer -> green_mask_shift,
        framebuffer -> blue_mask_size, framebuffer -> blue_mask_shift,
        NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, 0, 0, 1,
        0, 0,
        0,
        0,
        true
    );
}
