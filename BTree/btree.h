/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BTREE_H__
#define BTREE_H__

#include "BTNode.h" /* ����B-���ڵ��� */

/* B-��ģ���� */
template <typename T> class BTree { 
protected:
   int _size;								/* ��ŵĹؼ������� */
   int _order;								/* B-���Ľ״Σ�����Ϊ3��������ʱָ����һ�㲻���޸� */
   BTNodePosi(T) _root;						/* ���ڵ� */
   BTNodePosi(T) _hot;						/* BTree::search()�����ʵķǿգ��������գ��Ľڵ�λ�� */
   void solveOverflow ( BTNodePosi(T) );	/* ����������֮��ķ��Ѵ��� */
   void solveUnderflow ( BTNodePosi(T) );	/* ��ɾ��������֮��ĺϲ����� */
public:
											/* ���캯����Ĭ��Ϊ��͵�3�� */
   BTree ( int order = 3 ) : _order ( order ), _size ( 0 ) 
   { _root = new BTNode<T>(); }
											/* �����������ͷ����нڵ� */
   ~BTree() { if ( _root ) release ( _root ); } 
   int const order() { return _order; }		/* �״� */
   int const size() { return _size; }		/* ��ģ */
   BTNodePosi(T) & root() { return _root; } /* ���� */
   bool empty() const { return !_root; }	/* �п� */
   BTNodePosi(T) search ( const T& e );		/* ���� */
   bool insert ( const T& e );				/* ���� */
   bool remove ( const T& e );				/* ɾ�� */
}; /* BTree

/* ��B-���в��ҹؼ���e */
template <typename T> 
BTNodePosi(T) BTree<T>::search(const T& e) { 
	BTNodePosi(T) v = _root; 
	_hot = NULL;							/* �Ӹ��ڵ���� */
	while (v) {								/* ������ */
		Rank r = v->key.search(e);			/* �ڵ�ǰ�ڵ��У��ҵ�������e�����ؼ��� */
		if ((0 <= r) && (e == v->key[r])) 
			return v;						/* �ɹ����ڵ�ǰ�ڵ�������Ŀ��ؼ��� */
		_hot = v; 
		v = v->child[r + 1];				/* ����ת���Ӧ������_hotָ���丸����������I/O�����ʱ�� */
	}										/* �������������Ƕ��ֲ��ң�����ͨ����_order��ֱ��˳����� */
	return NULL;							/* ʧ�ܣ����յִ��ⲿ�ڵ� */
}

/* ���ؼ���e����B���� */
template <typename T> 
bool BTree<T>::insert(const T& e) {			
	BTNodePosi(T) v = search(e);			/* ȷ��Ŀ��ڵ㲻���� */
	if (v) 
		return false; 
	Rank r = _hot->key.search(e);			/* �ڽڵ�_hot������ؼ��������в��Һ��ʵĲ���λ�� */
	_hot->key.insert(r + 1, e);				/* ���¹ؼ��������Ӧ��λ�� */
	_hot->child.insert(r + 2, NULL);		/* ����һ��������ָ�� */
	_size++;								/* ����ȫ����ģ */
	solveOverflow(_hot);					/* ���б�Ҫ���������� */
	return true;							/* ����ɹ� */
}

/* ��BTree����ɾ���ؼ���e */
template <typename T> 
bool BTree<T>::remove(const T& e) {			
	BTNodePosi(T) v = search(e); 
	if (!v) return false;					/* ȷ��Ŀ��ؼ������ */
	Rank r = v->key.search(e);				/* ȷ��Ŀ��ؼ����ڽڵ�v�е��ȣ����ϣ��϶��Ϸ��� */
	if (v->child[0])						/* ��v��Ҷ�ӣ���e�ĺ�̱�����ĳҶ�ڵ� */
	{
		BTNodePosi(T) u = v->child[r + 1];	/* ����������һֱ���󣬼��� */
		while (u->child[0])					/* �ҳ�e�ĺ�� */
			u = u->child[0]; 
		v->key[r] = u->key[0];				/* ����֮����λ�� */
		v = u; 
		r = 0;
	}										/* ���ˣ�v��Ȼλ����ײ㣬�����е�r���ؼ�����Ǵ�ɾ���� */
	v->key.remove(r);						/* ɾ��e���Լ����������ⲿ�ڵ�֮һ */
	v->child.remove(r + 1);
	_size--; 
	solveUnderflow(v);						/* ���б�Ҫ��������ת��ϲ� */
	return true;
}

/* �ؼ����������ڵ����磬�����ڵ���Ѵ��� */
template <typename T> 
void BTree<T>::solveOverflow(BTNodePosi(T) v) {
	if (_order >= v->child.size())						/* �ݹ������ǰ�ڵ㲢δ���� */
		return;
	Rank s = _order / 2;								/* ��㣨��ʱӦ��_order = key.size() = child.size() - 1�� */
	BTNodePosi(T) u = new BTNode<T>();					/* ע�⣺�½ڵ�����һ���պ��� */
	for (Rank j = 0; j < _order - s - 1; j++) {			/* v�Ҳ�_order-s-1�����Ӽ��ؼ������Ϊ�Ҳ�ڵ�u */
		u->child.insert(j, v->child.remove(s + 1));		/* ����ƶ�Ч�ʵ� */
		u->key.insert(j, v->key.remove(s + 1));			/* �˲��ԿɸĽ� */
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);	/* �ƶ�v��ҵĺ��� */
	if (u->child[0])									/* ��u�ĺ����Ƿǿգ��� */
		for (Rank j = 0; j < _order - s; j++)			/* �����ǵĸ��ڵ�ͳһ */
			u->child[j]->parent = u;					/* ָ��u */
	BTNodePosi(T) p = v->parent;						/* v��ǰ�ĸ��ڵ�p */
	if (!p)												/* ��p���򴴽�֮ */
	{
		_root = p = new BTNode<T>();
		p->child[0] = v; 
		v->parent = p;
	} 
	Rank r = 1 + p->key.search(v->key[0]);				/* p��ָ��u��ָ����� */
	p->key.insert(r, v->key.remove(s));					/* ���ؼ������� */
	p->child.insert(r + 1, u);							/* �½ڵ�u�븸�ڵ�p���� */
	u->parent = p; 
	solveOverflow(p);									/* ����һ�㣬���б�Ҫ��������ѡ�������ݹ�O(logn)�� */
}

/* �ؼ���ɾ�������ڵ����磬�����ڵ���ת��ϲ����� */
template <typename T> 
void BTree<T>::solveUnderflow(BTNodePosi(T) v) {
	if ((_order + 1) / 2 <= v->child.size())			/* �ݹ������ǰ�ڵ㲢δ���� */
		return; 
	BTNodePosi(T) p = v->parent;
	if (!p) {											/* �ݹ�����ѵ����ڵ㣬û�к��ӵ����� */
		if (!v->key.size() && v->child[0]) {			/* ��������Ϊ������v�Ѳ����ؼ��룬ȴ�У�Ψһ�ģ��ǿպ��ӣ��� */
			/*DSA*/printf("collapse\n");
			_root = v->child[0];						/* ����ڵ�ɱ����� */
			_root->parent = NULL; 
			v->child[0] = NULL; 
			release(v);									/* ���������ö������� */
		}												/* �����߶Ƚ���һ�� */
		return;
	}
	Rank r = 0; 
	while (p->child[r] != v) 
		r++;
	/* ȷ��v��p�ĵ�r�����ӡ�����ʱv���ܲ����ؼ��룬�ʲ���ͨ���ؼ������ */
	/* ���⣬��ʵ���˺���ָ����е���֮��Ҳ��ֱ�ӵ���Vector::find()��λ */
	/*DSA*/printf("\nrank = %d", r);
	/*  ���1�������ֵܽ�ؼ��� */
	if (0 < r) {										/* ��v����p�ĵ�һ�����ӣ��� */
		BTNodePosi(T) ls = p->child[r - 1];				/* ���ֵܱش��� */
		if ((_order + 1) / 2 < ls->child.size()) {		/* �����ֵ��㹻���֡����� */
			/*DSA*/printf(" ... case 1\n");
			v->key.insert(0, p->key[r - 1]);			/* p���һ���ؼ����v����Ϊ��С�ؼ��룩 */
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1); /* ls�����ؼ���ת��p */
			v->child.insert(0, ls->child.remove(ls->child.size() - 1));
														/* ͬʱls�����Ҳຢ�ӹ��̸�v */
			if (v->child[0]) v->child[0]->parent = v;	/* ��Ϊv������ຢ�� */
			return;										/* ���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦�� */
		}
	}													/* ���ˣ����ֵ�ҪôΪ�գ�Ҫô̫���ݡ� */
	/*  ���2�������ֵܽ�ؼ��� */
	if (p->child.size() - 1 > r) {						/* ��v����p�����һ�����ӣ��� */
		BTNodePosi(T) rs = p->child[r + 1];				/* ���ֵܱش��� */
		if ((_order + 1) / 2 < rs->child.size()) {		/* �����ֵ��㹻���֡����� */
			/*DSA*/printf(" ... case 2\n");
			v->key.insert(v->key.size(), p->key[r]);	/* p���һ���ؼ����v����Ϊ���ؼ��룩 */
			p->key[r] = rs->key.remove(0);				/* ls����С�ؼ���ת��p */
			v->child.insert(v->child.size(), rs->child.remove(0));
														/* ͬʱrs������ຢ�ӹ��̸�v */
			if (v->child[v->child.size() - 1])			/* ��Ϊv�����Ҳຢ�� */
				v->child[v->child.size() - 1]->parent = v;
			return;										/* ���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦�� */
		}
	}													/* ���ˣ����ֵ�ҪôΪ�գ�Ҫô̫���ݡ� */
	/*  ���3�������ֵ�ҪôΪ�գ���������ͬʱ����Ҫô��̫���ݡ������ϲ� */
	if (0 < r) {										/* �����ֵܺϲ� */
		/*DSA*/printf(" ... case 3L\n");
		BTNodePosi(T) ls = p->child[r - 1];				/* ���ֵܱش��� */
		ls->key.insert(ls->key.size(), p->key.remove(r - 1)); 
		p->child.remove(r);
														/* p�ĵ�r - 1���ؼ���ת��ls��v������p�ĵ�r������ */
		ls->child.insert(ls->child.size(), v->child.remove(0));
		if (ls->child[ls->child.size() - 1])			/* v������ຢ�ӹ��̸�ls�����Ҳຢ�� */
			ls->child[ls->child.size() - 1]->parent = ls;
		while (!v->key.empty()) {						/* vʣ��Ĺؼ���ͺ��ӣ�����ת��ls */
			ls->key.insert(ls->key.size(), v->key.remove(0));
			ls->child.insert(ls->child.size(), v->child.remove(0));
			if (ls->child[ls->child.size() - 1]) ls->child[ls->child.size() - 1]->parent = ls;
		}
		release(v);										/* �ͷ�v */
	}
	else {												/* �����ֵܺϲ� */
		/*DSA*/printf(" ... case 3R\n");
		BTNodePosi(T) rs = p->child[r + 1];				/* ���ֶȱش��� */
		rs->key.insert(0, p->key.remove(r)); 
		p->child.remove(r);
														/* p�ĵ�r���ؼ���ת��rs��v������p�ĵ�r������ */
		rs->child.insert(0, v->child.remove(v->child.size() - 1));
		if (rs->child[0]) rs->child[0]->parent = rs;	/* v������ຢ�ӹ��̸�ls�����Ҳຢ�� */
		while (!v->key.empty()) {						/* vʣ��Ĺؼ���ͺ��ӣ�����ת��rs */
			rs->key.insert(0, v->key.remove(v->key.size() - 1));
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			if (rs->child[0]) rs->child[0]->parent = rs;
		}
		release(v);										/* �ͷ�v */
	}
	solveUnderflow(p);									/* ����һ�㣬���б�Ҫ��������ѡ�������ݹ�O(logn)�� */
	return;
}

#endif
