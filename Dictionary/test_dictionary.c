#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <dictionary.h>

#define GET_KEY_INT_SET(x) x.set_list_item.key

int main(int argc, char** argv)
{
    int_dictionary* my_dict;

    my_dict = create_new_int_dictionary(9,2,3);

    int_dictionary_insert(my_dict, "CIAO", 10);
    int_dictionary_insert(my_dict, "HELLO", 20);
    int_dictionary_insert(my_dict, "WORLD", 30);
    
    int_dictionary_print(my_dict);
    return 0;
}