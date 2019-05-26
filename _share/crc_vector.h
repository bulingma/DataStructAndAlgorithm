/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CRC_VECTOR_H__
#define CRC_VECTOR_H__

#include "..\vector\vector.h"

template <typename T> void crc ( Vector<T> & V ) { //ͳ������������������Ԫ��֮�ͣ�
   //T crc = 0; V.traverse ( Crc<T> ( crc ) ); //��crcΪ�����������б���
   T crc = 0; V.traverse((Crc<T> &) Crc<T>(crc)); //��crcΪ�����������б���
   printf ( "CRC =" ); print ( crc ); printf ( "\n" ); //���ͳ�Ƶõ�������
}

#endif // !CRC_VECTOR_H__