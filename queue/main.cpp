/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
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

int testID = 0; //测试编号

/******************************************************************************************
* 测试栈
******************************************************************************************/
template <typename T>						//元素类型
void testQueue(int n) {
	Queue<T> Q;
	printf("\n  ==== Test %2d. Growing queue\n", testID++);
	while (Q.size() < n) {
		(Q.empty() || (30 < dice(100))) ?
			Q.enqueue(dice((T)2 * n)) :		//70%入队
			(void)Q.dequeue();				//30%出队
		print(Q);
	}
	printf("\n  ==== Test %2d. Shrinking queue\n", testID++);
	while (!Q.empty()) {
		(70 < dice(100)) ?
			Q.enqueue(dice((T)2 * n)) :		//30%入队
			(void)Q.dequeue();				//70%出队
		print(Q);
	}
}

/******************************************************************************************
* 测试队列
******************************************************************************************/
int main() {
	string strNumber = "5";
	srand((unsigned int)time(NULL));
	testQueue<int>(atoi(strNumber.c_str())); //元素类型可以在这里任意选择
	return 0;
}