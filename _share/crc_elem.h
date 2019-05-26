/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CRC_ELEM_H__
#define CRC_ELEM_H__

template <typename T> struct Crc { //函数对象：累计T类对象的特征（比如总和），以便校验对象集合
   T& c;
   Crc ( T& crc ) : c ( crc ) {}
   virtual void operator() ( T& e ) { c += e; } //假设T可直接相加
};

#endif 