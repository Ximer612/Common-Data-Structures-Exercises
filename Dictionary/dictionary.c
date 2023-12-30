#include <sets.h>
#include <stdlib.h>
#include <dictionary.h>
#include <stdlib.h>
#define DEBUG_PRINT
#include <console_utilities.h>

int_dictionary* create_new_int_dictionary(const size_t hashmap_size, const size_t hashmap_singly_max_length/*, const size_t max_collisions*/)
{
    if(hashmap_size < 1 || hashmap_singly_max_length < 1)
    {
        RED_PRINT("Insert a valid number!");
        return NULL;
    }

    int_dictionary* dict = malloc(sizeof(int_dictionary));

    if (!dict)
    {
        RED_PRINT("Cannot alloc memory for dictionary");
        return NULL;
    }
    
    set_table* tmp_set_table = create_new_set_table(hashmap_size,hashmap_singly_max_length);

    if(!tmp_set_table)
    {
        free(dict);
        return NULL;
    }

    dict->set = *((int_set_table*)tmp_set_table);
    free(tmp_set_table);
    //dict->max_collisions = max_collisions;

    return dict;
}

int int_dictionary_insert(int_dictionary* dict, const char* new_item_key, const int new_item_value)
{
    int return_value = int_set_insert(&dict->set,new_item_key,new_item_value);
    if( return_value != -1)
    {
        if(return_value == 2)
        {
            double_dictionary:

            int_set_table* tmp_set_table = (int_set_table*) create_new_set_table(dict->set.hashmap_size*2,dict->set.hashmap_singly_max_length);

            if(!tmp_set_table) return -1;

            int_set_list_item* actual_item;
            char* key;
            int value;

            int_dictionary_print(dict);

            for (size_t i = 0; i < dict->set.hashmap_size; i++)
            {
                actual_item = dict->set.items[i];

                if(!actual_item) continue;

                singly_loop:

                char* key = (char*)actual_item->set_list_item.key;
                int value = actual_item->value;

                return_value = int_set_insert(tmp_set_table,key,value);

                if(!actual_item->set_list_item.list_item.next) continue;

                actual_item = (int_set_list_item *)actual_item->set_list_item.list_item.next;
                key = (char*)actual_item->set_list_item.key;
                value = actual_item->value;
                goto singly_loop;
            }            

            //try again to add this item
            return_value = int_set_insert(tmp_set_table,new_item_key,new_item_value);

            dict->set = *((int_set_table*)tmp_set_table);

            if(return_value == 2)
            {
                goto double_dictionary;
            } 

            free(tmp_set_table);

            GREEN_PRINT("Dictionary size doubled successfully!");
            
        }
        
        return 0;

    }

    return -1;
}

void int_dictionary_print(int_dictionary* dict)
{
    BLUE_PRINT("Dictionary length = %llu, Singly max length = %llu",dict->set.hashmap_size, dict->set.hashmap_singly_max_length);
    int_set_print(&dict->set);  
}
