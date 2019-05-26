/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

/******************************************************************************************
* Test of Hashtable
******************************************************************************************/
#include<iostream>
using namespace std;
#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "Hashtable.h"

/******************************************************************************************
* ����ɢ�б�
******************************************************************************************/
template <typename K, typename V> //key��value
void testHashtable(int n) {
	Hashtable<K, V> ht(n); 
	print(ht);
	while (ht.size() < 4 * n) {
		printf("\n");
		switch (dice(3)) {
			case 0: { //���ң��ɹ��� <= 33.3%
				K key = dice((K)n * 12); //[0, 3n)��Χ�ڵ�key
				printf("Searching ");
				print(key); 
				printf("(%04d) :\n", hashCode(key));
				V* pValue = ht.get(key);
				pValue ? printf("Found with "), print(*pValue) : (void)printf("Not found"); 
				printf("\n");
				break;
			}
			case 1: { //ɾ�����ɹ��� <= 33.3%
				K key = dice((K)n * 12); //[0, 3n)��Χ�ڵ�key
				printf("Removing "); 
				print(key); 
				printf("(%04d) :\n", hashCode(key));
				ht.remove(key) ? printf("Done\n"), print(ht) : (void)printf("Entry not exists\n");
				break;
			}
			default: {//���룬�ɹ��� == 100%
				K key = dice((K)n * 12); 
				V v = (V) 'A' + dice(26); //��[0, 2n)*['A'~'Z']��Χ�ڵĴ���
				printf("Inserting <"); 
				print(key); 
				printf("(%04d)", hashCode(key));
				printf(","); 
				print(v);
				printf(">\n");
				ht.put(key, v) ? printf("Done\n"), print(ht) : (void)printf("Dup key\n");
				break;
			}
		} //switch
	} //while
	while (ht.size() > 0) {
		printf("\n");
		K key = dice((K)n * 12); //[0, 3n)��Χ�ڵ�key
		printf("Removing "); 
		print(key); 
		printf(" :\n");
		ht.remove(key) ? printf("Done\n"), print(ht) : (void)printf("Entry not exists\n");
	}
}

/******************************************************************************************
* ������
******************************************************************************************/
int main(int argc, char* argv[]) {
	int iNumber = 6;
	srand((unsigned int)time(NULL));
	testHashtable<int, char>(iNumber); //Ԫ�����Ϳ�������������ѡ��
	return 0;
}
