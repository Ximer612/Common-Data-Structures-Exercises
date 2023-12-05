#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console_utilities.h"
#include "lists_utilities.h"

struct list_item
{
    struct list_item* next; 
    unsigned int count;   
};

struct int_list_item
{
    struct list_item list_item; //it's like his parent
    int value;    
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
    
    item->next = NULL;
    return item;
}

struct list_item* list_pop(struct list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next  = NULL;

    SET_RED_PRINT();
    printf("#Removed the head element\n");
    SET_DEFAULT_PRINT();  

    return current_head;
}

unsigned int list_length(const struct list_item* head)
{
    return head->count;
}

unsigned int list_length_slow(struct list_item* head)
{
    unsigned int counter = 0;

    struct list_item* current_item = head;

    while(current_item) // WHILE IS NOT NULL
    {
        counter++;
        current_item = current_item->next;
    }

    return counter;
}

struct list_item* list_remove_item_at_index(struct list_item** head,const unsigned int index)
{
    if(!(*head) || index > (*head)->count) return NULL;

    if(index == 0) 
    {
        return list_pop(head);
    }

    struct list_item* current_item = (*head)->next;
    struct list_item* previous_item = (*head);

    for (int i = 1; i < (*head)->count; i++)
    {
        if(i == index)
        {
            previous_item->next = current_item->next;
            (*head)->count--;
            current_item->next=NULL;

            SET_RED_PRINT();
            printf("#Removed the element at index %d \n",i);
            SET_DEFAULT_PRINT();
            return current_item;
        }

        previous_item = current_item;
        current_item = current_item->next;
    } 

    SET_RED_PRINT();
    printf("#Index not founded\n");
    SET_DEFAULT_PRINT();
    return NULL;
}

struct int_list_item* int_remove_item_at_value(struct int_list_item** head,const unsigned int value)
{
    if(!(*head)) return NULL;

    if((*head)->value == value) 
    {
        struct int_list_item* popped_item = TO_INT_LIST(list_pop((struct list_item**)(head)));
        return popped_item;
    }

    struct int_list_item* current_item = TO_INT_LIST((*head))->list_item.next;
    struct int_list_item* previous_item = (*head);

    for (int i = 1; i < (*head)->list_item.count; i++)
    {
        if(current_item->value == value)
        {
            previous_item->list_item.next = current_item->list_item.next;
            (*head)->list_item.count--;
            current_item->list_item.next=NULL;

            SET_RED_PRINT();
            printf("#Removed the element at index %d with value %d\n",i,current_item->value);
            SET_DEFAULT_PRINT();
            return current_item;
        }

        previous_item = current_item;
        current_item = TO_INT_LIST(current_item)->list_item.next;
    } 

    SET_RED_PRINT();
    printf("#Value %d not founded in the list\n",value);
    SET_DEFAULT_PRINT();
    return NULL;
}

void list_print(struct list_item* head)
{
    if(!head)
    {
        SET_RED_PRINT();
        printf("#The list is empty!\n");
        SET_DEFAULT_PRINT();
        return;
    }

    struct list_item* current_item = head;

    SET_GREEN_PRINT();
    printf("#The list length is = %d\n",head->count);
    SET_DEFAULT_PRINT();

    for (int i = 0; i < head->count; i++)
    {
        printf("[%d] == %d \n",i,(TO_INT_LIST(current_item))->value);  

        if(!current_item->next) continue;
        current_item = current_item->next;
    }
}

struct list_item* list_reverse(struct list_item* head)
{
    if(!head || head->count <2 ) return head;

    struct list_item* reversedList = NULL;

    const unsigned int count = head->count;    

    for (int i = 0; i < count; i++)
    {
        struct list_item* current_local_item = head;

        for (int j = count-i-1; j > 0; j--)
        {
            current_local_item = current_local_item->next;
        }

        list_append(&reversedList,current_local_item);
    }

    SET_GREEN_PRINT();
    printf("Reversed list!\n");
    SET_DEFAULT_PRINT();
    return reversedList;
}

int main(int argc, char** argv){

    struct list_item* head = NULL; // it's a pointer not a my_list_item

    struct int_list_item* items_to_add;
    void** to_free_memory[5];
    const int items_to_create = 4;

    for (int i = 0; i < items_to_create; i++)
    {
        items_to_add = TO_INT_LIST( malloc(sizeof(struct int_list_item)) );
        to_free_memory[i] = (void*)items_to_add;
        (*items_to_add).value = 3 + i*3;
        list_append(&head,&(*items_to_add).list_item);
    }

    struct int_list_item new_item;
    new_item.value = 999;
    list_append(&head,&new_item.list_item);

    list_print(head);

    list_remove_item_at_index(&head,1);

    list_print(head);

    int_remove_item_at_value(TO_INT_LIST_POINTER(&head),8);

    list_print(head);

    struct int_list_item* reversed_list = TO_INT_LIST(list_reverse(head));

    list_print(TO_GENERIC_LIST(reversed_list));

    int_remove_item_at_value(TO_INT_LIST_POINTER(&reversed_list),9);
    int_remove_item_at_value(TO_INT_LIST_POINTER(&reversed_list),12);
    list_print(TO_GENERIC_LIST(reversed_list));
    int_remove_item_at_value(TO_INT_LIST_POINTER(&reversed_list),3);
    list_remove_item_at_index(TO_GENERIC_LIST_POINTER(&reversed_list),0);
    list_print(TO_GENERIC_LIST(reversed_list));

    SET_GREEN_PRINT();

    for (int i = 0; i < items_to_create; i++)
    {
        printf("#Cleaning the address => %p\n",to_free_memory[i]);
        free(to_free_memory[i]);
    }

    printf("#Memory clean!\n");
    SET_DEFAULT_PRINT();
}