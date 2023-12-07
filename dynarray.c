#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct aiv_dynarray
{
    size_t count;
    size_t capacity;
    size_t item_size;
    void *data;
};

struct aiv_dynarray* aiv_dynarray_init(const size_t initial_capacity, const size_t item_size)
{
    struct aiv_dynarray* dynarray = malloc(sizeof(struct aiv_dynarray));
    if (!dynarray)
    {
        return NULL;
    }

    dynarray->count = 0;
    dynarray->capacity = initial_capacity;
    dynarray->item_size = item_size;
    dynarray->data = malloc(item_size * initial_capacity);
    if (!dynarray->data)
    {
        free(dynarray);
        return NULL;
    }

    return dynarray;
}

long long aiv_dynarray_add(struct aiv_dynarray* dynarray, const void* value)
{
    if (dynarray->count + 1 > dynarray->capacity)
    {
        printf("reached capacity!\n");
        // REALLOC!
        dynarray->capacity *= 2;
        void* new_data = realloc(dynarray->data, dynarray->item_size * dynarray->capacity);
        if (!new_data)
        {
            printf("FAILED TO REALLOC!\n");
            return -1;
        }
        dynarray->data = new_data;
    }
    else
    {
        //cast because the compiler dosen't know what a void* is and how much memory it deservers so to move byte to byte we use a char* (pointer math theory)
        memcpy(((char*)dynarray->data) + (dynarray->item_size * dynarray->count), value, dynarray->item_size);
    }

    dynarray->count++;

    return dynarray->count-1;
}

int main(int argc, char **argv)
{
    struct aiv_dynarray* myarray = aiv_dynarray_init(2, sizeof(int));
    if (!myarray)
    {
        printf("unable to create dynamic array\n");
        return -1;
    }

    printf("dynarray created at %p (data at %p)\n", myarray, myarray->data);

    int value = 100;
    for(int i = 0; i < 10; i++)
    {
        printf("added at %lld\n", aiv_dynarray_add(myarray, &value));
        printf("capacity: %llu\n", myarray->capacity);
    }

    return 0;
}