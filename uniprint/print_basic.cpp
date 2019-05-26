/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Junhui DENG(deng@tsinghua.edu.cn) is first author, Yuguang Ma learn、add and modify it .
* All rights reserved.
******************************************************************************************/

#include "print.h"

/******************************************************************************************
 * 基本类型
 ******************************************************************************************/
void UniPrint::p ( int e ) { printf ( " %04d", e ); }
void UniPrint::p ( float e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( double e ) { printf ( " %4.1f", e ); }
void UniPrint::p ( char e ) { printf ( " %c", ( 31 < e ) && ( e < 128 ) ? e : '$' ); }

void UniPrint::p ( VStatus e ) {
   switch ( e ) {
      case UNDISCOVERED:   printf ( "U" ); break;
      case DISCOVERED:     printf ( "D" ); break;
      case VISITED:        printf ( "V" ); break;
      default:             printf ( "X" ); break;
   }
}
void UniPrint::p ( EType e ) {
   switch ( e ) {
      case UNDETERMINED:   printf ( "U" ); break;
      case TREE:           printf ( "T" ); break;
      case CROSS:          printf ( "C" ); break;
      case BACKWARD:       printf ( "B" ); break;
      case FORWARD:        printf ( "F" ); break;
      default:             printf ( "X" ); break;
   }
}
