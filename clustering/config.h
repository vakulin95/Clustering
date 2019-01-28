/* config.h */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#if defined OPTION_TRACE_DEBUG
	#define TRACE(args ...) printf(args)
#else
	#define TRACE(args ...)
#endif /* OPTION_DEBUG_TRACE */

/* <! If defined output file will be small to decrease time
   > */
#define OPTION_SHORT_OUTPUT

/* <! Number of elements in output
      [Optional for OPTION_SHORT_OUTPUT]
   > */
#if defined OPTION_SHORT_OUTPUT
#define DEF_OUT_SIZE		1000
#endif	/* OPTION_SHORT_OUTPUT */
#define DEF_LOOP_OPTION 4
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

extern char g_arr_cluster_num[DEF_NUM_OF_ELEMENTS];
extern int g_arr_general[DEF_NUM_OF_ELEMENTS][DEF_DIMENSIONS];

#endif	/* __CONFIG_H__ */
