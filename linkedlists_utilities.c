#include <linked_lists.h>

extern struct int_list_item;

void list_print(struct singly_list_item* head)
{
    struct singly_list_item* current_item = head;

    printf("#The list length is = %d\n",head->count);

    for (int i = 0; i < head->count; i++)
    {
        printf("[%d] == %d \n",i,((struct int_list_item*)(current_item))->value);  

        if(!current_item->next) continue;
        current_item = current_item->next;
    }
}