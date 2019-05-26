/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

/******************************************************************************************
 * Test of AVL Tree
 ******************************************************************************************/
#include<iostream>
using namespace std;
#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "AVL.h"

/******************************************************************************************
 * Test an AVL
 ******************************************************************************************/
template <typename T> void  testAVL ( int n ) {
   AVL<T> avl;
   while ( avl.size() < n ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      switch ( dice ( 3 ) ) {
         case 0: { //���ң��ɹ��� <= 33.3%
            printf ( "Searching for " ); print ( e ); printf ( " ...\n" );
            BinNodePosi(T) & p = avl.search ( e );
            p ?
            printf ( "Found with" ), print ( p ), printf ( "\n" ) :
            printf ( "Not found\n" );
            break;
         }
         case 1: { //ɾ�����ɹ��� <= 33.3%
            printf ( "Removing " ); print ( e ); printf ( " ...\n" );
            avl.remove ( e ) ? printf ( "Done\n" ), print ( avl ) : (void)printf ( "Not exists\n" );
            break;
         }
         default: {//���룬�ɹ��� == 100%
            printf ( "Inserting " ); print ( e ); printf ( " ...\n" );
            BinNodePosi(T) p = avl.insert ( e );
            if ( p->data != e ) { print ( p->data ); printf ( " <> " ); print ( e ); printf ( "\n" ); }
            printf ( "Done with" ), print ( p ), printf ( "\n" ), print ( avl );
            break;
         }
      }
   }
   while ( avl.size() > 0 ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      printf ( "Removing " ); print ( e ); printf ( " ...\n" );
      avl.remove ( e ) ? printf ( "Done\n" ), print ( avl ) : (void)printf ( "Not exists\n" );
   }
}

/******************************************************************************************
 * ���������
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
	int size = 10;
	srand ( ( unsigned int ) time ( NULL ) );
	testAVL<int> (size); //Ԫ�����Ϳ�������������ѡ��
	return 0;
}