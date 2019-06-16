/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PQ_LIST_H__
#define PQ_LIST_H__

#include "../PQ/PQ.h"		//引入优先级队列ADT
#include "../List/List.h"	//引入列表

//基于列表实现的优先级队列
template <typename T> 
class PQ_List : public PQ<T>, public List<T> 
{ 
	/*DSA*/friend class UniPrint;			//演示输出使用，否则不必设置友类
public:
	PQ_List() { }							//默认构造
	PQ_List(T* E, int n)					//批量构造
	{ 
		while (0 < n--) 
			this->insertAsFirst((E[n]));
	}
	void insert(T e) 
	{ 
		this->insertAsLast(e);				//直接将新元素插至队列末尾
	}
	T getMax()								//取出优先级最高的元素
	{ 
		return this->selectMax()->data; 
	}
	T delMax()								//删除优先级最高的元素
	{ 
		return this->remove(this->selectMax());
	} 
}; //PQ_List

#endif
