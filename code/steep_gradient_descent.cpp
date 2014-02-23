
#include "linear_search.h"

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
	double r, // scale factor in backtracking
){
	double dec;
	vec_dot(&dec,g,p,-c);
	if(dec<0){ // non suitable step
		return -1;
	}
	double alpha=init_step;
	vec_add(xp,x,p,-alpha);
	double newFx;
	while((newFx=proc_evaluate(instance,xp,g,n)) > fx+alpha*dec ){
		alpha*=r;
		vec_add(xp,x,p,-alpha);
	}
	*fx=newFx;
	return alpha;
}

void steep_gradient_descent(const char* filename,int maxIter,double objDelta){
	Problem prob=read_problem(filename);
	int iter=0;
	double *x=new double[prob.n];
	memset(x,0,sizeof(x)*prob.n);
	double *xp=new double[prob.n];
	double *g=new double[prob.n];
	double *p=new double[prob.n];
	double fx=func_evaluate(x,g,prob);
	vec_cpy(p,g,prob.n);
	while(true){
		++iter;
		double last=fx;
		double alpha=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,prob.n,&fx,0.4,2,0.8);
		double decrease=last-fx;
		if(maxIter>0 && iter>=maxIter){
			break;
		}
		if(objDelta>0 && decrease<objDelta){
			break;
		}
	}
}
int main(){

	return 0;
}
