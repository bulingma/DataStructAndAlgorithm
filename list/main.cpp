/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

/******************************************************************************************
* Test of list
******************************************************************************************/
#include<iostream>
using namespace std;
#include "list.h"
#include "../UniPrint/print.h"

int testID = 0; //���Ա��

/******************************************************************************************
* ������ɳ���Ϊn���б����п��ܰ����ظ��ڵ㣩
******************************************************************************************/
template <typename T> //Ԫ������
void randomList(List<T> & list, int n) { //��[0, 2n)��ѡ��n��ż������������б�
	ListNodePosi(T) p =
		(rand() % 2) ?
		list.insertAsLast(rand() % (T)n * 2) :
		list.insertAsFirst(rand() % (T)n * 2);
	for (int i = 1; i < n; i++)
		p = rand() % 2 ?
		list.insertB(p, rand() % (T)n * 2) :
		list.insertA(p, rand() % (T)n * 2);
}

/******************************************************************************************
* �����б�
******************************************************************************************/
#define PRINT(x)  { print(x); crc(x); checkOrder(x); }
template <typename T> //Ԫ������
void   testList(int testSize) {
	printf("\n  ==== Test %2d. Generate two lists each of size %d by random insertions\n", testID++, testSize);
	List<T> La; randomList(La, testSize); 
	PRINT(La);
	List<T> Lb; randomList(Lb, testSize); 
	PRINT(Lb);

	printf("\n  ==== Test %2d. Call list members by rank (with high complexity)\n", testID++);
	for (int i = 0; i < La.size(); i++) print(La[i]); 
	printf("\n");
	for (int i = 0; i < Lb.size(); i++) print(Lb[i]);
	printf("\n");

	printf("\n  ==== Test %2d. Concatenation\n", testID++); 
	PRINT(La); 
	PRINT(Lb);
	while (0 < Lb.size()) La.insertAsLast(Lb.remove(Lb.first()));
	PRINT(La); 
	PRINT(Lb);

	printf("\n  ==== Test %2d. Increase\n", testID++); 
	PRINT(La);
	increase(La); 
	PRINT(La);

	printf("\n  ==== Test %2d. Lowpass (with high complexity) on\n", testID++); 
	PRINT(La);
	int i = La.size(); 
	while (0 < --i) { 
		La[i - 1] += La[i]; 
		La[i - 1] >>= 1; 
	} 
	PRINT(La);

	printf("\n  ==== Test %2d. reverse\n", testID++, testSize);
	La.reverse();
	PRINT(La);

	printf("\n  ==== Test %2d. Copy\n", testID++); 
	PRINT(La);
	List<T> Ld(La); 
	PRINT(Ld);

	printf("\n  ==== Test %2d. Trim by random deletions\n", testID++); 
	PRINT(Ld);
	while (testSize / 4 < Ld.size()) {
		int N = rand() % Ld.size(); 
		printf("removing L[%d]=", N);
		ListNodePosi(T) p = Ld.first(); 
		while (0 < N--) p = p->succ;
		print(p->data); 
		printf(" ...\n");
		Ld.remove(p); 
		PRINT(Ld);
	}

	printf("\n  ==== Test %2d. Copy\n", testID++); 
	PRINT(La);
	List<T> Le(La); 
	PRINT(Le);

	printf("\n  ==== Test %2d. FIND in\n", testID++); 
	PRINT(Le);
	for (int i = 0; i <= testSize * 2; i++) { //��һ����[0, 2n]�е����п���
		ListNodePosi(T) p = Le.find((T)i); 
		printf("Looking for "); 
		print((T)i); 
		printf(": ");
		if (p) { 
			printf(" found with"); 
			print(p->data); 
		}
		else printf(" not found");
		printf("\n");
	} //��ȷ�ĽṹӦ���Ǵ��£�n+1�Σ�ʧ�ܡ���n�Σ��ɹ����

	printf("\n  ==== Test %2d. Sort\n", testID++); 
	PRINT(La);
	La.sort(); 
	PRINT(La);

	printf("\n  ==== Test %2d. SEARCH in\n", testID++); 
	PRINT(La);
	for (int i = 0; i <= testSize * 2; i++) { //��һ����[0, 2n]�е����п���
		ListNodePosi(T) p = La.search((T)i); 
		printf("Looking for "); 
		print((T)i); 
		printf(": ");
		printf(" stopped at"); 
		print(p->data);
		if ((T)i == p->data) 
			printf(" and found");
		printf("\n");
	} //��ȷ�ĽṹӦ���Ǵ��£�n+1�Σ�ʧ�ܡ���n�Σ��ɹ����

	printf("\n  ==== Test %2d. Remove redundancy in\n", testID++); 
	PRINT(La);

	printf("%d node(s) removed\n", La.uniquify()); 
	PRINT(La); 
	La.reverse(); 
	PRINT(La);

	printf("\n  ==== Test %2d. Remove redundancy in\n", testID++); 
	PRINT(Le);

	printf("%d node(s) removed\n", Le.deduplicate()); 
	PRINT(Le);

	printf("\n  ==== Test %2d. Sort\n", testID++); 
	PRINT(Le);

	Le.sort(); 
	PRINT(Le);

	return;
}

/******************************************************************************************
* �����б�
******************************************************************************************/
int main() 
{
	string strNumber = "5";
	srand((unsigned int)time(NULL));
	testList<int>(atoi(strNumber.c_str())); //Ԫ�����Ϳ�������������ѡ��
	return 0;
}