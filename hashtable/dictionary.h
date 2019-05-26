/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef DICTIONARY_H__
#define DICTIONARY_H__

 /* �ʵ�Dictionaryģ���� */
template <typename K, typename V> 
struct Dictionary { 
   virtual int size() const = 0;		/* ��ǰ�������� */
   virtual bool put ( K, V ) = 0;		/* �����������ֹ��ͬ����ʱ����ʧ�ܣ� */
   virtual V* get ( K k ) = 0;			/* ��ȡ���� */
   virtual bool remove ( K k ) = 0;		/* ɾ������ */
};

#endif