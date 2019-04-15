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
	if (T==NULL)//���������Ľӵ�Ϊ��ʱ��ֱ�ӷ��ؿ�
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
//�ǵݹ�ʵ��
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
		/*����������һ���ڵ���*/
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
����ڵ���һƬ��Ҷ����ô���Ա�����ɾ����
����ӵ���һ�����ӣ���ýڵ�������丸�ڵ����ָ���ƹ��ýڵ��ɾ��
������������ӣ�
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
	else if (T->Right != NULL && T->Left != NULL) { //�ҵ��˸ýڵ㣬�����ж��������������Ƿ���ڡ�
		/*�滻����������СԪ��*/
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
