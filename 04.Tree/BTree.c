#pragma once
#include <stdlib.h>
#include "BTree.h"

SearchTree MakeEmpty(SearchTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType X, SearchTree T)
{
	if (T == NULL)
		return NULL;
	if (X < T->Element)
		return Find(X, T->Left);
	if (X > T->Element)
		return Find(X, T->Right);
	else
		return T;
}

Position FindMin(SearchTree T)
{
	if (T==NULL)//当搜索树的接点为空时候，直接返回空
	{
		return NULL;
	}
	//当某个节点的左子树为空的时候 ，直接返回该节点
	//如果不加入这个判断，会产生这样一个问题，当左节点为空的时候，用递归调用，根据第一行判断，会直接返回空值
	if (T->Left == NULL)
	{
		return T;
	}
	else
	{
		return FindMin(T->Left);//搜索T接点左侧子树的最小值，
	}
}
//非递归实现
Position FindMax(SearchTree T)
{
	if (T == NULL)
	{
		return NULL;
	}
	while (T->Right != NULL)
	{
		T = T->Right;
	}
	return T;
}

SearchTree Insert(ElementType X, SearchTree T)
{
	if (T == NULL)
	{
		/*创建并返回一个节点数*/
		T = malloc(sizeof(struct TreeNode));
		if (T == NULL)
		{
			return NULL;
		}
		T->Element = X;
		T->Left = NULL;
		T->Right = NULL;
	}
	else
	if (X < T->Element)
	{
		T->Left = Insert(X, T->Left);
	}
	else
	if (X > T->Element)
	{
		T->Right = Insert(X, T->Right);
	}
	return T;
}
/*
如果节点是一片树叶，那么可以被立即删除。
如果接点有一个儿子，则该节点可以在其父节点调整指针绕过该节点后被删除
如果有两个儿子，
*/
SearchTree Delete(ElementType X, SearchTree T)
{
	Position TmpCell;
	if (T ==NULL)
	{
		printf("Element Not Found!");
	}
	else if (X < T->Element)
	{
		T->Left = Delete(X, T->Left);
	}
	else if (X > T->Element)
	{
		T->Right = Delete(X, T->Right);
	}
	else if (T->Right != NULL && T->Left != NULL) { //找到了该节点，再来判断他的左右子树是否存在。
		/*替换右子树的最小元素*/
		TmpCell = FindMin(T->Right);
		T->Element = TmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
	}
	else
	{
		TmpCell = T;
		if (T->Left == NULL)
		{
			T = T->Right;
		}
		else if (T->Right == NULL)
		{
			T = T->Left;
		}
		free(TmpCell);
	}
	return T;
}
