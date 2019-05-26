/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef CRC_ELEM_H__
#define CRC_ELEM_H__

template <typename T> struct Crc { //���������ۼ�T�����������������ܺͣ����Ա�У����󼯺�
   T& c;
   Crc ( T& crc ) : c ( crc ) {}
   virtual void operator() ( T& e ) { c += e; } //����T��ֱ�����
};

#endif 