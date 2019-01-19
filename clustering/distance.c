/* distance.c */

#include "distance.h"

float euclidean_distance_func(int *x1, int *x2, int dim)
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
