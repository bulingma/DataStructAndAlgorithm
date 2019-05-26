/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef INCREASE_ELEM_H__
#define INCREASE_ELEM_H__

template <typename T> struct Increase //�������󣺵���һ��T�����
   {  virtual void operator() ( T& e ) { e++; }  }; //����T��ֱ�ӵ�����������++

#endif