#include <cstring>
#include <iostream>
#include "linear_search.h"
#include "vec_op.h"
using namespace std;

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
		double alpha=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,prob.n,&fx,0.4,2,0.8);
		if(alpha<0){
			cout<<"stop, cannot find suitable step length."<<endl;
			break;
		}
		double decrease=last-fx;
		cout<<"#iteration "<<iter<<" #obj_value "<<fx<<endl;
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
	steep_gradient_descent("../data/train.lbm",100,1e-6);
	return 0;
}
