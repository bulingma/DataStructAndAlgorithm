/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#include<iostream>
using namespace std;
#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "Splay.h"

template <typename T> void  testSplayPeriod ( int n ) { //�����Է��ʲ���
   Splay<T> splay;
   for ( int i = 0; i < n; i++ ) splay.insert ( ( T ) i ); print ( splay );
   for ( int i = 0; i < n; i++ ) { splay.search ( ( T ) i ); print ( splay ); }
}

template <typename T> void  testSplayRandom ( int n ) { //������ʲ���
   Splay<T> splay;
   while ( splay.size() < n ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      switch ( dice ( 3 ) ) {
         case 0: { //���ң��ɹ��� <= 33.3%
            printf ( "Searching for " ); print ( e ); printf ( " ...\n" );
            splay.search ( e ) ?
            printf ( "Found with" ), print ( splay.root() ), printf ( "\n" ) :
            printf ( "Not found\n" );
            break;
         }
         case 1: { //ɾ�����ɹ��� <= 33.3%
            printf ( "Removing " ); print ( e ); printf ( " ...\n" );
            splay.remove ( e ) ? (void)printf ( "Removal done\n" ) : print ( e ), (void)printf ( " not exists\n" );
            break;
         }
         default: {//���룬�ɹ��� == 100%
            printf ( "Inserting " ); print ( e ); printf ( " ...\n" );
            splay.insert ( e );
            ( e == splay.root()->data ) ? printf ( "Insertion done with" ), print ( splay.root() ), (void)printf ( "\n" ) : print ( e ), "duplicated";
            break;
         }
      } //switch
      print ( splay ); //���۵����ĸ��ӿڣ�Splay�������ҵ�����̬������ͳһ���
   } //while
   while ( splay.size() > 0 ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      printf ( "Removing " ); print ( e ); printf ( " ...\n" );
      splay.remove ( e ) ? printf ( "Removal done\n" ), print ( splay ) : print ( e ), (void)printf ( " not exists\n" );
   }
} //�κ�������һ�ӿڣ���Բ�ͬ�ֲ��ķ��ʣ���֤���϶�Splay��̯�����Ľ���

int main ( int argc, char* argv[] ) { //���������
	int size = 10;
	srand ( ( unsigned int ) time ( NULL ) );
	testSplayRandom<int> (size); //Ԫ�����Ϳ�������������ѡ��
	testSplayPeriod<int> (size); //Ԫ�����Ϳ�������������ѡ��
	return 0;
}