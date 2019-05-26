/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn��add and modify it .
* All rights reserved.
******************************************************************************************/

/*DSA*/#include "../bitmap/bitmap.h"

int primeNLT ( int c, int n, char* file ) { //����file�ļ��еļ�¼����[c, n)��ȡ��С������
   Bitmap B ( file, n ); //file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
   while ( c < n ) //��c��ʼ����λ��
      if ( B.test ( c ) ) c++; //���ԣ�����
      else return c; //�����׸����ֵ�����
   return c; //��û������������������n��ʵ���в�����˼򻯴���
}
