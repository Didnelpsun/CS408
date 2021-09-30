#include "head.h"

// 邻接矩阵图
typedef struct {
    // 顶点表
    element_type* vex;
    // 边表
    weight_type *edge;
    // 定点数
    int vex_length;
    // 边数
    int edge_length;
} AdjacentArrayGraph;

// 邻接表图
// 边表结点
typedef struct EdgeNode{
    // 该弧指向顶点的位置
    int vex;
    // 指向下条弧的指针
    struct EdgeNode *next;
    // 边权值
    weight_type weigh;
} EdgeNode;

// 顶点表结点
typedef struct VexNode{
    // 顶点信息
    element_type data;
    // 指向第一条依赖该顶点的弧的指针
    EdgeNode* frist;
} VexNode, *AdjacentList;

// 邻接表
typedef struct {
    // 邻接表数据
    AdjacentList data;
    // 顶点数
    int vex_length;
    // 边数
    int edge_length;
} AdjacentListGraph;

