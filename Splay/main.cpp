/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#include<iostream>
using namespace std;
#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "Splay.h"

template <typename T> void  testSplayPeriod ( int n ) { //周期性访问测试
   Splay<T> splay;
   for ( int i = 0; i < n; i++ ) splay.insert ( ( T ) i ); print ( splay );
   for ( int i = 0; i < n; i++ ) { splay.search ( ( T ) i ); print ( splay ); }
}

template <typename T> void  testSplayRandom ( int n ) { //随机访问测试
   Splay<T> splay;
   while ( splay.size() < n ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)范围内的e
      switch ( dice ( 3 ) ) {
         case 0: { //查找，成功率 <= 33.3%
            printf ( "Searching for " ); print ( e ); printf ( " ...\n" );
            splay.search ( e ) ?
            printf ( "Found with" ), print ( splay.root() ), printf ( "\n" ) :
            printf ( "Not found\n" );
            break;
         }
         case 1: { //删除，成功率 <= 33.3%
            printf ( "Removing " ); print ( e ); printf ( " ...\n" );
            splay.remove ( e ) ? (void)printf ( "Removal done\n" ) : print ( e ), (void)printf ( " not exists\n" );
            break;
         }
         default: {//插入，成功率 == 100%
            printf ( "Inserting " ); print ( e ); printf ( " ...\n" );
            splay.insert ( e );
            ( e == splay.root()->data ) ? printf ( "Insertion done with" ), print ( splay.root() ), (void)printf ( "\n" ) : print ( e ), "duplicated";
            break;
         }
      } //switch
      print ( splay ); //无论调用哪个接口，Splay都会自我调整形态，故需统一输出
   } //while
   while ( splay.size() > 0 ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)范围内的e
      printf ( "Removing " ); print ( e ); printf ( " ...\n" );
      splay.remove ( e ) ? printf ( "Removal done\n" ), print ( splay ) : print ( e ), (void)printf ( " not exists\n" );
   }
} //课后：利用这一接口，针对不同分布的访问，验证课上对Splay分摊分析的结论

int main ( int argc, char* argv[] ) { //测试主入口
	int size = 10;
	srand ( ( unsigned int ) time ( NULL ) );
	testSplayRandom<int> (size); //元素类型可以在这里任意选择
	testSplayPeriod<int> (size); //元素类型可以在这里任意选择
	return 0;
}