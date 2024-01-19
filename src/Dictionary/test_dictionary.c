#define DEBUG_PRINT
#include <console_utilities.h>
#include <dictionary.h>

#define GET_KEY_INT_SET(x) x.set_list_item.key

int main(int argc, char** argv)
{
    dictionary* my_dict;

    my_dict = create_new_dictionary(1,2,INT_TYPE);

    dictionary_insert(my_dict, "CIAO",  (void*)10);
    dictionary_insert(my_dict, "HELLO", (void*)20);
    dictionary_insert(my_dict, "WORLD", (void*)30);
    dictionary_insert(my_dict, "TEST",  (void*)40);
    dictionary_insert(my_dict, "FIFTY", (void*)50);
    dictionary_insert(my_dict, "EARTH", (void*)30);
    
    dictionary_print(my_dict);

    free_dictionary(my_dict);
    return 0;
}