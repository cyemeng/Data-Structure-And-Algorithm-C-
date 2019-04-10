#include "TreeNode.h"

typedef int ElementType;

/**
树接点生命，由于每个结点的儿子书可以变化很大且事先不知道，因此建立到各个儿子节点的链接不行，这样会产生很多的空间浪费，
解决方案，将每个接点的所有儿子都放在树节点链表中。
**/
struct TreeNode
{
	ElementType Element;
	PtrToNode FirstChild;
	PtrToNode NextSibing;  //下一个兄弟
};