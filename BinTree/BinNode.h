/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BINNODE_H__
#define BINNODE_H__

#include "../stack/stack@list.h"			/* ����ջģ���� */
#include "../queue/queue.h"					/* �������ģ���� */

#define BinNodePosi(T) BinNode<T>*									/* �ڵ�λ�� */
#define stature(p) ((p) ? (p)->height : -1)							/* �ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ�� */
typedef enum { RB_RED, RB_BLACK } RBColor;							/* �ڵ���ɫ */

/******************************************************************************************
* BinNode״̬�����ʵ��ж�
******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) )				/* ����ӵ��һ������ */
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )			/* ͬʱӵ���������� */
#define IsLeaf(x) ( ! HasChild(x) )

/******************************************************************************************
* ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
******************************************************************************************/
/*�ֵ�*/
#define sibling(p) ( IsLChild( *(p) ) ? (p)->parent->rc : (p)->parent->lc )		
/*����*/
#define uncle(x) ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )
/*���Ը��׵�����*/
#define FromParentTo(x) ( IsRoot(x) ? this->_root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

/******************************************************************************************
* ��AVL�������ض���ϵ����ظ���
******************************************************************************************/
/*�߶ȸ��³�������*/
/*DSA*/#define HeightUpdated(x)( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) )		/* ����ƽ������ */
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) )			/* ƽ������ */
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) )	/* AVLƽ������ */

/******************************************************************************************
* �����������ض���ϵ����ظ���
******************************************************************************************/
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) )			/* �ⲿ�ڵ�Ҳ�����ڽڵ� */
#define IsRed(p) ( ! IsBlack(p) )									/* �Ǻڼ��� */
#define BlackHeightUpdated(x) (										/*RedBlack�߶ȸ�������*/ \
   ( stature( (x).lc ) == stature( (x).rc ) ) && \
   ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) \
)

/* �������ڵ�ģ���� */
template <typename T> 
   struct BinNode { 
	
	/* ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ�� */
	T data;											/* ��ֵ */
	BinNodePosi(T) parent;							/* ���ڵ㼰���Һ��� */
	BinNodePosi(T) lc; 
	BinNodePosi(T) rc;								
	int height;										/* �߶ȣ�ͨ�ã� */
	int npl;										/* Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩 */
	RBColor color;									/* ��ɫ��������� */

	/* ���캯�� */
	BinNode() : parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { }

	BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED ) :
	data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { }
	
	/* �����ӿ� */
	int size();										/* ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ */

	BinNodePosi(T) insertAsLC ( T const& e);		/* ��Ϊ��ǰ�ڵ�����Ӳ����½ڵ� */

	BinNodePosi(T) insertAsRC ( T const& e);		/* ��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ� */

	BinNodePosi(T) succ();							/* ȡ��ǰ�ڵ��ֱ�Ӻ�� */

	template <typename VST> void travPre ( VST& visit);		/* ����������� */

	template <typename VST> void travIn ( VST& visit);		/* ����������� */

	template <typename VST> void travPost ( VST& visit);	/* ����������� */

	template <typename VST> void travLevel(VST& visit);		/* ������α��� */
	
	/* �Ƚ������е�����������һ���������в��䣩 */
	bool operator< ( BinNode const& bn ) { return data < bn.data; } 			/* С�� */
	
	bool operator== ( BinNode const& bn ) { return data == bn.data; }			/* ���� */

	/*DSA*/
	/*DSA*/BinNodePosi(T) zig();							/* ˳ʱ����ת */

	/*DSA*/BinNodePosi(T) zag();							/* ��ʱ����ת */
													
	/*DSA*/void stretchByZig(BinNodePosi(T) & x, int h);	/* ͨ��zig��ת������������x��������Ҳ�ͨ· */
													
	/*DSA*/void stretchByZag(BinNodePosi(T) & x);			/* ͨ��zag��ת������������x����������ͨ· */
};

/* ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ */
template <typename T> int BinNode<T>::size() {		
	int s = 1;										/* ���뱾�� */
	if (lc) s += lc->size();						/* �ݹ������������ģ */
	if (rc) s += rc->size();						/* �ݹ������������ģ */
	return s;
}

/* ��e��Ϊ��ǰ�ڵ�����Ӳ�������� */
template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this);
} 

/* ��e��Ϊ��ǰ�ڵ���Һ��Ӳ�������� */
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this);
} 

/* ��λ�ڵ�v��ֱ�Ӻ�� */
template <typename T> BinNodePosi(T) BinNode<T>::succ() { 
	BinNodePosi(T) s = this;						/* ��¼��̵���ʱ���� */
	if (rc) {										/* �����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ��� */
		s = rc;										/* �������� */
		while (HasLChild(*s)) s = s->lc;			/* �����С���Ľڵ� */
	}
	else {											/* ����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ��� */
		while (IsRChild(*s)) s = s->parent;			/* ������������֧�����ϳ����Ϸ��ƶ� */
		s = s->parent;								/* ����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ� */
	}
	return s;
}

/* ��������������㷨ͳһ��� */
template <typename T> template <typename VST>		/* Ԫ�����͡������� */
void BinNode<T>::travPre(VST& visit) {				
	switch (rand() % 3) {							/* �˴������ѡ���������ԣ�������ѡ�� */
	case 1:travPre_I1(this, visit); break;			/* ������#1 */
	case 2:travPre_I2(this, visit); break;			/* ������#2 */
	default:travPre_R(this, visit); break;			/* �ݹ�� */
	}
}

/* ��������������㷨��������#1�� */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travPre_I1(BinNodePosi(T) x, VST& visit) {		
	Stack<BinNodePosi(T)> S;						/* ����ջ */
	if (x) S.push(x);								/* ���ڵ���ջ */
	while (!S.empty()) {							/* ��ջ���֮ǰ����ѭ�� */
		x = S.pop();								/* ���������ʵ�ǰ�ڵ㣬��ǿպ��ӵ���ջ����Ϊ���Һ��� */
		visit(x->data);				
		if (HasRChild(*x)) S.push(x->rc); 
		if (HasLChild(*x)) S.push(x->lc);
	}
}

/* �ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ��������������� */
template <typename T, typename VST>					/* Ԫ�����͡������� */
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S) 
{
	while (x) {
		visit(x->data);								/* ���ʵ�ǰ�ڵ� */
		S.push(x->rc);								/* �Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ�� */
		x = x->lc;									/* �����֧����һ�� */
	}
}

/* ��������������㷨��������#2�� */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travPre_I2(BinNodePosi(T) x, VST& visit) 
{		
	Stack<BinNodePosi(T)> S;						/* ����ջ */
	while (true) {
		visitAlongLeftBranch(x, visit, S);			/* �ӵ�ǰ�ڵ�������������� */
		if (S.empty()) break;						/* ֱ��ջ�� */
		x = S.pop();								/* ������һ������� */
	}
}

/* ��������������㷨���ݹ�棩 */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travPre_R(BinNodePosi(T) x, VST& visit) {		
	if (!x) return;
	visit( x->data );
	travPre_R( x->lc, visit );
	travPre_R( x->rc, visit );
}

/* ��������������㷨ͳһ��� */
template <typename T> template <typename VST>		/* Ԫ�����͡������� */
void BinNode<T>::travIn(VST& visit) {				
	switch (rand() % 5) {							/* �˴������ѡ���������ԣ�������ѡ�� */
	case 1: travIn_I1(this, visit); break;			/* ������#1 */
	case 2: travIn_I2(this, visit); break;			/* ������#2 */
	case 3: travIn_I3(this, visit); break;			/* ������#3 */
	case 4: travIn_I4(this, visit); break;			/* ������#4 �ܾ�������ǳ�������� */
	default: travIn_R(this, visit); break;			/* �ݹ�� */
	}
}

/* �ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ� */
template <typename T>
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while (x) {										/* ��ǰ�ڵ���ջ���漴������֧���룬����ֱ�������� */
		S.push(x);
		x = x->lc;
	} 
}

/* ��������������㷨��������#1�� */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travIn_I1(BinNodePosi(T) x, VST& visit) {		
	Stack<BinNodePosi(T)> S;						/* ����ջ */
	while (true) {
		goAlongLeftBranch(x, S);					/* �ӵ�ǰ�ڵ������������ջ */
		if (S.empty()) break;						/* ֱ�����нڵ㴦����� */
		x = S.pop();								/* ����ջ���ڵ㲢����֮ */
		visit(x->data);				
		x = x->rc;									/* ת�������� */
	}
}

/* ��������������㷨��������#2�� */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travIn_I2(BinNodePosi(T) x, VST& visit) {		/* ��������������㷨��������#2�� */
	Stack<BinNodePosi(T)> S;						/* ����ջ */
	while (true)
		if (x) {
			S.push(x);								/* ���ڵ��ջ */
			x = x->lc;								/* ������������� */
		}
		else if (!S.empty()) {
			x = S.pop();							/* ��δ���ʵ�������Ƚڵ���ջ */
			visit(x->data);							/* ���ʸ����Ƚڵ� */
			x = x->rc;								/* �������ȵ������� */
		}
		else
			break;									/* ������� */
}

/* ��������������㷨��������#3�����踨��ջ�� */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travIn_I3(BinNodePosi(T) x, VST& visit) {		/* ��������������㷨��������#3�����踨��ջ�� */
	bool backtrack = false;							/* ǰһ���Ƿ�մ����������ݡ���ʡȥջ����O(1)�����ռ� */
	while (true)
		if (!backtrack && HasLChild(*x))			/* �����������Ҳ��Ǹոջ��ݣ��� */
			x = x->lc;								/* ������������� */
		else {										/* ���򡪡�����������ոջ��ݣ��൱������������ */
			visit(x->data);							/* ���ʸýڵ� */
			if (HasRChild(*x)) {					/* �����������ǿգ��� */
				x = x->rc;							/* ������������������ */
				backtrack = false;					/* ���رջ��ݱ�־ */
			}
			else {									/* ���������գ��� */
				if (!(x = x->succ())) break;		/* ���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ� */
				backtrack = true;					/* �����û��ݱ�־ */
			}
		}
}

/* ���������������������#4������ջ���־λ�� */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travIn_I4(BinNodePosi(T) x, VST& visit) {		/* ���������������������#4������ջ���־λ�� */
	while (true)
		if (HasLChild(*x))							/* �������������� */
			x = x->lc;								/* ������������� */
		else {										/* ���� */
			visit(x->data);							/* ���ʵ�ǰ�ڵ㣬�� */
			while (!HasRChild(*x))					/* ���ϵ������ҷ�֧�� */
				if (!(x = x->succ())) return;		/* ������ֱ�Ӻ�̣���û�к�̵�ĩ�ڵ㴦��ֱ���˳��� */
				else visit(x->data);				/* �����µĵ�ǰ�ڵ� */
				x = x->rc;							/* ��ֱ�����ҷ�֧����ת��ǿյ������� */
		}
}

/* ��������������㷨���ݹ�棩 */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travIn_R(BinNodePosi(T) x, VST& visit) {		
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

/* ��������������㷨ͳһ��� */
template <typename T> template <typename VST>		/* Ԫ�����͡������� */
void BinNode<T>::travPost(VST& visit) {				
	switch (rand() % 2) {							/* �˴������ѡ���������ԣ�������ѡ�� */
	case 1: travPost_I(this, visit); break;			/* ������-������� */
	default: travPost_R(this, visit); break;		/* �ݹ�� */
	}
}

//����Sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
template <typename T> 
static void gotoHLVFL(Stack<BinNodePosi(T)>& S) {	/* ��;�����ڵ�������ջ */
	while (BinNodePosi(T) x = S.top())				/* �Զ����£�������鵱ǰ�ڵ㣨��ջ���� */
		if (HasLChild(*x)) {						/* ���������� */
			if (HasRChild(*x)) S.push(x->rc);		/* �����Һ��ӣ�������ջ */
			S.push(x->lc);							/* Ȼ���ת������ */
		}
		else										/* ʵ������ */
			S.push(x->rc);							/* ������ */
	S.pop();										/* ����֮ǰ������ջ���Ŀսڵ� */
}

/* �������ĺ�������������棩 */
template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit) {		
	Stack<BinNodePosi(T)> S;						/* ����ջ */
	if (x)											
		S.push(x);									/* ���ڵ���ջ */
	while (!S.empty()) {
		if (S.top() != x->parent)					/* ��ջ���ǵ�ǰ�ڵ�֮�������Ϊ�����֣�����ʱ�� */
			gotoHLVFL(S);							/* ����������Ϊ��֮�����У��ҵ�HLVFL���൱�ڵݹ��������У� */
		x = S.pop();								/* ����ջ������ǰһ�ڵ�֮��̣���������֮ */
		visit(x->data);				
	}
}

/* ��������������㷨���ݹ�棩 */
template <typename T, typename VST>					/* Ԫ�����͡������� */
void travPost_R(BinNodePosi(T) x, VST& visit) {		
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

/* ��������α����㷨 */
template <typename T> template <typename VST>		/* Ԫ�����͡������� */
void BinNode<T>::travLevel(VST& visit) {			
	Queue<BinNodePosi(T)> Q;						/* �������� */
	Q.enqueue(this);								/* ���ڵ���� */
	while (!Q.empty()) {							/* �ڶ����ٴα��֮ǰ���������� */
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);								/* ȡ�����׽ڵ㲢����֮ */
		if (HasLChild(*x)) Q.enqueue(x->lc);		/* ������� */
		if (HasRChild(*x)) Q.enqueue(x->rc);		/* �Һ������ */
	}
}

/* ˳ʱ����ת */
template <typename T>
BinNodePosi(T) BinNode<T>::zig() {					
	BinNodePosi(T) lChild = lc;
	lChild->parent = this->parent;
	if (lChild->parent)
		((this == lChild->parent->rc) ? lChild->parent->rc : lChild->parent->lc) = lChild;
	lc = lChild->rc; 
	if (lc) 
		lc->parent = this;
	lChild->rc = this; 
	this->parent = lChild;
	return lChild;
}

/* ��ʱ����ת */
template <typename T> 
BinNodePosi(T) BinNode<T>::zag() {					
	BinNodePosi(T) rChild = rc;
	rChild->parent = this->parent;
	if (rChild->parent)
		((this == rChild->parent->lc) ? rChild->parent->lc : rChild->parent->rc) = rChild;
	rc = rChild->lc; 
	if (rc) rc->parent = this;
	rChild->lc = this; 
	this->parent = rChild;
	return rChild;
}

/* ͨ��zig��ת������������x��������Ҳ�ͨ· */
template <typename T> 
void stretchByZig(BinNodePosi(T) & x, int h) {
	int c = 0;
	for (BinNodePosi(T) v = x; v; v = v->rc) {
		while (v->lc)
		{
			v = v->zig();
			c++;
		}
		v->height = --h;
	}
	while (x->parent) x = x->parent;
	printf("\nh = %d, c = %d\n\n", h, c);
}

/* ͨ��zag��ת������������x����������ͨ· */
template <typename T> 
void stretchByZag(BinNodePosi(T) & x) {
	int c = 0;											/* ��¼��ת���� */
	int h = 0;
	BinNodePosi(T) p = x; 
	while (p->rc) 
		p = p->rc;										/* ���ڵ㣬�����������յĸ� */
	while (x->lc) 
		x = x->lc; 
	x->height = h++;									/* ת����ʼ�����ͨ·��ĩ�� */
	for (; x != p; x = x->parent, x->height = h++) {	/* ��x�������ѿգ�������һ�� */
		while (x->rc)									/* ���򣬷����� */
		{
			x->zag();									/* ��xΪ����zag��ת */
			c++;
		}
	}													/* ֱ���ִ������ĸ� */
	printf("\nh = %d, c = %d\n\n", h, c);
}

#endif