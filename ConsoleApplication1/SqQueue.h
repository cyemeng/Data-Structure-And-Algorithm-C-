#ifndef SqQueue_H
#define SqQueue_H

#include <stdio.h>
#include <stdlib.h>	
#include "../common/common.h"

/* 宏定义 */

#define MAXQSIZE 1000

typedef QElementType;

typedef struct {
	QElementType data[MAXQSIZE];
	int front;
	int rear;
}SqQueue;

/*初始化空队列*/
Status InitSqQueue(SqQueue* Q);

/*获取队列当前元素个数*/
int QueueLength(SqQueue Q);

/*入队*/
Status EnQueue(SqQueue* Q, QElementType e);
/*若队列不为空,则删除Q中队头元素,用e返回值*/
Status DeQueue(SqQueue* Q, QElementType* e);

#endif // !_SqQueue
