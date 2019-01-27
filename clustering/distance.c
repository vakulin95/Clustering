/* distance.c */

#include "distance.h"

float euclidean_distance_func_dd(int *x1, int *x2, int dim)
{
    size_t i;
    float ret = 0;
    
    /* TRACE(">>euclidean_distance_func\n"); */

    for (i = 0; i < dim; i++)
    {
	ret += (x1[i] - x2[i]) * (x1[i] - x2[i]);
    }

    ret = sqrt(ret);
    
    /* TRACE("<<euclidean_distance_func, ret = %f\n", ret); */
    
    return ret;
}

float euclidean_distance_func_df(int *x1, float *x2, int dim)
{
    size_t i;
    float ret = 0;
    
    /* TRACE(">>euclidean_distance_func\n"); */

    for (i = 0; i < dim; i++)
    {
	ret += (x1[i] - x2[i]) * (x1[i] - x2[i]);
    }

    ret = sqrt(ret);
    
    /* TRACE("<<euclidean_distance_func, ret = %f\n", ret); */
    
    return ret;
}

float euclidean_distance_func_ff(float *x1, float *x2, int dim)
{
    size_t i;
    float ret = 0;
    
    TRACE(">>euclidean_distance_func\n");

    for (i = 0; i < dim; i++)
    {
	ret += (x1[i] - x2[i]) * (x1[i] - x2[i]);
    }

    ret = sqrt(ret);
    
    TRACE("<<euclidean_distance_func, ret = %f\n", ret);
    
    return ret;
}

float calculate_average_func(size_t cluster, int dimension)
{
    size_t i;
    int elnum_in_cluster;
    float sum;
    float retval;

    TRACE(">>calculate_average_func\n");   
    sum = 0;
    elnum_in_cluster = 0;
    for (i = 0; i < DEF_NUM_OF_ELEMENTS; ++i)
    {
	if (g_arr_cluster_num[i] == cluster)
	{
	    elnum_in_cluster++;
	    sum += g_arr_general[i][dimension];
	}
    }

    retval = sum/elnum_in_cluster;
    TRACE("<<calculate_average_func, ret = %f\n", retval);
    
    return retval;
}
