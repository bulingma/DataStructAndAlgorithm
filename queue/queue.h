/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef _QUEUE_H__
#define _QUEUE_H__

/* ��ListΪ���� */
#include "../list/list.h"		

/* ����ģ���ࣨ�̳�Listԭ�нӿڣ� */
template <typename T> class Queue : public List<T> {	
public: 
	/* size()��empty()�Լ��������Žӿھ���ֱ������ */
	void enqueue(T const& e) { (this->insertAsLast(e)); }	/* ��ӣ�β������ */
	T dequeue() { return (this->remove( this->first() )); }	/* ���ӣ��ײ�ɾ�� */
	T& front() { return (this->first())->data; }			/* ���� */
};

#endif