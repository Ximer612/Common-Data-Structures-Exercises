#ifndef DICTIONARY_DEFINITION
#define DICTIONARY_DEFINITION

#include <sets.h>
#include <stdlib.h>

typedef struct dictionary
{
    set_table set;
}dictionary;


dictionary* create_new_dictionary(const size_t hashmap_size, const size_t hashmap_singly_max_length, const enum VALUE_TYPE value_type);
int dictionary_insert(dictionary* dict, const char* new_item_key, const void* new_item_value);
void dictionary_print(dictionary* dict);
void free_dictionary(dictionary* dict);

#endif