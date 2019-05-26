/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef ICREASE_LIST_H__
#define ICREASE_LIST_H__

/*DSA*/#include "..\list\list.h"

template <typename T> void increase ( List<T> & L ) //统一递增列表中的各元素
{  L.traverse ( (Increase<T> &) Increase<T>() );  } //以Increase<T>()为基本操作进行遍历

#endif // !ICREASE_LIST_H__