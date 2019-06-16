/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

/******************************************************************************************
 * Test of PQ_ComplHeap & PQ_LeftHeap
 ******************************************************************************************/
//#define DSA_PQ_COMPLHEAP
//#define DSA_PQ_LEFTHEAP
#define DSA_PQ_LIST

#include<iostream>
using namespace std;
#include "../_share/util.h"
#include "../UniPrint/print.h"

#if defined(DSA_PQ_LEFTHEAP)
#include "../PQ_LeftHeap/PQ_LeftHeap.h"
#elif defined(DSA_PQ_COMPLHEAP)
#include "../PQ_ComplHeap/PQ_ComplHeap.h"
#elif defined(DSA_PQ_LIST)
#include "../PQ_List/PQ_List.h"
#endif

#include <windows.h>

/******************************************************************************************
 * ��Ի����б������Լ���ʽ��ʵ�ֵ����ȼ����У�������ͳһ�Ĳ���
 ******************************************************************************************/
template <typename PQ, typename T>				//�����͡���������
void  testHeap ( int n ) {
   T* A = new T[2*n/3];							//��������Ϊ2*n/3�����飬��
   for ( int i = 0; i < 2 * n / 3; i++ )		//�������������2*n/3������
	   A[i] = dice ( ( T ) 3 * n ); 
   /*DSA*/printf ( "%d random keys created:\n", 2 * n / 3 );

   /*DSA*/for ( int i = 0; i < 2 * n / 3; i++ ) 
	   print ( A[i] ); 
   printf ( "\n" );

   PQ heap ( A + n / 6, n / 3 ); //�������ѣ�PQ_ComplHeapʵ����Robert Floyd�㷨��
   delete [] A;

   /*DSA*/system("cls"); 
   print ( heap );  
   Sleep(100);
   while ( heap.size() < n ) { //�������
      if ( dice ( 100 ) < 70 ) { //70%���ʲ����´���
         T e = dice ( ( T ) 3 * n ); 
		 /*DSA*/printf ( "Inserting" ); 
		 print ( e ); 
		 printf ( " ...\n" );
         heap.insert ( e ); 
		 /*DSA*/printf ( "Insertion done\n" );
      } 
	  else { //30%����ժ��������
         if ( !heap.empty() ) {
            /*DSA*/printf ( "Deleting max ...\n" );
            T e = heap.delMax();
			/*DSA*/printf ( "Deletion done with" ); 
			print ( e ); 
			printf ( "\n" );
         }
      }
      /*DSA*/system("cls"); 
	  print ( heap ); 
	  Sleep(100);
   }
   while ( !heap.empty() ) { //���
      T e = heap.delMax();
	  /*DSA*/printf ( "Deletion done with" ); 
	  print ( e ); 
	  printf ( "\n" );

      /*DSA*/system("cls"); 
	  print ( heap ); 
	  Sleep(100);
   }
}

/******************************************************************************************
 * ���ȼ����в���
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
	int n = 10;
   srand ( ( unsigned int ) time ( NULL ) );

#if defined(DSA_PQ_LEFTHEAP)
   testHeap<PQ_LeftHeap<int>, int> (n); //�������Ϳ�������������ѡ��

#elif defined(DSA_PQ_COMPLHEAP)
   testHeap<PQ_ComplHeap<int>, int> (n); //�������Ϳ�������������ѡ��

#elif defined(DSA_PQ_LIST)
   testHeap<PQ_List<int>, int> (n); //�������Ϳ�������������ѡ��

#else
   printf ( "PQ type not defined yet\n" );

#endif

   return 0;
}
