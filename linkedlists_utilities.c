extern struct list_item;
extern struct list_item* head;

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