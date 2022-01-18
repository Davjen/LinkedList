#pragma once
#include <stdint.h>

#define ptr_of_ptr(obj) (struct list_node_double**)obj
#define ptr_list(obj) (struct list_node_double*)obj



typedef struct list_node_double
{
 struct list_node_double *prev;
 struct list_node_double *next;
}dlist_node_t;

typedef struct string_item_double
{
 struct list_node_double node;
 const char* string;
}dstring_item_t;

dlist_node_t *list_append (dlist_node_t **head, dlist_node_t *item);
dstring_item_t *string_item_new(const char *string);
dlist_node_t *list_pop(dlist_node_t **head);
int check_item(dlist_node_t **list_to_check, dlist_node_t *item_to_check);
void insert_before(dlist_node_t **list,dlist_node_t *item_to_insert,dlist_node_t *next_item);
void print_list(dlist_node_t *list);
void list_remove(dlist_node_t **list, dlist_node_t *item);
dlist_node_t *list_get_tail(dlist_node_t **head);
void insert_after(dlist_node_t **list,dlist_node_t *item_to_insert,dlist_node_t *prev_item);