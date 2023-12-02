#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct list_item
{
    struct list_item *prev;
    struct list_item *next;
    unsigned int count;
};

struct list_item* list_get_tail(struct list_item* head)
{
    if(!head)
    {
        return NULL;
    }

    struct list_item* current_item = head;
    struct list_item* last_item = NULL;
    
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }
    
    return last_item;
}

struct list_item* list_append(struct list_item** head, struct list_item* item)
{
    struct list_item* tail = list_get_tail(*head);

    if(!(tail))
    {
        *head  = item;
        (*head)->count=1;
    }
    else{
        tail->next = item;
        (*head)->count++;
    }
    
    item->prev = tail;
    item->next = NULL;
    return item;
}