// ²âÊÔÎÄ¼þ

#include "../head/sequence_list.h"
#include "../head/link_list.h"

int SequenceListTest() {
    DynamicSequenceList list;
    list.Insert(0, 'a');
    element_type a[6] = {'1','2','3','4','5','6'};
    list.LoopInsert(a, 0, 6);
    printf("%c", list.data[2]);
    /*element_type b[3] = { '9', 'a', 'e' };
    list.LoopInsert(b, 1, 2);*/
    list.Printf();
    //printf("%c", list.data[2]);
    /*list.Printf();
    printf("\n");
    int len = 2;
    element_type elem[2];
    list.MultiDelete(0, len, elem);*/
    /*list.Printf();
    for (int i = 0; i < len; i++) {
        printf("%c\n", elem[i]);
    }*/
    /*DynamicSequenceList dlist;
    InitDynamicSequenceList(&dlist);
    OtherIncreaseDynamicSequenceList(&dlist, 15);
    printf("%d", dlist.max_size);*/
    //int index = list.Locate('5');
    //printf("%d", index);
    //list.Destroy();
    return 0;
}

int LinkListTest() {
    LinkList list = nullptr;
    InitLinkListWithoutHead(list);
//    InitLinkListWithHead(list);
    //LinkList list = CreateLinkListWithHead();
//    int empty = EmptyLinkListWithHead(list);
//    LinkList list = CreateLinkListWithoutHead();
    int empty = EmptyLinkListWithoutHead(list);
    printf("%d", empty);
    return 0;
}

