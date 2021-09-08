#include <stdio.h>
#include <stdlib.h>
#include <wrkq.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int global = 0;

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

    opt.n_workers = 16;
    opt.queue_depth = 255;
    q = wrkq_new(&opt);

    for (i = 0; i < 1000; i++) {
        struct wrkq_job job;
        job.func = hello;
        job.arg = NULL;
        wrkq_nq(q, job);
    }

    sleep(1);
    wrkq_destroy(q);
    return 0;
}
