#include <cstring>
#include <iostream>
#include "linear_search.h"
#include "vec_op.h"
using namespace std;

void calc_direction(double *s,double *y,int n,int m,int k,bool fullMark,double *result){

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
	
	double *x=new double[prob.n];
	memset(x,0,sizeof(x)*prob.n);
	double *xp=new double[prob.n];
	double *g=new double[prob.n];
	double *p=new double[prob.n];

	bool fullMark=false;
	int k=0;

	double fx=func_evaluate(x,g,prob);
	int evaluateCnt=1;
	cout<<"init obj value="<<fx<<endl;
	double c1=1e-4;
	while(true){
		++iter;
		double last=fx;
		vec_cpy(p,g,prob.n);
		double init_step=calc_init_step(g,prob.n,iter);
		double alpha=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,prob.n,&fx,c1,init_step,0.8,&evaluateCnt);
		if(alpha<0){
			cout<<"stop, cannot find suitable step length."<<endl;
			break;
		}
		vec_cpy(x,xp,prob.n);
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
