/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

/******************************************************************************************
* Test of B-Tree
******************************************************************************************/
#include<iostream>
using namespace std;
#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "BTree.h"

/******************************************************************************************
* Test a BTree
******************************************************************************************/
template <typename T> void  testBTree ( int order, int n ) {
   BTree<T> bt ( order );
   while ( bt.size() < n ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)范围内的e
      switch ( dice ( 3 ) ) {
         case 0: { //查找，成功率 <= 33.3%
            printf ( "Searching for " ); print ( e ); printf ( " ... " );
            BTNodePosi(T) p = bt.search ( e );
            printf ( p ? "Found\n" : "Not found\n" );
            break;
         }
         case 1: { //删除，成功率 <= 33.3%
            printf ( "Removing " ); print ( e ); printf ( " ... " );
            bt.remove ( e ) ?
            printf ( "Done\n" ), print ( bt ) : (void)printf ( "Not exists\n" );
            break;
         }
         default: {//插入，成功率 == 100%
            printf ( "Inserting " ); print ( e ); printf ( " ... " );
            int oldSize = bt.size();
            bt.insert ( e ) ? printf ( "Done\n" ), print ( bt ) : (void)printf ( "Dup key\n" );
            break;
         }
      }
   }
   while ( bt.size() > 0 ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)范围内的e
      printf ( "Removing " ); print ( e ); printf ( " ... " );
      bt.remove ( e ) ? printf ( "Done\n" ), print ( bt ) : (void)printf ( "not exists\n" );
   }
}

/******************************************************************************************
* 测试主入口
******************************************************************************************/
int main ( int argc, char* argv[] ) {
   int order = 4; 
   if ( order < 3 )  { printf ( "Make sure the order (%d) is no less than 3.\a\a\n", order ); return 1; }
   int size = 10;
   srand ( ( unsigned int ) time ( NULL ) );
   testBTree<int> (order, size); //元素类型、比较器可以在这里任意选择
   return 0;
}