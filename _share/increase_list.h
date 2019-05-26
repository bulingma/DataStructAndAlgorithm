/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef ICREASE_LIST_H__
#define ICREASE_LIST_H__

/*DSA*/#include "..\list\list.h"

template <typename T> void increase ( List<T> & L ) //ͳһ�����б��еĸ�Ԫ��
{  L.traverse ( (Increase<T> &) Increase<T>() );  } //��Increase<T>()Ϊ�����������б���

#endif // !ICREASE_LIST_H__