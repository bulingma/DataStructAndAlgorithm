/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_H__
#define PRINT_H__

#include <stdio.h> /* 采用C风格精细控制输出格式 */

#if 0
#include "../huffman/huffChar.h" /* Huffman超字符 */
#endif
#include "../BinTree/BinTree.h"						/* 二叉树 */
#include "../BST/BST.h"								/* 二叉搜索树 */
#include "../Splay/Splay.h"							/* 伸展树 */
#include "../AVL/AVL.h"								/* AVL树 */
#include "../redBlack/RedBlack.h"					/* 红黑树 */
#include "../BTree/BTree.h"							/* 二叉搜索树（B-树） */
#include "../Hashtable/Entry.h"						/* 词条 */
#include "../Hashtable/Hashtable.h"					/* 散列表 */
#include "../graphMatrix/Graph.h"					/* 图 */
#include "../graphMatrix/GraphMatrix.h"				/* 基于邻接矩阵实现的图 */

/******************************************************************************************
 * 数据元素、数据结构通用输出接口
 ******************************************************************************************/
template <typename T> static void print ( T* x ) {  x ? print ( *x ) : (void)printf ( " <NULL>" );  }
template <typename T> static void print ( T& x ) {  UniPrint::p ( x );  }
template <typename T> static void print ( const T& x ) {  UniPrint::p ( x );  }		/* for Stack */
static void print ( char* x ) {  printf ( " %s", x ? x : "<NULL>" );  }				/* 字符串特别处理 */
static void print ( const char* x ) {  printf ( " %s", x ? x : "<NULL>" );  }		/* 字符串特别处理 */

class UniPrint {
public:
   static void p ( int );
   static void p ( float );
   static void p ( double );
   static void p ( char );

#if 0
   static void p ( HuffChar& );														/* Huffman（超）字符 */
#endif
   static void p ( VStatus );														/* 图顶点的状态 */
   static void p ( EType );															/* 图边的类型 */

   template <typename K, typename V> static void p ( Entry<K, V>& );				/* Entry */
   template <typename T> static void p ( BinNode<T>& );								/* BinTree节点 */
   template <typename T> static void p ( BinTree<T>& );								/* 二叉树 */
   template <typename T> static void p(BTree<T>&);									/* B-树 */
   template <typename T> static void p(BST<T>&);									/* BST */
   template <typename T> static void p(Splay<T>&);									/* Splay */
   template <typename T> static void p(AVL<T>&);									/* AVL */
   template <typename T> static void p(RedBlack<T>&);								/* RedBlack */
   template <typename K, typename V> static void p(Hashtable<K, V>&);				/* Hashtable */
   template <typename Tv, typename Te> static void p(GraphMatrix<Tv, Te>&);			/* Graph */

   template <typename T> static void p ( T& );										/* 向量、列表等支持traverse()遍历操作的线性结构 */
   template <typename T> static void p ( T* s )										/* 所有指针 */
   {  s ? p ( *s ) : print ( "<NULL>" ); }											/* 统一转为引用 */
}; /* UniPrint */


#include "Print_BinNode.h"
#include "Print_BinTree.h"
#include "Print_BTree.h"
#include "Print_Entry.h"
#include "Print_Hashtable.h"
#include "Print_graphmatrix.h"
#include "Print_traversable.h"

#endif // !PRINT_H__ 