#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define GET_MY_LIST(x) &(x.list_item)
#define TO_GENERIC_LIST(x) (struct list_item*)(x)
#define TO_INT_LIST(x) (struct list_int_item*)(x)

#define SET_BLUE_PRINT(x) printf("\033[0;34m")
#define SET_GREEN_PRINT(x) printf("\033[0;32m")
#define SET_RED_PRINT(x) printf("\033[0;31m")
#define SET_DEFAULT_PRINT(x) printf("\033[0;00m")

struct list_item
{
    struct list_item* next; 
    unsigned int count;   
};

struct list_int_item
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
    return current_head;
}

unsigned int list_length(struct list_item* head)
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

struct list_item* list_remove_item_at_index(struct list_item** head, unsigned int index)
{
    if(!(*head) || index > (*head)->count) return NULL;

    if(index == 0) 
    {
        SET_RED_PRINT();
        printf("#Removed the head element");
        SET_DEFAULT_PRINT();
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
    printf("#Index not founded");
    SET_DEFAULT_PRINT();
    return NULL;
}

struct list_int_item* int_remove_item_at_value(struct list_int_item** head, unsigned int value)
{
    if(!(*head)) return NULL;

    if((*head)->value == value) 
    {
        SET_RED_PRINT();
        printf("#Removed the head element \n");
        SET_DEFAULT_PRINT();
        struct list_int_item* popped_item = TO_INT_LIST(list_pop((struct list_item**)(head)));
        return popped_item;
    }

    struct list_int_item* current_item = TO_INT_LIST((*head))->list_item.next;
    struct list_int_item* previous_item = (*head);

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
    printf("#Value not founded in the list");
    SET_DEFAULT_PRINT();
    return NULL;
}

void list_print(struct list_item* head)
{
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

struct list_item* list_reverse(struct list_item** head)
{
    if(!(*head) || (*head)->count <2) return *head;

    struct list_item* localHead = NULL;

    const unsigned int count = (*head)->count;    

    for (int i = 0; i < count; i++)
    {
        struct list_item* current_local_item = (*head);

        for (int j = count-i-1; j > 0; j--)
        {
            current_local_item = current_local_item->next;
        }

        list_append(&localHead,current_local_item);
    }

    SET_GREEN_PRINT();
    printf("Reversed list!\n");
    SET_DEFAULT_PRINT();
    return localHead;
}

int main(int argc, char** argv){

    struct list_item* head = NULL; // it's a pointer not a my_list_item

    struct list_int_item first_int_item;
    first_int_item.value = 0;
    list_append(&head,TO_GENERIC_LIST(&first_int_item.list_item));

    struct list_int_item second_int_item;
    second_int_item.value = 2;
    list_append(&head,GET_MY_LIST(second_int_item));

    struct list_int_item third_int_item;
    third_int_item.value = 4;
    list_append(&head,GET_MY_LIST(third_int_item));

    struct list_int_item fourth_int_item;
    fourth_int_item.value = 8;
    list_append(&head,GET_MY_LIST(fourth_int_item));

    struct list_int_item fifth_int_item;
    fifth_int_item.value = 16;
    list_append(&head,GET_MY_LIST(fifth_int_item));

    list_print(head);

    list_remove_item_at_index(&head,1);

    list_print(head);

    int_remove_item_at_value((struct list_int_item**)&head,8);

    list_print(head);

    struct list_int_item* reversed_list = TO_INT_LIST(list_reverse(&head));

    list_print(TO_GENERIC_LIST(reversed_list));
}