/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef ENTRY_H__
#define ENTRY_H__

 /* 词条模板类 */
template <typename K, typename V> struct Entry {
   K key;																	 /* 关键码、数值 */
   V value; 
   Entry ( K k = K(), V v = V() ) : key ( k ), value ( v ) {};				 /* 默认构造函数 */
   Entry ( Entry<K, V> const& e ) : key ( e.key ), value ( e.value ) {};	 /* 基于克隆的构造函数 */
   bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }			 /* 比较器：小于 */
   bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }			 /* 比较器：大于 */
   bool operator== ( Entry<K, V> const& e ) { return key == e.key; }		 /* 判等器：等于 */
   bool operator!= ( Entry<K, V> const& e ) { return key != e.key; }		 /* 判等器：不等于 */
};  /* 得益于比较器和判等器，从此往后，不必严格区分词条及其对应的关键码 */

#endif