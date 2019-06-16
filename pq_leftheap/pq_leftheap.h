/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PQ_LEFTHEAP_H__
#define PQ_LEFTHEAP_H__

#include "../PQ/PQ.h"			//�������ȼ�����ADT
#include "../BinTree/BinTree.h" //����������ڵ�ģ����

template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T> {	//���ڶ�����������ʽ����ʽʵ�ֵ�PQ
   /*DSA*/friend class UniPrint;						//��ʾ���ʹ�ã����򲻱���������
public:
   PQ_LeftHeap() { }									//Ĭ�Ϲ���
   PQ_LeftHeap ( T* E, int n )							//�������죺�ɸĽ�ΪFloyd�����㷨
   {  
	   for ( int i = 0; i < n; i++ ) 
		   insert ( E[i] ); 
   }
   void insert ( T );									//���ձȽ���ȷ�������ȼ��������Ԫ��
   T getMax();											//ȡ�����ȼ���ߵ�Ԫ��
   T delMax();											//ɾ�����ȼ���ߵ�Ԫ��
}; //PQ_LeftHeap

#include "../_share/release.h"
#include "../_share/util.h"

//���ںϲ������Ĵ��������㷨
template <typename T> 
void PQ_LeftHeap<T>::insert(T e)
{ 
	BinNodePosi(T) v = new BinNode<T>(e);				//Ϊe����һ���������ڵ�
	this->_root = merge(this->_root, v);				//ͨ���ϲ�����½ڵ�Ĳ���
	//   _root->parent = NULL;							//��Ȼ��ʱ�ѷǿգ�������Ӧ���ø�������
	this->_size++;										//���¹�ģ
}

//��ȡ�ǿ���ʽ�������ȼ���ߵĴ���
template <typename T> 
T PQ_LeftHeap<T>::getMax()								
{
	return this->_root->data;
}//���մ˴�Լ�����Ѷ������ȼ���ߵĴ���

 //���ںϲ������Ĵ���ɾ���㷨����ǰ���зǿգ�
template <typename T>
T PQ_LeftHeap<T>::delMax()
{ 
	BinNodePosi(T) lHeap = this->_root->lc;				//���Ӷ�
	BinNodePosi(T) rHeap = this->_root->rc;				//���Ӷ�
	T e = this->_root->data;
	delete this->_root;									//ɾ�����ڵ�
	this->_size--;
	this->_root = merge(lHeap, rHeap);					//ԭ�����ӶѺϲ�
	//   if ( _root ) _root->parent = NULL;				//���ѷǿգ�������Ӧ���ø�������
	return e;											//����ԭ���ڵ��������
}

//����������ȼ�ȷ�����˵ķ�ʽ���ϲ���a��bΪ���ڵ��������ʽ��
template <typename T> 
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b) 
{
	if (!a) return b;									//�˻����
	if (!b) return a;									//�˻����
	if (lt(a->data, b->data)) 
		swap(a, b);										//һ�����������ȷ��b����
	a->rc = merge(a->rc, b);							//��a�����Ӷѣ���b�ϲ�
	a->rc->parent = a;									//�����¸��ӹ�ϵ
	if (!a->lc || a->lc->npl < a->rc->npl)				//���б�Ҫ
		swap(a->lc, a->rc);								//����a�������Ӷѣ���ȷ�����Ӷѵ�npl����
	a->npl = a->rc ? a->rc->npl + 1 : 1;				//����a��npl
	return a;											//���غϲ���ĶѶ�
} //���㷨ֻʵ�ֽṹ�ϵĺϲ����ѵĹ�ģ�����ϲ�����߸������


#endif // PQ_LEFTHEAP_H__