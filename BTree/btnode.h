/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BTNODE_H__
#define BTNODE_H__

#include "../vector/vector.h"
#define BTNodePosi(T) BTNode<T>*	/* B-���ڵ�λ�� */

/* B-���ڵ�ģ���� */
template <typename T> 
struct BTNode
{
	/* ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ�� */
	BTNodePosi(T) parent;			/* ���ڵ� */
	Vector<T> key;					/* �ؼ������� */
	Vector<BTNodePosi(T)> child;	/* �����������䳤���ܱ�key��һ�� */

	/* ���캯����ע�⣺BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼʱ��0���ؼ����1���պ���ָ�룩 */
	BTNode() 
	{ 
		parent = NULL; 
		child.insert ( 0, NULL ); 
	}

	BTNode ( T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL ) 
	{
		parent = NULL;				/* ��Ϊ���ڵ㣬���ҳ�ʼʱ */
		key.insert ( 0, e );		/* ֻ��һ���ؼ��룬�Լ� */
		child.insert ( 0, lc );		/* �������� */
		child.insert ( 1, rc ); 
		if ( lc ) 
			lc->parent = this; 
		if ( rc ) 
			rc->parent = this;
	}
};

#endif // !BTNODE_H__