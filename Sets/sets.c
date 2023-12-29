#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <sets.h>

size_t djb33x_hash(const char* key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

set_table* create_new_set_table(const size_t hashmap_size, const size_t hashmap_singly_max_length)
{
    set_table* table = malloc(sizeof(set_table));
    if (!table)
    {
        RED_PRINT("Cannot alloc memory for table");
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->hashmap_singly_max_length = hashmap_singly_max_length;
    table->items = calloc(table->hashmap_size, sizeof(set_list_item**)); //calloc because there can be everything in this nodes

    if (!table->items)
    {
        free(table);
        RED_PRINT("Cannot alloc memory for table's items");
        return NULL;
    }

    GREEN_PRINT("Created set table successfully!");
    return table;
}

set_list_item* set_find(set_table* set_table, const char* key, size_t* founded_slot)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (set_table)->hashmap_size;

    set_list_item* compare_node = set_table->items[index];


    for (size_t i = 0; i < (set_table)->hashmap_singly_max_length; i++)
    {
        if (set_table->items[index] && set_table->items[index]->key_len > 0)
        {
            if (compare_node->key_len == key_len && !memcmp(compare_node->key, key, key_len))
            {
                GREEN_PRINT("FOUND [%s] at index %llu slot %llu", key, index, i+1);
                if(founded_slot) *founded_slot = i;
                return compare_node;
            }

            if(compare_node->list_item.next)
                compare_node = ((set_list_item*)compare_node->list_item.next);
            else break;
        }
    }

    RED_PRINT("THE KEY [%s] WAS NOT FOUNDED IN THIS SET", key);
    return NULL;
}

int set_insert(set_table* my_set_table, const char* key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % my_set_table->hashmap_size;

    //printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    set_list_item* head = my_set_table->items[index];

    singly_list_item* tail = list_get_tail(&head->list_item);

    //if no tail = no head
    if(!tail) {

        my_set_table->items[index] = malloc(sizeof(set_list_item));

        if (!my_set_table->items[index])
        {
            RED_PRINT("Cannot allocate enough memory!");
            return -1;
        }

        my_set_table->items[index]->key = key;
        my_set_table->items[index]->key_len = key_len;
        my_set_table->items[index]->list_item.next = NULL;
        my_set_table->items[index]->list_item.count = 1;

        GREEN_PRINT("[%s] ADDED ELEMENT AT THE INDEX %llu!",key, index);
        return 0;
    }

    if(GET_SET_ITEMS_COUNT(my_set_table,index) >= my_set_table->hashmap_singly_max_length)
    {
        RED_PRINT("CANNOT ADD [%s] MAX SLOTS ITEMS FOR THIS INDEX ALREADY REACHED!", key);
        return -1;
    }

    if(set_find(my_set_table,key, NULL))
    {
        RED_PRINT("THE ELEMENT [%s] WAS ALREADY IN THE SET AND WAS NOT ADDED AGAIN!",key);
        return -1; 
    }
    
    // if has a tail
    set_list_item* new_item = malloc(sizeof(set_list_item));

    if (!new_item)
    {
        RED_PRINT("Cannot allocate enough memory!");
        return -1;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->list_item.next = NULL;

    tail->next = &(new_item->list_item);
    my_set_table->items[index]->list_item.count++;

    GREEN_PRINT("ADDED [%s] IN THE %d SLOT AT THE INDEX %llu AFTER THE [%s]!",key, GET_SET_ITEMS_COUNT(my_set_table,index) , index, ((set_list_item*)tail)->key);
    return 0;
}

int int_set_insert(int_set_table* my_set_table, const char* key, const int value)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % my_set_table->hashmap_size;

    //printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    int_set_list_item* head = my_set_table->items[index];

    singly_list_item* tail = list_get_tail(&head->set_list_item.list_item);

    //if no tail = no head
    if(!tail) {

        my_set_table->items[index] = malloc(sizeof(int_set_list_item));

        if (!my_set_table->items[index])
        {
            RED_PRINT("Cannot allocate enough memory!");
            return -1;
        }

        my_set_table->items[index]->set_list_item.key = key;
        my_set_table->items[index]->set_list_item.key_len = key_len;
        my_set_table->items[index]->set_list_item.list_item.next = NULL;
        my_set_table->items[index]->set_list_item.list_item.count = 1;
        my_set_table->items[index]->value = value;

        

        GREEN_PRINT("[%s] ADDED ELEMENT AT THE INDEX %llu!",key, index);
        return 0;
    }

    if(GET_INT_SET_ITEMS_COUNT(my_set_table,index) >= my_set_table->hashmap_singly_max_length)
    {
        RED_PRINT("CANNOT ADD [%s] MAX SLOTS ITEMS FOR THIS INDEX ALREADY REACHED!", key);
        return -1;
    }

    /*if(set_find(TO_GENERIC_SET(my_set_table) ,key, NULL))
    {
        RED_PRINT("THE ELEMENT [%s] WAS ALREADY IN THE SET AND WAS NOT ADDED AGAIN!",key);
        return -1; 
    }*/
    
    // if has a tail
    int_set_list_item* new_item = malloc(sizeof(int_set_list_item));

    if (!new_item)
    {
        RED_PRINT("Cannot allocate enough memory!");
        return -1;
    }

    new_item->set_list_item.key = key;
    new_item->set_list_item.key_len = key_len;
    new_item->set_list_item.list_item.next = NULL;
    new_item->value = value;

    tail->next = &(new_item->set_list_item.list_item);
    my_set_table->items[index]->set_list_item.list_item.count++;

    GREEN_PRINT("ADDED [%s] IN THE %d SLOT AT THE INDEX %llu AFTER THE [%s]!",key, GET_INT_SET_ITEMS_COUNT(my_set_table,index) , index, ((int_set_list_item*)tail)->set_list_item.key);
    return 2;
}

void set_list_print(set_list_item* head)
{
    if(!head)
    {
        RED_PRINT("#The list is empty!");
        return;
    }

    set_list_item* current_item = head;

    BLUE_PRINT("#The list length is = %d",head->list_item.count);

    for (int i = 0; i < head->list_item.count; i++)
    {
        WHITE_PRINT("[%d] == %s",i,current_item->key);  

        if(!current_item->list_item.next) continue;
        current_item = (set_list_item*)(current_item->list_item.next);
    }
}

void set_print(const set_table* set_table)
{
    set_list_item* print_node;

    for (int i = 0; i < set_table->hashmap_size; i++)
    {
        print_node = set_table->items[i];

        if(!print_node) continue;

        for (int j = 0; j < set_table->hashmap_singly_max_length; j++)
        {
            WHITE_PRINT("index %d slot %d [%s], length = %llu",i,j+1, print_node->key, print_node->key_len);

            if(print_node->list_item.next)
            {
                print_node = (set_list_item*)print_node->list_item.next;
            }
            else break;
        }        
    }    
}

void int_set_print(const int_set_table* set_table)
{
    int_set_list_item* print_node;

    for (int i = 0; i < set_table->hashmap_size; i++)
    {
        print_node = set_table->items[i];

        if(!print_node) continue;

        for (int j = 0; j < set_table->hashmap_singly_max_length; j++)
        {
            WHITE_PRINT("KEY = [%s], VALUE = %d",print_node->set_list_item.key, print_node->value);

            if(print_node->set_list_item.list_item.next)
            {
                print_node = (int_set_list_item*)print_node->set_list_item.list_item.next;
            }
            else break;
        }        
    }   
}

set_list_item* set_remove(set_table* set_table, const char* key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % set_table->hashmap_size;

    size_t founded_slot;

    set_list_item* to_remove_item = set_find(set_table,key,&founded_slot);

    if(!to_remove_item)
    {
        return NULL;
    }

    set_list_print((set_table)->items[index]);

    list_remove_item_at_index(((struct singly_list_item**)(&(set_table)->items[index])), founded_slot);

    set_list_print((set_table)->items[index]);

    return to_remove_item;
}

void set_free(set_table** set_table)
{
    set_list_item* free_node;

    for (int i = 0; i < (*set_table)->hashmap_size; i++)
    {
        free_node = (*set_table)->items[i];

        if(!free_node) continue;

        for (int j = 0; j < (*set_table)->hashmap_singly_max_length; j++)
        {
            GREEN_PRINT("#Cleaning the address of [%s] => %p",free_node->key,free_node);

            set_list_item* next_node = (set_list_item*)free_node->list_item.next;

            free(free_node);

            if(next_node)
            {
                free_node = next_node;
            }
            else break;
        }        
    }
}