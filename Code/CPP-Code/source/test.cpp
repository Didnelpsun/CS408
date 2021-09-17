// 测试文件

#include "../head/sequence_list.h"
#include "../head/link_list.h"
#include "../head/double_link_list.h"
#include "../head/static_link_list.h"
#include "../head/sequence_stack.h"
#include "../head/share_stack.h"
#include "../head/link_stack.h"
#include "../head/sequence_queue.h"
#include "../head/link_queue.h"

bool SequenceListTest() {
    DynamicSequenceList list;
    element_type a[6] = {'1','2','3','4','5','6'};
    list.LoopInsert(a, 0, 6);
    list.Print();
//    element_type * data = list.GetData();
    element_type* b = list.LoopDelete(1, 3);
    list.Print();
    for (int i = 0; i < 3; i++) {
        cout << b[i] << endl;
    }
    list.Destroy();
    return true;
}

bool LinkListTest() {
    element_type a[6] = {'0', '1','2','3','4','5' };
//    LinkListWithHead list;
//    list.NextInsert(a, 0, 5);
//    list.Print();
//    list.Delete(2, 4);
//    list.Print();
    /*cout << list.GetLength() << endl;
    LinkListWithoutHead list2;
    list2.PriorInsert(a, 2, 3);
    list2.Print();
    cout << list2.GetLength() << endl;*/
    auto* list = new LinkListWithoutHead();
    list->NextInsert(a, 0 ,5);
    list->Print();
    int len = 2;
    element_type* b = list->Delete(2, len);
    for (int i = 0; i < len; i++) {
        cout << b[i] << endl;
    }
    list->Print();
    cout << list->Locate('1') << endl;
    return true;
}

bool StaticLinkListTest(){
    return true;
}