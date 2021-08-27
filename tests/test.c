#include <stdio.h>
#include <stdlib.h>
#include <wrkq.h>

void *hello(void *ptr) {
#define UNUSED(A) (void)(A)
    UNUSED(ptr);
#undef UNUSED
    puts("*** HELLO WORLD ***");
    return NULL;
}

int main(void) {
    struct wrkq_options opt;
    struct wrkq_t *q = NULL;
    size_t i;
    struct wrkq_item *items = malloc(1000 * sizeof(*items));

    opt.n_workers = 16;
    opt.queue_depth = 255;
    q = wrkq_new(&opt);

    for (i = 0; i < 1000; i++) {
        items[i].func = hello;
        items[i].arg = NULL;
        wrkq_nq(q, &items[i]);
    }

    wrkq_destroy(q);
    free(items);
    return 0;
}
