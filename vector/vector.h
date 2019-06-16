/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef VECTOR_H__
#define VECTOR_H__

typedef int Rank;											/* �� */
#define DEFAULT_CAPACITY  3									/* Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ���� */

/* ����ģ���� */
template <typename T> class Vector {
protected:
	Rank _size;												/* ��ģ�������������� */
	int _capacity;  
	T* _elem;										
	void copyFrom(T const* A, Rank lo, Rank hi);			/* ������������A[lo, hi) */
	void expand();											/* �ռ䲻��ʱ���� */
	void shrink();											/* װ�����ӹ�Сʱѹ�� */
	bool bubble(Rank lo, Rank hi);							/* ɨ�轻�� */
	void bubbleSort(Rank lo, Rank hi);						/* ���������㷨 */
	Rank max(Rank lo, Rank hi);								/* ѡȡ���Ԫ�� */
	void selectionSort(Rank lo, Rank hi);					/* ѡ�������㷨 */
	void merge(Rank lo, Rank mi, Rank hi);					/* �鲢�㷨 */
	void mergeSort(Rank lo, Rank hi);						/* �鲢�����㷨 */
	Rank partition(Rank lo, Rank hi);						/* ��㹹���㷨 */
	void quickSort(Rank lo, Rank hi);						/* ���������㷨 */
	void heapSort(Rank lo, Rank hi);						/* ������ */

public:
	/* ���캯�� */
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)	/* ����Ϊc����ģΪs������Ԫ�س�ʼΪv */
	{
		_elem = new T[_capacity = c]; 
		for (_size = 0; _size < s; _elem[_size++] = v);
	} /* s<=c */
	Vector(T const* A, Rank n)								/* �������帴�� */
	{ 
		copyFrom(A, 0, n); 
	}		
	Vector(T const* A, Rank lo, Rank hi)					/* ���� */
	{ 
		copyFrom(A, lo, hi); 
	}	
	Vector(Vector<T> const& V)								/* �������帴�� */
	{ 
		copyFrom(V._elem, 0, V._size); 
	}	
	Vector(Vector<T> const& V, Rank lo, Rank hi)			/* ���� */
	{					
		copyFrom(V._elem, lo, hi); 
	} 														/* �������� */
	~Vector() { delete[] _elem; }							/* �ͷ��ڲ��ռ� */
	
	/* ֻ�����ʽӿ� */
	Rank size() const { return _size; }						/* ��ģ */
	bool empty() const { return !_size; }					/* �п� */
	int disordered() const;									/* �ж������Ƿ������� */
	Rank find(T const& e) const								/* ��������������� */
	{ 
		return find(e, 0, _size);
	}		
	Rank find(T const& e, Rank lo, Rank hi) const;			/* ��������������� */
	Rank search(T const& e) const							/* ��������������� */
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}

	/* ��δ�������ڴ�ѧϰ */
	Rank search(T const& e, Rank lo, Rank hi) const;		/* ��������������� */

	/* ��д���ʽӿ� */
	T& operator[] (Rank r) const;							/* �����±������������������������ʽ���ø�Ԫ�� */
	Vector<T> & operator= (Vector<T> const&);				/* ���ظ�ֵ���������Ա�ֱ�ӿ�¡���� */
	T remove(Rank r);										/* ɾ����Ϊr��Ԫ�� */
	int remove(Rank lo, Rank hi);							/* ɾ����������[lo, hi)֮�ڵ�Ԫ�� */
	Rank insert(Rank r, T const& e);						/* ����Ԫ�� */
	Rank insert(T const& e)									/* Ĭ����ΪĩԪ�ز��� */
	{ 
		return insert(_size, e); 
	}		
	void sort(Rank lo, Rank hi);							/* ��[lo, hi)���� */
	void sort() { sort(0, _size); }							/* �������� */
	void unsort(Rank lo, Rank hi);							/* ��[lo, hi)���� */
	void unsort() { unsort(0, _size); }						/* �������� */
	int deduplicate();										/* ����ȥ�� */
	int uniquify();											/* ����ȥ�� */
	
	/* ���� */
	void traverse(void(*visit) (T&));						/* ������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ� */

	template <typename VST> 
	void traverse(VST& visit);								/* ������ʹ�ú������󣬿�ȫ�����޸ģ� */
};

/* ����������A[lo, hi)Ϊ������������ */
template <typename T>										/* Ԫ������ */
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) 
{
	_elem = new T[_capacity = 2 * (hi - lo)];				/* ����ռ䣬��ģ���� */
	_size = 0;
	while (lo < hi)											/* A[lo, hi)�ڵ�Ԫ����һ */
		_elem[_size++] = A[lo++];							/* ������_elem[0, hi - lo) */
}

/* �����ռ䲻��ʱ���� */
template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;							/* ��δ��Աʱ���������� */
	if (_capacity < DEFAULT_CAPACITY)						/* ��������С���� */
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];							/* �����ӱ� */
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];								/* ����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ������'='�� */
															/*DSA*/ //printf("\n_ELEM [%x]*%d/%d expanded and shift to [%x]*%d/%d\n", oldElem, _size, _capacity/2, _elem, _size, _capacity);
	delete[] oldElem;										/* �ͷ�ԭ�ռ� */
}

/* װ�����ӹ�Сʱѹ��������ռ�ռ� */
template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;			/* ����������DEFAULT_CAPACITY���� */
	if (_size << 2 > _capacity) return;						/* ��25%Ϊ�� */
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];							/* �������� */
	for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];	/* ����ԭ�������� */
	delete[] oldElem;										/* �ͷ�ԭ�ռ� */
}

/* һ��ɨ�轻�� */
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true;										/* ���������־ */
	while (++lo < hi)										/* �������ң���һ����������Ԫ�� */
		if (_elem[lo - 1] > _elem[lo]) {					/* �������� */
			sorted = false;									/* ��ζ����δ�������򣬲���Ҫ */
															/* swap������û��ʵ��*/
			swap(_elem[lo - 1], _elem[lo]);					/* ͨ������ʹ�ֲ����� */
		}
	return sorted;											/* ���������־ */
}

/* �������������� */
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)				/* assert: 0 <= lo < hi <= size */
{
	while (!bubble(lo, hi--));								/* ������ɨ�轻����ֱ��ȫ�� */
}

/* ��[lo, hi]���ҳ������*/
template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
	Rank mx = hi;
	while (lo < hi--)										/* ����ɨ�� */
		if (_elem[hi] > _elem[mx])							/* ���ϸ�Ƚ� */
			mx = hi;										/* ������max�ж��ʱ��֤�������ȣ�������֤selectionSort�ȶ� */
	return mx;
}

/* ����ѡ������ */
template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {			/* assert: 0 < lo <= hi <= size */
	/*DSA*/printf("\tSELECTIONsort [%3d, %3d)\n", lo, hi);
	while (lo < --hi)
		swap(_elem[max(lo, hi)], _elem[hi]);				/* ��[hi]��[lo, hi]�е�����߽��� */
}

/* ���������Ĺ鲢 */
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {			/* ���������������[lo, mi)��[mi, hi) */
	T* A = _elem + lo;										/* �ϲ��������A[0, hi - lo) = _elem[lo, hi) */
	int lb = mi - lo; T* B = new T[lb];						/* ǰ������B[0, lb) = _elem[lo, mi) */
	for (Rank i = 0; i < lb; B[i] = A[i++]);				/* ����ǰ������ */
	int lc = hi - mi; T* C = _elem + mi;					/* ��������C[0, lc) = _elem[mi, hi) */
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); )	/* B[j]��C[k]�е�С������Aĩβ */
	{
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] <  B[j]))) A[i++] = C[k++];
	}
	delete[] B;												/* �ͷ���ʱ�ռ�B */
}															/* �鲢��õ���������������[lo, hi) */

															/* �����鲢���� */
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {				/* 0 <= lo < hi <= size */
	/*DSA*/printf("\tMERGEsort [%3d, %3d)\n", lo, hi);
	if (hi - lo < 2) return;								/* ��Ԫ��������Ȼ���򣬷���... */
	int mi = (lo + hi) / 2;									/* ���е�Ϊ�� */
	mergeSort(lo, mi);										/* �ֱ����� */
	mergeSort(mi, hi);
	merge(lo, mi, hi);										/* �鲢 */
}

/* ��㹹���㷨��ͨ������Ԫ��λ�ù�������[lo, hi]����㣬���������� */
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {				/* �汾B�����Ż��������ؼ�����ͬ���˻���� */
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);	/* ��ѡһ��Ԫ������Ԫ�ؽ��� */
	T pivot = _elem[lo];									/* ����Ԫ��Ϊ��ѡ��㡪�������Ͻ�������Ч�����ѡȡ */
	while (lo < hi) {										/* �����������˽�������м�ɨ�� */
		while (lo < hi)
			if (pivot < _elem[hi])							/* �ڴ���pivot��ǰ���� */
				hi--;										/* ������չ�Ҷ������� */
			else											/* ֱ������������pivot�� */
			{
				_elem[lo++] = _elem[hi]; break;
			}												/* ���������������� */
		while (lo < hi)
			if (_elem[lo] < pivot)							/* ��С��pivot��ǰ���� */
				lo++;										/* ������չ��������� */
			else											/* ֱ��������С��pivot�� */
			{
				_elem[hi--] = _elem[lo]; break;
			}												/* ��������Ҷ������� */
	}														/* assert: lo == hi */
	_elem[lo] = pivot;										/* �����ݵ�����¼����ǰ����������֮�� */
	return lo;												/* ���������� */
}

/* ������������ */
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {				/* 0 <= lo < hi <= size */
	/*DSA*/printf("\tQUICKsort [%3d, %3d)\n", lo, hi);
	if (hi - lo < 2) return;								/* ��Ԫ��������Ȼ���򣬷���... */
	Rank mi = partition(lo, hi - 1);						/* ��[lo, hi - 1]�ڹ������ */
	quickSort(lo, mi);										/* ��ǰ׺�ݹ����� */
	quickSort(mi + 1, hi);									/* �Ժ�׺�ݹ����� */
}

/* ���������� */
template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) {				//0 <= lo < hi <= size
															/*DSA*/
	printf("\tHEAPsort [%3d, %3d)\n", lo, hi);
	PQ_ComplHeap<T> H(_elem + lo, hi - lo);					//�����������佨��һ����ȫ����ѣ�O(n)
	while (!H.empty())										//������ժ�����Ԫ������������ĺ�׺��ֱ���ѿ�
															/*DSA*/
	{
		_elem[--hi] = H.delMax();							//��Ч�ڶѶ���ĩԪ�ضԻ�������
															/*DSA*/
		for (int i = lo; i < hi; i++) print(H[i]);
		print(_elem[hi]);
		printf("\n");
		/*DSA*/
	}
}

/* ������������������Ԫ�ضԵ����� */
template <typename T>
int Vector<T>::disordered() const {
	int n = 0;												/* ������ */
	for (int i = 1; i < _size; i++)							/* ��һ���_size - 1������Ԫ�� */
		if (_elem[i - 1] > _elem[i]) n++;					/* ��������� */
	return n;												/* ���������ҽ���n = 0 */
}

/* ����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo - 1 */
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {	/* assert: 0 <= lo < hi <= _size */
	while ((lo < hi--) && (e != _elem[hi]));				/* �Ӻ���ǰ��˳����� */
	return hi;												/* ��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص��� */
}

/* ���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size */
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
	/*DSA*/printf("BIN search (C)\n");
	while (lo < hi) {										/* ÿ������������һ�αȽ��жϣ���������֧ */
		/*DSA*/ for (int i = 0; i < lo; i++) printf("     "); if (lo >= 0) for (int i = lo; i < hi; i++) printf("....^"); printf("\n");
		Rank mi = (lo + hi) >> 1;							/* ���е�Ϊ��� */
		(e < A[mi]) ? hi = mi : lo = mi + 1;				/* ���ȽϺ�ȷ������[lo, mi)��(mi, hi) */
	}														/* �ɹ����Ҳ�����ǰ��ֹ */
	/*DSA*/ for (int i = 0; i < lo - 1; i++) printf("     "); if (lo > 0) printf("....|\n"); else printf("<<<<|\n");
	return --lo;											/* ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������ */
}															/* �ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ�� */
		
/* ����Fib������ */
#include "..\fibonacci\Fib.h"
/* Fibonacci�����㷨���汾B��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size */
template <typename T> static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
	/*DSA*/printf("FIB search (B)\n");
	Fib fib(hi - lo);										/* ��O(log_phi(n = hi - lo)ʱ�䴴��Fib���� */
	while (lo < hi) {										/* ÿ������������һ�αȽ��жϣ���������֧ */
		/*DSA*/ for (int i = 0; i < lo; i++) printf("     "); if (lo >= 0) for (int i = lo; i < hi; i++) printf("....^"); else printf("<<<<|"); printf("\n");
		while (hi - lo < fib.get()) fib.prev();				/* ͨ����ǰ˳����ң���̯O(1)����������������Σ� */
		Rank mi = lo + fib.get() - 1;						/* ȷ������Fib(k) - 1����� */
		(e < A[mi]) ? hi = mi : lo = mi + 1;				/* �ȽϺ�ȷ������ǰ���[lo, mi)�����(mi, hi) */
	}														/* �ɹ����Ҳ�����ǰ��ֹ */
	/*DSA*/ for (int i = 0; i < lo - 1; i++) printf("     "); if (lo > 0) printf("....|\n"); else printf("<<<<|\n");
	return --lo;											/* ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������ */
}															/* �ж������Ԫ��ʱ�����ܱ�֤������������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ�� */

/* ����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ���� */
template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {/* assert: 0 <= lo < hi <= _size */
															/* ����50%�ĸ������ʹ�ö��ֲ��һ�Fibonacci���� */
	return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

/* �����±������ */
template <typename T>
T& Vector<T>::operator[] (Rank r) const
{
	return _elem[r];
} /* assert: 0 <= r < _size */

  /* ���ظ�ֵ������ */
template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V) {
	if (_elem) delete[] _elem;								/* �ͷ�ԭ������ */
	copyFrom(V._elem, 0, V.size());							/* ���帴�� */
	return *this;											/* ���ص�ǰ��������ã��Ա���ʽ��ֵ */
}

/* ɾ����������Ϊr��Ԫ�أ�0 <= r < size */
template <typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r];											/* ���ݱ�ɾ��Ԫ�� */
	remove(r, r + 1);										/* ��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ�� */
	return e;												/* ���ر�ɾ��Ԫ�� */
}

/* ɾ������[lo, hi) */
template <typename T> int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0;									/* ����Ч�ʿ��ǣ����������˻����������remove(0, 0) */
	while (hi < _size) _elem[lo++] = _elem[hi++];			/* [hi, _size)˳��ǰ��hi - lo����Ԫ */
	_size = lo;												/* ���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)���� */
	shrink();												/* ���б�Ҫ�������� */
	return hi - lo;											/* ���ر�ɾ��Ԫ�ص���Ŀ */
}

/* ��e��Ϊ��ΪrԪ�ز��� */
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {				/* assert: 0 <= r <= size */
	expand();												/* ���б�Ҫ������ */
	for (int i = _size; i > r; i--)							/* �Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ */
		_elem[i] = _elem[i - 1];
	_elem[r] = e;											/* ������Ԫ�ز��������� */
	_size++;
	return r;												/* ������ */
}

/* ��������[lo, hi)���� */
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
	switch (rand() % 5) {									/* ���ѡȡ�����㷨���ɸ��ݾ���������ص����ѡȡ������ */
	case 1:  bubbleSort(lo, hi); break;						/* �������� */
	case 2:  selectionSort(lo, hi); break;					/* ѡ������ϰ�⣩ */
	case 3:  mergeSort(lo, hi); break;						/* �鲢���� */
	case 4:  heapSort(lo, hi); break;						/* ������ */
	default: quickSort(lo, hi); break;						/* ���������Ժ���ܣ� */
	}
	/*DSA*/													/* selectionSort(lo, hi); */
}

/* �ȸ��������������[lo, hi) */
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* V = _elem + lo;										/* ��������_elem[lo, hi)������һ����V[0, hi - lo) */
	for (Rank i = hi - lo; i > 0; i--)						/* �Ժ���ǰ */
		swap(V[i - 1], V[rand() % i]);						/* ��V[i - 1]��V[0, i)��ĳһԪ��������� */
}

/* �÷��������⣬������ */
/* ɾ�������������ظ�Ԫ�أ���Ч�棩 */
template <typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size;									/* ��¼ԭ��ģ */
	Rank i = 1;												/* ��_elem[1]��ʼ */
	while (i < _size)										/* ��ǰ�����һ�����Ԫ��_elem[i] */
		(find(_elem[i], 0, i) < 0) ?						/* ����ǰ׺��Ѱ����֮��ͬ�ߣ�����һ���� */
		i++ : remove(i);									/* ������ͬ������������̣�����ɾ����ͬ�� */
	return oldSize - _size;									/* ������ģ�仯��������ɾ��Ԫ������ */
}

/* ���������ظ�Ԫ���޳��㷨����Ч�棩 */
template <typename T>
int Vector<T>::uniquify() {
	Rank i = 0, j = 0;										/* ���Ի��조���ڡ�Ԫ�ص��� */
	while (++j < _size)										/* ��һɨ�裬ֱ��ĩԪ�� */
		if (_elem[i] != _elem[j])							/* ������ͬ�� */
			_elem[++i] = _elem[j];							/* ���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ� */
	_size = ++i;											/* ֱ�ӽس�β������Ԫ�� */
	shrink();
	return j - i;											/* ������ģ�仯��������ɾ��Ԫ������ */
}

/* �������� */
template <typename T>
void Vector<T>::traverse(void(*visit) (T&))					/* ��������ָ����� */
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

/* �������� */
template <typename T> template <typename VST>				/* Ԫ�����͡������� */
void Vector<T>::traverse(VST& visit)						/* ��������������� */
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

#endif