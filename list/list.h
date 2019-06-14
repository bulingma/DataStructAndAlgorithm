/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef LIST_H__
#define LIST_H__

#include "listNode.h"								/* �����б�ڵ��� */

/* �б�ģ���� */
template <typename T> class List {

private:
	int _size;										/* ��ģ */
	ListNodePosi(T) header;							/* ͷ�ڱ� */
	ListNodePosi(T) trailer;						/* β�ڱ� */

protected:
	void init();									/* �б���ʱ�ĳ�ʼ�� */
	int clear();									/* ������нڵ㡢����ԭ����Ԫ�ظ��� */
	void copyNodes(ListNodePosi(T) p, int n);		/* �����б�����λ��p���n�� */
	void merge(ListNodePosi(T) & p, int n, List<T>& L, ListNodePosi(T) q, int m); /* �鲢 */
	void mergeSort(ListNodePosi(T) & p, int n);		/* �Դ�p��ʼ������n���ڵ�鲢���� */
	void selectionSort(ListNodePosi(T) p, int n);	/* �Դ�p��ʼ������n���ڵ�ѡ������ */
	void insertionSort(ListNodePosi(T) p, int n);	/* �Դ�p��ʼ������n���ڵ�������� */

public:
	/* ���캯�� */
	List() { init(); }													/* Ĭ�Ϲ��캯�� */

	List(List<T> const& L);												/* �������캯�������帴���б�L */

	List(List<T> const& L, Rank r, int n);								/* �������캯���������б�L���Ե�r�����n�� */

	List(ListNodePosi(T) p, int n);										/* �����б�����λ��p���n�� */

	/* �������� */
	~List();															/* �ͷţ�����ͷ��β�ڱ����ڵģ����нڵ� */

	/* ֻ�����ʽӿ� */
	Rank size() const { return _size; }									/* ��ģ */

	bool empty() const { return _size <= 0; }							/* �п� */

	T& operator[] (Rank r) const;										/* ���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ� */

	ListNodePosi(T) first() const { return header->succ; }				/* �׽ڵ�λ�� */

	ListNodePosi(T) last() const { return trailer->pred; }				/* ĩ�ڵ�λ�� */

	bool valid(ListNodePosi(T) p){ return p && (trailer != p) && (header != p); }			/* �ж�λ��p�Ƿ����Ϸ� */

	int disordered() const;												/* �ж��б��Ƿ������� */

	ListNodePosi(T) find(T const& e) const { return find(e, _size, trailer); }				/* �����б���� */

	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;	/* ����������� */

	ListNodePosi(T) search(T const& e) const { return search(e, _size, trailer); }			/* �����б���� */

	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; /* ����������� */

	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);				/* ��p����n-1�������ѡ������� */

	ListNodePosi(T) selectMax(){ return selectMax(header->succ, _size); }					/* ��������� */

	/* ��д���ʽӿ� */
	ListNodePosi(T) insertAsFirst(T const& e);							/* ��e�����׽ڵ���� */

	ListNodePosi(T) insertAsLast(T const& e);							/* ��e����ĩ�ڵ���� */

	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);				/* ��e����p�ĺ�̲��� */

	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);				/* ��e����p��ǰ������ */

	T remove(ListNodePosi(T) p);										/* ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ� */

	void merge(List<T>& L){ merge(first(), size, L, L.first(), L._size); }					/* ȫ�б�鲢 */

	void sort(ListNodePosi(T) p, int n);								/* �б��������� */

	void sort() { sort(first(), _size); }								/* �б��������� */

	int deduplicate();													/* ����ȥ�� */

	int uniquify();														/* ����ȥ�� */

	void reverse();														/* ǰ���ã�ϰ�⣩ */

	/* ���� */
	void traverse( void (*visit) ( T& ) );								/* ����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ� */

	template <typename VST>												/* ������ */
	void traverse(VST& visit);											/* ����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�*/
};

#include "../_share/release.h"
#include "../_share/util.h"

/* �б��ʼ�����ڴ����б����ʱͳһ���� */
template <typename T>
void List<T>::init() {
	header = new ListNode<T>;						/* ����ͷ�ڱ��ڵ� */
	trailer = new ListNode<T>;						/* ����β�ڱ��ڵ� */
	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;										/* ��¼��ģ */
}

/* ����б� */
template <typename T>
int List<T>::clear() {
	int oldSize = _size;
	while (0 < _size) remove(header->succ);			/* ����ɾ���׽ڵ㣬ֱ���б��� */
	return oldSize;
}

/* �б��ڲ������������б�����λ��p���n�� */
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {	/* p�Ϸ�����������n-1�����̽ڵ� */
	init();											/* ����ͷ��β�ڱ��ڵ㲢����ʼ�� */
	while (n--)										/* ������p��n��������Ϊĩ�ڵ���� */
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

/* �����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢 */
template <typename T>
void List<T>::merge(ListNodePosi(T) & p, int n, List<T>& L, ListNodePosi(T) q, int m) {
	// assert:  this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
	//          L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
	// ע�⣺�ڹ鲢����֮��ĳ��ϣ��п��� this == L && rank(p) + n = rank(q)
	ListNodePosi(T) pp = p->pred;				/* ����ǰ����������header�����Ա㷵��ǰ ... */
	while (0 < m)								/* ��q��δ�Ƴ�����֮ǰ */
		if ((0 < n) && (p->data <= q->data))	/* ��p������������v(p) <= v(q)���� */
		{
			if (q == (p = p->succ)) break;
			n--;
		}										/* p����ϲ����б����滻Ϊ��ֱ�Ӻ�� */
		else									/* ��p�ѳ����ҽ��v(q) < v(p)���� */
		{
			insertB(p, L.remove((q = q->succ)->pred));
			m--;
		}										/* ��qת����p֮ǰ */
	p = pp->succ;								/* ȷ���鲢������ģ��£���� */
}

/* �б�Ĺ鲢�����㷨������ʼ��λ��p��n��Ԫ������ */
template <typename T>
void List<T>::mergeSort(ListNodePosi(T) & p, int n) {	/* valid(p) && rank(p) + n <= size */
	/*DSA*/printf("\tMERGEsort [%3d]\n", n);
	if (n < 2) return;									/* ��������Χ���㹻С����ֱ�ӷ��أ�����... */
	int m = n >> 1;										/* ���е�Ϊ�� */
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++)							/* �����б� */
		q = q->succ;
	mergeSort(p, m);									/* ��ǰ�������б�ֱ����� */
	mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);						/* �鲢 */
}														/* ע�⣺�����p��Ȼָ��鲢������ģ��£���� */

														/* �б��ѡ�������㷨������ʼ��λ��p��n��Ԫ������ */
template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) { /* valid(p) && rank(p) + n <= size */
	/*DSA*/printf("SelectionSort ...\n");
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)							/* ����������Ϊ(head, tail) */
		tail = tail->succ;
	while (1 < n) {										/* �����ٻ�ʣ�����ڵ�֮ǰ���ڴ����������� */
		ListNodePosi(T) max = selectMax(head->succ, n); /* �ҳ�����ߣ�����ʱ�������ȣ� */
		insertB(tail, remove(max));						/* ����������������ĩβ����Ϊ���������µ���Ԫ�أ� */
														/*DSA*/ /* swap(tail->pred->data, selectMax( head->succ, n )->data ); */
		tail = tail->pred; n--;
	}
}

/* �б�Ĳ��������㷨������ʼ��λ��p��n��Ԫ������ */
template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n) { /* valid(p) && rank(p) + n <= size */
	/*DSA*/printf("InsertionSort ...\n");
	for (int r = 0; r < n; r++) {						/* ��һΪ���ڵ� */
		insertA(search(p->data, r, p), p->data);		/* �����ʵ���λ�ò����� */
		p = p->succ;									/* ת����һ�ڵ� */
		remove(p->pred);
	}
}



/* �����б�����λ��p���n�assert: pΪ�Ϸ�λ�ã���������n-1����̽ڵ㣩 */
template <typename T>
List<T>::List(ListNodePosi(T) p, int n) {
	copyNodes(p, n);
}

/* ���帴���б�L */
template <typename T>
List<T>::List(List<T> const& L) {
	copyNodes(L.first(), L._size);
}

/* ����L���Ե�r�����n�assert: r+n <= L._size�� */
template <typename T>
List<T>::List(List<T> const& L, Rank r, int n) {
	copyNodes(L[r], n);
}

/* �б������� */
template <typename T> List<T>::~List()
{
	clear();										/* ����б��ͷ�ͷ��β�ڱ��ڵ� */
	delete header;
	delete trailer;
} 

/* �����±����������ͨ����ֱ�ӷ����б�ڵ㣨�䷽�㣬Ч�ʵͣ������ã� */
template <typename T> 
T& List<T>::operator[] (Rank r) const {				/* assert: 0 <= r < size */
	ListNodePosi(T) p = first();					/* ���׽ڵ���� */
	while (0 < r--) p = p->succ;					/* ˳����r���ڵ㼴�� */
	return p->data;									/* Ŀ��ڵ㣬������������Ԫ�� */
}

/* ͳ����������Ԫ�ضԵ����� */
template <typename T> 
int List<T>::disordered() const {					
	int n = 0; 
	ListNode<T>* p = first();
	for (int i = 0; i < _size - 1; p = p->succ, i++)
		if (p->data > p->succ->data) n++;
	return n;
}

/* �������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�����e������� */
template <typename T> 
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p) const {
	while (0 < n--)									/*  (0 <= n <= rank(p) < _size������p�������n��ǰ������������ */
		if (e == (p = p->pred)->data)
			return p;								/*  ����ȶԣ�ֱ�����л�ΧԽ�� */
	return NULL;									/*  pԽ����߽���ζ�������ڲ���e������ʧ�� */
}													/*  ʧ��ʱ������NULL */

/* �������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�������e������� */
template <typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const {
	/*  assert: 0 <= n <= rank(p) < _size */
	/*DSA*/printf("searching for "); print(e); printf(" :\n");
	while (0 <= n--)								/* ����p�������n��ǰ����������������Ƚ� */
		/*DSA*/ {
		printf("  <%4d>", p->pred->data);
		if (((p = p->pred)->data) <= e) break;		/* ֱ�����С���ֵԽ���ΧԽ�� */
	/*DSA*/
	} printf("\n");
													/*  assert: ����λ��p�ط����������Լ���������ܴ�ǰ���һ�ιؼ���ȽϿ���û�����壨��Ч����-inf�Ƚϣ� */
	return p;										/* ���ز�����ֹ��λ�� */
}													/* ʧ��ʱ������������߽��ǰ����������header�����������߿�ͨ��valid()�жϳɹ���� */

/* ����ʼ��λ��p��n��Ԫ����ѡ������� */
template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodePosi(T) max = p;							/* ������ݶ�Ϊ�׽ڵ�p */
	for (ListNodePosi(T) cur = p; 1 < n; n--)			/* ���׽ڵ�p�������������ڵ���һ��max�Ƚ� */
		if (!lt((cur = cur->succ)->data, max->data))	/* ����ǰԪ�ز�С��max���� */
			max = cur;									/* �������Ԫ��λ�ü�¼ */
	return max;											/* �������ڵ�λ�� */
}


/* e�����׽ڵ���� */
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

/* e����ĩ�ڵ���� */
template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

/* e����p�ĺ�̲��루After�� */
template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

/* e����p��ǰ�����루Before�� */
template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

/* ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ� */
template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
	T e = p->data;									/* ���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ�� */
	p->succ->pred = p->pred;
	p->pred->succ = p->succ;
	delete p;
	_size--;
	return e;
}

/* �б��������� */
template <typename T> void List<T>::sort(ListNodePosi(T) p, int n) {
	switch (rand() % 3) {							/* ���ѡȡ�����㷨���ɸ��ݾ���������ص����ѡȡ������ */
	case 1:  insertionSort(p, n); break;			/* �������� */
	case 2:  selectionSort(p, n); break;			/* ѡ������ */
	default: mergeSort(p, n); break;				/* �鲢���� */
	}
}

/* �޳������б��е��ظ��ڵ� */
template <typename T> int List<T>::deduplicate() { 
	if (_size < 2) return 0;						/* ƽ���б���Ȼ���ظ� */
	int oldSize = _size;							/* ��¼ԭ��ģ */
	ListNodePosi(T) p = header; Rank r = 0;			/* p���׽ڵ㿪ʼ */
	while (trailer != (p = p->succ)) {				/* ����ֱ��ĩ�ڵ� */
		ListNodePosi(T) q = find(p->data, r, p);	/* ��p��r�����棩ǰ���в�����ͬ�� */
		q ? remove(q) : r++;						/* ����ȷ���ڣ���ɾ��֮�������ȼ�һ */
	}												/* assert: ѭ�������е�����ʱ�̣�p������ǰ��������ͬ */
	return oldSize - _size;							/* �б��ģ�仯��������ɾ��Ԫ������ */
}

/* �����޳��ظ�Ԫ�أ�Ч�ʸ��� */
template <typename T> 
int List<T>::uniquify() { 
	if (_size < 2) return 0;						/* ƽ���б���Ȼ���ظ� */
	int oldSize = _size;							/* ��¼ԭ��ģ */
	ListNodePosi(T) p = first(); ListNodePosi(T) q; /* pΪ��������㣬qΪ���� */
	while (trailer != (q = p->succ))				/* ����������ڵĽڵ��(p, q) */
		if (p->data != q->data) p = q;				/* �����죬��ת����һ���� */
		else remove(q);								/* ������ͬ����ɾ������ */
		return oldSize - _size;						/* �б��ģ�仯��������ɾ��Ԫ������ */
}

/* ǰ���� */
template <typename T> void List<T>::reverse() { 
	ListNodePosi(T) p = header;							/* ͷ��β�ڵ� */
	ListNodePosi(T) q = trailer; 
	for (int i = 1; i < _size; i += 2)					/* �����ס�ĩ�ڵ㿪ʼ��������ڣ�׽�Ե� */
		swap((p = p->succ)->data, (q = q->pred)->data); /* �����Գƽڵ�������� */
}

/* ��������ָ����Ʊ��� */
template <typename T> 
void List<T>::traverse( void( *visit ) ( T& )) {
	for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) 
		visit( p->data );
}

/* ��������������Ʊ��� */
template <typename T> template <typename VST>		/* Ԫ�����͡������� */
void List<T>::traverse( VST& visit ) {
	for ( ListNodePosi(T) p = header->succ; p != trailer; p = p->succ ) 
		visit( p->data );
}

#endif