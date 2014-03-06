#include <cstring>
#include <iostream>
#include "linear_search.h"
#include "vec_op.h"
using namespace std;

// L-BFGS two-loop recursion
// @s the difference of Xk+1 and Xk for k=0 to m-1
// @y the difference of Gk+1 and Gk for k=0 to m-1
// @rho 1.0/(Yk'*Sk)
// @alpha alpha variable in the two-loop
// @g gradient at current iteration
// @n the number of parameter
// @m we keep at most latest m iteration information
// @gamma the initail approximation of inverse Hessian using gamma*I
// @result the bfgs direciton we need
void calc_bfgs_direction(double *s,double *y,double *rho,double *alpha,double *g,int n,int m,int k,double gamma,double *result){
	double *q=result;
	vec_cpy(q,g,n);
	int beg=(k-1)%m,end=0;
	if(k>m)	end=k%m;
	cout<<"In calc bfgs direction: beg="<<beg<<" end="<<end<<endl;
	for(int i=beg;true;i=(m+i-1)%m){
		alpha[i]=rho[i]*vec_dot(s+i*n,q,n);
		vec_add(q,q,y+i*n,n,1,-alpha[i]);
		if(i==end)	break;
	}
	vec_mul(q,n,gamma);
	for(int i=end;true;i=(i+1)%m){
		double beta=rho[i]*vec_dot(y+i*n,q,n);
		vec_add(q,q,s+i*n,n,1,alpha[i]-beta);
		if(i==beg)	break;
	}
}
void lbfgs(const char* filename,int maxIter,double objDelta,int m){
	time_t t=time(0);
	cout<<"begin read probelm:"<<asctime(localtime(&t))<<endl;
	Problem prob=read_problem(filename);
//	debug
//	Problem prob;	prob.n=2;
	t=time(0);
	cout<<"end of read:"<<asctime(localtime(&t))<<endl;
	int iter=0;
	int n=prob.n;
	double *mem=new double[2*n*m+2*m+5*n];
	double *s=mem; //new double[n*m];
	double *y=mem+n*m; //new double[n*m];
	double *rho=mem+2*n*m; //new double[m];
	double *alpha=mem+2*n*m+m; //new double[m];
	int k=0;
	
	double *x=mem+2*n*m+2*m; //new double[n];
	memset(x,0,sizeof(x)*n);
	double *xp=mem+2*n*m+2*m+n; //new double[n];
	double *g=mem+2*n*m+2*m+2*n; //new double[n];
	double *xg=mem+2*n*m+2*m+3*n; //new double[n];
	double *p=mem+2*n*m+2*m+4*n; //new double[n];

	double fx=func_evaluate(x,g,prob);
	int evaluateCnt=1;
	cout<<"init obj value="<<fx<<endl;
	double c1=1e-4;
	while(true){
		double last=fx;
		double step_len; // step length determined by linear search method
		//backup gradient at now
		vec_cpy(xg,g,n);
		if(0==k){  // the first step, we have to use steepest gradient search
			vec_cpy(p,g,n);
			double init_step=guess_init_step(g,n,iter);
			step_len=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,n,&fx,c1,init_step,0.8,&evaluateCnt);
		}else{
			double gamma=vec_dot(s+(k-1)%m*n,y+(k-1)%m*n,n)/vec_dot(y+(k-1)%m*n,y+(k-1)%m*n,n);
			cout<<"gamma="<<gamma<<endl;
			for(int i=0;i<10;++i){
				cout<<"s["<<i<<"]="<<s[(k-1)%m*n+i]<<"  y["<<i<<"]="<<y[(k-1)%m*n+i]<<endl;
			}
			calc_bfgs_direction(s,y,rho,alpha,g,n,m,k,gamma,p);
			cout<<" the bfgs direction:"<<endl;
			for(int i=0;i<10;++i) cout<<p[i]<<"   ";
			cout<<endl;

			step_len=backtracking_linear_search(&prob,evaluator_interface,x,xp,g,p,n,&fx,c1,1.0,0.8,&evaluateCnt);
		}
		if(step_len<0){
			cout<<"stop, cannot find suitable step length."<<endl;
			break;
		}
		vec_add(s+n*(k%m),xp,x,n,1,-1);
		vec_add(y+n*(k%m),g,xg,n,1,-1);
		rho[k%m]=1.0/vec_dot(y+n*(k%m),s+n*(k%m),n);
		cout<<"rho["<<k%m<<"]="<<rho[k%m]<<endl<<endl;
		vec_cpy(x,xp,n);
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
	delete []mem;
}
int main(int argc,char **argv){
	lbfgs("../data/train.lbm",60,1e-6,30);
	return 0;
}
