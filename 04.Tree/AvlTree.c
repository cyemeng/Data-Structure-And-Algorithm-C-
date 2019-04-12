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

/*
				k2
			   /
			  /
			K1
		 
*/
static Position SingleRotateWithLeft(Position K2)
{

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
<<<<<<< HEAD
			T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
			return T;
=======
			else
			{
				T = DoubleRotateWithLeft(T);
			}
>>>>>>> 37c69a8ef05fd83ab590be1821f21e4d021a3715
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

//�ǵݹ�ʵ��
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
	if (T == NULL)//���������Ľӵ�Ϊ��ʱ��ֱ�ӷ��ؿ�
	{
		return NULL;
	}
	//��ĳ���ڵ��������Ϊ�յ�ʱ�� ��ֱ�ӷ��ظýڵ�
	//�������������жϣ����������һ�����⣬����ڵ�Ϊ�յ�ʱ���õݹ���ã����ݵ�һ���жϣ���ֱ�ӷ��ؿ�ֵ
	if (T->Left == NULL)
	{
		return T;
	}
	else
	{
		return FindMin(T->Left);//����T�ӵ������������Сֵ��
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

AvlTree Delete(ElementType X, AvlTree T) {
	Position P;
	P = Find(X, T);
	if ( P == NULL) //����Ѱ�Ľڵ�Ϊ�յ�ʱ��
		return T;
	else //����
	{
		
	}
}
