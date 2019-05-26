/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CRC_VECTOR_H__
#define CRC_VECTOR_H__

#include "..\vector\vector.h"

template <typename T> void crc ( Vector<T> & V ) { //统计向量的特征（所有元素之和）
   //T crc = 0; V.traverse ( Crc<T> ( crc ) ); //以crc为基本操作进行遍历
   T crc = 0; V.traverse((Crc<T> &) Crc<T>(crc)); //以crc为基本操作进行遍历
   printf ( "CRC =" ); print ( crc ); printf ( "\n" ); //输出统计得到的特征
}

#endif // !CRC_VECTOR_H__