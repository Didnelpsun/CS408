// ²âÊÔÎÄ¼þ

#include "sequence_list.h"
#include "link_list.h"

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
    int len = 2;
    element_type elem[2];
    MultiDeleteDynamicSequenceList(&list, 0, len, elem);
    PrintfDynamicSequenceList(list);
    for (int i = 0; i < len; i++) {
        printf("%c\n", elem[i]);
    }
    /*DynamicSequenceList dlist;
    InitDynamicSequenceList(&dlist);
    OtherIncreaseDynamicSequenceList(&dlist, 15);
    printf("%d", dlist.max_size);*/
    /*int index = LocateDynamicSequenceListElement(list, '5');
    printf("%d", index);
    DestroyDynamicSequenceList(&list);*/
    return 0;
}

int LinkListTest() {
    //LinkList list;
    //InitLinkListWithHead(list);
    //int empty = EmptyLinkListWithHead(list);
    //printf("%d", empty);
    return 0;
}

