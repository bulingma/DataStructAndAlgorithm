/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

#ifndef PQ_H__
#define PQ_H__

//���ȼ�����PQģ����
template <typename T> struct PQ 
{ 
   virtual void insert ( T ) = 0;	//���ձȽ���ȷ�������ȼ�����������
   virtual T getMax() = 0;			//ȡ�����ȼ���ߵĴ���
   virtual T delMax() = 0;			//ɾ�����ȼ���ߵĴ���
};

#endif // PQ_H__