#ifndef _BtreeNode_H
#include <stdio.h>

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType, SearchTree T);
ElementType Retrieve(Position P);


#endif // !_Btree_H

/*
������������������е�ÿһ���ڵ�X,���������������еĹؼ���ֵС��X�Ĺؼ���ֵ���������д���X�ؼ���ֵ��
*/
struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};