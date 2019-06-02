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
#define DEFAULT_CACHE_SIZE (8)	//Ĭ��Cache�������

/* �ڵ�ģ���� */
template <typename T_KEY, typename T_VALUE>
class LRUCacheNode {
public:
	T_KEY _key;
	T_VALUE _value;
	LRUCacheNodePosi(T_KEY, T_VALUE) _pred;				/* ǰ�� */
	LRUCacheNodePosi(T_KEY, T_VALUE) _succ;				/* ��� */	

	LRUCacheNode() {}									/* Ĭ�Ϲ��캯�� */
														/* ���캯�� */
	LRUCacheNode(T_KEY key, T_VALUE value, LRUCacheNodePosi(T_KEY, T_VALUE) pred = NULL, LRUCacheNodePosi(T_KEY, T_VALUE) succ = NULL) : \
		_key(key), _value(value), _pred(pred), _succ(succ) {}

	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsPred(T_KEY const& key, T_VALUE const& value)			/* ������ǰ�ڵ�֮ǰ�����½ڵ� */
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrInsertingNode = new LRUCacheNode(key, value, _pred, this);
		_pred->_succ = ptrInsertingNode;
		_pred = ptrInsertingNode;
		return ptrInsertingNode;
	}
	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsSucc(T_KEY const& key, T_VALUE const& value)			/* ���浱ǰ�ڵ�֮������½ڵ� */
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrInsertingNode = new LRUCacheNode(key, value, this, _succ);
		_succ->_pred = ptrInsertingNode;
		_succ = ptrInsertingNode;
		return ptrInsertingNode;
	}
};

/* LRUCacheģ����-ʹ��mapʵ�� */
template <typename T_KEY, typename T_VALUE> 
class LRUCacheUseMap{
private:
	int _count;											//��ǰ�ڵ�����
	int _size;											//��ģ
	LRUCacheNodePosi(T_KEY, T_VALUE) _cachelist;		//�б�
	LRUCacheNodePosi(T_KEY, T_VALUE) _head;				//�б�ͷ
	LRUCacheNodePosi(T_KEY, T_VALUE) _tail;				//�б�β
	map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)> _mp;	//��¼key��map
	void init();										//LRUCacheUseMap��ʼ��
	void moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode);							//���ڵ��ƶ�������ͷ
	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsFirst(T_KEY const& key, T_VALUE const& value);	//�����½ڵ㵽����ͷ
	void removeLastNode(T_KEY &keyName);				//ɾ��β�ڵ�

public:
	LRUCacheUseMap() { init(); }						//���캯��
	void setCacheSize(unsigned int size);				//���û���ռ��С

	/******************************************************************
	* ��ȡ����ֵ
	* ʱ�临�Ӷ�					��O(logn) = O(logn)��map���Ҹ��Ӷ� + O(1)��list�ƶ����нڵ㵽�б�ͷ�ĸ��Ӷ�
	******************************************************************/
	T_VALUE get(T_KEY key);								

	/******************************************************************
	* ���û���ֵ
	* ʱ�临�Ӷȣ�
	*	�Ѵ��ڸ�key					��O(logn) = O(logn)��map���Ҹ��Ӷ� + O(1)��list�ƶ����нڵ㵽�б�ͷ�ĸ��Ӷ�
	*	�����ڸ�key�Ҳ���Ҫ��̭		��O(logn) = O(logn)��map���Ҹ��Ӷ� + O(logn)��map���븴�Ӷ� + O(1)��list���븴�Ӷȣ����뵽�б�ͷ��
	*	û��������Ҫ��̭			��O(logn) = O(logn)��map���ҡ����븴�Ӷ� + O(logn)��mapɾ�����Ӷ�  + O(1)��listɾ�������븴�Ӷȣ����뵽�б�ͷ��
	******************************************************************/
	void set(T_KEY key, T_VALUE value);		

	void printLRUCacheList();							//��ӡ�������
};

/* ���ڵ��ƶ�������ͷ */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseMap<T_KEY, T_VALUE>::moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode)
{	
	if (ptrNode == _head->_succ) 
		return;											//�Ѿ�������ͷ������Ҫ�ƶ�

	ptrNode->_pred->_succ = ptrNode->_succ;				//��������ժ���ڵ�
	ptrNode->_succ->_pred = ptrNode->_pred;

	_head->_succ = ptrNode;								//���뵽�����е�ͷ���
	ptrNode->_pred = _head;
	ptrNode->_succ = _cachelist;
	_cachelist->_pred = ptrNode;
	_cachelist = ptrNode;
}

/* �½��ڵ㲢���뵽����ͷ */
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

/* ɾ��β�ڵ�*/
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

 /* ���û���ռ��С */
 template <typename T_KEY, typename T_VALUE>
 void LRUCacheUseMap<T_KEY, T_VALUE>::setCacheSize(unsigned int size)
 {
	 _size = size;
 }

/* ��ȡ����key�Ļ���ֵ */
template <typename T_KEY, typename T_VALUE>
T_VALUE LRUCacheUseMap<T_KEY, T_VALUE>::get(T_KEY key)
{
	if (NULL == _cachelist)			/* ���ض���Ϊ�գ��򷵻� */
	{
		return -1;
	}
	typedef map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)>::iterator it_map;
	it_map it = _mp.find(key);
	if (_mp.end() == it)			/* �����Cache�в����ڸ�key���򷵻�-1 */
	{
		return -1;
	}
	else 
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
		moveNodeFirst(ptrHit);		/* ���ڵ���������ͷ�� */
		return _cachelist->_value;	/* ��������ֵ */
	}
}

/* ��������key�Ļ���ֵ */
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
		if (_mp.end() == it)				/* û������ */
		{
			if (_count == _size)			/* Cache���� */
			{
				T_KEY keyName;
				removeLastNode(keyName);	/* ɾ��β�ڵ� */
				_mp.erase(keyName);			/* ��map��ɾ�� */
			}

			/* �½��ڵ㲢��������ͷ */
			insertAsFirst(key, value);
			_cachelist = _head->_succ;
			_mp[key] = _cachelist;
		}
		else								/* ���� */
		{
			LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
			ptrHit->_value = value;
			moveNodeFirst(ptrHit);			/* ���ڵ���������ͷ�� */
		}
	}
}

/* ��ӡ������� */
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

/* LRUCacheģ����-ʹ�ù�ϣ��ʵ�֣�std::unordered_map�ײ����hashtableʵ�֣� */
template <typename T_KEY, typename T_VALUE>
class LRUCacheUseHashtable {
private:
	int _count;											//��ǰ�ڵ�����
	int _size;											//��ģ
	LRUCacheNodePosi(T_KEY, T_VALUE) _cachelist;		//�б�
	LRUCacheNodePosi(T_KEY, T_VALUE) _head;				//�б�ͷ
	LRUCacheNodePosi(T_KEY, T_VALUE) _tail;				//�б�β
	unordered_map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)> _mp;	//��¼key��map
	void init();										//LRUCacheUseHashtable��ʼ��
	void moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode);							//���ڵ��ƶ�������ͷ
	LRUCacheNodePosi(T_KEY, T_VALUE) insertAsFirst(T_KEY const& key, T_VALUE const& value);	//�����½ڵ㵽����ͷ
	void removeLastNode(T_KEY &keyName);				//ɾ��β�ڵ�

public:
	LRUCacheUseHashtable() { init(); }					//���캯��
	void setCacheSize(unsigned int size);				//���û���ռ��С

	/******************************************************************
	* ��ȡ����ֵ
	* ʱ�临�Ӷ�					��O(1) = O(1)��hashtable���Ҹ��Ӷ� + O(1)��list�ƶ����нڵ㵽�б�ͷ�ĸ��Ӷ�
	******************************************************************/
	T_VALUE get(T_KEY key);

	/******************************************************************
	* ���û���ֵ
	* ʱ�临�Ӷȣ�
	*	�Ѵ��ڸ�key					��O(1) = O(1)��hashtable���Ҹ��Ӷ� + O(1)��list�ƶ����нڵ㵽�б�ͷ�ĸ��Ӷ�
	*	�����ڸ�key�Ҳ���Ҫ��̭		��O(1) = O(1)��hashtable���Ҹ��Ӷ� + O(1)��hashtable���븴�Ӷ�  + O(1)��list���븴�Ӷȣ����뵽�б�ͷ��
	*	û��������Ҫ��̭			��O(1) = O(1)��hashtable���ҡ����븴�Ӷ� + O(1)��hashtableɾ�����Ӷ�  + O(1)��listɾ�������븴�Ӷȣ����뵽�б�ͷ��
	******************************************************************/
	void set(T_KEY key, T_VALUE value);
	void printLRUCacheList();							//��ӡ�������
};


/* ���ڵ��ƶ�������ͷ */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::moveNodeFirst(LRUCacheNodePosi(T_KEY, T_VALUE) &ptrNode)
{
	if (ptrNode == _head->_succ)
		return;											//�Ѿ�������ͷ������Ҫ�ƶ�

	ptrNode->_pred->_succ = ptrNode->_succ;				//��������ժ���ڵ�
	ptrNode->_succ->_pred = ptrNode->_pred;

	_head->_succ = ptrNode;								//���뵽�����е�ͷ���
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

/* ɾ��β�ڵ�*/
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

/* ���û���ռ��С */
template <typename T_KEY, typename T_VALUE>
void LRUCacheUseHashtable<T_KEY, T_VALUE>::setCacheSize(unsigned int size)
{
	_size = size;
}
/* ��ȡ����key�Ļ���ֵ */
template <typename T_KEY, typename T_VALUE>
T_VALUE LRUCacheUseHashtable<T_KEY, T_VALUE>::get(T_KEY key)
{
	if (NULL == _cachelist)			/* ���ض���Ϊ�գ��򷵻� */
	{
		return -1;
	}
	typedef unordered_map<T_KEY, LRUCacheNodePosi(T_KEY, T_VALUE)>::iterator it_unorderedmap;
	it_unorderedmap it = _mp.find(key);
	if (_mp.end() == it)			/* �����Cache�в����ڸ�key���򷵻�-1 */
	{
		return -1;
	}
	else
	{
		LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
		moveNodeFirst(ptrHit);		/* ���ڵ���������ͷ�� */
		return _cachelist->_value;	/* ��������ֵ */
	}
}

/* ��������key�Ļ���ֵ */
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
		if (_mp.end() == it)				/* û������ */
		{
			if (_count == _size)			/* Cache���� */
			{
				T_KEY keyName;
				removeLastNode(keyName);	/* ɾ��β�ڵ� */
				_mp.erase(keyName);			/* ��map��ɾ�� */
			}

			/* �½��ڵ㲢��������ͷ */
			insertAsFirst(key, value);
			_cachelist = _head->_succ;
			_mp[key] = _cachelist;
		}
		else								/* ���� */
		{
			LRUCacheNodePosi(T_KEY, T_VALUE) ptrHit = it->second;
			ptrHit->_value = value;
			moveNodeFirst(ptrHit);			/* ���ڵ���������ͷ�� */
		}
	}
}

/* ��ӡ������� */
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
