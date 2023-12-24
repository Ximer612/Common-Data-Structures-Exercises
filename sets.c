#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <linked_lists.h>

#define GET_SET_ITEMS_COUNT(set_table,index) ((set_table->nodes[index])->list_item.count)

struct singly_list_item
{
    struct singly_list_item* next; 
    unsigned int count;   
};

typedef struct 
{
    struct singly_list_item list_item;
    const char *key;
    size_t key_len;
}set_list_item;  

typedef struct
{
    set_list_item **items; //array of pointers of items
    size_t hashmap_size;
    size_t hashmap_singly_max_length;
} set_table;

struct singly_list_item* list_get_tail(struct singly_list_item* head)
{
    if(!head)
    {
        return NULL;
    }

    struct singly_list_item* current_item = head;
    struct singly_list_item* last_item = NULL;
    
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }
    
    return last_item;
}

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

set_list_item* set_find(set_table* set_table, const char* key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (set_table)->hashmap_size;


    set_list_item* compare_node = set_table->items[index];

    for (size_t i = 0; i < (set_table)->hashmap_singly_max_length; i++)
    {
        if (set_table->items[index]->key_len > 0)
        {
            if (compare_node->key_len == key_len && !memcmp(compare_node->key, key, key_len))
            {
                GREEN_PRINT("FOUND [%s] at index %llu slot %llu", key, index, i+1);
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

int set_insert(set_table** set_table, const char* key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (*set_table)->hashmap_size;

    //printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    set_list_item* head = (*set_table)->items[index];

    struct singly_list_item* tail = list_get_tail(&head->list_item);

    //if no tail = no head
    if(!tail) {

        (*set_table)->items[index] = malloc(sizeof(set_list_item));

        if (!(*set_table)->items[index])
        {
            RED_PRINT("Cannot allocate enough memory!");
            return -1;
        }

        (*set_table)->items[index]->key = key;
        (*set_table)->items[index]->key_len = key_len;
        (*set_table)->items[index]->list_item.next = NULL;
        (*set_table)->items[index]->list_item.count = 1;

        GREEN_PRINT("[%s] ADDED ELEMENT AT THE INDEX %llu!",key, index);
        return 0;
    }

    if((*set_table)->items[index]->list_item.count >= (*set_table)->hashmap_singly_max_length)
    {
        RED_PRINT("MAX ELEMENT FOR THIS INDEX ALREADY ADDED!");
        return -1;
    }

    if(set_find(*set_table,key))
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
    (*set_table)->items[index]->list_item.count++;

    GREEN_PRINT("[%s] ADDED ELEMENT AS %d AT THE INDEX %llu AFTER THE [%s]!",key, (*set_table)->items[index]->list_item.count , index, ((set_list_item*)tail)->key);
    return 0;
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
            printf("index %d slot %d [%s], length = %llu \n",i,j+1, print_node->key, print_node->key_len);

            if(print_node->list_item.next)
            {
                print_node = (set_list_item*)print_node->list_item.next;
            }
            else break;
        }        
    }    
}

set_list_item* set_remove(set_table** set_table)
{


    return NULL;
}

// void set_free(set_table* set_table)
// {
//     set_list_item** print_node;

//     for (int i = 0; i < set_table->hashmap_size; i++)
//     {
//         print_node = set_table->items[i];

//         if(!print_node) continue;

//         for (int j = 0; j < set_table->hashmap_singly_max_length; j++)
//         {
//             printf("FREE index %d slot %d [%s], length = %llu \n",i,j+1, (*print_node)->key, (*print_node)->key_len);

//             free(print_node);

//             if((*print_node)->list_item.next)
//             {
//                 print_node = (set_list_item*)(*print_node)->list_item.next;
//             }
//             else break;
//         }        
//     } 
// }

int main(int argc, char** argv)
{
    set_table* my_set_table = create_new_set_table(64, 4);
    set_insert(&my_set_table, "Hello");
    set_insert(&my_set_table, "Hella");
    set_insert(&my_set_table, "Hilla");
    set_insert(&my_set_table, "Holle");
    set_insert(&my_set_table, "Halla");
    set_insert(&my_set_table, "Hilli");
    set_insert(&my_set_table, "Holla");
    set_insert(&my_set_table, "Hello");

    set_print(my_set_table);
    
    set_list_item* founded_element = set_find(my_set_table, "Holle");

    //printf("%s", ((set_list_item*)my_set_table->items[7]->list_item.next)->key);

    //set_free(&my_set_table);

    return 0;
}