#include <stddef.h>
#include <stdio.h>
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

void insert_before(dlist_node_t **list,dlist_node_t *item_to_insert,dlist_node_t *next_item){

    dlist_node_t *first_item = *list;

    if(!first_item){
        perror("No List");
        return;
    }
    if(check_item(list,next_item)==0){
        perror("Next item doesn't exist!");
        return;
    }

    if(next_item == first_item){
        //FIRST ELEMENT
        *list=item_to_insert;
        item_to_insert->next = next_item;
        item_to_insert->prev=NULL;
        
        next_item->prev = item_to_insert;
    return;
        //printf(*list);
    }

    dlist_node_t *prev_node = next_item->prev;

    prev_node->next = item_to_insert;
    item_to_insert->prev = prev_node;
    item_to_insert->next = next_item;
    next_item->prev = item_to_insert;

return;
}

void insert_after(dlist_node_t **list,dlist_node_t *item_to_insert,dlist_node_t *prev_item){
    dlist_node_t *first_item = *list;

    if(!first_item){
        perror("No List");
        return;
    }
    if(check_item(list,prev_item)==0){
        perror("prev item doesn't exist!");
        return;
    }

    if(prev_item->next == NULL){
        //LAST Element
        
        item_to_insert->next = NULL;
        item_to_insert->prev=prev_item;
        
        prev_item->next = item_to_insert;
    return;
        //printf(*list);
    }

    // 0 1 2 3
    // 0 1 5 2 3

    prev_item->next->prev = item_to_insert;
    item_to_insert->next = prev_item->next;
    prev_item->next = item_to_insert;
    item_to_insert->prev=prev_item;

return;
}

void print_list(dlist_node_t *list){
    
    dstring_item_t *list_item = (dstring_item_t*)list;
    while (list)
    {
        printf("%s\n", list_item->string);
        list_item = (dstring_item_t*)list_item->node.next;
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

    if(check_item(list,item)==0){
        perror("Item is not contained");
        return; //l'oggetto non esiste
    }

    if (tmp_list == item)
    {
        list_pop(list);
        return;
    } // faccio riferimento al primo valore

     (item->prev)->next = item->next;
     (item->next)->prev = item->prev;

//cleaning the removed item
    item->prev=NULL;
    item->next=NULL;
    return;
}

int main()
{
    dstring_item_t *my_linked_list =NULL;

    dstring_item_t *first_item=string_item_new("0");
    dstring_item_t *second_item=string_item_new("1");
    dstring_item_t *third_item=string_item_new("2");
    dstring_item_t *fourth_item=string_item_new("3");
    dstring_item_t *fifth_item=string_item_new("5");

    list_append(ptr_of_ptr(&my_linked_list),ptr_list(first_item));
    list_append(ptr_of_ptr(&my_linked_list),ptr_list(second_item));
    list_append(ptr_of_ptr(&my_linked_list),ptr_list(third_item));
    list_append(ptr_of_ptr(&my_linked_list),ptr_list(fourth_item));


    
    // list_remove(ptr_of_ptr(&my_linked_list),ptr_list(first_item));
    // insert_before(ptr_of_ptr(&my_linked_list),ptr_list(fifth_item),ptr_list(fourth_item));
    insert_after(ptr_of_ptr(&my_linked_list),ptr_list(fifth_item),ptr_list(first_item));
    print_list((dlist_node_t*)my_linked_list);
    
    /* code */
    return 0;
}
