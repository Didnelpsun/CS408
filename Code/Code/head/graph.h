#include "head.h"

// �ڽӾ���ͼ
typedef struct {
    // �����
    element_type* vex;
    // �߱�
    weight_type *edge;
    // ������
    int vex_length;
    // ����
    int edge_length;
} AdjacentArrayGraph;

// �ڽӱ�ͼ
// �߱���
typedef struct EdgeNode{
    // �û�ָ�򶥵��λ��
    int vex;
    // ָ����������ָ��
    struct EdgeNode *next;
    // ��Ȩֵ
    weight_type weigh;
} EdgeNode;

// �������
typedef struct VexNode{
    // ������Ϣ
    element_type data;
    // ָ���һ�������ö���Ļ���ָ��
    EdgeNode* frist;
} VexNode, *AdjacentList;

// �ڽӱ�
typedef struct {
    // �ڽӱ�����
    AdjacentList data;
    // ������
    int vex_length;
    // ����
    int edge_length;
} AdjacentListGraph;

