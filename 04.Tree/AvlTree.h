#pragma once
#ifndef _AvlTree_H

typedef ElementType;
struct AvlNode;
typedef struct AvlNode* Position;
typedef struct AvlNode* AvlTree;
//创建空的平衡二叉树
AvlTree MakeEmpty(AvlTree T);
//查找平衡二叉树，返回对应的节点位置
Position Find(ElementType X, AvlTree T);
//查找最大值
Position FindMax(AvlTree T);
//查找最小值
Position FindMin(AvlTree T);
//插入
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
ElementType Retrieve(Position P);


#endif // !_AvlTree_H

struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
};
