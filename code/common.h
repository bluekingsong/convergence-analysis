#ifndef _COMMON_H
#define _LIBLINEAR_H
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
lbfgsfloatval_t func_evaluate(const lbfgsfloatval_t *w,lbfgsfloatval_t *g,const Problem &data,const lbfgsfloatval_t step=0);

Problem read_problem(const char *filename);

#ifdef __cplusplus
}
#endif
#endif /* _LIBLINEAR_H */
