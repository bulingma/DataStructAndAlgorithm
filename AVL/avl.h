/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef AVL_H__
#define AVL_H__

#include "../BST/BST.h" /* ����BSTʵ��AVL�� */

/******************************************************************************************
* �����Һ�����ȡ������
* ��AVLƽ�����ǰ�����ȷ���ع�����
******************************************************************************************/
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*���*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*�Ҹ�*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
   ) \
   ) \
)

/* ��BST����AVL��ģ���� */
template <typename T> 
class AVL : public BST<T> { 
public:
   BinNodePosi(T) insert ( const T& e );	/* ���루��д�� */
   bool remove ( const T& e );				/* ɾ������д�� */
/* BST::search()������ӿڿ�ֱ������ */
};

/* ���ؼ���e����AVL���� */
template <typename T> 
BinNodePosi(T) AVL<T>::insert(const T& e) { 
	BinNodePosi(T) & x = this->search(e); 
	if (x)											/* ȷ��Ŀ��ڵ㲻���� */
		return x; 
	BinNodePosi(T) xx = x = new BinNode<T>(e, this->_hot); /* �����½ڵ�x */
	this->_size++;
													/* ��ʱ��x�ĸ���_hot�����ߣ������游�п���ʧ�� */
	for (BinNodePosi(T) g = this->_hot; g; g = g->parent) /* ��x֮���������ϣ�������������g */
	{ 
		if (!AvlBalanced(*g)) {						/* һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬�������� */
			FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g))); /* ���½���ԭ�� */
			break;									/* g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴���� */
		}
		else										/* ����g��Ȼƽ�⣩��ֻ��򵥵� */
			this->updateHeight(g);						/* ������߶ȣ�ע�⣺����gδʧ�⣬�߶���������ӣ� */
	}												/* ����ֻ��һ�ε�����������������������ȫ���߶ȱ�Ȼ��ԭ */
	return xx;										/* �����½ڵ�λ�� */
}													/* ����e�Ƿ������ԭ���У�����AVL::insert(e)->data == e */

/* ��AVL����ɾ���ؼ���e */
template <typename T> 
bool AVL<T>::remove(const T& e) { 
	BinNodePosi(T) & x = this->search(e);
	if (!x) return false;							/* ȷ��Ŀ����ڣ�����_hot�����ã� */
	removeAt(x, this->_hot);						/* �Ȱ�BST����ɾ��֮���˺�ԭ�ڵ�֮��_hot�������Ⱦ�����ʧ�⣩ */
	this->_size--;
	for (BinNodePosi(T) g = this->_hot; g; g = g->parent) /* ��_hot�������ϣ�������������g */
	{ 
		if (!AvlBalanced(*g))						/* һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬�������������� */
			g = FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g))); /* ԭ���� */
		this->updateHeight(g);							/* ��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ� */
	}												/* ��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ��� */
	return true;									/* ɾ���ɹ� */
}													/* ��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false */

#endif // !AVL_H__