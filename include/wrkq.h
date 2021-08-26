#ifndef WRKQ_H
#define WRKQ_H

int foo(void);

struct wrkq_item {
    /* 
     * this function gets invoked with the argument 'arg' once it gets pulled
     * from the work queue
     */
    void (*func)(void *);

    /* input argument to func */
    void *arg;
};

struct wrkq_options {
    /* number of worker threads */
    size_t n_workers;

    /* maximum number of items in the work queue */
    size_t q_depth;
};

struct wrkq_t {
    struct wrkq_item *queue;
    pthread_t *threads;
    size_t n_workers;
    size_t q_depth;
    size_t q_index;
};

struct wrkq_t *wrkq_new(struct wrkq_options *opt);

void wrkq_destroy(struct wrkq_t *q);

#endif /* WRKQ_H */
