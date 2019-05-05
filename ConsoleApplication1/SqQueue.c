#ifndef SqQueue_C
#define SqQueue_C

#include "SqQueue.h"

typedef int QElementType;

Status InitSqQueue(SqQueue *Q)
{
	Q->rear = Q->front = 0;
	return OK;
}

int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front+MAXQSIZE)%MAXQSIZE;

}

Status EnQueue(SqQueue* Q, QElementType e)
{
	if (Q->rear +1 == Q->front)
	{
		return ERROR;
	}
	Q->data[Q->rear + 1] = e;
	Q->rear = (Q->rear + 1)%MAXQSIZE;
	return OK;
}

Status DeQueue(SqQueue* Q, QElementType *e)
{
	if (Q->front == Q->rear)
	{
		return ERROR;
	}
	/*����ͷԪ�ظ�ֵ��e*/
	*e = Q->data[Q->front];
	/*ָ�����һλ*/
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

#endif