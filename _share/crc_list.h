/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CRC_LIST_H__
#define CRC_LIST_H__

#include "..\list\list.h"

template <typename T> void crc ( List<T> & L ) { //统计列表的特征（所有元素总和）
   //T crc = 0; L.traverse ( Crc<T> ( crc ) ); //以crc为基本操作进行遍历
	T crc = 0; L.traverse ((Crc<T> &) Crc<T> ( crc ) ); //以crc为基本操作进行遍历
   printf ( "CRC =" ); print ( crc ); printf ( "\n" ); //输出统计得到的特征
}

#endif