#include "head.h"

// 双亲表示法
// 结点
typedef struct {
    element_type data;
    // 双亲位置
    int parent;
} ParentTreeNode;
// 数
typedef struct {
    // 数组
    ParentTreeNode* data;
    // 长度
    int length;
    // 最大容量
    int max_length;
} ParentTree;

// 孩子兄弟表示法
// 结点
typedef struct ChildSiblingTreeNode {
    // 数据
    element_type data;
    // 第一个孩子
    struct ChildSiblingTreeNode *frist_child;
    // 下一个兄弟
    struct ChildSiblingTreeNode *next_sibling;
} ChildSiblingTreeNode, *ChildSiblingTree;