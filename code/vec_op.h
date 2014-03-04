#ifndef _VECOP_H_
#define _VECOP_H_

// @vec_len the length of vectors
// @retval inner product of vec1 and vec2
double vec_dot(double *vec1,double *vec2,int vec_len);

// @result_vec result vector of factor1*vec1+factor2*vec2;
// @vec_len the legnth of vectors
void vec_add(double *result_vec,double *vec1,double *vec2,int vec_len,double factor1,double factor2);

// @dest destination of copy vector @src
// @vec_len the length of vectors
void vec_cpy(double *dest,double *src,int vec_len);

// #retval L1-norm of @vec, i.e. sum of |vec[i]|
double vec_l1_norm(double *vec,int vec_len);

// vec=factor*vec,@factor is a scalar
void vec_mul(double *vec,int vec_len,double factor);
#endif
