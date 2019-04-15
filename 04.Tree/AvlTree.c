#include "AvlTree.h"
#include <stdio.h>
#include <stdlib.h>


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
ƽ��������� K2 �ڵ㲻ƽ��ʱ��Ĳ���
					k2
				  /   \
				k1	   Z
			  /    \
			X		Y
��ΪK1�������߶ȱ��������߶ȴ������K2,K1��ת��
K2�������߶ȼӼ�ȥ1��K2��������ȥһ��һ��һ��������ƽ��
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
��K3�ڵ㴦���������߶�λ2���������߶�Ϊ0��������ʧ��״̬
��ô
��ô������ȶ�K1,K2��һ���Ҳ൥���������л��ɱ�ת���ʧ��״̬������һ����൥������
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
��K1�ڵ㴦���������߶�λ0���������߶�Ϊ2��������ʧ��״̬
��ô
��ô������ȶ�K1,K3��һ�����൥���������л��ɱ�ת���ʧ��״̬������һ����൥������
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
			printf("�����ڴ����ʧ�ܣ�");
			return NULL;
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
/*
	�����ɾ���Ľڵ�����Ҷ����ô��������ɾ��
	����ڵ���һ�����ӣ���ô�ýڵ��ƹ����ڵ��ɾ����
	������������ӣ�һ��Ĳ�������������������С�����ݴ���ýڵ�����ݲ��ҵݹ��ɾ���Ǹ��ڵ㣬�������ǿյ�
	��Ϊ����������С�Ľڵ㲻���������ӣ����ԣ��ڶ���ɾ����ʱ�������
*/
AvlTree Delete(ElementType X, AvlTree T) {
	Position tmpCell;
	if (T == NULL) //����Ѱ�Ľڵ�Ϊ�յ�ʱ��
		return NULL;
	else if (X < T->Element)
	{
		T->Left = Delete(X, T->Left);
	}
	else if (X > T->Element)
	{
		T->Right = Delete(X, T->Right);
	}
	else if (T->Left && T->Right) //�ҵ��ýڵ㣬 //����������
	{
		tmpCell = FindMin(T->Right);
		T->Element = tmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
	}
	else //��һ������
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
