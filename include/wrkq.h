#ifndef WRKQ_H
#define WRKQ_H

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int foo(void);

struct wrkq_item {
    /* 
     * this function gets invoked with the argument 'arg' once it gets pulled
     * from the work queue
     */
    void *(*func)(void *);

    /* input argument to func */
    void *arg;
};

struct wrkq_result {
    void *value;
    size_t id;
};

struct wrkq_options {
    /* number of worker threads */
    size_t n_workers;

    /* maximum number of items in the work queue */
    size_t queue_depth;
};

struct wrkq_t;

struct wrkq_t *wrkq_new(struct wrkq_options *opt);

void wrkq_destroy(struct wrkq_t *q);

size_t wrkq_nq(struct wrkq_t *q, struct wrkq_item *item);

void wrkq_dq(struct wrkq_t *q, struct wrkq_result *out);

#endif /* WRKQ_H */
