#include "TreeNode.h"

typedef int ElementType;

/**
���ӵ�����������ÿ�����Ķ�������Ա仯�ܴ������Ȳ�֪������˽������������ӽڵ�����Ӳ��У�����������ܶ�Ŀռ��˷ѣ�
�����������ÿ���ӵ�����ж��Ӷ��������ڵ������С�
**/
struct TreeNode
{
	ElementType Element;
	PtrToNode FirstChild;
	PtrToNode NextSibing;  //��һ���ֵ�
};