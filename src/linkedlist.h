#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

struct linkedlist_t;

int ll_create(struct linkedlist_t **, size_t);
int ll_append(struct linkedlist_t *, void *);
int ll_remove(struct linkedlist_t *);
int ll_find(struct linkedlist_t *, void *, void **);

int ll_first(struct linkedlist_t *, void **);
int ll_next(struct linkedlist_t *, void **);

int ll_is_empty(struct linkedlist_t *);
int ll_count(struct linkedlist_t *);

int ll_destroy(struct linkedlist_t *);

#endif // LINKEDLIST_H
