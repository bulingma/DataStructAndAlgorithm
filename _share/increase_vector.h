/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef INCREASE_VECTOR_H__
#define INCREASE_VECTOR_H__

/*DSA*/#include "..\vector\vector.h"

template <typename T> void increase ( Vector<T> & V ) //统一递增向量中的各元素
{  V.traverse ((Increase<T> &) Increase<T>() );  } //以Increase<T>()为基本操作进行遍历

#endif // !INCREASE_VECTOR_H__