#include <cstring>
#include <cmath>
#include "vec_op.h"
using namespace std;

void vec_dot(double *result,double *vec1,double *vec2,int vec_len){
	*result=0;
	for(int i=0;i<vec_len;++i)	*result+=vec1[i]*vec2[i];
}

void vec_add(double *result_vec,double *vec1,double *vec2,int vec_len,double factor1,double factor2){
	for(int i=0;i<vec_len;++i)	result_vec[i]=factor1*vec1[i]+factor2*vec2[i];
}

void vec_cpy(double *dest,double *src,int vec_len){
	if(0==dest ||0==src || dest==src)	return;
	memcpy(dest,src,sizeof(dest)*vec_len);
}

double vec_l1_norm(double *vec,int vec_len){
	double result=0.0;
	for(int i=0;i<vec_len;++i)	result+=abs(vec[i]);
	return result;
}
