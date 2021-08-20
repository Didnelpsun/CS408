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
    //element_type a[6] = { '1','2','3','4','5','6' };
    //list.LoopInsert(a, 1, 6);
    list.Insert(1, '3');
    list.Print();
    list.Insert(2, '4');
    list.Print();
    return 0;
}

