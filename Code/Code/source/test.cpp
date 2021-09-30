// ≤‚ ‘
#include <iostream>
#include "../head/sequence_list.h"
#include "../head/link_list.h"
#include "../head/double_link_list.h"
#include "../head/static_link_list.h"
#include "../head/sequence_stack.h"
#include "../head/link_stack.h"
#include "../head/share_stack.h"
#include "../head/sequence_queue.h"
#include "../head/link_queue.h"
#include "../head/sequence_string.h"
#include "../head/link_string.h"
#include "../head/link_tree.h"
#include "../head/thread_tree.h"
#include "../head/tree.h"
#include "../head/graph.h"
#include "../head/search.h"
#include "../head/sort.h"

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
    element_type* elem = MultiDeleteSequenceList(list, 0, len);
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
        printf("??%d?%c\n", i, data[i]);
    }
    printf("?????%d", GetLengthLinkList(list));
    printf("%c???%d", '3', LocateLinkList(list, '3'));
    return true;
}

bool SortTest(){
    LinearTable table;
    int a[3] = {2,4,1};
    table.data = a;
    table.length = 3;
    StraightInsertSort(table);
    printf("%d", table.data[0]);
    printf("%d", table.data[1]);
    printf("%d", table.data[2]);
    return true;
}