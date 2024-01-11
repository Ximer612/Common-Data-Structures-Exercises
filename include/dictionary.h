#include <sets.h>
#include <stdlib.h>


typedef struct int_dictionary
{
    set_table set;
}int_dictionary;

int_dictionary* create_new_int_dictionary(const size_t hashmap_size, const size_t hashmap_singly_max_length);
int int_dictionary_insert(int_dictionary* dict, const char* key, const int value);
void int_dictionary_print(int_dictionary* dict);
void free_int_dictionary(int_dictionary* dict);