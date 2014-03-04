#include <cstring>
#include <iostream>
#include "linear_search.h"
#include "vec_op.h"
using namespace std;

// @s the difference of Xk+1 and Xk for k=0 to m-1
// @y the difference of Gk+1 and Gk for k=0 to m-1
// @n the number of parameter
// @m we keep at most latest m iteration information
// @gamma the initail approximation of inverse Hessian using gamma*I
// @result the bfgs direciton we need
void calc_bfgs_direction(double *s,double *y,int n,int m,int k,double gamma,double *result){
	double *g=y+n*(k%m);  // the gradient at now
	vec_cpy(result,g,n);
	for(int i=(k-1)
}
void lbfgs(const char* filename,int maxIter,double objDelta,int m){
	time_t t=time(0);
	cout<<"begin read probelm:"<<asctime(localtime(&t))<<endl;
	Problem prob=read_problem(filename);
	t=time(0);
	cout<<"end of read:"<<asctime(localtime(&t))<<endl;
	int iter=0;
	double *s=new double[prob.n*m];
	double *y=new double[prob.n*m];
	int k=0;
	
	double *x=new double[prob.n];
	memset(x,0,sizeof(x)*prob.n);
	double *xp=new double[prob.n];
	double *g=new double[prob.n];
	double *p=new double[prob.n];

	double fx=func_evaluate(x,g,prob);
	int evaluateCnt=1;
	cout<<"init obj value="<<fx<<endl;
	double c1=1e-4;
	while(true){
		double last=fx;
		double alpha;
		//backup gradient at now
		vec_cpy(y+n*(k%m),g,n);
		if(0==k){  // the first step, we have to use steepest gradient search
			vec_cpy(p,g,prob.n);
			double init_step=calc_init_step(g,prob.n,iter);
			alpha=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,prob.n,&fx,c1,init_step,0.8,&evaluateCnt);
		}else{
			double r1,r2;
			vec_dot(&r1,s+last_iter_index*n,y+last_iter_index*n,n);
			vec_dot(&r2,y+last_iter_index*n,y+last_iter_index*n,n);
			double gamma=r1/r2;
			calc_bfgs_direction(s,y,n,m,k,gamma,p);
			alpha=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,prob.n,&fx,c1,1.0,0.8,&evaluateCnt);
		}
		if(alpha<0){
			cout<<"stop, cannot find suitable step length."<<endl;
			break;
		}
		vec_add(s+n*(k%m),xp,x,n,1,-1);
		vec_add(y+n*(k%m),g,y+n*(k%m),n,1,-1);
		vec_cpy(x,xp,prob.n);
		++k;
		++iter;
		double decrease=last-fx;
		cout<<"#iteration "<<iter<<" #obj_value "<<fx<<" #ave_obj "<<fx/prob.l<<" #evaluate_cnt "<<evaluateCnt<<endl;
		t=time(0);
		cout<<"time:"<<asctime(localtime(&t))<<endl;
		if(maxIter>0 && iter>=maxIter){
			break;
		}
		if(objDelta>0 && decrease<objDelta){
			break;
		}
	}
	delete []x;
	delete []xp;
	delete []g;
	delete []p;
}
int main(int argc,char **argv){
	steep_gradient_descent("../data/train.lbm",100,1);
	return 0;
}
