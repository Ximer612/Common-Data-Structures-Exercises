#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <console_utilities.h>

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
} set_table;

size_t djb33x_hash(const char* key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

set_table* create_new_set_table(const size_t hashmap_size)
{
    set_table* table = malloc(sizeof(set_table));
    if (!table)
    {
        RED_PRINTF("Cannot alloc memory for table");
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->items = calloc(table->hashmap_size, sizeof(set_list_item**)); //calloc because there can be everything in this nodes

    if (!table->items)
    {
        free(table);
        RED_PRINTF("Cannot alloc memory for table's items");
        return NULL;
    }

    GREEN_PRINTF("Created set table successfully!");
    return table;
}

void set_insert(set_table** set_table, const char* key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % (*set_table)->hashmap_size;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    set_list_item* head = (*set_table)->items[index];
    set_list_item* tail;

    while (head)
    {
        tail = head;
        head = (set_list_item*)head->list_item.next;
    }
    


    // for (size_t i = 0; i < GET_SET_ITEMS_COUNT(set,index); i++)
    // {
    //     if (set->hashmap[index][i].key_len == 0)
    //     {
    //         set->hashmap[index][i].key = key;
    //         set->hashmap[index][i].key_len = key_len;
    //         printf("added %s at index %llu slot %llu\n", key, index, i);
    //         return;
    //     }
    // }
    BLUE_PRINTF("ADDED ELEMENT!");
    return;
}

// void set_find(struct set_table* set, const char* key)
// {
//     const size_t key_len = strlen(key);

//     const size_t hash = djb33x_hash(key, key_len);

//     const size_t index = hash % HASHMAP_SIZE;

//     printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

//     for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
//     {
//         if (set->hashmap[index][i].key_len > 0)
//         {
//             if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
//             {
//                 printf("FOUND %s at index %llu slot %llu\n", key, index, i);
//                 return;
//             }
//         }
//     }
// }

void set_print(set_table* set)
{

}

int main(int argc, char** argv)
{
    set_table* my_set_table = create_new_set_table(64);
    set_insert(&my_set_table, "Hello");

    //struct set_table myset;
    //memset(&myset, 0, sizeof(struct set_table));

    //set_insert(&myset, "Hello2");
    //set_insert(&myset, "Test");
    //set_insert(&myset, "Foobar");
    //set_insert(&myset, "XYZ");
    //set_insert(&myset, "AAAAAA");
    //set_insert(&myset, "AAAAAa");

    //set_find(&myset, "XYZ");

    //set_print(&myset);

    return 0;
}