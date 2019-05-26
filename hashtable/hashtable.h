/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef HASHTABLE_H__
#define HASHTABLE_H__

#include "dictionary.h"			/* 引入词典ADT */
#include "../bitmap/bitmap.h"	/* 引入位图 */
#include "../prime/primeNLT.h"	/* 引入素数 */
#include "hashtable_hashcode.h"	/* 引入散列函数 */

/* 符合Dictionary接口的Hashtable模板类 */
template <typename K, typename V>					/* key、value */
class Hashtable : public Dictionary<K, V> { 
   /*DSA*/friend class UniPrint;
private:
   Entry<K, V>** ht;								/* 桶数组，存放词条指针 */
   int M;											/* 桶数组容量 */
   int N;											/* 词条数量 */
   Bitmap* lazyRemoval;								/* 懒惰删除标记 */
#define lazilyRemoved(x)  (lazyRemoval->test(x))	
#define markAsRemoved(x)  (lazyRemoval->set(x))
protected:
   int probe4Hit ( const K& k );					/* 沿关键码k对应的查找链，找到词条匹配的桶 */
   int probe4Free ( const K& k );					/* 沿关键码k对应的查找链，找到首个可用空桶 */
   void rehash();									/* 重散列算法：扩充桶数组，保证装填因子在警戒线以下 */
public:
   Hashtable ( int c = 5 );							/* 创建一个容量不小于c的散列表（为测试暂时选用较小的默认值） */
   ~Hashtable();									/* 释放桶数组及其中各（非空）元素所指向的词条 */
   int size() const { return N; }					/* 当前的词条数目 */
   bool put ( K, V );								/* 插入（禁止雷同词条，故可能失败） */
   V* get ( K k );									/* 读取 */
   bool remove ( K k );								/* 删除 */
};

/* 创建散列表，容量为不小于c的素数M */
template <typename K, typename V> 
Hashtable<K, V>::Hashtable(int c) { 
													/* 不小于c的素数M */
	char * pcExternalFile = new char[64];
	strncpy(pcExternalFile, "../_input/prime-1048576-bitmap.txt", 64);
	M = primeNLT(c, 1048576, pcExternalFile);
	//M = primeNLT(c, 1048576, "../_input/prime-1048576-bitmap.txt"); 
	N = 0; 
	ht = new Entry<K, V>*[M];						/* 开辟桶数组（还需核对申请成功），初始装填因子为N/M = 0% */
	memset(ht, 0, sizeof(Entry<K, V>*) *M);			/* 初始化各桶 */
	lazyRemoval = new Bitmap(M);					/* 懒惰删除标记比特图 */
	//*DSA*/printf("A bucket array has been created with capacity = %d\n\n", M);
}

/* 析构前释放桶数组及非空词条 */
template <typename K, typename V> 
Hashtable<K, V>::~Hashtable() { 
	for (int i = 0; i < M; i++)						/* 逐一检查各桶 */
		if (ht[i]) release(ht[i]);					/* 释放非空的桶 */
	release(ht);									/* 释放桶数组 */
	release(lazyRemoval);							/* 释放懒惰删除标记 */
}

/******************************************************************************************
* 沿关键码k对应的查找链，找到与之匹配的桶（供查找和删除词条时调用）
* 试探策略多种多样，可灵活选取；这里仅以线性试探策略为例
******************************************************************************************/
template <typename K, typename V> 
int Hashtable<K, V>::probe4Hit(const K& k) {
	int r = hashCode(k) % M;						/* 从起始桶（按除余法确定）出发 */
	//*DSA*/printf(" ->%d", r);
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r)))
		r = (r + 1) % M;							/* 沿查找链线性试探：跳过所有冲突的桶，以及带懒惰删除标记的桶 */
		//*DSA*/printf(" ->%d", r);
		//*DSA*/printf("\n");
	return r;										/* 调用者根据ht[r]是否为空，即可判断查找是否成功，ht[r]为空：查找成功，ht[r]非空：查找失败（key雷同元素） */
}

/******************************************************************************************
* 沿关键码k对应的查找链，找到首个可用空桶（仅供插入词条时调用）
* 试探策略多种多样，可灵活选取；这里仅以线性试探策略为例
******************************************************************************************/
template <typename K, typename V> 
int Hashtable<K, V>::probe4Free(const K& k) {
	int r = hashCode(k) % M;						/* 从起始桶（按除余法确定）出发 */
	//*DSA*/printf(" ->%d", r);						/* 首个试探的桶单元地址 */*
	while (ht[r])									/* 沿查找链逐桶试探，直到首个空桶（无论是否带有懒惰删除标记） */
		r = (r + 1) % M;				
	//*DSA*/   while (ht[r]) { r = (r+1) % M; printf(" ->%d", r); } printf("\n");
	return r;										/* 为保证空桶总能找到，装填因子及散列表长需要合理设置 */
}

/******************************************************************************************
* 重散列算法：装填因子过大时，采取“逐一取出再插入”的朴素策略，对桶数组扩容
* 不可简单地（通过memcpy()）将原桶数组复制到新桶数组（比如前端），否则存在两个问题：
* 1）会继承原有冲突；2）可能导致查找链在后端断裂——即便为所有扩充桶设置懒惰删除标志也无济于事
******************************************************************************************/
template <typename K, typename V>
void Hashtable<K, V>::rehash() {
	int old_capacity = M;
	Entry<K, V>** old_ht = ht;
	/* 容量至少加倍 */
	char * pcExternalFile = new char[64];
	strncpy(pcExternalFile, "../_input/prime-1048576-bitmap.txt", 64);
	M = primeNLT(2 * M, 1048576, pcExternalFile);
	//M = primeNLT(2 * M, 1048576, "../_input/prime-1048576-bitmap.txt");
	N = 0;
	ht = new Entry<K, V>*[M];
	memset(ht, 0, sizeof(Entry<K, V>*) * M);		/* 新桶数组 */
	release(lazyRemoval);
	lazyRemoval = new Bitmap(M);					/* 新开懒惰删除标记比特图 */
													//*DSA*/printf("A bucket array has been created with capacity = %d\n\n", M); */
	for (int i = 0; i < old_capacity; i++)			/* 扫描原桶数组 */
		if (old_ht[i])								/* 将非空桶中的词条逐一 */
			put(old_ht[i]->key, old_ht[i]->value);	/* 插入至新的桶数组 */
	release(old_ht);								/* 释放原桶数组——由于其中原先存放的词条均已转移，故只需释放桶数组本身 */
}

/* 散列表词条插入 */
template <typename K, typename V> 
bool Hashtable<K, V>::put(K k, V v) { 								
	if (ht[probe4Hit(k)])							/* probe4Hit函数仅仅给出应该放入的位置：r ,新元素的空间还需另外开辟，所以此处如果找到的位置已经不为空，则必然为雷同元素 */
		return false;								/* 雷同元素不必重复插入 */
	int r = probe4Free(k);							/* 为新词条找个空桶（只要装填因子控制得当，必然成功） */
	ht[r] = new Entry<K, V>(k, v);					/* 插入（注意：懒惰删除标记无需复位） */
	++N;			
	if (N * 2 > M) 
		rehash();									/* 装填因子高于50%后重散列 */
	return true;
}

/* 散列表词条查找算法 */
template <typename K, typename V>
V* Hashtable<K, V>::get(K k){
	int r = probe4Hit(k);
	return ht[r] ? &(ht[r]->value) : NULL;			/* 禁止词条的key值雷同 */
} 

/* 散列表词条删除算法 */
template <typename K, typename V>
bool Hashtable<K, V>::remove(K k) { 
	int r = probe4Hit(k); 
	if (!ht[r]) 
		return false;								/* 对应词条不存在时，无法删除 */
	release(ht[r]);									/* 否则释放桶中词条，设置懒惰删除标记，并更新词条总数 */
	ht[r] = NULL;
	markAsRemoved(r); 
	N--; 
	return true;
}

#endif
