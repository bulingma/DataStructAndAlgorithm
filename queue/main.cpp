/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

/******************************************************************************************
* Test of queue
******************************************************************************************/
#include<iostream>
using namespace std;
#include "queue.h"
#include "../_share/util.h"
#include "../UniPrint/print.h"

int testID = 0; //���Ա��

/******************************************************************************************
* ����ջ
******************************************************************************************/
template <typename T>						//Ԫ������
void testQueue(int n) {
	Queue<T> Q;
	printf("\n  ==== Test %2d. Growing queue\n", testID++);
	while (Q.size() < n) {
		(Q.empty() || (30 < dice(100))) ?
			Q.enqueue(dice((T)2 * n)) :		//70%���
			(void)Q.dequeue();				//30%����
		print(Q);
	}
	printf("\n  ==== Test %2d. Shrinking queue\n", testID++);
	while (!Q.empty()) {
		(70 < dice(100)) ?
			Q.enqueue(dice((T)2 * n)) :		//30%���
			(void)Q.dequeue();				//70%����
		print(Q);
	}
}

/******************************************************************************************
* ���Զ���
******************************************************************************************/
int main() {
	string strNumber = "5";
	srand((unsigned int)time(NULL));
	testQueue<int>(atoi(strNumber.c_str())); //Ԫ�����Ϳ�������������ѡ��
	return 0;
}