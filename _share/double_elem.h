/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef DOUBLE_ELEM_H__
#define DOUBLE_ELEM_H__

template <typename T> struct Double //函数对象：倍增一个T类对象
   {  virtual void operator() ( T& e ) { e *= 2; }  }; //假设T可直接倍增

#endif