/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_TRAVERSABLE_H__
#define PRINT_TRAVERSABLE_H__

/******************************************************************************************
 * 向量、列表等支持traverse()遍历操作的线性结构
 ******************************************************************************************/
template <typename T> //元素类型
void UniPrint::p ( T& s ) { //引用
   printf ( "%s[%d]*%d:\n", typeid ( s ).name(), &s, s.size() ); //基本信息
   s.traverse ( print ); //通过print()遍历输出所有元素
   printf ( "\n" );
}

#endif // !PRINT_TRAVERSABLE_H__