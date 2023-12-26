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

struct singly_list_item* list_pop(struct singly_list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct singly_list_item* current_head = *head;
    const unsigned int current_count = (*head)->count;
    *head = (*head)->next;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next  = NULL;

    SET_RED_PRINT();
    printf("#Removed the head element\n");
    SET_DEFAULT_PRINT();  

    return current_head;
}

struct singly_list_item* list_remove_item_at_index(struct singly_list_item** head,const size_t index)
{
    if(!(*head) || index > (*head)->count) 
    {           
        SET_RED_PRINT();
        printf("#Can't remove the item at index %llu \n",index);
        SET_DEFAULT_PRINT(); return NULL;
    }

    if(index == 0) 
    {
        return list_pop(head);
    }

    struct singly_list_item* current_item = (*head)->next;
    struct singly_list_item* previous_item = (*head);

    for (int i = 1; i < (*head)->count; i++)
    {
        if(i == index)
        {
            previous_item->next = current_item->next;
            (*head)->count--;
            current_item->next=NULL;

            SET_RED_PRINT();
            printf("#Removed the element at index %d \n",i);
            SET_DEFAULT_PRINT();
            return current_item;
        }

        previous_item = current_item;
        current_item = current_item->next;
    } 

    SET_RED_PRINT();
    printf("#Index not founded\n");
    SET_DEFAULT_PRINT();
    return NULL;
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

int set_insert(set_table* set_table, const char* key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % set_table->hashmap_size;

    //printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    set_list_item* head = set_table->items[index];

    struct singly_list_item* tail = list_get_tail(&head->list_item);

    //if no tail = no head
    if(!tail) {

        set_table->items[index] = malloc(sizeof(set_list_item));

        if (!set_table->items[index])
        {
            RED_PRINT("Cannot allocate enough memory!");
            return -1;
        }

        set_table->items[index]->key = key;
        set_table->items[index]->key_len = key_len;
        set_table->items[index]->list_item.next = NULL;
        set_table->items[index]->list_item.count = 1;

        GREEN_PRINT("[%s] ADDED ELEMENT AT THE INDEX %llu!",key, index);
        return 0;
    }

    if(set_table->items[index]->list_item.count >= set_table->hashmap_singly_max_length)
    {
        RED_PRINT("CANNOT ADD [%s] MAX SLOTS ITEMS FOR THIS INDEX ALREADY REACHED!", key);
        return -1;
    }

    if(set_find(set_table,key, NULL))
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
    set_table->items[index]->list_item.count++;

    GREEN_PRINT("ADDED [%s] IN THE %d SLOT AT THE INDEX %llu AFTER THE [%s]!",key, set_table->items[index]->list_item.count , index, ((set_list_item*)tail)->key);
    return 0;
}

void list_print(struct singly_list_item* head)
{
    if(!head)
    {
        SET_RED_PRINT();
        printf("#The list is empty!\n");
        SET_DEFAULT_PRINT();
        return;
    }

    struct singly_list_item* current_item = head;

    SET_GREEN_PRINT();
    printf("#The list length is = %d\n",head->count);
    SET_DEFAULT_PRINT();

    for (int i = 0; i < head->count; i++)
    {
        printf("[%d] == %s \n",i, ((set_list_item*)current_item)->key);  

        if(!current_item->next) continue;
        current_item = current_item->next;
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

    list_print((struct singly_list_item*)(set_table)->items[index]);

    list_remove_item_at_index(((struct singly_list_item**)(&(set_table)->items[index])), founded_slot);

    list_print((struct singly_list_item*)(set_table)->items[index]);

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

int main(int argc, char** argv)
{
    set_table* animals_set = create_new_set_table(2, 4);

    set_insert(animals_set, "Cow");
    set_insert(animals_set, "Dog");
    set_insert(animals_set, "Cat");
    set_insert(animals_set, "Ant");
    set_insert(animals_set, "Bee");
    set_insert(animals_set, "Bear");
    set_insert(animals_set, "Pig");
    set_insert(animals_set, "Cow");

    set_print(animals_set);
    
    set_remove(animals_set,"Human");
    set_remove(animals_set,"Bee");
    
    set_list_item* founded_element = set_find(animals_set, "Bee", NULL);

    set_print(animals_set);

    set_free(&animals_set);

    return 0;
}