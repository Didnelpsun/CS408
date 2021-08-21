// 测试文件

#include "../head/sequence_list.h"
#include "../head/link_list.h"

int SequenceListTest() {
    DynamicSequenceList list;
    element_type a[6] = {'1','2','3','4','5','6'};
    list.LoopInsert(a, 0, 6);
    list.Print();
    element_type b[4];
    list.LoopDelete(1, 3, b);
    list.Print();
    for (int i = 0; i < 3; i++) {
        cout << b[i] << endl;
    }
    list.Destroy();
    return 0;
}

int LinkListTest() {
    LinkListWithHead list;
    //cout << list.Empty() << endl;
    element_type a[6] = { '1','2','3','4','5','6' };
    list.PriorInsert(a, 2, 3);
    list.Print();
    cout << list.GetLength() << endl;
    LinkListWithoutHead list2;
    list2.PriorInsert(a, 2, 3);
    list2.Print();
    cout << list2.GetLength() << endl;
    return 0;
}