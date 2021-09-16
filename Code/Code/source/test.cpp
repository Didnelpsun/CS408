// 测试文件
#include <iostream>
#include "../head/sequence_list.h"
#include "../head/link_list.h"
#include "../head/double_link_list.h"
#include "../head/static_link_list.h"
#include "../head/sequence_stack.h"

using namespace std;

bool SequenceListTest() {
    DynamicSequenceList list;
    InitSequenceList(list);
    element_type a[6] = {'1','2','3','4','5','6'};
    LoopInsertSequenceList(list, a, 0, 6);
    //printf("%d", list.length);
    PrintSequenceList(list);
    printf("\n");
    int len = 2;
    element_type elem[2];
    MultiDeleteSequenceList(list, 0, len, elem);
    PrintSequenceList(list);
    for (int i = 0; i < len; i++) {
        printf("%c\n", elem[i]);
    }
    cout << EmptySequenceList(list) << endl;
    return true;
}

bool LinkListTest() {
    element_type a[6] = { '0', '1','2','3','4','5' };
    LinkList list = InitLinkList();
    cout << EmptyLinkList(list) << endl;
    //InsertLinkListWithoutHead(list, 0, '2');
    InsertLinkListWithoutHead(list, 0, '4');
    //InsertLinkListWithHead(list, 1, '5');
    PriorInsertLinkList(list, a, 1, 5);
    PrintLinkList(list);
    int length = 2;
    //element_type* data = DeleteLinkListWithHead(list, 2, length);
    element_type* data = DeleteLinkListWithoutHead(list, 2, length);
    PrintLinkList(list);
    for (int i = 0; i < length; i++) {
        printf("第%d为%c\n", i, data[i]);
    }
    printf("长度为%d", GetLengthLinkList(list));
    printf("%c地址%d", '3', LocateLinkList(list, '3'));
    return true;
}