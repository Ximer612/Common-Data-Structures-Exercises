#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_LIST(x) &(x.list_item)
#define TO_GENERIC_LIST(x) (struct my_list_item*)(x)
#define TO_INT_LIST(x) (struct my_int_item*)(x)

#define SET_BLUE_PRINT(x) printf("\033[0;34m")
#define SET_GREEN_PRINT(x) printf("\033[0;32m")
#define SET_RED_PRINT(x) printf("\033[0;31m")
#define SET_DEFAULT_PRINT(x) printf("\033[0;00m")

struct my_list_item
{
    struct my_list_item* next; 
    unsigned int count;   
};

struct my_int_item
{
    struct my_list_item list_item; //it's like his parent
    int value;    
};

struct my_list_item* my_list_get_tail(struct my_list_item* head)
{
    if(!head)
    {
        return NULL;
    }

    struct my_list_item* current_item = head;
    struct my_list_item* last_item = NULL;
    
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }
    
    return last_item;
}

struct my_list_item* my_list_append(struct my_list_item** head, struct my_list_item* item)
{
    struct my_list_item* tail = my_list_get_tail(*head);

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

struct my_list_item* my_list_pop(struct my_list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct my_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next  = NULL;
    return current_head;
}

unsigned int my_list_length(struct my_list_item* head)
{
    return head->count;
}

unsigned int my_list_length_slow(struct my_list_item* head)
{
    unsigned int counter = 0;

    struct my_list_item* current_item = head;

    while(current_item) // WHILE IS NOT NULL
    {
        counter++;
        current_item = current_item->next;
    }

    return counter;
}

struct my_list_item* my_list_remove_item(struct my_list_item** head, unsigned int index)
{
    if(!(*head) || index > (*head)->count) return NULL;

    if(index == 0) 
    {
        SET_RED_PRINT();
        printf("#Removed the head element");
        SET_DEFAULT_PRINT();
        return my_list_pop(head);
    }

    struct my_list_item* current_item = (*head)->next;
    struct my_list_item* previous_item = (*head);

    for (int i = 1; i < (*head)->count; i++)
    {
        if(i == index)
        {
            previous_item->next = current_item->next;
            (*head)->count--;
            current_item->next=NULL;

            SET_RED_PRINT();
            printf("#Removed the %d element\n",i);
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

struct my_int_item* my_int_remove_item(struct my_int_item** head, unsigned int value)
{
    if(!(*head)) return NULL;

    if((*head)->value == value) 
    {
        SET_RED_PRINT();
        printf("#Removed the head element \n");
        SET_DEFAULT_PRINT();
        struct my_int_item* popped_item = TO_INT_LIST(my_list_pop((struct my_list_item**)(head)));
        return popped_item;
    }

    struct my_int_item* current_item = TO_INT_LIST((*head))->list_item.next;
    struct my_int_item* previous_item = (*head);

    for (int i = 1; i < (*head)->list_item.count; i++)
    {
        if(current_item->value == value)
        {
            previous_item->list_item.next = current_item->list_item.next;
            (*head)->list_item.count--;
            current_item->list_item.next=NULL;

            SET_RED_PRINT();
            printf("#Removed the %d element with value %d\n",i,current_item->value);
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

void my_list_print(struct my_list_item* head)
{
    struct my_list_item* current_item = head;

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

struct my_list_item* my_list_reverse(struct my_list_item** head)
{
    if(!(*head) || (*head)->count <2) return *head;

    struct my_list_item* localHead = NULL;

    const unsigned int count = (*head)->count;    

    for (int i = 0; i < count; i++)
    {
        struct my_list_item* current_local_item = (*head);

        for (int j = count-i-1; j > 0; j--)
        {
            current_local_item = current_local_item->next;
        }

        my_list_append(&localHead,current_local_item);
    }

    SET_GREEN_PRINT();
    printf("Reversed list!\n");
    SET_DEFAULT_PRINT();
    return localHead;
}

int main(int argc, char** argv){

    struct my_list_item* head = NULL; // it's a pointer not a my_list_item

    struct my_int_item first_int_item;
    first_int_item.value = 0;
    my_list_append(&head,TO_GENERIC_LIST(&first_int_item.list_item));

    struct my_int_item second_int_item;
    second_int_item.value = 2;
    my_list_append(&head,MY_LIST(second_int_item));

    struct my_int_item third_int_item;
    third_int_item.value = 4;
    my_list_append(&head,MY_LIST(third_int_item));

    struct my_int_item fourth_int_item;
    fourth_int_item.value = 8;
    my_list_append(&head,MY_LIST(fourth_int_item));

    struct my_int_item fifth_int_item;
    fifth_int_item.value = 16;
    my_list_append(&head,MY_LIST(fifth_int_item));

    my_list_print(head);

    my_list_remove_item(&head,1);

    my_list_print(head);

    my_int_remove_item((struct my_int_item**)&head,8);

    my_list_print(head);

    struct my_int_item* reversed_list = TO_INT_LIST(my_list_reverse(&head));

    my_list_print(TO_GENERIC_LIST(reversed_list));
}