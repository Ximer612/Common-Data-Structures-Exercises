#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <doubly_linked.h>

doubly_list_item* list_get_tail(doubly_list_item* head)
{
    if(!head)
    {
        return NULL;
    }

    doubly_list_item* current_item = head;
    doubly_list_item* last_item = NULL;
    
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }
    
    return last_item;
}

doubly_list_item* list_append(doubly_list_item** head, doubly_list_item* item)
{
    doubly_list_item* tail = list_get_tail(*head);

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

doubly_list_item* list_pop(doubly_list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    doubly_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->prev = NULL;
        (*head)->count = current_count - 1;
    }

    current_head->next  = NULL;

    RED_PRINT("#Removed the head element");

    return current_head;
}

doubly_list_item* list_remove_by_index(doubly_list_item** head, const unsigned int index)
{
    if(!(*head) || (*head)->count < index) return NULL;

    if(index == 0)
    {      
        return list_pop(head);
    }

    doubly_list_item* current_head = (*head)->next;

    for (int i = 1; i < (*head)->count; i++)
    {
        if(i == index)
        {
            current_head->prev->next = current_head->next;
            if(current_head->next)
                current_head->next->prev = current_head->prev;
            (*head)->count--;
            return current_head;
        }

        current_head = current_head->next;
    }
    
    return NULL;
}

int_doubly_list_item* int_remove_item_at_value(int_doubly_list_item** head,const unsigned int value)
{
    if(!(*head)) return NULL;

    if((*head)->value == value) 
    {
        return TO_INT_LIST(list_pop((doubly_list_item**)(head)));
    }

    int_doubly_list_item* current_item = TO_INT_LIST((*head))->list_item.next;

    for (int i = 1; i < (*head)->list_item.count; i++)
    {
        if(current_item->value == value)
        {
            current_item->list_item.prev->next = current_item->list_item.next;
            if(current_item->list_item.next)
                current_item->list_item.next->prev = current_item->list_item.prev;

            (*head)->list_item.count--;

            current_item->list_item.next=NULL;
            current_item->list_item.prev=NULL;

            RED_PRINT("#Removed the element at index %d with value %d",i,current_item->value);
            return current_item;
        }

        current_item = TO_INT_LIST(current_item)->list_item.next;
    } 

    RED_PRINT("#Value %d not founded in the list",value);
    return NULL;
}

void list_add_element_after_index(doubly_list_item** head, doubly_list_item* item, const unsigned int index)
{
    if(!(*head) || index < 0) 
    {
        RED_PRINT("#Cannot add element after the index %d",index);
        return;
    }

    if(index > (*head)->count)
    {
        list_append(head,item);
        RED_PRINT("#Added at the bottom of the list , the index was %d but list was %d",index, (*head)->count);
        return;
    }

    doubly_list_item* current_head = *head;

    for (int i = 0; i < (*head)->count; i++)
    {
        if(i == index)
        {

            item->prev = current_head;
            item->next = current_head->next;
            item->prev->next = item;
            if(item->next)
                item->next->prev = item;
            (*head)->count++;
            GREEN_PRINT("#Item added at the index %d",index+1);
            return;
        }

        current_head = current_head->next;
    }

    RED_PRINT("#Index %d not founded in the list",index);
    return;
}

void list_add_element_before_index(doubly_list_item** head, doubly_list_item* item, const unsigned int index)
{
    if(!(*head) || (*head)->count < index) 
    {
        RED_PRINT("#Cannot add element before the index %d",index);
        return;
    }

    if(index == 0)
    {
        doubly_list_item* last_head = *head;
        item->count = (*head)->count+1;
        *head = item;
        item->next = last_head;
        item->prev = NULL;
        last_head->prev = *head;

        GREEN_PRINT("#Item added as new head %d", item->count);
        return;
    }

    doubly_list_item* current_head = (*head)->next;

    for (int i = 1; i < (*head)->count; i++)
    {
        if(i == index)
        {
            item->prev = current_head->prev;
            item->next = current_head;

            current_head->prev->next = item;
            current_head->prev = item;

            (*head)->count++;
            GREEN_PRINT("#Item added at the index %d",index-1);
            return;
        }

        current_head = current_head->next;
    }

    RED_PRINT("#Index %d not founded in the list",index);

    return;
}

unsigned int find_index_by_int_value(const doubly_list_item* head, const unsigned int value)
{
    if(!head) return -1;

    int_doubly_list_item* current_item = TO_INT_LIST(head);

    for (int i = 0; i < head->count; i++)
    {
        if(current_item->value == value)
        {
            GREEN_PRINT("#Founded element at index %d with value %d",i,current_item->value);
            return i;
        }

        current_item = TO_INT_LIST(current_item)->list_item.next;
    } 

    RED_PRINT("#Value %d not founded in the list",value);
    return -1;
}

void doubly_list_print(doubly_list_item* head)
{
    if(!head)
    {
        RED_PRINT("#The list is empty!");
        return;
    }

    doubly_list_item* current_item = head;

    GREEN_PRINT("#The list length is = %d",head->count);

    for (int i = 0; i < head->count; i++)
    {
        WHITE_PRINT("[%d] == %d",i,(TO_INT_LIST(current_item))->value);  

        if(!current_item->next) continue;
        current_item = current_item->next;
    }
}

doubly_list_item* shuffle_list(doubly_list_item* head)
{
    if(!(head) || (head)->count <2 ) return head;

    doubly_list_item* reversed_list = head;

    const unsigned int count = head->count; 
    
    doubly_list_item* current_item = reversed_list;

    doubly_list_item* random_item;

    BLUE_PRINT("#########################################################");

    for (int i = 0; i < count; i++)
    {
        //to improve random shuffle
        const unsigned int random_index = rand() % count;

        CYAN_PRINT("Swapping the element in %d with the element at %d",i,random_index);

        random_item = list_remove_by_index(&reversed_list, i);
        //printf("#Removed the %d element!\n",i);
        //list_print(reversed_list);

        list_add_element_after_index(&reversed_list,random_item,i-1);

        random_item = list_remove_by_index(&reversed_list, (random_index-1)%count );
        //printf("#Removed the %d element! %p\n",random_index-1, random_item);
        //list_print(reversed_list);
        
        list_add_element_after_index(&reversed_list,random_item,random_index-1);        
        //list_print(reversed_list);
        //printf("Swapped! %d  -- %d\n\n",i,random_index);
    }

    BLUE_PRINT("#########################################################");
    GREEN_PRINT("Shuffled list!");
    return reversed_list;
}

