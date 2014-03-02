#include <cstring>
#include <iostream>
#include "linear_search.h"
#include "vec_op.h"
using namespace std;

double calc_init_step(const double *g,const int n,int iter){
	double result=abs(g[0]);
	for(int i=1;i<n;++i){
		result=max(result,abs(g[i]));
	}
	return 10.0/result;
}

void steep_gradient_descent(const char* filename,int maxIter,double objDelta){
	time_t t=time(0);
	cout<<"begin read probelm:"<<asctime(localtime(&t))<<endl;
	Problem prob=read_problem(filename);
	t=time(0);
	cout<<"end of read:"<<asctime(localtime(&t))<<endl;
	int iter=0;
	double *x=new double[prob.n];
	memset(x,0,sizeof(x)*prob.n);
	double *xp=new double[prob.n];
	double *g=new double[prob.n];
	double *p=new double[prob.n];
	double fx=func_evaluate(x,g,prob);
	cout<<"init obj value="<<fx<<endl;
	while(true){
		++iter;
		double last=fx;
		vec_cpy(p,g,prob.n);
		double init_step=calc_init_step(g,prob.n,iter);
		double alpha=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,prob.n,&fx,0.4,init_step,0.9);
		if(alpha<0){
			cout<<"stop, cannot find suitable step length."<<endl;
			break;
		}
		vec_cpy(x,xp,prob.n);
		double decrease=last-fx;
		cout<<"#iteration "<<iter<<" #obj_value "<<fx<<" #ave_obj "<<fx/prob.l<<endl;
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
	steep_gradient_descent("../data/train.lbm",10,1e-6);
	return 0;
}
