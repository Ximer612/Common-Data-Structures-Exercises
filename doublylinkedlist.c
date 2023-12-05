#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "console_utilities.h"
#include "lists_utilities.h"

struct list_item
{
    struct list_item *prev;
    struct list_item *next;
    unsigned int count;
};

struct int_list_item
{
    struct list_item list_item;
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
    
    item->prev = tail;
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
        (*head)->prev = NULL;
        (*head)->count = current_count - 1;
    }

    current_head->next  = NULL;

    SET_RED_PRINT();
    printf("#Removed the head element\n");
    SET_DEFAULT_PRINT();  

    return current_head;
}

struct list_item* list_remove_by_index(struct list_item** head, const unsigned int index)
{
    if(!(*head) || (*head)->count < index) return NULL;

    if(index == 0)
    {      
        return list_pop(head);
    }


    struct list_item* current_head = (*head)->next;

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

struct int_list_item* int_remove_item_at_value(struct int_list_item** head,const unsigned int value)
{
    if(!(*head)) return NULL;

    if((*head)->value == value) 
    {
        return TO_INT_LIST(list_pop((struct list_item**)(head)));
    }

    struct int_list_item* current_item = TO_INT_LIST((*head))->list_item.next;

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

            SET_RED_PRINT();
            printf("#Removed the element at index %d with value %d\n",i,current_item->value);
            SET_DEFAULT_PRINT();
            return current_item;
        }

        current_item = TO_INT_LIST(current_item)->list_item.next;
    } 

    SET_RED_PRINT();
    printf("#Value %d not founded in the list\n",value);
    SET_DEFAULT_PRINT();
    return NULL;
}

void list_add_element_after_index(struct list_item** head, struct list_item* item, const unsigned int index)
{
    if(!(*head) || index < 0) 
    {
        SET_RED_PRINT();
        printf("#Cannot add element after the index %d\n",index);
        SET_DEFAULT_PRINT();
        return;
    }

    if(index > (*head)->count)
    {
        list_append(head,item);
        SET_RED_PRINT();
        printf("#Added at the bottom of the list , the index was %d but list was %d\n",index, (*head)->count);
        SET_DEFAULT_PRINT();
        return;
    }

    struct list_item* current_head = *head;

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
            SET_GREEN_PRINT();
            printf("#Item added at the index %d\n",index+1);
            SET_DEFAULT_PRINT();
            return;
        }

        current_head = current_head->next;
    }

    SET_RED_PRINT();
    printf("#Index %d not founded in the list\n",index);
    SET_DEFAULT_PRINT();

    return;
}

void list_add_element_before_index(struct list_item** head, struct list_item* item, const unsigned int index)
{
    if(!(*head) || (*head)->count < index) 
    {
        SET_RED_PRINT();
        printf("#Cannot add element before the index %d\n",index);
        SET_DEFAULT_PRINT();
        return;
    }

    if(index == 0)
    {
        struct list_item* last_head = *head;
        item->count = (*head)->count+1;
        *head = item;
        item->next = last_head;
        item->prev = NULL;
        last_head->prev = *head;

        SET_GREEN_PRINT();
        printf("#Item added as new head %d \n", item->count);
        SET_DEFAULT_PRINT();
        return;
    }

    struct list_item* current_head = (*head)->next;

    for (int i = 1; i < (*head)->count; i++)
    {
        if(i == index)
        {
            item->prev = current_head->prev;
            item->next = current_head;

            current_head->prev->next = item;
            current_head->prev = item;

            (*head)->count++;
            SET_GREEN_PRINT();
            printf("#Item added at the index %d\n",index-1);
            SET_DEFAULT_PRINT();
            return;
        }

        current_head = current_head->next;
    }

    SET_RED_PRINT();
    printf("#Index %d not founded in the list\n",index);
    SET_DEFAULT_PRINT();

    return;
}

unsigned int find_index_by_int_value(const struct list_item* head, const unsigned int value)
{
    if(!head) return -1;


    struct int_list_item* current_item = TO_INT_LIST(head);

    for (int i = 0; i < head->count; i++)
    {
        if(current_item->value == value)
        {
            SET_GREEN_PRINT();
            printf("#Founded element at index %d with value %d\n",i,current_item->value);
            SET_DEFAULT_PRINT();
            return i;
        }

        current_item = TO_INT_LIST(current_item)->list_item.next;
    } 

    SET_RED_PRINT();
    printf("#Value %d not founded in the list\n",value);
    SET_DEFAULT_PRINT();
    return -1;
}

void list_print(struct list_item* head)
{
    if(!head)
    {
        SET_RED_PRINT();
        printf("#The list is empty!");
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

struct list_item* shuffle_list(struct list_item* head)
{
    if(!(head) || (head)->count <2 ) return head;

    struct list_item* reversed_list = head;

    const unsigned int count = head->count; 
    
    struct list_item* current_item = reversed_list;

    struct list_item* random_item;

    SET_BLUE_PRINT();
    printf("#########################################################\n");
    SET_DEFAULT_PRINT();

    for (int i = 0; i < count; i++)
    {
        const unsigned int random_index = rand() % count;

        printf("Swapping the element in %d with the element at %d\n",i,random_index);

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

    SET_BLUE_PRINT();
    printf("#########################################################\n");
    SET_DEFAULT_PRINT();

    SET_GREEN_PRINT();
    printf("Shuffled list!\n");
    SET_DEFAULT_PRINT();
    return reversed_list;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    struct list_item* head;
    struct int_list_item* items_to_add;

    void** to_free_memory[10];
    const int items_to_create = 10;

    for (int i = 0; i < items_to_create; i++)
    {
        items_to_add = TO_INT_LIST(malloc(sizeof(struct int_list_item)));
        to_free_memory[i] = (void*)items_to_add;
        (*items_to_add).value = 1 + i*1;
        list_append(&head,&(*items_to_add).list_item);
    }
    
    list_print(head);

    list_remove_by_index(&head,0);
    int_remove_item_at_value(TO_INT_LIST_POINTER(&head),9);
    list_print(head);

    struct int_list_item new_item1;
    new_item1.value = 123;

    list_add_element_after_index(&head,TO_GENERIC_LIST(&new_item1),1);

    list_print(head);

    struct int_list_item new_item2;
    new_item2.value = 456;

    const int new_item2_index =  find_index_by_int_value(head,new_item1.value);
    list_add_element_before_index(&head,TO_GENERIC_LIST(&new_item2),new_item2_index);

    list_print(head);

    struct list_item* shuffled_list = shuffle_list(head);
    list_print(shuffled_list);

    SET_GREEN_PRINT();

    for (int i = 0; i < items_to_create; i++)
    {
        //printf("#Cleaning the address => %p\n",to_free_memory[i]);
        free(to_free_memory[i]);
    }

    printf("#Memory clean!\n");
    SET_DEFAULT_PRINT();

    return 0;
}