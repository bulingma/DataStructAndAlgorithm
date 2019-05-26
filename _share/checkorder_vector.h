/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CHECKORDER_VECTOR_H__
#define CHECKORDER_VECTOR_H__

#include "..\vector\vector.h"

template <typename T> void checkOrder ( Vector<T> & V ) { //�ж������Ƿ���������
   int unsorted = 0; //���������
   V.traverse ((CheckOrder<T> &)CheckOrder<T> ( unsorted, V[0] ) ); //���б���
   if ( 0 < unsorted )
      printf ( "Unsorted with %d adjacent disordered pair(s)\n", unsorted );
   else
      printf ( "Sorted\n" );
}

//template <typename T> void checkOrder(Vector<T> & V) {
//   if (0 < V.disordered())
//      printf("Unsorted with %d adjacent disordered pair(s)\n", V.disordered());
//   else
//      printf("Sorted\n");
//}

#endif // !CHECKORDER_VECTOR_H__