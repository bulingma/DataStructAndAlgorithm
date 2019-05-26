/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CRC_LIST_H__
#define CRC_LIST_H__

#include "..\list\list.h"

template <typename T> void crc ( List<T> & L ) { //ͳ���б������������Ԫ���ܺͣ�
   //T crc = 0; L.traverse ( Crc<T> ( crc ) ); //��crcΪ�����������б���
	T crc = 0; L.traverse ((Crc<T> &) Crc<T> ( crc ) ); //��crcΪ�����������б���
   printf ( "CRC =" ); print ( crc ); printf ( "\n" ); //���ͳ�Ƶõ�������
}

#endif