/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CEHCKORDER_LIST_H__
#define CEHCKORDER_LIST_H__

#include "..\list\list.h"

template <typename T> void checkOrder ( List<T> & L ) { //�ж��б��Ƿ���������
   int unsorted = 0; //���������
   L.traverse ( (CheckOrder<T> &) CheckOrder<T> ( unsorted, L.first()->data ) ); //���б���
   if ( 0 < unsorted )
      printf ( "Unsorted with %d adjacent disordered pair(s)\n", unsorted );
   else
      printf ( "Sorted\n" );
   printf ( "DISORDERED = %d\n", L.disordered() );
}

#endif