#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG_PRINT
#include <console_utilities.h>
#include <sets.h>

int main(int argc, char** argv)
{
    set_table* animals_set = create_new_set_table(2, 4);

    set_insert(animals_set, "Cow");
    set_insert(animals_set, "Dog");
    set_insert(animals_set, "Cat");
    set_insert(animals_set, "Ant");
    set_insert(animals_set, "Bee");
    set_insert(animals_set, "Bear");
    set_insert(animals_set, "Pig");
    set_insert(animals_set, "Cow");

    set_print(animals_set);
    
    set_remove(animals_set,"Human");
    set_list_item* bee = set_remove(animals_set,"Bee");
    
    set_list_item* founded_element = set_find(animals_set, "Bee", NULL);

    set_print(animals_set);
    
    set_free(&animals_set);
    free(bee);
    GREEN_PRINT("#Cleaning the address of [%s] => %p", bee->key, bee);

    return 0;
}