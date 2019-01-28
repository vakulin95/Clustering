/* gendata/main.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../clustering/clustering_lib.h"
#include "../clustering/config.h"
#include "../clustering/distance.h"

/* main defines */

/* <! Minimum and maximum thresholds
      of values in every dimension
   > */
#define DEF_MIN_VALUE		0
#define DEF_MAX_VALUE		100000

/* <! Threshold of the range of elements
      from each other in one cluster
   > */
#define DEF_ACCURACY	       	1000

/* <! If not null, at least 2 clusters will intersect 
   > */
#define DEF_CLUSTERS_INTERSECT 0

/* <! Path to output file defines 
   > */
#define DEF_OUT_PATH		"../data/"
#define DEF_PATH_STR_LEN	32

#define OPTION_EXECUTE
#define OPTION_RAND_CLUSTERS_SIZE
#define OPTION_CHECK_CENTROIDS
#define OPTION_SHUFFLE

/* globals */
int g_arr_general_out[DEF_NUM_OF_ELEMENTS][DEF_DIMENSIONS];
float g_arr_centroids[DEF_NUM_OF_CLUSTERS][DEF_DIMENSIONS];

/* <! Check that centroid ind is not clother 
      to other centroids then defined accuracy
   @ variables:
     - ind  : index of centroid 
   @ return:
     - index of the first found centroid, that is closer to 
       centroid with index ind then defined accuracy or 
       number of clusters otherwise
   > */
size_t check_centroid(size_t ind);

/* <! Generate point near centroid ind
   @ variables:
     - ind         : index of point
     - cluster_num : number of cluster 
   @ return:
     - NULL
   > */
int gen_point_near_centroid(size_t ind, size_t cluster_num);

/* <! Swap points into g_arr_general_out
   @ variables:
     - ind1 : index of point 1
     - ind2 : index of point 2
   @ return:
     - NULL
   > */
int swap_points(size_t ind1, size_t ind2);

int main()
{
    size_t i, j, k;
    FILE *ptr_f;
    char path[DEF_PATH_STR_LEN];
    long int arr_el_num_per_cluster[DEF_NUM_OF_CLUSTERS]; 
    long int el_num_left;
    
    int debug_tmp;

    printf("\n------------------------generate data-------------------------\n\n");
    
#if defined OPTION_EXECUTE
    
    srand(time(0));

    /* define number of elements in every cluster */
    el_num_left = DEF_NUM_OF_ELEMENTS;
    for (i = 1; i < DEF_NUM_OF_CLUSTERS; i++)
    {
#if defined OPTION_RAND_CLUSTERS_SIZE
	arr_el_num_per_cluster[i] = rand() % (DEF_NUM_OF_ELEMENTS / DEF_NUM_OF_CLUSTERS) + ((DEF_NUM_OF_ELEMENTS / DEF_NUM_OF_CLUSTERS) / 3);
#else
	arr_el_num_per_cluster[i] = DEF_NUM_OF_ELEMENTS / DEF_NUM_OF_CLUSTERS;
#endif /* OPTION_RAND_CLUSTERS_SIZE */
	el_num_left -= arr_el_num_per_cluster[i];
    }
    arr_el_num_per_cluster[0] = el_num_left;

    debug_tmp = 0;
    for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {
	TRACE("DEBUG: arr_el_num_per_cluster[%lu]: %ld\n", i, arr_el_num_per_cluster[i]);
	debug_tmp += arr_el_num_per_cluster[i];
    }

    if (DEF_NUM_OF_ELEMENTS != debug_tmp)
    {
	TRACE("DEBUG: CRITICAL: DEF_NUM_OF_ELEMENTS != debug_tmp\n\n");
	exit(1);
    }

    TRACE("\n");
    /* define centroids coordinates */
    if ((DEF_MAX_VALUE - DEF_ACCURACY) == (DEF_MIN_VALUE + DEF_ACCURACY))
    {
	TRACE("DEBUG: CRITICAL: check max and min borders!\n");
	exit(1);
    }
    
    for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {
	for (j = 0; j < DEF_DIMENSIONS; j++)
	{
	    g_arr_centroids[i][j] = rand() %
		((DEF_MAX_VALUE - DEF_ACCURACY) - (DEF_MIN_VALUE + DEF_ACCURACY)) +
		(DEF_MIN_VALUE + DEF_ACCURACY);
	}
    }

#if defined OPTION_CHECK_CENTROIDS
    /* locate centroids using accuracy */
    for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {
	k = 0;
	while (check_centroid(i) < DEF_NUM_OF_CLUSTERS)
	{
	    TRACE("DEBUG: centroids too close, try to generate centroids again\n");
	    for (j = 0; j < DEF_DIMENSIONS; j++)
	    {
		g_arr_centroids[i][j] = rand() %
		    ((DEF_MAX_VALUE - DEF_ACCURACY) - (DEF_MIN_VALUE + DEF_ACCURACY)) +
		    (DEF_MIN_VALUE + DEF_ACCURACY);
	    }
	    
	    if (++k > 10)
	    {
		TRACE("DEBUG: CRITICAL: accuracy too large!\n");
		exit(2);
	    }
	}
    }
#endif	/* OPTION_CHECK_CENTROIDS */

    if (DEF_CLUSTERS_INTERSECT && DEF_NUM_OF_CLUSTERS > 1)
    {
	TRACE("Clusters 0 and 1 wil intersect\n");
	
	for (i = 0; i < DEF_DIMENSIONS; i++)
	{
	    if ((g_arr_centroids[0][i] + DEF_ACCURACY / 2) < DEF_MAX_VALUE)
	    {
		g_arr_centroids[1][i] = g_arr_centroids[0][i] + DEF_ACCURACY / 2;
	    }
	}
    }
    
    /* main loop for g_arr_general_out */
    for (i = 0, k = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {
	for (j = 0; j < arr_el_num_per_cluster[i]; j++, k++)
	{
	    gen_point_near_centroid(k, i);
	}
    }

    /* print centroids */
    for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {	
	for (j = 0; j < DEF_DIMENSIONS; j++)
	{
	    TRACE("g_arr_centroids[%lu][%lu]:\t%.3f\n", i, j, g_arr_centroids[i][j]);
	}
	TRACE("\n");
    }
    TRACE("\n");

    /* print points and check that values are correct */
    for (i = 0; i < DEF_NUM_OF_ELEMENTS; i++)
    {	
	for (j = 0; j < DEF_DIMENSIONS; j++)
	{
	    if (g_arr_general_out[i][j] > DEF_MAX_VALUE || g_arr_general_out[i][j] < DEF_MIN_VALUE)
	    {
		TRACE("DEBUG: CRITICAL: g_arr_general_out[%lu][%lu]:\t%d\nMAX: %d MIN: %d\n\n",
		      i, j, g_arr_general_out[i][j], DEF_MAX_VALUE, DEF_MIN_VALUE);
		exit(1);
	    }
	    TRACE("g_arr_general_out[%lu][%lu]:\t%d\n", i, j, g_arr_general_out[i][j]);
	}
	TRACE("\n");
    }
    TRACE("\n");

#if defined OPTION_SHUFFLE
    /* shuffle points */
    for (i = 0; i < DEF_NUM_OF_ELEMENTS * 2; i++)
    {
	j = rand() % DEF_NUM_OF_ELEMENTS;
	
	swap_points((i % DEF_NUM_OF_ELEMENTS), j);
    }
#endif	/* OPTION_SHUFFLE */

    /* print points and check that values are correct once more */
    for (i = 0; i < DEF_NUM_OF_ELEMENTS; i++)
    {	
	for (j = 0; j < DEF_DIMENSIONS; j++)
	{
	    if (g_arr_general_out[i][j] > DEF_MAX_VALUE || g_arr_general_out[i][j] < DEF_MIN_VALUE)
	    {
		TRACE("DEBUG: CRITICAL: g_arr_general_out[%lu][%lu]:\t%d\nMAX: %d MIN: %d\n\n",
		      i, j, g_arr_general_out[i][j], DEF_MAX_VALUE, DEF_MIN_VALUE);
		exit(1);
	    }
	    TRACE("g_arr_general_out[%lu][%lu]:\t%d\n", i, j, g_arr_general_out[i][j]);
	}
	TRACE("\n");
    }
    
    printf("write data into file\n");

    sprintf(path, "%s%s", DEF_OUT_PATH, "input.dat");
    ptr_f = fopen(path, "w");

    for (i = 0; i < DEF_NUM_OF_ELEMENTS; i++)
    {	
	for (j = 0; j < DEF_DIMENSIONS; j++)
	{
	    fprintf(ptr_f, "%d ", g_arr_general_out[i][j]);
	}
	fprintf(ptr_f, "\n");
    }

    fclose(ptr_f);
    
#endif	/* OPTION_EXECUTE */
    printf("\n--------------------------------------------------------------\n");

    return 0;
}

size_t check_centroid(size_t ind)
{
    size_t i, ret;
    float dist;

    for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {
	if (i == ind)
	{
	    continue;
	}
	
	dist = CALC_DISTANCE_FF(g_arr_centroids[ind], g_arr_centroids[i], DEF_DIMENSIONS);
	TRACE("DEBUG: distance %f\n", dist);
	
	if (dist < 3 * DEF_ACCURACY)
	{
	    ret = i;
	    break;
	}
	else
	{
	    ret = DEF_NUM_OF_CLUSTERS;
	}
    }
    TRACE("\n");

    return ret;
}

int gen_point_near_centroid(size_t ind, size_t cluster_num)
{
    size_t i;
    int min_value, max_value;

    for (i = 0; i < DEF_DIMENSIONS; i++)
    {
	min_value = g_arr_centroids[cluster_num][i] - DEF_ACCURACY;
	max_value = g_arr_centroids[cluster_num][i] + DEF_ACCURACY;
	
	g_arr_general_out[ind][i] = rand() % (max_value - min_value) + min_value;
    }
    
    return 0;
}

int swap_points(size_t ind1, size_t ind2)
{
    size_t i;
    int temp;

    for (i = 0; i < DEF_DIMENSIONS; i++)
    {
	temp = g_arr_general_out[ind1][i];
	g_arr_general_out[ind1][i] = g_arr_general_out[ind2][i];
	g_arr_general_out[ind2][i] = temp;
    }

    return 0;
}
