#include "hashtable.h"

int main()
{
    LinkedList list;
    list.first = NULL;
printList(&list);

    enqueue(&list, "a");
    enqueue(&list, "b");
    enqueue(&list, "c");
printList(&list);

    dequeue(&list);
printList(&list);

    Node* a = findItem(&list, "f");
    printf("Find \'a\': %s\n", a->stone);

    destructList(&list);

    return 0;
}