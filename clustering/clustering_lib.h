/* clustering_lib.h */

#ifndef __CLUSTERING_LIB_H__
#define __CLUSTERING_LIB_H__

#include "distance.h"

#if defined OPTION_TRACE_DEBUG
	#define TRACE(args ...) printf(args)
#else
	#define TRACE(args ...)
#endif /* OPTION_DEBUG_TRACE */

#if defined OPTION_DIST_EUCLIDEAN
#define CALC_DISTANCE(x1, x2, dim)	euclidean_distance_func(x1, x2, dim)
#endif

#endif	/* __CLUSTERING_LIB_H__ */
