/* algo.c */

#include "algo.h"

int quadratic_error_algorithm(void)
{
    size_t i, j, k;
    int ret;
    float arr_centroids[DEF_NUM_OF_CLUSTERS][DEF_DIMENSIONS];
    float old_centroid[DEF_NUM_OF_CLUSTERS];
    float min_distance, temp_distance;

    ret = 0;
    TRACE("\n-----------------------quadratic_error_algorithm-----------------------\n\n");

    input_data();
    
    /* generate random centroids */
    TRACE("Rand centroids:\n");
    for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {
	for (j = 0; j < DEF_DIMENSIONS; j++)
	{
	    arr_centroids[i][j] = g_arr_general[i][j];
	    TRACE("%f ", arr_centroids[i][j]);
	}
	TRACE("\n");
    }

#ifdef OPTION_TRACE_DEBUG
    k = 0;
#endif	/* OPTION_TRACE_DEBUG */
    temp_distance = FLT_MAX;
    while (temp_distance > DEF_STOP_DELTA)
    {
	/* Initial Cluster Distribution */
	for (i = 0; i < DEF_NUM_OF_ELEMENTS; ++i)
	{
	    min_distance = FLT_MAX;
	    for (j = 0; j < DEF_NUM_OF_CLUSTERS; ++j)
	    {
		temp_distance = CALC_DISTANCE_DF(g_arr_general[i], arr_centroids[j],
					      DEF_DIMENSIONS);
		if (temp_distance < min_distance)
		{
		    min_distance = temp_distance;
		    g_arr_cluster_num[i] = j;
		}
	    }
	}

	/* Upgrading Cluster Centers */
	temp_distance = 0;
	for (i = 0; i < DEF_NUM_OF_CLUSTERS; ++i)
	{
	    for (j = 0; j< DEF_DIMENSIONS; ++j)
	    {
		old_centroid[j] = arr_centroids[i][j];		
		arr_centroids[i][j] = calculate_average_func(i, j);
	    }

	    temp_distance += CALC_DISTANCE_FF(old_centroid, arr_centroids[i],
					  DEF_DIMENSIONS);
	}
	temp_distance /= DEF_NUM_OF_CLUSTERS;

#ifdef OPTION_TRACE_DEBUG
	k++;
	TRACE("iteration:\t%lu, distance delta:\t%f\n", k, temp_distance);
#endif	/* OPTION_TRACE_DEBUG */
    }

    output_result();
    
    TRACE("-----------------------------------------------------------------------\n\n");

    return ret;
}
