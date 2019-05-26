/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef SPLAY_H__
#define SPLAY_H__

#include "../BST/BST.h"			/* ����BSTʵ��Splay */

/* ��BST������Splay��ģ���� */
template <typename T>
class Splay : public BST<T> {
protected:
   BinNodePosi(T) splay ( BinNodePosi(T) v );	/* ���ڵ�v��չ���� */
public:
   BinNodePosi(T) & search ( const T& e );		/* ���ң���д�� */
   BinNodePosi(T) insert ( const T& e );		/* ���루��д�� */
   bool remove ( const T& e );					/* ɾ������д�� */
};

/* ����չ���в���e */
template <typename T> 
BinNodePosi(T) & Splay<T>::search(const T& e) { 
	BinNodePosi(T) p = searchIn(this->_root, e, this->_hot = NULL);
	this->_root = splay(p ? p : this->_hot);	/* �����һ�������ʵĽڵ���չ���� */
	return this->_root;
}												/* ������BST��ͬ�����۲��ҳɹ����_root��ָ����󱻷��ʵĽڵ� */

/* ���ؼ���e������չ���� */
template <typename T> 
BinNodePosi(T) Splay<T>::insert(const T& e) { 
	if (!this->_root) {							/* ����ԭ��Ϊ�յ��˻���� */
		this->_size++;
		return this->_root = new BinNode<T>(e);
	} 
	if (e == search(e)->data) 
		return this->_root;						/* ȷ��Ŀ��ڵ㲻���� */
	this->_size++;
	BinNodePosi(T) t = this->_root;				/* �����½ڵ㡣���µ���<=7��ָ������ɾֲ��ع� */
	if (this->_root->data < e) {				/* �����¸�����t��t->rcΪ���Һ��� */
		t->parent = this->_root = new BinNode<T>(e, NULL, t, t->rc); /* 2 + 3�� */
		if (HasRChild(*t)) {									/* <= 2�� */
			t->rc->parent = this->_root;
			t->rc = NULL;
		}
	}
	else {										/* �����¸�����t->lc��tΪ���Һ��� */
		t->parent = this->_root = new BinNode<T>(e, NULL, t->lc, t);	/* 2 + 3�� */
		if (HasLChild(*t)) {											/* <= 2�� */
			t->lc->parent = this->_root;
			t->lc = NULL; 
		} 
	}
	this->updateHeightAbove(t);					/* ����t�������ȣ�ʵ����ֻ��_rootһ�����ĸ߶� */
	return this->_root;							/* �½ڵ��Ȼ��������������֮ */
}												/* ����e�Ƿ������ԭ���У�����ʱ����_root->data == e */

/* ����չ����ɾ���ؼ���e */
template <typename T>
bool Splay<T>::remove(const T& e) { 
	if (!this->_root || (e != search(e)->data))
		return false;							/* �����ջ�Ŀ�겻���ڣ����޷�ɾ�� */
	BinNodePosi(T) w = this->_root;				/* assert: ��search()��ڵ�e�ѱ���չ������ */
	if (!HasLChild(*(this->_root))) {			/* ��������������ֱ��ɾ�� */
		this->_root = this->_root->rc;
		if (this->_root) this->_root->parent = NULL;
	}
	else if (!HasRChild(*(this->_root))) {		/* ������������Ҳֱ��ɾ�� */
		this->_root = this->_root->lc;
		if (this->_root) this->_root->parent = NULL;
	}
	else {										/* ����������ͬʱ���ڣ��� */
		BinNodePosi(T) lTree = this->_root->lc;
		lTree->parent = NULL; 
		this->_root->lc = NULL;					/* ��ʱ���������г� */
		this->_root = this->_root->rc;
		this->_root->parent = NULL;				/* ֻ���������� */
		this->search(w->data);					/* ��ԭ����ΪĿ�꣬��һ�Σ��ض�ʧ�ܵģ����� */
												/*  assert: ���ˣ�����������С�ڵ����չ�������ң�������ͬ�ڵ㣩���������ؿգ����� */
		this->_root->lc = lTree;				/* ֻ�轫ԭ�������ӻ�ԭλ���� */
		lTree->parent = this->_root;
	}
	release(w->data);							/* �ͷŽڵ㣬���¹�ģ */
	release(w); 
	this->_size--;
	if (this->_root)
		this->updateHeight(this->_root);		/* �˺������ǿգ��������ĸ߶���Ҫ���� */
	return true;								/* ���سɹ���־ */
}												/* ��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false */

/* �ڽڵ�*p��*lc������Ϊ�գ�֮�佨���������ӹ�ϵ */
template <typename NodePosi> inline 
void attachAsLChild(NodePosi p, NodePosi lc)
{ 
	p->lc = lc; 
	if (lc) lc->parent = p; 
}

/* �ڽڵ�*p��*rc������Ϊ�գ�֮�佨�������ң��ӹ�ϵ */
template <typename NodePosi> inline 
void attachAsRChild(NodePosi p, NodePosi rc)
{
	p->rc = rc;
	if (rc) rc->parent = p;
}

/* Splay����չ�㷨���ӽڵ�v���������չ */
template <typename T> 
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) {	/* vΪ��������ʶ�����չ�Ľڵ�λ�� */
	if (!v) return NULL; 
	BinNodePosi(T) p;								/* *v�ĸ������游 */
	BinNodePosi(T) g; 
	while ((p = v->parent) && (g = p->parent)) {	/* ���¶��ϣ�������*v��˫����չ */
		BinNodePosi(T) gg = g->parent;				/* ÿ��֮��*v����ԭ���游��great-grand parent��Ϊ�� */
		if (IsLChild(*v))
			if (IsLChild(*p)) {						/* zig-zig */
				/*DSA*/printf("\tzIg-zIg :"); print(g); print(p); print(v); printf("\n");
				attachAsLChild(g, p->rc); attachAsLChild(p, v->rc);
				attachAsRChild(p, g); attachAsRChild(v, p);
			}
			else {									/* zig-zag */
				/*DSA*/printf("\tzIg-zAg :"); print(g); print(p); print(v); printf("\n");
				attachAsLChild(p, v->rc); attachAsRChild(g, v->lc);
				attachAsLChild(v, g); attachAsRChild(v, p);
			}
		else if (IsRChild(*p)) {					/* zag-zag */
			/*DSA*/printf("\tzAg-zAg :"); print(g); print(p); print(v); printf("\n");
			attachAsRChild(g, p->lc); attachAsRChild(p, v->lc);
			attachAsLChild(p, g); attachAsLChild(v, p);
		}
		else {										/* zag-zig */
			/*DSA*/printf("\tzAg-zIg :"); print(g); print(p); print(v); printf("\n");
			attachAsRChild(p, v->lc); attachAsLChild(g, v->rc);
			attachAsRChild(v, g); attachAsLChild(v, p);
		}
		if (!gg) v->parent = NULL;					/* ��*vԭ�ȵ����游*gg�����ڣ���*v����ӦΪ���� */
		else										/* ����*gg�˺�Ӧ����*v��Ϊ����Һ��� */
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		this->updateHeight(g);
		this->updateHeight(p);
		this->updateHeight(v);
	}												/* ˫����չ����ʱ������g == NULL����p���ܷǿ� */
	if (p = v->parent) {							/* ��p����ǿգ����������һ�ε��� */
		/*DSA*/if (IsLChild(*v)) {
			printf("\tzIg :"); 
			print(p);
			print(v); 
			printf("\n");
		}
		/*DSA*/else {
			printf("\tzAg :");
			print(p); 
			print(v);
			printf("\n");
		}
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rc);
			attachAsRChild(v, p);
		}
		else{ 
			attachAsRChild(p, v->lc); 
			attachAsLChild(v, p); 
		}
		this->updateHeight(p);
		this->updateHeight(v);
	}
	v->parent = NULL;
	return v;
}													/* ����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ظýڵ��λ���Ա��ϲ㺯���������� */
#endif // !SPLAY_H__