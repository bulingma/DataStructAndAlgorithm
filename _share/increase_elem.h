/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef INCREASE_ELEM_H__
#define INCREASE_ELEM_H__

template <typename T> struct Increase //函数对象：递增一个T类对象
   {  virtual void operator() ( T& e ) { e++; }  }; //假设T可直接递增或已重载++

#endif