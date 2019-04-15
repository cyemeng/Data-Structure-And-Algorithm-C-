#include "AvlTree.h"
#include <stdio.h>
#include <stdlib.h>


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

static int Max(int a, int b) {
	if (a < b) {
		return b;
	}
	else
	{
		return a;
	}
}

/*
平衡二叉树在 K2 节点不平衡时候的操作
					k2
				  /   \
				k1	   Z
			  /    \
			X		Y
因为K1左子树高度比右子树高度大二。对K2,K1旋转后，
K2左子树高度加减去1，K2右子树减去一，一加一减，正好平衡
*/

static Position SingleRotateWithLeft(Position K2)
{
	Position K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(K2->Left->Height, K2->Right->Height) + 1;
	K1->Height = Max(K1->Left->Height, K1->Right->Height) + 1;
	return K1;
}
/*

			  K1

		 ?			K2
				  /   \
				X	   K3
					  / \
					 Y	 Z

			  K1

		 ?			K3
				  /   \
				K2	   Z
			  X	  Y
*/
static Position SingleRotateWithRight(Position K2)
{
	Position K3 = K2->Right;
	K2->Right = K3->Left;
	K3->Left = K2;

	K2->Height = Max(K2->Left->Height, K2->Right->Height) + 1;
	K3->Height = Max(K3->Left->Height, K3->Right->Height) + 1;
	return K3;
}

/*
This function can be called only if K3 has a left child,and K3's left child has a right child.
Do the left-right double rotation. Update heights, then return new root.

					 k3
				  /    \
				k1	     D
			  /   \
			A	   k2
				  B  C
在K3节点处，左子树高度位2，右子树高度为0，出现了失衡状态
那么
我么你可以先对K1,K2做一次右侧单旋操作，切换成标转左侧失衡状态，再做一次左侧单玄操作
*/
static Position DoubleRotateWithLeft(Position K3)
{
	// roate between K1 K2
	K3->Left = SingleRotateWithRight(K3->Left);
	// roate between K3 K2
	return SingleRotateWithLeft(K3);
}

/*
This function can be called only if K3 has a right child,and K3's right child has a left child.
Do the right-left double rotation. Update heights, then return new root.

					  k1
				  /       \
				D           k3	     
						  /   \
						k2     A	   
					   B  C
在K1节点处，左子树高度位0，右子树高度为2，出现了失衡状态
那么
我么你可以先对K1,K3做一次左侧侧单旋操作，切换成标转左侧失衡状态，再做一次左侧单玄操作
*/
static Position DoubleRotateWithRight(Position K1)
{
	K1->Right = SingleRotateWithLeft(K1->Right);
	return SingleRotateWithRight(K1);
}


AvlTree MakeEmpty(AvlTree T)
{
	if (T != NULL){
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

AvlTree Insert(ElementType X, AvlTree T)
{
	if (T == NULL)
	{
		T = malloc(sizeof(struct AvlNode));
		if (T == NULL)
		{
			printf("错误，内存分配失败！");
			return NULL;
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
				T = SingleRotateWithLeft(T); 
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->Element)
	{
		T->Right = Insert(X, T);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (X > T->Right->Element)
			{
				T = SingleRotateWithRight(T);
			}
			else
			{
				T = DoubleRotateWithRight(T);
			}
		}
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

//非递归实现
Position FindMax(AvlTree T)
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


Position FindMin(AvlTree T)
{
	if (T == NULL)//当搜索树的接点为空时候，直接返回空
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

Position Find(ElementType X, AvlTree T) {
	if (T == NULL)
		return NULL;
	if ( X < T->Element)
		return Find(X, T->Left);
	else if ( X > T->Element)
		return Find(X, T->Right);
	else
		return T;
}
/*
	如果待删除的节点是树叶，那么可以立即删除
	如果节点有一个孩子，那么该节点绕过父节点后删除。
	如果有两个孩子；一般的策略是用其右子树的最小的数据代替该节点的数据并且递归的删除那个节点，现在他是空的
	因为右子树中最小的节点不可能有左孩子，所以，第二次删除的时候很容易
*/
AvlTree Delete(ElementType X, AvlTree T) {
	Position tmpCell;
	if (T == NULL) //当搜寻的节点为空的时候
		return NULL;
	else if (X < T->Element)
	{
		T->Left = Delete(X, T->Left);
	}
	else if (X > T->Element)
	{
		T->Right = Delete(X, T->Right);
	}
	else if (T->Left && T->Right) //找到该节点， //有两个孩子
	{
		tmpCell = FindMin(T->Right);
		T->Element = tmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
	}
	else //有一个孩子
	{
		tmpCell = T;
		if (T->Left == NULL)
		{
			T = T->Right;
		}
		else if (T->Right == NULL) {
			T = T->Left;
		}
		free(tmpCell);
	}
	return T;
}
