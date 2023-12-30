#include <sets.h>

// typedef struct
// {
//     set_table set; //24
//     int max_collisions; //4
// }dictionary;

typedef struct
{
    int_set_table set; //24
    //int max_collisions; //4
    //int actual_collisions;
}int_dictionary;

int_dictionary* create_new_int_dictionary(const size_t hashmap_size, const size_t hashmap_singly_max_length/*, const size_t max_collisions*/);
int int_dictionary_insert(int_dictionary* dict, const char* key, const int value);
void int_dictionary_print(int_dictionary* dict);