/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef HASHTABLE_H__
#define HASHTABLE_H__

#include "dictionary.h"			/* ����ʵ�ADT */
#include "../bitmap/bitmap.h"	/* ����λͼ */
#include "../prime/primeNLT.h"	/* �������� */
#include "hashtable_hashcode.h"	/* ����ɢ�к��� */

/* ����Dictionary�ӿڵ�Hashtableģ���� */
template <typename K, typename V>					/* key��value */
class Hashtable : public Dictionary<K, V> { 
   /*DSA*/friend class UniPrint;
private:
   Entry<K, V>** ht;								/* Ͱ���飬��Ŵ���ָ�� */
   int M;											/* Ͱ�������� */
   int N;											/* �������� */
   Bitmap* lazyRemoval;								/* ����ɾ����� */
#define lazilyRemoved(x)  (lazyRemoval->test(x))	
#define markAsRemoved(x)  (lazyRemoval->set(x))
protected:
   int probe4Hit ( const K& k );					/* �عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ */
   int probe4Free ( const K& k );					/* �عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ */
   void rehash();									/* ��ɢ���㷨������Ͱ���飬��֤װ�������ھ��������� */
public:
   Hashtable ( int c = 5 );							/* ����һ��������С��c��ɢ�б�Ϊ������ʱѡ�ý�С��Ĭ��ֵ�� */
   ~Hashtable();									/* �ͷ�Ͱ���鼰���и����ǿգ�Ԫ����ָ��Ĵ��� */
   int size() const { return N; }					/* ��ǰ�Ĵ�����Ŀ */
   bool put ( K, V );								/* ���루��ֹ��ͬ�������ʿ���ʧ�ܣ� */
   V* get ( K k );									/* ��ȡ */
   bool remove ( K k );								/* ɾ�� */
};

/* ����ɢ�б�����Ϊ��С��c������M */
template <typename K, typename V> 
Hashtable<K, V>::Hashtable(int c) { 
													/* ��С��c������M */
	char * pcExternalFile = new char[64];
	strncpy(pcExternalFile, "../_input/prime-1048576-bitmap.txt", 64);
	M = primeNLT(c, 1048576, pcExternalFile);
	//M = primeNLT(c, 1048576, "../_input/prime-1048576-bitmap.txt"); 
	N = 0; 
	ht = new Entry<K, V>*[M];						/* ����Ͱ���飨����˶�����ɹ�������ʼװ������ΪN/M = 0% */
	memset(ht, 0, sizeof(Entry<K, V>*) *M);			/* ��ʼ����Ͱ */
	lazyRemoval = new Bitmap(M);					/* ����ɾ����Ǳ���ͼ */
	//*DSA*/printf("A bucket array has been created with capacity = %d\n\n", M);
}

/* ����ǰ�ͷ�Ͱ���鼰�ǿմ��� */
template <typename K, typename V> 
Hashtable<K, V>::~Hashtable() { 
	for (int i = 0; i < M; i++)						/* ��һ����Ͱ */
		if (ht[i]) release(ht[i]);					/* �ͷŷǿյ�Ͱ */
	release(ht);									/* �ͷ�Ͱ���� */
	release(lazyRemoval);							/* �ͷ�����ɾ����� */
}

/******************************************************************************************
* �عؼ���k��Ӧ�Ĳ��������ҵ���֮ƥ���Ͱ�������Һ�ɾ������ʱ���ã�
* ��̽���Զ��ֶ����������ѡȡ���������������̽����Ϊ��
******************************************************************************************/
template <typename K, typename V> 
int Hashtable<K, V>::probe4Hit(const K& k) {
	int r = hashCode(k) % M;						/* ����ʼͰ�������෨ȷ�������� */
	//*DSA*/printf(" ->%d", r);
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
		r = (r + 1) % M;							/* �ز�����������̽���������г�ͻ��Ͱ���Լ�������ɾ����ǵ�Ͱ */
		//*DSA*/printf(" ->%d", r);
		//*DSA*/printf("\n");
	return r;										/* �����߸���ht[r]�Ƿ�Ϊ�գ������жϲ����Ƿ�ɹ���ht[r]Ϊ�գ����ҳɹ���ht[r]�ǿգ�����ʧ�ܣ�key��ͬԪ�أ� */
}

/******************************************************************************************
* �عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ�������������ʱ���ã�
* ��̽���Զ��ֶ����������ѡȡ���������������̽����Ϊ��
******************************************************************************************/
template <typename K, typename V> 
int Hashtable<K, V>::probe4Free(const K& k) {
	int r = hashCode(k) % M;						/* ����ʼͰ�������෨ȷ�������� */
	//*DSA*/printf(" ->%d", r);						/* �׸���̽��Ͱ��Ԫ��ַ */*
	while (ht[r])									/* �ز�������Ͱ��̽��ֱ���׸���Ͱ�������Ƿ��������ɾ����ǣ� */
		r = (r + 1) % M;				
	//*DSA*/   while (ht[r]) { r = (r+1) % M; printf(" ->%d", r); } printf("\n");
	return r;										/* Ϊ��֤��Ͱ�����ҵ���װ�����Ӽ�ɢ�б���Ҫ�������� */
}

/******************************************************************************************
* ��ɢ���㷨��װ�����ӹ���ʱ����ȡ����һȡ���ٲ��롱�����ز��ԣ���Ͱ��������
* ���ɼ򵥵أ�ͨ��memcpy()����ԭͰ���鸴�Ƶ���Ͱ���飨����ǰ�ˣ�����������������⣺
* 1����̳�ԭ�г�ͻ��2�����ܵ��²������ں�˶��ѡ�������Ϊ��������Ͱ��������ɾ����־Ҳ�޼�����
******************************************************************************************/
template <typename K, typename V>
void Hashtable<K, V>::rehash() {
	int old_capacity = M;
	Entry<K, V>** old_ht = ht;
	/* �������ټӱ� */
	char * pcExternalFile = new char[64];
	strncpy(pcExternalFile, "../_input/prime-1048576-bitmap.txt", 64);
	M = primeNLT(2 * M, 1048576, pcExternalFile);
	//M = primeNLT(2 * M, 1048576, "../_input/prime-1048576-bitmap.txt");
	N = 0;
	ht = new Entry<K, V>*[M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);		/* ��Ͱ���� */
	release(lazyRemoval);
	lazyRemoval = new Bitmap(M);					/* �¿�����ɾ����Ǳ���ͼ */
													//*DSA*/printf("A bucket array has been created with capacity = %d\n\n", M); */
	for (int i = 0; i < old_capacity; i++)			/* ɨ��ԭͰ���� */
		if (old_ht[i])								/* ���ǿ�Ͱ�еĴ�����һ */
			put(old_ht[i]->key, old_ht[i]->value);	/* �������µ�Ͱ���� */
	release(old_ht);								/* �ͷ�ԭͰ���顪����������ԭ�ȴ�ŵĴ�������ת�ƣ���ֻ���ͷ�Ͱ���鱾�� */
}

/* ɢ�б�������� */
template <typename K, typename V> 
bool Hashtable<K, V>::put(K k, V v) { 								
	if (ht[probe4Hit(k)])							/* probe4Hit������������Ӧ�÷����λ�ã�r ,��Ԫ�صĿռ仹�����⿪�٣����Դ˴�����ҵ���λ���Ѿ���Ϊ�գ����ȻΪ��ͬԪ�� */
		return false;								/* ��ͬԪ�ز����ظ����� */
	int r = probe4Free(k);							/* Ϊ�´����Ҹ���Ͱ��ֻҪװ�����ӿ��Ƶõ�����Ȼ�ɹ��� */
	ht[r] = new Entry<K, V>(k, v);					/* ���루ע�⣺����ɾ��������踴λ�� */
	++N;			
	if (N * 2 > M) 
		rehash();									/* װ�����Ӹ���50%����ɢ�� */
	return true;
}

/* ɢ�б���������㷨 */
template <typename K, typename V>
V* Hashtable<K, V>::get(K k){
	int r = probe4Hit(k);
	return ht[r] ? &(ht[r]->value) : NULL;			/* ��ֹ������keyֵ��ͬ */
} 

/* ɢ�б����ɾ���㷨 */
template <typename K, typename V>
bool Hashtable<K, V>::remove(K k) { 
	int r = probe4Hit(k); 
	if (!ht[r]) 
		return false;								/* ��Ӧ����������ʱ���޷�ɾ�� */
	release(ht[r]);									/* �����ͷ�Ͱ�д�������������ɾ����ǣ������´������� */
	ht[r] = NULL;
	markAsRemoved(r); 
	N--; 
	return true;
}

#endif
