/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn¡¢add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_ENTRY_H__
#define PRINT_ENTRY_H__

/******************************************************************************************
 * Entry
 ******************************************************************************************/
template <typename K, typename V>
void UniPrint::p ( Entry<K, V>& e ) //ÒýÓÃ
{  printf ( "-<" ); print ( e.key ); printf ( ":" ); print ( e.value ); printf ( ">-" );  }

#endif