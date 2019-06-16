/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
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
 * 针对基于列表、向量以及左式堆实现的优先级队列，做过程统一的测试
 ******************************************************************************************/
template <typename PQ, typename T>				//堆类型、词条类型
void  testHeap ( int n ) {
   T* A = new T[2*n/3];							//创建容量为2*n/3的数组，并
   for ( int i = 0; i < 2 * n / 3; i++ )		//在其中随机生成2*n/3个词条
	   A[i] = dice ( ( T ) 3 * n ); 
   /*DSA*/printf ( "%d random keys created:\n", 2 * n / 3 );

   /*DSA*/for ( int i = 0; i < 2 * n / 3; i++ ) 
	   print ( A[i] ); 
   printf ( "\n" );

   PQ heap ( A + n / 6, n / 3 ); //批量建堆（PQ_ComplHeap实现了Robert Floyd算法）
   delete [] A;

   /*DSA*/system("cls"); 
   print ( heap );  
   Sleep(100);
   while ( heap.size() < n ) { //随机测试
      if ( dice ( 100 ) < 70 ) { //70%概率插入新词条
         T e = dice ( ( T ) 3 * n ); 
		 /*DSA*/printf ( "Inserting" ); 
		 print ( e ); 
		 printf ( " ...\n" );
         heap.insert ( e ); 
		 /*DSA*/printf ( "Insertion done\n" );
      } 
	  else { //30%概率摘除最大词条
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
   while ( !heap.empty() ) { //清空
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
 * 优先级队列测试
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
	int n = 10;
   srand ( ( unsigned int ) time ( NULL ) );

#if defined(DSA_PQ_LEFTHEAP)
   testHeap<PQ_LeftHeap<int>, int> (n); //词条类型可以在这里任意选择

#elif defined(DSA_PQ_COMPLHEAP)
   testHeap<PQ_ComplHeap<int>, int> (n); //词条类型可以在这里任意选择

#elif defined(DSA_PQ_LIST)
   testHeap<PQ_List<int>, int> (n); //词条类型可以在这里任意选择

#else
   printf ( "PQ type not defined yet\n" );

#endif

   return 0;
}
