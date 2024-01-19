#ifndef DOUBLY_LIST_DEFINE
#define DOUBLY_LIST_DEFINE

#define GET_MY_LIST(x) &(x.list_item)
#define TO_INT_LIST(x) (int_doubly_list_item*)(x)
#define TO_INT_LIST_POINTER(x) (int_doubly_list_item**)(x)
#define TO_GENERIC_DOUBLY_LIST(x)  (doubly_list_item*)(x)
#define TO_GENERIC_DOUBLY_LIST_POINTER(x) (doubly_list_item**)(x)

struct doubly_list_item
{
    struct doubly_list_item *prev;
    struct doubly_list_item *next;
    unsigned int count;
}typedef doubly_list_item;

struct int_doubly_list_item
{
    doubly_list_item list_item;
    int value;
}typedef int_doubly_list_item;

doubly_list_item* list_get_tail(doubly_list_item* head);
doubly_list_item* list_append(doubly_list_item** head, doubly_list_item* item);
doubly_list_item* list_pop(doubly_list_item** head);
doubly_list_item* list_remove_by_index(doubly_list_item** head, const unsigned int index);
int_doubly_list_item* int_remove_item_at_value(int_doubly_list_item** head,const unsigned int value);
void list_add_element_after_index(doubly_list_item** head, doubly_list_item* item, const unsigned int index);
void list_add_element_before_index(doubly_list_item** head, doubly_list_item* item, const unsigned int index);
unsigned int find_index_by_int_value(const doubly_list_item* head, const unsigned int value);
void doubly_list_print(doubly_list_item* head);
doubly_list_item* shuffle_list(doubly_list_item* head);

#endif