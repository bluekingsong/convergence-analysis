#include <cstring>
#include <iostream>
#include <vector>
#include "linear_search.h"
#include "vec_op.h"
using namespace std;

void evaluate_gradient(const double *w,FeatureNode *x,double y,double *g,int n,vector<int>& indies){
	double t=0;
	int i=0;
	while(x[i].index>0){
		t+=w[x[i].index-1]*x[i].value;
		++i;
	}
	double u=sigmod(t);
	//memset(g,0,sizeof(g)*n);
	for(i=0;i<indies.size();++i)	g[indies[i]]=0;
	indies.clear();
	i=0;
	while(x[i].index>0){
		g[x[i].index-1]=(u-y)*x[i].value;
		indies.push_back(x[i].index-1);
		++i;
	}
}

void sgd(const char* filename,int iteration,double learningRate){
	time_t t=time(0);
	cout<<"begin read probelm:"<<asctime(localtime(&t))<<endl;
	Problem prob=read_problem(filename);
	t=time(0);
	cout<<"end of read:"<<asctime(localtime(&t))<<endl;
	int iter=0;
	int n=prob.n;
	double *mem=new double[3*n];
	double *w=mem;
	double *g=mem+n;
	double *xg=mem+2*n;
	memset(w,0,sizeof(w)*n);
	memset(xg,0,sizeof(xg)*n);
	vector<int> indies;
	double fx=func_evaluate(w,g,prob);
	cout<<"init obj value="<<fx<<endl;
	while(iter++<iteration){
		double last=fx;
		for(int i=0;i<prob.l;++i){
			evaluate_gradient(w,(prob.x)[i],(prob.y)[i],xg,n,indies);
			vec_add(w,w,xg,n,1.0,-learningRate);
			if(i%50000==0){
				t=time(0);
				cout<<"progress:"<<i<<" time:"<<asctime(localtime(&t))<<endl;
			}
		}
		fx=func_evaluate(w,g,prob);
		double decrease=last-fx;
		cout<<"#iteration "<<iter<<" #obj_value "<<fx<<" #ave_obj "<<fx/prob.l<<endl;
		t=time(0);
		cout<<"time:"<<asctime(localtime(&t))<<endl;
	}
	delete []mem;
}
int main(int argc,char **argv){
	sgd("../data/train.lbm",6,0.002);
	return 0;
}
