/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef RAND_H__
#define RAND_H__

#include <stdlib.h>
#include <time.h> //ͨ���õ�ǰʱ�������������

/******************************************************************************************
 * ��[0, range)���������һ����
 ******************************************************************************************/
static int dice ( int range ) { return rand() % range; } //ȡ[0, range)�е��������
static int dice ( int lo, int hi ) { return lo + rand() % ( hi - lo ); } //ȡ[lo, hi)�е��������
static float dice ( float range ) { return rand() % ( 1000 * ( int ) range ) / ( float ) 1000.; }
static double dice ( double range ) { return rand() % ( 1000 * ( int ) range ) / ( double ) 1000.; }
static char dice ( char range ) { return ( char ) ( 32 + rand() % 96 ); }

#endif // !RAND_H__