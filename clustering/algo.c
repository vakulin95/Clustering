/* algo.c */

#include "config.h"
#include "distance.h"
#include "inout.h"
#include "algo.h"

char g_arr_cluster_num[DEF_NUM_OF_ELEMENTS];
int g_arr_general[DEF_NUM_OF_ELEMENTS][DEF_DIMENSIONS];

int quadratic_error_algorithm(void)
{
    size_t i, j, k, m, temp_ind;
    int ret;
    float arr_centroids[DEF_NUM_OF_CLUSTERS][DEF_DIMENSIONS];
    float old_centroid[DEF_NUM_OF_CLUSTERS];
    float min_distance, temp_distance;

    ret = 0;
    srand(time(0));
    TRACE("\n-----------------------quadratic_error_algorithm-----------------------\n\n");
    
    /* generate random centroids */
    TRACE("Rand centroids:\n");
    for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
    {
	temp_ind = rand() % DEF_NUM_OF_ELEMENTS;
	
	for (j = 0; j < DEF_DIMENSIONS; j++)
	{
	    arr_centroids[i][j] = g_arr_general[temp_ind][j];
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
    
    TRACE("-----------------------------------------------------------------------\n\n");

    return ret;
}

int parallel_quadratic_error_algorithm(void)
{
    size_t i, j, k, m, temp_ind;
    int ret, rank, size, thread_step;
    float arr_centroids[DEF_NUM_OF_CLUSTERS][DEF_DIMENSIONS];
    float old_centroid[DEF_NUM_OF_CLUSTERS];
    float *min_distance, *temp_distance;
    double t1, t2;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0)
    {
	ret = 0;
	t1 = MPI_Wtime();
	srand(time(0));
	TRACE("\n---------------parallel_quadratic_error_algorithm---------------\n\n");

	temp_distance = (float*)malloc(sizeof(float) * size);
	min_distance = (float*)malloc(sizeof(float) * size);
	
	/* generate random centroids */
	TRACE("Rand centroids:\n");
	for (i = 0; i < DEF_NUM_OF_CLUSTERS; i++)
	{
	    temp_ind = rand() % DEF_NUM_OF_ELEMENTS;
	
	    for (j = 0; j < DEF_DIMENSIONS; j++)
	    {
		arr_centroids[i][j] = g_arr_general[temp_ind][j];
		TRACE("%f ", arr_centroids[i][j]);
	    }
	    TRACE("\n");
	}

	temp_distance[0] = FLT_MAX;
	thread_step = DEF_NUM_OF_ELEMENTS / size;
    }
	

    for (m = 0; m < DEF_LOOP_OPTION; m++)
    {
	/* Initial Cluster Distribution */
	for (i = rank * thread_step; i < (rank + 1) * thread_step; i++)
	{
	    min_distance[rank] = FLT_MAX;
	    for (j = 0; j < DEF_NUM_OF_CLUSTERS; ++j)
	    {
		temp_distance[rank] = CALC_DISTANCE_DF(g_arr_general[i], arr_centroids[j],
					      DEF_DIMENSIONS);
		if (temp_distance[rank] < min_distance[rank])
		{
		    min_distance[rank] = temp_distance[rank];
		    g_arr_cluster_num[i] = j;
		}
	    }
	}

	/* Upgrading Cluster Centers */
	/* temp_distance = 0; */
	for (i = rank; i < DEF_NUM_OF_CLUSTERS; i += size)
	{
	    for (j = 0; j < DEF_DIMENSIONS; ++j)
	    {
		/* old_centroid[j] = arr_centroids[i][j]; */
		arr_centroids[i][j] = calculate_average_func(i, j);
	    }

	    /* temp_distance += CALC_DISTANCE_FF(old_centroid, arr_centroids[i], */
	    /* 				  DEF_DIMENSIONS); */
	}
	/* temp_distance /= DEF_NUM_OF_CLUSTERS; */
    }

    t2 = MPI_Wtime();

    if (rank == 0)
    {
	if (size == 1)
	{
	    output_time(t2 - t1, "outdat1.dat");
	}
	else
	{
	    output_time(t2 - t1, "outdat2.dat");
	}
    }
    
    MPI_Finalize();
    
    TRACE("-----------------------------------------------------------------------\n\n");

    return ret;
}
