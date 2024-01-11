#define GET_SET_ITEMS_COUNT(set_table,index) ((set_table->items[index])->list_item.count)
#define GET_INT_SET_ITEMS_COUNT(set_table,index) (set_table->items[index]->set_list_item.list_item.count)
#define TO_GENERIC_SET(x) (set_table*)x

#include <singly_linked.h>

#ifndef SET_DEFINE
#define SET_DEFINE

typedef struct set_list_item
{
    singly_list_item list_item;
    const char *key;
    size_t key_len;
}set_list_item;  

typedef struct set_table
{
    set_list_item **items; //array of pointers of items
    size_t hashmap_size;
    size_t hashmap_singly_max_length;
} set_table;

typedef struct int_set_list_item
{
    set_list_item set_list_item;
    int value;
}int_set_list_item;




#endif

size_t djb33x_hash(const char* key, const size_t keylen);
set_table* create_new_set_table(const size_t hashmap_size, const size_t hashmap_singly_max_length);
set_list_item* set_find(set_table* set_table, const char* key, size_t* founded_slot);
set_list_item* set_insert(set_table* my_set_table, const char* key, int* has_reached_max);
void set_list_print(set_list_item* head);
void set_print(const set_table* set_table);
set_list_item* set_remove(set_table* set_table, const char* key);
void set_free(set_table* set_table);

void int_set_print(const set_table* set_table);
set_list_item* int_set_insert(set_table* my_set_table, const char* key, const int value,int* has_reached_max);

