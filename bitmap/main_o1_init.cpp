/******************************************************************************************
 * Data Structures And Algorithm in C++
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma warning(disable : 4996 4800)
#include "../_share/util.h"
#include "bitmap.h"
//#include "bitmap_O1_init.h"

/* 以上两个头文件只需包含任意其中一个即可;
bitmap.h: 空间复杂度最低
bitmap_O1_init.h: 以空间作为补偿，节省初始化时间 */

/******************************************************************************************
 * 测试位图
 ******************************************************************************************/
int testBitmap ( int n ) {
   bool* B = new bool[n]; 
   memset ( B, 0, n * sizeof ( bool ) );	//常规位图，创建后随即O(n)时间初始化
   Bitmap M ( n );
   for ( int i = 0; i < 9 * n; i++ ) {
      Rank k = dice ( n );
      if ( dice ( 2 ) ) 
	  {
         printf ( "set(%d) ...", k );		//set(k)
         B[k] = true; 
		 M.set ( k );
      }
	  else 
	  {
         printf ( "clear(%d) ...", k );		//clear(k)
         B[k] = false;
		 M.clear ( k );
      }
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
	srand ( ( unsigned int ) time ( NULL ) );	//设置随机种子
	return testBitmap (iNumber);				//启动测试
}