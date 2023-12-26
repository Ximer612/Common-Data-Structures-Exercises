#define TO_INT_LIST(x) (int_singly_list_item*)(x)
#define TO_INT_LIST_POINTER(x) (int_singly_list_item**)(x)
#define GET_MY_LIST(x) &(x.list_item)
#define TO_GENERIC_SINGLY_LIST(x) (singly_list_item*)(x)
#define TO_GENERIC_SINGLY_LIST_POINTER(x) (singly_list_item**)(x)

typedef struct singly_list_item
{
    struct singly_list_item* next; 
    unsigned int count;   
}singly_list_item;

typedef struct int_singly_list_item
{
    singly_list_item list_item; //it's like his parent
    int value;    
}int_singly_list_item;

singly_list_item* list_get_tail(singly_list_item* head);
singly_list_item* list_append(singly_list_item** head, singly_list_item* item);
singly_list_item* list_pop(singly_list_item** head);
unsigned int list_length(const singly_list_item* head);
unsigned int list_length_slow(singly_list_item* head);
singly_list_item* list_remove_item_at_index(singly_list_item** head,const unsigned int index);
int_singly_list_item* int_remove_item_at_value(int_singly_list_item** head,const unsigned int value);
void int_list_print(int_singly_list_item* head);
singly_list_item* list_reverse(singly_list_item* head);
