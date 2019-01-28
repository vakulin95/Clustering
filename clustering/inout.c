/* inout.c */

#include "inout.h"
#include "config.h"

void input_data(void)
{
    size_t i, j;
    FILE *ptr_f;
    char path[DEF_PATH_STR_LEN];    

    TRACE("<<input_data\n");
    
    sprintf(path, "%s%s", DEF_DATA_PATH, "input.dat");

    ptr_f = fopen(path, "r");

    if (ptr_f == 0)
    {
	TRACE("DEBUG: input_data() - open file error!\n");
    }
    
    for (i = 0; i < DEF_NUM_OF_ELEMENTS; ++i)
    {
	for (j = 0; j < DEF_DIMENSIONS - 1; ++j)
	{
	    fscanf(ptr_f, "%d ", &g_arr_general[i][j]);
	    /* TRACE("%d ", g_arr_general[i][j]); */
	}
	fscanf(ptr_f, "%d\n", &g_arr_general[i][j]);
	/* TRACE("%d\n", g_arr_general[i][j]); */
    }

    fclose(ptr_f);
    TRACE(">>input_data\n");
    
    return;
}

void output_result(void)
{
    size_t i, j;
    FILE *ptr_f;
    char path[DEF_PATH_STR_LEN];
    int step;

    TRACE(">>output_result\n");
    
    sprintf(path, "%s%s", DEF_DATA_PATH, "output.dat");

    ptr_f = fopen(path, "w");

    if (ptr_f == 0)
    {
	TRACE("DEBUG: output_result() - open file error!\n");
    }
    
#if defined OPTION_SHORT_OUTPUT
    step = DEF_NUM_OF_ELEMENTS / DEF_OUT_SIZE;

    if (!step)
    {
	step = 1;
    }
    
    for (i = 0; i < DEF_NUM_OF_ELEMENTS; i += step)
    {
	for (j = 0; j < DEF_DIMENSIONS; ++j)
	{
	    fprintf(ptr_f, "%d ", g_arr_general[i][j]);
	}
	fprintf(ptr_f, "%d\n", g_arr_cluster_num[i]);
    }
#else
    for (i = 0; i < DEF_NUM_OF_ELEMENTS; i++)
    {
	for (j = 0; j < DEF_DIMENSIONS; ++j)
	{
	    fprintf(ptr_f, "%d ", g_arr_general[i][j]);
	}
	fprintf(ptr_f, "%d\n", g_arr_cluster_num[i]);
    }    
#endif	/* OPTION_SHORT_OUTPUT */
    
    fclose(ptr_f);
    TRACE("<<output_result\n");
    
    return;
}

void output_time(double t, char name[32])
{
    size_t i, j;
    FILE *ptr_f;
    char path[DEF_PATH_STR_LEN];
    int step;

    TRACE(">>output_time\n");
    
    sprintf(path, "%s%s", DEF_DATA_PATH, name);

    ptr_f = fopen(path, "a");

    if (ptr_f == 0)
    {
	TRACE("DEBUG: output_result() - open file error!\n");
    }
    
    fprintf(ptr_f, "%d %lf\n", DEF_NUM_OF_ELEMENTS, t);
    
    fclose(ptr_f);
    TRACE("<<output_time\n");
    
    return;
}
