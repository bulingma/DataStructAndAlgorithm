/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BTNODE_H__
#define BTNODE_H__

#include "../vector/vector.h"
#define BTNodePosi(T) BTNode<T>*	/* B-树节点位置 */

/* B-树节点模板类 */
template <typename T> 
struct BTNode
{
	/* 成员（为简化描述起见统一开放，读者可根据需要进一步封装） */
	BTNodePosi(T) parent;			/* 父节点 */
	Vector<T> key;					/* 关键码向量 */
	Vector<BTNodePosi(T)> child;	/* 孩子向量（其长度总比key多一） */

	/* 构造函数（注意：BTNode只能作为根节点创建，而且初始时有0个关键码和1个空孩子指针） */
	BTNode() 
	{ 
		parent = NULL; 
		child.insert ( 0, NULL ); 
	}

	BTNode ( T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL ) 
	{
		parent = NULL;				/* 作为根节点，而且初始时 */
		key.insert ( 0, e );		/* 只有一个关键码，以及 */
		child.insert ( 0, lc );		/* 两个孩子 */
		child.insert ( 1, rc ); 
		if ( lc ) 
			lc->parent = this; 
		if ( rc ) 
			rc->parent = this;
	}
};

#endif // !BTNODE_H__