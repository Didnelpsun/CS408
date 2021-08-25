// 测试文件

#include "../head/sequence_list.h"
#include "../head/link_list.h"

int SequenceListTest() {
    DynamicSequenceList list;
    element_type a[6] = {'1','2','3','4','5','6'};
    list.LoopInsert(a, 0, 6);
    list.Print();
    element_type* b = list.LoopDelete(1, 3);
    list.Print();
    for (int i = 0; i < 3; i++) {
        cout << b[i] << endl;
    }
    list.Destroy();
    return 0;
}

int LinkListTest() {
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
    int len = 3;
    element_type* b = list->Delete(2, len);
    for (int i = 0; i < len; i++) {
        cout << b[i] << endl;
    }
    list->Print();
    return 0;
}