#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include "common.h"
using namespace std;

// function implemented to evaluate the opt-fun value and gradients at parameter w by using step length @step in linear search
lbfgsfloatval_t func_evaluate(const lbfgsfloatval_t *w,lbfgsfloatval_t *g,const problem &data, const lbfgsfloatval_t step=0){
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
		while(-1!=feature_node[j].index){
			t+=w[feature_node[j].index]*feature_node[j].value;
			++j;
		}
		lbfgsfloatval_t u=sigmod(t);
		lbfgsfloatval_t gradient=u-y;
		j=0;
		while(-1!=feature_node[j].index){
			g[feature_node[j].index]+=gradient;
			++j;
		}
		NLL+=-(yi*log(ui)+(1-yi)*log(1-ui));
	}
	return NLL;
}
double evaluator_interface(
	void *instance, // user-specified object
	double *x, // the current variables
	double *g, // gradient
	int n, // number of variables
){
	Problem *prob=(Problem*)instance;
	func_evaluate(x,g,*prob);
}
