#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <wrkq.h>

int foo(void) {
    puts("called foo");
    return 42;
}

/*
 * TODO: create ring buffer
 */
/*
 * Producer-consumer model
 *
 * The locking gets pretty hairy here, best to use an existing algorithm
 * that is known to work (see multi producer/consumer example)
 * https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem#Using_semaphores
 */
static void *producer(void *args) {
#define UNUSED(A) (void)(A)
    UNUSED(args);
#undef UNUSED
    for (;;) {
        /*
         * data = produce_item()
         * sem_wait(empty_count)
         * lock(buffer_mutex)
         * put_item_in_buffer(data)
         * unlock(buffer_mutex)
         * sem_post(fill_count)
         */
    }
    return NULL;
}

static void *consumer(void) {
    /*
     * sem_wait(fill_count)
     * lock(buffer_mutex)
     * item = remove_item_from_buffer()
     * unlock(buffer_mutex)
     * sem_post(empty_count)
     * return item
     */
    return NULL;
}

static void *wrkq_thread_loop(void *args) {
    struct work_t *q = args;
#define UNUSED(A) (void)(A)
    UNUSED(q);
#undef UNUSED
    /* TODO: wait for ring buffer to unlock */
    return NULL;
}

struct wrkq_t *wrkq_new(struct wrkq_options *opt) {
    struct wrkq_item *queue = NULL;
    struct wrkq_t *q = NULL;
    pthread_t *threads = NULL;
    size_t i;

#define UNUSED(A) (void)(A)
    UNUSED(consumer);
    UNUSED(producer);
#undef UNUSED
    
    q = malloc(sizeof(*q));
    if (!q) {
        goto fail;
    }
    q->n_workers = opt->n_workers;
    q->q_depth = opt->q_depth;

    queue = malloc(sizeof(*queue) * opt->q_depth);
    if (!queue) {
        goto fail;
    }
    q->queue = queue;
    q->q_index = 0;

    threads = malloc(sizeof(*threads) * opt->n_workers);
    if (!threads) {
        goto fail;
    }
    q->threads = threads;

    /* TODO: setup ring buffer */
    for (i = 0; i < opt->n_workers; i++) {
        int status = pthread_create(&threads[i], NULL, wrkq_thread_loop, NULL);
        if (status) {
            perror("wrkq: failed to create thread");
            goto fail; /* TODO: how to handle failed threads? */
        } else {
            pthread_detach(threads[i]);
        }
    }
    
    return q;

fail:
    free(q);
    free(queue);
    free(threads);
    return NULL;
}

void wrkq_destroy(struct wrkq_t *q) {
    free(q->queue);
    free(q);
}
