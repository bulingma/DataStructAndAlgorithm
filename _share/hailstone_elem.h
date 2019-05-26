/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef HAILSTONE_ELEM_H__
#define HAILSTONE_ELEM_H__

/* 3n+1���⣨Hailstone���⣩*/
template <typename T> struct Hailstone { //�������󣺰���Hailstone����ת��һ��T�����
   virtual void operator() ( T& e ) { //����T��ֱ������������
      int step = 0; //ת�����貽��
      while ( 1 != e ) { //���桢ż��ת����ֱ��Ϊ1
         ( e % 2 ) ? e = 3 * e + 1 : e /= 2;
         step++;
      }
      e = step; //����ת����������
   }
};

#endif