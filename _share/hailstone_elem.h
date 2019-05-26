/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef HAILSTONE_ELEM_H__
#define HAILSTONE_ELEM_H__

/* 3n+1问题（Hailstone问题）*/
template <typename T> struct Hailstone { //函数对象：按照Hailstone规则转化一个T类对象
   virtual void operator() ( T& e ) { //假设T可直接做算术运算
      int step = 0; //转换所需步数
      while ( 1 != e ) { //按奇、偶逐步转换，直至为1
         ( e % 2 ) ? e = 3 * e + 1 : e /= 2;
         step++;
      }
      e = step; //返回转换所经步数
   }
};

#endif