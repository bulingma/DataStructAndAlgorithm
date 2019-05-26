/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_H__
#define PRINT_H__

#include <stdio.h> /* ����C���ϸ���������ʽ */

#if 0
#include "../huffman/huffChar.h" /* Huffman���ַ� */
#endif
#include "../BinTree/BinTree.h"						/* ������ */
#include "../BST/BST.h"								/* ���������� */
#include "../Splay/Splay.h"							/* ��չ�� */
#include "../AVL/AVL.h"								/* AVL�� */
#include "../redBlack/RedBlack.h"					/* ����� */
#include "../BTree/BTree.h"							/* ������������B-���� */
#include "../Hashtable/Entry.h"						/* ���� */
#include "../Hashtable/Hashtable.h"					/* ɢ�б� */
#include "../graphMatrix/Graph.h"					/* ͼ */
#include "../graphMatrix/GraphMatrix.h"				/* �����ڽӾ���ʵ�ֵ�ͼ */

/******************************************************************************************
 * ����Ԫ�ء����ݽṹͨ������ӿ�
 ******************************************************************************************/
template <typename T> static void print ( T* x ) {  x ? print ( *x ) : (void)printf ( " <NULL>" );  }
template <typename T> static void print ( T& x ) {  UniPrint::p ( x );  }
template <typename T> static void print ( const T& x ) {  UniPrint::p ( x );  }		/* for Stack */
static void print ( char* x ) {  printf ( " %s", x ? x : "<NULL>" );  }				/* �ַ����ر��� */
static void print ( const char* x ) {  printf ( " %s", x ? x : "<NULL>" );  }		/* �ַ����ر��� */

class UniPrint {
public:
   static void p ( int );
   static void p ( float );
   static void p ( double );
   static void p ( char );

#if 0
   static void p ( HuffChar& );														/* Huffman�������ַ� */
#endif
   static void p ( VStatus );														/* ͼ�����״̬ */
   static void p ( EType );															/* ͼ�ߵ����� */

   template <typename K, typename V> static void p ( Entry<K, V>& );				/* Entry */
   template <typename T> static void p ( BinNode<T>& );								/* BinTree�ڵ� */
   template <typename T> static void p ( BinTree<T>& );								/* ������ */
   template <typename T> static void p(BTree<T>&);									/* B-�� */
   template <typename T> static void p(BST<T>&);									/* BST */
   template <typename T> static void p(Splay<T>&);									/* Splay */
   template <typename T> static void p(AVL<T>&);									/* AVL */
   template <typename T> static void p(RedBlack<T>&);								/* RedBlack */
   template <typename K, typename V> static void p(Hashtable<K, V>&);				/* Hashtable */
   template <typename Tv, typename Te> static void p(GraphMatrix<Tv, Te>&);			/* Graph */

   template <typename T> static void p ( T& );										/* �������б��֧��traverse()�������������Խṹ */
   template <typename T> static void p ( T* s )										/* ����ָ�� */
   {  s ? p ( *s ) : print ( "<NULL>" ); }											/* ͳһתΪ���� */
}; /* UniPrint */


#include "Print_BinNode.h"
#include "Print_BinTree.h"
#include "Print_BTree.h"
#include "Print_Entry.h"
#include "Print_Hashtable.h"
#include "Print_graphmatrix.h"
#include "Print_traversable.h"

#endif // !PRINT_H__ 