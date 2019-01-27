/* config.h */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#if defined OPTION_TRACE_DEBUG
	#define TRACE(args ...) printf(args)
#else
	#define TRACE(args ...)
#endif /* OPTION_DEBUG_TRACE */

/* <! Number of clusters
      [Optional for Quadratic error algorithm]
   > */
#if defined OPTION_QUADR_ERR_ALGO
//#undef DEF_NUM_OF_CLUSTERS
//#define DEF_NUM_OF_CLUSTERS	4
#endif	/* OPTION_QUADR_ERR_ALGO */

/* <! Path to output file defines 
   > */
#define DEF_DATA_PATH		"data/"
#define DEF_PATH_STR_LEN	32

/* <! Algorithm Stop Criterion
   > */
#define DEF_STOP_DELTA		1.0

char g_arr_cluster_num[DEF_NUM_OF_ELEMENTS];
int g_arr_general[DEF_NUM_OF_ELEMENTS][DEF_DIMENSIONS];

#if defined OPTION_QUADR_ERR_ALGO
int g_arr_elnum_in_cluster[DEF_NUM_OF_CLUSTERS];
#endif	/* OPTION_QUADR_ERR_ALGO */

#endif	/* __CONFIG_H__ */
