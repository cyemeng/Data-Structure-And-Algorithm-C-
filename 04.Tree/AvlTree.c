#include "AvlTree.h"
#include <stdio.h>

typedef int ElementType;

//对于任意的节点ni,ni+1的深度为从根到ni的唯一路径长度。因此，根的深度为0。
//ni的高是从ni到一片树叶的最长路径的长。因此
//树叶的高度是0，一棵树的高度等于他根的高度 
static int
Height(Position P)
{
	if (P == NULL)
	{
		return -1; //如果一个接点并不存在，那么这个节点的高度为-1，如果存在，但只是一个叶子接点，那么高度是0.
	}
	else
	{
		return P->Height;
	}
}

AvlTree MakeEmpty(AvlTree T)
{
	if (T == NULL)
	{
		return NULL;
	}
	else
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
}

AvlTree Insert(ElementType X, AvlTree T)
{
	if (T == NULL)
	{
		T = malloc(sizeof(struct AvlNode));
		if (T == NULL)
		{
			printf("错误，内存分配失败！");
		}
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else if (X < T->Element) //如果一个值小于该节点的值，
	{
		T->Left = Insert(X, T->Left); //在该节点的左子树中插入
		if (Height(T->Left) - Height(T->Right) == 2)	//当插入完毕后，左子树高度和右子树的高度相差为2，就会有不平衡发生。
		{
			if (X < T->Left->Element)
			{
				T = SingleRotateWithLeft(T);
			} 
			else
			{
				T = DooubleRotageWithLeft(T);
			}
		}
		else if (X >T->Element)
		{
			T->Right = Insert(X, T->Right);
			if (Height(T->Left) - Height(T->Right) == 2)
			{
				if (X > T->Right->Element)
					T = SingleRotateWithRight(T);
				else
					T = DoubleRotateWithRight(T);
			}
			T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
			return T;
		}
	}
}
