/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_HASHTABLE_H__
#define PRINT_HASHTABLE_H__

/******************************************************************************************
 * Hashtable
 ******************************************************************************************/
template <typename K, typename V> //e、value
void UniPrint::p ( Hashtable<K, V>& ht ) { //引用
   printf ( "%s[%d]*%d/%d:\n", typeid ( ht ).name(), &ht, ht.N, ht.M ); //基本信息
   for ( int i = 0; i < ht.M; i++ ) //输出桶编号
      printf ( "  %4d  ", i );
   printf ( "\n" );
   for ( int i = 0; i < ht.M; i++ ) //输出所有元素
      if ( ht.ht[i] ) printf ( "-<%04d>-", ht.ht[i]->key ); //演示用，仅适用于int
      else if ( ht.lazyRemoval->test ( i ) ) printf ( "-<xxxx>-" );
      else printf ( "--------" );
   printf ( "\n" );
   for ( int i = 0; i < ht.M; i++ ) //输出所有元素
      if ( ht.ht[i] ) printf ( "    %c   ", ht.ht[i]->value ); //演示用，仅适用于char
//      if (ht.ht[i]) printf("%8s", ht.ht[i]->value); //针对Huffman编码中使用的散列表
      else if ( ht.lazyRemoval->test ( i ) ) printf ( " <xxxx> " );
      else printf ( "        " );
   printf ( "\n" );
}

#endif // !PRINT_HASHTABLE_H__