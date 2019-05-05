// Graphic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include "../StackQueue/SqQueue.h"
#define _CRT_SECURE_NO_WARNINGS

typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define INFINITY 65535

typedef struct
{
	/*顶点表*/
	VertexType vexs[MAXVEX];
	/* 邻接矩阵， 可看作边表*/
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes, numEdge;
}MGrapic;

/*边表结点,横向看的*/
typedef struct EdgeNode
{
	/*邻接点域,存储该顶点对应的下标*/
	int adjvex;
	/*用于存储权值*/
	EdgeType weight;
	/*邻域,指向下一个邻接点*/
	struct EdgeNode* next;
}EdgeNode;

/*顶点表节点,纵向看的*/
typedef struct VertextNode
{
	/*顶点域,存储顶点信息*/
	VertexType data;
	/*边表头指针,用来存储边表头起始地址*/
	EdgeNode* firstedge;

}VertextNode, AdjList[MAXVEX]; //多个顶点表节点构成了一个AdjList,

/*该结构中存储了AdjList,而且包含顶点数目,和边的数目,*/
typedef struct
{
	AdjList adjList;
	/*图中当前顶点的数目*/
	int numVertexes, numEdges;
}AGraph;

/*建立图的邻接表结构*/
void CreateALGraphic(AGraph* G)
{
	int i, j, k;
	EdgeNode* e;
	printf_s("请输入节点数目和边数目:\n");
	scanf_s("%d,%d", &G->numVertexes, &G->numEdges);
	/*读取顶点信息,建立顶点表*/
	for ( i = 0; i < G->numVertexes; i++)
	{
		printf_s("请输入节点%d里面存储的数据(字符):\n",i);
		/*输入顶点信息,轮询每个图节点,给他赋值*/
		getchar();
		G->adjList[i].data = getchar();
		/*将对应的图节点的边表值为空表*/
		G->adjList[i].firstedge = NULL;
	}
	/*建立边表*/
	for ( k = 0; k < G->numEdges; k++)
	{
		printf_s("输入边(vi,vj)上的开始结束端点编号:");
		scanf_s("%d,%d", &i, &j);
		/*向内存申请空间*/
		/*生成边表节点*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*邻接序号为j*/
		e->adjvex = j;
		/*将e指针指向当前顶点指向的节点*/
		e->next = G->adjList[i].firstedge;//e接管了他的next
		/*将当前指针指向e*/
		G->adjList[i].firstedge = e;//他的next 指向e,其实上面两个步骤就是链表的插入步骤
		/*向内存申请空间*/
		/*生成边表结点*/
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		/*邻接序号为i*/
		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}

void CreateMGrapic(MGrapic* G)
{
	int i, j, k, w;
	printf("请输入定点数和边数:\n");
	scanf_s("%d,%d", &G->numVertexes, &G->numEdge);
	/*读取定点信息，建立顶点表*/
	for ( i = 0; i < G->numVertexes	; i++)
	{
		scanf_s(&G->vexs[i]);
	}
	for ( i = 0; i < G->numVertexes; i++)
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			/*初始化邻接矩阵*/
			G->arc[i][j] = INFINITY;
		}
	}
	/*读取numedge条边,建立邻接矩阵*/
	for ( k = 0; k < G->numEdge; k++)
	{
		printf("输入第%d条边(vi,vj)上的上标i,下标J,和权w:\n", k);
		scanf_s("%d,%d,%d", &i, &j, &w);
		G->arc[i][j] = w;
		/*因为无向图,矩阵对称*/
		G->arc[j][i] = G->arc[i][j];	
	}
}

/*图的深度优先遍历*/
void DFS(AGraph* G,int v, int *visited)
{
	VertextNode V = G->adjList[v];
	EdgeNode *e;
	
	printf("遍历的第%d节点:%c\n", v, V.data);
	visited[v] = 1;
	e = V.firstedge;
	while (e != NULL)
	{
		if (visited[e->adjvex] == 0) {
			DFS(G, e->adjvex, visited);
		}
		e = e->next;
	}
}

void BFS(AGraph *G, int v, int visited[MAXVEX])
{
	int j;
	EdgeNode* e;
	SqQueue* Q;
	Q = malloc(sizeof(SqQueue));
	if (Q == NULL)
		return ERROR;
	InitSqQueue(Q);
	printf("遍历的第%d节点:%c\n", v, G->adjList[v].data);
	visited[v] = 1;
	EnQueue(Q, (QElementType)v);
	if (Q->rear != Q->front)
	{
		DeQueue(Q, &j);
		e = G->adjList[j].firstedge;
		while (e !=NULL)
		{
			if (visited[e->adjvex] == 0) //当前邻接点未访问
			{
				printf("遍历的第%d节点:%c\n", j, G->adjList[j].data);
				visited[e->adjvex] = 1;
				EnQueue(Q, (QElementType)e->adjvex);
			}
			e = e->next;
		}
	}
}

int main()
{
	int visited[MAXVEX];
	int i;
	AGraph* G;
	G = (AGraph*) malloc(sizeof(AGraph));
	if (G != NULL) {
		CreateALGraphic(G);
	}
	for ( i = 0; i < MAXVEX; i++)
	{
		visited[i] = 0;
	}
	BFS(G, 0, visited);
}
