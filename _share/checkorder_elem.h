/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CHECKORDER_ELEM_H__
#define CHECKORDER_ELEM_H__

template <typename T> struct CheckOrder { //���������ж�һ��T������Ƿ�ֲ�����
   T pred; int& u;
   CheckOrder ( int& unsorted, T& first ) : pred ( first ), u ( unsorted ) { }
   virtual void operator() ( T& e ) { if ( pred > e ) u++; pred = e; }
};

#endif // !CHECKORDER_ELEM_H__