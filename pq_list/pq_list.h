/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PQ_LIST_H__
#define PQ_LIST_H__

#include "../PQ/PQ.h"		//�������ȼ�����ADT
#include "../List/List.h"	//�����б�

//�����б�ʵ�ֵ����ȼ�����
template <typename T> 
class PQ_List : public PQ<T>, public List<T> 
{ 
	/*DSA*/friend class UniPrint;			//��ʾ���ʹ�ã����򲻱���������
public:
	PQ_List() { }							//Ĭ�Ϲ���
	PQ_List(T* E, int n)					//��������
	{ 
		while (0 < n--) 
			this->insertAsFirst((E[n]));
	}
	void insert(T e) 
	{ 
		this->insertAsLast(e);				//ֱ�ӽ���Ԫ�ز�������ĩβ
	}
	T getMax()								//ȡ�����ȼ���ߵ�Ԫ��
	{ 
		return this->selectMax()->data; 
	}
	T delMax()								//ɾ�����ȼ���ߵ�Ԫ��
	{ 
		return this->remove(this->selectMax());
	} 
}; //PQ_List

#endif
