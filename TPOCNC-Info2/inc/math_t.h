#ifndef INC_MATH_T_H_
#define INC_MATH_T_H_

/*
  2  * (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  3  * See the copyright notice in the ACK home directory, in the file "Copyright".
  4  *
  5  * Author: Ceriel J.H. Jacobs
  6  */ /* $Header: /users/cosc/staff/paul/CVS/minix1.7/src/lib/math/atan2.c,v 1.2 1996/04/10 21:15:02 paul Exp $ */

//Macros

#define 	M_E   2.7182818284590452354

#define 	M_LOG2E   1.4426950408889634074	/* log_2 e */

#define 	M_LOG10E   0.43429448190325182765	/* log_10 e */

#define 	M_LN2   0.69314718055994530942	/* log_e 2 */

#define 	M_LN10   2.30258509299404568402	/* log_e 10 */

#define 	M_PI   3.14159265358979323846	/* pi */

#define 	M_PI_2   1.57079632679489661923	/* pi/2 */

#define 	M_PI_4   0.78539816339744830962	/* pi/4 */

#define 	M_1_PI   0.31830988618379067154	/* 1/pi */

#define 	M_2_PI   0.63661977236758134308	/* 2/pi */

#define 	M_2_SQRTPI   1.12837916709551257390	/* 2/sqrt(pi) */

#define 	M_SQRT2   1.41421356237309504880	/* sqrt(2) */

#define 	M_SQRT1_2   0.70710678118654752440	/* 1/sqrt(2) */

double atan2_t(double y, double x);

float atan3_t ( float dy, float dx );


#endif /* INC_MATH_T_H_ */
