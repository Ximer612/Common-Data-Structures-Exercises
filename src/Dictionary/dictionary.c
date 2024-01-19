#include <sets.h>
#include <stdlib.h>
#include <dictionary.h>
#include <stdlib.h>
#define DEBUG_PRINT
#include <console_utilities.h>

dictionary* create_new_dictionary(const size_t hashmap_size, const size_t hashmap_singly_max_length, const enum VALUE_TYPE value_type)
{
    if(hashmap_size < 1 || hashmap_singly_max_length < 1)
    {
        RED_PRINT("Insert a valid number!");
        return NULL;
    }

    dictionary* dict = malloc(sizeof(dictionary));

    if (!dict)
    {
        RED_PRINT("Cannot alloc memory for dictionary");
        return NULL;
    }
    
    set_table* tmp_set_table = create_new_set_table(hashmap_size,hashmap_singly_max_length, value_type);

    if(!tmp_set_table)
    {
        free(dict);
        return NULL;
    }

    dict->set = *(tmp_set_table);
    tmp_set_table->value_type = value_type;
    free(tmp_set_table);

    return dict;
}

int dictionary_insert(dictionary* dict, const char* new_item_key, const void* new_item_value)
{
    int has_reached_max;
    set_list_item* added_item = generic_set_insert(&dict->set,new_item_key,(void*)new_item_value,&has_reached_max);
    
    if(!added_item)
    {
        if(has_reached_max == 1) //1 = too much collisions
        {
            CYAN_PRINT("Starting doubling of the dictionary!");

            generic_set_list_item* actual_item;
            char* key;
            void* value;

            double_dictionary:

            set_table* tmp_set_table = create_new_set_table(dict->set.hashmap_size*2,dict->set.hashmap_singly_max_length, dict->set.value_type);

            if(!tmp_set_table) return -1;

            for (size_t i = 0; i < dict->set.hashmap_size; i++)
            {
                actual_item = (generic_set_list_item*)dict->set.items[i];

                if(!actual_item) continue;

                singly_loop:

                char* key = (char*)actual_item->set_list_item.key;
                value = actual_item->value;

                generic_set_insert(tmp_set_table,key,(void*)value,&has_reached_max);
                if(has_reached_max == 1) goto double_dictionary;

                if(!actual_item->set_list_item.list_item.next) continue;

                actual_item = (generic_set_list_item*)actual_item->set_list_item.list_item.next;
                key = (char*)actual_item->set_list_item.key;
                value = actual_item->value;
                goto singly_loop;
            }            

            //try again to add this item
            generic_set_insert(tmp_set_table,new_item_key,(void*)new_item_value,&has_reached_max);

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

void dictionary_print(dictionary* dict)
{
    BLUE_PRINT("Dictionary length = %llu, Singly max length = %llu",dict->set.hashmap_size, dict->set.hashmap_singly_max_length);
    generic_set_print(&dict->set);  
}

void free_dictionary(dictionary* dict)
{
    set_free((set_table*)&dict->set);
}
