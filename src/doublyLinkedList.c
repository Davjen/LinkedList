#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <doublyLinkedList.h>

dlist_node_t *list_append(dlist_node_t **head, dlist_node_t *item)
{
    dlist_node_t *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

dstring_item_t *string_item_new(const char *string)
{
    dstring_item_t *item = malloc(sizeof(dstring_item_t));
    if (!item)
    {
        return NULL;
    }

    item->string = string; //
    return item;
}

dlist_node_t *list_pop(dlist_node_t **head)
{
    dlist_node_t *current_head = *head;

    if (!current_head)
        return NULL;

    *head = (*head)->next;
    current_head->next = NULL;
    (*head)->prev = NULL;

    return current_head;
}

dlist_node_t *list_get_tail(dlist_node_t **head)
{

    dlist_node_t *current_node = *head;
    dlist_node_t *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

int check_item(dlist_node_t **list_to_check, dlist_node_t *item_to_check)
{

    dlist_node_t *current_item = *list_to_check;
    dlist_node_t *last_node = NULL;

    while (current_item)
    {
        if (current_item == item_to_check)
        {
            return 1;
        }
        last_node = current_item;
        current_item = current_item->next;
    }

    return 0;
}




void list_insert_before(dlist_node_t **head, dlist_node_t *item, dlist_node_t *item_to_insert)
{
    if (item_to_insert == item)
    {
        return;
    }
    if (item->prev)
    {
        item_to_insert->prev = item->prev;
        (item->prev)->next = item_to_insert;
    }
    else
    {
        *head = item_to_insert;
        item_to_insert->prev = NULL;
    }
    item_to_insert->next = item;
    item->prev = item_to_insert;

    return;
}


void insert_after(dlist_node_t **list, dlist_node_t *item_to_insert, dlist_node_t *prev_item)
{
    dlist_node_t *first_item = *list;

    if (!first_item)
    {
        perror("No List");
        return;
    }
    if (check_item(list, prev_item) == 0)
    {
        perror("prev item doesn't exist!");
        return;
    }

    if (prev_item->next == NULL)
    {
        //LAST Element

        item_to_insert->next = NULL;
        item_to_insert->prev = prev_item;

        prev_item->next = item_to_insert;
        return;
        //printf(*list);
    }

    // 0 1 2 3
    // 0 1 5 2 3

    prev_item->next->prev = item_to_insert;
    item_to_insert->next = prev_item->next;
    prev_item->next = item_to_insert;
    item_to_insert->prev = prev_item;

    return;
}

void print_list(dlist_node_t *list)
{

    dstring_item_t *list_item = (dstring_item_t *)list;
    while (list)
    {
        printf("%s\n", list_item->string);
        list_item = (dstring_item_t *)list_item->node.next;
    }
}

void list_remove(dlist_node_t **list, dlist_node_t *item)
{

    dlist_node_t *tmp_list = *list;

    if (!tmp_list)
    {
        perror("List is Empty");
        return; // Lista vuota
    }

    if (check_item(list, item) == 0)
    {
        perror("Item is not contained");
        return; //l'oggetto non esiste
    }

    if (tmp_list == item)
    {
        list_pop(list);
        return;
    } // faccio riferimento al primo valore

    (item->prev)->next = item->next;
    if (item->next != NULL)
    {

        (item->next)->prev = item->prev;
    }

    //cleaning the removed item
    item->prev = NULL;
    item->next = NULL;
    return;
}


dlist_node_t *get_item_with_index(dlist_node_t **list, int position)
{
    int size = get_list_size(list);
    if (position >= size || position < 0)
    {
        perror("Posizione sbagliata");
        return NULL;
    }

    dlist_node_t *current_node = *list;
    // dlist_node_t *last_node = NULL;

    for (int i = 0; i < position; i++)
    {
        // last_node = current_node;
        current_node = current_node->next;
    }

    return current_node;
}

void print_string_from_list(dlist_node_t *node)
{
    printf("%s", ((dstring_item_t *)node)->string);
}

int get_list_size(dlist_node_t **list)
{
    dlist_node_t *head = *list;

    if (!head)
    {
        return 0;
    }

    int counter = 0;
    while (head)
    {
        counter++;
        head = head->next;
    }

    return counter;
}

void randomizer_list(dlist_node_t **list)
{

    int list_size = get_list_size(list); //O(N)

    srand(time(0));

    for (int i = list_size - 1; i > 0; i--)//O(N)
    {

        int j = rand() % (i + 1);

        dlist_node_t *picked = get_item_with_index(list, i); //O(N)
        dlist_node_t *picked2 = get_item_with_index(list, j);

        if (picked2 == picked)
        {
            return;
        }
        list_remove(list, picked);

        list_insert_before(list, picked2, picked);
    }
}

int main()
{
    dstring_item_t *my_linked_list = NULL;

    dstring_item_t *first_item = string_item_new("0");
    dstring_item_t *second_item = string_item_new("1");
    dstring_item_t *third_item = string_item_new("2");
    dstring_item_t *fourth_item = string_item_new("3");
    dstring_item_t *fifth_item = string_item_new("4");
    dstring_item_t *sixth_item = string_item_new("5");
    dstring_item_t *seventh_item = string_item_new("7");

    list_append(ptr_of_ptr(&my_linked_list), ptr_list(first_item));
    list_append(ptr_of_ptr(&my_linked_list), ptr_list(second_item));
    list_append(ptr_of_ptr(&my_linked_list), ptr_list(third_item));
    list_append(ptr_of_ptr(&my_linked_list), ptr_list(fourth_item));
    list_append(ptr_of_ptr(&my_linked_list), ptr_list(fifth_item));
    list_append(ptr_of_ptr(&my_linked_list), ptr_list(sixth_item));


    randomizer_list(ptr_of_ptr(&my_linked_list));
    print_list((dlist_node_t *)my_linked_list);


    /* code */
    return 0;
}
