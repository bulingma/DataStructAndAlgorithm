/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_HASHTABLE_H__
#define PRINT_HASHTABLE_H__

/******************************************************************************************
 * Hashtable
 ******************************************************************************************/
template <typename K, typename V> //e��value
void UniPrint::p ( Hashtable<K, V>& ht ) { //����
   printf ( "%s[%d]*%d/%d:\n", typeid ( ht ).name(), &ht, ht.N, ht.M ); //������Ϣ
   for ( int i = 0; i < ht.M; i++ ) //���Ͱ���
      printf ( "  %4d  ", i );
   printf ( "\n" );
   for ( int i = 0; i < ht.M; i++ ) //�������Ԫ��
      if ( ht.ht[i] ) printf ( "-<%04d>-", ht.ht[i]->key ); //��ʾ�ã���������int
      else if ( ht.lazyRemoval->test ( i ) ) printf ( "-<xxxx>-" );
      else printf ( "--------" );
   printf ( "\n" );
   for ( int i = 0; i < ht.M; i++ ) //�������Ԫ��
      if ( ht.ht[i] ) printf ( "    %c   ", ht.ht[i]->value ); //��ʾ�ã���������char
//      if (ht.ht[i]) printf("%8s", ht.ht[i]->value); //���Huffman������ʹ�õ�ɢ�б�
      else if ( ht.lazyRemoval->test ( i ) ) printf ( " <xxxx> " );
      else printf ( "        " );
   printf ( "\n" );
}

#endif // !PRINT_HASHTABLE_H__