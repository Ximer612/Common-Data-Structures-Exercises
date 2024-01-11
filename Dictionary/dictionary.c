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

    dict->set = *(tmp_set_table);
    free(tmp_set_table);
    //dict->max_collisions = max_collisions;

    return dict;
}

int int_dictionary_insert(int_dictionary* dict, const char* new_item_key, const int new_item_value)
{
    int has_reached_max;
    set_list_item* added_item = int_set_insert(&dict->set,new_item_key,new_item_value,&has_reached_max);
    
    if(!added_item)
    {
        if(has_reached_max == 1) //1 = too much collisions
        {

            CYAN_PRINT("Starting doubling of the dictionary!");

            int_set_list_item* actual_item;
            char* key;
            int value;

            double_dictionary:

            set_table* tmp_set_table = create_new_set_table(dict->set.hashmap_size*2,dict->set.hashmap_singly_max_length);

            if(!tmp_set_table) return -1;

            for (size_t i = 0; i < dict->set.hashmap_size; i++)
            {
                actual_item = (int_set_list_item*)dict->set.items[i];

                if(!actual_item) continue;

                singly_loop:

                char* key = (char*)actual_item->set_list_item.key;
                int value = actual_item->value;

                int_set_insert(tmp_set_table,key,value,&has_reached_max);
                if(has_reached_max == 1) goto double_dictionary;

                if(!actual_item->set_list_item.list_item.next) continue;

                actual_item = (int_set_list_item *)actual_item->set_list_item.list_item.next;
                key = (char*)actual_item->set_list_item.key;
                value = actual_item->value;
                goto singly_loop;
            }            

            //try again to add this item
            int_set_insert(tmp_set_table,new_item_key,new_item_value,&has_reached_max);

            dict->set = *(tmp_set_table);

            if(has_reached_max == 1)
            {
                goto double_dictionary;
            } 

            free(tmp_set_table);

            MAGENTA_PRINT("Dictionary size doubled successfully!");

            return 0;            
        }
        
        return -1;

    }

    return 0;
}

void int_dictionary_print(int_dictionary* dict)
{
    BLUE_PRINT("Dictionary length = %llu, Singly max length = %llu",dict->set.hashmap_size, dict->set.hashmap_singly_max_length);
    int_set_print(&dict->set);  
}

void free_int_dictionary(int_dictionary* dict)
{
    set_free((set_table*)&dict->set);
}
