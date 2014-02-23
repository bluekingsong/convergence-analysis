#ifndef _COMMON_H_
#define _COMMON_H_
#ifdef __cplusplus
extern "C" {
#endif

struct FeatureNode{
	int index; // legal index start from 0. -1 means end of the feature vector
	double value;
};

struct Problem{
	int n,l;  // number of features & number of instances
	double *y; // label
	struct FeatureNode **x;
	double bias;            /* < 0 if no bias term */
};

typedef double lbfgsfloatval_t;
double func_evaluate(const double *w,double *g,const Problem &data,const double step=0);

double evaluator_interface(
	void *instance, // user-specified object
	double *x, // the current variables
	double *g, // gradient
	int n, // number of variables
);
// simplest linear search method: backtracking linear search
Problem read_problem(const char *filename);

#ifdef __cplusplus
}
#endif
#endif
