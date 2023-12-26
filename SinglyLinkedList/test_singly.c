#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <sets.h>

int main(int argc, char** argv){

    singly_list_item* head = NULL; // it's a pointer not a my_list_item

    int_singly_list_item* items_to_add;
    void** to_free_memory[5];
    const int items_to_create = 5;

    for (int i = 0; i < items_to_create; i++)
    {
        items_to_add = TO_INT_LIST( malloc(sizeof(int_singly_list_item)) );
        to_free_memory[i] = (void*)items_to_add;
        (*items_to_add).value = 3 + i*3;
        list_append(&head,&(*items_to_add).list_item);
    }

    int_singly_list_item new_item;
    new_item.value = 999;
    list_append(&head,&new_item.list_item);

    int_list_print((int_singly_list_item*)head);

    list_remove_item_at_index(&head,2);

    int_list_print((int_singly_list_item*)head);

    int_remove_item_at_value(TO_INT_LIST_POINTER(&head),8);

    int_list_print((int_singly_list_item*)head);

    int_singly_list_item* reversed_list = TO_INT_LIST(list_reverse(head));

    int_list_print(reversed_list);

    int_remove_item_at_value(TO_INT_LIST_POINTER(&reversed_list),9);
    int_remove_item_at_value(TO_INT_LIST_POINTER(&reversed_list),12);
    int_list_print(reversed_list);
    int_remove_item_at_value(TO_INT_LIST_POINTER(&reversed_list),3);
    list_remove_item_at_index(TO_GENERIC_SINGLY_LIST_POINTER(&reversed_list),0);
    int_list_print(reversed_list);

    SET_GREEN_PRINT();
    for (int i = 0; i < items_to_create; i++)
    {
        printf("#Cleaning the address => %p\n",to_free_memory[i]);
        free(to_free_memory[i]);
    }

    printf("#Memory clean!\n");
    SET_DEFAULT_PRINT();
}