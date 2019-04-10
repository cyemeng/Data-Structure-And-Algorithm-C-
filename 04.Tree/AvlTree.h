#pragma once
#ifndef _AvlTree_H

typedef ElementType;
struct AvlNode;
typedef struct AvlNode* Position;
typedef struct AvlNode* AvlTree;
//�����յ�ƽ�������
AvlTree MakeEmpty(AvlTree T);
//����ƽ������������ض�Ӧ�Ľڵ�λ��
Position Find(ElementType X, AvlTree T);
//�������ֵ
Position FindMax(AvlTree T);
//������Сֵ
Position FindMin(AvlTree T);
//����
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
