#pragma once
#include <stdint.h>

#define ptr_of_ptr(obj) (struct list_node **)obj
#define ptr_list(obj) (struct list_node*)obj
#define ez_append_list(list,item) list_append(ptr_of_ptr(&list),(struct list_node*)item)
#define ez_reverse_list(list) list_inverter(ptr_of_ptr(&list))


struct list_node{
    struct list_node *next;
};

// struct generic_item{
//     struct list_node node;
//     uint8_t item; 
// }

struct string_item
{
 struct list_node node;
 const char* string;
};

struct list_node *list_get_tail(struct list_node **head);
struct list_node *list_append(struct list_node **head, struct list_node *item);
struct list_node *list_pop(struct list_node **head);
struct list_node *list_remove(struct list_node **list, struct list_node *item);
struct list_node *list_inverter(struct list_node ** list);