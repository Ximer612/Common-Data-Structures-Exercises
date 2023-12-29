#include <sets.h>
#include <dictionary.h>
#include <stdlib.h>
#include <console_utilities.h>

int_dictionary* create_new_int_dictionary(const size_t hashmap_size, const size_t hashmap_singly_max_length, const size_t max_collisions)
{
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
    dict->max_collisions = max_collisions;

    return dict;
}

int int_dictionary_insert(int_dictionary* dict, const char* key, const int value)
{
    int return_value = int_set_insert(&dict->set,key,value);
    if( return_value != -1)
    {
        if(return_value == 2)
        {
            dict->actual_collisions++;

            if(dict->actual_collisions > dict->max_collisions)
            {
                //double the dictionary
                RED_PRINT("TOO MUCH COLLISIONS!");
                return 0;
            }
        }
        
        return 0;

    }

    return -1;
}

void int_dictionary_print(int_dictionary* dict)
{
    int_set_print(&dict->set);  
}
