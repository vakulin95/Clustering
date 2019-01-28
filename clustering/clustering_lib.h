/* clustering_lib.h */

#ifndef __CLUSTERING_LIB_H__
#define __CLUSTERING_LIB_H__

#include "distance.h"
#include "inout.h"
#include "algo.h"

#if defined OPTION_QUADR_ERR_ALGO
#define CLUSTER_DATA() parallel_quadratic_error_algorithm()
#else
#define CLUSTER_DATA()
#endif	/* OPTION_QUADR_ERR_ALGO */

#endif	/* __CLUSTERING_LIB_H__ */
