#define GET_MY_LIST(x) &(x.list_item)

#define TO_GENERIC_SINGLY_LIST(x) (struct singly_list_item*)(x)
#define TO_GENERIC_SINGLY_LIST_POINTER(x) (struct singly_list_item**)(x)

#define TO_GENERIC_DOUBLY_LIST(x) (struct doubly_list_item*)(x)
#define TO_GENERIC_DOUBLY_LIST_POINTER(x) (struct doubly_list_item**)(x)

#define TO_INT_LIST(x) (struct int_list_item*)(x)
#define TO_INT_LIST_POINTER(x) (struct int_list_item**)(x)
