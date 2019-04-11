#include "AvlTree.h"
#include <stdio.h>

typedef int ElementType;

//��������Ľڵ�ni,ni+1�����Ϊ�Ӹ���ni��Ψһ·�����ȡ���ˣ��������Ϊ0��
//ni�ĸ��Ǵ�ni��һƬ��Ҷ���·���ĳ������
//��Ҷ�ĸ߶���0��һ�����ĸ߶ȵ��������ĸ߶� 
static int
Height(Position P)
{
	if (P == NULL)
	{
		return -1; //���һ���ӵ㲢�����ڣ���ô����ڵ�ĸ߶�Ϊ-1��������ڣ���ֻ��һ��Ҷ�ӽӵ㣬��ô�߶���0.
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
			printf("�����ڴ����ʧ�ܣ�");
		}
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else if (X < T->Element) //���һ��ֵС�ڸýڵ��ֵ��
	{
		T->Left = Insert(X, T->Left); //�ڸýڵ���������в���
		if (Height(T->Left) - Height(T->Right) == 2)	//��������Ϻ��������߶Ⱥ��������ĸ߶����Ϊ2���ͻ��в�ƽ�ⷢ����
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
