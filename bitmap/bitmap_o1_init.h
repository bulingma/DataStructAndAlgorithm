/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BITMAP_O1_INIT_H__
#define BITMAP_O1_INIT_H__
#pragma warning(disable : 4996 4800)
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "../_share/release.h"

/* λͼBitmap�ࣺ�Կռ���Ϊ��������ʡ��ʼ��ʱ�䣨��������룬��֧��ɾ���� */
class Bitmap { 
private:
   Rank* F; 
   Rank N;		/* ��ģΪN������F����¼[k]����ǵĴ��򣨼�����ջT[]�е��ȣ� */
   Rank* T; 
   Rank top;	/* ����ΪN��ջT����¼����Ǹ�λ�ȵ�ջ���Լ�ջ��ָ�� */

protected:
   inline bool valid ( Rank r ) 
   { 
	   return ( 0 <= r ) && ( r < top ); 
   }
   inline bool erased ( Rank k )						 /* �ж�[k]�Ƿ�������ǹ����Һ����ֱ���� */
   { 
	   return valid ( F[k] ) && ! ( T[ F[k] ] + 1 + k ); /* ����Լ����T[ F[k] ] = - 1 - k */
   } 

public:
   Bitmap ( Rank n = 8 )								 /* ��ָ������Ĭ�ϣ���ģ��������ͼ��Ϊ������ʱѡ�ý�С��Ĭ��ֵ�� */
   {													 /* ��O(1)ʱ������ʽ�س�ʼ�� */
	   N = n; 
	   F = new Rank[N]; 
	   T = new Rank[N]; 
	   top = 0; 
   } 
   ~Bitmap()											/* ����ʱ�ͷſռ� */
   {											
	   delete [] F; 
	   delete [] T; 
   } 

	/* �ӿ� */
   inline void set ( Rank k )							/* ���� */
   {							
      if ( test ( k ) )									/* �����Ѵ���ǵ�λ */
		  return;							
      if ( !erased ( k ) )								/* ��ϵ���α�ǣ��򴴽���У�黷 */
		  F[k] = top++;				
      T[ F[k] ] = k;									/* ��ϵ������Ǻ��������ָ�ԭУ�黷 */
   }
   inline void clear ( Rank k )							/* ɾ�� */
   {  
	   if ( test ( k ) )								/* ���Բ�����ǵ�λ */
		   T[ F[k] ] = - 1 - k;  
   } 
   inline bool test ( Rank k )							/* ���� */
   {  
	   return valid ( F[k] ) && ( k == T[ F[k] ] );  
   }
};
#endif // !BITMAP_O1_INIT_H__