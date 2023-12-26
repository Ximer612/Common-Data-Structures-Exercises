#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <doubly_linked.h>

int main(int argc, char** argv)
{
    srand(time(NULL));

    doubly_list_item* head;
    int_doubly_list_item* items_to_add;

    void** to_free_memory[10];
    const int items_to_create = 10;

    for (int i = 0; i < items_to_create; i++)
    {
        items_to_add = TO_INT_LIST(malloc(sizeof(int_doubly_list_item)));
        to_free_memory[i] = (void*)items_to_add;
        (*items_to_add).value = 1 + i*1;
        list_append(&head,&(*items_to_add).list_item);
    }
    
    doubly_list_print(head);

    list_remove_by_index(&head,0);
    int_remove_item_at_value(TO_INT_LIST_POINTER(&head),9);
    doubly_list_print(head);

    int_doubly_list_item new_item1;
    new_item1.value = 123;

    list_add_element_after_index(&head,TO_GENERIC_DOUBLY_LIST(&new_item1),1);

    doubly_list_print(head);

    int_doubly_list_item new_item2;
    new_item2.value = 456;

    const int new_item2_index =  find_index_by_int_value(head,new_item1.value);
    list_add_element_before_index(&head,TO_GENERIC_DOUBLY_LIST(&new_item2),new_item2_index);

    doubly_list_print(head);

    doubly_list_item* shuffled_list = shuffle_list(head);
    doubly_list_print(shuffled_list);

    SET_GREEN_PRINT();

    for (int i = 0; i < items_to_create; i++)
    {
        printf("#Cleaning the address => %p\n",to_free_memory[i]);
        free(to_free_memory[i]);
    }

    printf("#Memory clean!\n");
    SET_DEFAULT_PRINT();
    return 0;
}