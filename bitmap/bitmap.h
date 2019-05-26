/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef BITMAP_H__
#define BITMAP_H__
#pragma warning(disable : 4996 4800)
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "../_share/release.h"

 /* λͼBitmap�� */
class Bitmap { 
private:
   char* M;							/* ����ͼ����ŵĿռ�M[]������ΪN*sizeof(char)*8���� */
   int N; 
protected:
   void init ( int n ) 
   {
	   M = new char[N = ( n + 7 ) / 8]; 
	   memset ( M, 0, N ); 
   }
public:
   Bitmap ( int n = 8 )				/* ��ָ����Ĭ�Ϲ�ģ��������ͼ��Ϊ������ʱѡ�ý�С��Ĭ��ֵ�� */
   { 
	   init ( n ); 
   } 
   Bitmap ( char* file, int n = 8 ) /* ��ָ����Ĭ�Ϲ�ģ����ָ���ļ��ж�ȡ����ͼ */
   {  
	   init ( n ); 
	   FILE* fp = fopen ( file, "r" ); 
	   fread ( M, sizeof ( char ), N, fp ); 
	   fclose ( fp );  
   }
   ~Bitmap()						/* ����ʱ�ͷű���ͼ�ռ� */
   { 
	   delete [] M; 
	   M = NULL; 
   } 

   void set( int k ) 
   { 
	   expand ( k ); 
	   M[k >> 3] |= ( 0x80 >> ( k & 0x07 ) ); 
   }
   void clear ( int k ) 
   { 
	   expand ( k );   
	   M[k >> 3] &= ~ ( 0x80 >> ( k & 0x07 ) ); 
   }
   bool test  ( int k ) 
   { 
	   expand ( k ); 
	   return M[k >> 3] & ( 0x80 >> ( k & 0x07 ) ); 
   }

   void dump ( char* file )			/* ��λͼ���嵼����ָ�����ļ����Ա�Դ˺����λͼ������ʼ�� */
   {  
	   FILE* fp = fopen ( file, "w" ); 
	   fwrite ( M, sizeof ( char ), N, fp ); 
	   fclose ( fp );  
   }
   char* bits2string ( int n )		/* ��ǰnλת��Ϊ�ַ��� */
   {
      expand ( n - 1 );				/* ��ʱ���ܱ����ʵ����λΪbitmap[n - 1] */
      char* s = new char[n + 1];	/* �ַ�����ռ�ռ䣬���ϲ�����߸����ͷ� */
	  s[n] = '\0'; 
	  for (int i = 0; i < n; i++)
		  s[i] = test(i) ? '1' : '0';
      return s; //�����ַ���λ��
   }
   void expand ( int k ) {			/* �������ʵ�Bitmap[k]�ѳ��磬�������� */
      if ( k < 8 * N )				/* ���ڽ��ڣ��������� */
		  return; 
      int oldN = N; 
	  char* oldM = M;
      init ( 2 * k );				/* ���������ƣ��ӱ����� */
      memcpy_s ( M, N, oldM, oldN );/* ԭ����ת�����¿ռ�  --�˴���ԭ�����Ƿ��ѱ�memsetΪ0������ */
	  delete [] oldM; 
   }
   /*DSA*/
	void print ( int n )			/* ��λ��ӡ�Լ���λͼ���ݣ��Ǳ���ӿ� */
    {  
	   expand ( n ); 
	   for ( int i = 0; i < n; i++ ) 
		   printf ( test ( i ) ? "1" : "0" ); 
	}
};

#endif // !BITMAP_H__