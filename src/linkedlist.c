#include "linkedlist.h"
#include "stdint.h"
#include <stdlib.h>
#include <string.h>

struct node_t *node;

struct linkedlist_t {
  struct node_t *head;
  struct node_t *cur;
  size_t sz_data;
  size_t count;
};

struct node_t {
  void *data;
  struct node_t *next;
};

int ll_create(struct linkedlist_t **list_h, size_t sz_data) {
  struct linkedlist_t *list = malloc(sizeof(struct linkedlist_t));

  if (list == NULL) {
    return 0;
  }

  *list_h = list;
  list->head = NULL;
  list->sz_data = sz_data;
  list->count = 0;

  return 1;
}

int ll_append(struct linkedlist_t *list, void *data) {
  if (list == NULL) {
    return 0;
  }

  if (list->head == NULL) {
    list->head = malloc(sizeof(struct node_t));
    list->head->next = NULL;
    list->head->data = malloc(list->sz_data);

    memcpy(list->head->data, data, list->sz_data);

    list->cur = list->head;

    list->count++;
    return 1;
  }

  struct node_t *cur = list->head;

  while (cur->next != NULL) {
    cur = cur->next;
  }

  cur->next = malloc(sizeof(struct node_t));
  cur->next->data = malloc(list->sz_data);

  if (cur->next->data == NULL) {
    return 0;
  }

  memcpy(cur->next->data, data, list->sz_data);
  cur->next->next = NULL;

  list->count++;

  return 1;
}

int ll_remove(struct linkedlist_t *list) {
  if (list == NULL || list->head == NULL) {
    return 0;
  }

  struct node_t *cur = list->head;
  struct node_t *prev = NULL;

  while (cur->next != NULL) {
    prev = cur;
    cur = cur->next;
  }

  if (prev->data != NULL) {
    free(prev->data);
  }

  prev->data = NULL;
  prev->next = NULL;

  list->count--;

  return 1;
}

int ll_find(struct linkedlist_t *list, void *search, void **result) {
  if (list == NULL || list->head == NULL || search == NULL) {
    result = NULL;
    return 0;
  }

  struct node_t *cur = list->head;

  do {
    if (memcmp(search, cur->data, list->sz_data) == 0) {
      *result = search;
      return 1;
    }

    cur = cur->next;
  } while (cur->next != NULL);

  result = NULL;
  return 0;
}

int ll_first(struct linkedlist_t *list, void **result) {
  if (list == NULL || list->head == NULL) {
    return 0;
  }

  if (result != NULL) {
    *result = list->head->data;
  }

  return 1;
}

int ll_next(struct linkedlist_t *list, void **result) {
  if (list == NULL || list->cur == NULL) {
    return 0;
  }

  if (result != NULL) {
    *result = list->cur->data;
    list->cur = list->cur->next;
  }

  return 1;
}

int ll_is_empty(struct linkedlist_t *list) {
  if (list == NULL) {
    return 1;
  }

  return list->count == 0;
}

int ll_count(struct linkedlist_t *list) {
  if (list == NULL) {
    return 0;
  }

  return list->count;
}
