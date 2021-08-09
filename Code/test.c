// ²âÊÔÎÄ¼þ

#include "head.h"
#include "sequence_list.h"

int SequenceListTest() {
    DynamicSequenceList list;
    InitDynamicSequenceList(&list);
    element_type a[6] = {'1','2','3','4','5','6'};
    LoopInsertDynamicSequenceList(&list, a, 0, 6);
    element_type b[3] = { 9, 'a', 'e' };
    LoopInsertDynamicSequenceList(&list, b, 1, 2);
    //printf("%d", list.length);
    PrintfDynamicSequenceList(list);
    printf("\n");
    element_type elem;
    MultiDeleteDynamicSequenceList(&list, 2, 2, &elem);
    PrintfDynamicSequenceList(list);
    /*DynamicSequenceList dlist;
    InitDynamicSequenceList(&dlist);
    OtherIncreaseDynamicSequenceList(&dlist, 15);
    printf("%d", dlist.max_size);*/
    int index = LocateDynamicSequenceListElement(list, '5');
    printf("%d", index);
    return 0;
}

