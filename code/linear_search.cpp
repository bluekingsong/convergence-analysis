
#include "linear_search.h"

double backtracking_linear_search(
	void *instance, // user-specified object
	func_evaluator proc_evaluate, // object-function value evaluator
	double *x, // current point
	double *xp, // backup place for x
	double *g, // current gradient
	double *p, // negative of search direction
	int n, // number of varialbes
	double fx, // current function value at x
	double c, // sufficient decrease condition threshold
	double init_step, // initial step length
	double r, // scale factor in backtracking
){
	double dec;
	vec_dot(&dec,g,p,-c);
	if(dec<0){ // non suitable step
		return -1;
	}
	double alpha=init_step;
	vec_add(xp,x,p,-alpha);
	while( proc_evaluate(instance,xp,g,n) > fx+alpha*dec ){
		alpha*=r;
		vec_add(xp,x,p,-alpha);
	}
	return alpha;
}
