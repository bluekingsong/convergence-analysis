all: lbfgs gd

lbfgs: lbfgs.cpp common.cpp common.h linear_search.cpp linear_search.h read_problem.cpp vec_op.cpp vec_op.h
	g++ -g lbfgs.cpp common.cpp linear_search.cpp read_problem.cpp vec_op.cpp -o lbfgs
gd: steep_gradient_descent.cpp common.cpp common.h linear_search.cpp linear_search.h read_problem.cpp vec_op.cpp vec_op.h
	g++ steep_gradient_descent.cpp  common.cpp linear_search.cpp  read_problem.cpp  vec_op.cpp -o gradient_descent
