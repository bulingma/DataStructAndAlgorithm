/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#pragma warning(disable : 4996 4800)
#include "../_share/util.h"
#include "bitmap_O1_init.h"

/******************************************************************************************
 * 测试位图
 ******************************************************************************************/
int testBitmap ( int n ) {
   bool* B = new bool[n]; 
   memset ( B, 0, n * sizeof ( bool ) );	//常规位图，创建后随即O(n)时间初始化
   Bitmap M ( n );
   for ( int i = 0; i < 9 * n; i++ ) 
   {
      Rank k = dice ( n );
      printf ( "set(%d) ...", k );			//set(k)
      B[k] = true;
	  M.set ( k );
      printf ( "done\n CRC: " );

      for ( int j = 0; j < n; j++ ) 
		  printf ( "%6c", B[j] == M.test ( j ) ? ' ' : '!' );

      printf ( "\n B[]: " );
      for ( int j = 0; j < n; j++ ) 
		  printf ( "%6c", B[j] ? 'x' : '.' );

      printf ( "\n M[]: " );
      for ( int j = 0; j < n; j++ ) 
		  printf ( "%6c", M.test ( j ) ? 'x' : '.' );

      printf ( "\n\n\n" );
   }
   delete [] B;
   return 0;
}

/******************************************************************************************
 * 测试位图
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   int iNumber = 10;
   srand((unsigned int)time(NULL));	//设置随机种子
   return testBitmap (iNumber); //启动测试
}