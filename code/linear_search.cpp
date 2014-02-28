#include <iostream>
#include "linear_search.h"
#include "vec_op.h"
using namespace std;

double backtracking_linear_search(
	void *instance, // user-specified object
	func_evaluator proc_evaluate, // object-function value evaluator
	double *x, // current point
	double *xp, // backup place for x
	double *g, // current gradient
	double *p, // negative of search direction
	int n, // number of varialbes
	double *fx, // current function value at x
	double c, // sufficient decrease condition threshold
	double init_step, // initial step length
	double r // scale factor in backtracking
){
	double dec;
	vec_dot(&dec,g,p,n);
	if(dec<0){ // non suitable step,p is not a descent search direction
		return -1;
	}
	cout<<"unit decrease of g'p="<<dec<<endl;
	for(int i=0;i<10;i++){
		cout<<"x["<<i<<"]="<<x[i]<<" p["<<i<<"]="<<p[i]<<endl;
	}
	double alpha=init_step;
	vec_add(xp,x,p,n,1,-alpha);
	double old_fx=*fx;
	while( (*fx=proc_evaluate(instance,xp,g,n)) > old_fx+alpha*c*dec ){
		cout<<"try step length "<<alpha<<" get obj "<<*fx<<endl;
		alpha*=r;
		vec_add(xp,x,p,n,1,-alpha);
	}
	return alpha;
}
