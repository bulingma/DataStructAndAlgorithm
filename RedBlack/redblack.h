/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef REDBLACK_H__
#define REDBLACK_H__

#include "../BST/BST.h"								/* ����BSTʵ��RedBlack */
 /* RedBlack��ģ���� */
template <typename T> 
class RedBlack : public BST<T> { 
protected:
   void solveDoubleRed ( BinNodePosi(T) x );		/* ˫������ */
   void solveDoubleBlack ( BinNodePosi(T) x );		/* ˫������ */
   int updateHeight ( BinNodePosi(T) x );			/* ���½ڵ�x�ĸ߶� */
public:
   BinNodePosi(T) insert ( const T& e );			/* ���루��д�� */
   bool remove ( const T& e );						/* ɾ������д�� */
/*  BST::search()������ӿڿ�ֱ������ */
};

/* ��e�������� */
template <typename T> 
BinNodePosi(T) RedBlack<T>::insert(const T& e) 
{ 
	BinNodePosi(T) & x = this->search(e); 
	if (x) 
		return x;									/* ȷ��Ŀ�겻���ڣ������_hot�����ã� */
	x = new BinNode<T>(e, this->_hot, NULL, NULL, -1);	/* ������ڵ�x����_hotΪ�����ڸ߶�-1 */
	this->_size++;
	solveDoubleRed(x);								/* ��˫�������󣬼��ɷ��� */
	return x ? x : this->_hot->parent;
}													/* ����e�Ƿ������ԭ���У�����ʱ����x->data == e */

/* �Ӻ������ɾ���ؼ���e */
template <typename T> 
bool RedBlack<T>::remove(const T& e) 
{
	BinNodePosi(T) & x = this->search(e);
	if (!x)											/* ȷ��Ŀ����ڣ�����_hot�����ã� */
		return false; 
	BinNodePosi(T) r = removeAt(x, this->_hot);		/* ʵʩɾ�� */
	if (!(--this->_size))
		return true;
	/*  assert: _hotĳһ���Ӹձ�ɾ�����ұ�r��ָ�ڵ㣨������NULL�����档���¼���Ƿ�ʧ�⣬������Ҫ���� */
	if (!this->_hot)								/* ���ձ�ɾ�����Ǹ��ڵ㣬�����úڣ������ºڸ߶� */
	{
		this->_root->color = RB_BLACK;
		updateHeight(this->_root);
		return true;
	}
	/*  assert: ���£�ԭx����r���طǸ���_hot�طǿ� */
	if (BlackHeightUpdated(*(this->_hot)))			/* ���������ȵĺ������Ȼƽ�⣬��������� */
		return true; 
	if (IsRed(r))									/* ������rΪ�죬��ֻ������ת�� */
	{
		r->color = RB_BLACK; 
		r->height++; 
		return true;
	}
	/*  assert: ���£�ԭx����r����Ϊ��ɫ */
	// *DSA*/printBinTree(_hot, 0, 0);
	solveDoubleBlack(r);							/* ��˫�ڵ����󷵻� */
	return true; 
}													/* ��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false */

/* ���½ڵ�߶� */
template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x) 
{ 
	x->height = max(stature(x->lc), stature(x->rc));/* ����һ��ڸ߶���ȣ����ǳ���˫�� */
	// /*DSA*/ /* ������и��ڵ����Һ��ӵĺڸ߶�ͨ����� */
	// /*DSA*/ /* ����֮����ȡ����ֵ���Ǳ�����ɾ���ڵ���ƽ����������У���ȷ���±�ɾ���ڵ㸸�׵ĺڸ߶� */
	// /*DSA*/ /* ����rotateAt()����ݱ�ɾ���ڵ������ߣ��߶�Сһ�����ø��ڵ�ĺڸ߶� */
	return IsBlack(x) ? x->height++ : x->height;	/* ����ǰ�ڵ�Ϊ�ڣ���������� */
}													/* ��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж� */

/******************************************************************************************
* RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
*    RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
*    RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
******************************************************************************************/
template <typename T> 
void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)	/* x��ǰ��Ϊ�� */
{ 
	if (IsRoot(*x))									/* ���ѣ��ݹ飩ת������������ת�ڣ������ڸ߶�Ҳ��֮���� */
	{
		this->_root->color = RB_BLACK;
		this->_root->height++;
		return;
	}												/* ����x�ĸ���p�ش��� */
	BinNodePosi(T) p = x->parent; 
	if (IsBlack(p)) 
		return;										/* ��pΪ�ڣ������ֹ���������� */
	BinNodePosi(T) g = p->parent;					/* ��ȻpΪ�죬��x���游�ش��ڣ��ұ�Ϊ��ɫ */
	BinNodePosi(T) u = uncle(x);					/* ���£���x�常u����ɫ�ֱ��� */
	if (IsBlack(u)) {								/* uΪ��ɫ����NULL��ʱ  */
		// *DSA*/printf("  case RR-1:\n");
		if (IsLChild(*x) == IsLChild(*p))			/* ��x��pͬ�ࣨ��zIg-zIg��zAg-zAg������ */
			p->color = RB_BLACK;					/* p�ɺ�ת�ڣ�x���ֺ� */
		else										/* ��x��p��ࣨ��zIg-zAg��zAg-zIg������ */
			x->color = RB_BLACK;					/* x�ɺ�ת�ڣ�p���ֺ� */
		g->color = RB_RED;							/* g�ض��ɺ�ת�� */
													/* �����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ */
													/* ����ת�󽫸��úڡ������ú죬��������Ⱦɫ��Ч�ʸ��� */
		BinNodePosi(T) gg = g->parent;				/* ���游��great-grand parent�� */
		BinNodePosi(T) r = FromParentTo(*g) = this->rotateAt(x); /* ��������������ڵ� */
		r->parent = gg;								/* ��ԭ���游���� */
	}
	else {											/* ��uΪ��ɫ */
		// *DSA*/printf("  case RR-2:\n");
		p->color = RB_BLACK;						/* p�ɺ�ת�� */
		p->height++;			
		u->color = RB_BLACK;						/* u�ɺ�ת�� */
		u->height++;
		if (!IsRoot(*g))							/* g���Ǹ�����ת�� */
			g->color = RB_RED; 
		solveDoubleRed(g);							/* ��������g��������β�ݹ飬���Ż�Ϊ������ʽ�� */
	}
}

/******************************************************************************************
* RedBlack˫�ڵ����㷨������ڵ�x�뱻������Ľڵ��Ϊ��ɫ������
* ��Ϊ�����๲���������
*    BB-1 ��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
*    BB-2R��2����ɫ��ת��2�κڸ߶ȸ��£�0����ת�����ٵݹ�
*    BB-2B��1����ɫ��ת��1�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
*    BB-3 ��2����ɫ��ת��2�κڸ߶ȸ��£�1����ת��תΪBB-1��BB2R
******************************************************************************************/
template <typename T> 
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r) {
	BinNodePosi(T) p = r ? r->parent : this->_hot;
	if (!p) 
		return;										/* r�ĸ��� */
	BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc; /* r���ֵ� */ 
	if (IsBlack(s)) {								/* �ֵ�sΪ�� */
		BinNodePosi(T) t = NULL;					/* s�ĺ캢�ӣ������Һ��ӽԺ죬�������ȣ��Ժ�ʱΪNULL�� */
		if (IsRed(s->rc)) t = s->rc;				/* ���� */
		if (IsRed(s->lc)) t = s->lc;				/* ���� */
		if (t) {									/* ��s�к캢�ӣ�BB-1 */
			// *DSA*/printf("  case BB-1: Child ("); print(s->lc); printf(") of BLACK sibling ("); print(s); printf(") is RED\n"); */
			RBColor oldColor = p->color;			/* ����ԭ�������ڵ�p��ɫ������t���丸�ס��游 */
													/*  ���£�ͨ����ת��ƽ�⣬���������������Һ���Ⱦ�� */
			BinNodePosi(T) b = FromParentTo(*p) = this->rotateAt(t); /* ��ת */
			if (HasLChild(*b)) {					/* ���� */
				b->lc->color = RB_BLACK; 
				updateHeight(b->lc); 
			} 
			if (HasRChild(*b)) {					/* ���� */
				b->rc->color = RB_BLACK;
				updateHeight(b->rc); 
			}
			b->color = oldColor; 
			updateHeight(b);						/* ���������ڵ�̳�ԭ���ڵ����ɫ */
			// *DSA*/printBinTree(b, 0, 0);
		}
		else {										/* ��s�޺캢�� */
			s->color = RB_RED;						/* sת�� */
			s->height--;
			if (IsRed(p)) {							/* BB-2R */
				// *DSA*/printf("  case BB-2R: Both children ("); print(s->lc); printf(") and ("); print(s->rc); printf(") of BLACK sibling ("); print(s); printf(") are BLACK, and parent ("); print(p); printf(") is RED\n"); /* s���Ӿ��ڣ�p��
				p->color = RB_BLACK;				/* pת�ڣ����ڸ߶Ȳ��� */
				// *DSA*/printBinTree(p, 0, 0);
			}
			else {									/* BB-2B */
				// *DSA*/printf("  case BB-2R: Both children ("); print(s->lc); printf(") and ("); print(s->rc); printf(") of BLACK sibling ("); print(s); printf(") are BLACK, and parent ("); print(p); printf(") is BLACK\n"); /* s���Ӿ��ڣ�p��
				p->height--;						/* p���ֺڣ����ڸ߶��½� */
													// *DSA*/printBinTree(p, 0, 0); */
				solveDoubleBlack(p);				/* �ݹ����� */
			}
		}
	}
	else											/* �ֵ�sΪ�죺BB-3 */
	{											
		// *DSA*/printf("  case BB-3: sibling ("); print(s); printf(" is RED\n"); /* s�죨˫�Ӿ�ڣ� */
		s->color = RB_BLACK; p->color = RB_RED;		/* sת�ڣ�pת�� */
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc; /* ȡt���丸sͬ�� */
		this->_hot = p;
		FromParentTo(*p) = this->rotateAt(t);		/* ��t���丸�ס��游��ƽ����� */
		// *DSA*/printBinTree<T>(s, 0, 0);
		solveDoubleBlack(r);						/* ��������r��˫�ڡ�����ʱ��p��ת�죬�ʺ���ֻ����BB-1��BB-2R */
	}
}

#endif // !REDBLACK_H__