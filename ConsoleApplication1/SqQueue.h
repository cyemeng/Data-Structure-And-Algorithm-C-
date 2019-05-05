#ifndef SqQueue_H
#define SqQueue_H

#include <stdio.h>
#include <stdlib.h>	
#include "../common/common.h"

/* �궨�� */

#define MAXQSIZE 1000

typedef QElementType;

typedef struct {
	QElementType data[MAXQSIZE];
	int front;
	int rear;
}SqQueue;

/*��ʼ���ն���*/
Status InitSqQueue(SqQueue* Q);

/*��ȡ���е�ǰԪ�ظ���*/
int QueueLength(SqQueue Q);

/*���*/
Status EnQueue(SqQueue* Q, QElementType e);
/*�����в�Ϊ��,��ɾ��Q�ж�ͷԪ��,��e����ֵ*/
Status DeQueue(SqQueue* Q, QElementType* e);

#endif // !_SqQueue
