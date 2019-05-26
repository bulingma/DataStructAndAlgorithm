/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#include<iostream>
using namespace std;
#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "stack@list.h"

int testID = 0; //测试编号

/******************************************************************************************
* 测试栈
******************************************************************************************/
template <typename T>	//元素类型
void testStack(int n) {
	Stack<T> S;
	printf("\n  ==== Test %2d. Growing stack\n", testID++);
	while (S.size() < n) {
		T e = rand() % (T)2 * n;
		if (S.empty() || (30 < (rand() % 100))) {//70%概率入栈
			printf("pushing "); 
			print(e); 
			printf(" ...\n");
			S.push(e);
		}
		else {									 //30%概率出栈
			printf("poping with ... "); 
			print(S.pop()); 
			printf("\n");
		}
		print(S);
	}
	
	printf("\n  ==== Test %2d. Shrinking stack\n", testID++);

	while (!S.empty()) {
		T e = dice((T)2 * n);
		if (70 < dice(100)) {					//30%概率入栈
			printf("pushing "); 
			print(e); 
			printf(" ...\n");
			S.push(e);
		}
		else {									//70%概率出栈
			printf("poping with ... "); 
			print(S.pop()); 
			printf("\n");
		}
		print(S);
	}
}


/******************************************************************************************
* 测试栈
******************************************************************************************/
int main(int argc, char* argv[]) {
	string strNumber = "5";
	srand((unsigned int)time(NULL));
	testStack<int>(atoi(strNumber.c_str())); //元素类型可以在这里任意选择
	return 0;
} 