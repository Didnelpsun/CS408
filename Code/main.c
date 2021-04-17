#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include "sequence_list.h"
#include "link_list.h"

int main()
{
    /*StaticSequenceList static_list;
    InitStaticSequenceList(&static_list);
    DynamicSequenceList dynamic_list;
    InitDynamicSequenceList(&dynamic_list);
    printf("%d\n", dynamic_list.max_size);
    ReIncreaseDynamicSequenceList(&dynamic_list, 25);
    printf("%d\n", dynamic_list.max_size);
    InsertStaticSequenceList(&static_list, 0, 2);
    InsertStaticSequenceList(&static_list, 1, 6);
    InsertStaticSequenceList(&static_list, 2, 5);
    PrintfStaticSequenceList(static_list);
    element_type i = DEFAULTELEM;
    DeleteStaticSequenceList(&static_list, 1, &i);
    PrintfStaticSequenceList(static_list);
    printf("%d", i);
    int elem = 65;
    int index = LocateStaticSequenceListElement(static_list, elem);
    printf("查找元素%d在序列%d位\n", elem, index + 1);
    return 0;*/
    LinkList list;
    InitLinkList(&list);
}