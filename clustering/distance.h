/* distance.h */

#ifndef __DISTANCE_H__
#define __DISTANCE_H__

#include "config.h"

#include <stdio.h>
#include <math.h>

#if defined OPTION_DIST_EUCLIDEAN
#define CALC_DISTANCE_DD(x1, x2, dim)	euclidean_distance_func_dd(x1, x2, dim)
#define CALC_DISTANCE_DF(x1, x2, dim)	euclidean_distance_func_df(x1, x2, dim)
#define CALC_DISTANCE_FF(x1, x2, dim)	euclidean_distance_func_ff(x1, x2, dim)
#endif

float euclidean_distance_func_dd(int *x1, int *x2, int dim);
float euclidean_distance_func_df(int *x1, float *x2, int dim);
float euclidean_distance_func_ff(float *x1, float *x2, int dim);

float calculate_average_func(size_t cluster, int dimension);

#endif	/* __DISTANCE_H__ */
