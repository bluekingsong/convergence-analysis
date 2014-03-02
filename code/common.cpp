#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstring>
#include "common.h"
using namespace std;

typedef double lbfgsfloatval_t;
// function implemented to evaluate the opt-fun value and gradients at parameter w by using step length @step in linear search
lbfgsfloatval_t func_evaluate(const lbfgsfloatval_t *w,lbfgsfloatval_t *g,const Problem &data){
	if(0==g){
		cerr<<"error:null pointer of gradients g,exit."<<endl;
		return 0;
	}
	int n=data.n; // number of features
	memset(g,0,sizeof(g)*n);
	lbfgsfloatval_t NLL=0.0;  // obj-function value
	for(int i=0;i<data.l;++i){
/*		time_t t=time(0);
		line_cnt++;
		if(line_cnt%1000000==0)
		{
			t=time(0);
			cout<<"progress:"<<line_cnt<<" time:"<<asctime(localtime(&t))<<endl;
		}*/
		const FeatureNode *instance=data.x[i];
		double yi=data.y[i];
		lbfgsfloatval_t t=0.0;
		int j=0;
		while(-1!=instance[j].index){
			t+=w[instance[j].index-1]*instance[j].value;
			if(i<2 && j<4) cout<<"index="<<instance[j].index<<" w[index]="<<w[instance[j].index-1]<<" ";
			++j;
		}
		lbfgsfloatval_t ui=sigmod(t);
		j=0;
		while(-1!=instance[j].index){
			g[instance[j].index-1]+=(ui-yi)*instance[j].value; // gradient, X'*(U-Y)
			++j;
		}
		if(i<2)	cout<<"************\nui="<<ui<<" t="<<t<<endl;
		if(yi)	NLL-=log(ui);
		else	NLL-=log(1-ui);
		//NLL+=-(yi*log(ui)+(1-yi)*log(1-ui));
	}
	return NLL;
}
double evaluator_interface(
	void *instance, // user-specified object
	double *x, // the current variables
	double *g, // gradient
	int n // number of variables
){
	Problem *prob=(Problem*)instance;
	func_evaluate(x,g,*prob);
}
double sigmod(double x){
	return 1/(1+exp(-x));
}
