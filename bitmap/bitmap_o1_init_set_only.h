/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BIT_O1_INIT_SET_ONLY_H__
#define BIT_O1_INIT_SET_ONLY_H__
#pragma warning(disable : 4996 4800)
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "../_share/release.h"

typedef int Rank;				/* �� */

 /* λͼBitmap�ࣺ�Կռ���Ϊ��������ʡ��ʼ��ʱ�䣨��������룬��֧��ɾ���� */
class Bitmap { 
private:
   Rank* F;						/* ��ģΪN������F����¼[k]����ǵĴ��򣨼�����ջT[]�е��ȣ� */
   Rank N;		
   Rank* T;						/* ����ΪN��ջT����¼����Ǹ�λ�ȵ�ջ���Լ�ջ��ָ�� */
   Rank top;	

protected:
   inline bool valid ( Rank r ) { return ( 0 <= r ) && ( r < top ); }

public:
   Bitmap ( Rank n = 8 )		/* ��ָ������Ĭ�ϣ���ģ��������ͼ��Ϊ������ʱѡ�ý�С��Ĭ��ֵ�� */
   {							/* ��O(1)ʱ������ʽ�س�ʼ�� */
	   N = n; 
	   F = new Rank[N]; 
	   T = new Rank[N]; 
	   top = 0; 
   } 

   ~Bitmap()					/* ����ʱ�ͷſռ� */ 
   {
	   delete [] F; 
	   delete [] T; 
   } 

	/*  �ӿ� */
   inline void set ( Rank k )	/* ���� */
   { 
      if ( test ( k ) )			/* �����Ѵ���ǵ�λ */
		  return; 
      F[k] = top++; 
	  T[ F[k] ] = k;			/* ����У�黷 */
   }

   inline bool test ( Rank k )	/* ���� */
   {  
	   return valid ( F[k] ) && ( k == T[ F[k] ] );  
   }
};

#endif // !BIT_O1_INIT_SET_ONLY_H__