/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PRINT_BINNODE_H__
#define PRINT_BINNODE_H__

/******************************************************************************************
 * BinTree�ڵ�
 ******************************************************************************************/
template <typename T> void UniPrint::p ( BinNode<T>& node ) {
   p ( node.data ); //��ֵ
   /******************************************************************************************
    * height & NPL
    ******************************************************************************************/
#if   defined(DSA_LEFTHEAP)
   printf ( "(%-2d)", node.npl ); //NPL
#elif defined(DSA_BST)
   printf ( "(%-2d)", node.height ); //�߶�
#elif defined(DSA_AVL)
   printf ( "(%-2d)", node.height ); //�߶�
#elif defined(DSA_REDBLACK)
   printf ( "(%-2d)", node.height ); //�߶�
#elif defined(DSA_SPLAY)
   printf ( "(%-2d)", node.height ); //�߶�
#endif
   /******************************************************************************************
    * ��������ָ��
    ******************************************************************************************/
   printf (
      (  ( node.lc && &node != node.lc->parent ) ||
         ( node.rc && &node != node.rc->parent )  ) ?
      "@" : " "
   );
   /******************************************************************************************
    * �ڵ���ɫ
    ******************************************************************************************/
#if defined(DSA_REDBLACK)
   printf ( node.color == RB_BLACK ? "B" : " " ); //�����Ժ�ڵ㣩
#endif
   /******************************************************************************************
    * ���ӣ��ڣ��߶ȡ�NPLƥ��
    ******************************************************************************************/
#if   defined(DSA_PQ_COMPLHEAP)
   //�߶Ȳ���ƥ��
#elif defined(DSA_PQ_LEFTHEAP)
   printf ( //NPL
      ( node.rc && node.npl != 1 + node.rc->npl ) ||
      ( node.lc && node.npl >  1 + node.lc->npl ) ?
      "%%" : " "
   );
#elif defined(DSA_REDBLACK)
   printf ( BlackHeightUpdated ( node ) ? " " : "!" ); //�ڸ߶�
#else
   printf ( HeightUpdated ( node ) ? " " : "!" ); //�����棩�߶�
#endif
   /******************************************************************************************
    * ����ƽ��
    ******************************************************************************************/
#if defined(DSA_AVL)
   if ( !AvlBalanced ( node ) ) printf ( "X" ); //AVLƽ��
   else if ( 0 < BalFac ( node ) ) printf ( "\\" ); //AVLƽ��
   else if ( BalFac ( node ) < 0 ) printf ( "/" ); //AVLƽ��
   else printf ( "-" ); //AVLƽ��
#elif defined(DSA_REDBLACK)
   if ( !Balanced ( node ) ) printf ( "X" ); //RBƽ��
   else if ( 0 < BalFac ( node ) ) printf ( "\\" ); //RBƽ��
   else if ( BalFac ( node ) < 0 ) printf ( "/" ); //RBƽ��
   else printf ( "-" ); //RBƽ��
#else
   //ƽ������ν
#endif
}

#endif // !PRINT_BINNODE_H__