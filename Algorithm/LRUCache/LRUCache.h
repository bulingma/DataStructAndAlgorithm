/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Author: Yuguang Ma 
* All rights reserved.
******************************************************************************************/

#ifndef LRUCACHE_H__ 
#define LRUCACHE_H__

#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

#define LRUCacheNodePosi(T_KEY, T_VALUE) LRUCacheNode<T_KEY, T_VALUE>*
#define DEFAULT_CACHE_SIZE (8)	//默认Cache缓存个数

/* 节点模板类 */
template <typename T_KEY, typename T_VALUE>
class LRUCacheNode {
public:
	T_KEY _key;
	T_VALUE _value;
	LRUCacheNodePosi(T_KEY, T_VALUE) _pred;				/* 前驱 */
	LRUCacheNodePosi(T_KEY, T_VALUE) _succ;				/* 后继 */	

	LRUCacheNode() {}									/* 默认构造函数 */
														/* 构造函数 */
	LRUCacheNode(T_KEY key, T_VALUE value, LRUCacheNodePosi(T_KEY, T_VALUE) pred = NULL, LRUCacheNodePosi(T_KEY, T_VALUE) succ = NULL) : \
		_key(key), _value(value), _pred(pred), _succ(succ) {}

	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsPred(T_KEY const& key, T_VALUE const& value)			/* 紧靠当前节点之前插入新节点 */
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrInsertingNode = new LRUCacheNode(key, value, _pred, this);
		_pred->_succ = ptrInsertingNode;
		_pred = ptrInsertingNode;
		return ptrInsertingNode;
	}
	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsSucc(T_KEY const& key, T_VALUE const& value)			/* 紧随当前节点之后插入新节点 */
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrInsertingNode = new LRUCacheNode(key, value, this, _succ);
		_succ->_pred = ptrInsertingNode;
		_succ = ptrInsertingNode;
		return ptrInsertingNode;
	}
};

/* LRUCache模板类-使用map实现 */
template <typename T_KEY, typename T_VALUE> 
class LRUCacheUseMap{
private:
	int _count;											//当前节点总数
	int _size;											//规模
	LRUCacheNodePosi(T_KEY, T_VALUE) _cachelist;		//列表
	LRUCacheNodePosi(T_KEY, T_VALUE) _head;				//列表头
	LRUCacheNodePosi(T_KEY, T_VALUE) _tail;				//列表尾
	map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)> _mp;	//记录key的map
	void init();										//LRUCacheUseMap初始化
	void moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode);							//将节点移动到链表头
	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsFirst(T_KEY const& key, T_VALUE const& value);	//插入新节点到链表头
	void removeLastNode(T_KEY &keyName);				//删除尾节点

public:
	LRUCacheUseMap() { init(); }						//构造函数
	void setCacheSize(unsigned int size);				//设置缓存空间大小

	/******************************************************************
	* 获取缓存值
	* 时间复杂度					：O(logn) = O(logn)的map查找复杂度 + O(1)的list移动命中节点到列表头的复杂度
	******************************************************************/
	T_VALUE get(T_KEY key);								

	/******************************************************************
	* 设置缓存值
	* 时间复杂度：
	*	已存在该key					：O(logn) = O(logn)的map查找复杂度 + O(1)的list移动命中节点到列表头的复杂度
	*	不存在该key且不需要淘汰		：O(logn) = O(logn)的map查找复杂度 + O(logn)的map插入复杂度 + O(1)的list插入复杂度（插入到列表头）
	*	没命中且需要淘汰			：O(logn) = O(logn)的map查找、插入复杂度 + O(logn)的map删除复杂度  + O(1)的list删除、插入复杂度（插入到列表头）
	******************************************************************/
	void set(T_KEY key, T_VALUE value);		

	void printLRUCacheList();							//打印输出函数
};

/* 将节点移动到链表头 */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseMap<T_KEY, T_VALUE>::moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode)
{	
	if (ptrNode == _head->_succ) 
		return;											//已经在链表头，则不需要移动

	ptrNode->_pred->_succ = ptrNode->_succ;				//从链表中摘除节点
	ptrNode->_succ->_pred = ptrNode->_pred;

	_head->_succ = ptrNode;								//插入到链表中的头结点
	ptrNode->_pred = _head;
	ptrNode->_succ = _cachelist;
	_cachelist->_pred = ptrNode;
	_cachelist = ptrNode;
}

/* 新建节点并插入到链表头 */
template<typename T_KEY, typename T_VALUE>
LRUCacheNodePosi(T_KEY, T_VALUE) LRUCacheUseMap<T_KEY, T_VALUE>::insertAsFirst(T_KEY const & key, T_VALUE const & value)
{
	_count++;
	return _head->insertAsSucc(key, value);
}

template <typename T_KEY, typename T_VALUE>
void LRUCacheUseMap<T_KEY, T_VALUE>::init()
{
	_size = DEFAULT_CACHE_SIZE;
	_count = 0;
	_cachelist = NULL;
	_head = new LRUCacheNode< T_KEY, T_VALUE>;
	_tail = new LRUCacheNode< T_KEY, T_VALUE>;
	_head->_pred = NULL;
	_tail->_succ = NULL;
	_head->_succ = _tail;
	_tail->_pred = _head;
}

/* 删除尾节点*/
template <typename T_KEY, typename T_VALUE>
 void LRUCacheUseMap<T_KEY, T_VALUE>::removeLastNode(T_KEY &keyName)
{
	LRUCacheNodePosi(T_KEY, T_VALUE) ptrDelNode = _tail->_pred;
	LRUCacheNodePosi(T_KEY, T_VALUE) ptrDelNodePre = ptrDelNode->_pred;
	ptrDelNodePre->_succ = _tail;
	_tail->_pred = ptrDelNodePre;
	_count--;
	keyName = ptrDelNode->_key;
	delete ptrDelNode;
	return;
}

 /* 设置缓存空间大小 */
 template <typename T_KEY, typename T_VALUE>
 void LRUCacheUseMap<T_KEY, T_VALUE>::setCacheSize(unsigned int size)
 {
	 _size = size;
 }

/* 获取输入key的缓存值 */
template <typename T_KEY, typename T_VALUE>
T_VALUE LRUCacheUseMap<T_KEY, T_VALUE>::get(T_KEY key)
{
	if (NULL == _cachelist)			/* 本地队列为空，则返回 */
	{
		return -1;
	}
	typedef map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)>::iterator it_map;
	it_map it = _mp.find(key);
	if (_mp.end() == it)			/* 如果在Cache中不存在该key，则返回-1 */
	{
		return -1;
	}
	else 
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
		moveNodeFirst(ptrHit);		/* 将节点置于链表头部 */
		return _cachelist->_value;	/* 返回命中值 */
	}
}

/* 设置输入key的缓存值 */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseMap<T_KEY, T_VALUE>::set(T_KEY key, T_VALUE value)
{
	if (NULL == _cachelist)
	{
		insertAsFirst(key, value);
		_cachelist = _head->_succ;
		_mp[key] = _cachelist;
	}
	else
	{
		typedef map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)>::iterator it_map;
		it_map it = _mp.find(key);
		if (_mp.end() == it)				/* 没有命中 */
		{
			if (_count == _size)			/* Cache已满 */
			{
				T_KEY keyName;
				removeLastNode(keyName);	/* 删除尾节点 */
				_mp.erase(keyName);			/* 在map中删除 */
			}

			/* 新建节点并插入链表头 */
			insertAsFirst(key, value);
			_cachelist = _head->_succ;
			_mp[key] = _cachelist;
		}
		else								/* 命中 */
		{
			LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
			ptrHit->_value = value;
			moveNodeFirst(ptrHit);			/* 将节点置于链表头部 */
		}
	}
}

/* 打印输出函数 */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseMap<T_KEY, T_VALUE>::printLRUCacheList()
{
	LRUCacheNodePosi(T_KEY, T_VALUE) p = _cachelist;
	int index = 0;
	while ((p != _tail) && (index < _count))
	{
		cout << "index = "<< index << ", key = " << p->_key << ", value = " << p->_value << endl;
		p = p->_succ;
		index++;
	}
}

/* LRUCache模板类-使用哈希表实现（std::unordered_map底层采用hashtable实现） */
template <typename T_KEY, typename T_VALUE>
class LRUCacheUseHashtable {
private:
	int _count;											//当前节点总数
	int _size;											//规模
	LRUCacheNodePosi(T_KEY, T_VALUE) _cachelist;		//列表
	LRUCacheNodePosi(T_KEY, T_VALUE) _head;				//列表头
	LRUCacheNodePosi(T_KEY, T_VALUE) _tail;				//列表尾
	unordered_map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)> _mp;	//记录key的map
	void init();										//LRUCacheUseHashtable初始化
	void moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode);							//将节点移动到链表头
	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsFirst(T_KEY const& key, T_VALUE const& value);	//插入新节点到链表头
	void removeLastNode(T_KEY &keyName);				//删除尾节点

public:
	LRUCacheUseHashtable() { init(); }					//构造函数
	void setCacheSize(unsigned int size);				//设置缓存空间大小

	/******************************************************************
	* 获取缓存值
	* 时间复杂度					：O(1) = O(1)的hashtable查找复杂度 + O(1)的list移动命中节点到列表头的复杂度
	******************************************************************/
	T_VALUE get(T_KEY key);

	/******************************************************************
	* 设置缓存值
	* 时间复杂度：
	*	已存在该key					：O(1) = O(1)的hashtable查找复杂度 + O(1)的list移动命中节点到列表头的复杂度
	*	不存在该key且不需要淘汰		：O(1) = O(1)的hashtable查找复杂度 + O(1)的hashtable插入复杂度  + O(1)的list插入复杂度（插入到列表头）
	*	没命中且需要淘汰			：O(1) = O(1)的hashtable查找、插入复杂度 + O(1)的hashtable删除复杂度  + O(1)的list删除、插入复杂度（插入到列表头）
	******************************************************************/
	void set(T_KEY key, T_VALUE value);
	void printLRUCacheList();							//打印输出函数
};


/* 将节点移动到链表头 */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode)
{
	if (ptrNode == _head->_succ)
		return;											//已经在链表头，则不需要移动

	ptrNode->_pred->_succ = ptrNode->_succ;				//从链表中摘除节点
	ptrNode->_succ->_pred = ptrNode->_pred;

	_head->_succ = ptrNode;								//插入到链表中的头结点
	ptrNode->_pred = _head;
	ptrNode->_succ = _cachelist;
	_cachelist->_pred = ptrNode;
	_cachelist = ptrNode;
}

template<typename T_KEY, typename T_VALUE>
LRUCacheNodePosi(T_KEY, T_VALUE) LRUCacheUseHashtable<T_KEY, T_VALUE>::insertAsFirst(T_KEY const & key, T_VALUE const & value)
{
	_count++;
	return _head->insertAsSucc(key, value);
}

template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::init()
{
	_size = DEFAULT_CACHE_SIZE;
	_count = 0;
	_cachelist = NULL;
	_head = new LRUCacheNode< T_KEY, T_VALUE>;
	_tail = new LRUCacheNode< T_KEY, T_VALUE>;
	_head->_pred = NULL;
	_tail->_succ = NULL;
	_head->_succ = _tail;
	_tail->_pred = _head;
}

/* 删除尾节点*/
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::removeLastNode(T_KEY &keyName)
{
	LRUCacheNodePosi(T_KEY, T_VALUE) ptrDelNode = _tail->_pred;
	LRUCacheNodePosi(T_KEY, T_VALUE) ptrDelNodePre = ptrDelNode->_pred;
	ptrDelNodePre->_succ = _tail;
	_tail->_pred = ptrDelNodePre;
	_count--;
	keyName = ptrDelNode->_key;
	delete ptrDelNode;
	return;
}

/* 设置缓存空间大小 */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::setCacheSize(unsigned int size)
{
	_size = size;
}
/* 获取输入key的缓存值 */
template <typename T_KEY, typename T_VALUE>
T_VALUE LRUCacheUseHashtable<T_KEY, T_VALUE>::get(T_KEY key)
{
	if (NULL == _cachelist)			/* 本地队列为空，则返回 */
	{
		return -1;
	}
	typedef unordered_map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)>::iterator it_unorderedmap;
	it_unorderedmap it = _mp.find(key);
	if (_mp.end() == it)			/* 如果在Cache中不存在该key，则返回-1 */
	{
		return -1;
	}
	else
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
		moveNodeFirst(ptrHit);		/* 将节点置于链表头部 */
		return _cachelist->_value;	/* 返回命中值 */
	}
}

/* 设置输入key的缓存值 */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::set(T_KEY key, T_VALUE value)
{
	if (NULL == _cachelist)
	{
		insertAsFirst(key, value);
		_cachelist = _head->_succ;
		_mp[key] = _cachelist;
	}
	else
	{
		typedef unordered_map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)>::iterator it_unorderedmap;
		it_unorderedmap it = _mp.find(key);
		if (_mp.end() == it)				/* 没有命中 */
		{
			if (_count == _size)			/* Cache已满 */
			{
				T_KEY keyName;
				removeLastNode(keyName);	/* 删除尾节点 */
				_mp.erase(keyName);			/* 在map中删除 */
			}

			/* 新建节点并插入链表头 */
			insertAsFirst(key, value);
			_cachelist = _head->_succ;
			_mp[key] = _cachelist;
		}
		else								/* 命中 */
		{
			LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
			ptrHit->_value = value;
			moveNodeFirst(ptrHit);			/* 将节点置于链表头部 */
		}
	}
}

/* 打印输出函数 */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::printLRUCacheList()
{
	LRUCacheNodePosi(T_KEY, T_VALUE) p = _cachelist;
	int index = 0;
	while ((p != _tail) && (index < _count))
	{
		cout << "index = " << index << ", key = " << p->_key << ", value = " << p->_value << endl;
		p = p->_succ;
		index++;
	}
}

#endif 
