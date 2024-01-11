#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <sets.h>

int main(int argc, char** argv)
{
    set_table* animals_set = create_new_set_table(5, 4, INT_TYPE);
    
    generic_set_insert(animals_set, "Cow",(void*)10, NULL);
    generic_set_insert(animals_set, "Dog",(void*)-20, NULL);
    generic_set_insert(animals_set, "Cat",(void*)30, NULL);
    generic_set_insert(animals_set, "Ant",(void*)-40, NULL);
    generic_set_insert(animals_set, "Bee",(void*)50, NULL);
    generic_set_insert(animals_set,"Bear",(void*)-60, NULL);
    generic_set_insert(animals_set, "Pig",(void*)70, NULL);

    generic_set_insert(animals_set, "Cow",(void*)-10, NULL);

    generic_set_print(animals_set);
    
    set_remove(animals_set,"Human");
    set_list_item* bee = set_remove(animals_set,"Bee");
    
    set_list_item* founded_element = set_find(animals_set, "Bee", NULL);

    generic_set_print(animals_set);
    
    set_free(animals_set);
    free(bee);
    
    GREEN_PRINT("#Cleaning the address of [%s] => %p", bee->key, bee);

    return 0;
}