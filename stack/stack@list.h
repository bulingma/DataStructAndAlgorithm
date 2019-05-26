/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#pragma once

/* ���б�Ϊ���࣬������ջģ���� */
#include "../list/list.h" 

template <typename T> class Stack : public List<T> {	/* ���б����/ĩ����Ϊջ��/�� */
public: 
	/* size()��empty()�Լ��������Žӿڣ�����ֱ������ */
	void push(T const& e) { this->insertAsLast(e); }	/* ��ջ����Ч�ڽ���Ԫ����Ϊ�б����Ԫ�ز��� */
	T pop() { return this->remove(this->last()); }		/* ��ջ����Ч��ɾ���б����Ԫ�� */
	T& top() { return (this->last())->data; }			/* ȡ����ֱ�ӷ����б����Ԫ�� */
};

//#endif

