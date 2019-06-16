/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PQ_H__
#define PQ_H__

//优先级队列PQ模板类
template <typename T> struct PQ 
{ 
   virtual void insert ( T ) = 0;	//按照比较器确定的优先级次序插入词条
   virtual T getMax() = 0;			//取出优先级最高的词条
   virtual T delMax() = 0;			//删除优先级最高的词条
};

#endif // PQ_H__