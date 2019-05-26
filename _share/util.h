/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef UTIL_H__
#define UTIL_H__

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

/******************************************************************************************
 * ���ԡ���ʾ��С����
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <typeinfo.h>
#include "comparator.h"

#include "checkOrder_Elem.h"
#include "checkOrder_list.h"
#include "checkOrder_vector.h"

#include "double_Elem.h"
#include "increase_Elem.h"
#include "hailstone_Elem.h"
#include "increase_list.h"
#include "increase_vector.h"

#include "crc_Elem.h"
#include "crc_list.h"
#include "crc_vector.h"

#include "rand.h" //�����

#if defined(DSA_DEBUG) //���뿪�أ����Ƶ������
#define DSA(x)  { x } //���
#else
#define DSA(x) //�����
#endif

#endif // !UTIL_H__