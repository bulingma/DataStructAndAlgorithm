/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BIT_O1_INIT_SET_ONLY_H__
#define BIT_O1_INIT_SET_ONLY_H__
#pragma warning(disable : 4996 4800)
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "../_share/release.h"

typedef int Rank;				/* 秩 */

 /* 位图Bitmap类：以空间作为补偿，节省初始化时间（仅允许插入，不支持删除） */
class Bitmap { 
private:
   Rank* F;						/* 规模为N的向量F，记录[k]被标记的次序（即其在栈T[]中的秩） */
   Rank N;		
   Rank* T;						/* 容量为N的栈T，记录被标记各位秩的栈，以及栈顶指针 */
   Rank top;	

protected:
   inline bool valid ( Rank r ) { return ( 0 <= r ) && ( r < top ); }

public:
   Bitmap ( Rank n = 8 )		/* 按指定（或默认）规模创建比特图（为测试暂时选用较小的默认值） */
   {							/* 在O(1)时间内隐式地初始化 */
	   N = n; 
	   F = new Rank[N]; 
	   T = new Rank[N]; 
	   top = 0; 
   } 

   ~Bitmap()					/* 析构时释放空间 */ 
   {
	   delete [] F; 
	   delete [] T; 
   } 

	/*  接口 */
   inline void set ( Rank k )	/* 插入 */
   { 
      if ( test ( k ) )			/* 忽略已带标记的位 */
		  return; 
      F[k] = top++; 
	  T[ F[k] ] = k;			/* 建立校验环 */
   }

   inline bool test ( Rank k )	/* 测试 */
   {  
	   return valid ( F[k] ) && ( k == T[ F[k] ] );  
   }
};

#endif // !BIT_O1_INIT_SET_ONLY_H__