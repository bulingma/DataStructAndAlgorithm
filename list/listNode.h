/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef LISTNODE_H__
#define LISTNODE_H__

typedef int Rank;										/* �� */
#define ListNodePosi(T) ListNode<T>*					/* �б�ڵ�λ�� */

template <typename T> struct ListNode {					/* �б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣� */
														/* ��Ա */
	T data;												/* ��ֵ */
	ListNodePosi(T) pred;								/* ǰ�� */
	ListNodePosi(T) succ;								/* ��� */
														
	ListNode() {}										/* ���캯�� */														
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
		: data(e), pred(p), succ(s) { } 
														/* Ĭ�Ϲ����� */									   
	ListNodePosi(T) insertAsPred(T const& e);			/* ������ǰ�ڵ�֮ǰ�����½ڵ� */
	ListNodePosi(T) insertAsSucc(T const& e);			/* ���浱ǰ�ڵ�֮������½ڵ� */
};

/* ��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б������ڱ�ͷ�ڵ�header�� */
template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) 
{
	ListNodePosi(T) x = new ListNode(e, pred, this);	/* �����½ڵ� */
	pred->succ = x;										/* ������������ */
	pred = x;
	return x;											/* �����½ڵ��λ�� */
}

/* ��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б������ڱ�β�ڵ�trailer�� */
template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);	/* �����½ڵ� */
	succ->pred = x;										/* ������������ */
	succ = x;
	return x;											/* �����½ڵ��λ�� */
}

#endif