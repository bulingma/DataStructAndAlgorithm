/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef DOUBLE_ELEM_H__
#define DOUBLE_ELEM_H__

template <typename T> struct Double //�������󣺱���һ��T�����
   {  virtual void operator() ( T& e ) { e *= 2; }  }; //����T��ֱ�ӱ���

#endif