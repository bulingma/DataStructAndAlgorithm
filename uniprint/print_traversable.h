/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_TRAVERSABLE_H__
#define PRINT_TRAVERSABLE_H__

/******************************************************************************************
 * �������б��֧��traverse()�������������Խṹ
 ******************************************************************************************/
template <typename T> //Ԫ������
void UniPrint::p ( T& s ) { //����
   printf ( "%s[%d]*%d:\n", typeid ( s ).name(), &s, s.size() ); //������Ϣ
   s.traverse ( print ); //ͨ��print()�����������Ԫ��
   printf ( "\n" );
}

#endif // !PRINT_TRAVERSABLE_H__