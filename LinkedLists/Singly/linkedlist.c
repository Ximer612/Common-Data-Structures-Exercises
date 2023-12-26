#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <singly_linked.h>

singly_list_item* list_get_tail(singly_list_item* head)
{
    if(!head)
    {
        return NULL;
    }

    singly_list_item* current_item = head;
    singly_list_item* last_item = NULL;
    
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }
    
    return last_item;
}

singly_list_item* list_append(singly_list_item** head, singly_list_item* item)
{
    singly_list_item* tail = list_get_tail(*head);

    if(!(tail))
    {
        *head  = item;
        (*head)->count=1;
    }
    else{
        tail->next = item;
        (*head)->count++;
    }
    
    item->next = NULL;
    return item;
}

singly_list_item* list_pop(singly_list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    singly_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next  = NULL;

    RED_PRINT("#Removed the head element");

    return current_head;
}

unsigned int list_length(const singly_list_item* head)
{
    return head->count;
}

unsigned int list_length_slow(singly_list_item* head)
{
    unsigned int counter = 0;

    struct singly_list_item* current_item = head;

    while(current_item) // WHILE IS NOT NULL
    {
        counter++;
        current_item = current_item->next;
    }

    return counter;
}

singly_list_item* list_remove_item_at_index(singly_list_item** head,const unsigned int index)
{
    if(!(*head) || index > (*head)->count) 
    {           
        RED_PRINT("#Can't remove the item at index %d",index);
        return NULL;
    }

    if(index == 0) 
    {
        return list_pop(head);
    }

    struct singly_list_item* current_item = (*head)->next;
    struct singly_list_item* previous_item = (*head);

    for (int i = 1; i < (*head)->count; i++)
    {
        if(i == index)
        {
            previous_item->next = current_item->next;
            (*head)->count--;
            current_item->next=NULL;

            RED_PRINT("#Removed the element at index %d",i);
            return current_item;
        }

        previous_item = current_item;
        current_item = current_item->next;
    } 

    RED_PRINT("#Index not founded");
    return NULL;
}

int_singly_list_item* int_remove_item_at_value(int_singly_list_item** head,const unsigned int value)
{
    if(!(*head)) return NULL;

    if((*head)->value == value) 
    {
        int_singly_list_item* popped_item = TO_INT_LIST(list_pop((singly_list_item**)(head)));
        return popped_item;
    }

    int_singly_list_item* current_item = TO_INT_LIST((*head))->list_item.next;
    int_singly_list_item* previous_item = (*head);

    for (int i = 1; i < (*head)->list_item.count; i++)
    {
        if(current_item->value == value)
        {
            previous_item->list_item.next = current_item->list_item.next;
            (*head)->list_item.count--;
            current_item->list_item.next=NULL;

            RED_PRINT("#Removed the element at index %d with value %d",i,current_item->value);
            return current_item;
        }

        previous_item = current_item;
        current_item = TO_INT_LIST(current_item)->list_item.next;
    } 

    RED_PRINT("#Value %d not founded in the list",value);
    return NULL;
}

void int_list_print(int_singly_list_item* head)
{
    if(!head)
    {
        RED_PRINT("#The list is empty!");
        return;
    }

    int_singly_list_item* current_item = head;

    BLUE_PRINT("#The list length is = %d",head->list_item.count);

    for (int i = 0; i < head->list_item.count; i++)
    {
        WHITE_PRINT("[%d] == %d",i,current_item->value);  

        if(!current_item->list_item.next) continue;
        current_item = (int_singly_list_item*)current_item->list_item.next;
    }
}

singly_list_item* list_reverse(singly_list_item* head)
{
    if(!head || head->count <2 ) return head;

    singly_list_item* reversedList = NULL;

    const unsigned int count = head->count;    

    for (int i = 0; i < count; i++)
    {
        singly_list_item* current_local_item = head;

        for (int j = count-i-1; j > 0; j--)
        {
            current_local_item = current_local_item->next;
        }

        list_append(&reversedList,current_local_item);
    }

    MAGENTA_PRINT("Reversed list!");
    return reversedList;
}