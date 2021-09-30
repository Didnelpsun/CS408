#include "head.h"

// ˫�ױ�ʾ��
// ���
typedef struct {
    element_type data;
    // ˫��λ��
    int parent;
} ParentTreeNode;
// ��
typedef struct {
    // ����
    ParentTreeNode* data;
    // ����
    int length;
    // �������
    int max_length;
} ParentTree;

// �����ֵܱ�ʾ��
// ���
typedef struct ChildSiblingTreeNode {
    // ����
    element_type data;
    // ��һ������
    struct ChildSiblingTreeNode *frist_child;
    // ��һ���ֵ�
    struct ChildSiblingTreeNode *next_sibling;
} ChildSiblingTreeNode, *ChildSiblingTree;