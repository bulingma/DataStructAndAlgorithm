/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef ENTRY_H__
#define ENTRY_H__

 /* ����ģ���� */
template <typename K, typename V> struct Entry {
   K key;																	 /* �ؼ��롢��ֵ */
   V value; 
   Entry ( K k = K(), V v = V() ) : key ( k ), value ( v ) {};				 /* Ĭ�Ϲ��캯�� */
   Entry ( Entry<K, V> const& e ) : key ( e.key ), value ( e.value ) {};	 /* ���ڿ�¡�Ĺ��캯�� */
   bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }			 /* �Ƚ�����С�� */
   bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }			 /* �Ƚ��������� */
   bool operator== ( Entry<K, V> const& e ) { return key == e.key; }		 /* �е��������� */
   bool operator!= ( Entry<K, V> const& e ) { return key != e.key; }		 /* �е����������� */
};  /* �����ڱȽ������е������Ӵ����󣬲����ϸ����ִ��������Ӧ�Ĺؼ��� */

#endif