#include <linkedList.h>
#include <stddef.h>

struct list_node *list_get_tail(struct list_node **head)
{

    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

struct list_node *list_append(struct list_node **head, struct list_node *item)
{ // gli passo ** perchè così sovrascrive il valore
    struct list_node *tail = list_get_tail(head);

    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }

    item->next = NULL;
    return item;
}

struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;

    if (!current_head)
        return NULL;

    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }

    item->string = string; //
    return item;
}

struct list_node *list_remove(struct list_node **list, struct list_node *item)
{

    struct list_node *tmp_list = *list;

    if (!tmp_list)
    {
        return -1; // errore è nulla
    }

    if (tmp_list == item)
    {

        list_pop(list);

        return 0;

    } // faccio riferimento al primo valore

    while (tmp_list->next != item)
    {

        tmp_list = tmp_list->next;
        if (tmp_list == NULL)
        {
            return -1;
        }
    }

    // here tmp_list->next == item

    // tmp_list->next;// (item to remove)

    tmp_list->next = item->next; // override the item to remove with his next.

    return 0;
}

struct list_node *list_inverter(struct list_node **head)
{

    struct list_node *new_list = NULL;

    struct list_node *start_point = *head;
    struct list_node *tail = list_get_tail(head); //SAVING THE end point.

    ez_append_list(new_list, tail);
    while (start_point != tail)
    {
        tail = list_get_tail(head);
        ez_append_list(new_list, tail);

        list_remove(head, tail);
    }

    return new_list;

    //   if(!*head)
    //     return NULL;
    //     // printf("elemento nuova lista %s\n",((struct string_item*)new_list)->string);
    //      struct list_node *current = *head; // 0
    //      struct list_node *next_of_current = NULL;
    //      struct list_node *temporary_node = NULL;

    //     while(current){
    //         next_of_current = current->next; //1 2 3
    //         current->next = temporary_node; //1=NULL //this way i make null the link of the first item 0 1
    //         temporary_node = current; //0 1 2
    //         current = next_of_current;//1 2
    //     }
            //fucking 0 0 00 0 0 0
    //     return temporary_node;
}

int main()
{
    struct string_item *my_linked_list = NULL;
    struct string_item *new_list = NULL;

    struct string_item *first_item = string_item_new("0");
    struct string_item *second_item = string_item_new("1");
    struct string_item *third_item = string_item_new("2");
    struct string_item *fourth_item = string_item_new("3");

    ez_append_list(my_linked_list, first_item);
    ez_append_list(my_linked_list, second_item);
    ez_append_list(my_linked_list, third_item);
    ez_append_list(my_linked_list, fourth_item);

    new_list = ez_reverse_list(my_linked_list);
    // list_append(ptr_of_ptr(&my_linked_list),(struct list_node*)first_item);
    // list_append((struct list_node **)&my_linked_list,(struct list_node*)second_item);
    // list_append((struct list_node **)&my_linked_list,(struct list_node*)third_item);

    // list_remove((struct list_node **)&my_linked_list,(struct list_node *)first_item);
    //  list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Hello World"));
    //  list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test001"));
    //  list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test002"));
    //  list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Last Item of the Linked List"));
    struct string_item *string_item = my_linked_list;
    struct string_item *new_item_list = new_list;
    while (new_item_list)
    {
        printf("%s\n", new_item_list->string);
        new_item_list = (struct string_item *)new_item_list->node.next;
    }
    return 0;
}
