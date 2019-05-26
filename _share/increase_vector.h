/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef INCREASE_VECTOR_H__
#define INCREASE_VECTOR_H__

/*DSA*/#include "..\vector\vector.h"

template <typename T> void increase ( Vector<T> & V ) //ͳһ���������еĸ�Ԫ��
{  V.traverse ((Increase<T> &) Increase<T>() );  } //��Increase<T>()Ϊ�����������б���

#endif // !INCREASE_VECTOR_H__