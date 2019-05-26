/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BST_H__
#define BST_H__

#include "../BinTree/BinTree.h"						/* ����BinTree */
#define EQUAL(e, v)  (!(v) || (e) == (v)->data)		/* �ڵ�v��������ͨ���ڱ����Ĺؼ������e */

template <typename T> 
class BST : public BinTree<T> {						/* ��BinTree����BSTģ���� */
protected:
   BinNodePosi(T) _hot;								/* �����С��ڵ�ĸ��� */
   BinNodePosi(T) connect34 (						/* ���ա�3 + 4���ṹ������3���ڵ㼰�Ŀ����� */
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) );
   BinNodePosi(T) rotateAt ( BinNodePosi(T) x );	/* ��x���丸�ס��游��ͳһ��ת���� */

public:												/* �����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д */
   virtual BinNodePosi(T) & search ( const T& e );	/* ���� */
   virtual BinNodePosi(T) insert ( const T& e );	/* ���� */
   virtual bool remove ( const T& e );				/* ɾ�� */
};

/* ����vΪ���ģ�AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ���e */
template <typename T> 
static BinNodePosi(T) & searchIn(BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot) 
{
	if (EQUAL(e, v)) 
		return v;
	hot = v;										/* �˻���������������ڵ�v������ */
	while (1) {										/* һ��أ��������ϵ� */
		BinNodePosi(T) & c = (e < hot->data) ? hot->lc : hot->rc; /* ȷ�����뷽�� */
		if (EQUAL(e, c))							/* ���з��أ���������һ�� */
			return c; 
		hot = c; 
	}												/* hotʼ��ָ�����һ��ʧ�ܽڵ� */
}													/* ����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL�� */

/* ��BST�в��ҹؼ���e */
template <typename T> 
BinNodePosi(T) & BST<T>::search(const T& e)			
{
	return searchIn(this->_root, e, _hot = NULL);	/* ����Ŀ��ڵ�λ�õ����ã��Ա�������롢ɾ������ */
} 

/* ���ؼ���e����BST���� */
template <typename T> 
BinNodePosi(T) BST<T>::insert(const T& e) 
{ 
	BinNodePosi(T) & x = search(e); 
	if (x) 
		return x;									/* ȷ��Ŀ�겻���ڣ������_hot�����ã� */
	x = new BinNode<T>(e, _hot);					/* �����½ڵ�x����eΪ�ؼ��룬��_hotΪ�� */
	this->_size++;									/* ����ȫ����ģ */
	this->updateHeightAbove(x);						/* ����x�����������ȵĸ߶� */
	return x;										/* �²���Ľڵ㣬��ΪҶ�� */
}													/* ����e�Ƿ������ԭ���У�����ʱ����x->data == e */

/******************************************************************************************
* BST�ڵ�ɾ���㷨��ɾ��λ��x��ָ�Ľڵ㣨ȫ�־�̬ģ�庯����������AVL��Splay��RedBlack�ȸ���BST��
* Ŀ��x�ڴ�ǰ�����Ҷ�λ����ȷ�Ϸ�NULL���ʱ�ɾ���ɹ�����searchIn��ͬ������֮ǰ���ؽ�hot�ÿ�
* ����ֵָ��ʵ�ʱ�ɾ���ڵ�Ľ����ߣ�hotָ��ʵ�ʱ�ɾ���ڵ�ĸ��ס������߾��п�����NULL
******************************************************************************************/
template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T) & x, BinNodePosi(T) & hot) 
{
	BinNodePosi(T) w = x;							/* ʵ�ʱ�ժ���Ľڵ㣬��ֵͬx */
	BinNodePosi(T) succ = NULL;						/* ʵ�ʱ�ɾ���ڵ�Ľ����� */
	if (!HasLChild(*x))								/* ��*x��������Ϊ�գ���� */
		succ = x = x->rc;							/* ֱ�ӽ�*x�滻Ϊ�������� */
	else if (!HasRChild(*x))						/* ��������Ϊ�գ���� */
		succ = x = x->lc;							/* �ԳƵش�����ע�⣺��ʱsucc != NULL */
	else {											/* ���������������ڣ���ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���ڵ㣬Ϊ����Ҫ */
		w = w->succ();								/* �����������У��ҵ�*x��ֱ�Ӻ��*w */
		swap(x->data, w->data);						/* ����*x��*w������Ԫ�� */
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc;	/* ����ڵ�*w */
	}
	hot = w->parent;								/* ��¼ʵ�ʱ�ɾ���ڵ�ĸ��� */
	if (succ) 
		succ->parent = hot;							/* ������ɾ���ڵ�Ľ�������hot���� */
	release(w->data);
	release(w); 
	return succ;									/* �ͷű�ժ���ڵ㣬���ؽ����� */
}

/* ��BST����ɾ���ؼ���e */
template <typename T> 
bool BST<T>::remove(const T& e) 
{ 
	BinNodePosi(T) & x = search(e); 
	if (!x) 
		return false;								/* ȷ��Ŀ����ڣ�����_hot�����ã� */
	removeAt(x, _hot);								/* ʵʩɾ�� */
	this->_size--; 
	this->updateHeightAbove(_hot);					/* ����_hot�����������ȵĸ߶� */
	return true;
}													/* ɾ���ɹ�����ɷ���ֵָʾ */

/******************************************************************************************
* ���ա�3 + 4���ṹ����3���ڵ㼰���Ŀ���������������֮��ľֲ��������ڵ�λ�ã���b��
* �������ڵ����ϲ�ڵ�֮���˫�����ӣ��������ϲ���������
* ������AVL��RedBlack�ľֲ�ƽ�����
******************************************************************************************/
template <typename T>
BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	/* *DSA*/print(a); print(b); print(c); printf("\n");
	a->lc = T0; if (T0) T0->parent = a;
	a->rc = T1; if (T1) T1->parent = a; this->updateHeight(a);
	c->lc = T2; if (T2) T2->parent = c;
	c->rc = T3; if (T3) T3->parent = c; this->updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; this->updateHeight(b);
	return b;										/* �������µĸ��ڵ� */
}

/******************************************************************************************
* BST�ڵ���ת�任ͳһ�㷨��3�ڵ� + 4�����������ص���֮��ֲ��������ڵ��λ��
* ע�⣺��������������ȷָ���ϲ�ڵ㣨������ڣ�������������������ϲ㺯�����
******************************************************************************************/
template <typename T> 
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)	/* vΪ�ǿ��ﱲ�ڵ� */
{ 
	/*DSA*/if (!v) { printf("\a\nFail to rotate a null node\n"); exit(-1); }
	BinNodePosi(T) p = v->parent;					/* ��v��p��g���λ�÷�������� */
	BinNodePosi(T) g = p->parent; 
	if (IsLChild(*p))								/* zig */
		if (IsLChild(*v)) 
		{											/* zig-zig */ // /* *DSA*/printf("\tzIg-zIg: ");
			p->parent = g->parent;					/* �������� */
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else 
		{											/* zig-zag */  // /* *DSA*/printf("\tzIg-zAg: ");
			v->parent = g->parent;					/* �������� */
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	else											/* zag */
		if (IsRChild(*v)) 
		{											/* zag-zag */ // /* *DSA*/printf("\tzAg-zAg: ");
			p->parent = g->parent;					/* �������� */
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else 
		{											/* zag-zig */  // /* *DSA*/printf("\tzAg-zIg: ");
			v->parent = g->parent;					/* �������� */
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
}

#endif