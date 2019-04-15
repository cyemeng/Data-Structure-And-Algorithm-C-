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
二叉查找树，对于树中的每一个节点X,他的左子树中所有的关键字值小于X的关键字值，右子树中大于X关键字值。
*/
struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};